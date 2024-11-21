#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#ifdef M5STICKC
#include "ITimeViewer.h"
#include <M5StickCPlus.h>

class TextViewer : public ITimeViewer {
private:
    int x, y;

public:
    TextViewer(int xCoord, int yCoord);
    void init();
    void displayTime(int minutes, int seconds) override;
    void displayMessage(const char* message);
    void clear() override;
};

#endif
#endif // TEXTVIEWER_H