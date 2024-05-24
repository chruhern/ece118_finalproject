/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "MainHSM.h"
#include "SubHSM_Align.h"

#include <stdio.h>
#include "ES_Timers.h"
#include "Robot.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    SubForward,
    SubReverse,
    SubTurn,
    Brake,
            
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"SubForward",
	"SubReverse",
	"SubTurn",
	"Brake",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */
int sub_align_xor_shift(int seed);
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;

// Random number generation
int seed = 0;
int rand = 0;
#define MAX_TURN_TIME_TICKS 250 // Assume time in milliseconds, of the time it takes to turn 90 degrees at maximum speed
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitAlignSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunAlignSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunAlignSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = SubForward;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case SubForward: // in the first state, replace this with correct names
        printf("In forward state. \r\n");
        switch (ThisEvent.EventType) {
            
            case ES_ENTRY:
                // Initialize actions to be performed at this state
                // Move the robot forward
                Robot_SetLeftMotor(750);
                Robot_SetRightMotor(750);
                //Robot_SetLeftMotor(0);
                //Robot_SetRightMotor(0);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;

            // If any of the front bumpers or tape sensors have triggered, then transition to the turn state
            case FL_TAPE_DETECTED:
                // Transition to the next state of reversal
                nextState = Brake;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case FR_TAPE_DETECTED:
                // Transition to the next state of reversal
                nextState = Brake;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

    //        case FL_BUMPER_PRESSED:
    //            // Transition to the next state of reversal
    //            nextState = SubReverse;
    //            makeTransition = TRUE;
    //            ThisEvent.EventType = ES_NO_EVENT;
    //            break;
    //
    //        case FR_BUMPER_PRESSED:
    //            // Transition to the next state of reversal
    //            nextState = SubReverse;
    //            makeTransition = TRUE;
    //            ThisEvent.EventType = ES_NO_EVENT;
    //            break;

            case ES_NO_EVENT:
            default: // all unhandled events pass the event back up to the next level
                break;
            }
        break;
        
        case Brake:
            printf("Braking. \r\n");
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // Stop the robot
                    Robot_SetLeftMotor(0);
                    Robot_SetRightMotor(0);
                    
                    // Init Timer
                    ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, 2000);
                    break;

                case ES_EXIT:
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                        nextState = SubReverse;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_NO_EVENT:
                default:
                    break;
                }
            break; 
            
    case SubReverse:
        printf("Transitioning to reverse. \r\n");
        switch (ThisEvent.EventType) {
        case ES_ENTRY:
            // Initialize actions to be performed at this state
            // Reverse the bot
            Robot_SetLeftMotor(-750); // MOTOR_MAX
            Robot_SetRightMotor(-750);

            ES_Timer_InitTimer(SUB_TRACK_REVERSE_TIMER, 1500);
            break;
                
        case ES_EXIT:
            break;

        case ES_TIMEOUT:
            if (ThisEvent.EventParam == SUB_TRACK_REVERSE_TIMER) {
                nextState = SubForward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ES_NO_EVENT:
        default: // Nothing happens on default states
            break;
        }
        
        break;
        

    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunAlignSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunAlignSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
int sub_align_xor_shift(int seed) {
    // Pseudorandomly generate a value
    int val = seed;
    val ^= (val << 13);
    val ^= (val >> 17);
    val ^= (val << 5);
    return val;
}
