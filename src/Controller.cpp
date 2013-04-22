#include "Controller.h"
#include "sgct.h"
#include <iostream>

Controller::Controller(){
std::cout << "conyrretolrer kons trrukoet CHECKPOINT 1" << std::endl;
    joystickPresent = GL_FALSE;
    numberOfAxes = 0;
    numberOfButtons = 0;

    controllerLoader();
    inputLoader();
std::cout << "conyrretolrer kons trrukoet CHECKPOINT 2" << std::endl;
}

Controller::~Controller(){

    if( numberOfAxes > 0 )
		delete [] axes;
	if( numberOfButtons > 0 )
		delete [] buttons;
}

void Controller::controllerLoader(){
std::cout << "CONTROLLER LOADER CHECKPOINT 1" << std::endl;
    joystickPresent = sgct::Engine::getJoystickParam( GLFW_JOYSTICK_1, GLFW_PRESENT );
	if( joystickPresent == GL_TRUE )
	{
		sgct::MessageHandler::Instance()->print("Joystick 1 is present.\n");

		numberOfAxes = sgct::Engine::getJoystickParam( GLFW_JOYSTICK_1, GLFW_AXES );
		numberOfButtons = sgct::Engine::getJoystickParam( GLFW_JOYSTICK_1, GLFW_BUTTONS );

		sgct::MessageHandler::Instance()->print("Number of axes %d\nNumber of buttons %d\n",
			numberOfAxes,
			numberOfButtons);

		if( numberOfAxes > 0 )
			axes = new float[numberOfAxes];

		if( numberOfButtons > 0 )
			buttons = new unsigned char[numberOfButtons];
	}
}

void Controller::inputLoader(){
    if( joystickPresent == GL_TRUE ){
		sgct::Engine::getJoystickAxes( GLFW_JOYSTICK_1, axes, numberOfAxes );
		sgct::Engine::getJoystickButtons( GLFW_JOYSTICK_1, buttons, numberOfButtons );
        /*for(int i=0; i<numberOfAxes; i++)
            sgct::MessageHandler::Instance()->print("%.3f ", axes[i]);
        for(int i=0; i<numberOfButtons; i++)
            sgct::MessageHandler::Instance()->print("%d ", buttons[i]);
        sgct::MessageHandler::Instance()->print("\r");
        */
	}
}

double Controller::getAxes(int axis_index){
    return (double)axes[axis_index];
}
