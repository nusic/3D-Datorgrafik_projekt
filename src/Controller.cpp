#include "Controller.h"


Controller::Controller(int index){
    joystickPresent = GL_FALSE;
    numberOfAxes = 0;
    numberOfButtons = 0;
    controllerIndex = index;

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
    joystickPresent = sgct::Engine::getJoystickParam(controllerIndex, GLFW_PRESENT);
	if(joystickPresent == GL_TRUE){
		//sgct::MessageHandler::Instance()->print("Joystick 1 is present.\n");

		numberOfAxes = sgct::Engine::getJoystickParam(controllerIndex, GLFW_AXES);
		numberOfButtons = sgct::Engine::getJoystickParam(controllerIndex, GLFW_BUTTONS);

		//sgct::MessageHandler::Instance()->print("Number of axes %d\nNumber of buttons %d\n",
		//	numberOfAxes,
		//	numberOfButtons);

		if(numberOfAxes > 0)
			axes = new float[numberOfAxes];

		if(numberOfButtons > 0)
			buttons = new unsigned char[numberOfButtons];
	}
    else{
        axes = new float[6]; //Maximum number of axes
        buttons = new unsigned char[14]; //Maximum number of buttons
	}
}

bool Controller::joystickIsPresent() const{
    return joystickPresent == GL_TRUE;
}

void Controller::inputLoader(){
    if(joystickPresent == GL_TRUE){
		sgct::Engine::getJoystickAxes(controllerIndex, axes, numberOfAxes);
		sgct::Engine::getJoystickButtons(controllerIndex, buttons, numberOfButtons);

        for(int i=0; i<numberOfAxes; i++)
            sgct::MessageHandler::Instance()->print("%.3f ", axes[i]);
        for(int i=0; i<numberOfButtons; i++)
            sgct::MessageHandler::Instance()->print("%i", buttons[i]);
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
    else{
        if (glfwGetKey('W') == GLFW_PRESS) axes[CONTROLLER_LEFT_Y_AXIS] = 1;
        else if (glfwGetKey('S') == GLFW_PRESS) axes[CONTROLLER_LEFT_Y_AXIS] = -1;
        else axes[CONTROLLER_LEFT_Y_AXIS] = 0;

        if (glfwGetKey('A') == GLFW_PRESS) axes[CONTROLLER_LEFT_X_AXIS] = -1;
        else if (glfwGetKey('D') == GLFW_PRESS) axes[CONTROLLER_LEFT_X_AXIS] = 1;
        else axes[CONTROLLER_LEFT_X_AXIS] = 0;

    }
    return true;
}

bool Controller::validateRightStickValues(){
    if(joystickPresent == GL_TRUE){
        if(axes[CONTROLLER_RIGHT_X_AXIS] < 0.2f && axes[CONTROLLER_RIGHT_X_AXIS] > -0.2f &&
            axes[CONTROLLER_RIGHT_Y_AXIS] < 0.2f && axes[CONTROLLER_RIGHT_Y_AXIS] > -0.2f){
            return false;
        }
        return true;
    }
    else{
        int yInput = 0;
        int xInput = 0;

        if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS) yInput++;
        if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS) yInput--;
        if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS) xInput--;
        if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS) xInput++;

        if(xInput || yInput){
            axes[CONTROLLER_RIGHT_X_AXIS] = xInput;
            axes[CONTROLLER_RIGHT_Y_AXIS] = yInput;
        }
    }
    return true;
}
