#include "RGB.h"
// #include <iostream>
// #include <string>

RGB::RGB(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
}
RGB::RGB(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

RGB::RGB(CuColour colour){
    this->r = (colour & (0b11111111 << 16)) >> 16;
    this->g = (colour & (0b11111111 << 8)) >> 8;
    this->b = (colour & 0b11111111);
}



CuColour RGB::getColour() const{
    CuColour colour =0;

    colour = (r << 16) | (g << 8) | b;


    return colour;
}
void RGB::setColour(CuColour colour){
    r = (colour & (0b11111111 << 16)) >> 16;
    g = (colour & (0b11111111 << 8)) >> 8;
    b = (colour & 0b11111111);

}

// void RGB::print() const {
//     std::cout<<"("<<r<<", "<<g<<", "<<b<<")"<<std::endl;
// }

int RGB::getR() const{
    return r;
}
int RGB::getG() const{
    return g;
}
int RGB::getB() const{
    return b;
}
void RGB::setR(int r){
    this->r = r;
}
void RGB::setG(int g){
    this->g = g;
}
void RGB::setB(int b){
    this->b = b;
}

const RGB RGB::BLACK(){
    return RGB(0,0,0);
}
const RGB RGB::WHITE(){
    return RGB(255,255,255);
}
const RGB RGB::RED(){
    return RGB(255,0,0);
}
const RGB RGB::GREEN(){
    return RGB(0,255,0);
};

const RGB RGB::BLUE(){  
    return RGB(0, 0, 255);
};

unsigned long RGB::getColorPixel(Display* display) const {
    Colormap colormap = DefaultColormap(display, DefaultScreen(display));
    XColor xcolor;
    xcolor.red = r * 257;   // Convert 0-255 range to 0-65535 range
    xcolor.green = g * 257;
    xcolor.blue = b * 257;
    xcolor.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(display, colormap, &xcolor);
    return xcolor.pixel;
}