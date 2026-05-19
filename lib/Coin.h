#ifndef COIN_H
#define COIN_H

#include "N5110.h"
#include "Utils.h"

class Coin {
public:
    Coin(); 
    void init(int size, int screenWidth, int screenHeight, int sharkx, int sharky, int sharkWidth, int sharkHeight, int sharkSpeed); // Initialize coin
    //void init(int size, int screenWidth, int screenHeight, int sharkX, int sharkY, int sharkWidth, int sharkHeight); 
    void draw(N5110 &lcd); // Draw coin on LCD
    void update(); // Update coin position
    bool checkCollected(int submarineX, int submarineY, int submarineWidth, int submarineHeight);
     // Check if coin is collected
    Position2D get_position(); // Get coin's position

private:
    
    int _screenWidth; // Screen width
    int _screenHeight; // Screen height
    int _size; // Size of the coin
    int _speed; // the speed of the coin
    Position2D _position; // Position of the coin
};

#endif