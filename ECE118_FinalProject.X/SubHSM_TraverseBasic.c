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
     
    // ***** Initial Avoidance ***** //
    AVOID_INIT_REVERSE,
    AVOID_FORWARD,
    AVOID_REVERSE,
    AVOID_TURN_90_LEFT,
            
    // ***** Wall Alignment ***** //
    INIT_TRAVERSE_FORWARD,
    INIT_PIVOT_WALL_LEFT,
    INIT_PIVOT_WALL_RIGHT,
    INIT_TRAVERSE_WALL_REVERSE,
    INIT_TANK_LEFT,
            
    // ***** Left Wall Follow ***** //
    LEFT_FOLLOW_WALL,
    LEFT_FOLLOW_REVERSE,
    LEFT_FOLLOW_TURN_TO_TAPE,
    LEFT_FOLLOW_RIGHT_TANK,
            
    // ***** Right Wall Follow ***** //
    RIGHT_FOLLOW_WALL,
    RIGHT_FOLLOW_REVERSE,
    RIGHT_FOLLOW_TURN_TO_TAPE,
    RIGHT_FOLLOW_TANK_LEFT,
    
    // ***** Alignment ***** //
    ALIGN_REVERSE,
    ALIGN_TURN_TO_TAPE,
    ALIGN_REAR_RIGHT_TO_TAPE,
    ALIGN_FOLLOW_TAPE,
    ALIGN_DISPENSE,
            
    BUFFER_STATE,

} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"AVOID_INIT_REVERSE",
	"AVOID_FORWARD",
	"AVOID_REVERSE",
	"AVOID_TURN_90_LEFT",
	"INIT_TRAVERSE_FORWARD",
	"INIT_PIVOT_WALL_LEFT",
	"INIT_PIVOT_WALL_RIGHT",
	"INIT_TRAVERSE_WALL_REVERSE",
	"INIT_TANK_LEFT",
	"LEFT_FOLLOW_WALL",
	"LEFT_FOLLOW_REVERSE",
	"LEFT_FOLLOW_TURN_TO_TAPE",
	"LEFT_FOLLOW_RIGHT_TANK",
	"RIGHT_FOLLOW_WALL",
	"RIGHT_FOLLOW_REVERSE",
	"RIGHT_FOLLOW_TURN_TO_TAPE",
	"RIGHT_FOLLOW_TANK_LEFT",
	"ALIGN_REVERSE",
	"ALIGN_TURN_TO_TAPE",
	"ALIGN_REAR_RIGHT_TO_TAPE",
	"ALIGN_FOLLOW_TAPE",
	"ALIGN_DISPENSE",
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

// ***** PIVOTING ***** //
#define PIVOT_LEFT_INWARD_ML 0
#define PIVOT_LEFT_INWARD_MR MOTOR_MAX

#define PIVOT_RIGHT_INWARD_ML MOTOR_MAX
#define PIVOT_RIGHT_INWARD_MR 0

#define PIVOT_LEFT_OUTWARD_ML 0
#define PIVOT_LEFT_OUTWARD_MR -MOTOR_MAX

#define PIVOT_RIGHT_OUTWARD_ML -MOTOR_MAX
#define PIVOT_RIGHT_OUTWARD_MR 0

// ***** AVOIDANCE ***** //
#define INIT_REVERSE_TICKS 250
#define INIT_BUFFER 250
#define INIT_BACK_OUT_REVERSE_TICK 250
#define INIT_TURN_90_TICKS 1000

// ***** INITIAL ALIGN ***** //
#define INIT_WALL_REVERSE_TICK 200
#define INIT_TANK_LEFT_TICK 600

// ***** LEFT FOLLOW ***** //
#define LF_BIAS_LEFT_ML 500
#define LF_BIAS_LEFT_MR 1000

#define LF_BIAS_RIGHT_ML 1000
#define LF_BIAS_RIGHT_MR 700

#define LF_REVERSE_TICK 2000
#define LF_TANK_RIGHT_TICK 1550

#define LF_HARD_LEFT_ML 500
#define LF_HARD_LEFT_MR 1000

// ***** RIGHT FOLLOW ***** //
#define RF_BIAS_LEFT_ML 850
#define RF_BIAS_LEFT_MR 1000

#define RF_BIAS_RIGHT_ML 1000
#define RF_BIAS_RIGHT_MR 500

#define RF_REVERSE_TICK 2000
#define RF_TANK_LEFT_TICK 1550

#define RF_HARD_RIGHT_ML 1000
#define RF_HARD_RIGHT_MR 500

// ******** DISPENSAL ********** //
#define DISP_VEER_LEFT_ML 750
#define DISP_VEER_LEFT_MR 1000

#define DISPENSE_REVERSE_TICK 1000
#define DISPENSAL_TICK 2000
#define PASS_TO_DISPENSE 0
int total_passes = 0;

int angle_tick_drift = 0;
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
            nextState = AVOID_FORWARD;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    
    // ********** AVOIDANCE AND FIND WALL ********** //
    case AVOID_INIT_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("AVOID_INIT_REVERSE \r\n");
                // Reverse the bot
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                // Initialize timer to reverse
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, INIT_REVERSE_TICKS);
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
                    ES_Timer_InitTimer(BUFFER_TIMER, INIT_BUFFER);
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
                Robot_SetLeftMotor(MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;

            // Put all detection events over here
            // If bumped front bumper, and obstacle is hit, ignore, but if it is, do the pivot
            case FL_BUMPER_PRESSED:
                printf("Front left bumper touched. \r\n");
                if (Robot_GetBumperFLO() == BUMPER_RELEASED) {
                    nextState = INIT_PIVOT_WALL_LEFT;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
                
            case FR_BUMPER_PRESSED:
                printf("Front right bumepr touched. \r\n");
                if (Robot_GetBumperFRO() == BUMPER_RELEASED) {
                    nextState = INIT_PIVOT_WALL_RIGHT;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
                
            // If obstacle, go to avoid state
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
            // When tape is hit, perform a 90 degree left.
            case FL_TAPE_DETECTED:
                nextState = AVOID_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_TAPE_DETECTED:
                nextState = AVOID_REVERSE;
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
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, INIT_BACK_OUT_REVERSE_TICK);
                break;
                
            case FR_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, INIT_BACK_OUT_REVERSE_TICK);
                break;
                
            case FLO_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, INIT_BACK_OUT_REVERSE_TICK);
                break;
                
            case FRO_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, INIT_BACK_OUT_REVERSE_TICK);
                break;
                
            // If tape is no longer detected, perform 90 degree turn
            case FL_TAPE_NOT_DETECTED:
                nextState = AVOID_TURN_90_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_TAPE_NOT_DETECTED:
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
                printf("AVOID_TURN_90_LEFT \r\n");
                // Perform a left turn to the left
                Robot_SetLeftMotor(MAX_LEFT_TURN_90_LEFT);
                Robot_SetRightMotor(MAX_LEFT_TURN_90_RIGHT);

                // Initialize a timer to track the turn time
                ES_Timer_InitTimer(SUB_ALIGN_TURN_TIMER, INIT_TURN_90_TICKS);
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
        
    // ********** INITIAL ALIGNMENT WITH WALL ********** //
    case INIT_TRAVERSE_FORWARD:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("INIT_FORWARD \r\n");
                
                // Move forward until either front left or bumper bumpers have been touched. Assume it is facing wall at start.
                Robot_SetLeftMotor(MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When front left or right bumper has been triggered, align based on direction.
            case FL_BUMPER_PRESSED:
                nextState = INIT_PIVOT_WALL_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_PRESSED:
                nextState = INIT_PIVOT_WALL_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case INIT_PIVOT_WALL_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("INIT_PIVOT_WALL_LEFT \r\n");
                // If the left bumper hits the wall, then pivot left inward.
                Robot_SetLeftMotor(PIVOT_LEFT_INWARD_ML);
                Robot_SetRightMotor(PIVOT_LEFT_INWARD_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;

            // Put all detection events over here
            // Pivot until rear left bumper is hit
            case FR_BUMPER_PRESSED:
                nextState = INIT_TRAVERSE_WALL_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case INIT_PIVOT_WALL_RIGHT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("INIT_PIVOT_WALL_RIGHT \r\n");
                // If the right bumper hits, pivot right outwards
                Robot_SetLeftMotor(PIVOT_RIGHT_INWARD_ML);
                Robot_SetRightMotor(PIVOT_RIGHT_INWARD_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When rear right bumper hits, 
            case FL_BUMPER_PRESSED:
                nextState = INIT_TRAVERSE_WALL_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
    
    case INIT_TRAVERSE_WALL_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("INIT_WALL_REVERSE \r\n");
                // Reverse until bumpers are no longer touched, then initialize a timer to move backwards for some time
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = INIT_TANK_LEFT;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
            
            // Reverse until either bumpers are released, then initialize a timer to continue reversal
            case FL_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, INIT_WALL_REVERSE_TICK);
                break;
                
            case FR_BUMPER_RELEASED:
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, INIT_WALL_REVERSE_TICK);
                break;
            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case INIT_TANK_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("INIT_TANK_LEFT \r\n");
                
                // Perform a left tank turn (undershoot if possible)
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                // Initialize tank based on a timer
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, INIT_TANK_LEFT_TICK);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    // Continue to left wall follow
                    nextState = LEFT_FOLLOW_WALL;
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
    // ********** LEFT WALL FOLLOWING ********** //  
    case LEFT_FOLLOW_WALL:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("LEFT_FOLLOW_WALL \r\n");
                
                // Start with a right bias
                Robot_SetLeftMotor(LF_BIAS_RIGHT_ML);
                Robot_SetRightMotor(LF_BIAS_RIGHT_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When traversing left, depending on if the front right bumper is hit or released, adjust the bias.
            case FR_BUMPER_PRESSED:
                // Pressed, so bias left
                Robot_SetLeftMotor(LF_BIAS_LEFT_ML);
                Robot_SetRightMotor(LF_BIAS_LEFT_MR);
                break;
                
            case FR_BUMPER_RELEASED:
                // Released, so bias right
                Robot_SetLeftMotor(LF_BIAS_RIGHT_ML);
                Robot_SetRightMotor(LF_BIAS_RIGHT_MR);
                break;
                
            // When the front left tape hits, this indicates it has reached the tape.
            case FR_TAPE_DETECTED:
                // Transition out to other state
                nextState = LEFT_FOLLOW_REVERSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FL_TAPE_DETECTED:
               // Stop the motor
               nextState = LEFT_FOLLOW_REVERSE;
               makeTransition = TRUE;
               ThisEvent.EventType = ES_NO_EVENT;
               break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case LEFT_FOLLOW_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("LEFT_FOLLOW_REVERSE \r\n");
                // Reverse with a left bias (since it is against the wall)
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX/2);
                
                // Initialize a timer to reverse
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, LF_REVERSE_TICK);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    // After reversal, perform a hard left.
                    nextState = LEFT_FOLLOW_TURN_TO_TAPE;
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
        
    case LEFT_FOLLOW_TURN_TO_TAPE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("LEFT_FOLLOW_TURN_TO_TAPE \r\n");
                // Perform a hard left (but not a pivot) until the front left is detected
                Robot_SetLeftMotor(LF_HARD_LEFT_ML);
                Robot_SetRightMotor(LF_HARD_LEFT_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When front right tape is detected, perform a tank turn right to reverse directions
            case FR_TAPE_DETECTED:
                nextState = LEFT_FOLLOW_RIGHT_TANK;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case LEFT_FOLLOW_RIGHT_TANK:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("LEFT_FOLLOW_RIGHT_TANK \r\n");
                // Perform a tank right turn based on a timer
                Robot_SetLeftMotor(MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                // Initialize a timer to tank turn right
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, LF_TANK_RIGHT_TICK + angle_tick_drift);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = RIGHT_FOLLOW_WALL;
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
        
    // ********** RIGHT WALL FOLLOWING ********** //  
    case RIGHT_FOLLOW_WALL:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("RIGHT_FOLLOW_WALL \r\n");
                // Initially bias to the left and use bumper events to determine bias.
                Robot_SetLeftMotor(RF_BIAS_LEFT_ML);
                Robot_SetRightMotor(RF_BIAS_LEFT_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            case FL_BUMPER_PRESSED:
                // Front left pressed, bias right
                Robot_SetLeftMotor(RF_BIAS_RIGHT_ML);
                Robot_SetRightMotor(RF_BIAS_RIGHT_MR);
                break;
                
            case FL_BUMPER_RELEASED:
                // Front left released, bias left
                Robot_SetLeftMotor(RF_BIAS_LEFT_ML);
                Robot_SetRightMotor(RF_BIAS_LEFT_MR);
                break;
                
            // When either tape events trigger, perform the reversal
            case FL_TAPE_DETECTED:
                if (total_passes >= PASS_TO_DISPENSE) {
                    // Reset total passes
                    total_passes = 0;
                    nextState = ALIGN_REVERSE;
                } else {
                    total_passes++;
                    nextState = RIGHT_FOLLOW_REVERSE;
                }
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_TAPE_DETECTED:
                if (total_passes >= PASS_TO_DISPENSE) {
                     // Reset total passes
                    total_passes = 0;
                    nextState = ALIGN_REVERSE;
                } else {
                    total_passes++;
                    nextState = RIGHT_FOLLOW_REVERSE;
                }
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case RIGHT_FOLLOW_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("RIGHT_FOLLOW_REVERSE \r\n");
                // Reverse with a right bias (since it is against the wall while in the right traversal)
                Robot_SetLeftMotor(-MOTOR_MAX/2);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                // Initialize a timer to reverse
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, RF_REVERSE_TICK);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    // After reversal, perform a hard left.
                    nextState = RIGHT_FOLLOW_TURN_TO_TAPE;
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
        
    case RIGHT_FOLLOW_TURN_TO_TAPE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("RIGHT_FOLLOW_TURN_TO_TAPE \r\n");
                // Perform a hard right (since you are traversing in the right direction)
                Robot_SetLeftMotor(RF_HARD_RIGHT_ML);
                Robot_SetRightMotor(RF_HARD_RIGHT_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When front left tape is detected, perform a tank turn left to reverse directions
            case FL_TAPE_DETECTED:
                nextState = RIGHT_FOLLOW_TANK_LEFT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case RIGHT_FOLLOW_TANK_LEFT:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("RIGHT_FOLLOW_TANK_LEFT \r\n");
                // Perform a tank left turn based on a timer
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                // Initialize a timer to tank turn right
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, RF_TANK_LEFT_TICK + angle_tick_drift);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, go back to left traversal
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    // Increment the drift value by a small amount? 50
                    //angle_tick_drift += 75;
                    nextState = LEFT_FOLLOW_WALL;
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
        
    // ********** TRACK ALIGNMENT ********** //  
    case ALIGN_REVERSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("ALIGN_REVERSE \r\n");
                // Reverse with a right bias (since it is against the wall while in the right traversal)
                Robot_SetLeftMotor(-MOTOR_MAX/2);
                Robot_SetRightMotor(-MOTOR_MAX);
                
                // Initialize a timer to reverse
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, DISPENSE_REVERSE_TICK);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    // After reversal, perform a hard left.
                    nextState = ALIGN_TURN_TO_TAPE;
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
        
    case ALIGN_TURN_TO_TAPE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("ALIGN_TURN_TO_TAPE \r\n");
                // Perform a hard right (since you are traversing in the right direction)
                Robot_SetLeftMotor(RF_HARD_RIGHT_ML);
                Robot_SetRightMotor(RF_HARD_RIGHT_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When front left tape is detected, perform a tank turn left to reverse directions
            case FL_TAPE_DETECTED:
                nextState = ALIGN_REAR_RIGHT_TO_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case ALIGN_REAR_RIGHT_TO_TAPE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("ALIGN_REAR_RIGHT_TO_TAPE \r\n");
                // Perform a tank turn left until rear right tape detector detects
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(MOTOR_MAX);
                
                // Enable servo
                Robot_SetServoEnabled(D_SERVO_INACTIVE);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // When the rear right tape hits, continue forward to the door
            case RR_TAPE_DETECTED:
                nextState = ALIGN_FOLLOW_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case ALIGN_FOLLOW_TAPE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Stick out the servo and move forward to the tape. Keep moving until bumpers have been triggered.
                // Veer to the left
                Robot_SetLeftMotor(DISP_VEER_LEFT_ML);
                Robot_SetRightMotor(DISP_VEER_LEFT_MR);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Move until bumpers have been triggered
            case FL_BUMPER_PRESSED:
                nextState = ALIGN_DISPENSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_PRESSED:
                nextState = ALIGN_DISPENSE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case ALIGN_DISPENSE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Enable the collector
                Robot_SetPropllerMode(PROPELLER_RELEASE, 500);
                
                // Start a countdown timer
                ES_Timer_InitTimer(SUB_BASIC_TRAVERSE_TURN_TIMER, DISPENSAL_TICK);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // After timeout, go back to the reverse traverse state (INIT_TRAVERSE_WALL_REVERSE)
                if (ThisEvent.EventParam == SUB_BASIC_TRAVERSE_TURN_TIMER) {
                    nextState = INIT_TRAVERSE_WALL_REVERSE;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    
                    // Re-enable propeller to be back to collect mode
                    Robot_SetPropllerMode(PROPELLER_COLLECT, 400);
                    
                    // Disable Servo
                    Robot_SetServoEnabled(D_SERVO_ACTIVE);
                }
                break;
            
            // Put all detection events over here

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case BUFFER_STATE:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("BUFFER_STATE \r\n");
                
                // Stop the motor
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

