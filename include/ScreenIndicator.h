#ifndef SCREENINDICATOR_H
#define SCREENINDICATOR_H

#include <M5StickCPlus.h>
#include "ILight.h"

class ScreenIndicator : public ILight {
private:
    int x, y;
    uint16_t color;

public:
    ScreenIndicator(int xCoord, int yCoord, uint16_t circleColor);
    void init() override;
    void turnOn() override;
    void turnOff() override;
};

#endif // SCREENINDICATOR_H