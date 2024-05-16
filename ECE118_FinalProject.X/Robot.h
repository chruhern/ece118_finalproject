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
unsigned char Robot_GetTrackWireFL();
unsigned char Robot_GetTrackWireFR();

/**
 * @Function Robot_GetTapeXX(void)
 * @param None
 * @return Status of the tape detector wire, 1 if tape detected detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetTapeFL();
unsigned char Robot_GetTapeFR();
unsigned char Robot_GetTapeRL();
unsigned char Robot_GetTapeRR();

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

/**
 * @Function Robot_GetBeacon(void)
 * @param None
 * @return Status of the beacon, returns 1 if beacon is detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetBeacon();

/**
 * @Function Robot_GetPingDistance(void)
 * @param None
 * @return Distance in millimeters (or whatever the value the ping sensor returns)
 * @brief  To be used for object detection, such as the beacon.
 * @author Derrick Lai */
unsigned int Robot_GetPingDistance(); 

// Test, to be removed later
int Robot_GetTape();

