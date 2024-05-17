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

/*******************************************************************************
* #DEFINES *
******************************************************************************/
#define LEFT_MOTOR_EN PWM_PORTY04
#define RIGHT_MOTOR_EN PWM_PORTY10
#define PROPELLER_MOTOR_EN PWM_PORTY12

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
    PWM_AddPins(PWM_PORTY04); // EnA PWM, Y04 (allowed PWM pins)
    PORTZ05_TRIS = PIN_OUTPUT; // InA
    PORTZ06_TRIS = PIN_OUTPUT; // InB
    
    // Initial values for forward drive
    PORTZ05_LAT = 1;
    PORTZ06_LAT = 0;
    
    // Right drive motor
    PWM_AddPins(PWM_PORTY10); // EnB PWM, Y10
    PORTZ03_TRIS = PIN_OUTPUT; // InA
    PORTZ04_TRIS = PIN_OUTPUT; // InB
    
    // Initial values for forward drive
    PORTZ03_LAT = 1; 
    PORTZ04_LAT = 0;
    
    // Propeller motor
    PWM_AddPins(PWM_PORTY12); // EnA PWM, Y12
    PORTZ07_TRIS = PIN_OUTPUT; // InA
    PORTZ08_TRIS = PIN_OUTPUT; // InB
    
    // Initial values for forward drive
    PORTZ07_LAT = 1;
    PORTZ08_LAT = 0;
    
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
    
    // If the given speed is greater or less than the maximum and minimum allowed thresholds, then clamp it down.
    int actualSpeed;
    if (motorSpeed > MOTOR_MAX) {
        actualSpeed = motorSpeed;
    } else if (motorSpeed < -MOTOR_MAX) {
        actualSpeed = -motorSpeed;
    } else {
        actualSpeed = motorSpeed;
    }
    
    // Based on the speed, set the direction
    int isForward = (actualSpeed > 0);
    PORTZ05_LAT = isForward ? 1 : 0;
    PORTZ06_LAT = isForward ? 0 : 1;
    
    //printf("Setting pin 5 and 6 to the following, Z05: %d, Z06: %d. \r\n", PORTZ05_LAT, PORTZ06_LAT);
    
    // Obtain the absolute speed
    unsigned int abs_speed = isForward ? actualSpeed : (unsigned int)-actualSpeed;
    
    //printf("The abs speed is %d and %d \r\n", abs_speed, actualSpeed);
    // Set the duty cycle, which its return value will be success or error
    char motor_status = PWM_SetDutyCycle(PWM_PORTY04, abs_speed);
    if (motor_status) {
        //printf("Setting PWM of the left motor... \r\n");
        return SUCCESS;
    } else {
        printf("Failed to set left motor... \r\n");
        return ERROR;
    }
    
}

/**
 * @Function Robot_SetRightMotor(char motorSpeed)
 * @param newSpeed - A value between -1000 and 1000 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the right motor.
 * @author Derrick Lai */
char Robot_SetRightMotor(int motorSpeed) {
    
    // If the given speed is greater or less than the maximum and minimum allowed thresholds, then clamp it down.
    int actualSpeed;
    if (motorSpeed > MOTOR_MAX) {
        actualSpeed = motorSpeed;
    } else if (motorSpeed < -MOTOR_MAX) {
        actualSpeed = -motorSpeed;
    } else {
        actualSpeed = motorSpeed;
    }
    
    // Based on the speed, set the direction
    int isForward = (actualSpeed > 0);
    PORTZ03_LAT = isForward ? 1 : 0;
    PORTZ04_LAT = isForward ? 0 : 1;
    
    //printf("Setting pin 3 and 4 to the following, Z03: %d, Z04: %d. \r\n", PORTZ03_LAT, PORTZ04_LAT);
    
    // Obtain the absolute speed
    unsigned int abs_speed = isForward ? actualSpeed : (unsigned int)-actualSpeed;
    //printf("The abs speed is %d and %d \r\n", abs_speed, actualSpeed);
    
    // Set the duty cycle, which its return value will be success or error
    char motor_status = PWM_SetDutyCycle(PWM_PORTY10, abs_speed);
    if (motor_status) {
        //printf("Setting PWM of the right motor... \r\n");
        return SUCCESS;
    } else {
        printf("Failed to set right motor... \r\n");
        return ERROR;
    }
    
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


// ***** TEST HARNESS ***** //
// Remember to include the TemplateES_Main.c file once you finished your test harness.
// This harness uses blocking code, shocking...
#define ROBOT_HARNESS

#ifdef ROBOT_HARNESS
const unsigned int bot_switch_time = 5000000;
unsigned int bot_curr_time = bot_switch_time;
int bot_curr_direction = 1; // 1 is forward, -1 is backward
int bot_speed = 250;
int main() {
    
    printf("Running the test harness for the robot. \r\n");
    // Initialize the robot
    BOARD_Init();
    Robot_Init();
    
    // Main event loop
    while (1) {
        
        // If the time passes the switch time, reverse direction.
        if (bot_curr_time >= bot_switch_time) {
            
            // Reverse direction
            bot_curr_direction = -bot_curr_direction;
            
            // Run motors
            int robot_speed = bot_speed * bot_curr_direction;
            printf("Bot speed is %d. \r\n", robot_speed);
            Robot_SetLeftMotor(robot_speed); // bot_speed * bot_curr_direction
            Robot_SetRightMotor(robot_speed);
            
            // Reset time
            bot_curr_time = 0;
        }
        
        // Increment time
        bot_curr_time++;
    }
    
    return (SUCCESS);
}
#endif