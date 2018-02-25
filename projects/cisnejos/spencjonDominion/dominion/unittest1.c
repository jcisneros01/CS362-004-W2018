//testDiscardCard.c
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertDominionTest.h"


#define DEBUG 0
#define NOISY_TEST 1

int checkDiscardCard(int hp, int tf, int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("discardCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);

  r = discardCard(hp,p, post,tf);

  //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);
  if(tf < 1)
    {
      pre.playedCards[pre.playedCardCount] = pre.hand[p][hp];
      pre.playedCardCount++;
      if(assertGameStateDom((pre.playedCardCount == post->playedCardCount), "CheckDiscardCard Trash Flag", &pre, post))
      {
        return 1;
      }
    }
  pre.hand[p][hp] = -1;
  if(hp == (pre.handCount[p] -1) )
    {
      pre.handCount[p]--;
    }
  else if ( pre. handCount[p] == 1 )
    {
      pre.handCount[p]--;
    }
  else
    {
      pre.hand[p][hp] = pre.hand[p][pre.handCount[p] -1];
      pre.hand[p][pre.handCount[p] -1] = -1;
      pre.handCount[p]--;
    }

  if(assertStandardDom(r == 0, "CheckDiscardCard Asserting R -eq 0"))
  {
    return 1;
  }

  if(assertGameStateDom(memcmp(&pre, post, sizeof(struct gameState)) == 0, "CheckDiscardCard Final Assertion Gamestate equal", &pre, post))
  {
    return 1;
  }
  //printf("Check on current game discard has completed successfully...");
  return 0;

}


int main () {

  int p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing discardCard.\n");


  printf ("SIMPLE FIXED TESTS: discardCard(...)\n");
  for (p = 0; p < 4; p++)
  {
    for (deckCount = 0; deckCount < 5; deckCount++)
    {
      for (discardCount = 0; discardCount < 5; discardCount++)
      {
      	for (handCount = 0; handCount < 5; handCount++)
        {
      	  memset(&G, 23, sizeof(struct gameState));
      	  initializeGame(2, k, 1, &G);
      	  G.deckCount[p] = deckCount;
      	  memset(G.deck[p], 0, sizeof(int) * deckCount);
      	  G.discardCount[p] = discardCount;
      	  memset(G.discard[p], 0, sizeof(int) * discardCount);
      	  G.handCount[p] = handCount;
      	  memset(G.hand[p], 0, sizeof(int) * handCount);
          if(checkDiscardCard(handCount, 0, p, &G))
          {
              printf("\n****ERROR: Tests Failed, requeted return****\n");
              return 1;
          }
      	}
      }
    }
    printf("\nTest for p = %i has passed\n", p);
  }
  printf("\nAll tests have passed\n");

  return 0;
}
