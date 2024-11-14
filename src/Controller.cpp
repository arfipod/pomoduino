#include "Controller.h"
#include <Arduino.h>

// Constructor
Controller::Controller(DisplayModule* disp1, DisplayModule* disp2,
                       EncoderModule* enc, LEDModule* red, LEDModule* green)
  : display1(disp1), display2(disp2), encoder(enc),
    ledRed(red), ledGreen(green),
    workTimer(new TimerModule(WORK, 35UL * 60 * 1000)),    // 35 minutos
    breakTimer(new TimerModule(BREAK_TIME, 10UL * 60 * 1000)), // 10 minutos
    currentState(IDLE), lastBlinkTime(0), blinkState(false),
    currentSelection(WORK) {}

// Destructor para liberar memoria
Controller::~Controller() {
    delete workTimer;
    delete breakTimer;
}

// Inicializar todos los módulos
void Controller::setup() {
  // Inicializar displays
  display1->init();
  display2->init();

  // Inicializar LEDs
  ledRed->init();
  ledGreen->init();

  // Inicializar encoder
  encoder->init();
  encoder->setInstance();

  // Inicializar temporizadores
  workTimer->reset();
  breakTimer->reset();

  // Inicializar estado
  currentState = IDLE;
  currentSelection = WORK;

  // Mostrar el tiempo seleccionado en los displays
  display2->displayTime(35, 0); // Display 2 para trabajo: 35:00
  display1->displayTime(10, 0); // Display 1 para descanso: 10:00

  // Encender el LED rojo para indicar selección de WORK
  ledRed->turnOn();
  ledGreen->turnOff();

  // Inicializar variables de parpadeo
  lastBlinkTime = millis();
  blinkState = false;
}

// Actualizar displays
void Controller::updateDisplays() {
  if (currentSelection == WORK) {
    int remaining = workTimer->getTimeRemaining();
    int minutes = remaining / 60;
    int seconds = remaining % 60;
    display2->displayTime(minutes, seconds, true);
    display1->clear();
  } else { // BREAK_TIME
    int remaining = breakTimer->getTimeRemaining();
    int minutes = remaining / 60;
    int seconds = remaining % 60;
    display1->displayTime(minutes, seconds, true);
    display2->clear();
  }
}

// Manejar el parpadeo de los displays
void Controller::handleBlinking() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkTime >= 500) { // Cambiar cada 500 ms
    lastBlinkTime = currentMillis;
    blinkState = !blinkState;
    if (currentSelection == WORK) {
      if (blinkState) {
        display2->clear(); // Apagar el display
      } else {
        display2->displayTime(0, 0, false); // Mostrar "00:00" sin colon
      }
    } else { // BREAK_TIME
      if (blinkState) {
        display1->clear(); // Apagar el display
      } else {
        display1->displayTime(0, 0, false); // Mostrar "00:00" sin colon
      }
    }
  }
}

// Lógica principal del loop
void Controller::loop() {
  // Manejar botón del encoder
  if (encoder->isButtonPressed()) {
    switch (currentState) {
      case IDLE:
        // Iniciar el temporizador seleccionado
        if (currentSelection == WORK) {
          workTimer->start();
          ledRed->turnOn();
          ledGreen->turnOff();
          currentState = RUNNING_WORK;
        } else {
          breakTimer->start();
          ledGreen->turnOn();
          ledRed->turnOff();
          currentState = RUNNING_BREAK;
        }
        break;

      case RUNNING_WORK:
      case RUNNING_BREAK:
        // Al presionar el botón durante un conteo regresivo:
        // Poner el temporizador actual a cero y cambiar al otro temporizador
        if (currentSelection == WORK) {
          // Poner el temporizador de trabajo a cero
          workTimer->reset();
          // Iniciar el temporizador de descanso
          breakTimer->start();
          currentSelection = BREAK_TIME;
          // Encender LED verde y apagar el rojo
          ledGreen->turnOn();
          ledRed->turnOff();
          currentState = RUNNING_BREAK;
        } else {
          // Poner el temporizador de descanso a cero
          breakTimer->reset();
          // Iniciar el temporizador de trabajo
          workTimer->start();
          currentSelection = WORK;
          // Encender LED rojo y apagar el verde
          ledRed->turnOn();
          ledGreen->turnOff();
          currentState = RUNNING_WORK;
        }
        break;

      case BLINKING_WORK:
        // Reiniciar el temporizador de descanso
        currentSelection = BREAK_TIME;
        breakTimer->reset();
        breakTimer->start();
        ledGreen->turnOn();
        ledRed->turnOff();
        currentState = RUNNING_BREAK;
        break;

      case BLINKING_BREAK:
        // Reiniciar el temporizador de trabajo
        currentSelection = WORK;
        workTimer->reset();
        workTimer->start();
        ledRed->turnOn();
        ledGreen->turnOff();
        currentState = RUNNING_WORK;
        break;
    }
  }

  // Actualizar temporizadores
  workTimer->update();
  breakTimer->update();

  // Verificar si algún temporizador ha terminado
  if (currentState == RUNNING_WORK && workTimer->isFinished()) {
    currentState = BLINKING_WORK;
    workTimer->reset();
  }

  if (currentState == RUNNING_BREAK && breakTimer->isFinished()) {
    currentState = BLINKING_BREAK;
    breakTimer->reset();
  }

  // Actualizar displays y LEDs según el estado
  switch (currentState) {
    case IDLE:
      // Mostrar el tiempo seleccionado
      if (currentSelection == WORK) {
        display2->displayTime(35, 0); // Display 2 para trabajo
        display1->displayTime(10, 0); // Display 1 para descanso
      } else {
        display1->displayTime(10, 0); // Display 1 para descanso
        display2->displayTime(35, 0); // Display 2 para trabajo
      }
      break;

    case RUNNING_WORK:
      // Actualizar displays con tiempo restante
      updateDisplays();
      break;

    case RUNNING_BREAK:
      // Actualizar displays con tiempo restante
      updateDisplays();
      break;

    case BLINKING_WORK:
    case BLINKING_BREAK:
      // Manejar el parpadeo de los displays
      handleBlinking();
      break;
  }

  // Imprimir el estado actual y tiempo restante para depuración
  switch (currentState) {
    case IDLE:
      Serial.println("Estado: IDLE");
      break;
    case RUNNING_WORK:
      Serial.print("Estado: RUNNING_WORK - Tiempo restante: ");
      Serial.println(workTimer->getTimeRemaining());
      break;
    case RUNNING_BREAK:
      Serial.print("Estado: RUNNING_BREAK - Tiempo restante: ");
      Serial.println(breakTimer->getTimeRemaining());
      break;
    case BLINKING_WORK:
      Serial.println("Estado: BLINKING_WORK");
      break;
    case BLINKING_BREAK:
      Serial.println("Estado: BLINKING_BREAK");
      break;
  }

  // Pequeña demora para evitar demasiadas actualizaciones
  delay(100);
}
