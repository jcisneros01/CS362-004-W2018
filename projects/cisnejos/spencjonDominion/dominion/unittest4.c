#include <string.h>
#include "dominion.h"
#include "assertDominionTest.h"
#include "dominion_helpers.h"
#include "rngs.h"

int checkIsGameOver(struct gameState* state) {
    int returned;  
    struct gameState modify = *state;
    
    returned = isGameOver(&modify);  
    
    if(assertStandardDom((returned == 0), "Just Initialized\n")){
        return 1;
    }

    modify.supplyCount[province] = 0;
    returned = isGameOver(&modify);  
    if(assertStandardDom((returned == 1), "Provinces == 0\n")){
        return 1;
    }

    modify.supplyCount[province] = 2;
    modify.supplyCount[smithy] = 0;
    modify.supplyCount[adventurer] = 0;
    modify.supplyCount[great_hall] = 0;
    returned = isGameOver(&modify);  
    if(assertStandardDom((returned == 1), "3 supply piles are empy\n")){
        return 1;
    }

    printf("All Tests passed\n");
    return 0;
}

int main(){
  int r, p;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  struct gameState G;

  printf ("Simple Fixed Tests: isGameOver(...)\n");

  for(p = 2; p < 5; p++){
      r = initializeGame(p, k, 1, &G);
      if(assertStandardDom((r == 0), "initializeGame failed\n")){
        printf("Return Requested.. Returning... \n");
        return 1;
      }
      if(checkIsGameOver(&G)){
        printf("Return Requested.. Returning...\n");
        return 1;
    }
    printf("Tests passed for %i players\n", p);
  }
  printf("Tests passed for all number of players\n");
  return 0;
}