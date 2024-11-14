#ifndef DISPLAYMODULE_H
#define DISPLAYMODULE_H

#include <TM1637Display.h>

class DisplayModule {
  private:
    int clkPin;
    int dioPin;
    TM1637Display display;

  public:
    // Constructor
    DisplayModule(int clk, int dio);

    // Inicializar el display
    void init();

    // Mostrar tiempo en formato MM:SS
    void displayTime(int minutes, int seconds, bool colonOn = true);

    // Mostrar un número (para contador simple)
    void displayNumber(int number);

    // Limpiar el display
    void clear();
};

#endif // DISPLAYMODULE_H
