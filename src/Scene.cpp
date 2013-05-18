#include "Scene.h"

Scene::Scene():
Model(new ModelMesh("data/meshes/bigscene.obj", 1.0f, 1.0f, 1.0f), "Ground", "SimpleColor"){

	minVertexValues = getMesh()->getMinVertexValues();
	maxVertexValues = getMesh()->getMaxVertexValues();
	sceneDimensions = maxVertexValues - minVertexValues;
	printf("sceneDimensions: x = %f,  y = %f,  z = %f\n",
		sceneDimensions.x, sceneDimensions.y, sceneDimensions.z);
}

std::vector<LightSource*> Scene::lightSources;

Scene::~Scene(){

}



void Scene::initScene(){
	//First render the heightmap for the "ground mesh" only.
	
	bool renderToHeightMapSupported = true;
	const int HEIGHT_MAP_RESOLUTION = 512;
    if(!renderToHeightMap(HEIGHT_MAP_RESOLUTION, HEIGHT_MAP_RESOLUTION)){
    	renderToHeightMapSupported = false;
    	std::string path = "data/heightmap/heightmap.bmp";
    	readBMP(path.c_str());
    }

    //Now we can use the previously rendered heightmap to place static objects
    initStaticObjects();

	//Render to the heightmap again, now with static game objects added.
    if(renderToHeightMapSupported)
    	renderToHeightMap(HEIGHT_MAP_RESOLUTION, HEIGHT_MAP_RESOLUTION);

	initDynamicObjects();

	printf("TOTAL NUMBER OF VERTICES: %i\n", getNumberOfVertices());
}

void Scene::initStaticObjects(){
	StaticGameObject* sgo;
	srand(time(NULL));
	for (int i = 0; i < 30; ++i){
		float x = sceneDimensions.x * (rand()/(float)RAND_MAX) + minVertexValues.x;
		float z = sceneDimensions.z * (rand()/(float)RAND_MAX) + minVertexValues.z;
		float y = getYPosition(x, z);
		float phi 	= 360.0f*(rand()/(float)RAND_MAX);
		float size = (rand()/(float)RAND_MAX) + 1.0f;

		sgo = new StaticGameObject("data/meshes/tree.obj");
		sgo->setPosition(x, y, z);
		sgo->setSize(size);
		sgo->setRotation(phi);

		addChildNode(sgo->getSceneGraphBranch());
	}
}

void Scene::initDynamicObjects(){
	Player * body1 = new Character;
	body1->setPosition(0.0f, 0.0f, 5.0f);
	addPlayer(body1);
/*
	Player * body2 = new Character;
	body2->setPosition(-5.0f, 0.0f, 0.0f);
	addPlayer(body2);
	
	Player * body3 = new Player;
	body3->setPosition(5.0f, 0.0f, 0.0f);
	addPlayer(body3);

	Player * body4 = new Player;
	body4->setPosition(0.0f, 0.0f, -5.0f);
	addPlayer(body4);

	Player * body5 = new Player;
	body5->setPosition(0.0f, 0.0f, 0.0f);
	addPlayer(body5);

	Player * body6 = new Player;
	body6->setPosition(5.0f, 0.0f, -5.0f);
	addPlayer(body6);

	Player * body7 = new Player;
	body7->setPosition(-5.0f, 0.0f, 5.0f);
	addPlayer(body7);
	*/



	Camera* camera = new Camera(-30, 5, 15);
	camera->setLookAt(0, 0, 0);
	camera->setVelocity(0.05/2, 0.02/2, 0.01/2);

	FollowCamera* fc = new FollowCamera(players);

	//Uncomment the two lines below to get simple static front view
	//camera->setPosition(0, 20, -15);
	//camera->setVelocity(0, 0, 0);

	//FollowCamera* followCamera = new FollowCamera(body1, 0.0f, 30.0f, 30.0f);

	cameras.push_back(fc);

	cameras.push_back(camera);
	//cameras.push_back(followCamera);

}


void Scene::addPlayer(Player * p){
	//Put player on the ground
	p->setYPosition(getYPosition(p->getPosition().x, p->getPosition().z));
	addChildNode(p->getSceneGraphBranch());
	players.push_back(p);
}


void Scene::update(float dt){

	for (int i = 0; i < cameras.size(); ++i){
		cameras[i]->update(dt);
		cameras[i]->calcMatrices();
	}

	for (int i = 0; i < players.size(); ++i){
		players[i]->updateUserInputs();
		updatePlayerPosition5Sa(players[i], cameras[0]);
		updatePlayerHeadDirection(players[i], cameras[0]);
		players[i]->update(dt);
	}
}

void Scene::updatePlayerHeadDirection(Player* p, Camera* cam) const{
	glm::vec2 state;
	p->getRightControllerValues(state.x, state.y);

	if (cam != NULL){
		state = getStateInCamSpace(state, p->getPosition(), cam);

    float phiTarget = 180.0f / 3.141592 * glm::atan(state.x,-state.y);
    float phiDiff = fmod(phiTarget - p->head.getPhi() + 3*180.0f, 360.0f) - 180.0f;
    p->head.setAngleVel(phiDiff);
	/*
    sgct::MessageHandler::Instance()->print(
        "phi = %f, phiTarget = %f, phiDiff = %f", head.getPhi(), phiTarget, phiDiff);
    sgct::MessageHandler::Instance()->print("\r");
	*/
	}
}

void Scene::updatePlayerPosition1Sa(Player * p, Camera* cam) const{
	float xState, yState;
	p->getLeftControllerValues(xState, yState);
	//Uppdatera riktningen
    p->setDirection(180.0f / 3.141592f * glm::atan(xState,-yState));

/*
    Beräkna X och Y i heighmappen för "den kritiska ytterkanten" av player. Dvs positionen
    för meshens främre kant. Vi kan beräkna den genom att vi har tillgång till
    radien. Sedan måste vi veta vilket håll vi är påväg mot. Vi använder
        xState
        yState
    för detta. Dock kommer vi kunna "krypa" i branta backar som man annars
    inte kan gå i. Därför normaliserar vi dessa först innan vi använder
    dom. OBS vi kan inte normalisera en nollvektor, så vi måste testa detta först.
*/
    glm::vec2 sn = glm::vec2(0.0f, 0.0f);
    if(xState || yState)
        sn = glm::normalize(glm::vec2(xState, yState));


    //Beräkna vilket X och Y players främre kant skulle ha i heightmappen.
    int imgX = heightmapWidth/2  + worldToHeightmapX * (p->getPosition().x + sn.x*p->getBaseRadius());
    int imgY = heightmapHeight/2 + worldToHeightmapZ * (p->getPosition().z - sn.y*p->getBaseRadius());


    //Testa om players främre kant befinner sig innanför heightmappen
    if (0 < imgX && imgX < heightmapWidth &&
        0 < imgY && imgY < heightmapHeight){



	    //Beräkna höjden för players främre kant.
	    int imgXYPos = (int)(imgX + heightmapWidth*imgY);
	    float yTemp = heightmap[imgXYPos];

	    //Temporärt kan vi använde denna som ett tröskelvärde
	    //som avgör hur brant en player kan gå.
	    float maxStep = 2.0f;

	    //Testa om denna höjdskillnad är för stor för att kunna röra sig upp för.
        if(abs(yTemp - p->getPosition().y) < maxStep){
	        //Fritt fram för player att röra sig!
	        //Vi tar fram players riktiga position i höjdmappen
	        //dvs den som baseras på centrum av player
	        imgX = heightmapWidth/2  + worldToHeightmapX * (p->getPosition().x);
	        imgY = heightmapHeight/2 + worldToHeightmapZ * (p->getPosition().z);

	        //Hämta höjden från mappen
	        imgXYPos = (int)(imgX + heightmapWidth*imgY);
	        yTemp = heightmap[imgXYPos];

	        //Sätt nya värden på hastighet och höjd
	        p->setVelocity(xState, 0.0f, -yState);
	        p->setYPosition(yTemp);

            /*
		    sgct::MessageHandler::Instance()->print(
		      "position.x = %f  position.z = %f  imgX = %i  imgY = %i  heightmap[%i] = %f",
		       getPosition().x, getPosition().z, imgX,      imgY,                imgXYPos, yTemp);
		    sgct::MessageHandler::Instance()->print("\r");
			*/
	        return;
    	}
    }

    //Om vi befinner oss utanför mappen eller
    //om vi har en för brant backe framför oss så stå still
    p->setVelocity(0.0f, 0.0f, 0.0f);
}

void Scene::updatePlayerPosition4Sa(Player * p, Camera* cam) const{

	glm::vec2 state;
	p->getLeftControllerValues(state.x, state.y);
	if (cam != NULL)
		state = getStateInCamSpace(state, p->getPosition(), cam);
	p->setDirection(180.0f / 3.141592f * glm::atan(state.x,-state.y));



	//pre-compute
	int halfHw = heightmapWidth/2;
	int halfHh = heightmapHeight/2;
	float r = p->getBaseRadius();

    int imgX 	= halfHw + worldToHeightmapX * (p->getPosition().x);
	int imgY 	= halfHh + worldToHeightmapZ * (p->getPosition().z);
    int imgXmax = halfHw + worldToHeightmapX * (p->getPosition().x + r);
    int imgXmin = halfHw + worldToHeightmapX * (p->getPosition().x - r);
    int imgYmax = halfHh + worldToHeightmapZ * (p->getPosition().z - r);
    int imgYmin = halfHh + worldToHeightmapZ * (p->getPosition().z + r);


    //Test if max/min values are inside map
    if (0 < imgXmin && imgXmax < heightmapWidth &&
    	0 < imgYmin && imgYmax < heightmapHeight){

    	float maxStep = 0.5f;
    	float yXmax = heightmap[ (imgXmax + heightmapWidth*imgY) ];
    	float yXmin = heightmap[ (imgXmin + heightmapWidth*imgY) ];
    	float yYmax = heightmap[ (imgX + heightmapWidth*imgYmax) ];
    	float yYmin = heightmap[ (imgX + heightmapWidth*imgYmin) ];

    	glm::vec2 grad = glm::vec2((yXmax-yXmin)/r, (yYmax-yYmin)/r);
    	float steep = glm::length(grad);
    	if(steep > maxStep){
	    	grad = glm::normalize(grad);
	    	glm::mat2 T = glm::mat2(grad, glm::vec2(-grad.y, grad.x));
	    	glm::vec2 eState = T * state;
	    	eState[0] = -0.5f * steep * steep;
	    	state = glm::transpose(T) * eState;
    	}

    	p->setYPosition((yXmax+yXmin+yYmax+yYmin)/4.0f);
    	p->setVelocity(state.x, 0.0f, -state.y);
    	return;

    }

    p->setVelocity(0.0f, 0.0f, 0.0f);
}


void Scene::updatePlayerPosition5Sa(Player * p, Camera* cam) const{

	glm::vec2 state;
	p->getLeftControllerValues(state.x, state.y);
	if (cam != NULL)
		state = getStateInCamSpace(state, p->getPosition(), cam);



	//pre-compute
	int halfHw = heightmapWidth/2;
	int halfHh = heightmapHeight/2;
	float r = p->getBaseRadius() * 0.5f;


	//Calculate X och Y coordinates for player's front in heightmap
    glm::vec2 sn = glm::vec2(0.0f, 0.0f);
    if(state.x || state.y){
    	sn = glm::normalize(state);
    	p->setDirection(180.0f / 3.141592f * glm::atan(state.x,-state.y));
    }

    int imgX = halfHw + worldToHeightmapX * (p->getPosition().x + sn.x*r);
    int imgY = halfHh + worldToHeightmapZ * (p->getPosition().z - sn.y*r);


    //Player front inside map?

	bool atEdge = false;
	if ((0 		> imgX 			  && state.x < 0.0f) ||
		(imgX 	> heightmapWidth  && state.x > 0.0f)){
		sn.x = 0.0f;
		atEdge = true;
	}

	if ((0 		> imgY 			  && state.y < 0.0f) ||
		(imgY 	> heightmapHeight && state.y > 0.0f)){
		sn.y = 0.0f;
		atEdge = true;
	}

    if (!atEdge){

	    //Don't need X and P for player front anymore. now sample 4.
	    imgX 	 	= halfHw + worldToHeightmapX * (p->getPosition().x);
		imgY 		= halfHh + worldToHeightmapZ * (p->getPosition().z);

	    int imgXmax = halfHw + worldToHeightmapX * (p->getPosition().x + r);
	    int imgXmin = halfHw + worldToHeightmapX * (p->getPosition().x - r);
	    int imgYmax = halfHh + worldToHeightmapZ * (p->getPosition().z - r);
	    int imgYmin = halfHh + worldToHeightmapZ * (p->getPosition().z + r);

	    //If max/min values outside heigtmap -> set height to 0.
    	float yXmax = 0;
    	float yXmin = 0;
    	float yYmax = 0;
    	float yYmin = 0;
    	float validSamples = 0.0f;

    	if (imgXmax < heightmapWidth ){ yXmax = heightmap[ (imgXmax + heightmapWidth*imgY) ]; ++validSamples;}
		if (0 		< imgXmin		 ){ yXmin = heightmap[ (imgXmin + heightmapWidth*imgY) ]; ++validSamples;}
		if (imgYmax < heightmapHeight){ yYmax = heightmap[ (imgX + heightmapWidth*imgYmax) ]; ++validSamples;}
		if (0 		< imgYmin		 ){ yYmin = heightmap[ (imgX + heightmapWidth*imgYmin) ]; ++validSamples;}

		if(validSamples == 4.0f){

	    	//Calc gradient based on the 4 height samples
	    	glm::vec2 grad = glm::vec2((yXmax-yXmin)/r, -(yYmax-yYmin)/r);
	    	float steep = glm::length(grad);
	    	float maxStep = 0.5f;
	    	if(steep > maxStep){

	    		//Define new ON-base from grad and a vector orthogonal to grad
		    	grad = glm::normalize(grad);
		    	glm::mat2 T = glm::mat2(grad, glm::vec2(-grad.y, grad.x));

		    	//Transform state to the new base e.
		    	glm::vec2 eState = T * sn;

		    	//Remove or decrease velocity along positive grad

		    	eState.x -= 0.5f*steep;

		    	//Back to world coordinates.
		    	//T^t = T^-1 since normalized base(?)
		    	state = glm::transpose(T) * eState;
	    	}
	    }

    	p->setYPosition((yXmax+yXmin+yYmax+yYmin)/validSamples);
    	p->setVelocity(state.x, 0.0f, -state.y);

    	return;
    }

    p->setVelocity(sn.x, 0.0f, -sn.y);

}

glm::vec2 Scene::getStateInCamSpace(glm::vec2 state, glm::vec3 playerPos, Camera* cam) const{
	glm::vec3 camToPlayerDirXYZ = cam->getLookAt() - cam->getPosition();// + playerPos;
    glm::vec2 camDir = glm::vec2(-camToPlayerDirXYZ.z, -camToPlayerDirXYZ.x);

    if (camDir.x || camDir.y){
    	camDir = glm::normalize(camDir);
    	glm::mat2 T = glm::mat2(camDir, glm::vec2(-camDir.y, camDir.x));
    	glm::vec2 tState = T * state;
    	return tState;
	}
	else return state;
}


float Scene::getYPosition(float x, float z){
	//Här kan man optimera genom att lagra uträkningen av heigtWidth/sceneDimensions.x osv
	int imgX = heightmapWidth /2 + worldToHeightmapX * x;
	int imgY = heightmapHeight/2 + worldToHeightmapZ * z;

	int imgXYPos = (int)(imgX + heightmapWidth*imgY);

	if (0 < imgX && imgX < heightmapWidth &&
	    0 < imgY && imgY < heightmapHeight)
	    return heightmap[imgXYPos];
	return -1.0f;
}

void Scene::addGenerations(Model* mother, int n){
	if(n<=0)
		return;
	GameObject* child1 = new GameObject(2, 1, 1, 0.7);
	GameObject* child2 = new GameObject(-2, 1, 1, 0.7);

	mother->addChildNode(child1->getSceneGraphBranch());
	mother->addChildNode(child2->getSceneGraphBranch());

	addGenerations(child1->getMainModel(), n-1);
	addGenerations(child2->getMainModel(), n-1);

}

void Scene::drawScene(glm::mat4 P, glm::mat4 V) {
	renderToScreen(P, V, glm::mat4(1.0f));
}

void Scene::renderToScreen(glm::mat4 P, glm::mat4 V, glm::mat4 parentModelMatrix){
	Model::renderToScreen(P, V, parentModelMatrix);
}

int _n = 0;
bool Scene::renderToHeightMap(int xRes, int yRes){

	// The FBO that will be used when rendering the heightmap
	GLuint frameBufferObj = 0;
	GLuint depthTex = 0;

	glGenFramebuffers(1, &frameBufferObj); //generate the framebuffer object
	glGenTextures(1, &depthTex);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObj); //bind it to the framebuffer target
	glBindTexture(GL_TEXTURE_2D, depthTex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, xRes, yRes, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depthTex, 0);

	// Check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Unable to create framebuffer for height map!" << std::endl;
		return false;
	}

	// We want to render from this view
	glm::mat4 V = glm::lookAt(
		glm::vec3(0,0,0), // position
		glm::vec3(0,-1,0), // look at: downwards
		glm::vec3(0,0,-1)); // up vector: -z, makes x point to the right

	glm::vec3 minVertexValues = getMesh()->getMinVertexValues();
	glm::vec3 maxVertexValues = getMesh()->getMaxVertexValues();

	// Create the box where the orthogonal projection takes place
	glm::mat4 P = glm::ortho(
		minVertexValues.x, // left
		maxVertexValues.x, // right
		minVertexValues.z, // bottom
		maxVertexValues.z, // top
		-maxVertexValues.y, // zNear
		-minVertexValues.y); // zFar ---- z is y since we look from above

	//First model matrix is just a enhetsmatrisnångångnudå
	glm::mat4 M(1.0);
	glm::mat4 VP = P * V;

	glViewport(0,0,xRes,yRes);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render to the FBO
	renderToDepthBuffer(VP, M);
	glDisable(GL_CULL_FACE);

	//Och hänne ska vi använda glReadPixels..
	// Actual RGB data
    unsigned char* allData = new unsigned char [xRes * yRes * 3];
	heightmap = new float[xRes * yRes];

    heightmapWidth = xRes;
    heightmapHeight = yRes;
    heightmapArrayLength = xRes * yRes;

    worldToHeightmapX =  xRes  / sceneDimensions.x;
    worldToHeightmapZ = -yRes / sceneDimensions.z;

	glReadPixels(
		0,
 		0,
 		xRes,
 		yRes,
 		GL_RGB,
 		GL_UNSIGNED_BYTE,
 		allData);

	int maxDepth = allData[0];
    int minDepth = allData[0];
    for(int i = 3; i < xRes * yRes * 3; i+=3){
    	if(allData[i] > maxDepth) maxDepth = allData[i];
    	if(allData[i] < minDepth) minDepth = allData[i];
    }

    float scale = sceneDimensions.y / ( (float)(maxDepth - minDepth));
    printf("  maxDepth = %i,  minDepth = %i,  scale = %f\n", maxDepth, minDepth, scale);


    float minSceneY = minVertexValues.y;
    for(int i = 0; i < xRes * yRes * 3; i+=3){
   		//1. Before scaling the image, we need to have 0 in heightmap
   		//means 0 in world coordinates. Therefor reduce all pixels with
   		//minDepth. Now minimum depth will be 0.

    	//2. Scale

   		//3. After the scaling, we need to add the minimum value from the
   		//scene vertices. That makes the heighmap place the player correctly
   		//according to the actual mesh.

        heightmap[i/3] = (float)(allData[i] - minDepth)*scale + minSceneY;

    }

	delete[] allData;
	glDeleteFramebuffers(1, &frameBufferObj);
	glDeleteTextures(1, &depthTex);

	return true;
}


void Scene::readBMP(const char* filename)
{
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * allData;

    // Open the file
    FILE * file = fopen(filename,"rb");
    if (!file){
    	printf("Image could not be opened\n");
    }
    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    	printf("Not a correct BMP file\n");
    }
    if ( header[0]!='B' || header[1]!='M' ){
    	printf("Not a correct BMP file\n");
    }


    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    heightmapWidth = width;
    heightmapHeight = height;
    heightmapArrayLength = width * height;

    worldToHeightmapX =  heightmapWidth  / sceneDimensions.x;
    worldToHeightmapZ = -heightmapHeight / sceneDimensions.z;

    printf("heightmap:\n  imageSize read from file = %i\n", imageSize);
    printf("  width * height * 3 = %i\n", width * height * 3);

    //Imagesize include the header or something. It's too big.
    //We cant use it to loop through the rows and column in the pic,
    //we will get outside the array bounds and get rubbish values.
    //Instead, simply define image size as below:
    imageSize = width*height*3;
    if (dataPos==0)      dataPos=54;

    // Create a buffer
    allData = new unsigned char [imageSize];
    heightmap = new float[imageSize/3];

    fread(allData,1,imageSize,file);

    unsigned char maxDepth = allData[0];
    unsigned char minDepth = allData[0];
    for(int i = 3; i < imageSize; i+=3){
    	if(allData[i] > maxDepth) maxDepth = allData[i];
    	if(allData[i] < minDepth) minDepth = allData[i];
    	if(allData[i] == 0)
    		printf("  ZERO PIXEL at %i\n", i/3);
    }

    float scale = sceneDimensions.y / ( (float)(maxDepth - minDepth));
    printf("  maxDepth = %i,  minDepth = %i,  scale = %f\n", maxDepth, minDepth, scale);


    float minSceneY = minVertexValues.y;
    for(int i = 0; i < imageSize; i+=3){
   		//1. Before scaling the image, we need to have 0 in heightmap
   		//means 0 in world coordinates. Therefor reduce all pixels with
   		//minDepth. Now minimum depth will be 0.

    	//2. Scale

   		//3. After the scaling, we need to add the minimum value from the
   		//scene vertices. That makes the heighmap place the player correctly
   		//according to the actual mesh.

        heightmap[i/3] = (float)(allData[i] - minDepth)*scale + minSceneY;
    }

    fclose(file);
}
