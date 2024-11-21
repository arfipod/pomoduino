#include "EncoderButton.h"

EncoderButton::EncoderButton(int sw) : swPin(sw), lastButtonPressTime(0) {}

void EncoderButton::init() {
    pinMode(swPin, INPUT_PULLUP);
}

bool EncoderButton::isPressed() {
    if (digitalRead(swPin) == LOW) {
        if (millis() - lastButtonPressTime > 200) { // Debounce de 200 ms
            lastButtonPressTime = millis();
            return true;
        }
    }
    return false;
}