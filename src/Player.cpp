#include "Player.h"
#include <new>

int Player::numberOfPlayers = 0;

Player::Player():
GameObject(){
    speed = 5.0f;
    controller = new Controller(numberOfPlayers);

    head = GameObject(0.0f, 2.0f, 0.0f);
    translationNode->addChildNode(head.getSceneGraphBranch());
    light = new LightSource(head.modelNode);
	light->setDirection(0,-1,4);
	light->setColor(0.9,0.8,0.7);
    light->setIntensity(70);
	light->setSpread(30);

    numberOfPlayers++;



    /*
    En player skapar en ScenGraphBranch som ser ut så här



        GameObject (body)
        ------------------
        |   Translation  |
        |         |      
        |         |------------------------    GameObject (head)
        |         |               ------  |  ------ 
        |      Rotation  |        |   Translation |
        |         |      |        |       |       |
        |      Scaling   |        |   Rotation    |
        |         |      |        |       |       |
        |       Model    |        |   Scaling     |
        ------------------        |       |       |     
                                  |     Model     |
                                  ------  |  ------
                                          | 
                                     LightSource

    */
}

Player::~Player(){
    delete controller;
    //Väntar med att deletea lightSource då en del måsta fixas i den destruktorn
}

void Player::updatePlayerOrientation(float dt, float * heightmap, int heightmapWidth, int heightmapHeight, glm::vec3 sceneDimensions){
    controller->inputLoader();

    if(controller->validateLeftStickValues()){

        //spara kontrollens axis values i variabler för läsbarhet
        float xState = controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS);

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
        int imgX = heightmapWidth/2  + heightmapWidth /sceneDimensions.x * (getPosition().x + sn.x*getBaseRadius());
        int imgY = heightmapHeight/2 - heightmapHeight/sceneDimensions.z * (getPosition().z - sn.y*getBaseRadius());


        //Beräkna höjden för players främre kant.
        int imgXYPos = (int)(imgX + heightmapWidth*imgY);
        float yTemp = heightmap[imgXYPos];


        //Temporärt kan vi använde denna som ett tröskelvärde 
        //som avgör hur brant en player kan gå.
        float maxStep = 1.0f;

        //Testa om players främre kant befinner sig innanför heightmappen
        //OCH Testa om denna höjdskillnad är för stor för att kunna röra sig upp för.
        if (0 < imgX && imgX < heightmapWidth &&
            0 < imgY && imgY < heightmapHeight &&
            abs(yTemp - getPosition().y) < maxStep){
            
            //Fritt fram för player att röra sig!
            //Vi tar fram players riktiga position i höjdmappen
            //dvs den som baseras på centrum av player
            imgX = heightmapWidth/2  + heightmapWidth /sceneDimensions.x * (getPosition().x);
            imgY = heightmapHeight/2 - heightmapHeight/sceneDimensions.z * (getPosition().z);

            //Hämta höjden från mappen
            imgXYPos = (int)(imgX + heightmapWidth*imgY);
            yTemp = heightmap[imgXYPos];

            //Sätt nya värden på hastighet och höjd
            setVelocity(xState, 0.0f, -yState);
            setYPosition(yTemp);
        }
        else{
            //Om vi befinner oss utanför mappen eller
            //om vi har en för brant backe framför oss så stå still
            setVelocity(0.0f, 0.0f, 0.0f);
        }
/*
        sgct::MessageHandler::Instance()->print(
          "position.x = %f  position.z = %f  imgX = %i  imgY = %i  heightmap[%i] = %f", 
           getPosition().x, getPosition().z, imgX,      imgY,                imgXYPos, yTemp);
        sgct::MessageHandler::Instance()->print("\r");
*/
        
        //Uppdatera riktningen oavsett om vi kunde röra oss eller inte
        setDirection(180.0f / 3.141592f * glm::atan(xState,-yState));

        //Slutligen uppdaterar vi vår position
        update(dt);
    }
    if (controller->validateRightStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS);
        head.rotationNode->setRotation(180.0f / 3.141592 * glm::atan(xState,-yState), glm::vec3(0.0f,1.0f,0.0f));
    }

}
