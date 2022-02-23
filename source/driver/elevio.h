#pragma once


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


void elevio_init(void);
/**
 * @brief Sets the motor direction of the elevator
 * 
 * @param dirn 
 */
void elevio_motorDirection(MotorDirection dirn);

/**
 * @brief Sets the lights on up and down on Floorpanel, and floors on elevator panel 
 * 
 * @param floor 
 * @param button [hall up is 0]
 * @param value 
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
 * @brief Turns on the floor lights on the floor panal 
 * 
 * @param floor The flor one wishes to turn on 
 */
void elevio_floorIndicator(int floor);

/**
 * @brief Turns on the door open light
 * 
 * @param value ture or false
 */
void elevio_doorOpenLamp(int value);

/**
 * @brief Turns on the elevator stoped lamp
 * 
 * @param value 
 */
void elevio_stopLamp(int value);

/**
 * @brief a function that cheks if a cirtan butten is pushed 
 * 
 * @param floor 
 * @param button 
 * @return int 
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief cheks where the elevator is, in relation to the floors.
 * 
 * @return int 
 */
int elevio_floorSensor(void);

/**
 * @brief cheks is stop buttoon is pushed
 * 
 * @return int 
 */
int elevio_stopButton(void);
int elevio_obstruction(void);

