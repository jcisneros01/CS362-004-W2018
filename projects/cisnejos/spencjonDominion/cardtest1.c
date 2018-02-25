#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertDominionTest.h"

int checkSmithyCard(int currentPlayer, struct gameState* gameReturned){
    
    int returned;
    struct gameState gameExpected;
    memcpy (&gameExpected, gameReturned, sizeof(struct gameState));
    returned = playCard(0,1,1,1,gameReturned);
    
    if(assertStandardDom(returned == -1, "Play Card Failed")){
        return 1;
    }

    gameExpected.handCount[currentPlayer] += 2;
    gameExpected.deckCount[currentPlayer] -= 2;
    printf("HandCount1: %i     2: %i    DeckCount1: %i      2: %i      \n", gameExpected.handCount[currentPlayer], gameReturned->handCount[currentPlayer], gameExpected.deckCount[currentPlayer], gameReturned->deckCount[currentPlayer] );
    if (assertStandardDom(gameReturned->deckCount[currentPlayer] == gameExpected.deckCount[currentPlayer], "Deck Count Varies")){
        return 1;
    }
    if (assertStandardDom(gameReturned->handCount[currentPlayer] == gameExpected.handCount[currentPlayer], "Hand Count Varies")){
        return 1;
    }
    return 0;
}


int main () {

  int p, i;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("SIMPLE FIXED TESTS: Smithy Card\n");
  for (p = 2; p < 5; p++)
  {
    for(i = 0; i < p; i++)
    {
        initializeGame(2, k, 1, &G);
        G.hand[i][0] = 13; //place smithy card into hand
        G.whoseTurn = i; //it's that person's turn
        
        if(checkSmithyCard(i, &G))
        {
            printf("\n****ERROR: Tests Failed, requeted return****\n");
            return 1;
        } 
    }
    printf("\nTest for numPlayers = %i has passed\n", p);
  }
  printf("\nAll tests have passed\n");

  return 0;
}
