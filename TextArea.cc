#include "TextArea.h"

TextArea::TextArea(int x, int y, int width, int height, const std::string& id, const std::string& label, 
    const RGB& fill, const RGB& border){
    this->dim.x = x;
    this->dim.y = y;
    this->dim.width = width;
    this->dim.height = height;
    this->id = id;
    this->text = label;
    this->fill = fill;
    this->border = border;
}

TextArea::TextArea(const Rectangle& dim, const std::string& id, const std::string& label, 
    const RGB& fill, const RGB& border){
    this->dim = dim;
    this->id = id;
    this->text = label;
    this->fill = fill;
    this->border = border;
}

// void TextArea::draw(Display *display, Window win, GC gc, int x, int y) const {
//     x += dim.x;  
//     y += dim.y;

//     XSetForeground(display, gc, fill.getColour());
//     XFillRectangle(display, win, gc, x, y, dim.width, dim.height);
    
//     XSetForeground(display, gc, border.getColour());
//     XDrawRectangle(display, win, gc, x, y, dim.width, dim.height);
    
//     const char* font_name = "fixed"; 
//     XID font = XLoadFont(display, font_name);
//     XFontStruct* font_info = XQueryFont(display, font);
//     if (!font_info) {
//         XCloseDisplay(display);
//         return; 
//     }
//     XSetFont(display, gc, font);

//     int text_width = XTextWidth(font_info, text.c_str(), text.length());
//     int length = text.length();

//     while (text_width > dim.width - 10){
//         length--;
//         text_width = XTextWidth(font_info, text.c_str(), length);
//     }

//     int offsetX = (dim.width - text_width)/2;

//     int text_height = font_info->ascent + font_info->descent;

//     int offsetY = (dim.height - text_height)/2 + font_info->ascent;

//     XFreeFontInfo(NULL, font_info, 1);
// }

void TextArea::draw(Display *display, Window win, GC gc, int xOffset, int yOffset) const {
    
    XSetForeground(display, gc, fill.getColorPixel(display));
    XFillRectangle(display, win, gc, xOffset + dim.x, yOffset + dim.y, dim.width, dim.height);
    XSetForeground(display, gc, border.getColorPixel(display));
    XDrawRectangle(display, win, gc, xOffset + dim.x, yOffset + dim.y, dim.width, dim.height);

    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    int lineHeight = 20; // Adjust as needed
    int textX = xOffset + dim.x + 5;
    int textY = yOffset + dim.y + lineHeight;

    std::string remainingText = text;
    while (!remainingText.empty() && textY < yOffset + dim.y + dim.height - lineHeight) {
        int charsWidth = XTextWidth(XQueryFont(display, XGContextFromGC(gc)), remainingText.c_str(), remainingText.length());
        int charsToFit = remainingText.length();
        
        while (charsWidth > dim.width - 10 && charsToFit > 0) {
            charsToFit--;
            charsWidth = XTextWidth(XQueryFont(display, XGContextFromGC(gc)), remainingText.c_str(), charsToFit);
        }

        XDrawString(display, win, gc, textX, textY, remainingText.c_str(), charsToFit);
        remainingText = remainingText.substr(charsToFit);
        textY += lineHeight;
    }
}

bool TextArea::overlaps(const TextArea& ta) const {
    return dim.overlaps(ta.dim);
}

void TextArea::print() const {
    std::cout << "TextArea: " << id << " at (" << dim.x << ", " << dim.y 
              << ") with dim " << dim.width << "x" << dim.height
              << ", Label: " << text << std::endl;
}

std::string TextArea::getId() const {
    return id;
}

int TextArea::getWidth() const {
    return dim.width;
}

int TextArea::getHeight() const {
    return dim.height;
}

void TextArea::setText(const std::string& text) {
    this->text = text;
}

void TextArea::setHeight(int height) {
    dim.height = height;
}
