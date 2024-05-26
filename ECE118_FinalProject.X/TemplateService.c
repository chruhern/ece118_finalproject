/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TemplateService.h"
#include <stdio.h>

#include "TemplateEventChecker.h"
#include "LED.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define BATTERY_DISCONNECT_THRESHOLD 175
#define TIMER_0_TICKS 20 // 100ms

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTemplateService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    ES_Timer_InitTimer(SIMPLE_SERVICE_TIMER, TIMER_0_TICKS);
    
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTemplateService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunTemplateService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    switch (ThisEvent.EventType) {
    case ES_INIT:
        // No hardware initialization or single time setups, those
        // go in the init function above.
        //
        // This section is used to reset service for some reason
        break;
        
    case ES_TIMERACTIVE:
        
    case ES_TIMERSTOPPED:
        break;
    
    // You have to put user events above the timeout, remove this, this is just as a test
//    case FL_TAPE_DETECTED:
//        printf("Front Left tape detected. \r\n");
//        break;
//        
//    case FL_TAPE_NOT_DETECTED:
//        printf("Front Left tape no longer detected. \r\n");
//        break;
//        
//    case FR_TAPE_DETECTED:
//        printf("Front right tape detected. \r\n");
//        break;
//        
//    case FR_TAPE_NOT_DETECTED:
//        printf("Front right tape no longer detected. \r\n");
//        break;
//
//    case RL_TAPE_DETECTED:\
//        printf("Rear Left tape detected. \r\n");
//        break;
//        
//    case RL_TAPE_NOT_DETECTED:
//        printf("Rear Left tape no longer detected. \r\n");
//        break;
//
//    case RR_TAPE_DETECTED:
//        printf("Rear right tape detected. \r\n");
//        break;
//        
//    case RR_TAPE_NOT_DETECTED:
//        printf("Rear right tape no longer detected. \r\n");
//        break;
//        
//    case FL_BUMPER_PRESSED:
//        printf("Front left bumper pressed. \r\n");
//        break;
//        
//    case FL_BUMPER_RELEASED:
//        printf("Front left bumper released. \r\n");
//        break;
//
//    case FR_BUMPER_PRESSED:
//        printf("Front right bumper pressed. \r\n");
//        break;
//        
//    case FR_BUMPER_RELEASED:
//        printf("Front right bumper released. \r\n");
//        break;
//
//    case RL_BUMPER_PRESSED:
//        printf("Rear left bumper pressed. \r\n");
//        break;
//        
//    case RL_BUMPER_RELEASED:
//        printf("Rear left bumper released. \r\n");
//        break;
//
//    case RR_BUMPER_PRESSED:
//        printf("Rear right bumper pressed. \r\n");
//        break;
//        
//    case RR_BUMPER_RELEASED:
//        printf("Rear right bumper released. \r\n");
//        break;
//        
//    case LEFT_TRACK_DETECTED:
//        printf("Left track detected. \r\n");
//        break;
//
//    case LEFT_TRACK_NOT_DETECTED:
//        printf("Left track not detected. \r\n");
//        break;
//
//    case RIGHT_TRACK_DETECTED:
//        printf("Right track detected. \r\n");
//        break;
//
//    case RIGHT_TRACK_NOT_DETECTED:
//        printf("Right track not detected. \r\n");
//        break;
//        
//    case BEACON_DETECTED:
//        printf("Beacon has been detected. \r\n");
//        break;
//        
//    case BEACON_NOT_DETECTED:
//        printf("Beacon is no longer detected. \r\n");
//        break;

    case ES_TIMEOUT:
        ES_Timer_InitTimer(SIMPLE_SERVICE_TIMER, TIMER_0_TICKS);
        // Poll each sensor to raise events if needed
        // Tape
        EventCheck_TapeFL();
        EventCheck_TapeFR();
        EventCheck_TapeRL();
        EventCheck_TapeRR();
        
        // Bumper
        EventCheck_BumperFL();
        EventCheck_BumperFR();
        EventCheck_BumperRL();
        EventCheck_BumperRR();
        EventCheck_BumperFLO();
        EventCheck_BumperFRO();
        
        // Beacon
        EventCheck_Beacon();

//#ifdef SIMPLESERVICE_TEST     // keep this as is for test harness      
//    default:
//        printf("\r\nEvent: %s\tParam: 0x%X",
//                EventNames[ThisEvent.EventType], ThisEvent.EventParam);
//        break;
//#endif
    }

    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

