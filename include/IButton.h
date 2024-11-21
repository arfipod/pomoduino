#ifndef IBUTTON_H
#define IBUTTON_H

class IButton {
public:
    virtual ~IButton() {}

    // Inicializa el botón
    virtual void init() = 0;

    // Verifica si el botón está presionado
    virtual bool isPressed() = 0;
};

#endif // IBUTTON_H