// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "DracView.h"
#include "Places.h"
#include "Map.h"

void decideDraculaMove(DracView gameState)
{
    /* things we can do:
       - giveMeTheRound(gameState);
       - giveMeTheScore(gameState);
       - howHealthyIs(gameState, player);
       - whereIs(gameState, player);
       - lastMove(gameState, player, *start, *end);
       - whatsThere(gameState, where, *numTraps, *numVamps);
       - giveMeTheTrail(gameState, player, trail[TRAIL_SIZE]);
       - *whereCanIgo(gameState, *numLocations, road, sea);
    */
       
    LocationID *numLocations = malloc(sizeof(LocationID));
    
    LocationID *moveArray = whereCanIgo(gameState,numLocations,TRUE,FALSE);
    
    int numMoves = sizeof(moveArray)/sizeof(LocationID);
    time_t t;
   
    /* Intializes random number generator */
    srand((unsigned) time(&t));

    int moveIndex = rand() % numMoves;
    printf("I want to move to location %d\n",moveIndex);
    
    printf("The value in the moveArray is %d\n",moveArray[moveIndex]);
    LocationID Move = moveArray[moveIndex];
    
    //printf("%d\n",Move);
    
    

    registerBestPlay(idToAbbrev(Move),"I come to suck your blood");

    
}
