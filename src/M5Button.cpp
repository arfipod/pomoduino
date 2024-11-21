#include "M5Button.h"

void M5Button::init() {
    M5.update(); // Inicializa la biblioteca
}

bool M5Button::isPressed() {
    M5.update();
    return M5.BtnA.wasPressed();
}