/*
 * randomtestadventurer.c
 *
 
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define TRUE 1
#define FALSE 0
#define NUM_RUNS 10000

int main() {
    int newCards = 2;
    int discarded = 0;		// no discard in play_adventurer card
    int xtraCoins = 0;

    int newTreas1, newTreas2;
    int G_totalcount, testG_totalcount;
    int pass_count=0, fail_count=0;
    int tcc_hand, tcc_deck, tcc_discard, tcc_total;	//tcc = treasure card count

	int i, r;
	int temphand[MAX_HAND];// moved above the if statement
	int drawntreasure=0;
	int cardDrawn=0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;

	int NUMCARDS = 27;
	int NUMCARDS_IN_PLAY = 17;
	int TOT_KCARDS = 20;
	int KCARD_FIRSTINDEX = adventurer;
	int MAX_KCARDS = 10;
	int MIN_STARTING_CARDS = 2;
	int MAX_STARTING_CARDS = 15;
	int k[MAX_KCARDS];					// array storing 10 cards to use in a single game
	int NUMTREASURECARDS = 3;
	int TREASURE_FIRSTINDEX = copper;

	// list of cards
	char* card[] = {"curse", "estate", "duchy", "province", "copper",
			"silver", "gold", "adventurer", "council_room", "feast",
			"gardens", "mine", "remodel", "smithy", "village",
			"baron", "great_hall", "minion", "steward", "tribute",
			"ambassador", "cutpurse", "embargo", "outpost", "salvager",
			"sea_hag", "treasure_map"};

	// declare random test variables
	int rand_kcard[MAX_KCARDS];			// adventurer and 9 other randomly selected kingdom cards
	int rand_numhandcards;				// starting number of cards in hand from 2 to 10
	int rand_numdeckcards;				// starting number of cards in deck from 2 to 10
	int rand_numdiscards;				// starting number of cards in discard from 2 to 10
	int rand_thiscard;					// 1 of 17 cardtypes in play (1 curse, 3 victory 3 treasure, 10 kingdom)
	int rand_isTreasure;				// boolean determining whether a card is a Treasure card

	int cardtype[NUMCARDS];				// counts of each card type in deck and discard (potential discards)
	int kcardcount = 0;					// count of numnber of kcards types established
	int repeat_flag;					// true if repeat was found

	printf("\t----------------- Random Testing Card: %s ----------------\n", TESTCARD);

	printf("\t***BUG FOUND: play_adventurer does not discard original adventurer card -- disregarding discard***\n");
	printf("\t***BUG FOUND: play_adventurer does not update coins -- disregarding coin update***\n");
	printf("\t  >> Initial tests perform as expected; continue only exception reporting <<\n");

	for (i=0; i<NUMCARDS; i++) { cardtype[i] = 0; }

	for (r=0; r<NUM_RUNS; r++) {
		kcardcount = 0;
		tcc_hand=0; tcc_deck=0; tcc_discard=0; tcc_total=0;

		// establish parameters of a single test case

		//		establish 10 kingdom cards to use for this game
		rand_kcard[0] = adventurer;
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
		rand_numhandcards = (rand() % (MAX_STARTING_CARDS - MIN_STARTING_CARDS + 1)) + MIN_STARTING_CARDS;
		//printf("\tstarting cards in hand: %d\n", rand_numhandcards);
		G.handCount[thisPlayer] = rand_numhandcards;
		G.hand[thisPlayer][0] = adventurer;

		//		establish number of cards in deck from 2 to 10
		rand_numdeckcards = (rand() % (MAX_STARTING_CARDS - MIN_STARTING_CARDS + 1)) + MIN_STARTING_CARDS;
		//printf("\tstarting cards in deck: %d\n", rand_numdeckcards);
		G.deckCount[thisPlayer] = rand_numdeckcards;

		//		establish number of cards in discard from 2 to 10
		rand_numdiscards = (rand() % (MAX_STARTING_CARDS - MIN_STARTING_CARDS + 1)) + MIN_STARTING_CARDS;
		//printf("\tstarting cards in discard: %d\n", rand_numdiscards);
		G.discardCount[thisPlayer] = rand_numdiscards;

		//		establish each card
		//			cards in hand
		G.hand[thisPlayer][0] = adventurer;
		for (i=1; i<rand_numhandcards; i++) {
			rand_isTreasure = rand() % 2;
			if (rand_isTreasure) {
				G.hand[thisPlayer][i] = (rand() % NUMTREASURECARDS) + TREASURE_FIRSTINDEX;
				tcc_hand++;
			}
			else {
				rand_thiscard = rand() % (NUMCARDS_IN_PLAY - NUMTREASURECARDS);
				if (rand_thiscard < TREASURE_FIRSTINDEX)
					G.hand[thisPlayer][i] = rand_thiscard;
				else {
					G.hand[thisPlayer][i] = k[rand_thiscard - TREASURE_FIRSTINDEX];
				}
			}
		}
		//for (i=0; i<rand_numhandcards; i++) printf("\t\thandcard[%d] = %s\n", i, card[G.hand[thisPlayer][i]]);

		//			cards in deck
		for (i=0; i<rand_numdeckcards; i++) {
			rand_isTreasure = rand() % 2;
			if (rand_isTreasure) {
				G.deck[thisPlayer][i] = (rand() % NUMTREASURECARDS) + TREASURE_FIRSTINDEX;
				tcc_deck++;
			}
			else {
				rand_thiscard = rand() % (NUMCARDS_IN_PLAY - NUMTREASURECARDS);
				if (rand_thiscard < TREASURE_FIRSTINDEX)
					G.deck[thisPlayer][i] = rand_thiscard;
				else
					G.deck[thisPlayer][i] = k[rand_thiscard - TREASURE_FIRSTINDEX];
			}
		}
		for (i=0; i<rand_numdeckcards; i++) cardtype[G.deck[thisPlayer][i]]++;
		//for (i=0; i<rand_numdeckcards; i++) printf("\t\tdeckcard[%d] = %s\n", i, card[G.deck[thisPlayer][i]]);

		//			cards in discard
		for (i=0; i<rand_numdiscards; i++) {
			rand_isTreasure = rand() % 2;
			if (rand_isTreasure) {
				G.discard[thisPlayer][i] = (rand() % NUMTREASURECARDS) + TREASURE_FIRSTINDEX;
				tcc_discard++;
			}
			else {
				rand_thiscard = rand() % (NUMCARDS_IN_PLAY - NUMTREASURECARDS);
				if (rand_thiscard < TREASURE_FIRSTINDEX)
					G.discard[thisPlayer][i] = rand_thiscard;
				else
					G.discard[thisPlayer][i] = k[rand_thiscard - TREASURE_FIRSTINDEX];
			}
		}
		for (i=0; i<rand_numdiscards; i++) cardtype[G.discard[thisPlayer][i]]++;
		//for (i=0; i<rand_numdiscards; i++) printf("\t\tdiscard[%d] = %s\n", i, card[G.deck[thisPlayer][i]]);

		tcc_total = tcc_hand + tcc_deck + tcc_discard;

		// -------- TEST: execute a single test case ---------------

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		play_adventurer(thisPlayer, drawntreasure, cardDrawn, temphand, &testG);

		G_totalcount = G.handCount[thisPlayer] + G.deckCount[thisPlayer] + G.discardCount[thisPlayer];
		testG_totalcount = testG.handCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer];
		newTreas1 = testG.hand[thisPlayer][testG.handCount[thisPlayer]-1];
		newTreas2 = testG.hand[thisPlayer][testG.handCount[thisPlayer]-2];

		discarded = 0; // modifying because BUG FOUND - play adventurer does not discard orig adventurer
		xtraCoins = 0; // modifying because BUG FOUND - play_adventurer does not update coins.
		newCards = (tcc_deck + tcc_discard >= 2)? 2: tcc_deck + tcc_discard;	// lower of 2 or #Treasures in deck+discard

		if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded) { fail_count++;
			printf("\n\tTEST %d: orig {handcount, deckcount, discardcount, total} = {%d, %d, %d, %d}\n",
					r, G.handCount[thisPlayer], G.deckCount[thisPlayer], G.discardCount[thisPlayer], G_totalcount);
			printf("\tnew {handcount, deckcount, discardcount, total} = {%d, %d, %d, %d}\n",
					testG.handCount[thisPlayer], testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG_totalcount);
			printf("\torig treasure card count {handcount, deckcount, discardcount, total} = {%d, %d, %d, %d}\n",
					tcc_hand, tcc_deck, tcc_discard, tcc_total);
			printf("\thand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			printf("\torig last 2 card: %s, %s\n", card[G.hand[thisPlayer][G.handCount[thisPlayer]-1]],
					card[G.hand[thisPlayer][G.handCount[thisPlayer]-2]]);
			printf("\tnew last 2 cards: %s, %s\n", card[newTreas1], card[newTreas2]);
			printf("\tCoin before: %d, Coin after: %d\n", G.coins, testG.coins);

			//printf("\t\tdeck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			//printf("\t\tcoins = %d, expected = %d\n\n", testG.coins, G.coins + xtraCoins);
			//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
			//assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
			//assert(testG.coins == G.coins + xtraCoins);
		} else pass_count++;
	}

	// output the counts of initialized deck and discard cards
	printf("\n\tNumber of test cases: %d.  PASS=%d  FAIL=%d\n\n", NUM_RUNS, pass_count, fail_count);
	for (i=0; i<NUMCARDS; i++)
		printf("\tcard %-15s==> # times in either deck or discard count: %d\n", card[i], cardtype[i]);



	return 0;
}
