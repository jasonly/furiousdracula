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
        registerBestPlay("MU","I come to start in the middle of the board");
    } else
    {   int numLocations;
        int *locationArray;
        locationArray = whereCanIgo(gameState,&numLocations,1, 0);

        int *dracTrail = calloc(sizeof(int),6);
       
        giveMeTheTrail(gameState, 4, dracTrail);
        
        //this but works out if we have already gone through a place in our
        //trail, meaning that we do not get disqualified
        int count = 0;
        int Move = 0;
        int i = 0;
        int possLength = 0;
        int x = numLocations;
        while(i < numLocations){
             while (count < 6) {
                 if (dracTrail[count] == locationArray[x]) {
                     locationArray[x] = -1;
                     x--;
                     count = 0;
                 }else count++;
             }
            Move = locationArray[x];
            possLength++;
            x--;
            i++;
        }
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
        a = 0; b = 0;
        int c = 0; int d = 0; int e = 0;
        int ref = e;
        
        //checking whether the possible moves for Dracula are possible moves for the hunters
        while(e < possLength){
            while(a < hunter0Locations){
                if(hunter0Moves[a] == possibleMoves[e]){
                    e++;
                    a = hunter0Locations;
                }else a++;
            }
            while(b < hunter1Locations){
                if(hunter1Moves[b] == possibleMoves[e]){
                    e++;
                    b = hunter1Locations;
                }else b++;
            }
            while(c < hunter2Locations){
                if(hunter2Moves[c] == possibleMoves[e]){
                    e++;
                    c = hunter2Locations;
                }else c++;
            }
            while(d < hunter3Locations){
                if(hunter3Moves[d] == possibleMoves[e]){
                    e++;
                    d = hunter3Locations;
                }else d++;
            }
            if((d == hunter3Locations) && (ref == e)){
                registerBestPlay(idToAbbrev(possibleMoves[e]),"What a Clever Move");
            }
            a = 0; b = 0; c = 0; d = 0;
            e++;
            ref = e;
        }
        if(e == possLength) registerBestPlay(idToAbbrev(Move),"Well this is unfortunate");

    
    }
    
    
}
