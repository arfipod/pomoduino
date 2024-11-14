// main.cpp

#include <Arduino.h>
#include "DisplayModule.h"
#include "EncoderModule.h"
#include "LEDModule.h"
#include "TimerModule.h"
#include "Controller.h"

// Definición de pines
#define CLK1 4
#define DIO1 5
#define CLK2 6
#define DIO2 7

#define ENCODER_CLK 2
#define ENCODER_DT 3
#define ENCODER_SW 8

#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define EXTRA_GND_PIN 12

// Instancias de módulos
DisplayModule display1(CLK1, DIO1);     // Display para 10 minutos (Descanso)
DisplayModule display2(CLK2, DIO2);     // Display para 35 minutos (Trabajo)
LEDModule ledRed(LED_RED_PIN);
LEDModule ledGreen(LED_GREEN_PIN);
EncoderModule encoder(ENCODER_CLK, ENCODER_DT, ENCODER_SW);
Controller controller(&display1, &display2, &encoder, &ledRed, &ledGreen);

void setup() {
  // Configurar el pin 12 como GND adicional
  pinMode(EXTRA_GND_PIN, OUTPUT);
  digitalWrite(EXTRA_GND_PIN, LOW);

  // Inicializar la comunicación serial para depuración
  Serial.begin(9600);

  // Inicializar el controlador
  controller.setup();
}

void loop() {
  // Ejecutar la lógica principal
  controller.loop();
}
