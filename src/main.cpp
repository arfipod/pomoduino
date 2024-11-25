#include <Arduino.h>

// Project dependencies
#include "Controller.h"
#include "DisplayViewer.h"
#include "TextViewer.h"
#include "EncoderModule.h"
#include "LEDModule.h"
#include "TimerModule.h"

// Define pins for Arduino UNO
#if defined(ARDUINO_UNO)
#include "EncoderButton.h"
#include "LEDIndicator.h"
#define WORK_DISPLAY_CLK 6
#define WORK_DISPLAY_DIO 7
#define BREAK_DISPLAY_CLK 4
#define BREAK_DISPLAY_DIO 5
#define ENCODER_CLK 2
#define ENCODER_DT 3
#define ENCODER_SW 8
#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define BUZZER_PIN 11

#elif defined(M5STICKC)
// Define M5StickCPlus as target
#include <M5StickCPlus.h>
#include "M5Button.h"
#include "ScreenIndicator.h"
#include "M5Buzzer.h"
#include "M5BatteryMonitor.h"
#define WORK_DISPLAY_X 10
#define WORK_DISPLAY_Y 20
#define BREAK_DISPLAY_X 10
#define BREAK_DISPLAY_Y 60
#endif

// Create pointers for viewers, controller, and modules
ITimeViewer* workViewer = nullptr;
ITimeViewer* breakViewer = nullptr;
Controller* controller = nullptr;

IButton* button = nullptr;
ILight* ledRed = nullptr;
ILight* ledGreen = nullptr;
IBuzzer* buzzer = nullptr;
IBatteryMonitor* batteryMonitor = nullptr;

ITimer* workTimer = nullptr;
ITimer* breakTimer = nullptr;

// Setup function
void setup() {
    Serial.begin(115200);

#if defined(ARDUINO_UNO)
    // Specific initialization for Arduino UNO
    button = new EncoderButton(ENCODER_SW);
    ledRed = new LEDIndicator(LED_RED_PIN);
    ledGreen = new LEDIndicator(LED_GREEN_PIN);
    workViewer = new DisplayViewer(WORK_DISPLAY_CLK, WORK_DISPLAY_DIO);
    breakViewer = new DisplayViewer(BREAK_DISPLAY_CLK, BREAK_DISPLAY_DIO);
    workViewer->init();
    breakViewer->init();
    buzzer = new ArduinoBuzzer(BUZZER_PIN);
    batteryMonitor = nullptr; // No battery monitor for Arduino UNO

#elif defined(M5STICKC)
    // Specific initialization for M5StickCPlus
    M5.begin();
    M5.Lcd.setRotation(1);

    button = new M5Button();
    ledRed = new ScreenIndicator(180, 37, RED);
    ledGreen = new ScreenIndicator(180, 75, GREEN);

    workViewer = new TextViewer(WORK_DISPLAY_X, WORK_DISPLAY_Y);
    breakViewer = new TextViewer(BREAK_DISPLAY_X, BREAK_DISPLAY_Y);
    workViewer->init();
    breakViewer->init();
    buzzer = new M5Buzzer();
    batteryMonitor = new M5BatteryMonitor();

#endif

    button->init();
    ledRed->init();
    ledGreen->init();
    buzzer->init();
    if (batteryMonitor) {
        batteryMonitor->init();
    }

    // Create instances of TimerModule and assign to ITimer
    workTimer = new TimerModule(WORK, 35UL * 60 * 1000);      // 35 minutes
    breakTimer = new TimerModule(BREAK_TIME, 10UL * 60 * 1000); // 10 minutes

    // Create the controller passing dependencies
    controller = new Controller(workViewer, breakViewer, button, ledRed, ledGreen,
                                workTimer, breakTimer, buzzer, batteryMonitor);

    controller->setup();

    // Display initial values on viewers
    workViewer->displayTime(workTimer->getInitialMinutes(), 0);
    breakViewer->displayTime(breakTimer->getInitialMinutes(), 0);
}

void loop() {
    controller->loop();
}
