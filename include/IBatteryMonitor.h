#ifndef IBATTERYMONITOR_H
#define IBATTERYMONITOR_H

class IBatteryMonitor {
public:
    virtual ~IBatteryMonitor() {}

    // Initialize the battery monitor
    virtual void init() = 0;

    // Update battery status (to be called in loop)
    virtual void update() = 0;
};

#endif // IBATTERYMONITOR_H