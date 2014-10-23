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
   
     LocationID *numLocations = malloc(sizeof(LocationID));
     LocationID *moveArray = whereCanIgo(gameState,numLocations,1,1, 1);

     int moveIndex = 54;
     printf("I want to move to location %d\n",moveIndex);
     printf("The value in the moveArray is %d\n",moveArray[moveIndex]);
     LocationID Move = moveArray[moveIndex];
      //printf("%d\n",Move);
     registerBestPlay(idToAbbrev(Move),"moving");
                                     
     }
}
