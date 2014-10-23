// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

void decideDraculaMove(DracView gameState)
{

    int round = giveMeTheRound(gameState);

    if (round == 0) 
    {
        registerBestPlay("MU","I come to suck your blood");
    } else
    {   int numLocations;
    //    printf("numLocations is %d", *numLocations);
        int * locationArray;
        locationArray = whereCanIgo(gameState,&numLocations,1, 1);
        
        int *dracTrail = calloc(sizeof(int),6);
       
        giveMeTheTrail(gameState, 4, dracTrail);
        
        int count = 0;
        while (count < 6) {
            if (dracTrail[count] == locationArray[numLocations]) {
                numLocations--;
                count = 0;
            }
            else count++;
        }
            
        registerBestPlay(idToAbbrev(locationArray[numLocations]),"hunters are poos");
    }
}
