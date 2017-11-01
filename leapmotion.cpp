#include "leapmotion.hpp"

void SampleListener::onInit(const Controller& controller) {
    isPressed = false;
    swipe_counter = 0;
    initializeForPython();
    std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    //controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    //controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
    //controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {  
    Py_CLEAR(pModule);
    Py_Finalize();
    std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    Leap::PointableList pointables = frame.pointables();
    Leap::FingerList fingers = frame.fingers();
    Leap::GestureList gestures = frame.gestures();
    
    int32_t index_id = -1;
    Leap::Vector position;
    float x, y, new_x, new_y;

    bool isRecog = false;

    Leap::Finger finger;
    Leap::Pointable pointable;
    Leap::Gesture gesture;

    if (swipe_counter > 0) {
        swipe_counter--;
    }

    // スワイプのジェスチャーを認識する
    if (swipe_counter == 0) {
        for (int g = 0; g < gestures.count(); g++) {
            gesture = gestures[g];

            if (gesture.type() == Leap::Gesture::TYPE_SWIPE) {
                Leap::SwipeGesture swipe = gesture;
                if (swipe.direction().x < -0.7) {
                    std::cout << swipe.direction().x << std::endl;
                    PyObject_CallMethod(pModule, "swipe_screen", "(i)", 0);
                    // スワイプを認識したら関数を抜ける
                    isPressed = false;
                    swipe_counter = 100;
                    return;
                } else if (swipe.direction().x > 0.7) {
                    std::cout << swipe.direction().x << std::endl;
                    PyObject_CallMethod(pModule, "swipe_screen", "(i)", 1);
                    // スワイプを認識したら関数を抜ける
                    isPressed = false;
                    swipe_counter = 100;
                    return;
                }
            }
        }
    }
    
    for (int p = 0; p < fingers.count(); p++) {
        finger = fingers[p];
        if (fingerNames[finger.type()] == "Index") {
            index_id = finger.id();
            break;
        }
    }
    
    if (index_id != -1) {
        for (int p = 0; p < pointables.count(); p++) {
            pointable = pointables[p];
            // ポインタブルな人差し指を検知
            if (pointable.id() == index_id) {
                position = pointable.stabilizedTipPosition();
                x = position.x;
                y = position.y;
                std::cout << x << "," << y << std::endl;

                // リープモーションにおける座標系をスクリーンの座標系に変換する
                new_x = (x + 120.0) / 240.0 * 1440.0;
                if (new_x < 0.0) {
                    new_x = 0.0;
                } else if (new_x > 1440.0 - 1.0) {
                    new_x = 1440.0 - 1.0;
                }
                new_y = (250.0 - y) / 150.0 * 900.0;
                if (new_y < 0.0) {
                    new_y = 0.0;
                } else if (new_y > 900.0 - 1.0) {
                    new_y = 900.0 - 1.0;
                }

                // タッチの認識
                if (isPressed) {
                    if (pointable.touchDistance() > 0.0) {
                        isPressed = false;
                        PyObject_CallMethod(pModule, "touch", "(dd)", touch_x, touch_y);
                        std::cout << "===== PRESS_OK =====" << std::endl;
                    }
                } else {
                    if (pointable.touchDistance() < -0.1) {
                        isPressed = true;
                        touch_x = new_x;
                        touch_y = new_y;
                        std::cout << "***** PRESS_Prepare *****" << std::endl;
                    }
                }

                //PyObject_CallMethod(pModule, "python_log", "(s)", "hoge");
                PyObject_CallMethod(pModule, "warp", "(dd)", new_x, new_y);
                // pTmp = PyObject_CallMethod(pModule, "warp", "(dd)", new_x, new_y);
                // PyArg_Parse(pTmp, "s", &sTmp);
                // std::string res(sTmp);

                isRecog = true;
                break;
            }
        }
    }

    // 指を認識できなかった時は押したときのフラグを折る
    if (!isRecog) {
        isPressed = false;
    }
}

void SampleListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
    std::cout << "Device Changed" << std::endl;
    const DeviceList devices = controller.devices();
    
    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void SampleListener::onServiceConnect(const Controller& controller) {
    std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}

bool SampleListener::initializeForPython() {
    Py_Initialize();
    // カレントディレクトリのパスを通す
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyString_FromString("."));

    // カレントディレクトリにあるpythonモジュールをインポートする
    pModule = PyImport_ImportModule("script");

    if (pModule != NULL) {
        return true;
    } else {
        return false;
    }
}





