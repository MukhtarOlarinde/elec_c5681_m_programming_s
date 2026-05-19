#ifndef SUBMARINE_H
#define SUBMARINE_H
#include "N5110.h"
#include "Utils.h"
#include "Joystick.h" 
#include "Shark.h"
#include <vector>

enum SubmarineState {NORMAL, JUMPING, FALLING};

class Submarine {
public:
    Submarine(); // Constructor
    void init(int x, int height, int width, int speed); // Initialize the submarine
    void update(UserInput input, N5110 &lcd); // Update submarine state based on user input
    void draw(N5110 &lcd); // Draw submarine and associated sharks on the LCD

    Position2D get_position(); // Get submarine's position
    int get_height(); // Get submarine's height
    int get_width(); // Get submarine's width
    int get_speed(); // Get submarine's speed
    void set_position(Position2D position); // Set submarine's position
    std::vector<Shark*>& getSharks(); // Get vector of shark pointers



    // Updates the submarine's position according to gravity and jump mechanics
    //void updatePosition();

    // Triggers the submarine jump when called
    //void jump();

    // Handles input from the joystick for jump control
    //void handleInput(float joystickY);

    // Returns the current vertical position of the submarine
    //float getPosition();

private:
    int _x; // X-coordinate of the submarine
    int _y; // Y-coordinate of the submarine
    int _height; // Height of the submarine
    int _width; // Width of the submarine
    int _speed; // Speed of the submarine
    int _size; // Size of the submarine (for drawing)
    std::vector<Shark*> _sharks; // Vector to hold pointers to sharks

    // int _x, _y, _height, _width, _speed, _size;
    SubmarineState _state; // State of the submarine
    int _jumpHeight; // Height of the submarine's jump
    int _jumpSpeed; // Speed of the submarine's jump

    float submarineY;    // Vertical position of the submarine
    float velocityY;     // Current vertical velocity of the submarine
    float gravity;       // Gravity value (pulls the submarine down)
    float jumpForce;     // Force applied when the submarine jumps
    bool isJumping;      // Flag to check if the submarine is already jumping
    const float groundLevel = 0.0;  // Minimum Y position (ground level)
    const float maxHeight = 20.0;   // Maximum Y position (jump limit)
    static int _originalY;  // Original Y-coordinate used for jump/fall handling

    
};
#endif