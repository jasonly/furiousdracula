// hunter.c
// Implementation of your "Fury of Dracula" hunter AI
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"

void decideHunterMove(HunterView gameState)
{
        if(whoAmI(gameState) == 0) registerBestPlay("KL","G KL");
        if(whoAmI(gameState) == 1) registerBestPlay("SR","S SR");
        if(whoAmI(gameState) == 2) registerBestPlay("PA","H PA");
        if(whoAmI(gameState) == 3) registerBestPlay("MU","M MU");
}
