#ifndef SHARK_ENGINE_H
#define SHARK_ENGINE_H

#include "N5110.h"
#include "mbed.h"
#include "Joystick.h"
#include "Submarine.h"
#include "Coin.h"
#include "Shark.h"
#include "Utils.h"
#include <vector>

#define NOTE_C4 262 //octave C

class SharkEngine {
public:
    //SharkEngine(); 
    SharkEngine();
    void init(); 
    void update(UserInput input, N5110 &lcd, PwmOut &buzzer); // Update game state based on user input
    void draw(N5110 &lcd); // Draw the elements onto the LCD.
    bool coinCollected();
    int getCollectedCoins()  {
        return collectedcoins;
    }
    //void playSound(int frequency); //Buzzer plays a note once every 600ms
    void playSound(PwmOut &buzzer); //Buzzer plays a note once every 600ms
    void GameOverSound(int frequency, PwmOut &buzzer);
    //void setBuzzer(PwmOut& buzzer); // Setter method for the buzzer
    
    

private:
    Submarine submarine; // Submarine game character
    std::vector<Shark*> sharks; // Vector to hold pointers to sharks
    std::vector<Coin*> coins; // Vector to hold pointers to coins
    int collectedcoins; //counter to count the number of coins collected
    int numberofcoins;
    //int frequency;
    //PwmOut &buzzer; // Reference to the buzzer object
   

  
};

#endif