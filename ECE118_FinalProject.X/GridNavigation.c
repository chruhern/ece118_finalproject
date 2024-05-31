/*
 * File:   GridNavigation.c
 * Author: derri
 *
 * Created on May 28, 2024, 6:19 PM
 */

/*******************************************************************************
* #INCLUDES *
******************************************************************************/
// Internal PIC32
#include "xc.h"
#include <stdio.h>
#include <Board.h>

/*******************************************************************************
* #DEFINES *
******************************************************************************/

unsigned int GetManhattanDistance(int start_x, int start_y, int target_x, int target_y);
void GetAdjacentNodes(unsigned int start_x, unsigned int start_y, int result[]);
/*******************************************************************************
* PUBLIC FUNCTION IMPLEMENTATIONS *
******************************************************************************/
/**
 * @Function GridNav_Init()
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Initializes the grid for use, only do this a single time, this is not an object. Do not reuse
 * @author Derrick Lai */
char GridNav_Init() {
    
    return SUCCESS;
}


/**
 * @Function GridNav_SetNode(int x, int y, int nodeStatus)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Sets a node of a grid given the coordinate to its status of safe, obstacle, or unknown
 * @author Derrick Lai */
char GridNav_SetNode(int x, int y, int nodeStatus) {
    
    return SUCCESS;
}

/**
 * @Function GridNav_FindPath(int start_x, int start_y, int target_x, int target_y);
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Uses A* pathfinding to find the shortest path from start to target destination node. Provides an array of waypoints.
 * @author Derrick Lai */
char GridNav_FindPath(int start_x, int start_y, int target_x, int target_y, int waypoints[]) {
    
    return SUCCESS;
}

/*******************************************************************************
* Private FUNCTION IMPLEMENTATIONS *
******************************************************************************/
/**
 * @Function GridNav_GetManhattanDistance(int start_x, int start_y, int target_x, int target_y);
 * @param None
 * @return SUCCESS or ERROR
 * @brief  Calculates the Manhattan distance given the start and end nodes.
 * @author Derrick Lai */
unsigned int GetManhattanDistance(int start_x, int start_y, int target_x, int target_y) {
    // Weird fucking bit hack thing to get the absolute value:
    // https://stackoverflow.com/questions/9772348/get-absolute-value-without-using-abs-function-nor-if-statement
    
    // Calculate the differences
    int delta_x = target_x - start_x;
    int delta_y = target_y - target_x;
    
    // Mask bit thing
    int const mask_x = delta_x >> sizeof(int) * 8 - 1; // 8 is the bits in a char
    int const mask_y = delta_y >> sizeof(int) * 8 - 1;
    
    unsigned int res_x = (delta_x + mask_x) ^ mask_x;
    unsigned int res_y = (delta_y + mask_y) ^ mask_y;
    
    // The Manhattan distance is the sum of the absolute distances
    return (res_x + res_y);
    
}