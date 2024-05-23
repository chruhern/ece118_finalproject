 /*
 * File:   TapeDetectorHarness.c
 * Author: derri
 *
 * Created on May 10, 2024, 1:49 PM
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
int EXPMA(int value);

#define TAPE_PIN AD_PORTW4 // AC pin definition

// Tape sensor threshold values (experimentally determined)
#define TAPE_HIGH_THRESHOLD 500
#define TAPE_LOW_THRESHOLD 50

#define TAPE_HIGH 1
#define TAPE_LOW 0

unsigned int tape_status = TAPE_LOW;
unsigned int prev_tape_reading = 0;

// EMA Filter
#define ALPHA 0.09
/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/

#define TAPE_SENSOR_HARNESS

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
    AD_AddPins(TAPE_PIN);
    
    // Main event loop
    while (1) {
        // Read the value from the ADC pin if needed
        if (AD_IsNewDataReady() == TRUE) {
            int tape_sensor_reading = EXPMA(AD_ReadADPin(TAPE_PIN));
            unsigned int new_status;
            
            // Compare readings and trigger event if the value is different for hysteresis
            if (tape_sensor_reading >= TAPE_HIGH_THRESHOLD) {
                new_status = TAPE_HIGH;
            } else if (tape_sensor_reading <= TAPE_LOW_THRESHOLD) {
                new_status = TAPE_LOW;
            }
            
            // Print out message if status is different
            if (new_status != tape_status) {
                if (new_status == TAPE_HIGH) {
                    printf("Tape sensor detected high. \r\n");
                } else {
                    printf("Tape sensor detected low. \r\n");
                }
                
                printf("The tape sensor reading from the ADC is %d. \r\n", tape_sensor_reading);
            }
            
            // Update previous status to the new status
            tape_status = new_status;
            
            // Test Display (remove when you have successfully gotten a pin reading)
            //printf("The tape sensor reading from the ADC is %d. \r\n", tape_sensor_reading);
            //printf("Tape: %d. \r\n", tape_sensor_reading);
        }
    }
    
    return 0;
}
#endif

/*******************************************************************************
* PRIVATE FUNCTION IMPLEMENTATIONS *
******************************************************************************/
#ifdef TAPE_SENSOR_HARNESS
int EXPMA(int value) {
    EMA = (value * ALPHA)+((prev_tape_reading)*(1 - ALPHA));
    prev_tape_reading = EMA;
    return EMA;
}
#endif