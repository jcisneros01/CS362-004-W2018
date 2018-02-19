 
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

void assertEqual(int expected, int actual, char *string ) {
    if (expected == actual) {
        // printf("Test Passed\n\n");
    } else {
         printf("%s - ", string);
         printf("Test Failed\n");
    }
}

void checkSmithyEffects(int currentPlayer, struct gameState *post) {

	// copy game state
	struct gameState pre;	  
	memcpy (&pre, post, sizeof(struct gameState));

	// set player 2
	int otherPlayer;
	if (currentPlayer == 1) {
		otherPlayer = 0;
	} else {
		otherPlayer = 1;
	}
	
	int card = smithy;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int bonus = 0;

	// play card
	cardEffect(card, choice1, choice2, choice3, post, handPos, &bonus);

	// get expected state
	for (int i = 1;  i <= 3; i++) {
	 drawCard(currentPlayer, &pre);
	}

	discardCard(handPos, currentPlayer, &pre, 0);

	// check output
	assertEqual(pre.handCount[currentPlayer], post->handCount[currentPlayer], "Test 1: handCount");

	assertEqual(pre.deckCount[currentPlayer], post->deckCount[currentPlayer], "Test 2: deckCount");

	assertEqual(pre.discardCount[currentPlayer], post->discardCount[currentPlayer], "Test 3: discardCount");

	// no state change should occur for other players.
	assertEqual(pre.deckCount[otherPlayer], post->deckCount[otherPlayer], "TEST 5A: No change to player's Deck");
	assertEqual(pre.handCount[otherPlayer], post->handCount[otherPlayer], "TEST 5B: No change to player's Deck");	

	// No state change should occur to the victory card piles 
	for (int i = 1; i <= 3; i++) {
		assertEqual(pre.supplyCount[i], post->supplyCount[i], "TEST 6: No change to victory card piles");
	}

	// No state change should occur to the kingdom card piles 
	int kindomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	for (int i = 0; i < 10; i++) {
		assertEqual(pre.supplyCount[kindomCards[i]], post->supplyCount[kindomCards[i]], "TEST 7: No change to kindom card piles");
	}
	
}

int main() {

	// Game init variables
    int numberOfPlayers = 2;
    int kindomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int randomSeed = 1000;
	struct gameState G;


    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&G);  

	printf("Testing Card: Smithy\n");

	SelectStream(2);
  	PutSeed(3);

	// iterate through tests
	for (int i = 1; i <= 2000; i++)	 {

		// create random game state
		for (int j = 0; j < sizeof(struct gameState); j++) {
		  ((char*)&G)[j] = floor(Random() * 256);
		}
		
		// generate random function inputs
		for (int i = 0; i < 2; i++) {
			G.deckCount[i] = floor(Random() * MAX_DECK);
			G.discardCount[i] = floor(Random() * MAX_DECK);
			G.handCount[i] = floor(Random() * MAX_HAND);
		}
		int p = floor(Random() * 2);
		G.whoseTurn = p;
		G.playedCardCount = floor(Random() * (MAX_DECK-1));

		printf("\nRandom Test #: %d \n", i);
		
		// call test function
		checkSmithyEffects(p, &G);

	}

	return 0;
}

