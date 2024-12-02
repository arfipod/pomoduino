#ifdef M5STICKC

#include "M5Buzzer.h"

void M5Buzzer::init() {
    // Inicializar el altavoz si es necesario
    M5.Beep.begin();
}

void M5Buzzer::playTone(unsigned int frequency, unsigned long duration) {
    M5.Beep.setVolume(100);
    M5.Beep.tone(frequency, duration);
}

void M5Buzzer::stopTone() {
    M5.Beep.mute();
}

#endif // M5STICKC