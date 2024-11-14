#include "LEDModule.h"

// Constructor
LEDModule::LEDModule(int ledPin) 
  : pin(ledPin), state(false) {}

// Inicializar el LED
void LEDModule::init() {
  pinMode(pin, OUTPUT);
  turnOff();
}

// Encender el LED
void LEDModule::turnOn() {
  state = true;
  digitalWrite(pin, HIGH);
}

// Apagar el LED
void LEDModule::turnOff() {
  state = false;
  digitalWrite(pin, LOW);
}

// Verificar si el LED está encendido
bool LEDModule::isOn() const {
  return state;
}
