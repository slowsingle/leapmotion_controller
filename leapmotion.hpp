#ifndef leapmotion_hpp
#define leapmotion_hpp

#include "Leap.h"
#include <Python.h>

using namespace Leap;

class SampleListener : public Listener {
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
    bool initializeForPython();

private:
    PyObject *pModule; // *pTmp;
    char *sTmp;
    bool isPressed;

    double touch_x, touch_y;

    unsigned int swipe_counter;
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

#endif /* leapmotion_hpp */
