#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "sgct.h"
#include <iostream>

class Controller{
public:
    Controller(int index);
    ~Controller();
    void controllerLoader();
    void inputLoader();
    double getAxisValue(int axis_index);
    bool validateLeftStickValues();
    bool validateRightStickValues();

    bool joystickIsPresent() const;


    static const int CONTROLLER_LEFT_X_AXIS = 0;
    static const int CONTROLLER_LEFT_Y_AXIS = 1;
#ifdef __APPLE__
    static const int CONTROLLER_RIGHT_X_AXIS = 2;
    static const int CONTROLLER_RIGHT_Y_AXIS = 3;
#else
    static const int CONTROLLER_RIGHT_X_AXIS = 3;
    static const int CONTROLLER_RIGHT_Y_AXIS = 4;
#endif

private:
    float* axes;
    unsigned char* buttons;
    int numberOfAxes;
    int numberOfButtons;
    int joystickPresent;
};

#endif // CONTROLLER_H
