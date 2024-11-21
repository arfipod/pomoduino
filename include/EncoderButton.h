#ifndef ENCODERBUTTON_H
#define ENCODERBUTTON_H

#include <Arduino.h>
#include "IButton.h"

class EncoderButton : public IButton {
private:
    int swPin;
    unsigned long lastButtonPressTime;

public:
    EncoderButton(int sw);
    void init() override;
    bool isPressed() override;
};

#endif // ENCODERBUTTON_H