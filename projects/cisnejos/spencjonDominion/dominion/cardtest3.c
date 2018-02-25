#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertDominionTest.h"

int checkGreatHallCard(int currentPlayer, struct gameState* gameReturned){    
    int returned;
    struct gameState gameExpected;
    memcpy (&gameExpected, gameReturned, sizeof(struct gameState));

    returned = playCard(0,1,1,1,gameReturned);
    
    if(assertStandardDom(returned == 0, "Play Card Failed")){
        return 1;
    }
    
    //printf("NumActions Exp: %i, Returned: %i\n", gameExpected.numActions, gameReturned->numActions);
    if(assertStandardDom(gameExpected.numActions == gameReturned->numActions, "Actions inequal after additional")){
        return 1;
    }   
    
    return 0;
}


int main () {

  int p, i;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("SIMPLE FIXED TESts: Great_Hall\n");
  for (p = 2; p < 5; p++)
  {
    for(i = 0; i < p; i++)
    {
        //printf("Testing Players: %i, Player: %i\n", p, i);
        initializeGame(2, k, 1, &G);
        G.hand[i][0] = 16; //place great_hall card into hand
        G.whoseTurn = i; //it's that person's turn
        
        if(checkGreatHallCard(i, &G))
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