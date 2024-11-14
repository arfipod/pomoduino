#ifndef TIMERMODULE_H
#define TIMERMODULE_H

#include <Arduino.h>

enum TimerType {
    WORK,
    BREAK_TIME
};

class TimerModule {
  private:
    TimerType type;
    unsigned long duration; // Duración en milisegundos
    unsigned long startTime;
    bool running;
    bool finished;

  public:
    // Constructor
    TimerModule(TimerType t, unsigned long dur);

    // Iniciar el temporizador
    void start();

    // Actualizar el temporizador (llamado en loop)
    void update();

    // Verificar si el temporizador ha terminado
    bool isFinished();

    // Verificar si el temporizador está corriendo
    bool isRunning();

    // Obtener tiempo restante en segundos
    unsigned long getTimeRemaining();

    // Reiniciar el temporizador
    void reset();
};

#endif // TIMERMODULE_H
