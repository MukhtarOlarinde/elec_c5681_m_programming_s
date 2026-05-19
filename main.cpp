#include "mbed.h"
#include "N5110.h"
#include "SharkEngine.h"
#include "Joystick.h"
#include "Utils.h"

#define SUBMARINE_WIDTH 2
#define SUBMARINE_HEIGHT 8
#define SUBMARINE_SIZE 2
#define SUBMARINE_SPEED 3

///////////// objects ///////////////////
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn buttonA(BUTTON1);
PwmOut buzzer(PA_15); 

///////////// prototypes ///////////////
SharkEngine shark ;
void init();
void render();
void welcome();
void game_over();
UserInput get_input();

//void playSound(int frequency); //Buzzer plays a note once every 600ms

int main() {
    //SharkEngine shark(buzzer); // Pass buzzer object to SharkEngine constructor
    
    // Define buzzer pin
    //PwmOut buzzer(PA_15);
    init();      // initialise devices and objects
    welcome();   // waiting for the user to start 
    render();    // first draw the initial frame 
    int fps = 10;
    thread_sleep_for(1000/fps);  // and wait for one frame period - milliseconds
    
 

    while (true) {  // main game loop
        
        UserInput input = get_input();
        shark.update(input, lcd, buzzer);   // update the shark engine based on input    
        render();                  // draw frame on screen
        lcd.refresh();
        
        thread_sleep_for(1000/fps); // wait for one frame period - milliseconds
    }    

    game_over();
}

void init() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.5);
    joystick.init();
}

void render() {  // clear screen, re-draw and refresh
    lcd.clear();  
    shark.draw(lcd);
}

void welcome() { // splash screen
    lcd.printString(" Move Shark ! ",0,4);  
    lcd.printString("Press Nucleo",0,1);
    lcd.printString("Blue button",0,2);
    lcd.printString("To Start",0,3);
    lcd.refresh();

        while (buttonA.read() == 1)
        {
            ThisThread::sleep_for(100ms);
        }
}

/*
 void play_note(int frequency){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);    //set the period of the pwm signal (in us)
    buzzer.pulsewidth_us(1*buzzer.read_period_us()/2);           
    ThisThread::sleep_for(500ms);     
    buzzer.pulsewidth_us(0); 
    ThisThread::sleep_for(100ms); 
    }
    */

// void game_over() { // splash screen 
//     while (1) {
//         lcd.clear();
//         lcd.printString("  Game Over ",0,2);  
//         lcd.refresh();
//         ThisThread::sleep_for(250ms);
//         lcd.clear();
//         lcd.refresh();
//         ThisThread::sleep_for(250ms);
//     }
// }


UserInput get_input() {
    AnalogIn joyX(PC_1);
    AnalogIn joyY(PC_0);
    
    float x = joyX.read();
    float y = joyY.read();
    
    UserInput input;

    float threshold = 0.1;

    if (y > 0.5 + threshold) {
        input.d = N; // Move Sonic up
    } else if (y < 0.5 - threshold) {
        input.d = S; // Move Sonic down
    } else {
        input.d = CENTRE; // No movement
    }

    return input;
}


/*void playSound(int frequency) {
    // Set the buzzer frequency and play the note
    buzzer.period_us((float)1000000.0f / (float)frequency);
    buzzer.pulsewidth_us(1 * buzzer.read_period_us() / 2);
    buzzer.pulsewidth_us(0);
    ThisThread::sleep_for(100ms);
}
*/