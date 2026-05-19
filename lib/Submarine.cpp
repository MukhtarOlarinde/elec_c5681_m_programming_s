#include "Submarine.h"

Submarine::Submarine() :   _jumpHeight(20), _jumpSpeed(2), _state(NORMAL)

{ }

void Submarine::init(int x, int height, int width, int speed) {
    printf("Submarine: Init\n");
    _x = x;
    _y = HEIGHT - height - 5;
    _height = height;
    _width = width;
    _speed = speed;
    _size = 3;

    const int numSharks = 3;
    for (int i = 0; i < numSharks; ++i) 
    {
        int height = 5 + rand() % 10;
        int width = 2 + rand() % 4;
        int speed = 1 + rand() % 3;
        int y = rand() % (HEIGHT - height - 1);

        Shark* shark = new Shark(WIDTH - 1, y, width, height, speed);
        //creates a new shark to be in the shark vector
        _sharks.push_back(shark);//adds the new shark to the shark vector
    }
    //creates 3 sharks in the shark vector

}

void Submarine::draw(N5110 &lcd) {
    printf("Submarine: Draw\n");
    
    //int largerSize = _size * 2;
    
    //lcd.drawCircle(_x, _y, largerSize, FILL_BLACK);

     
    //lcd.drawCircle(_x, _y, _size, FILL_BLACK);

    const int submarinesprite[11][12]= {
	{ 0,0,0,0,0,0,0,1,1,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,1,1,0,1,1,0,0 },
	{ 0,0,0,0,1,0,0,0,0,0,1,0 },
	{ 1,1,0,1,0,0,0,0,0,0,0,1 },
	{ 0,1,1,1,0,0,1,0,1,0,0,1 },
	{ 1,1,0,1,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,1,0,0,0,0,0,1,0 },
	{ 0,0,0,0,0,1,1,0,1,1,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0 }
};

    lcd.drawSprite(_x, _y, 11, 12, (int*)submarinesprite);

    for (auto &shark : _sharks) {
        shark->draw(lcd);
    }
    //draws a shark in the sharks' vector 
}

void Submarine::update(UserInput input, N5110 &lcd) {
    printf("Submarine: Update\n");
    _speed = 2;// sets the speed of the submarine to be constant 2
    

    /*
    int newY = _y;//sets the new position of the submarine to be controlled by the user input.

    //uses the user's control of the joystick as an input to move the submarine's position
    if (input.d == N) { newY -= _speed; }
    else if (input.d == S) { newY += _speed; }
    //reduces speed if input is North, increases if it is South moving the sub up.
    if (newY < 1) { newY = 1; }
    if (newY > HEIGHT - _height - 1) { newY = HEIGHT - _height - 1; }
    //check if submarine is within the boundary.
    _y = newY;//replaces submarine with a new sub in a different position.


   
    for (auto &shark : _sharks) {
        shark->move();
    }
    //updates the position of the current shark on the lcd.

    draw(lcd);
    lcd.refresh();
    //updates the screen by drawing the submarine's and the shark's new position.
    
}*/

    int _originalY = _y; 
    // Store the original height before the jump
     switch (_state) 
     //The switch statement evaluates the current state of the submarine, _state, and 
     //executes the corresponding block of code based on its value.
     
     {
    case NORMAL:
            if (input.d == N) 
            //If the input direction (input.d) is N (indicating the user wants to jump), the state changes to JUMPING.
            _originalY = _y; // Store the original height before the jump
            _state = JUMPING;
        } else {
            int newY = _y;
            if (input.d == S) { newY += _speed; }
            if (newY < 1) { newY = 1; }
            if (newY > HEIGHT - _height - 1) { newY = HEIGHT - _height - 1; }
            _y = newY;
        }
        break;

    case JUMPING:
        _y -= _jumpSpeed;
        if (_y <= HEIGHT - _height - _jumpHeight) {
            _state = FALLING;
        }
        break;

    case FALLING:
        _y += _jumpSpeed;
        bool passedAllSharks = true;
        //A bool variable passedAllSharks is introduced to check if the submarine has passed all sharks.

        for (auto &shark : _sharks) {
            if (_y + _height > shark->get_position().y) {
                passedAllSharks = false;
                break;
            }
        }
        //checks if the submarine's bottom edge is still intersecting with any shark. 
        //If it is, passedAllSharks is set to false.

        if (passedAllSharks) {
            if (_y >= _originalY) {
                _y = _originalY;
                _state = NORMAL;
            }
        }
        //if the bool is true, he submarine's vertical position _y is incremented until it reaches _originalY, 
        //at which point the state changes back to NORMAL.
        break;
}

for (auto &shark : _sharks) {
    shark->move();
}

draw(lcd);
lcd.refresh();
      

Position2D Submarine::get_position() { 
    return {_x, _y}; 
    }

int Submarine::get_height() { 
    return _height; 
    }

int Submarine::get_width() { 
    return _width; 
    }

std::vector<Shark*>& Submarine::getSharks() {
    return _sharks;
}

// Get Submarine's speed
int Submarine::get_speed() {
    return _speed;
}

// Set Submarine's position
void Submarine::set_position(Position2D position) {
    _x = position.x;
    _y = position.y;
}