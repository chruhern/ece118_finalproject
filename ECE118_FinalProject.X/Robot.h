/* 
 * File:   Robot.h
 * Author: derri
 *
 * Created on May 15, 2024, 3:32 PMPORTY04_TRIS = PIN_INPUT;
 */

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define PROPELLER_COLLECT 0
#define PROPELLER_RELEASE 1

#define PIN_INPUT 1
#define PIN_OUTPUT 0

#define MOTOR_MAX 1000 // Max cycle for the motor (goes both ways, positive and negative)
#define PROPELLER_MAX 1000 // Max speed of the propeller

// Sensor statuses
#define TAPE_DETECTED 0
#define TAPE_NOT_DETECTED 1

#define BUMPER_PRESSED 1
#define BUMPER_RELEASED 0

#define BEACON_ON_SIGHT 1
#define BEACON_OFF_SIGHT 0

// ***** Calibration ***** //
// -- Straight Movement -- //
// Values that allow for maximum forward speed that maintains a straight line.
#define LEFT_FORWARD_MAX 1000
#define RIGHT_FORWARD_MAX 1000

// Values that allow for maximum reverse speed that maintains a straight line.
#define LEFT_REVERSE_MAX -1000
#define RIGHT_REVERSE_MAX -1000

// -- Turning -- //
// Timer value to allow for 90 degree turn.
#define TURN_90_LEFT_TICKS 500
#define TURN_90_RIGHT_TICKS 500

// Values that allow for a tank turn 90 degree left turn
#define MAX_LEFT_TURN_90_LEFT -1000
#define MAX_LEFT_TURN_90_RIGHT 1000

// Values that allow for a tank turn 90 degrees right turn
#define MAX_RIGHT_TURN_90_LEFT 1000
#define MAX_RIGHT_TURN_90_RIGHT -1000

// Buffer time to prevent momentum of wheels from affecting directions.
#define ROBOT_STOP_BUFFER_TICKS 2000
// ************************************** //
/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/
/**
 * @Function Robot_Init()
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Initializes the necessary ADC pins, IO digital pins, timers, and anything else needed for the robot to run.
 * @author Derrick Lai */
char Robot_Init();

/**
 * @Function Robot_SetLeftMotor(char motorSpeed)
 * @param newSpeed - A value between -1000 and 1000 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Derrick Lai */
char Robot_SetLeftMotor(int motorSpeed);

/**
 * @Function Robot_SetRightMotor(char motorSpeed)
 * @param newSpeed - A value between -1000 and 1000 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the right motor.
 * @author Derrick Lai */
char Robot_SetRightMotor(int motorSpeed);

/**
 * @Function Robot_SetPropllerMode(int propellerMode)
 * @param propellerMode - The mode (or direction of the propeller) to either collect or release the balls
 * @return SUCCESS or ERRORS
 * @brief  Allows for setting the direction of the motor that controls the propeller to either collect or release the balls
 * @author Derrick Lai */
char Robot_SetPropllerMode(int propellerMode);

/**
 * @Function Robot_GetTrackWireXX(void)
 * @param None
 * @return Status of the track wire, 1 if detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned int Robot_LevelGetTrackWireFL();
unsigned int Robot_LevelGetTrackWireFR();

/**
 * @Function Robot_GetTapeXX(void)
 * @param None
 * @return Status of the tape detector wire, 1 if tape detected detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned int Robot_GetTapeFL();
unsigned int Robot_GetTapeFR();
unsigned int Robot_GetTapeRL();
unsigned int Robot_GetTapeRR();

/**
 * @Function Robot_GetBumperXX(void)
 * @param None
 * @return Status of the bumper detector wire, 1 if bumper pressed, 0 otherwise
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetBumperFL();
unsigned char Robot_GetBumperFR();
unsigned char Robot_GetBumperRL();
unsigned char Robot_GetBumperRR();
unsigned char Robot_GetBumperFLO();
unsigned char Robot_GetBumperFRO();

/**
 * @Function Robot_GetBeacon(void)
 * @param None
 * @return Status of the beacon, returns 1 if beacon is detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned int Robot_GetBeacon();

/**
 * @Function Robot_GetPingDistance(void)
 * @param None
 * @return Distance in millimeters (or whatever the value the ping sensor returns)
 * @brief  To be used for object detection, such as the beacon.
 * @author Derrick Lai */
unsigned int Robot_GetPingDistance(); 

/**
 * @Function Robot_EXPMA(void)
 * @param value -> The most current ADC reading
 * @param prev_value -> The pointer to the previous ADC reading
 * @return An integer representing the newly filtered value
 * @brief  Used to smoothen data for the track wire detector.
 * @author Derrick Lai */
int Robot_EXPMA(int value, unsigned int *prev_value);


