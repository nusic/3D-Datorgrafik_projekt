#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller{
public:
    Controller();
    ~Controller();
    void controllerLoader();
    void inputLoader();
    double getAxisValue(int axis_index);
    bool validateLeftStickValues();
private:
    float* axes;
    unsigned char* buttons;
    int numberOfAxes;
    int numberOfButtons;
    int joystickPresent;
};

#endif // CONTROLLER_H
