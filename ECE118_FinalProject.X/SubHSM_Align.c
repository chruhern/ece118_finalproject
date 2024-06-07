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
       
    INIT_REVERSE,
    AVOID_FORWARD,
    AVOID_REVERSE,
    AVOID_TURN_90_LEFT,
    AVOID_REAR_GRADUAL_LEFT,
    AVOID_REAR_GRADUAL_RIGHT,

    ALIGN_PIVOT_LEFT_INWARD,
    ALIGN_PIVOT_RIGHT_INWARD,
    ALIGN_PIVOT_RIGHT_OUTWARD,
            
    TRAVERSE_LEFT_TANK_LEFT_90_OVER,
    TRAVERSE_LEFT_FWDR_BIAS,
    TRAVERSE_LEFT_FWDL_BIAS,
            
    TRAVERSE_LEFT_REVERSE_SERVO,
    TRAVERSE_LEFT_FORWARD_SERVO,

    TRAVERSE_RIGHT_REVERSE,
    TRAVERSE_RIGHT_TANK_LEFT_180_OVER,
    TRAVERSE_RIGHT_TANK_RIGHT_90_OVER,
    TRAVERSE_RIGHT_FWDR_BIAS,
    TRAVERSE_RIGHT_FWDL_BIAS,
            
    TRAVERSE_RIGHT_REVERSE_WALL,
    TRAVERSE_RIGHT_TANK_RIGHT_WALL,
    TRAVERSE_RIGHT_FORWARD_WALL,
            
    TRAVERSE_RIGHT_PV_RIGHT_IN_ALIGN,
    TRAVERSE_RIGHT_PV_LEFT_IN_ALIGN,
    TRAVERSE_RIGHT_PV_RIGHT_OUT_ALIGN,
            
    TRAVERSE_RIGHT_WALL_FWDR_BIAS,
    TRAVERSE_RIGHT_WALL_FWDL_BIAS,
            
    BOT_ALIGNED,         
    BUFFER_STATE,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"INIT_REVERSE",
	"AVOID_FORWARD",
	"AVOID_REVERSE",
	"AVOID_TURN_90_LEFT",
	"AVOID_REAR_GRADUAL_LEFT",
	"AVOID_REAR_GRADUAL_RIGHT",
	"ALIGN_PIVOT_LEFT_INWARD",
	"ALIGN_PIVOT_RIGHT_INWARD",
	"ALIGN_PIVOT_RIGHT_OUTWARD",
	"TRAVERSE_LEFT_TANK_LEFT_90_OVER",
	"TRAVERSE_LEFT_FWDR_BIAS",
	"TRAVERSE_LEFT_FWDL_BIAS",
	"TRAVERSE_LEFT_REVERSE_SERVO",
	"TRAVERSE_LEFT_FORWARD_SERVO",
	"TRAVERSE_RIGHT_REVERSE",
	"TRAVERSE_RIGHT_TANK_LEFT_180_OVER",
	"TRAVERSE_RIGHT_TANK_RIGHT_90_OVER",
	"TRAVERSE_RIGHT_FWDR_BIAS",
	"TRAVERSE_RIGHT_FWDL_BIAS",
	"TRAVERSE_RIGHT_REVERSE_WALL",
	"TRAVERSE_RIGHT_TANK_RIGHT_WALL",
	"TRAVERSE_RIGHT_FORWARD_WALL",
	"TRAVERSE_RIGHT_PV_RIGHT_IN_ALIGN",
	"TRAVERSE_RIGHT_PV_LEFT_IN_ALIGN",
	"TRAVERSE_RIGHT_PV_RIGHT_OUT_ALIGN",
	"TRAVERSE_RIGHT_WALL_FWDR_BIAS",
	"TRAVERSE_RIGHT_WALL_FWDL_BIAS",
	"BOT_ALIGNED",
	"BUFFER_STATE",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */
// Fucking horrible practice, but if it works it works...
int isDetectedTapeFL(void);
int isDetectedTapeFR(void);
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;

#define BOT_BRAKE_TICKS 500 // Brake the robot for half a second after alignment.

// Turning and Movements (Define here because they seem to be different)

// ***** Pivoting ***** //
// When pivoting, motor is set to the maximum
#define PIVOT_LEFT_INWARD_ML 0
#define PIVOT_LEFT_INWARD_MR MOTOR_MAX

#define PIVOT_RIGHT_INWARD_ML MOTOR_MAX
#define PIVOT_RIGHT_INWARD_MR 0

#define PIVOT_LEFT_OUTWARD_ML 0
#define PIVOT_LEFT_OUTWARD_MR -MOTOR_MAX

#define PIVOT_RIGHT_OUTWARD_ML -MOTOR_MAX
#define PIVOT_RIGHT_OUTWARD_MR 0

#define TANK_90_LEFT_OVERSHOOT_TICK 650
#define TANK_90_RIGHT_OVERSHOOT_TICK 650

#define WALL_REVERSE_TICK 500

#define LEFT_SERVO_REVERSE_TICK 250
#define AVOID_REVERSE_TICK 250

// If we have met the wall, then we know that the next tape detection is alignment with the track wire
#define WALL_MET 1
#define WALL_NOT_MET 0
unsigned int right_traversal_met_wall = WALL_NOT_MET;

// Biasing //
int source_state = InitPSubState; // This could cause problems. But this is meant to use the previous state to compare which events to detect for biasing.

#define LEFT_BIAS_ML 700
#define LEFT_BIAS_MR 1000

#define RIGHT_BIAS_ML 1000
#define RIGHT_BIAS_MR 800

#define TR_LEFT_BIAS_ML 800
#define TR_LEFT_BIAS_MR 1000

#define TR_RIGHT_BIAS_ML 1000
#define TR_RIGHT_BIAS_MR 700

#define GRADUAL_FORWARD_TICKS 2000
#define GRADUAL_TURN_FACTOR_L 600
#define GRADUAL_TURN_FACTOR_R 600

#define TRAVERSE_RIGHT_180_REVERSE_TICK 250

#define ALIGN_BUFFER_TICKS 1000
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
            nextState = INIT_REVERSE; //AVOID_FORWARD;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    // ******************** AVOIDANCE ******************** //
    case INIT_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("INIT_REVERSE \r\n");
                // Reverse the bot
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                // Initialize timer to reverse
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, TRAVERSE_RIGHT_180_REVERSE_TICK);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, resume to the avoid forward state
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    // Stop the robot
                    Robot_SetLeftMotor(0);
                    Robot_SetRightMotor(0);
                    
                    // Initialize another timer to buffer for a few seconds
                    ES_Timer_InitTimer(BUFFER_TIMER, ALIGN_BUFFER_TICKS);
                } else if (ThisEvent.EventParam == BUFFER_TIMER) {
                    nextState = AVOID_FORWARD;
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
        
    case AVOID_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("AVOID_FORWARD \r\n");
                // Move the robot forward
                Robot_SetLeftMotor(LEFT_FORWARD_MAX);
                Robot_SetRightMotor(RIGHT_FORWARD_MAX);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;

            // Put all detection events over here
            // If bumped into either a wall or obstacle, turn and continue moving forward. We want to find the tape.
            case FL_BUMPER_PRESSED:
                nextState = AVOID_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_PRESSED:
                nextState = AVOID_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            // If front tape is detected, then alignment is possible
            // Buffer state to stop the state from continuing. This allows for incremental testing...
            case FL_TAPE_DETECTED:
                nextState = ALIGN_PIVOT_LEFT_INWARD; // ALIGN_TURN_LEFT // BUFFER_STATE
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_TAPE_DETECTED:
                nextState = ALIGN_PIVOT_RIGHT_INWARD; // ALIGN_TURN_RIGHT
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
            break;
        
    case AVOID_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("AVOID_REVERSE \r\n");
                // Move the robot backwards
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // If the timeout is over, traverse to the avoid turn 90 state
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    nextState = AVOID_TURN_90_LEFT;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            // Put all detection events over here
            // When obstacle has been bumped, reverse until release, then continue to release a bit more
            case FL_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, AVOID_REVERSE_TICK);
                break;
                
            case FR_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, AVOID_REVERSE_TICK);
                break;
                
            case FLO_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, AVOID_REVERSE_TICK);
                break;
                
            case FRO_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, AVOID_REVERSE_TICK);
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
    
    case AVOID_TURN_90_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("AVOID_TURN_90_LEFT \r\n");
                // Perform a left turn to the left
                Robot_SetLeftMotor(MAX_LEFT_TURN_90_LEFT);
                Robot_SetRightMotor(MAX_LEFT_TURN_90_RIGHT);

                // Initialize a timer to track the turn time
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, TURN_90_LEFT_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After finished turning, transition back to the forward state.
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    nextState = AVOID_FORWARD;
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
    
    
        
    case BUFFER_STATE:
        // This state offers no functionality except for stopping the robot for testing purposes.
        switch (ThisEvent.EventType) {
        case ES_ENTRY:
            // Stop the robot and remain at this state
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
/**
 * Function: isTapeFL(void)
 * @param None
 * @return Whether if the front left tape is detected*/
int isDetectedTapeFL(void) {
    return (Robot_GetTapeFL() > 500);
}

int isDetectedTapeFR(void) {
    return (Robot_GetTapeFR() > 500);
}