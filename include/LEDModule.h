#ifndef LEDMODULE_H
#define LEDMODULE_H

#include <Arduino.h>

class LEDModule {
  private:
    int pin;
    bool state;

  public:
    // Constructor
    LEDModule(int ledPin);

    // Inicializar el LED
    void init();

    // Encender el LED
    void turnOn();

    // Apagar el LED
    void turnOff();

    // Verificar si el LED está encendido
    bool isOn() const;
};

#endif // LEDMODULE_H
