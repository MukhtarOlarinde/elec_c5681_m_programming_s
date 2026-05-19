#include "Coin.h"

Coin::Coin() {}

void Coin::init(int size, int screenWidth, int screenHeight, int sharkx, int sharky, int sharkWidth, 
int sharkHeight, int sharkSpeed) {
    _size = size;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    // Initialize coin position in front of the shark
   
    _position.x = sharkx - sharkWidth;//so the first coin appears just beyond the shark
    _position.y = sharky + sharkHeight / 2 - size / 2;
    _speed = sharkSpeed; //let coins move at the same rate as the sharks

    // Initialize coin position on the other side of the shark with 5 pixels of separation
    //try using this or that 
    //_position.x = sharkX + sharkWidth + 5;  // Adjusted by adding 5 pixels
    //_position.y = sharkY + sharkHeight / 2 - size / 2;
    //_speed = sharkSpeed; // Set coin speed to shark speed
}

void Coin::update() {
    // Move the coin to the left (follow the shark)
    
    _position.x -= _speed;
}

void Coin::draw(N5110 &lcd) {
  
    lcd.drawCircle(_position.x, _position.y, _size, FILL_BLACK);//to draw the coin
}

bool Coin::checkCollected(int submarineX, int submarineY, int submarineWidth, int submarineHeight) {
    // Check if the submarine collects the coin(same position as each other)
    if (_position.x < submarineX + submarineWidth &&
        _position.x + _size > submarineX &&
        _position.y < submarineY + submarineHeight &&
        _position.y + _size > submarineY) {
        return true;
    }
    return false;
}

Position2D Coin::get_position() {
    return _position;
}