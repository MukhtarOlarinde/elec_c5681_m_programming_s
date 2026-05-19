#include "Shark.h"

// Constructor
Shark::Shark(int x, int y, int width, int height, int speed)
    : _x(x), _y(y), _width(width), _height(height), _speed(speed) {}

// Draw obstacle on LCD
void Shark::draw(N5110 &lcd) {

    const int sharksprite[15][21]= {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1 },
	{ 0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,1,0,1 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1 },
	{ 0,0,1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,1,1 },
	{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0 }
};
    //lcd.drawRect(_x, _y, _width, _height, FILL_BLACK);
    lcd.drawSprite(_x, _y - 5, 15, 21, (int*)sharksprite);
}

// Move the shark horizontally
void Shark::move() {
    _x -= _speed;
}

// Get the cuurent position of the shark
Position2D Shark::get_position() {
    return {_x, _y};
}

// Get the width of the shark
int Shark::get_width() {
    return _width;
}

// Get the height of the shark
int Shark::get_height() {
    return _height;
}

//Get the speed of the shark
int Shark::get_speed()  {
    return _speed;
}