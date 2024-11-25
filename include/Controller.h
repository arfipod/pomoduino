#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ITimeViewer.h"
#include "IButton.h"
#include "ILight.h"
#include "ITimer.h"
#include "IBuzzer.h"
#include "IBatteryMonitor.h"

// Enumeration to represent the controller state
enum State {
    IDLE,
    RUNNING_WORK,
    RUNNING_BREAK,
    BLINKING_WORK,
    BLINKING_BREAK
};

class Controller {
private:
    ITimeViewer* workViewer;
    ITimeViewer* breakViewer;
    IButton* button;
    ILight* ledRed;
    ILight* ledGreen;
    ITimer* workTimer;
    ITimer* breakTimer;
    IBuzzer* buzzer;
    IBatteryMonitor* batteryMonitor;
    State currentState;

    void updateDisplays();
    void handleBlinking();

public:
    // Constructor including the battery monitor
    Controller(ITimeViewer* work, ITimeViewer* rest, IButton* btn, ILight* red, ILight* green,
               ITimer* workT, ITimer* breakT, IBuzzer* buzz, IBatteryMonitor* batteryMon);

    void setup();
    void loop();

    ~Controller();
};

#endif // CONTROLLER_H
