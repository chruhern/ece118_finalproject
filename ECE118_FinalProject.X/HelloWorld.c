/*
 * File:   HelloWorld.c
 * Author: derri
 *
 * Created on May 10, 2024, 12:56 PM
 */

// MPLab Internal Libraries
#include <xc.h>
#include <stdio.h>

// Libraries
#include "Board.h"
#include "AD.h"
#include "IO_Ports.h"
#include "LED.h"
#include "pwm.h"
#include "timers.h"

//#define TEST_MAIN

#ifdef TEST_MAIN
int main(void)
{
    
    // Initialize the Board
    BOARD_Init();
    
    // Initialize the LED
    LED_Init();
    
    printf("Hello World! This is the test code for the ECE118 final project \r\n");
    
    // Add Banks
    LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    
    // Turn on the LEDs
    LED_SetBank(LED_BANK1, 0xF);
    LED_SetBank(LED_BANK2, 0xF);
    LED_SetBank(LED_BANK3, 0xF);
    
    while (1) {
    ;
    }
}
#endif

