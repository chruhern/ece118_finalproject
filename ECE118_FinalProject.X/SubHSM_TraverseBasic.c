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
#include "SubHSM_TraverseBasic.h"

#include "SubHSM_Align.h"
#include <stdio.h>
#include "Robot.h"
#include "ES_Timers.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
            
    BASIC_TRAVERSE_FORWARD,
    BASIC_TRAVERSE_LEFT_REVERSE,
    BASIC_TRAVERSE_RIGHT_REVERSE,
    BASIC_TRAVERSE_GRADUAL_RIGHT,
    BASIC_TRAVERSE_GRADUAL_LEFT,
            
    BASIC_TRAVERSE_PIVOT_WALL_LEFT,
    BASIC_TRAVERSE_PIVOT_WALL_RIGHT,
    BASIC_TRAVERSE_WALL_REVERSE,
    BASIC_TRAVERSE_TANK_LEFT_WALL,
    BASIC_TRAVERSE_TANK_RIGHT_WALL,
    BASIC_TRAVERSE_FOLLOW_WALL_LEFT,
    BASIC_TRAVERSE_FOLLOW_WALL_RIGHT,  
            
    BASIC_TRAVERSE_REAR_PIVOT_LEFT_OUT,
    BASIC_TRAVERSE_REAR_PIVOT_RIGHT_OUT,
            
    BASIC_TRAVERSE_TANK_EXIT,
            
    BUFFER_STATE,

} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"BASIC_TRAVERSE_FORWARD",
	"BASIC_TRAVERSE_LEFT_REVERSE",
	"BASIC_TRAVERSE_RIGHT_REVERSE",
	"BASIC_TRAVERSE_GRADUAL_RIGHT",
	"BASIC_TRAVERSE_GRADUAL_LEFT",
	"BASIC_TRAVERSE_PIVOT_WALL_LEFT",
	"BASIC_TRAVERSE_PIVOT_WALL_RIGHT",
	"BASIC_TRAVERSE_WALL_REVERSE",
	"BASIC_TRAVERSE_TANK_LEFT_WALL",
	"BASIC_TRAVERSE_TANK_RIGHT_WALL",
	"BASIC_TRAVERSE_FOLLOW_WALL_LEFT",
	"BASIC_TRAVERSE_FOLLOW_WALL_RIGHT",
	"BASIC_TRAVERSE_REAR_PIVOT_LEFT_OUT",
	"BASIC_TRAVERSE_REAR_PIVOT_RIGHT_OUT",
	"BASIC_TRAVERSE_TANK_EXIT",
	"BUFFER_STATE",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */
void CalcTurnAngle(int time_elasped);

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;

#define TB_TANK_LEFT_TICKS 800
#define TB_TANK_RIGHT_TICKS 800

#define PIVOT_90_LEFT_TICKS 500
#define PIVOT_90_RIGHT_TICKS 500

#define MAX_TURN_DEG 180
#define MIN_TURN_DEG 10
#define MAX_TIME_SEC 10 // Max time to be considered in seconds

#define TRAV_MIN(x, y) (((x) < (y)) ? (x) : (y))
#define TRAV_MAX(x, y) (((x) > (y)) ? (x) : (y))

#define PIVOT_LEFT_INWARD_ML 0
#define PIVOT_LEFT_INWARD_MR MOTOR_MAX

#define PIVOT_RIGHT_INWARD_ML MOTOR_MAX
#define PIVOT_RIGHT_INWARD_MR 0

#define PIVOT_LEFT_OUTWARD_ML 0
#define PIVOT_LEFT_OUTWARD_MR -MOTOR_MAX

#define PIVOT_RIGHT_OUTWARD_ML -MOTOR_MAX
#define PIVOT_RIGHT_OUTWARD_MR 0

#define WALL_PIVOT_TICK 2000

#define WALL_BIAS_LEFT_ML 900
#define WALL_BIAS_LEFT_MR 1000

#define WALL_BIAS_RIGHT_ML 1000
#define WALL_BIAS_RIGHT_MR 800

#define WALL_REVERSE_TICK 250
#define WALL_FORWARD_TICK 250

// Track time
uint32_t prev_event_time;
uint32_t delta_time;
uint32_t turn_ticks = 1000; // How how much to turn in ticks

#define PREV_LEFT 0
#define PREV_RIGHT 1
int alreadyReversed = 0;
int prevDirection;

int visited_left = 0; // Whether if it has visited the left.
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTraverseBasicSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTraverseBasicSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunTraverseBasicSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTraverseBasicSubHSM(ES_Event ThisEvent)
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
ES_Event RunTraverseBasicSubHSM(ES_Event ThisEvent)
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
            nextState = BASIC_TRAVERSE_FORWARD;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
        
    case BASIC_TRAVERSE_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move the robot forward (whether if it is straight or not doesn't matter)
                Robot_SetLeftMotor(MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                // Track the time
                prev_event_time = ES_Timer_GetTime();
                break;

            case ES_EXIT:
                // When event exits, compute the delta time
                delta_time = ES_Timer_GetTime() - prev_event_time;
                
                // Calculate the turn tick given delta time
                CalcTurnAngle(delta_time);
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Add detection events for front left tape and bumpers, and front right tape and bumpers.
            // ********** Left Traversals ********** //
            case FL_TAPE_DETECTED:
                nextState = BASIC_TRAVERSE_LEFT_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FL_BUMPER_PRESSED:
                // If the bumper has been pressed, then pivot to follow the wall
                nextState = BASIC_TRAVERSE_PIVOT_WALL_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            // ********** Right Traversals ********** //
            case FR_TAPE_DETECTED:
                nextState = BASIC_TRAVERSE_RIGHT_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_PRESSED:
                nextState = BASIC_TRAVERSE_PIVOT_WALL_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_LEFT_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Reverse the robot
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Reverse until the front left bumpers or tape is no longer detected
            case FL_TAPE_NOT_DETECTED:
                nextState = BASIC_TRAVERSE_GRADUAL_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FL_BUMPER_RELEASED:
                nextState = BASIC_TRAVERSE_GRADUAL_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_RIGHT_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Reverse the robot
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Same as left reverse, except tape detection is for right tape undetection
            case FR_TAPE_NOT_DETECTED:
                nextState = BASIC_TRAVERSE_GRADUAL_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_RELEASED:
                nextState = BASIC_TRAVERSE_GRADUAL_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_GRADUAL_RIGHT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a right tank turn
                Robot_SetLeftMotor(MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                // Initialize timer
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, turn_ticks);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // When timer has timed out, transition back to the forward state
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = BASIC_TRAVERSE_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                };
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_GRADUAL_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a left tank turn
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, turn_ticks);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // When timer has timed out, transition back to the forward state
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = BASIC_TRAVERSE_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                };
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
    
    // ********** WALL ALIGN FOLLOW ********** //
    case BASIC_TRAVERSE_PIVOT_WALL_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // If the left bumper hits the wall, then pivot left inward.
                Robot_SetLeftMotor(PIVOT_LEFT_INWARD_ML);
                Robot_SetRightMotor(PIVOT_LEFT_INWARD_MR);
                
                printf("pivoting left inward. \r\n");
                
                // Initialize a timer to turn, because of the lack of rear side bumpers, assume it takes time to align.
                //ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, WALL_PIVOT_TICK);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, move right.
//                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
//                    nextState = BASIC_TRAVERSE_FOLLOW_WALL_RIGHT;
//                    makeTransition = TRUE;
//                    ThisEvent.EventType = ES_NO_EVENT;
//                }
                break;
            
            // Put all detection events over here
            // Pivot until rear left bumper is hit
            case FR_BUMPER_PRESSED:
                printf("front right bumper pressed. \r\n");
                nextState = BASIC_TRAVERSE_TANK_LEFT_WALL;//BASIC_TRAVERSE_FOLLOW_WALL_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_PIVOT_WALL_RIGHT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // If the right bumper hits, pivot right outwards
                Robot_SetLeftMotor(PIVOT_RIGHT_INWARD_ML);
                Robot_SetRightMotor(PIVOT_RIGHT_INWARD_MR);
                
                printf("pivoting right inward. \r\n");
                
                // Initialize a timer to turn, because of the lack of rear side bumpers, assume it takes time to align.
                //ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, WALL_PIVOT_TICK);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, move with a left bias to follow the wall.
//                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
//                    nextState = BASIC_TRAVERSE_FOLLOW_WALL_LEFT;
//                    makeTransition = TRUE;
//                    ThisEvent.EventType = ES_NO_EVENT;
//                }
                break;
            
            // Put all detection events over here
            // When rear right bumper hits, 
            case FL_BUMPER_PRESSED:
                printf("front left bumper pressed. \r\n");
                nextState = BASIC_TRAVERSE_TANK_LEFT_WALL;//BASIC_TRAVERSE_FOLLOW_WALL_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
    
    case BASIC_TRAVERSE_WALL_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("wall reversing. \r\n");
                // Reverse until bumpers are no longer touched, then initialize a timer to move backwards for some time
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // When timeout, perform a left tank turn to be parallel to the wall.
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = BASIC_TRAVERSE_TANK_RIGHT_WALL;//BASIC_TRAVERSE_FOLLOW_WALL_LEFT;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Put all detection events over here
            // When either front bumpers are released, initialize a timer to continue backing out
            case FL_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, WALL_REVERSE_TICK);
                break;
                
            case FR_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, WALL_REVERSE_TICK);
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
     
    case BASIC_TRAVERSE_TANK_LEFT_WALL:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("tanking left. \r\n");
                // Perform a tank turn left to be as parallel to the wall as possible
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, TB_TANK_LEFT_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, follow the wall to the left.
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    if (visited_left == 1) {
                        nextState = BASIC_TRAVERSE_FOLLOW_WALL_RIGHT;
                    } else {
                        nextState = BASIC_TRAVERSE_FOLLOW_WALL_LEFT;
                    }
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

    case BASIC_TRAVERSE_TANK_RIGHT_WALL:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Tank turn to the right.
                printf("tanking right. \r\n");
                Robot_SetLeftMotor(MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, TB_TANK_RIGHT_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, follow the wall to the right.
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = BASIC_TRAVERSE_FOLLOW_WALL_RIGHT;
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
            
    case BASIC_TRAVERSE_FOLLOW_WALL_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move forward with a right bias
                Robot_SetLeftMotor(WALL_BIAS_RIGHT_ML);
                Robot_SetRightMotor(WALL_BIAS_RIGHT_MR);
                
                printf("Attempting left wall follow. \r\n");
                break;

            case ES_EXIT:
                // Set left visited to true, as left traversal is finished
                visited_left = 1;
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Keep moving left until the front left tape detects(farthest when moving left)
            // When this occurs, attempt to pivot right outwards until rear bumpers are hit
            case FL_TAPE_DETECTED:
                nextState = BASIC_TRAVERSE_REAR_PIVOT_RIGHT_OUT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FLO_BUMPER_PRESSED:
                nextState = BASIC_TRAVERSE_REAR_PIVOT_RIGHT_OUT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FRO_BUMPER_PRESSED:
                nextState = BASIC_TRAVERSE_REAR_PIVOT_RIGHT_OUT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            // ***** Alignment **** //
            case FR_BUMPER_PRESSED:
                // Bias to the left
                Robot_SetLeftMotor(WALL_BIAS_LEFT_ML);
                Robot_SetRightMotor(WALL_BIAS_LEFT_MR);
                break;
                
            case FR_BUMPER_RELEASED:
                // Bias to the right
                Robot_SetLeftMotor(WALL_BIAS_RIGHT_ML);
                Robot_SetRightMotor(WALL_BIAS_RIGHT_MR);
                break;
                
            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_FOLLOW_WALL_RIGHT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move forward, but with a right bias. This is essentially following the wall to the
                Robot_SetLeftMotor(WALL_BIAS_LEFT_ML);
                Robot_SetRightMotor(WALL_BIAS_LEFT_MR);
                
                printf("Attempting right wall follow. \r\n");
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Keep moving when the front left tape is detected, or any of the obstacle bumpers
            // If no reversal has been made, then perform a reverse, otherwise, continue normal alignment.
            case FR_TAPE_DETECTED:
                nextState = BASIC_TRAVERSE_REAR_PIVOT_LEFT_OUT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FLO_BUMPER_PRESSED:
                nextState = BASIC_TRAVERSE_REAR_PIVOT_LEFT_OUT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FRO_BUMPER_PRESSED:
                nextState = BASIC_TRAVERSE_REAR_PIVOT_LEFT_OUT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
             // ***** Alignment **** //
            case FL_BUMPER_PRESSED:
                // Bias to the left
                Robot_SetLeftMotor(WALL_BIAS_RIGHT_ML);
                Robot_SetRightMotor(WALL_BIAS_RIGHT_MR);
                break;
                
            case FL_BUMPER_RELEASED:
                // Bias to the right
                Robot_SetLeftMotor(WALL_BIAS_LEFT_ML);
                Robot_SetRightMotor(WALL_BIAS_LEFT_MR);
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_REAR_PIVOT_LEFT_OUT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform an outward left pivot
                Robot_SetLeftMotor(PIVOT_LEFT_OUTWARD_ML);
                Robot_SetRightMotor(PIVOT_LEFT_OUTWARD_MR);
                break;

            case ES_EXIT:
                // Set visit left state back to false, as the process has been finished
                visited_left = 0;
                break;

            case ES_TIMEOUT:
                // After timeout, begin exit state, go back to the forward state
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = BASIC_TRAVERSE_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Put all detection events over here
            case RR_BUMPER_PRESSED:
                // Initialize a timer to move to the right gradually
                Robot_SetLeftMotor(WALL_BIAS_RIGHT_ML);
                Robot_SetRightMotor(WALL_BIAS_RIGHT_MR);
                
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, WALL_FORWARD_TICK);
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_REAR_PIVOT_RIGHT_OUT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform an outward right pivot
                Robot_SetLeftMotor(PIVOT_RIGHT_OUTWARD_ML);
                Robot_SetRightMotor(PIVOT_RIGHT_OUTWARD_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = BASIC_TRAVERSE_TANK_LEFT_WALL;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Put all detection events over here
            case RL_BUMPER_PRESSED:
                // Initialize a timer to move forward for a short time
                Robot_SetLeftMotor(MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, WALL_FORWARD_TICK);
                break;
                
            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BASIC_TRAVERSE_TANK_EXIT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                
                // Depending on what the previous direction of movement was, perform a tank turn of either left or right
                if (prevDirection == PREV_LEFT) {
                    // If moving in the left direction, then turn left to exit.
                    Robot_SetLeftMotor(-MOTOR_MAX);
                    Robot_SetRightMotor(MOTOR_MAX);
                } else {
                    // If moving in the right drection, then tank turn right to exit
                    Robot_SetLeftMotor(MOTOR_MAX);
                    Robot_SetRightMotor(-MOTOR_MAX);
                }
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Keep turning until rear left bumper triggers, then go back to forward traversal
            case RR_BUMPER_PRESSED:
                nextState = BASIC_TRAVERSE_FORWARD;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case RL_BUMPER_PRESSED:
                nextState = BASIC_TRAVERSE_FORWARD;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
    
    case BUFFER_STATE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // At this state, just stop the robot from moving.
                Robot_SetLeftMotor(0);
                Robot_SetRightMotor(0);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
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
        RunTraverseBasicSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTraverseBasicSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
void CalcTurnAngle(int time_elasped) {
    // Calculate angle based on elasped time
    int raw_angle =  (MAX_TURN_DEG / MAX_TIME_SEC) * TRAV_MIN(MAX_TIME_SEC, time_elasped);
    int true_angle = TRAV_MAX(MIN_TURN_DEG, raw_angle);
    
    // Convert angle to time
    float turn_time = ((float)true_angle / 90.0) * (float)PIVOT_90_LEFT_TICKS; // ticks, how long it takes to turn 90 degrees
    
    // Convert ticks back to an integer value and set it
    turn_ticks = (int)turn_time;
    
    //printf("The turn ticks is %d. \r\n", turn_ticks);
    //printf("The time elasped is : %d. \r\n", time_elasped);
}
