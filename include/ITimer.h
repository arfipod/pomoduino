#ifndef ITIMER_H
#define ITIMER_H

class ITimer {
public:
    virtual ~ITimer() {}

    // Iniciar el temporizador
    virtual void start() = 0;

    // Actualizar el temporizador (llamado en loop)
    virtual void update() = 0;

    // Verificar si el temporizador ha terminado
    virtual bool isFinished() const = 0;

    // Verificar si el temporizador está corriendo
    virtual bool isRunning() const = 0;

    // Obtener tiempo restante en segundos
    virtual unsigned long getTimeRemaining() const = 0;

    // Reiniciar el temporizador
    virtual void reset() = 0;

    // **Nuevo método para obtener los minutos iniciales**
    virtual unsigned long getInitialMinutes() const = 0;
};

#endif // ITIMER_H