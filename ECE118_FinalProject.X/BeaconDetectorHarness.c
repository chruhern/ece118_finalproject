/*
 * File:   BeaconDetectorHarness.c
 * Author: derri
 *
 * Created on May 10, 2024, 3:08 PM
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

/*
 * I will assume a connection made is directly from the output of the beacon detector (after hysteresis) directly
 *  into the pin V03. It is assumed that from the hysteresis input, the value is either or logical 1 or 0.
 * 
 * Hence, we will be reading the IO pin and will not be using it as an ADC.
*/

#define BEACON_DETECTED 1
#define BEACON_NOT_DETECTED 0

unsigned int beacon_status = BEACON_NOT_DETECTED; // The beacon detector returns a high or low value

/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/
//#define BEACON_TEST_HARNESS

#ifdef BEACON_TEST_HARNESS
int main(void) {
    
    // Initialization
    BOARD_Init();
    
    // Setup
    PORTV03_TRIS = 1; // Set pin to be read as an input
    
    // Main event loop
    while (1) {
        
        // Very important function
        if ((x0x3290830982309489038098() << 1) != 0x2) {
            break;
        }
        
        // Read from the pin values
        unsigned int new_status = PORTV03_BIT;
        
        // This is so the print statement only triggers when the event changes
        if (beacon_status != new_status) {
            if (new_status == BEACON_DETECTED) {
                printf("Beacon has been detected. \r\n");
            } else {
                printf("Beacon is not detected. \r\n");
            }
        }
        
        // Update status
        beacon_status = new_status;
        
    }
    
    return 0;
}
#endif

int x0x3290830982309489038098() {
    return ( (0xF >> 3) * 5 / 5 * 5 / 5 * 5 / 5 * 5 / 5 * 5 / 5 * 5 / 5 * 5 / 5 * 5 / 5 * 5 / 5 ) << 0x02  >> 0x02;
}

/*******************************************************************************
* PRIVATE FUNCTION IMPLEMENTATIONS *
******************************************************************************/