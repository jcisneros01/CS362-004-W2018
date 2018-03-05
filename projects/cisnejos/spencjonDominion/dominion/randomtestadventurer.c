 #include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

void assertEqual(int expected, int actual, char *string ) {
    if (expected == actual) {
        // printf("Test Passed\n\n");
    } else {
         printf("%s - ", string);
         printf("Test Failed\n");
    }
}

void checkAdventurer(int currentPlayer, struct gameState *post) {

	// copy game state
	struct gameState pre;	  
	memcpy (&pre, post, sizeof(struct gameState));

	// // set player 2
	int otherPlayer;
	if (currentPlayer == 1) {
		otherPlayer = 0;
	} else {
		otherPlayer = 1;
	}
	
	int card = adventurer;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int bonus = 0;

	// play card
	cardEffect(card, choice1, choice2, choice3, post, handPos, &bonus);

	//get expected state
	  int drawntreasure=0;
	  int cardDrawn;
	  int temphand[MAX_HAND];
	  int z = 0;

	while(drawntreasure<2){
		if (pre.deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
		    shuffle(currentPlayer, &pre);
		}

		drawCard(currentPlayer, &pre);

		cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else{
			temphand[z]=cardDrawn;
			pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	 }
	while(z-1>=0){
		pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	 	 z=z-1;
	}

	// check output
	int treasureCardNumActual = 0;
	int treasureCardNumExpected = 0;

	// check actual
	for (int i = 0; i < post->handCount[currentPlayer]; i++) {
		
		int card = post->hand[currentPlayer][i];

		if (card >= 4 && card  <= 6) {
			treasureCardNumActual++;
		}
	}

	// check expected
	for (int i = 0; i < pre.handCount[currentPlayer]; i++) {
		
		int card = pre.hand[currentPlayer][i];

		if (card >= 4 && card  <= 6) {
			treasureCardNumExpected++;
		}
	}

	assertEqual(treasureCardNumExpected, treasureCardNumActual, "TEST 1: hand +2 treasure cards");

	assertEqual(pre.handCount[currentPlayer], post->handCount[currentPlayer], "Test 2: handCount");

	assertEqual(pre.deckCount[currentPlayer], post->deckCount[currentPlayer], "Test 3: deckCount");

	assertEqual(pre.discardCount[currentPlayer], post->discardCount[currentPlayer], "Test 4: discardCount");


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

	srand(time(NULL)); // Seed Random func

	// Game init variables
    int numberOfPlayers = 2;
    int kindomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int randomSeed = 1000;
	struct gameState G;


    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&G);  

	printf("Testing Card: Adventurer\n");

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
			G.deckCount[i] = rand() % (MAX_DECK + 1 - 3) + 3; 
			G.discardCount[i] = floor(Random() * (MAX_DECK - G.deckCount[i]));
			G.handCount[i] = floor(Random() * (MAX_HAND - 3));
		}
		int p = floor(Random() * 2);
		G.whoseTurn = p;

		//  add 3 random treasure cards to deck
		 for (int i = 0; i < 3; i++) {
		 	G.deck[p][i] =  rand() % (6 + 1 - 4) + 4; 
		 }	

		printf("\nRandom Test #: %d \n", i);
		
		// call test function
		checkAdventurer(p, &G);

	}

	return 0;
}

