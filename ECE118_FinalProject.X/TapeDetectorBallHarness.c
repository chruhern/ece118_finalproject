/*
 * File:   TapeDetectorBallHarness.c
 * Author: derri
 *
 * Created on May 21, 2024, 3:51 PM
 */


/*******************************************************************************
* #INCLUDES *
******************************************************************************/
// Internal PIC32
#include "xc.h"
#include <stdio.h>

// Libraries
#include <BOARD.h>
#include <RC_Servo.h>
#include <AD.h>
#include <LED.h>
#include <IO_Ports.h>

/*******************************************************************************
* PRIVATE TYPEDEFS *
******************************************************************************/
// Prototypes
int BALL_EXPMA(int value);

#define BALL_PIN AD_PORTV3 // AC pin definition

// Tape sensor for ball detection
#define BALL_DETECTED_THRESHOLD 200
#define BALL_NOT_DETECTED_THRESHOLD 100

#define BALL_DETECTED 1
#define BALL_NOT_DETECTED 0

unsigned int ball_status = BALL_NOT_DETECTED;
unsigned int prev_ball_status = 0;

// EMA Filter
#define ALPHA 0.09
/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/

//#define TAPE_SENSOR_HARNESS

#ifdef TAPE_SENSOR_HARNESS
    unsigned int EMA = 0;
#endif
    
#ifdef TAPE_SENSOR_HARNESS
int main(void) {
    
    printf("Starting up test harness for tape sensor detection. \r\n");
    printf("Warning, all test harnesses uses the same pin, which is V3. \r\n");
    
    // Initialization functions
    BOARD_Init(); // Board
    AD_Init(); // AD Pins
    
    // Setup
    AD_AddPins(BALL_PIN);
    
    // Main event loop
    while (1) {
        // Read the value from the ADC pin if needed
        if (AD_IsNewDataReady() == TRUE) {
            int ball_sensor_reading = BALL_EXPMA(AD_ReadADPin(BALL_PIN));
            unsigned int new_status;
            
            // Compare readings and trigger event if the value is different for hysteresis
            if (ball_sensor_reading >= BALL_DETECTED_THRESHOLD) {
                new_status = BALL_DETECTED;
            } else if (ball_sensor_reading <= BALL_NOT_DETECTED_THRESHOLD) {
                new_status = BALL_NOT_DETECTED;
            }
            
            // Print out message if status is different
//            if (new_status != tape_status) {
//                if (new_status == TAPE_HIGH) {
//                    printf("Tape sensor detected high. \r\n");
//                } else {
//                    printf("Tape sensor detected low. \r\n");
//                }
//                
//                printf("The tape sensor reading from the ADC is %d. \r\n", tape_sensor_reading);
//            }
            
            // Update previous status to the new status
            ball_status = new_status;
            
            // Test Display (remove when you have successfully gotten a pin reading)
            printf("The tape sensor reading from the ADC is %d. \r\n", ball_sensor_reading);
        }
    }
    
    return 0;
}
#endif

/*******************************************************************************
* PRIVATE FUNCTION IMPLEMENTATIONS *
******************************************************************************/
#ifdef TAPE_SENSOR_HARNESS
int BALL_EXPMA(int value) {
    EMA = (value * ALPHA)+((prev_ball_status)*(1 - ALPHA));
    prev_ball_status = EMA;
    return EMA;
}
#endif