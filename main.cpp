#include <iostream>
#include <cstring>
//#include <Python.h>
#include "leapmotion.hpp"
#include <unistd.h>

int main(int argc, char** argv) {
    // Create a sample listener and controller
    SampleListener listener;
    Controller controller;
    
    // Have the sample listener receive events from the controller
    controller.addListener(listener);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    
    // Keep this process running until Enter is pressed
    //sleep(10);
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    // listener.finalizeForPython();
    // sleep(5);
    // std::cout << "Python was finalized." << std::endl;
    
    // Remove the sample listener when done
    controller.removeListener(listener);

    std::cout << "END" << std::endl;

    std::exit(0);
    return 0;
}
