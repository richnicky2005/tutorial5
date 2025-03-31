#ifndef RGB_H
#define RGB_H
#include <iostream>
#include "defs.h"
#include <X11/Xlib.h>

class RGB{
    private:
        int r;
        int g;
        int b;
    public:
        RGB(int r, int g, int b); 
        RGB(CuColour colour);
        RGB();
        CuColour getColour() const;
        void setColour(CuColour colour);
        // void print() const;

        int getR() const;
        int getG() const;
        int getB() const;
        void setR(int r);
        void setB(int b);
        void setG(int g);

        static const RGB WHITE();
        static const RGB BLACK();
        static const RGB RED();
        static const RGB GREEN();
        static const RGB BLUE();

        unsigned long getColorPixel(Display* display) const;
};

#endif
