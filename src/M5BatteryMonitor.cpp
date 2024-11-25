#ifdef M5STICKC

#include "M5BatteryMonitor.h"

M5BatteryMonitor::M5BatteryMonitor() : lastBatteryUpdate(0) {}

void M5BatteryMonitor::init() {
    M5.Axp.EnableCoulombcounter();
}

void M5BatteryMonitor::update() {
    unsigned long currentTime = millis();
    if (currentTime - lastBatteryUpdate >= BATTERY_UPDATE_INTERVAL) {
        // Get battery voltage
        float voltage = M5.Axp.GetBatVoltage();

        // Calculate battery percentage
        float batteryPercentage = calculateBatteryPercentage(voltage);
        batteryPercentage = constrain(batteryPercentage, 0.0, 100.0);

        // Display on screen
        int x = 220; // Adjust as needed
        int y = 0;   // Adjust as needed

        // Clear previous battery area
        M5.Lcd.fillRect(x - 60, y, 60, 15, TFT_BLACK);

        // Set cursor to top right
        M5.Lcd.setTextDatum(TR_DATUM); // Top Right
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        M5.Lcd.drawString("Bat: " + String((int)batteryPercentage) + "%", x, y);

        // Optional: Print to serial monitor
        Serial.print("Battery Voltage: ");
        Serial.println(voltage);
        Serial.print("Battery Percentage: ");
        Serial.println(batteryPercentage);

        lastBatteryUpdate = currentTime;
    }
}

float M5BatteryMonitor::calculateBatteryPercentage(float voltage) {
    const float MIN_VOLTAGE = 3.0; // Minimum voltage (0%)
    const float MAX_VOLTAGE = 4.2; // Maximum voltage (100%)

    if (voltage >= MAX_VOLTAGE) {
        return 100.0;
    } else if (voltage <= MIN_VOLTAGE) {
        return 0.0;
    } else {
        // Linear calculation of percentage
        return ((voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100.0;
    }
}

#endif // M5STICKC
