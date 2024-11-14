#ifndef ENCODERMODULE_H
#define ENCODERMODULE_H

#include <Arduino.h>

class EncoderModule {
  private:
    int clkPin;
    int dtPin;
    int swPin;
    volatile int counter;
    int lastStateDT;
    unsigned long lastButtonPressTime;

    // Método para actualizar el encoder
    void update();

  public:
    // Constructor
    EncoderModule(int clk, int dt, int sw);

    // Inicializar el encoder
    void init();

    // Manejar el botón del encoder con debounce
    bool isButtonPressed();

    // Obtener el valor del contador
    int getCounter();

    // Reiniciar el contador
    void resetCounter();

    // Configuración de la instancia para interrupciones
    void setInstance();

    // Método estático para manejar interrupciones
    static void handleInterrupt();

    // Instancia estática
    static EncoderModule* instance;
};

#endif // ENCODERMODULE_H
