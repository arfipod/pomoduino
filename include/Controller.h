#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ITimeViewer.h"
#include "IButton.h"
#include "ILight.h"
#include "ITimer.h" // Incluir la interfaz ITimer

// Enumeración para representar el estado del controlador
enum State {
    IDLE,
    RUNNING_WORK,
    RUNNING_BREAK,
    BLINKING_WORK,
    BLINKING_BREAK
};

class Controller {
private:
    ITimeViewer* workViewer;   // Visor de tiempo para el temporizador de trabajo
    ITimeViewer* breakViewer;  // Visor de tiempo para el temporizador de descanso
    IButton* button;           // Botón genérico para interacción del usuario
    ILight* ledRed;            // Indicador para el estado de trabajo
    ILight* ledGreen;          // Indicador para el estado de descanso
    ITimer* workTimer;         // Temporizador para la sesión de trabajo
    ITimer* breakTimer;        // Temporizador para la sesión de descanso
    State currentState;        // Estado actual del controlador

    // Actualiza las pantallas con la información del temporizador
    void updateDisplays();

    // Maneja el parpadeo al finalizar un temporizador
    void handleBlinking();

public:
    // Constructor del controlador
    Controller(ITimeViewer* work, ITimeViewer* rest, IButton* btn, ILight* red, ILight* green, ITimer* workT, ITimer* breakT);

    // Configuración inicial del controlador
    void setup();

    // Lógica principal del controlador que se ejecuta en cada ciclo
    void loop();

    // Destructor para limpiar recursos
    ~Controller();
};

#endif // CONTROLLER_H