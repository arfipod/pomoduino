#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include "ILight.h"
#include <Arduino.h>

class LEDIndicator : public ILight {
private:
    int pin;

public:
    LEDIndicator(int ledPin);
    void init() override;
    void turnOn() override;
    void turnOff() override;
};

#endif // LEDINDICATOR_H