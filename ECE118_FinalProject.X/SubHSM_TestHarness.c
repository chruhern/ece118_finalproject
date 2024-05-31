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
#include "SubHSM_TestHarness.h"

#include "Robot.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    ForwardTape,
    ReverseTape,
    ForwardBumper,
    ReverseBumper,
    ForwardCalibration,
    ReverseCalibration,
    TurnLeftCalibration,
    TurnRightCalibration,
            
    ForwardLeftBias,
    ForwardRightBias,
    BrakeRobot,
            
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"ForwardTape",
	"ReverseTape",
	"ForwardBumper",
	"ReverseBumper",
	"ForwardCalibration",
	"ReverseCalibration",
	"TurnLeftCalibration",
	"TurnRightCalibration",
	"ForwardLeftBias",
	"ForwardRightBias",
	"BrakeRobot",
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

unsigned int stop_timer_initialized = 0;
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
uint8_t InitHarnessSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunHarnessSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunHarnessSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This state is purely used as a test harness to test whether if the robot works for basic states.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 */
ES_Event RunHarnessSubHSM(ES_Event ThisEvent)
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
            nextState = ForwardTape; // Set this to the state you want to test out
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
        
    case ForwardLeftBias:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move robot, but bias to the left
                Robot_SetLeftMotor(980);
                Robot_SetRightMotor(1000);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            case FR_TAPE_NOT_DETECTED:
                nextState = ForwardRightBias;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FL_TAPE_DETECTED:
                // Stop the robot
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                    

            case ES_NO_EVENT:
            default:
                break;
            }
        break;

    case ForwardRightBias:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move forward, but bias to the right
                Robot_SetLeftMotor(1000);
                Robot_SetRightMotor(985);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            case FR_TAPE_DETECTED:
                nextState = ForwardLeftBias;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FL_TAPE_DETECTED:
                // Stop the robot
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
            
    case ForwardTape: // in the first state, replace this with correct names
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Make the robot move forward
                Robot_SetLeftMotor(0); // LEFT_FORWARD_MAX
                Robot_SetRightMotor(0); // RIGHT_FORWARD_MAX
                
                // Move the propeller
                Robot_SetPropllerMode(0);
                
                
                // Initialize a timer
                //ES_Timer_InitTimer(SUB_HARNESS_TEST_TIMER, ROBOT_STOP_BUFFER_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here. Check for all tape statuses
//            case FL_TAPE_DETECTED:
//                nextState = BrakeRobot;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//                break;
//                
//            case FR_TAPE_DETECTED:
//                nextState = BrakeRobot;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
    
    case ReverseTape:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Make the robot move the opposite direction
                Robot_SetLeftMotor(LEFT_REVERSE_MAX);
                Robot_SetRightMotor(RIGHT_REVERSE_MAX);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == SUB_HARNESS_TEST_TIMER) {
                    // Reset the timer status
                    stop_timer_initialized = 0;
                    
                    // Stop timer
                    //ES_Timer_StopTimer(SUB_HARNESS_TEST_TIMER);
                    
                    nextState = BrakeRobot;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }                
                break;
            
            // Put all detection events over here
            case RL_TAPE_DETECTED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
//                if (!stop_timer_initialized) {
//                    // Stop the robot, initialize a new timer
//                    Robot_SetLeftMotor(0);
//                    Robot_SetRightMotor(0);
//                    ES_Timer_InitTimer(SUB_HARNESS_TEST_TIMER, ROBOT_STOP_BUFFER_TICKS);
//                    
//                    // Set status to true
//                    stop_timer_initialized = 1;
//                }
                
            case RR_TAPE_DETECTED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
//                if (!stop_timer_initialized) {
//                    // Stop the robot, initialize a new timer
//                    Robot_SetLeftMotor(0);
//                    Robot_SetRightMotor(0);
//                    ES_Timer_InitTimer(SUB_HARNESS_TEST_TIMER, ROBOT_STOP_BUFFER_TICKS);
//                    
//                    // Set status to true
//                    stop_timer_initialized = 1;
//                }
                
            case ES_NO_EVENT:
            default:
                break;
            }
        break;

    case ForwardBumper:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move forward
                Robot_SetLeftMotor(0);
                Robot_SetRightMotor(0);
                
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            case FL_BUMPER_PRESSED:
                //Robot_SetServoEnabled(D_SERVO_ACTIVE);
                nextState = ForwardBumper;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_PRESSED:
                //Robot_SetServoEnabled(D_SERVO_ACTIVE);
                nextState = ForwardBumper;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FL_BUMPER_RELEASED:
                //Robot_SetServoEnabled(D_SERVO_INACTIVE);
                nextState = ForwardBumper;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_BUMPER_RELEASED:
                //Robot_SetServoEnabled(D_SERVO_INACTIVE);
                nextState = ForwardBumper;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case ReverseBumper:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Make the robot move the opposite direction
                Robot_SetLeftMotor(-MOTOR_MAX);
                Robot_SetRightMotor(-MOTOR_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            case RL_BUMPER_PRESSED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case RR_BUMPER_PRESSED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;    

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
     
    // Calibration (to allow for as precise as possible forward, reverse, turn left and right movements)
    case ForwardCalibration:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move the robot forward based on the calibrated speed
                Robot_SetLeftMotor(LEFT_FORWARD_MAX);
                Robot_SetRightMotor(RIGHT_FORWARD_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // No state transition, purely for calibration. Stop the motors when finished.
            case FL_TAPE_DETECTED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case FR_TAPE_DETECTED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
//            case FL_BUMPER_PRESSED:
//                nextState = BrakeRobot;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//                break;
//                
//            case FR_BUMPER_PRESSED:
//                nextState = BrakeRobot;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//                break;

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case ReverseCalibration:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Move the robot backwards based on the calibrated speed
                Robot_SetLeftMotor(LEFT_REVERSE_MAX);
                Robot_SetRightMotor(RIGHT_REVERSE_MAX);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                break;
            
            // Put all detection events over here
            // Stop movement upon detection, no transition
            case RL_TAPE_DETECTED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case RR_TAPE_DETECTED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case RL_BUMPER_PRESSED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            case RR_BUMPER_PRESSED:
                nextState = BrakeRobot;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                

            case ES_NO_EVENT:
            default:
                break;
            }
        break;
        
    case TurnLeftCalibration:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a left tank turn
                Robot_SetLeftMotor(-MOTOR_MAX); // MAX_LEFT_TURN_90_LEFT
                Robot_SetRightMotor(MOTOR_MAX); // MAX_LEFT_TURN_90_RIGHT
                
                // Initialize timer for left turn
                //ES_Timer_InitTimer(SUB_HARNESS_TEST_TIMER, TURN_90_LEFT_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // Once timeout occurs, stop the motors
                if (ThisEvent.EventParam == SUB_HARNESS_TEST_TIMER) {
                    nextState = BrakeRobot;
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
        
    case TurnRightCalibration:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Perform a right tank turn
                Robot_SetLeftMotor(MOTOR_MAX); // MAX_RIGHT_TURN_90_LEFT
                Robot_SetRightMotor(-MOTOR_MAX); // MAX_RIGHT_TURN_90_RIGHT
                
                // Initialize timer for right turn time
                //ES_Timer_InitTimer(SUB_HARNESS_TEST_TIMER, TURN_90_RIGHT_TICKS);
                break;

            case ES_EXIT:
                break;

            case ES_TIMEOUT:
                // Once timeout occurs, stop the motors
                if (ThisEvent.EventParam == SUB_HARNESS_TEST_TIMER) {
                    nextState = BrakeRobot;
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
    
    case BrakeRobot:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // Stop the robot from moving, nothing comes after this state
                Robot_SetLeftMotor(0);
                Robot_SetRightMotor(0);
                
                //Robot_SetServoEnabled(D_SERVO_ACTIVE);
                
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
        RunHarnessSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunHarnessSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

