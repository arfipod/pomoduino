#include "TimerModule.h"

// Constructor
TimerModule::TimerModule(TimerType t, unsigned long dur)
  : type(t), duration(dur), startTime(0), running(false), finished(false) {}

// Iniciar el temporizador
void TimerModule::start() {
  startTime = millis();
  running = true;
  finished = false;
}

// Actualizar el temporizador
void TimerModule::update() {
  if (running && !finished) {
    if (millis() - startTime >= duration) {
      running = false;
      finished = true;
    }
  }
}

// Verificar si el temporizador ha terminado
bool TimerModule::isFinished() {
  return finished;
}

// Verificar si el temporizador está corriendo
bool TimerModule::isRunning() {
  return running;
}

// Obtener tiempo restante en segundos
unsigned long TimerModule::getTimeRemaining() {
  if (!running) return 0;
  unsigned long elapsed = millis() - startTime;
  if (elapsed >= duration) return 0;
  return (duration - elapsed) / 1000;
}

// Reiniciar el temporizador
void TimerModule::reset() {
  running = false;
  finished = false;
}