#include "Controller.h"
#include "sgct.h"
#include <iostream>

Controller::Controller(){
    joystickPresent = GL_FALSE;
    numberOfAxes = 0;
    numberOfButtons = 0;

    controllerLoader();
    if(joystickPresent)
        inputLoader();
}

Controller::~Controller(){
    if(numberOfAxes > 0)
		delete [] axes;
	if(numberOfButtons > 0)
		delete [] buttons;
}

void Controller::controllerLoader(){
    joystickPresent = sgct::Engine::getJoystickParam(GLFW_JOYSTICK_1, GLFW_PRESENT);
	if(joystickPresent == GL_TRUE){
		sgct::MessageHandler::Instance()->print("Joystick 1 is present.\n");

		numberOfAxes = sgct::Engine::getJoystickParam(GLFW_JOYSTICK_1, GLFW_AXES);
		numberOfButtons = sgct::Engine::getJoystickParam(GLFW_JOYSTICK_1, GLFW_BUTTONS);

		sgct::MessageHandler::Instance()->print("Number of axes %d\nNumber of buttons %d\n",
			numberOfAxes,
			numberOfButtons);

		if(numberOfAxes > 0)
			axes = new float[numberOfAxes];

		if(numberOfButtons > 0)
			buttons = new unsigned char[numberOfButtons];
	}
    else{
        axes = NULL;
        buttons = NULL;
	}
}

void Controller::inputLoader(){
    if(joystickPresent == GL_TRUE){
		sgct::Engine::getJoystickAxes(GLFW_JOYSTICK_1, axes, numberOfAxes);
		sgct::Engine::getJoystickButtons(GLFW_JOYSTICK_1, buttons, numberOfButtons);
        for(int i=0; i<numberOfAxes; i++)
            sgct::MessageHandler::Instance()->print("%.3f ", axes[i]);
        for(int i=0; i<numberOfButtons; i++)
            sgct::MessageHandler::Instance()->print("%d ", buttons[i]);
        sgct::MessageHandler::Instance()->print("\r");

	}
}

double Controller::getAxisValue(int axis_index){
    return (double)axes[axis_index];
}

bool Controller::validateLeftStickValues(){
    if(joystickPresent == GL_TRUE){
        if(axes[CONTROLLER_LEFT_X_AXIS] < 0.2f && axes[CONTROLLER_LEFT_X_AXIS] > -0.2f &&
            axes[CONTROLLER_LEFT_Y_AXIS] < 0.2f && axes[CONTROLLER_LEFT_Y_AXIS] > -0.2f){
            return false;
        }
        return true;
    }
    return false;
}

bool Controller::validateRightStickValues(){
    if(joystickPresent == GL_TRUE){
        if(axes[CONTROLLER_RIGHT_X_AXIS] < 0.2f && axes[CONTROLLER_RIGHT_X_AXIS] > -0.2f &&
            axes[CONTROLLER_RIGHT_Y_AXIS] < 0.2f && axes[CONTROLLER_RIGHT_Y_AXIS] > -0.2f){
            return false;
        }
        return true;
    }
    return false;
}
