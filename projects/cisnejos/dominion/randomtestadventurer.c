#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void assertEqual(int expected, int actual) {
    if (expected == actual) {
        printf("Test Passed\n\n");
    } else {
         printf("Test Failed\n\n");
    }
}

void testAdventurerCard(int player, struct gameState *post) {

}

int main() {

	srand(time(NULL));
	
	// card variables
	int card = adventurer;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int bonus = 0;

     // Game init variables
    int numberOfPlayers = 2;
    int kindomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int randomSeed = 1000;
	struct gameState G;

	printf("Testing Card: Adventurer\n");
	printf ("RANDOM TESTS.\n");

    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&G);    

	// iterate through tests
	for (int i = 0; i < 2000; i++)	 {

		// randomly init game state
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}

		// generate random function inputs
		int currentPlayer = floor(Random() * 2);

		// randomize hand
		G.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		G.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		G.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		
		
		// call test function
		testAdventurerCard(currentPlayer, &G);

	}


	return 0;
}