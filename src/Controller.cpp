#include "Controller.h"
#include <Arduino.h>

Controller::Controller(ITimeViewer* work, ITimeViewer* rest, IButton* btn, ILight* red,
                       ILight* green, ITimer* workT, ITimer* breakT, IBuzzer* buzz,
                       IBatteryMonitor* batteryMon)
    : workViewer(work), breakViewer(rest), button(btn), ledRed(red), ledGreen(green),
      workTimer(workT), breakTimer(breakT), buzzer(buzz), batteryMonitor(batteryMon),
      currentState(IDLE) {}

Controller::~Controller() {
    delete workTimer;
    delete breakTimer;
    // Other pointers are managed elsewhere
}

void Controller::setup() {
    workViewer->clear();
    breakViewer->clear();
    ledRed->turnOff();
    ledGreen->turnOff();
    if (batteryMonitor) {
        batteryMonitor->init();
    }
}

void Controller::loop() {
    // Update battery monitor
    if (batteryMonitor) {
        batteryMonitor->update();
    }

    // Check if the button was pressed
    if (button->isPressed()) {
        if (currentState == IDLE || currentState == RUNNING_BREAK || currentState == BLINKING_BREAK) {
            // Reset break timer and its display
            breakTimer->reset();
            breakViewer->displayTime(breakTimer->getInitialMinutes(), 0);

            // Start the work timer
            workTimer->start();
            ledRed->turnOn();
            ledGreen->turnOff();
            currentState = RUNNING_WORK;
        } else if (currentState == RUNNING_WORK || currentState == BLINKING_WORK) {
            // Reset work timer and its display
            workTimer->reset();
            workViewer->displayTime(workTimer->getInitialMinutes(), 0);

            // Start the break timer
            breakTimer->start();
            ledGreen->turnOn();
            ledRed->turnOff();
            currentState = RUNNING_BREAK;
        }
    }

    // Update timers
    workTimer->update();
    breakTimer->update();

    // Handle blinking if necessary
    handleBlinking();

    // Update displays
    updateDisplays();
}

void Controller::updateDisplays() {
    if (currentState == RUNNING_WORK) {
        if (workTimer->isFinished()) {
            currentState = BLINKING_WORK;
        } else {
            unsigned long remaining = workTimer->getTimeRemaining();
            int minutes = remaining / 60;
            int seconds = remaining % 60;
            workViewer->displayTime(minutes, seconds);
        }
    } else if (currentState == RUNNING_BREAK) {
        if (breakTimer->isFinished()) {
            currentState = BLINKING_BREAK;
        } else {
            unsigned long remaining = breakTimer->getTimeRemaining();
            int minutes = remaining / 60;
            int seconds = remaining % 60;
            breakViewer->displayTime(minutes, seconds);
        }
    } else if (currentState == IDLE) {
        // Display initial times in IDLE state
        workViewer->displayTime(workTimer->getInitialMinutes(), 0);
        breakViewer->displayTime(breakTimer->getInitialMinutes(), 0);
    }
}

void Controller::handleBlinking() {
    if (currentState == BLINKING_WORK || currentState == BLINKING_BREAK) {
        static bool toggle = false;
        static unsigned long lastBlinkTime = 0;
        const unsigned long BLINK_INTERVAL = 500; // ms

        unsigned long currentTime = millis();
        if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
            if (toggle) {
                // Show "00:00"
                if (currentState == BLINKING_WORK) {
                    workViewer->displayTime(0, 0);
                } else {
                    breakViewer->displayTime(0, 0);
                }
            } else {
                // Clear screen
                if (currentState == BLINKING_WORK) {
                    workViewer->clear();
                } else {
                    breakViewer->clear();
                }
            }
            toggle = !toggle;
            lastBlinkTime = currentTime;
        }

        static bool soundPlayed = false;
        if (!soundPlayed) {
            buzzer->playTone(1000, 200); // 1000Hz for 200ms
            soundPlayed = true;
        }

        // Wait for user to press the button to start the next timer
        if (button->isPressed()) {
            if (currentState == BLINKING_WORK) {
                // Reset work timer and start break
                workTimer->reset();
                workViewer->displayTime(workTimer->getInitialMinutes(), 0);
                breakTimer->start();
                ledGreen->turnOn();
                ledRed->turnOff();
                currentState = RUNNING_BREAK;
            } else if (currentState == BLINKING_BREAK) {
                // Reset break timer and start work
                breakTimer->reset();
                breakViewer->displayTime(breakTimer->getInitialMinutes(), 0);
                workTimer->start();
                ledRed->turnOn();
                ledGreen->turnOff();
                currentState = RUNNING_WORK;
            }
            soundPlayed = false; // Reset for the next cycle
        }
    }
}
