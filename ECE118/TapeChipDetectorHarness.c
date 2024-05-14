/*
 * File:   TapeChipDetectorHarness.c
 * Author: derri
 *
 * Created on May 14, 2024, 2:23 PM
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
#define CHIP_HIGH 1
#define CHIP_LOW 0

unsigned int chip_status = CHIP_LOW;

// EMA Filter
#define ALPHA 0.09
/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/

#define TAPE_CHIP_HARNESS

#ifdef TAPE_CHIP_HARNESS
    unsigned int EMA = 0;
#endif
    
#ifdef TAPE_CHIP_HARNESS
int main(void) {
    
    printf("Starting up test harness for tape chip (HW-870) detection. \r\n");
    printf("Warning, all test harnesses uses the same pin, which is V3. \r\n");
    
    // Initialization functions
    BOARD_Init(); // Board
    
    // Set pin as input
    PORTV03_TRIS = 1;
    
    // Main event loop
    while (1) {
        
        // Read the input value of the pin
        int new_status = PORTV03_BIT;
        
        //printf("The new status is %d \r\n", new_status);
        if (new_status != chip_status) {
            if (new_status == CHIP_HIGH) {
                printf("Tape chip at high (tape detected). \r\n");
            } else {
                printf("Tape chip at low (no tape detected). \r\n");
            }
        }
        
        // Update previous status to current
        chip_status = new_status;
        
    }
    
    return 0;
}
#endif

/*******************************************************************************
* PRIVATE FUNCTION IMPLEMENTATIONS *
******************************************************************************/