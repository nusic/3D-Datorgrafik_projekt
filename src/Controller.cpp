#include "Controller.h"
#include "Player.h"

Controller::Controller(int index, Player* const _owner): owner(_owner){
    joystickPresent = GL_FALSE;
    numberOfAxes = 0;
    numberOfButtons = 0;
    controllerIndex = index;

    for(int i=0; i<LARGEST_BUTTON_INDEX; ++i){
        buttonPressed[i] = false;
        buttonTrigger[i] = false;
    }

    controllerLoader();
    if(joystickPresent){
        inputLoader();
        printf("controller loaded\n");
    }

}

Controller::~Controller(){
    if(numberOfAxes > 0)
		delete [] axes;
	if(numberOfButtons > 0)
		delete [] buttons;
}

const bool Controller::buttonIsTrigged(const int buttonIndex) const{
    return buttonTrigger[buttonIndex];
}

const bool Controller::buttonIsPressed(const int buttonIndex) const{
    return buttonPressed[buttonIndex];
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

		if(numberOfAxes > 0){
			axes = new float[numberOfAxes];
            for (int i = 0; i < numberOfAxes; ++i){
                axes[i] = 0.0f;
            }
        }

		if(numberOfButtons > 0){
			buttons = new unsigned char[numberOfButtons];
            for (int i = 0; i < numberOfButtons; ++i){
                buttons[i] = 0;
            }
        }
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
    
//        for(int i=0; i<numberOfAxes; i++)
//            sgct::MessageHandler::Instance()->print("%.3f ", axes[i]);
//        for(int i=0; i<numberOfButtons; i++)
//            sgct::MessageHandler::Instance()->print("%i", buttons[i]);
//        sgct::MessageHandler::Instance()->print("\r");

	}
    checkButtons();
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

        if(axes[CONTROLLER_LEFT_X_AXIS] && axes[CONTROLLER_LEFT_Y_AXIS]){
            axes[CONTROLLER_LEFT_X_AXIS] *= 0.70710678f;
            axes[CONTROLLER_LEFT_Y_AXIS] *= 0.70710678f;
        }
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

void Controller::checkButtons(){
    if(joystickPresent != GL_TRUE){
        if(glfwGetKey('X') == GLFW_PRESS) buttons[CONTROLLER_BUTTON_X] = 1;
        else buttons[CONTROLLER_BUTTON_X] = 0;

        if(glfwGetKey('Y') == GLFW_PRESS) buttons[CONTROLLER_BUTTON_Y] = 1;
        else buttons[CONTROLLER_BUTTON_Y] = 0;
    }

    updateButtonBools(CONTROLLER_BUTTON_RB);
    updateButtonBools(CONTROLLER_BUTTON_LB);
    updateButtonBools(CONTROLLER_BUTTON_A);

    if(buttonTrigger[CONTROLLER_BUTTON_RB] && !owner->isAttacking())
        owner->startAttackAnimation();

    if(buttonTrigger[CONTROLLER_BUTTON_A] && owner->isAlive())
        owner->toggleLight();
}

void Controller::updateButtonBools(const int buttonIndex){
    if(buttons[buttonIndex]){
        if(!buttonPressed[buttonIndex]){
            buttonTrigger[buttonIndex] = true;
            buttonPressed[buttonIndex] = true;
        }
        else
            buttonTrigger[buttonIndex] = false;
    }
    else
        buttonPressed[buttonIndex] = false;
}