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

    printf ("TESTING fullDeckCount():\n");

    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&State);    

    // Test initial game state
        printf("Test: Testing Starting Deck\n");
        printf("Testing Copper\n");
        assertEqual(7, fullDeckCount(0, copper, &State));
        printf("Testing Estate\n");
        assertEqual(3, fullDeckCount(0, estate, &State));

    // Test Random Deck State
    int deckCount = rand() % 10;
    int handCount = rand() % 6;
    int discardCount = rand() % 10;

    printf("Test: Random Deck\n");
    printf("Deck #: %d\n", deckCount);
    printf("Hand #: %d\n", handCount);
    printf("Discard #: %d\n", discardCount);

    // Set random values
    State.deckCount[0] = deckCount;
    State.handCount[0] = handCount;
    State.discardCount[0] = discardCount;

    // Set all cards to a random card
    int randomCard = rand() % 27;
    printf("Random Card # populated for all cards: %d\n", randomCard);

    for (int i = 0; i < State.deckCount[0]; i++)
      {
        State.deck[0][i] = randomCard;
      }

    for (int i = 0; i < State.handCount[0]; i++)
      {
        State.hand[0][i] = randomCard;
      }

    for (int i = 0; i < State.discardCount[0]; i++)
      {
        State.discard[0][i] = randomCard;
      }

    int actualTotal = fullDeckCount(0, randomCard, &State);
    int expectedTotal = deckCount + handCount + discardCount;
    printf("Actual  Total: %d, Expected  Total: %d\n", actualTotal, expectedTotal);

    assertEqual(expectedTotal, actualTotal);


    return 0;   
}