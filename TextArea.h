#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <iostream>
#include <string>
#include "defs.h"
#include "RGB.h"
#include <X11/Xlib.h>

class TextArea {
    private:
        Rectangle dim;
        std::string text;
        std::string id;
        RGB fill;
        RGB border;
        
    public:
        TextArea(int x, int y, int width, int height, const std::string& id, const std::string& label, 
                 const RGB& fill = RGB::WHITE(), const RGB& border = RGB::BLACK());
        TextArea(const Rectangle& dim, const std::string& id, const std::string& label, 
                 const RGB& fill = RGB::WHITE(), const RGB& border = RGB::BLACK());
        
        void draw(Display *display, Window win, GC gc, int x, int y) const;
        bool overlaps(const TextArea& ta) const;
        void print() const;
        std::string getId() const;

        // Add getters for other properties
        Rectangle getDimensions() const { return dim; }
        std::string getText() const { return text; }
        RGB getFill() const { return fill; }
        RGB getBorder() const { return border; }
        int getWidth() const;
        int getHeight() const;
        void setText(const std::string& text);
        void setHeight(int height);
};

#endif