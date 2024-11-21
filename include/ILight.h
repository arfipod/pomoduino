#ifndef ILIGHT_H
#define ILIGHT_H

class ILight {
public:
    virtual ~ILight() {}

    virtual void init() = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

#endif // ILIGHT_H