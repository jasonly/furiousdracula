// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"
#include <string.h>

void decideDraculaMove(DracView gameState)
{
    int round = giveMeTheRound(gameState);

    if (round == 0) {
        registerBestPlay("GA","");
    } else if (round == 1){
		registerBestPlay("CD","");
	} else if (round == 2){
		registerBestPlay("KL","");
	} else if (round == 3){
		registerBestPlay("D1","");
    } else if (round == 4){
        registerBestPlay("HI","");
    } else if (round == 5){
        registerBestPlay("TP","");
    } else if (round == 6){
        registerBestPlay("TP","");
	} else {   

   
    // Populate dracTrail with last 6 moves made
    int *dracTrail = calloc(sizeof(int),6);
    giveMeTheTrail(gameState, 4, dracTrail);
    
    // === PREDETERMINE HIDE AND DOUBLE BACK ===
    // Determine if hide has been used in trail. 
    // Returns HIDING = 0 if you can't hide, and 1 if you can.
    int hideCount = 0;
    int HIDING = 0;
    int reference0 = 0;
        
    while(hideCount < 6){
        if(dracTrail[hideCount] == 102){
            hideCount++; reference0++;
        } else hideCount++; 
    }
    if (reference0 == 0) HIDING = 1;
    
    // Can't hide at sea
    if (idToType(whereIs(gameState,4)) == SEA) { printf("At sea\n"); HIDING = 0; }
    
    // Determine if double back has been used in trail. 
    // Returns BACK = 0 if you can't hide, and 1 if you can.
    int backCount = 0;
    int BACK = 0;
    int reference1 = 0;
        
    while(backCount < 6){
        if(dracTrail[backCount] == 103){
            backCount++; reference1++;
        } else backCount++; 
    }
    if (reference1 == 0) BACK = 1;
    
       // === FIND LEGAL CONNECTED LAND AND WATER CONNECTIONS === //
    
                        // == BASIC MOVES == //
    
                            // = LAND = //
        
    // Populate landArray with possible connected LAND 
    // locations from current location
	int numLocations;
    int *landArray = whereCanIgo(gameState,&numLocations,1, 0);
    int landLength = numLocations;
    
    // Works out if we have already gone through a location in our
    // trail.
    // Each location in dracTrail is compared to every
    // location in landArray. 
    // If they're the same, that entry in landArray is changed
    // to -1, meaning we cannot move there, and landLength shortened.
    int count = 0;
    int x = 0;
        
    while(x < numLocations){
        while(count < 6){
            if(dracTrail[count] == landArray[x]){
                landArray[x] = -1;
                count = 8;
                landLength--;
            }else count++;
        }
        x++;
        count = 0;
    }
    
    // Make array as big as possible LAND moves for us is.
    int *landMoves = calloc(sizeof(int),landLength);
    
    // Little loop to transfer possible LAND moves into the new array
    int a = 0; int b = 0;
    while(a < numLocations){
        if(landArray[a] != -1){
            landMoves[b] = landArray[a];
            a++;
            b++;
        } else a++;
    }
    
    printf("%d land length\n", landLength);
    
    // Register first available move (just for safety)
    registerBestPlay(idToAbbrev(landMoves[0]),"1");
    
                            // = WATER = //
        
    // Populate waterArray with possible connected WATER 
    // locations from current location
    int waterLocations;
    int *waterArray = whereCanIgo(gameState,&waterLocations,0,1);
    int waterLength = waterLocations;
        
    // Works out if we have already gone through a location in our
    // trail.
    // Each location in dracTrail is compared to every
    // location in waterArray. 
    // If they're the same, that entry in waterArray is changed
    // to -1, meaning we cannot move there, and waterLength shortened.
    count = 0; x = 0;
        
    while(x < waterLocations){
        while(count < 6){
            if(dracTrail[count] == waterArray[x]){
                waterArray[x] = -1;
                count = 8;
                waterLength--;
            } else count++;
        }
        x++;
        count = 0;
    }
    // Make array as big as possible WATER moves for us is.
    int *waterMoves = calloc(sizeof(int),waterLength);
    
    // Little loop to transfer possible WATER moves into the new array
    a = 0; b = 0;
    while(a < waterLocations){
        if(waterArray[a] != -1){
            waterMoves[b] = waterArray[a];
            a++;
            b++;
        } else a++;
    }
    
                        // = REGISTER BASIC MOVE = //
        
    // Register first available move (just for safety)
    registerBestPlay(idToAbbrev(landMoves[0]),"1");
    
    // Check if no LAND move has been registered. If it hasn't, register
    // basic water move.
    if (landLength == 0) registerBestPlay(idToAbbrev(waterMoves[0]),"2");
    
    // Check if no basic LAND or WATER move has been registered. If not,
    // hide OR double back.
    if ((landLength == 0) && (waterLength == 0)) {
        if (HIDING == 1) {
            registerBestPlay("HI","3");
        } else if ((HIDING == 0) && (BACK == 1)) {
            registerBestPlay("D1","4");
        } else registerBestPlay("TP", "5");
    }
    
                            // == COMPLEX MOVES == //
    
    // Populate the hunter arrays with the possible moves that they can make
    // - both LAND and WATER
    int *hunter0Moves; int *hunter1Moves;
    int *hunter2Moves; int *hunter3Moves;
        
    int hunter0Locations; int hunter1Locations;
    int hunter2Locations; int hunter3Locations;
        
    hunter0Moves = whereCanTheyGo(gameState,&hunter0Locations,0,TRUE,TRUE,TRUE);
    hunter1Moves = whereCanTheyGo(gameState,&hunter1Locations,1,TRUE,TRUE,TRUE);
    hunter2Moves = whereCanTheyGo(gameState,&hunter2Locations,2,TRUE,TRUE,TRUE);
    hunter3Moves = whereCanTheyGo(gameState,&hunter3Locations,3,TRUE,TRUE,TRUE);
        
    // Attempting to determine the next move by working out
    // where we have been, where we can go, and if the hunters
    // can also go there in their next move, makes us safer!

    int hunter0Count = 0; int hunter1Count = 0;
    int hunter2Count = 0; int hunter3Count = 0; int dracCount = 0;
    int safeLength = landLength; int ref = 0;
        
    // Checking whether the possible LAND moves for Dracula
    // are possible LAND moves for the hunters
    // Note: we do not follow this check for water moves because...
    // WE DON'T CARE ABOUT MATCHING WATER MOVES!
    
    // This works by changing entries in the landMoves to -1
    // when there is a risk their move will be the same as our move
    while(dracCount < landLength){
        while(hunter0Count < hunter0Locations){
            if(hunter0Moves[hunter0Count] == landMoves[dracCount]){
            	landMoves[dracCount] = -1;                    
				dracCount++;
                hunter0Count = hunter0Locations; hunter1Count = hunter1Locations;
                hunter2Count = hunter2Locations; hunter3Count = hunter3Locations;
			    safeLength--;
            }else hunter0Count++;
        }
        while(hunter1Count < hunter1Locations){
            if(hunter1Moves[hunter1Count] == landMoves[dracCount]){
	        	landMoves[dracCount] = -1;                    
                dracCount++;
                hunter1Count = hunter1Locations; hunter2Count = hunter2Locations;
                hunter3Count = hunter3Locations;

			    safeLength--;
            }else hunter1Count++;
        }
        while(hunter2Count < hunter2Locations){
            if(hunter2Moves[hunter2Count] == landMoves[dracCount]){
	        	landMoves[dracCount] = -1;                 
                dracCount++;
                hunter2Count = hunter2Locations; hunter3Count = hunter3Locations;
				safeLength--;
                }else hunter2Count++;
            }
        while(hunter3Count < hunter3Locations){
            if(hunter3Moves[hunter3Count] == landMoves[dracCount]){
		        landMoves[dracCount] = -1;                
                dracCount++;
                hunter3Count = hunter3Locations;
				safeLength--;
            }else hunter3Count++;
        }
        //reset the counters, and if the dracCount hasn't already been incremented during the movement,
        hunter0Count = 0; hunter1Count = 0; hunter2Count = 0; hunter3Count = 0;
        if(dracCount == ref){
	    	dracCount++;
        }
        ref++;
    }
    
    // After changing the move list to the -1s, we must create a new array
    // of possible safe moves we can make.
    
    // Make array as big as possible SAFE LAND moves for us is.
    int *safeMoves = calloc(sizeof(int), safeLength);
    
    // Little loop to transfer possible SAFE LAND moves into the new array
    a = 0; b = 0;
    while(a < landLength){
        if(landMoves[a] != -1){
            safeMoves[b] = landMoves[a];
            a++;
            b++;
        } else a++;
    }
        printf("Number of Safe Moves: %d\n",safeLength);
        printf("Number of Water Moves: %d\n",waterLength);
                    // == REGISTER A SAFE MOVE == //
    if (safeLength > 0) registerBestPlay(idToAbbrev(safeMoves[0]),"7");
    
                        // == SMART MOVES == //
    if (safeLength == 0){
        // If greater than 20 health, move towards them anyway
        // (make a safe move next round if available)
        if((howHealthyIs(gameState,4) > 20) && (waterLength > 0)) {
                registerBestPlay(idToAbbrev(waterMoves[0]),"8");
        // If less than 20, try hiding or double backing.
        } else {
            if(HIDING == 1) {
                registerBestPlay("HI","9");
            } else if ((HIDING == 0) && (BACK == 1)) {
                registerBestPlay("D1","10");
            }
        }
    }
    
                        // == LAST RESORT MOVES == //
    // No moves available, TP 
    if ((landLength == 0) && (waterLength == 0)) {
        if (HIDING == 1) {
            registerBestPlay("HI","11");
        } else if ((HIDING == 0) && (BACK == 1)) {
            registerBestPlay("D1","12");
        } else registerBestPlay("TP", "13");
    }
    
    }

}
