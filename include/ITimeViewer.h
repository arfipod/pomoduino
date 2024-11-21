#ifndef ITIMEVIEWER_H
#define ITIMEVIEWER_H

class ITimeViewer {
public:
    virtual ~ITimeViewer() {}

    virtual void init() = 0;
    virtual void displayTime(int minutes, int seconds) = 0;
    virtual void clear() = 0;
};

#endif // ITIMEVIEWER_H