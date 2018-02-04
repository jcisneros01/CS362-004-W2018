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

    // Update Coins variables
    int player = 0;
    int bonus;

    // print heading
    printf ("TESTING updateCoins():\n");

    // init game
    initializeGame(numberOfPlayers,kindomCards,randomSeed,&State);

    // test hand of all gold 
        for (int i = 0; i < 5; i++) {
            State.hand[player][i] = gold;
        }

        bonus = rand() % 7;

        updateCoins(player, &State, bonus);

        printf("All Gold Test\n");

        // print cost
        printf("Actual Coin Total: %d, Expected Coin Total: %d\n", State.coins, 15 + bonus);

        assertEqual(15 + bonus, State.coins);

    // test hand of all silver 
        for (int i = 0; i < 5; i++) {
            State.hand[player][i] = silver;
        }

        bonus = rand() % 7;

        updateCoins(player, &State, bonus);

        // print card
        printf("All Silver Test\n");

        // print cost
        printf("Actual Coin Total: %d, Expected Coin Total: %d\n", State.coins, 10 + bonus);

        assertEqual(10 + bonus, State.coins);

    // test hand of all copper 
        for (int i = 0; i < 5; i++) {
            State.hand[player][i] = copper;
        }

        bonus = rand() % 7;

        updateCoins(player, &State, bonus);

        printf("All Copper Test\n");

        // print cost
        printf("Actual Coin Total: %d, Expected Coin Total: %d\n", State.coins, 5 + bonus);

        assertEqual(5 + bonus, State.coins);

    // test hand of random mix
        int treasureCard; // current card
        int expectedCoinTotal = 0; 

        for (int i = 0; i < 5; i++) {
            
            // get random card
            treasureCard = rand() % (6 + 1 - 4) + 4; 
            
            // Set random card
            State.hand[player][i] = treasureCard;
            
            // add to total
            switch(treasureCard) {
                case 4:
                    expectedCoinTotal += 1;
                    break;
                case 5:
                    expectedCoinTotal += 2;
                    break;
                case 6:
                    expectedCoinTotal += 3;
                    break;
            }
        }

        bonus = rand() % 7;

        updateCoins(player, &State, bonus);

        printf("Random Mix Test\n");

        // print cost
        printf("Actual Coin Total: %d, Expected Coin Total: %d\n", State.coins, expectedCoinTotal + bonus);

        assertEqual(expectedCoinTotal + bonus, State.coins);

    return 0;
}
