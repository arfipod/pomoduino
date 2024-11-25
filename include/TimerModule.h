#ifndef TIMERMODULE_H
#define TIMERMODULE_H

#include <Arduino.h>
#include "ITimer.h"

// Definir el tipo de temporizador
enum TimerType {
    WORK,
    BREAK_TIME
};

class TimerModule : public ITimer {
  private:
    TimerType type;
    unsigned long duration;        // Duración actual en milisegundos
    unsigned long startTime;
    bool running;
    bool finished;
    unsigned long initialDuration; // Duración inicial en milisegundos

  public:
    // Constructor
    TimerModule(TimerType t, unsigned long dur);

    // Implementación de métodos de ITimer
    void start() override;
    void update() override;
    bool isFinished() const override;
    bool isRunning() const override;
    unsigned long getTimeRemaining() const override;
    void reset() override;
    unsigned long getInitialMinutes() const override; // Método para obtener minutos iniciales
};

#endif // TIMERMODULE_H
