#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void assertEqual(int expected, int actual) {
    if (expected == actual) {
        printf("Test Passed\n\n");
    } else {
         printf("Test Failed\n\n");
    }
}

int main() {

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
	struct gameState State, StateCopy;

    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&State);    

	// Copy game state
	memcpy(&StateCopy, &State, sizeof(struct gameState));

	printf("Testing Card: Adventurer\n");

	// play card
	cardEffect(card, choice1, choice2, choice3, &State, handPos, &bonus);
	
	// check +2 treasure cards
		printf("TEST 1: hand +2 treasure cards\n");
		
		int treasureCardNumActual = 0;
		int treasureCardNumExpected = 0;

		// check actual
		for (int i = 0; i < State.handCount[0]; i++) {
			
			int card = State.hand[0][i];

			if (card >= 4 && card  <= 6) {
				treasureCardNumActual++;
			}
		}

		// check expected
		for (int i = 0; i < StateCopy.handCount[0]; i++) {
			
			int card = State.hand[0][i];

			if (card >= 4 && card  <= 6) {
				treasureCardNumExpected++;
			}
		}
		printf("hand count = %d, expected = %d\n", treasureCardNumActual, treasureCardNumExpected+2);
		assertEqual(treasureCardNumExpected+2, treasureCardNumActual);

	// No state change should occur for other players.
	printf("TEST 2: No change to player's Deck or Hand\n");
	printf("deck count = %d, expected = %d\n", State.deckCount[1], StateCopy.deckCount[1]);
	assertEqual(StateCopy.deckCount[1], State.deckCount[1]);
	printf("hand count = %d, expected = %d\n", State.handCount[1], StateCopy.handCount[1]);
	assertEqual(StateCopy.handCount[1], State.handCount[1]);

	// No state change should occur to the victory card piles 
	printf("TEST 3: No change to victory card piles\n");
	for (int i = 1; i <= 3; i++) {
		printf("Card # %d: count = %d, expected = %d\n", i , State.supplyCount[i], StateCopy.supplyCount[i]);
		assertEqual(StateCopy.supplyCount[i], State.supplyCount[i]);
	}
	
	// No state change should occur to the kingdom card piles 
	printf("TEST 4: No change to kindom card piles\n");
	for (int i = 0; i < 10; i++) {
		printf("Card # %d: count = %d, expected = %d\n", kindomCards[i] , State.supplyCount[kindomCards[i]], StateCopy.supplyCount[kindomCards[i]]);
		assertEqual(StateCopy.supplyCount[kindomCards[i]], State.supplyCount[kindomCards[i]]);
	}

	return 0;
}
