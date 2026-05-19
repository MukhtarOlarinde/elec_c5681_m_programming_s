#ifndef SHARK_H
#define SHARK_H

#include "N5110.h"
#include "Utils.h"
#include "Joystick.h" 

class Shark {
public:
    Shark(int x, int y, int width, int height, int speed); // Constructor
    void draw(N5110 &lcd); // Draw shark on the LCD
    void move(); // Move shark horizontally
    Position2D get_position(); // Get shark's position
    int get_width(); // Get shark's width
    int get_height(); // Get shark's height
    int get_speed();

private:
    int _x; // X-coordinate of the shark
    int _y; // Y-coordinate of the shark
    int _width; // Width of the shark
    int _height; // Height of the shark
    int _speed; // Speed of the shark
};

#endif