#ifndef UTILS_H
#define UTILS_H

// Screen dimensions
#define WIDTH 84
#define HEIGHT 48

// Direction enumeration
enum Direction { N, NE, E, SE, S, SW, W, NW, CENTRE };

// 2D vector structure
struct Vector2D {
    float x;
    float y;
};

// Polar coordinate structure (magnitude and angle)
struct Polar {
    float mag;
    float angle;
};

// 2D position structure
struct Position2D {
    int x;
    int y;
};

// User input structure
struct UserInput {
    Direction d;  // Direction from joystick
};

// Function to display game over screen
inline void gameOverScreen(N5110 &lcd) {
    lcd.clear();
    lcd.printString("  GAME OVER", 0, 0);
    lcd.printString("Press button", 0, 1);
    lcd.printString("to restart", 0, 2);
    lcd.refresh();
}

#endif