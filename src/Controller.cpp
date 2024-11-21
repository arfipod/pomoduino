#include "Controller.h"

Controller::Controller(ITimeViewer* work, ITimeViewer* rest, IButton* btn, ILight* red, ILight* green, ITimer* workT, ITimer* breakT)
    : workViewer(work), breakViewer(rest), button(btn), ledRed(red), ledGreen(green),
      workTimer(workT), breakTimer(breakT),
      currentState(IDLE) {}

Controller::~Controller() {
    delete workTimer;
    delete breakTimer;
    // También podrías eliminar otros punteros si fueron creados dinámicamente aquí
}

void Controller::setup() {
    workViewer->clear();
    breakViewer->clear();
    ledRed->turnOff();
    ledGreen->turnOff();
}

void Controller::loop() {
    // Verifica si se presionó el botón
    if (button->isPressed()) {
        if (currentState == IDLE || currentState == RUNNING_BREAK) {
            // Inicia el temporizador de trabajo
            workTimer->start();
            ledRed->turnOn();
            ledGreen->turnOff();
            currentState = RUNNING_WORK;
        } else if (currentState == RUNNING_WORK) {
            // Inicia el temporizador de descanso
            breakTimer->start();
            ledGreen->turnOn();
            ledRed->turnOff();
            currentState = RUNNING_BREAK;
        }
    }

    // Actualiza los temporizadores
    workTimer->update();
    breakTimer->update();

    // Actualiza las pantallas
    updateDisplays();

    // Maneja el parpadeo si es necesario
    handleBlinking();
}

void Controller::updateDisplays() {
    if (currentState == RUNNING_WORK) {
        unsigned long remaining = workTimer->getTimeRemaining();
        int minutes = remaining / 60;
        int seconds = remaining % 60;
        workViewer->displayTime(minutes, seconds);
    } else if (currentState == RUNNING_BREAK) {
        unsigned long remaining = breakTimer->getTimeRemaining();
        int minutes = remaining / 60;
        int seconds = remaining % 60;
        breakViewer->displayTime(minutes, seconds);
    } else if (currentState == BLINKING_WORK) {
        // Implementar lógica de parpadeo si es necesario
    } else if (currentState == BLINKING_BREAK) {
        // Implementar lógica de parpadeo si es necesario
    }
}

void Controller::handleBlinking() {
    if (currentState == BLINKING_WORK) {
        static bool toggle = false;
        if (toggle) {
            workViewer->clear();
        }
        toggle = !toggle;
    } else if (currentState == BLINKING_BREAK) {
        static bool toggle = false;
        if (toggle) {
            breakViewer->clear();
        }
        toggle = !toggle;
    }
}