#ifdef M5STICKC
#include "TextViewer.h"

TextViewer::TextViewer(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

void TextViewer::init() {
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(x, y);
    clear();
}

void TextViewer::displayTime(int minutes, int seconds) {
    M5.Lcd.setCursor(x, y);
    M5.Lcd.setTextSize(4);
    M5.Lcd.printf("%02d:%02d", minutes, seconds);
}

void TextViewer::displayMessage(const char* message) {
    M5.Lcd.setCursor(x, y);
    M5.Lcd.printf("%s", message);
}

void TextViewer::clear() {
    M5.Lcd.fillRect(x, y, 80, 20, BLACK); // Clear area
}
#endif
