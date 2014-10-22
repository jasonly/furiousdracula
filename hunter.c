// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"

void decideHunterMove(HunterView gameState)
{
    if(giveMeTheRound(gameState) == 0){
        if(whoAmI(gameState) == 0){
            registerBestPlay("KL","G KL");
        }
        if(whoAmI(gameState) == 1){
            registerBestPlay("SR","Strasbourg"); // messages could be to long
        }
        if(whoAmI(gameState) == 2){
            registerBestPlay("PA","Paris");
        }
        if(whoAmI(gameState) == 3){
            registerBestPlay("MU","Munich");
        }
        
    }else{
        int *numLocations = NULL;
        int * locationArray;
        locationArray = whereCanIgo(gameState,numLocations,1, 1, 1);
        registerBestPlay(idToAbbrev(locationArray[1]),"going");
    }
}
