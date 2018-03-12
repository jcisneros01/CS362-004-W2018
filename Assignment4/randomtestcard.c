/*
 * randomtestcard.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "salvager"
#define TRUE 1
#define FALSE 0
#define NUM_RUNS 10000

int main() {
    int newCards = 0;
    int discarded = 2;		// discard 1 salvager card and 1 trash card
    int xtraCoins = 0;
    int shuffledCards = 0;

	int i, r;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;

	int NUMCARDS = 27;
	int NUMCARDS_IN_PLAY = 17;
	int TOT_KCARDS = 20;
	int KCARD_FIRSTINDEX = adventurer;
	int MAX_KCARDS = 10;
	int MAX_CHOICE1 = 9;
	int MIN_CARDS_IN_HAND = 2;
	int MAX_CARDS_IN_HAND = 10;

	// list of cards
	char* card[] = {"curse", "estate", "duchy", "province", "copper",
			"silver", "gold", "adventurer", "council_room", "feast",
			"gardens", "mine", "remodel", "smithy", "village",
			"baron", "great_hall", "minion", "steward", "tribute",
			"ambassador", "cutpurse", "embargo", "outpost", "salvager",
			"sea_hag", "treasure_map"};

	// source:	http://boardgamegeek.com/thread/457960/list-of-all-dominion-cards,
	//			http://dominioncg.wikia.com/wiki
	int cardCost[] = 	{0,2,5,8,0,  3,6,6,5,4,  4,5,4,4,3,  4,3,5,3,5,  3,4,2,5,4,  4,4};
	int k[MAX_KCARDS];					// array storing 10 cards to use in a single game

	// declare random test variables
	int rand_kcard[MAX_KCARDS];			// salvager and 9 other randomly selected kingdom cards
	int rand_numhandcards;				// starting number of cards in hand from 2 to 10
	int rand_thiscard;					// 1 of 17 cardtypes in play (1 curse, 3 victory 3 treasure, 10 kingdom)
	int rand_cardchoice;				// choice of any card in hand excluding the salvager card being trashed

	int kcardcount = 0;					// count of numnber of kcards types established
	int trashed_cardcount[NUMCARDS];	// counts of each card type trashed
	int trashed_choice1count[MAX_CHOICE1];	// counts of each card position chosen to be trashed.
	int repeat_flag;					// true if repeat was found

	// initialize coverage counts of trashed card: cardtype and hand position
	for (i=0; i<NUMCARDS; i++)
		trashed_cardcount[i]=0;
	for (i=0; i<MAX_CHOICE1; i++)
		trashed_choice1count[i] = 0;

	printf("\t----------------- Random Testing Card: %s ----------------\n", TESTCARD);

	for (r=0; r<NUM_RUNS; r++) {
		kcardcount = 0;

		// establish parameters of a single test case

		//		establish 10 kingdom cards to use for this game
		rand_kcard[0] = salvager;
		kcardcount++;
		while (kcardcount < MAX_KCARDS) {
			repeat_flag = FALSE;
			rand_kcard[kcardcount] = (rand() % TOT_KCARDS) + KCARD_FIRSTINDEX;
			for (i=0; i<kcardcount; i++) {
				if (rand_kcard[kcardcount] == rand_kcard[i])
					repeat_flag = TRUE;
			}
			if (!repeat_flag)
				kcardcount++;
		}
		for (i=0; i<MAX_KCARDS; i++)
			k[i] = rand_kcard[i];
		//for (i=0; i<MAX_KCARDS; i++) printf("\trand_kcard[%d] = %s\n", i, card[k[i]]); 			printf("\n");
		//for (i=0; i<MAX_KCARDS; i++) printf("\trand_kcard[%d] = %s\n", i, card[rand_kcard[i]]); 	printf("\n");

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);


		//		establish number of cards in hand from 2 to 10
		rand_numhandcards = (rand() % (MAX_CARDS_IN_HAND - MIN_CARDS_IN_HAND + 1)) + MIN_CARDS_IN_HAND;
		//printf("\tstarting cards in hand: %d\n", rand_numhandcards);
		G.handCount[thisPlayer] = rand_numhandcards;
		G.hand[thisPlayer][0] = salvager;

		//		establish card in play for each card in hand after card 0 (salvager)
		for (i=1; i<rand_numhandcards; i++) {
			rand_thiscard = rand() % NUMCARDS_IN_PLAY;
			if (rand_thiscard < NUMCARDS_IN_PLAY - MAX_KCARDS) {
				G.hand[thisPlayer][i] = rand_thiscard;			// < 7 means non-kingdom card
			}
			else {												// 7-16 means a kingdom card
				G.hand[thisPlayer][i] = k[rand_thiscard - (NUMCARDS_IN_PLAY - MAX_KCARDS)];
			}
		}
		//for (i=0; i<G.handCount[thisPlayer]; i++) printf("\tcard[%d] = %s\n", i, card[G.hand[thisPlayer][i]]); 	printf("\n");

		//		establish choice of card to trash from 2 to #starting cards in hand
		if (rand_numhandcards > 2)
			rand_cardchoice = rand() % (rand_numhandcards - MIN_CARDS_IN_HAND) + 1;	// +1 to skip card 0, salvager
		else
			rand_cardchoice = 1;
		//printf("\tcard to trash: %s\n", card[G.hand[thisPlayer][rand_cardchoice]]); 	printf("\n");

		// 		tabulate count of card type and hand position for card trashed
		trashed_choice1count[rand_cardchoice]++;
		trashed_cardcount[G.hand[thisPlayer][rand_cardchoice]]++;


		// -------- TEST: execute a single test case ---------------

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		choice1 = rand_cardchoice;						//card to trash
		cardEffect(salvager, choice1, choice2, choice3, &testG, handpos, &bonus);

		newCards = 0;
		xtraCoins = cardCost[G.hand[thisPlayer][rand_cardchoice]];

		//printf("\tTEST %d: handcount %d, trashcard=[%s] +Coins %d\n",
		//		r, rand_numhandcards, card[G.hand[thisPlayer][rand_cardchoice]], xtraCoins);

		//printf("\t\thand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
		//printf("\t\tdeck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
		//printf("\t\tcoins = %d, expected = %d\n\n", testG.coins, G.coins + xtraCoins);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
		assert(testG.coins == G.coins + xtraCoins);
	}

	// output the coverage counts of trashed cards
	printf("\tNumber of test cases: %d\n\n", NUM_RUNS);
	for (i=0; i<NUMCARDS; i++)
		printf("\tcard %-15s==> # times trashed: %d\n", card[i], trashed_cardcount[i]);
	printf("\n");
	for (i=1; i<MAX_CHOICE1; i++)
		printf("\tcard position in hand: %d  ==> # times trashed: %d\n", i, trashed_choice1count[i]);

	return 0;
}


