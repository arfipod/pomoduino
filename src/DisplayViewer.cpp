#ifdef ARDUINO_UNO
#include "DisplayViewer.h"

DisplayViewer::DisplayViewer(int clkPin, int dioPin) : display(clkPin, dioPin) {}

void DisplayViewer::init() {
    display.setBrightness(0x0f);
    clear();
}

void DisplayViewer::displayTime(int minutes, int seconds) {
    int value = (minutes * 100) + seconds;
    display.showNumberDecEx(value, 0b01000000, true); // Show with colon
}

void DisplayViewer::clear() {
    display.clear();
}
#endif