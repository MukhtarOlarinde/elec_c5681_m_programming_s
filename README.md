# ELEC C5681 Microcontroller Programming - Shark Game

This is a Keil uVision embedded systems project for an interactive Shark-Dodging game implemented on an ARM Cortex-M microcontroller board.

## Project Overview

A submarine must navigate through an underwater environment, jumping over incoming sharks to collect coins and avoid collisions. The game features:

- **Submarine Character**: Controllable via joystick with jump mechanics
- **Shark Enemies**: Randomly spawned obstacles moving across the screen
- **Coin Collection**: Collectible items that follow shark movement patterns
- **LCD Display**: N5110 LCD for game rendering
- **Sound Effects**: Buzzer feedback for coin collection and game over
- **Scoring System**: Track collected coins throughout gameplay

## Project Structure

### Main Files
- `main.cpp` - Entry point and main game loop
- `lib/` - Library components

### Core Classes

#### Submarine (`lib/Submarine.*`)
Manages the player character with jump mechanics:
- States: NORMAL, JUMPING, FALLING
- Joystick-controlled vertical movement
- Collision detection with sharks

#### Shark (`lib/Shark.*`)
Represents enemy obstacles:
- Horizontal movement across screen
- Custom sprite rendering
- Position and collision boundary tracking

#### Coin (`lib/Coin.*`)
Collectible items that follow shark patterns:
- Positioned relative to shark movement
- Collision detection with submarine
- Spawning management

#### SharkEngine (`lib/SharkEngine.*`)
Main game controller:
- Initializes game state
- Manages game updates and rendering
- Handles collision logic
- Controls buzzer audio feedback
- Score tracking

#### Joystick (`lib/Joystick.*`)
Analog joystick input handler:
- Calibration and centering
- Direction detection (8 cardinal directions)
- Mapped coordinate transformation

#### Paddle & Ball (`lib/Paddle.*`, `lib/Ball.*`)
Legacy Pong game components (included for reference)

### Utilities
- `lib/Utils.h` - Common structures and constants
  - Screen dimensions
  - Direction enumeration
  - Vector and position structures

## Hardware Setup

### Required Components
- ARM Cortex-M Nucleo Board (e.g., Nucleo-F401RE)
- N5110 LCD Display
- Analog Joystick
- Buzzer/Speaker
- Push Button

### Pin Configuration

**LCD (N5110):**
- CLK: PC_7
- MOSI: PA_9
- DC: PB_10
- CE: PB_5
- RST: PB_3
- BL: PA_10

**Joystick:**
- Vertical: PC_1
- Horizontal: PC_0

**Buzzer:**
- PA_15 (PWM output)

**Button:**
- BUTTON1 (Blue button on Nucleo board)

## Building and Compilation

This project uses the Mbed OS framework and Keil uVision IDE:

1. Import the project into Keil uVision
2. Configure the target device
3. Build the project
4. Flash to the microcontroller board

## Game Controls

- **Joystick Up (N)**: Make submarine jump
- **Joystick Down (S)**: Move submarine down
- **Center Position**: Keep submarine at current height
- **Blue Button**: Start game / Restart after game over

## Gameplay

1. Press the blue button to start
2. Use the joystick to control the submarine's vertical position
3. Jump over incoming sharks
4. Collect coins for points (every 2 coins = 1 point)
5. Avoid shark collisions - game over if hit
6. Game automatically restarts after game over

## Game Features

### Audio Feedback
- Coin collection: Beep sound (2000 Hz for 20ms)
- Game Over: Lower frequency sound (262 Hz C4 note)

### Graphics
- Custom sprite rendering for submarine and sharks
- N5110 LCD display (84x48 pixels)
- Dynamic scoring display

### Game Mechanics
- Sharks spawn at the right side, move left
- Coins positioned relative to shark trajectories
- Submarine jumping allows obstacle avoidance
- Dynamic difficulty: Sharks speed increases with new spawns

## Future Enhancements

- Difficulty levels
- High score storage in EEPROM
- Multiple lives system
- Power-ups and special abilities
- Touch controls alternative input

## Author

Developed for ELEC C5681 Course
University of Leeds

## License

This project is for educational purposes.
