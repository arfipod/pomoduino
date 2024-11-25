#ifndef M5BUZZER_H
#define M5BUZZER_H

#ifdef M5STICKC

#include <M5StickCPlus.h>
#include "IBuzzer.h"

class M5Buzzer : public IBuzzer {
public:
    void init() override;
    void playTone(unsigned int frequency, unsigned long duration) override;
    void stopTone() override;
};

#endif // M5STICKC

#endif // M5BUZZER_H