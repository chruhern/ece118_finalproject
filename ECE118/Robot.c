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
#include <RC_Servo.h>
#include <AD.h>
#include <LED.h>
#include <IO_Ports.h>

char Robot_Init() {
    
    // Initializes all the different adc pins and bits needed to control it
    // Initialization
    LED_Init();
    
    // Initialize trise
    PORTV03_TRIS = 1; // Set as input
    
    // Set some LED Banks
    LED_AddBanks(LED_BANK1);
    
    return SUCCESS;
}

int Robot_GetTape() {
    return PORTV03_BIT;
}
