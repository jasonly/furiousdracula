// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"
#include "Places.h"
#include "Map.h"

void decideDraculaMove(DracView gameState)
{
    
    LocationID *numLocations = malloc(sizeof(LocationID));
	//default move to ensure that a move will be made
    LocationID *moveArray = whereCanIgo(gameState,numLocations,TRUE,FALSE);
    
    int numMoves = sizeof(moveArray)/sizeof(LocationID);
    //sizeof(moveArray)/sizeof(LocationID);
    //printf("The number of locations is %d\n",numMoves);
    int moveIndex = rand() % numMoves;
    printf("I want to move to location %d\n",moveIndex);
    
    printf("The value in the moveArray is %d\n",moveArray[moveIndex]);
    LocationID Move = moveArray[moveIndex];
    
    //printf("%d\n",Move);
    
    

        registerBestPlay(idToAbbrev(Move),"I come to suck your blood");

    
}
