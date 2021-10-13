#include "liskov_substitution.h"

Rectangle::Rectangle(const int _width, const int _height) : width{_width}, height{_height} {}

int Rectangle::getWidth() const {
    return width;
}

void Rectangle::setWidth(const int _width) {
    width = _width;
}

int Rectangle::getHeight() const {
    return height;
}

void Rectangle::setHeight(const int _height) {
    height = _height;
}

int Rectangle::area() const {
    return width*height;
}

string Rectangle::str() const {
    stringstream buffer;
    buffer << "Rectangle(width=" << width << ", height=" << height << ")" << endl;
    buffer << "Area: " << area() << endl;
    return buffer.str();
}

void process(Rectangle& r) {
    int width = r.getWidth();
    r.setHeight(10);
    cout << "Expected area: " << 10*width << ", got " << r.area() << endl;
}

Square::Square(const int size) : Rectangle(size, size) {};

void Square::setWidth(int _width) {
    this->width = this->height = _width;
}
void Square::setHeight(int _height) {
    this->width = this->height = _height;
}