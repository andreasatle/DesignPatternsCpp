#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "solid.h"

using namespace std;

/// Class LiskovSubstitutionPrinciple is the super-class of the rectangle example.
class LiskovSubstitutionPrinciple : public Solid {};

class Rectangle : public LiskovSubstitutionPrinciple {
protected:
    int width;
    int height;
public:
    Rectangle(const int _width, const int _height);
    int getWidth() const;
    virtual void setWidth(const int _width);
    int getHeight() const;
    virtual void setHeight(const int _height);
    int area() const;
    string str() const;
};

/// The function processes a rectange with rectangle logic.
///
/// The processing should work for all sub-classes of Rectangle.
/// We create an example Square that produce the wrong area,
/// so this violates the Liskov Substitution Principle.
void process(Rectangle& r);

class Square : public Rectangle {
public:
    Square(const int length);
    void setWidth(const int _width) override;
    void setHeight(const int _height) override;
};