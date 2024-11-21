#include "LEDIndicator.h"

LEDIndicator::LEDIndicator(int ledPin) : pin(ledPin) {}

void LEDIndicator::init() {
    pinMode(pin, OUTPUT);
    turnOff();
}

void LEDIndicator::turnOn() {
    digitalWrite(pin, HIGH);
}

void LEDIndicator::turnOff() {
    digitalWrite(pin, LOW);
}