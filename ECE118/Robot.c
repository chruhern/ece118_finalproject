/*
 * File:   Robot.c
 * Author: derri
 *
 * Created on May 15, 2024, 3:34 PM
 */


/*******************************************************************************
* #INCLUDES *
******************************************************************************/
// Internal PIC32
#include "xc.h"
#include <stdio.h>

// Libraries
#include <BOARD.h>
#include <AD.h>
#include <IO_Ports.h>
#include <pwm.h>
#include <LED.h>
#include <Robot.h>

/**
 * @Function Robot_Init()
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Initializes the necessary ADC pins, IO digital pins, timers, and anything else needed for the robot to run.
 * @author Derrick Lai */
char Robot_Init() {
    
    // Initializes all the different adc pins and bits needed to control it
    
    // Initialize all the necessary modules (I'm going to assume Board_Init() is active)
    AD_Init();
    LED_Init();
    PWM_Init();
    
    //  ***** INITIALIZE MOTOR PINS ***** //
    // Left drive motor
    PORTY04_TRIS = PIN_INPUT; // EnA PWM
    PORTZ05_TRIS = PIN_OUTPUT; // InA
    PORTZ06_TRIS = PIN_OUTPUT; // InB
    
    // Right drive motor
    PORTY03_TRIS = PIN_INPUT;
    PORTZ03_TRIS = PIN_OUTPUT;
    PORTZ04_TRIS = PIN_OUTPUT;
    
    // Propeller motor
    PORTY05_TRIS = PIN_INPUT;
    PORTZ07_TRIS = PIN_OUTPUT;
    PORTZ08_TRIS = PIN_OUTPUT;
    
    //  ***** INITIALIZE SENSOR PINS ***** //
    // Track wire detector (ADC is used for hysteresis, use V pins)
    AD_AddPins(AD_PORTV3);
    AD_AddPins(AD_PORTV4);
    
    // Tape detector (digital value, X pins, all set as inputs)
    PORTX03_TRIS = PIN_INPUT;
    PORTX04_TRIS = PIN_INPUT;
    PORTX05_TRIS = PIN_INPUT;
    PORTX06_TRIS = PIN_INPUT;
    
    // Bump switch detector (digital value, W pins, all set as inputs)
    PORTW03_TRIS = PIN_INPUT;
    PORTW04_TRIS = PIN_INPUT;
    PORTW05_TRIS = PIN_INPUT;
    PORTW06_TRIS = PIN_INPUT;
    
    // Beacon detector (digital value, but use Vpin, set as input)
    PORTV05_TRIS = PIN_INPUT;
    
    // Ping sensor (Initialize IC3)
    
    
    //  ***** INITIALIZE LEDs ***** //
    LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    // Perform a quick test to check if the lights have initialized, remove them later
    LED_SetBank(LED_BANK1, 0xF);
    LED_SetBank(LED_BANK2, 0xF);
    LED_SetBank(LED_BANK3, 0xF);
    
    // Return status
    return SUCCESS;
}

/**
 * @Function Robot_SetLeftMotor(char motorSpeed)
 * @param newSpeed - A value between -1000 and 1000 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Derrick Lai */
char Robot_SetLeftMotor(int motorSpeed) {
    
}

/**
 * @Function Robot_SetRightMotor(char motorSpeed)
 * @param newSpeed - A value between -1000 and 1000 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the right motor.
 * @author Derrick Lai */
char Robot_SetRightMotor(int motorSpeed) {
    
}

/**
 * @Function Robot_SetPropllerMode(int propellerMode)
 * @param propellerMode - The mode (or direction of the propeller) to either collect or release the balls
 * @return SUCCESS or ERRORS
 * @brief  Allows for setting the direction of the motor that controls the propeller to either collect or release the balls
 * @author Derrick Lai */
char Robot_SetPropllerMode(int propellerMode) {
    
}

/**
 * @Function Robot_GetTrackWireXX(void)
 * @param None
 * @return Status of the track wire, 1 if detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetTrackWireFL() {
    
}

unsigned char Robot_GetTrackWireFR() {
    
}

/**
 * @Function Robot_GetTapeXX(void)
 * @param None
 * @return Status of the tape detector wire, 1 if tape detected detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetTapeFL()  {
    
}

unsigned char Robot_GetTapeFR()  {
    
}

unsigned char Robot_GetTapeRL()  {
    
}

unsigned char Robot_GetTapeRR()  {
    
}


/**
 * @Function Robot_GetBumperXX(void)
 * @param None
 * @return Status of the bumper detector wire, 1 if bumper pressed, 0 otherwise
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetBumperFL()  {
    
}

unsigned char Robot_GetBumperFR()  {
    
}

unsigned char Robot_GetBumperRL()  {
    
}

unsigned char Robot_GetBumperRR()  {
    
}


/**
 * @Function Robot_GetBeacon(void)
 * @param None
 * @return Status of the beacon, returns 1 if beacon is detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetBeacon()  {
    
}

/**
 * @Function Robot_GetPingDistance(void)
 * @param None
 * @return Distance in millimeters (or whatever the value the ping sensor returns)
 * @brief  To be used for object detection, such as the beacon.
 * @author Derrick Lai */
unsigned int Robot_GetPingDistance()  {
    
}

// This is a test function for the event checker, to be removed later
int Robot_GetTape() {
    return PORTV03_BIT;
}
