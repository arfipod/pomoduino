#include "ScreenIndicator.h"

ScreenIndicator::ScreenIndicator(int xCoord, int yCoord, uint16_t circleColor)
    : x(xCoord), y(yCoord), color(circleColor) {}

void ScreenIndicator::init() {
    turnOff();
}

void ScreenIndicator::turnOn() {
    M5.Lcd.fillCircle(x, y, 15, color); // Fill circle
}

void ScreenIndicator::turnOff() {
    M5.Lcd.fillCircle(x, y, 15, BLACK); // Erase circle
}