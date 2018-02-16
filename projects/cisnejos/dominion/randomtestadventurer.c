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

void testAdventurerCard(int player, struct gameState *post);

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
    int numberOfPlayers = rand() % (4 + 1 - 2) + 2; 
    int kindomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int randomSeed = 1000;
	struct gameState G;

	printf("Testing Card: Adventurer\n");
	printf ("RANDOM TESTS.\n");

     
	// iterate through tests
	for (int i = 0; i < 2000; i++)	 {

		// init game
    	initializeGame(numberOfPlayers,kindomCards,randomSeed,&G);  

		// generate random function inputs
		int currentPlayer = rand() % 4;

		// randomize hand
		G.deckCount[currentPlayer] = rand() % 501; 
		G.discardCount[currentPlayer] = rand() % 501; 
		G.handCount[currentPlayer] = rand() % 501; 
		
		// call test function
		testAdventurerCard(currentPlayer, &G);

	}


	return 0;
}

void testAdventurerCard(int player, struct gameState *post) {
	
}
