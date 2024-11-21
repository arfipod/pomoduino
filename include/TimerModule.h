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
    unsigned long duration; // Duración en milisegundos
    unsigned long startTime;
    bool running;
    bool finished;

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
};

#endif // TIMERMODULE_H