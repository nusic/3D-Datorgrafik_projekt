#include "Scene.h"

Scene::Scene():

Model("demo_map", "ground_texture", "SimpleColor"){
	printf("\nScene object created\n");
	team.push_back(new Team());
	team.push_back(new Team());
	team[1]->camera->setAngle(3.14f);

	minVertexValues = getMesh()->getMinVertexValues();
	maxVertexValues = getMesh()->getMaxVertexValues();
	sceneDimensions = maxVertexValues - minVertexValues;
	printf("Dimensions from Scene mesh:\nx (length) = %f\ny (height) = %f\nz (width)  = %f\n\n",
		sceneDimensions.x, sceneDimensions.y, sceneDimensions.z);

	nodes = 0;
	verts = 0;
}

std::vector<LightSource*> Scene::lightSources;

Scene::~Scene(){

}



void Scene::initScene(){
	//First render the heightmap for the "ground mesh" only.
	int w = 45;
	std::cout << std::setw(w) << " " << "NODES | VERTICES" << std::endl;
	printf("Rendering hightmap ...\n");
	bool renderToHeightMapSupported = true;
	const int HEIGHT_MAP_RESOLUTION = 2048;

    if(!renderToHeightMap(HEIGHT_MAP_RESOLUTION, HEIGHT_MAP_RESOLUTION)){
    	renderToHeightMapSupported = false;
    	std::string path = "data/heightmap/heightmap.bmp";
    	readBMP(path.c_str());
    }
  



    
    std::cout << std::setw(w) << std::left << "Adding static physical objects ... ";
    initStaticPhysicalObjects();
  	printLoadingStats();

	printf("Rendering hightmap ...\n");
    if(renderToHeightMapSupported)
    	renderToHeightMap(HEIGHT_MAP_RESOLUTION, HEIGHT_MAP_RESOLUTION);    



    std::cout << std::setw(w) << std::left << "Adding static non-physical objects ... ";
    initStaticNonPhysicalObjects();
	printLoadingStats();



    std::cout << std::setw(w) << std::left << "Adding dynamic objects ... ";
	initDynamicObjects();
	printLoadingStats();
	nodes = verts = 0;

	std::cout << std::setw(w) << " " << "=============" << std::endl;
	std::cout << std::setw(w) << "TOTAL:";
	printLoadingStats();
	printf("\n");
	
}

void Scene::printLoadingStats(){
	int nodesTot = countChildNodes(true);
    int vertsTot = getNumberOfVertices();
    std::cout << std::setw(5) << std::right << nodesTot-nodes << " | ";
    std::cout << std::setw(5) << std::left << vertsTot-verts << std::endl;
    
    nodes = nodesTot;
	verts = vertsTot;
}

void Scene::initStaticPhysicalObjects(){/*
	std::vector<glm::vec2> tablePositions;
	tablePositions.push_back(glm::vec2(-69, -6));
	tablePositions.push_back(glm::vec2(-55, -6));
	tablePositions.push_back(glm::vec2(-26, -6));
	tablePositions.push_back(glm::vec2(-10, -6));

	tablePositions.push_back(glm::vec2(51, -3));
	tablePositions.push_back(glm::vec2(35, -3));

	tablePositions.push_back(glm::vec2(98, -6));

	tablePositions.push_back(glm::vec2(58, 73));
	tablePositions.push_back(glm::vec2(15, 73));

	tablePositions.push_back(glm::vec2(-26, -65));
	tablePositions.push_back(glm::vec2(-10, -65));
	tablePositions.push_back(glm::vec2(56, -65));
	tablePositions.push_back(glm::vec2(40, -65));


	StaticGameObject* sgo;


	for (int i = 0; i < tablePositions.size(); ++i){
		sgo = new StaticGameObject("table", "table_texture");
		float x = tablePositions[i].x;
		float z = tablePositions[i].y;
		float y = getYPosition(x, z);
		sgo->setPosition(x, y, z);
		sgo->setSize(1.5);
		addChildNode(sgo->getSceneGraphBranch());
	}

	/*
	srand(time(NULL));
	for (int i = 0; i < 10; ++i){
		float x = sceneDimensions.x * (rand()/(float)RAND_MAX) + minVertexValues.x;
		float z = sceneDimensions.z * (rand()/(float)RAND_MAX) + minVertexValues.z;
		float y = getYPosition(x, z);
		float phi 	= 360.0f*(rand()/(float)RAND_MAX);
		float size = (rand()/(float)RAND_MAX) + 2.0f;

		sgo = new StaticGameObject("table", "table_texture");

		
		sgo->setPosition(x, y, z);
		sgo->setSize(size);
		sgo->setRotation(phi);

		addChildNode(sgo->getSceneGraphBranch());
	}
	*/
}

void Scene::initStaticNonPhysicalObjects(){/*
	std::vector<Node*> stems = getNodesByName("stem2");

	for (int i = 0; i < stems.size(); ++i){
		stems[i]->addChildNode(new Model("branches2", "SimpleTexture2"));
	}
	*/
}

void Scene::initDynamicObjects(){

	Player * body1 = new Character;
	body1->setPosition(0.0f, 0.0f, -50.0f);
	addPlayerToTeam(0, body1);
/*
	Player * body2 = new Character;
	body2->setPosition(0.0f, 0.0f, -50.0f);
	addPlayerToTeam(0, body2);

	Player * body3 = new Character;
	body3->setPosition(0.0f, 0.0f, -50.0f);
	addPlayerToTeam(0, body3);

	Player * body4 = new Character;
	body4->setPosition(0.0f, 0.0f, 50.0f);
	addPlayerToTeam(1, body4);

	Player * body5 = new Character;
	body5->setPosition(0.0f, 0.0f, 50.0f);
	addPlayerToTeam(1, body5);
*/
}


void Scene::addPlayerToTeam(int index, Player * p){
	//Put player on the ground
	p->setYPosition(getYPosition(p->getPosition().x, p->getPosition().z));
	addChildNode(p->getSceneGraphBranch());
	team[index]->addPlayer(p);
}



void Scene::update(float dt){
	Team * tp;
	Player * pp;
	for (int i = 0; i < team.size(); ++i){
		tp = team[i];
		tp->camera->update(dt);

		for (int j = 0; j < tp->players.size(); ++j){
			pp = tp->players[j];
			if(pp->isAlive()){
				pp->updateUserInputs();
				updatePlayerPosition5Sa(pp, tp->camera);
				updatePlayerHeadDirection(pp, tp->camera);

				if(pp->getController()->buttonIsTrigged(Controller::CONTROLLER_BUTTON_RB)){
					playerAttack(pp, i);
				}

				if(pp->getController()->buttonIsTrigged(Controller::CONTROLLER_BUTTON_LB)){
					playerRevive(pp, i);
				}

			}
			pp->update(dt);
		}
	}
}

void Scene::playerAttack(Player * p, int teamIndex){
	glm::vec3 hitPos = p->getPosition();
	hitPos.x += glm::sin(3.141592f / 180.0f * p->head.getPhi()) * p->getBaseRadius() * 1;
	hitPos.z += glm::cos(3.141592f / 180.0f * p->head.getPhi()) * p->getBaseRadius() * 1;
	//StaticGameObject * sgo = new StaticGameObject(hitPos.x, hitPos.y, hitPos.z);
	//addChildNode(sgo->getSceneGraphBranch());

	for (int i = 0; i < team.size(); ++i){
		if(i != teamIndex){
			for (int j = 0; j < team[i]->players.size(); ++j){
				glm::vec3 diff = hitPos - team[i]->players[j]->getPosition();
				if(glm::length(diff) < 3.0f){
					team[i]->players[j]->kill();
					return;
				}
			}
		}
	}
}

void Scene::playerRevive(Player * p, int teamIndex){
	glm::vec3 hitPos = p->getPosition();
	hitPos.x += glm::sin(3.141592f / 180.0f * p->head.getPhi()) * p->getBaseRadius() * 2;
	hitPos.z += glm::cos(3.141592f / 180.0f * p->head.getPhi()) * p->getBaseRadius() * 2;

	
	for (int j = 0; j < team[teamIndex]->players.size(); ++j){
		glm::vec3 diff = hitPos - team[teamIndex]->players[j]->getPosition();
		if(glm::length(diff) < 4.0f){
			team[teamIndex]->players[j]->revive();
		}
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
	    	float maxStep = 1.0f;
	    	if(steep > maxStep){

				//Define new ON-base from grad and a vector orthogonal to grad
		    	grad = glm::normalize(grad);
		    	glm::mat2 T = glm::mat2(grad, glm::vec2(-grad.y, grad.x));

		    	//Transform state to the new base e.
		    	glm::vec2 eState = T * sn;

		    	//Remove or decrease velocity along positive grad

		    	//eState.x -= 0.5f*(steep - maxStep);
		    	if(eState.x > 0)
		    		eState.x = 0;

		    	//Back to world coordinates.
		    	//T^t = T^-1 since ON base
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
	int imgX = heightmapWidth /2 + worldToHeightmapX * x;
	int imgY = heightmapHeight/2 + worldToHeightmapZ * z;

	int imgXYPos = (int)(imgX + heightmapWidth*imgY);

	if (0 < imgX && imgX < heightmapWidth &&
	    0 < imgY && imgY < heightmapHeight)
	    return heightmap[imgXYPos];
	return -1.0f;
}

/*
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
*/




void Scene::drawScene(glm::mat4 P, glm::mat4 V) {
	renderToScreen(P, V, glm::mat4(1.0f));
}

void Scene::renderToScreen(glm::mat4 P, glm::mat4 V, glm::mat4 parentModelMatrix){
	Model::renderToScreen(P, V, parentModelMatrix);
}

bool Scene::renderToHeightMap(int xRes, int yRes){

	// The FBO that will be used when rendering the heightmap
	GLuint frameBufferObj = 0;
	GLuint depthTex = 0;

	glGenFramebuffers(1, &frameBufferObj); //generate the framebuffer object
	glGenTextures(1, &depthTex);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObj); //bind it to the framebuffer target
	glBindTexture(GL_TEXTURE_2D, depthTex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, xRes, yRes, 0, GL_RED, GL_FLOAT, NULL);
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
	/*
	printf("minx = %f\n maxx = %f\n miny = %f\n maxy = %f\n minz = %f\n maxz = %f\n",
		minVertexValues.x,
		maxVertexValues.x,
		minVertexValues.y,
		maxVertexValues.y,
		minVertexValues.z,
		maxVertexValues.z);
	*/

	//First model matrix is just a enhetsmatrisnångångnudå
	glm::mat4 M(1.0);
	glm::mat4 VP = P * V;

	glViewport(0,0,xRes,yRes);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	assert(sgct::ShaderManager::Instance()->bindShader("heightProgram"));
	// Render to the FBO
	renderToDepthBuffer(VP, M);
	glDisable(GL_CULL_FACE);
	//Don't use the currently bound shader anymore
	sgct::ShaderManager::Instance()->unBindShader();

	//Och hänne ska vi använda glReadPixels..
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
 		GL_RED,
 		GL_FLOAT,
 		&heightmap[0]);

    //printf("  maxDepth = %i,  minDepth = %i,  scale = %f\n", maxDepth, minDepth, scale);


    float minSceneY = minVertexValues.y;
    for(int i = 0; i < xRes * yRes; ++i){
   		//1. Before scaling the image, we need to have 0 in heightmap
   		//means 0 in world coordinates. Therefor reduce all pixels with
   		//minDepth. Now minimum depth will be 0.

    	//2. Scale

   		//3. After the scaling, we need to add the minimum value from the
   		//scene vertices. That makes the heighmap place the player correctly
   		//according to the actual mesh.

        heightmap[i] = (float)(heightmap[i])*sceneDimensions.y + minSceneY;

    }

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
