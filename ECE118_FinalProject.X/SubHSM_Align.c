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
       
    AVOID_FORWARD,
    AVOID_REVERSE,
    AVOID_TURN_90_LEFT,

    ALIGN_TURN_LEFT,
    ALIGN_TURN_RIGHT,
    ALIGN_TURN_90_LEFT,

    TRAVERSE_LEFT_FORWARD,
    TRAVERSE_LEFT_90_LEFT,

    TRAVERSE_RIGHT_REVERSE,
    TRAVERSE_RIGHT_TURN_180_LEFT,
    TRAVERSE_RIGHT_FORWARD,
    TRAVERSE_RIGHT_TURN_90_RIGHT,
    TRAVERSE_RIGHT_TURN_90_LEFT,

    BOT_ALIGNED,         
    BUFFER_STATE,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"AVOID_FORWARD",
	"AVOID_REVERSE",
	"AVOID_TURN_90_LEFT",
	"ALIGN_TURN_LEFT",
	"ALIGN_TURN_RIGHT",
	"ALIGN_TURN_90_LEFT",
	"TRAVERSE_LEFT_FORWARD",
	"TRAVERSE_LEFT_90_LEFT",
	"TRAVERSE_RIGHT_REVERSE",
	"TRAVERSE_RIGHT_TURN_180_LEFT",
	"TRAVERSE_RIGHT_FORWARD",
	"TRAVERSE_RIGHT_TURN_90_RIGHT",
	"TRAVERSE_RIGHT_TURN_90_LEFT",
	"BOT_ALIGNED",
	"BUFFER_STATE",
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

#define BOT_BRAKE_TICKS 500 // Brake the robot for half a second after alignment.

// Turning and Movements (Define here because they seem to be different)

// ***** Pivoting ***** //
// When pivoting, motor is set to the maximum
#define PIVOT_LEFT_TICKS 1200 // Time to perform a left pivot turn
#define PIVOT_RIGHT_TICKS 1100 // Time to perform a right pivot turn

#define PIVOT_LEFT_MOTOR_LEFT MOTOR_MAX
#define PIVOT_LEFT_MOTOR_RIGHT 0

#define PIVOT_RIGHT_MOTOR_LEFT 0
#define PIVOT_RIGHT_MOTOR_RIGHT MOTOR_MAX

// If we have met the wall, then we know that the next tape detection is alignment with the track wire
#define WALL_MET 1
#define WALL_NOT_MET 0
unsigned int right_traversal_met_wall = WALL_NOT_MET;
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
            nextState = AVOID_FORWARD;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    // ******************** AVOIDANCE ******************** //
    case AVOID_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
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
              
             // Uncomment this when your obstacle bumeprs are installed...
            case FLO_BUMPER_PRESSED:
                nextState = AVOID_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FRO_BUMPER_PRESSED:
                nextState = AVOID_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            // If front tape is detected, then alignment is possible
            // Buffer state to stop the state from continuing. This allows for incremental testing...
            case FL_TAPE_DETECTED:
                nextState = ALIGN_TURN_LEFT; // ALIGN_TURN_LEFT // BUFFER_STATE
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_TAPE_DETECTED:
                nextState = ALIGN_TURN_RIGHT; // ALIGN_TURN_RIGHT
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
                // Move the robot backwards
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;

            // Put all detection events over here
            case FL_BUMPER_RELEASED:
                nextState = AVOID_TURN_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_RELEASED:
                nextState = AVOID_TURN_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FLO_BUMPER_RELEASED:
                nextState = AVOID_TURN_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FRO_BUMPER_RELEASED:
                nextState = AVOID_TURN_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
    
    case AVOID_TURN_90_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
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
        
    // ******************** ALIGNMENT ******************** //
    case ALIGN_TURN_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Pivot the left wheel
                Robot_SetLeftMotor(0); // PIVOT_RIGHT_MOTOR_LEFT
                Robot_SetRightMotor(1000); // PIVOT_RIGHT_MOTOR_RIGHT
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Pivot until the front right tape has been detected, then perform 90 degree turn
            case FR_TAPE_DETECTED:
                nextState = ALIGN_TURN_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case ALIGN_TURN_RIGHT:\
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a left reverse pivot until front left tape is detected
                Robot_SetLeftMotor(1000); // -MOTOR_MAX + 100
                Robot_SetRightMotor(0); // -MOTOR_MAX)
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When front left tape is detected, consider it aligned
            case FL_TAPE_DETECTED:
                nextState = ALIGN_TURN_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case ALIGN_TURN_90_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // At this stage, start with traversing the left direction. Begin with a left turn.
                
                // Perform a pivot left turn to the left
                Robot_SetLeftMotor(-1000);
                Robot_SetRightMotor(0);

                // Initialize a timer to track the turn time
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, 1250);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, begin the forward side traversal
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    nextState = TRAVERSE_LEFT_FORWARD; // TRAVERSE_LEFT_FORWARD
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
        
    // ******************** LEFT TRAVERSAL ******************** //
    case TRAVERSE_LEFT_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move forward
                Robot_SetLeftMotor(LEFT_FORWARD_MAX);
                Robot_SetRightMotor(RIGHT_FORWARD_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // If the front left tape is detected, perform a 90 degree left turn.
            case FL_TAPE_DETECTED:
                nextState = TRAVERSE_LEFT_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            // If an obstacle is detected (obstacle bumper, then transition to right turn.)
            case FLO_BUMPER_PRESSED:
                nextState = TRAVERSE_RIGHT_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FRO_BUMPER_PRESSED:
                nextState = TRAVERSE_RIGHT_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                   
            // If it is a bumper, it may be an obstacle, so check that the obstacle bumper isn't also triggered.
            // If it isn't the obstacle, then assumed it has reached the track wire.
            case FL_BUMPER_PRESSED:
                if (Robot_GetBumperFLO() == BUMPER_RELEASED) {
                    nextState = BOT_ALIGNED;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
                
            case FR_BUMPER_PRESSED:
                if (Robot_GetBumperFRO() == BUMPER_RELEASED) {
                    nextState = BOT_ALIGNED;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
                
            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case TRAVERSE_LEFT_90_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a left pivot turn
                Robot_SetLeftMotor(-1000); // MAX_LEFT_TURN_90_LEFT
                Robot_SetRightMotor(1000); // MAX_LEFT_TURN_90_RIGHT

                // Initialize a timer to track the turn time
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, 600); // TURN_90_LEFT_TICKS
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, perform transition back to the forward state
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    nextState = TRAVERSE_LEFT_FORWARD;
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
        
    // ******************** RIGHT TRAVERSAL ******************** //
    case TRAVERSE_RIGHT_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Start reversing the robot
                Robot_SetLeftMotor(LEFT_REVERSE_MAX);
                Robot_SetRightMotor(RIGHT_REVERSE_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Keep reversing until obstacle bumpers are no longer active.
            case FLO_BUMPER_RELEASED:
                nextState = TRAVERSE_RIGHT_TURN_180_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FRO_BUMPER_RELEASED:
                nextState = TRAVERSE_RIGHT_TURN_180_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            // Add rear bumper events for guarding, but if this happens, there is a problem with your state machine...

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case TRAVERSE_RIGHT_TURN_180_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a full 180 tank turn
                Robot_SetLeftMotor(MAX_LEFT_TURN_90_LEFT);
                Robot_SetRightMotor(MAX_LEFT_TURN_90_RIGHT);

                // Initialize a timer to track the turn time, try doubling the time of the 90 degrees timer.
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, TURN_90_LEFT_TICKS << 1);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, transition to the the forward stage of right traversal
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    nextState = TRAVERSE_RIGHT_FORWARD;
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
        
    case TRAVERSE_RIGHT_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move forward
                Robot_SetLeftMotor(LEFT_FORWARD_MAX);
                Robot_SetRightMotor(RIGHT_FORWARD_MAX);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // If front right tape is detected, or the front left/right bottom bumpers are detected, turn right to follow tape
            // If the wall has been touched, then the next tape collision could lead to the track wire.
            case FL_TAPE_DETECTED:
                // If the wall has already been met, then assume alignment after 90' left. Otherwise, perform a 90' right turn.
                if (right_traversal_met_wall == WALL_MET) {
                    nextState = TRAVERSE_RIGHT_TURN_90_LEFT;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                } else {
                    nextState = TRAVERSE_RIGHT_TURN_90_RIGHT;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // If bottom bumpers are pressed, check if obstacle? Not sure, because right traversal assumes obstacle has been met.
            // If such bumpers are pressed, assume that it has met the wal, to next time is the track?
            case FL_BUMPER_PRESSED:
                right_traversal_met_wall = WALL_MET;
                nextState = TRAVERSE_RIGHT_TURN_90_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_PRESSED:
                right_traversal_met_wall = WALL_MET;
                nextState = TRAVERSE_RIGHT_TURN_90_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case TRAVERSE_RIGHT_TURN_90_RIGHT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a right pivot turn
                Robot_SetLeftMotor(PIVOT_RIGHT_MOTOR_LEFT);
                Robot_SetRightMotor(PIVOT_RIGHT_MOTOR_RIGHT);
                
                // Initialize a timer to keep track of turn time
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, PIVOT_RIGHT_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // When timed out, transition back to the forward state
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    nextState = TRAVERSE_RIGHT_FORWARD;
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
        
    case TRAVERSE_RIGHT_TURN_90_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a left pivot turn
                Robot_SetLeftMotor(PIVOT_LEFT_MOTOR_LEFT);
                Robot_SetRightMotor(PIVOT_LEFT_MOTOR_RIGHT);

                // Initialize a timer to track the turn time.
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, PIVOT_LEFT_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // When timed out, assumed the robot is aligned
                if (ThisEvent.EventParam == SUB_ALIGN_TURN_TIMER) {
                    nextState = BOT_ALIGNED;
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
        
    case BOT_ALIGNED:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Stop the robot
                Robot_SetLeftMotor(0);
                Robot_SetRightMotor(0);
                
                // Initialize a timer to brake the robot for a bit
                ES_Timer_InitTimer(GENERIC_BRAKE_TIMER, BOT_BRAKE_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // When timed out, make no state transitions, but post an event to move to the next state.
                // This will not work, it seems like you need a top level event.
                if (ThisEvent.EventParam == GENERIC_BRAKE_TIMER) {
                    ThisEvent.EventType = TRAP_DOOR_LOCATED;
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

