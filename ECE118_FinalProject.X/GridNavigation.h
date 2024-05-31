/* 
 * File:   GridNavigation.h
 * Author: derri
 *
 * Created on May 28, 2024, 6:09 PM
 */

#ifndef GRIDNAVIGATION_H
#define	GRIDNAVIGATION_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#include "ES_Timers.h"

// ***** GRID ***** //
#define GRID_SIZE_X 8
#define GRID_SIZE_Y 6

// Last value traversed, so in case obstacle collision occurs, we can reverse the same amount
extern int grid_last_traversed_time;

// ***** PATH DATATYPES ***** //
typedef enum {
    NODE_SAFE,
    NODE_OBSTACLE,
    NODE_UNKNOWN,
} NodeStatus;


/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/
/**
 * @Function GridNav_Init()
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Initializes the grid for use, only do this a single time, this is not an object. Do not reuse
 * @author Derrick Lai */
char GridNav_Init();


/**
 * @Function GridNav_SetNode(int x, int y, int nodeStatus)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Sets a node of a grid given the coordinate to its status of safe, obstacle, or unknown
 * @author Derrick Lai */
char GridNav_SetNode(int x, int y, int nodeStatus);

/**
 * @Function GridNav_FindPath(int start_x, int start_y, int target_x, int target_y);
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Uses A* pathfinding to find the shortest path from start to target destination node.
 * @author Derrick Lai */
char GridNav_FindPath(int start_x, int start_y, int target_x, int target_y, int waypoints[]);

#endif	/* GRIDNAVIGATION_H */

