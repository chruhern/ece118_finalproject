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

#include <stdio.h>
#include "ES_Timers.h"
#include "Robot.h"

#include "MainHSM.h"
#include "SubHSM_Search.h"

//  ***** Pathfinding ***** //
#include "GridNavigation.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
            
    SEARCH_INITIAL_TURN_90_LEFT,

    SEARCH_HORIZONTAL_FORWARD,
    SEARCH_HORIZONTAL_FORWARD_ALIGN,
    SEARCH_HORIZONTAL_LEFT_ALIGN,
    SEARCH_HORIZONTAL_RIGHT_ALIGN,

    SEARCH_VERTICAL_TURN_FIRST,
    SEARCH_VERTICAL_FORWARD,
    SEARCH_VERTICAL_TURN_SECOND,

    SEARCH_FINISHED,            
    
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"SEARCH_INITIAL_TURN_90_LEFT",
	"SEARCH_HORIZONTAL_FORWARD",
	"SEARCH_HORIZONTAL_FORWARD_ALIGN",
	"SEARCH_HORIZONTAL_LEFT_ALIGN",
	"SEARCH_HORIZONTAL_RIGHT_ALIGN",
	"SEARCH_VERTICAL_TURN_FIRST",
	"SEARCH_VERTICAL_FORWARD",
	"SEARCH_VERTICAL_TURN_SECOND",
	"SEARCH_FINISHED",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;

// *** Search Direction *** //
#define SEARCH_LEFT 1
#define SEARCH_RIGHT 0
unsigned int current_search_direction = SEARCH_LEFT; // Current direction that bot is moving
unsigned int horizontal_traversals = 0; // How many times have we traversed horizontally in the row
unsigned int vertical_traversals = 0; // How many times have we traversed vertically
unsigned int total_traversals = 0; // For finding the node coordinate. Total % GRID_X = X, Total / GRID_X = Y

int grid_last_traversed_time = 0; // Global variable?

// *** Travel Timers *** //
#define SEARCH_FORWARD_INC_TICKS 100

// All tank turns and pivots are 90 degrees
#define SEARCH_LEFT_TANK_TICKS 100
#define SEARCH_LEFT_TANK_L_MOTOR -1000
#define SEARCH_LEFT_TANK_R_MOTOR 1000

#define SEARCH_RIGHT_TANK_TICKS 100
#define SEARCH_RIGHT_TANK_L_MOTOR 1000
#define SEARCH_RIGHT_TANK_R_MOTOR -1000

#define SEARCH_LEFT_PIVOT_TICKS 100
#define SEARCH_LEFT_PIVOT_L_MOTOR -MOTOR_MAX
#define SEARCH_LEFT_PIVOT_R_MOTOR 0

#define SEARCH_RIGHT_PIVOT_TICKS 100
#define SEARCH_RIGHT_PIVOT_L_MOTOR 0
#define SEARCH_RIGHT_PIVOT_R_MOTOR -MOTOR_MAX

#define SUB_SEARCH_BRAKE_TICKS 200 // Time to brake before transitioning to the next state

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitSearchSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitSearchSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunSearchSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunSearchSubHSM(ES_Event ThisEvent)
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
ES_Event RunSearchSubHSM(ES_Event ThisEvent)
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
            nextState = SEARCH_INITIAL_TURN_90_LEFT;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
        
    case SEARCH_INITIAL_TURN_90_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a 90 degree tank turn to the left
                Robot_SetLeftMotor(SEARCH_LEFT_TANK_L_MOTOR);
                Robot_SetRightMotor(SEARCH_LEFT_TANK_R_MOTOR);
                
                // Initialize a timer
                ES_Timer_InitTimer(SUB_SEARCH_TURN_TIMER, SEARCH_LEFT_TANK_TICKS);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_SEARCH_TURN_TIMER) {
                    // Transition to the horizontal traversal state
                    nextState = SEARCH_HORIZONTAL_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;

    // ********** Horizontal Search ********** //
    // In forward search, set the search increment to be enough just to be before the tape, or else this fails!!!
    case SEARCH_HORIZONTAL_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Begin moving forward, keep track of the time of first traversal using the free running timer.
                Robot_SetLeftMotor(LEFT_FORWARD_MAX);
                Robot_SetRightMotor(RIGHT_FORWARD_MAX);
                
                // Keep track of time in case collision occurs, requiring reversal
                grid_last_traversed_time = ES_Timer_GetTime();
                
                // Set a timer to transition state once a single 'forward' increment is over.
                ES_Timer_InitTimer(SUB_SEARCH_FORWARD_INC_TIMER, SEARCH_FORWARD_INC_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_SEARCH_FORWARD_INC_TIMER) {
                    // If we have traversed the horizontal grid size, then transition to alignment. Otherwise, keep moving forward.
                    if (horizontal_traversals >= (GRID_SIZE_X - 1)) {
                        
                        // Reset the number of horizontal traversals after process is finished
                        horizontal_traversals = 0;
                        
                        nextState = SEARCH_HORIZONTAL_FORWARD;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else {
                        
                        // Increase the number of horizontal and total traversals (to determine when traversal ends)
                        horizontal_traversals++;
                        total_traversals++;
                        
                        // Add the node to the grid
                        printf("Add the fucking node to the grid right fucking now... \r\n");
                        int grid_x = total_traversals % GRID_SIZE_X;
                        int grid_y = total_traversals / GRID_SIZE_X;
                        
                        nextState = SEARCH_HORIZONTAL_FORWARD_ALIGN;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                }
                break;
            
            // Put all detection events over here.
            // If front tapes have been active, then begin alignment process, then transition back 

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case SEARCH_HORIZONTAL_FORWARD_ALIGN:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Keep moving forward (THEORETICALLY: THIS SHOULDN'T BE TOO MUCH, INCREMENT SHOULD BE RIGHT BEFORE TAPE)
                Robot_SetLeftMotor(LEFT_FORWARD_MAX);
                Robot_SetRightMotor(RIGHT_FORWARD_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When front tapes are detected, align according to whichever side triggered first
            case FL_TAPE_DETECTED:
                nextState = SEARCH_HORIZONTAL_LEFT_ALIGN;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_TAPE_DETECTED:
                nextState = SEARCH_HORIZONTAL_RIGHT_ALIGN;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case SEARCH_HORIZONTAL_LEFT_ALIGN:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a forward right pivot
                Robot_SetLeftMotor(SEARCH_RIGHT_PIVOT_L_MOTOR);
                Robot_SetRightMotor(SEARCH_RIGHT_PIVOT_R_MOTOR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // After alignment, perform a vertical turn (which the direction is dependent on the direction)
            case FR_TAPE_DETECTED:
                nextState = SEARCH_VERTICAL_TURN_FIRST;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case SEARCH_HORIZONTAL_RIGHT_ALIGN:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a left pivot
                Robot_SetLeftMotor(SEARCH_LEFT_PIVOT_L_MOTOR);
                Robot_SetRightMotor(SEARCH_LEFT_PIVOT_R_MOTOR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            case FL_TAPE_DETECTED:
                // Perform a vertical turn (direction tbd in state) when tape is detected. Assume alignment
                nextState = SEARCH_VERTICAL_TURN_FIRST;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    // ********** Vertical Search ********** //
    case SEARCH_VERTICAL_TURN_FIRST:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Based on the current direction, determine which direction to turn. If search left, turn left, otherwise right
                if (current_search_direction == SEARCH_LEFT) {
                    // Turn tank left, initialize timer for left tank turn
                    Robot_SetLeftMotor(SEARCH_LEFT_PIVOT_L_MOTOR);
                    Robot_SetRightMotor(SEARCH_LEFT_PIVOT_R_MOTOR);
                    
                    ES_Timer_InitTimer(SUB_SEARCH_TURN_TIMER, SEARCH_LEFT_TANK_TICKS);
                } else {
                    // Tank turn right, initialize timer for right tank turn
                    Robot_SetLeftMotor(SEARCH_RIGHT_TANK_L_MOTOR);
                    Robot_SetRightMotor(SEARCH_RIGHT_TANK_R_MOTOR);
                    
                    ES_Timer_InitTimer(SUB_SEARCH_TURN_TIMER, SEARCH_RIGHT_TANK_TICKS);
                };
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After transition, move to the forward state
                if (ThisEvent.EventParam == SUB_SEARCH_TURN_TIMER) {
                    nextState = SEARCH_VERTICAL_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case SEARCH_VERTICAL_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move forward in the forward direction.
                Robot_SetLeftMotor(LEFT_FORWARD_MAX);
                Robot_SetRightMotor(RIGHT_FORWARD_MAX);
                
                // Keep track of time in case collision occurs, requiring reversal
                grid_last_traversed_time = ES_Timer_GetTime();
                
                // Set a timer to transition state once a single 'forward' increment is over.
                ES_Timer_InitTimer(SUB_SEARCH_FORWARD_INC_TIMER, SEARCH_FORWARD_INC_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, transition to the second stage to perform a secondary turn
                if (ThisEvent.EventParam == SUB_SEARCH_FORWARD_INC_TIMER) {
                    nextState = SEARCH_VERTICAL_TURN_SECOND;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case SEARCH_VERTICAL_TURN_SECOND:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Essentially identical to the first stage of vertical turn.
                if (current_search_direction == SEARCH_LEFT) {
                    // Turn tank left, initialize timer for left tank turn
                    Robot_SetLeftMotor(SEARCH_LEFT_PIVOT_L_MOTOR);
                    Robot_SetRightMotor(SEARCH_LEFT_PIVOT_R_MOTOR);
                    
                    ES_Timer_InitTimer(SUB_SEARCH_TURN_TIMER, SEARCH_LEFT_TANK_TICKS);
                } else {
                    // Tank turn right, initialize timer for right tank turn
                    Robot_SetLeftMotor(SEARCH_RIGHT_TANK_L_MOTOR);
                    Robot_SetRightMotor(SEARCH_RIGHT_TANK_R_MOTOR);
                    
                    ES_Timer_InitTimer(SUB_SEARCH_TURN_TIMER, SEARCH_RIGHT_TANK_TICKS);
                };
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timer runs, check if the vertical turn is within the grid size y. If it is, traversal is finished
                if (ThisEvent.EventParam == SUB_SEARCH_TURN_TIMER) {
                    
                    // Check if vertical traversal is finished
                    if (vertical_traversals >= (GRID_SIZE_Y - 1)) {
                        nextState = SEARCH_FINISHED;
                    } else {
                        // If traversal isn't finished, then transition back to horizontal movement. Add node.
                        printf("Add the fucking node to the grid for vertical... \r\n");
                        int grid_x = total_traversals % GRID_SIZE_X;
                        int grid_y = total_traversals / GRID_SIZE_X;
                        
                        nextState = SEARCH_HORIZONTAL_FORWARD;
                    }
                    
                    // Increment vertical traversal
                    vertical_traversals++;
                    
                    // Make transition
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;

    case SEARCH_FINISHED:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Stop the robot, brake it for a moment
                Robot_SetLeftMotor(0);
                Robot_SetRightMotor(0);
                
                // Initialize timer for braking (GENERIC_BRAKE_TIMER)
                ES_Timer_InitTimer(GENERIC_BRAKE_TIMER, SUB_SEARCH_BRAKE_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, there is no transition within this state, transition out of state
                if (ThisEvent.EventParam == GENERIC_BRAKE_TIMER) {
                    // Post an event to signify HSM transition
                    ThisEvent.EventType = FIELD_MAPPED;
                }
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunSearchSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunSearchSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

