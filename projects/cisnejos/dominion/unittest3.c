#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

void assertEqual(int expected, int actual) {
    if (expected == actual) {
        printf("Test Passed\n\n");
    } else {
         printf("Test Failed\n\n");
    }
}

int main() {

    srand(time(NULL)); // Seed Random func

    // Game init variables
    int numberOfPlayers = 2;
    int kindomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int randomSeed = 1000;
    struct gameState State;

    printf ("TESTING isGameOver():\n");

    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&State);    

    // Supply cards are not empty
    printf("Test: Game is not over when supply cards including province are not empty \n");

    assertEqual(0, isGameOver(&State));
    
    // Province Supply pile is empty 
      
        // set province card supply to 0
        State.supplyCount[province] = 0;

        printf("Test: Game is over when province Supply pile is empty\n");

        assertEqual(1, isGameOver(&State));

    // Any three Supply piles are empty
        State.supplyCount[province] = 1;

        printf("Test: Game is over when any three Supply piles are empty\n");

        // Set empty piles
        State.supplyCount[0] = 0;
        State.supplyCount[1] = 0;
        State.supplyCount[2] = 0;

        assertEqual(1, isGameOver(&State));

    return 0;
}