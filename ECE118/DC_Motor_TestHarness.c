/*
 * File:   DC_Motor_TestHarness.c
 * Author: derri
 *
 * Created on May 11, 2024, 5:10 PM
 */

/*******************************************************************************
* #INCLUDES *
******************************************************************************/
// Internal PIC32
#include "xc.h"
#include <stdio.h>

#include <BOARD.h>
#include <RC_Servo.h>
#include <AD.h>
#include <LED.h>
#include <pwm.h>
#include <IO_Ports.h>

/*******************************************************************************
* PRIVATE TYPEDEFS *
******************************************************************************/
#define MOTOR_PIN PWM_PORTY10

const unsigned int duty_cycle = 800;

/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/
int main(void) {
    
    // Perform initialization
    printf("This is the test harness for a bidirection DC motor using the H-Bridge. \r\n");
    BOARD_Init();
    PWM_Init();
    LED_Init();
    
    // Set up PWM pin to Y10 (this goes into the EnableA pin)
    PWM_AddPins(MOTOR_PIN);

    // Initialize I/O pins for the switches and etc
    PORTV05_TRIS = 0; // Set port for IN1 as output
    PORTV06_TRIS = 0; // Set port for IN2 as output

    // Main event loop
    while (1) {
        // Set direction of the motors (invert them to change directions)
        PORTV06_LAT = 0;
        PORTV05_LAT = 1;
        
        // Set duty cycle
        PWM_SetDutyCycle(MOTOR_PIN, duty_cycle);

    }
    
    return 0;
}

/*******************************************************************************
* PRIVATE FUNCTION IMPLEMENTATIONS *
******************************************************************************/