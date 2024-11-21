#ifndef DISPLAYVIEWER_H
#define DISPLAYVIEWER_H

#ifdef ARDUINO_UNO
#include "ITimeViewer.h"
#include <TM1637Display.h>

class DisplayViewer : public ITimeViewer {
private:
    TM1637Display display;

public:
    DisplayViewer(int clkPin, int dioPin);
    void init();
    void displayTime(int minutes, int seconds) override;
    void clear() override;
};
#endif
#endif // DISPLAYVIEWER_H