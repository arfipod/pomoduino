#include <Arduino.h>

// Dependencias del proyecto
#include "Controller.h"
#include "DisplayViewer.h"
#include "TextViewer.h"
#include "EncoderModule.h"
#include "LEDModule.h"
#include "TimerModule.h" // Incluir TimerModule

// Definir pines para Arduino UNO
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

// Definir M5StickCPlus como objetivo
#elif defined(M5STICKC)
#include <M5StickCPlus.h>
#include "M5Button.h"
#include "ScreenIndicator.h"
#define WORK_DISPLAY_X 10
#define WORK_DISPLAY_Y 20
#define BREAK_DISPLAY_X 10
#define BREAK_DISPLAY_Y 60
#endif

// Crear punteros para los viewers y el controller
ITimeViewer* workViewer = nullptr;
ITimeViewer* breakViewer = nullptr;
Controller* controller = nullptr;

// Crear módulos comunes
IButton* button = nullptr;
ILight* ledRed = nullptr;
ILight* ledGreen = nullptr;

// Crear temporizadores
ITimer* workTimer = nullptr;
ITimer* breakTimer = nullptr;

// Función para calcular el porcentaje de batería
float calculateBatteryPercentage(float voltage) {
    const float MIN_VOLTAGE = 3.0; // Voltaje mínimo (0%)
    const float MAX_VOLTAGE = 4.2; // Voltaje máximo (100%)

    if (voltage >= MAX_VOLTAGE) {
        return 100.0;
    } else if (voltage <= MIN_VOLTAGE) {
        return 0.0;
    } else {
        // Cálculo lineal del porcentaje
        return ((voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100.0;
    }
}

#if defined(M5STICKC)
void displayBatteryInfo() {
    static unsigned long lastBatteryUpdate = 0;
    const unsigned long BATTERY_UPDATE_INTERVAL = 5000; // 5 segundos

    unsigned long currentTime = millis();
    if (currentTime - lastBatteryUpdate >= BATTERY_UPDATE_INTERVAL) {
        // Obtener datos del contador de Coulomb
        float coulombCharge = M5.Axp.GetCoulombData(); // Carga neta en mAh

        // Definir la capacidad total de la batería (por ejemplo, 110 mAh para M5StickCPlus)
        const float BATTERY_CAPACITY = 110.0; // Ajusta según la capacidad real de tu batería

        // Calcular el porcentaje de batería
        float batteryPercentage = (coulombCharge / BATTERY_CAPACITY) * 100.0;
        batteryPercentage = constrain(batteryPercentage, 0.0, 100.0);

        // Mostrar en la pantalla
        int x = 220; // Ajusta según necesidad
        int y = 120; // Ajusta según necesidad

        // Borrar el área anterior de la batería
        M5.Lcd.fillRect(x - 60, y - 15, 60, 15, TFT_BLACK);

        // Ajustar el cursor al extremo derecho
        M5.Lcd.setTextDatum(TR_DATUM); // Top Right
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        M5.Lcd.drawString("Bat: " + String((int)batteryPercentage) + "%", x, y);

        // Opcional: Mostrar en el monitor serial
        Serial.print("Carga neta (mAh): ");
        Serial.println(coulombCharge);
        Serial.print("Porcentaje de batería: ");
        Serial.println(batteryPercentage);

        lastBatteryUpdate = currentTime;
    }
}
#endif

void resetCoulombCounter() {
    M5.Axp.DisableCoulombcounter();
    M5.Axp.EnableCoulombcounter();
}

// Configuración inicial
void setup() {
    Serial.begin(115200);

    #if defined(ARDUINO_UNO)
    button = new EncoderButton(ENCODER_SW);
    ledRed = new LEDIndicator(LED_RED_PIN);
    ledGreen = new LEDIndicator(LED_GREEN_PIN);
    workViewer = new DisplayViewer(WORK_DISPLAY_CLK, WORK_DISPLAY_DIO);
    breakViewer = new DisplayViewer(BREAK_DISPLAY_CLK, BREAK_DISPLAY_DIO);
    workViewer->init();
    breakViewer->init();
    #elif defined(M5STICKC)
    M5.begin();
    M5.Lcd.setRotation(1);

    M5.Axp.EnableCoulombcounter();

    button = new M5Button();
    ledRed = new ScreenIndicator(180, 37, RED);
    ledGreen = new ScreenIndicator(180, 75, GREEN);

    workViewer = new TextViewer(WORK_DISPLAY_X, WORK_DISPLAY_Y);
    breakViewer = new TextViewer(BREAK_DISPLAY_X, BREAK_DISPLAY_Y);
    workViewer->init();
    breakViewer->init();
    #endif

    button->init();
    ledRed->init();
    ledGreen->init();

    // Crear instancias de TimerModule y asignarlas a ITimer
    workTimer = new TimerModule(WORK, 35UL * 60 * 1000); // 35 minutos
    breakTimer = new TimerModule(BREAK_TIME, 10UL * 60 * 1000); // 10 minutos

    // Crear el controlador pasando las dependencias
    controller = new Controller(workViewer, breakViewer, button, ledRed, ledGreen, workTimer, breakTimer);

    controller->setup();

    resetCoulombCounter();
}

void loop()
{
    controller->loop();

    #if defined(M5STICKC) // TODO Convertir en un componente y remover del loop principal
    displayBatteryInfo();
    #endif
}


