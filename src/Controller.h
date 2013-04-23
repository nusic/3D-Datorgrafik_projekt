#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller{
public:
    Controller();
    ~Controller();
    void controllerLoader();
    void inputLoader();
    double getAxes(int axis_index);
private:
    float* axes;
    unsigned char* buttons;
    int numberOfAxes;
    int numberOfButtons;
    int joystickPresent;
};

#endif // CONTROLLER_H
