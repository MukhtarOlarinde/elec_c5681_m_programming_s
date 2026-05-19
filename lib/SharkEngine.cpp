
#include "SharkEngine.h"

//PwmOut buzzer(PA_15); 
// Define buzzer pin
//PwmOut buzzer(PA_15);  // Example pin, replace with the actual pin connected to the buzzer
//SharkEngine shark(buzzer); // Pass buzzer object to SharkEngine constructor

// Constructor
//SharkEngine::SharkEngine(PwmOut& buzzer) : buzzer(buzzer)
SharkEngine::SharkEngine() :  collectedcoins(0), numberofcoins(0)
{
    init();//to put submarine at the bottom of the screen
    
}

// Initialize game
void SharkEngine::init() {
    // Initialize submarine
    submarine.init(10, 8, 8, 2);

    // Eliminate existing sharks from the vector and screen
    for (auto &shark : sharks) {
    delete shark; // remove the shark from the screen
    }
    sharks.clear(); // remove the shark from the sharks vector

    // Remove existing coins
    for (auto &coin : coins) {
    delete coin; // remove the coins from the screen
    }
    coins.clear(); // remove the coins from the coin vector

    
    int height = 10;// set a fixed height for sharks
    const int minSharks = 3; // set the minimum number of sharks we want on the screen initially





    

    // Loop to create initial sharks
    for (int i = 0; i < minSharks; ++i) {
        // Fixed width and speed for simplicity
        int width = 5;
        int speed = 1;
        
        // Create shark object and add to vector
        // Sharks start at the bottom of the screen
        int y = HEIGHT - height - 1;
        Shark* shark = new Shark(WIDTH - 1, y, width, height, speed);
        sharks.push_back(shark);

        // Initialize coins in front of each shark
        for (int j = 0; j < 6; ++j) { // Create 6 coins for each shark
            Coin* coin = new Coin();
            //coin->init(2, WIDTH, HEIGHT, shark->get_pos().x - 12, shark->get_pos().y, shark->get_width(), shark->get_height(), shark->get_speed());
            coin->init(2, WIDTH, HEIGHT, shark->get_position().x - (7 + j * 6), 
            shark->get_position().y, shark->get_width(), shark->get_height(), shark->get_speed());
            //the first coin has a 7 pixel offset from the shark, the next coin has a 13 pixel offset, 
            //the one after that has a 19 pixel offset
            coins.push_back(coin);
        }
      // Initialize coins behind each shark
        //for (int k = 0; k < 3; ++k) {
          //  Coin* coin = new Coin();
            //coin->init(2, WIDTH, HEIGHT, shark->get_pos().x + shark->get_width() + (24 + k * 6), shark->get_pos().y, shark->get_width(), shark->get_height(), shark->get_speed());
            //coins.push_back(coin);
        //}
    }
}

// Update game state
void SharkEngine::update(UserInput input, N5110 &lcd,  PwmOut &buzzer) {

    submarine.update(input, lcd);

    bool gameOver = false;

    // Update submarine's vertical position based on user input

    /*
    int newY = submarine.get_position().y;
    if (input.d == N) { newY -= submarine.get_speed(); }
    else if (input.d == S) { newY += submarine.get_speed(); }
    // Keep submarine within screen boundaries
    if (newY < 1) { newY = 1; }
    if (newY > HEIGHT - submarine.get_height() - 1) { newY = HEIGHT - submarine.get_height() - 1; }

    submarine.set_position({submarine.get_position().x, newY});




    bool gameOver = false; // Flag to indicate game over

    */


    // Move sharks and check for collision with sharks
    for (auto it = sharks.begin(); it != sharks.end();) {
        (*it)->move();

        Position2D submarinePosition = submarine.get_position();
        //stores subs current position
        if ((*it)->get_position().x <= 0)
        //checks if the shark has left the screen 
        {
            delete *it; //Removes the shark from the screen
            it = sharks.erase(it); // Remove the shark from the it vector so it can point to the next shark
        }
            else if (submarinePosition.x < (*it)->get_position().x + (*it)->get_width() &&
            submarinePosition.x + submarine.get_width() > (*it)->get_position().x &&
            submarinePosition.y < (*it)->get_position().y + (*it)->get_height() &&
            submarinePosition.y + submarine.get_height() > (*it)->get_position().y) 

        //checks if the shark has hit the submarine.
        //checks if sub's left is to the right of the sharks left
        //checks if sub's right is to the left of the sharks right
        //checks if sub's bottom is above or below the shark
            {
            printf("Shark hit the submarine!\n");
            gameOver = true; // Set game over flag
            break; // Exit the loop since game over
        } 
            else {
            ++it; // Move to the next shark
        }
    }

    // Update and draw coins
    for (auto it = coins.begin(); it != coins.end();) {
        (*it)->update();
        //to update the current coin object by moving it horizontally
        if ((*it)->checkCollected(submarine.get_position().x, submarine.get_position().y, 
            submarine.get_width(), submarine.get_height())) 
            //checks if the coin has been collected by the submarine
            {
            delete *it; // remove the coin from the screen
            collectedcoins++ ;  //increment the counter
            numberofcoins = collectedcoins / 2;
            //collectedcoins = collectedcoins -1;
            //buzzer.pulsewidth_us(0); 
            //play_note(1000); // Activate the buzzer with a frequency of 1000 Hz when a coin is collected
            //playSound(NOTE_C4, buzzer);
            //playSound(100);
            //printf("Buzzer sounds\n");
            playSound(buzzer); // Play the beep-like sound when a coin is collected
            
            it = coins.erase(it); // Remove the coin from the vector
            }
            else if((*it)->get_position().x <= 0)
            //checks if coin has reace=hed end of the screen
            {
            delete *it; // remove the coin from the screen
            it = coins.erase(it); // Remove the coin from the vector

            }

            else{
            (*it)->draw(lcd); // Draw the coin on the LCD
            ++it; // Move to the next coin
        }
    }

    // Generate new sharks to maintain a count of at least 3
    while (sharks.size() < 3) {
        int height = 10;
        int width = 5;
        int speed = 2;
        int y = HEIGHT - height - 1;
        Shark* shark = new Shark(WIDTH - 1, y, width, height, speed);
        sharks.push_back(shark);//puts new shark into the shark vector

        // Initialize coins for each new shark
        for (int j = 0; j < 4; ++j) { // Create 4 coins behind each new shark
            Coin* coin = new Coin();
            //coin->init(2, WIDTH, HEIGHT, shark->get_pos().x - 12, shark->get_pos().y, shark->get_width(), shark->get_height(), shark->get_speed());
            coin->init(2, WIDTH, HEIGHT, shark->get_position().x - (5 + j * 6), shark->get_position().y, 
            shark->get_width(), shark->get_height(), shark->get_speed());
            //the first coin after the first set has a 5 pixel offset from the shark, 
            //the next coin has a 11 pixel offset.
            coins.push_back(coin);
            //to put the new coins back into the coins vector
        }
    
     for (int j = 0; j < 3; ++j) { // Create 3 coins in front of each new shark
            Coin* coin = new Coin();
            
            coin->init(2, WIDTH, HEIGHT, shark->get_position().x + shark->get_width() + (24 + j * 6), 
            shark->get_position().y, shark->get_width(), shark->get_height(), shark->get_speed());
            //the first coin after the first set has a 5 pixel offset from the shark, 
            //the next coin has a 11 pixel offset.
            coins.push_back(coin);
            //to put the new coins back into the coins vector
        }
    }


    if (gameOver) {
        lcd.clear();
        GameOverSound(NOTE_C4, buzzer);
        lcd.printString("Game Over", 0, 2);
        lcd.refresh();
        ThisThread::sleep_for(2000ms); // Wait for 2 seconds
        init(); // Reset the game
        collectedcoins = 0; // Reset collected coins counter
        numberofcoins = 0; // Reset the counter to 0

        gameOverScreen(lcd);
    }
}

// Draw game elements
void SharkEngine::draw(N5110 &lcd) {
    submarine.draw(lcd);
    for (auto &shark : sharks) {
    shark->draw(lcd);
    }
    for (auto &coin : coins) {
    coin->draw(lcd);
    }

    // Display collected coins counter at the top right corner
    char buffer[10] = {0};
    sprintf(buffer, "%d", numberofcoins);
    lcd.printString(buffer, 60, 0);
}




// Play sound with specified frequency

// Play a brief beep-like sound
void SharkEngine::playSound(PwmOut &buzzer) {
    buzzer.period(1.0 / 2000);  // Set a high frequency for a brief beep-like sound
    buzzer.write(0.5);          // Set duty cycle to 50%
    ThisThread::sleep_for(20ms);  // Keep the sound on for 100 milliseconds
    buzzer.write(0.0);          // Turn off the buzzer
}

void SharkEngine::GameOverSound(int frequency, PwmOut &buzzer) 
{ // Set the buzzer frequency and play the note 
buzzer.period_us((float)1000000.0f / (float)frequency); 
buzzer.pulsewidth_us(1 * buzzer.read_period_us() / 2); 
buzzer.write(0.5);          // Set duty cycle to 50%
ThisThread::sleep_for(100ms);
printf("Buzzer sounds\n");
buzzer.write(0.0);          // Turn off the buzzer
}