#include <string.h>

#include "dominion.h"
#include "assertDominionTest.h"
#include "dominion_helpers.h"
#include "rngs.h"


int checkNumHandCards(struct gameState *state)
{
  int expected;
  int returned;
  char msg[] = "Num Cards Failed";
  expected = state->handCount[state->whoseTurn];
  returned = numHandCards(state);

  if(assertStandardDom((expected == returned), msg)) {
    return 1;
  }
  return 0;
}

int main(){
  int p, i, r;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  struct gameState G;
  char msg[] = "initializeGame failed";
  printf ("Simple Fixed Tests: numHandCards(...)\n");



  for(p = 2; p < 5; p++){
    for(i = 0; i < 4; i++){
      
      //printf("tmp 1");
      memset(&G, 23, sizeof(struct gameState));
      r = initializeGame(p, k, 1, &G);
      if(assertStandardDom((r == 0), msg)){
        printf("Return Requested.. Returning... \n");
        return 1;
      }
      ///printf("tmp 2");
      G.whoseTurn = i;
      //printf("tmp 3");
      if(checkNumHandCards(&G)){
        printf("Return Requested.. Returning...");
        return 1;
      } 
    }
    printf("Tests passed for %i players\n", i);
  }
  printf("Tests passed for all number of players\n");
  return 0;
}
