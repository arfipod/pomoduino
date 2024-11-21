#ifndef M5BUTTON_H
#define M5BUTTON_H

#include <M5StickCPlus.h>
#include "IButton.h"

class M5Button : public IButton {
public:
    void init() override;
    bool isPressed() override;
};

#endif // M5BUTTON_H