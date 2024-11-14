// Controller.h

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "DisplayModule.h"
#include "EncoderModule.h"
#include "LEDModule.h"
#include "TimerModule.h"

// Definir los estados
enum State {
    IDLE,
    RUNNING_WORK,
    RUNNING_BREAK,
    BLINKING_WORK,
    BLINKING_BREAK
};

class Controller {
  private:
    DisplayModule* display1; // Temporizador de 35 minutos
    DisplayModule* display2; // Temporizador de 10 minutos
    EncoderModule* encoder;
    LEDModule* ledRed;
    LEDModule* ledGreen;
    TimerModule* workTimer;
    TimerModule* breakTimer;
    State currentState;

    // Variables para el parpadeo
    unsigned long lastBlinkTime;
    bool blinkState;

    // Selección actual: WORK o BREAK
    TimerType currentSelection;

    // Actualizar displays
    void updateDisplays();

    // Manejar el parpadeo de los displays
    void handleBlinking();

  public:
    // Constructor
    Controller(DisplayModule* disp1, DisplayModule* disp2,
               EncoderModule* enc, LEDModule* red, LEDModule* green);

    // Destructor
    ~Controller();

    // Inicializar todos los módulos
    void setup();

    // Lógica principal del loop
    void loop();
};

#endif // CONTROLLER_H
