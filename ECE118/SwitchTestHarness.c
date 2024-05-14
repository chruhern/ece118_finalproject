/*
 * File:   SwitchTestHarness.c
 * Author: derri
 *
 * Created on May 14, 2024, 2:57 PM
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
#define SWITCH_PRESSED 1
#define SWITCH_RELEASED 0

unsigned int prev_switch_status = SWITCH_RELEASED;
/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/
#define SWITCH_HARNESS

#ifdef SWITCH_HARNESS
int main(void) {
    
    printf("Starting up test harness for the switch (to be used as the bumpers). \r\n");
    
    // Initialization functions
    BOARD_Init(); // Board
    
    // Set pin as input
    PORTV03_TRIS = 1;
    
    // Main event loop
    while (1) {
        // Read from the switch value
        int newStatus = PORTV03_BIT;
        //printf("The status is %d \r\n", newStatus);
        if (newStatus != prev_switch_status) {
            if (newStatus == SWITCH_PRESSED) {
                printf("The switch has been pressed. \r\n");
            } else {
                printf("The switch has been released. \r\n");
            }
        }
        
        // Update previous status to current
        prev_switch_status = newStatus;
    }
    
    return 0;
}
#endif

/*******************************************************************************
* PRIVATE FUNCTION IMPLEMENTATIONS *
******************************************************************************/