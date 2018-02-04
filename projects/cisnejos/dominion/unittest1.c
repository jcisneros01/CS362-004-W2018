#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertEqual(int expected, int actual) {
    if (expected == actual) {
        printf("Test Passed\n\n");
    } else {
         printf("Test Failed\n\n");
    }
}

int main() {

    // Game init variables
    int numberOfPlayers = 2;
    int kindomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int randomSeed = 1000;
    struct gameState State;

    // print heading
    printf ("TESTING getCost():\n");

    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&State);

    // array of expected costs for each card in order
    int expectedCost[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4}; 

    // Cycle through and test each card
    for (int i = 0; i < 27; i++) {

        // get test card
        int testCard = i;

        // get test card cost
        int actualCost = getCost(testCard);

        // print card
        printf("Testing Card #: %d\n", testCard);

        // print cost
        printf("Actual Cost: %d, Expected Cost: %d\n", actualCost, expectedCost[i]);

        assertEqual(expectedCost[i], actualCost);
    }
}
