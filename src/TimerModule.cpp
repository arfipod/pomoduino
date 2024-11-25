#include "TimerModule.h"

// Constructor
TimerModule::TimerModule(TimerType t, unsigned long dur)
    : type(t), duration(dur), startTime(0), running(false), finished(false), initialDuration(dur) {}

// Iniciar el temporizador
void TimerModule::start() {
    startTime = millis();
    running = true;
    finished = false;
    duration = initialDuration; // Asegurar que la duración se restablece al valor inicial
}

// Actualizar el temporizador
void TimerModule::update() {
    if (running && !finished) {
        unsigned long elapsed = millis() - startTime;
        if (elapsed >= duration) {
            running = false;
            finished = true;
        }
    }
}

// Verificar si el temporizador ha terminado
bool TimerModule::isFinished() const {
    return finished;
}

// Verificar si el temporizador está corriendo
bool TimerModule::isRunning() const {
    return running;
}

// Obtener tiempo restante en segundos
unsigned long TimerModule::getTimeRemaining() const {
    if (running) {
        unsigned long elapsed = millis() - startTime;
        if (elapsed >= duration) {
            return 0;
        }
        return (duration - elapsed) / 1000;
    } else {
        if (finished) {
            return 0;
        } else {
            return initialDuration / 1000; // Devolver duración inicial en segundos
        }
    }
}

// Reiniciar el temporizador
void TimerModule::reset() {
    running = false;
    finished = false;
    startTime = 0;
    duration = initialDuration;  // Restablecer la duración al valor inicial
}

// Obtener los minutos iniciales
unsigned long TimerModule::getInitialMinutes() const {
    return initialDuration / (60 * 1000);
}
