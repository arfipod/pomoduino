#ifndef IBUZZER_H
#define IBUZZER_H

class IBuzzer {
public:
    virtual ~IBuzzer() {}

    // Inicializar el buzzer
    virtual void init() = 0;

    // Reproducir un tono
    virtual void playTone(unsigned int frequency, unsigned long duration) = 0;

    // Detener el tono
    virtual void stopTone() = 0;
};

#endif // IBUZZER_H