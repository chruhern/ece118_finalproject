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
// Motors
#define LEFT_MOTOR_EN PWM_PORTY04
#define LEFT_MOTOR_INA_PIN_MODE PORTZ05_TRIS
#define LEFT_MOTOR_INB_PIN_MODE PORTZ06_TRIS
#define LEFT_MOTOR_INA PORTZ05_LAT
#define LEFT_MOTOR_INB PORTZ06_LAT

#define RIGHT_MOTOR_EN PWM_PORTY10
#define RIGHT_MOTOR_INA_PIN_MODE PORTZ03_TRIS
#define RIGHT_MOTOR_INB_PIN_MODE PORTZ04_TRIS
#define RIGHT_MOTOR_INA PORTZ03_LAT
#define RIGHT_MOTOR_INB PORTZ04_LAT

#define PROPELLER_MOTOR_EN PWM_PORTY12
#define PROPELLER_MOTOR_INA_PIN_MODE PORTZ07_TRIS
#define PROPELLER_MOTOR_INB_PIN_MODE PORTZ08_TRIS
#define PROPELLER_MOTOR_INA PORTZ07_LAT
#define PROPELLER_MOTOR_INB PORTZ08_LAT

// -- Sensors -- \\
// Sensor Pin Modes
#define BUMPER_FRONT_LEFT_PIN_MODE PORTX03_TRIS
#define BUMPER_FRONT_RIGHT_PIN_MODE PORTX04_TRIS
#define BUMPER_REAR_LEFT_PIN_MODE PORTX05_TRIS
#define BUMPER_REAR_RIGHT_PIN_MODE PORTX06_TRIS

#define TAPE_FRONT_LEFT_PIN AD_PORTW3
#define TAPE_FRONT_RIGHT_PIN AD_PORTW4
#define TAPE_REAR_LEFT_PIN AD_PORTW5
#define TAPE_REAR_RIGHT_PIN AD_PORTW6

#define TRACK_WIRE_LEFT_PIN AD_PORTV3
#define TRACK_WIRE_RIGHT_PIN AD_PORTV4

#define BEACON_PIN_MODE PORTV05_TRIS

// Sensor Statuses
#define BUMPER_FRONT_LEFT PORTX03_BIT
#define BUMPER_FRONT_RIGHT PORTX04_BIT
#define BUMPER_REAR_LEFT PORTX05_BIT
#define BUMPER_REAR_RIGHT PORTX06_BIT

#define BEACON_STATUS PORTV05_BIT
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
    PWM_AddPins(LEFT_MOTOR_EN); // EnA PWM, Y04 (allowed PWM pins)
    LEFT_MOTOR_INA_PIN_MODE = PIN_OUTPUT; // InA
    LEFT_MOTOR_INB_PIN_MODE = PIN_OUTPUT; // InB
    
    // Initial values for forward drive
    LEFT_MOTOR_INA = 1;
    LEFT_MOTOR_INB = 0;
    
    // Right drive motor
    PWM_AddPins(RIGHT_MOTOR_EN); // EnB PWM, Y10
    RIGHT_MOTOR_INA_PIN_MODE = PIN_OUTPUT; // InA
    RIGHT_MOTOR_INB_PIN_MODE = PIN_OUTPUT; // InB
    
    // Initial values for forward drive
    RIGHT_MOTOR_INA = 1; 
    RIGHT_MOTOR_INB = 0;
    
    // Propeller motor
    PWM_AddPins(PROPELLER_MOTOR_EN); // EnA PWM, Y12
    PROPELLER_MOTOR_INA_PIN_MODE = PIN_OUTPUT; // InA
    PROPELLER_MOTOR_INB_PIN_MODE = PIN_OUTPUT; // InB
    
    // Initial values for forward drive
    PROPELLER_MOTOR_INA = 1;
    PROPELLER_MOTOR_INB = 0;
    
    //  ***** INITIALIZE SENSOR PINS ***** //
    // Track wire detector (ADC is used for hysteresis, use V pins)
    AD_AddPins(TRACK_WIRE_LEFT_PIN);
    AD_AddPins(TRACK_WIRE_RIGHT_PIN);
    
    // Tape detector (adc value)
    AD_AddPins(TAPE_FRONT_LEFT_PIN);
    AD_AddPins(TAPE_FRONT_RIGHT_PIN);
    AD_AddPins(TAPE_REAR_LEFT_PIN);
    AD_AddPins(TAPE_REAR_RIGHT_PIN);
    
    // Bump switch detector (digital value, W pins, all set as inputs)
    BUMPER_FRONT_LEFT_PIN_MODE = PIN_INPUT;
    BUMPER_FRONT_RIGHT_PIN_MODE = PIN_INPUT;
    BUMPER_REAR_LEFT_PIN_MODE = PIN_INPUT;
    BUMPER_REAR_RIGHT_PIN_MODE = PIN_INPUT;
    
    // Beacon detector (digital value, but use Vpin, set as input)
    BEACON_PIN_MODE = PIN_INPUT;
    
    // Ping sensor (Initialize IC3)
    
    
    //  ***** INITIALIZE LEDs ***** //
    LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    // Perform a quick test to check if the lights have initialized, remove them later
//    LED_SetBank(LED_BANK1, 0xF);
//    LED_SetBank(LED_BANK2, 0xF);
//    LED_SetBank(LED_BANK3, 0xF);
    
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
    LEFT_MOTOR_INA = isForward ? 1 : 0;
    LEFT_MOTOR_INB = isForward ? 0 : 1;
    
    //printf("Setting pin 5 and 6 to the following, Z05: %d, Z06: %d. \r\n", PORTZ05_LAT, PORTZ06_LAT);
    
    // Obtain the absolute speed
    unsigned int abs_speed = isForward ? actualSpeed : (unsigned int)-actualSpeed;
    
    //printf("The abs speed is %d and %d \r\n", abs_speed, actualSpeed);
    // Set the duty cycle, which its return value will be success or error
    char motor_status = PWM_SetDutyCycle(LEFT_MOTOR_EN, abs_speed);
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
    RIGHT_MOTOR_INA = isForward ? 1 : 0;
    RIGHT_MOTOR_INB = isForward ? 0 : 1;
    
    //printf("Setting pin 3 and 4 to the following, Z03: %d, Z04: %d. \r\n", RIGHT_MOTOR_INA, RIGHT_MOTOR_INB);
    
    // Obtain the absolute speed
    unsigned int abs_speed = isForward ? actualSpeed : (unsigned int)-actualSpeed;
    //printf("The abs speed is %d and %d \r\n", abs_speed, actualSpeed);
    
    // Set the duty cycle, which its return value will be success or error
    char motor_status = PWM_SetDutyCycle(RIGHT_MOTOR_EN, abs_speed);
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
    
    // Set the direction of the motor based on the mode
    if (propellerMode == PROPELLER_COLLECT) {
        PROPELLER_MOTOR_INA = 1;
        PROPELLER_MOTOR_INB = 0;
    } else {
        PROPELLER_MOTOR_INA = 0;
        PROPELLER_MOTOR_INB = 1;
    }
    
    // Set the pwm
    char motor_status = PWM_SetDutyCycle(PROPELLER_MOTOR_EN, PROPELLER_MAX);
    if (motor_status == SUCCESS) {
        printf("Setting the propeller... \r\n");
        return SUCCESS;
    } else {
        printf("Failed to set propeller... \r\n");
        return ERROR;
    }
    
}

/**
 * @Function Robot_GetTrackWireXX(void)
 * @param None
 * @return Returns the adc value of the track wire.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned int Robot_LevelGetTrackWireFL() {
    return AD_ReadADPin(TRACK_WIRE_LEFT_PIN);
}

unsigned int Robot_LevelGetTrackWireFR() {
    return AD_ReadADPin(TRACK_WIRE_RIGHT_PIN);
}

/**
 * @Function Robot_GetTapeXX(void)
 * @param None
 * @return Status of the tape detector wire, 1 if tape detected detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned int Robot_GetTapeFL()  {
    return AD_ReadADPin(TAPE_FRONT_LEFT_PIN);
}

unsigned int Robot_GetTapeFR()  {
    return AD_ReadADPin(TAPE_FRONT_RIGHT_PIN);
}

unsigned int Robot_GetTapeRL()  {
    return AD_ReadADPin(TAPE_REAR_LEFT_PIN);
}

unsigned int Robot_GetTapeRR()  {
    return AD_ReadADPin(TAPE_REAR_RIGHT_PIN);
}


/**
 * @Function Robot_GetBumperXX(void)
 * @param None
 * @return Status of the bumper detector wire, 1 if bumper pressed, 0 otherwise
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetBumperFL()  {
    return BUMPER_FRONT_LEFT;
}

unsigned char Robot_GetBumperFR()  {
    return BUMPER_FRONT_RIGHT;
}

unsigned char Robot_GetBumperRL()  {
    return BUMPER_REAR_LEFT;
}

unsigned char Robot_GetBumperRR()  {
    return BUMPER_REAR_RIGHT;
}


/**
 * @Function Robot_GetBeacon(void)
 * @param None
 * @return Status of the beacon, returns 1 if beacon is detected, 0 otherwise.
 * @brief  To be used for event checker, reads from ADC pin to check if track wire detects anything. 
 * F -> Front, L -> Left, R -> Right or Rear
 * @author Derrick Lai */
unsigned char Robot_GetBeacon()  {
    return BEACON_STATUS;
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
//#define ROBOT_HARNESS

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
    
    // Add lights (Robot should have already done that)
    LED_AddBanks(LED_BANK1);
    
    // Main event loop
    // TEST CASE 1: LEFT AND RIGHT MOTORS ==================================================
//    while (1) {
//        
//        // If the time passes the switch time, reverse direction.
//        if (bot_curr_time >= bot_switch_time) {
//            
//            // Reverse direction
//            bot_curr_direction = -bot_curr_direction;
//            
//            // Run motors
//            int robot_speed = bot_speed * bot_curr_direction;
//            printf("Bot speed is %d. \r\n", robot_speed);
//            Robot_SetLeftMotor(robot_speed); // bot_speed * bot_curr_direction
//            Robot_SetRightMotor(robot_speed);
//            
//            // Reset time
//            bot_curr_time = 0;
//        }
//        
//        // Increment time
//        bot_curr_time++;
//    }
    //==================================================
    
    // Sensor Test ==================================================
    
    int prev_status = 0;
    int low = 40;
    int high = 300;
    while (1) {
        unsigned int tape_fl_status = Robot_GetTapeFL();
//        int tape_fr_status = Robot_GetTapeFR();
//        int tape_rl_status = Robot_GetTapeRL();
//        int tape_rr_status = Robot_GetTapeRR();
        
        int new_status;
        if (tape_fl_status > high) {
            new_status = 1;
        } else if (tape_fl_status < low) {
            new_status = 0;
        }
        
        if (new_status != prev_status) {
            if (new_status == 1) {
                printf("Tape detected \r\n");
                LED_SetBank(LED_BANK1, 0xF);
            } else {
                printf("Tape not detected \r\n");
                LED_SetBank(LED_BANK1, 0x0);
            }
        }
        //printf("Adc is %d \r\n", tape_fl_status);
        
        // Update status
        prev_status = new_status;
        
        
    }
    return (SUCCESS);
}
#endif