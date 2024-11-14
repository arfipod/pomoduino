#include "DisplayModule.h"

// Constructor
DisplayModule::DisplayModule(int clk, int dio) 
  : clkPin(clk), dioPin(dio), display(clk, dio) {}

// Inicializar el display
void DisplayModule::init() {
  display.setBrightness(0x0f); // Brillo máximo
  clear();
}

// Mostrar tiempo en formato MM:SS
void DisplayModule::displayTime(int minutes, int seconds, bool colonOn) {
  int displayNumber = minutes * 100 + seconds;
  display.showNumberDecEx(displayNumber, colonOn ? 0b01000000 : 0, true);
}

// Mostrar un número
void DisplayModule::displayNumber(int number) {
  display.showNumberDec(number);
}

// Limpiar el display
void DisplayModule::clear() {
  display.clear();
}
