// hunter.c
// Implementation of your "Fury of Dracula" hunter AI
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"
#include "Map.h"

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
int numLocations;
int *moveArray;
Map g;
g = newMap();
int d = numE(g,1);
printf("%d\n", d);
LocationID path[500];
TransportID trans[4];


moveArray = whereCanIgo(gameState,&numLocations,1,1,0);
int moveIndex = numLocations/2;
registerBestPlay(idToAbbrev(moveArray[moveIndex]),"Yes, we are moving!");
shortestPath(g, 19, 45, path, trans);
printf("%d",path[1]);

}
}
