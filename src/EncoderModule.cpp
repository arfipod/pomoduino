#include "EncoderModule.h"

// Inicialización del puntero estático
EncoderModule* EncoderModule::instance = nullptr;

// Constructor
EncoderModule::EncoderModule(int clk, int dt, int sw)
  : clkPin(clk), dtPin(dt), swPin(sw), counter(0), lastStateDT(0), lastButtonPressTime(0) {}

// Inicializar el encoder
void EncoderModule::init() {
  pinMode(clkPin, INPUT_PULLUP); // Activar pull-up interno
  pinMode(dtPin, INPUT_PULLUP);  // Activar pull-up interno
  pinMode(swPin, INPUT_PULLUP);
  lastStateDT = digitalRead(dtPin);
}

// Configurar la instancia para manejar interrupciones
void EncoderModule::setInstance() {
  instance = this;
  attachInterrupt(digitalPinToInterrupt(clkPin), EncoderModule::handleInterrupt, CHANGE);
}

// Método estático para manejar interrupciones
void EncoderModule::handleInterrupt() {
  if (instance) {
    instance->update();
  }
}

// Actualizar el contador del encoder
void EncoderModule::update() {
  int currentStateDT = digitalRead(dtPin);
  if (currentStateDT != lastStateDT) {
    if (digitalRead(clkPin) != currentStateDT) {
      counter++;
    } else {
      counter--;
    }
  }
  lastStateDT = currentStateDT;
}

// Manejar el botón del encoder con debounce
bool EncoderModule::isButtonPressed() {
  if (digitalRead(swPin) == LOW) {
    if (millis() - lastButtonPressTime > 200) { // Debounce de 200 ms
      lastButtonPressTime = millis();
      return true;
    }
  }
  return false;
}

// Obtener el valor del contador
int EncoderModule::getCounter() {
  return counter;
}

// Reiniciar el contador
void EncoderModule::resetCounter() {
  counter = 0;
}
