/*
 * File:   TrackWireDetectorHarness.c
 * Author: derri
 *
 * Created on May 10, 2024, 2:58 PM
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
int EXPMA(int value);

#define TRACK_WIRE_PIN AD_PORTV3 // AC pin definition

#define TRACK_DETECT_THRESHOLD 300
#define TRACK_NO_DETECT_THRESHOLD 250

#define TRACK_DETECT 1
#define TRACK_NO_DETECT 0

unsigned int track_wire_status = TRACK_NO_DETECT;

// EMA
unsigned int prev_track_reading = 0;

// EMA Filter
#define ALPHA 0.05
/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/

/*
 * The Gain for the Track Wire detector being used is three cascading stage of amplification.
 * 11 by 11 by 11 gain. (A 100k resistor and 10k resistor is used for all stages
 * 10mH inductor is used.
 * 47uF capacitor
 */
//#define TRACK_WIRE_HARNESS

#ifdef TRACK_WIRE_HARNESS
unsigned int EMA = 0;
#endif

#ifdef TRACK_WIRE_HARNESS
int main(void) {
    
    printf("Test harness for the track wire detector. \r\n");
    printf("Warning, all test harnesses uses the same pin, which is V3. \r\n");
    
    // Initialization functions
    BOARD_Init(); // Board
    AD_Init(); // AD Pins
    
    // Setup
    AD_AddPins(TRACK_WIRE_PIN);
    
    // Main event loop
    while (1) {
        
        // Read pin whenever new reading is available
        if (AD_IsNewDataReady() == TRUE) {
            int track_wire_reading = EXPMA(AD_ReadADPin(TRACK_WIRE_PIN));
            unsigned int new_status;
            
            // Compare and set values based on hysteresis bounds
            if (track_wire_reading > TRACK_DETECT_THRESHOLD) {
                new_status = TRACK_DETECT;
            } else if (track_wire_reading < TRACK_NO_DETECT_THRESHOLD) {
                new_status = TRACK_NO_DETECT;
            }                                                                                                       
            
            // Print out message if status is different
            if (new_status != track_wire_status) {
                if (new_status == TRACK_DETECT) {
                    printf("Track wire has been detected. \r\n");
                } else {
                    printf("Track wire has not been detected. \r\n");
                }
                
                printf("The track wire sensor reading from the ADC is %d. \r\n", track_wire_reading);
            }
            
            // Update previous status to the new status
            track_wire_status = new_status;
            
            // Test Display (remove when you have successfully gotten a pin reading)
            //printf("The track wire sensor reading from the ADC is %d. \r\n", track_wire_reading);
        }
    }
    
    return 0;
}
#endif


/*******************************************************************************
* PRIVATE FUNCTION IMPLEMENTATIONS *
******************************************************************************/
#ifdef TRACK_WIRE_HARNESS
int EXPMA(int value) {
    EMA = (value * ALPHA)+((prev_track_reading)*(1 - ALPHA));
    prev_track_reading = EMA;
    return EMA;
}
#endif