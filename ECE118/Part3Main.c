/*
 * File:   Part3Main.c
 * Author: derri
 *
 * Created on April 29, 2024, 9:30 PM
 */


#include "xc.h"
#include <stdio.h>

#include <BOARD.h>
#include <RC_Servo.h>
#include <AD.h>
#include <LED.h>
#include <pwm.h>
#include <IO_Ports.h>

#define MAX_ADC 1023
void LED_Dir(char dir, uint32_t pot);

//#define PART_3
#ifdef PART_3
int main(void) {
    
    printf("Starting out Part 4 \r\n");
    // Initialize Board
    BOARD_Init();
    
    // Initialize AD
    AD_Init();

    // Initialize PWM
    PWM_Init();
    
    // Initialize LEDs
    LED_Init();
    
    // Set up AD pin to W3 to take in input from potentiometer
    AD_AddPins(AD_PORTV3);
    
    // Set up PWM pin to Y10
    PWM_AddPins(PWM_PORTY10);
    
    // Initialize I/O pins for the switches and etc
    PORTV05_TRIS = 0; // Set port for IN1 as output
    PORTV06_TRIS = 0; // Set port for IN2 as output
    PORTV04_TRIS = 1; // Set port to take in switch value, so set input
    
    
    // Initialize the LEDs
    LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    
    // Calculate duty scale factor (must convert constants into floats, otherwise value will be 0 due to int conversion)
    float max_pwm = (float) MAX_PWM;
    float max_adc = (float) MAX_ADC;
    float duty_scale_factor = (max_pwm / max_adc);
    
    while (1) {
        // Read from the switches, if switch is on, set the output pins.
        if (PORTV04_BIT){
            PORTV06_LAT = 1;
            PORTV05_LAT = 0;
        
        }else{
            PORTV06_LAT = 0;
            PORTV05_LAT = 1;
        }
        
        
        // Check potentiometer value
        if (AD_IsNewDataReady() == TRUE) {
            
            // Get the ADC value
            unsigned int adc_val = AD_ReadADPin(AD_PORTV3);
            
            // Scale duty cycle according to the adc_value
            float scaled_duty_cycle = (float)adc_val * duty_scale_factor;
            
            if (adc_val < 200) {
                scaled_duty_cycle = 200;
            } else if (adc_val > 800) {
                scaled_duty_cycle = 800;
            }
            
            printf("Scaled duty cycle %d \r\n", (unsigned int)scaled_duty_cycle);
            PWM_SetDutyCycle(PWM_PORTY10, (unsigned int)scaled_duty_cycle);
            
            
            LED_Dir(PORTV04_BIT, adc_val);

        }
    }
}
#endif


void LED_Dir(char dir, uint32_t pot){
    uint16_t led_num = (4*pot)/1023;
    uint16_t led_bar = 0;
    
    while(led_num > 0) {
        led_bar = led_bar << 1;
        led_bar = led_bar | 0b1;
        led_num--;
    }
    
    if(dir == 1){
        LED_SetBank(LED_BANK3, 0b0000);
        LED_SetBank(LED_BANK2, 0b0000);
        LED_SetBank(LED_BANK1, led_bar & 0b1111);
    }else{
        LED_SetBank(LED_BANK1, 0b0000);
        LED_SetBank(LED_BANK2, 0b0000);
        LED_SetBank(LED_BANK3, led_bar & 0b1111);
    }

}


