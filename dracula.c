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
        registerBestPlay("CD","I come to start in the middle of the board");
    } else
    {   int numLocations;
        int *locationArray;
        locationArray = whereCanIgo(gameState,&numLocations,1, 0);
        printf("Number of places around me: %d\n",numLocations);
        printf("%d\n",locationArray[0]);
        
        int *dracTrail = calloc(sizeof(int),6);
       
        giveMeTheTrail(gameState, 4, dracTrail);
        
        //this but works out if we have already gone through a place in our
        //trail, meaning that we do not get disqualified
        int count = 0;
        int Move = locationArray[0];
        //int i = 0;
        int possLength = 0;
        int x = 0;
        //int reference = 0;
        
        while(x < numLocations){
            while(count < 6){
                if(dracTrail[count] == locationArray[x]){
                    locationArray[x] = -1;
                    count = 8;
                }else count++;
            }
            if(count == 6){
                Move = locationArray[x];
            }
            x++;
            count = 0;
        }
        /*
        while(i < numLocations){
             while (count < 6) {
                 if (dracTrail[count] == locationArray[x]) {
                     locationArray[x] = -1;
                     x--;
                     count = 0;
                 }else count++;
             }
            if(reference == 0){
                Move = locationArray[x];
                reference++;
            }
            possLength++;
            x--;
            i++;
        }*/
        
        printf("I think my best move will be: %d\n",Move);
        registerBestPlay(idToAbbrev(Move),"Ooh, wasn't that well thought out");
        
        //attempting to determine the next move by working out
        //where we have been, where we can go, and if the hunters
        //can also go there in their next move, makes us safer!
        int *possibleMoves = calloc(sizeof(int),possLength);
        int *hunter0Moves; int *hunter1Moves;
        int *hunter2Moves; int *hunter3Moves;
        
        int hunter0Locations; int hunter1Locations;
        int hunter2Locations; int hunter3Locations;
        
        //populate the arrays with the possible moves that the hunters can make
        hunter0Moves = whereCanTheyGo(gameState,&hunter0Locations,0,TRUE,TRUE,TRUE);
        hunter1Moves = whereCanTheyGo(gameState,&hunter1Locations,1,TRUE,TRUE,TRUE);
        hunter2Moves = whereCanTheyGo(gameState,&hunter2Locations,2,TRUE,TRUE,TRUE);
        hunter3Moves = whereCanTheyGo(gameState,&hunter3Locations,3,TRUE,TRUE,TRUE);
        
        //little loop to transfer possible moves into the new array
        int a = 0; int b = 0;
        while(a < numLocations){
            if(locationArray[a] != -1){
                possibleMoves[b] = locationArray[a];
                a++;
                b++;
            }else a++;
        }
        
        int hunter0Count = 0; int hunter1Count = 0;
        int hunter2Count = 0; int hunter3Count = 0; int dracCount = 0;
        int ref = dracCount;
        
        //checking whether the possible moves for Dracula are possible moves for the hunters
        while(dracCount < possLength){
            while(hunter0Count < hunter0Locations){
                if(hunter0Moves[hunter0Count] == possibleMoves[dracCount]){
                    dracCount++;
                    a = hunter0Locations;
                }else hunter0Count++;
            }
            while(hunter1Count < hunter1Locations){
                if(hunter1Moves[hunter1Count] == possibleMoves[dracCount]){
                    dracCount++;
                    hunter1Count = hunter1Locations;
                }else hunter1Count++;
            }
            while(hunter2Count < hunter2Locations){
                if(hunter2Moves[hunter2Count] == possibleMoves[dracCount]){
                    dracCount++;
                    hunter2Count = hunter2Locations;
                }else hunter2Count++;
            }
            while(hunter3Count < hunter3Locations){
                if(hunter3Moves[hunter3Count] == possibleMoves[dracCount]){
                    dracCount++;
                    hunter3Count = hunter3Locations;
                }else hunter3Count++;
            }
            if((hunter3Count == hunter3Locations - 1) && (ref == dracCount)){
                registerBestPlay(idToAbbrev(possibleMoves[dracCount]),"What a Clever Move");
            }
            hunter0Count = 0; hunter1Count = 0; hunter2Count = 0; hunter3Count = 0;
            if(ref == dracCount){
                dracCount++;
                ref = dracCount;
            }
        }
        if(dracCount == possLength) registerBestPlay(idToAbbrev(Move),"Well this is unfortunate");

    
        
    }
    
    
}
