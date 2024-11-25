#ifndef M5BATTERYMONITOR_H
#define M5BATTERYMONITOR_H

#ifdef M5STICKC

#include <M5StickCPlus.h>
#include "IBatteryMonitor.h"

class M5BatteryMonitor : public IBatteryMonitor {
private:
    unsigned long lastBatteryUpdate;
    const unsigned long BATTERY_UPDATE_INTERVAL = 5000; // 5 seconds

    float calculateBatteryPercentage(float voltage);

public:
    M5BatteryMonitor();
    void init() override;
    void update() override;
};

#endif // M5STICKC

#endif // M5BATTERYMONITOR_H