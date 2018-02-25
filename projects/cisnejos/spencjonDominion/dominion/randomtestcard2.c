#include "dominion.h"
#include "dominion_helpers.h"
#include "assertDominionTest.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>


/*
void copyGame(struct gameState *dst, struct gameState *src){
  int i, j;
  
  dst->numPlayers = src->numPlayers; //number of players
  
  for(i = 0; i <= treasure_map; i++){
    dst->supplyCount[i] = src->supplyCount[i];  //this is the amount of a specific type of card given a specific number.
    dst->embargoTokens[i] = src->supplyCount[i];
  }
  
  dst->outpostPlayed = src->outpostPlayed;
  dst->outpostTurn = src->outpostTurn;
  dst->whoseTurn = src->whoseTurn;
  dst->phase = src->phase;
  dst->numActions = src->numActions;  Starts at 1 each turn 
  dst->coins = src->coins;  Use as you see fit! 
  dst->numBuys = src->numBuys;  Starts at 1 each turn 
  for(i = 0; i < src->numPlayers; i++){
    dst->handCount[i] = src->handCount[i];
    for(j = 0; j < src->handCount[i]; j++)
        dst->hand[i][j] = src->hand[i][j];
  }
  for(i = 0; i < src->numPlayers; i++){
    dst->handCount[i] = src->handCount[i];
    dst->deckCount[i] = src->deckCount[i];
    dst->discardCount[i] = src->discardCount[i];
    for(j = 0; j < src->handCount[i]; j++)
        dst->hand[i][j] = src->hand[i][j];
    for(j = 0; j < src->deckCount[i]; j++)
        dst->deck[i][j] = src->deck[i][j];        
    for(j = 0; j < src->discardCount[i]; j++)
        dst->discard[i][j] = src->discard[i][j];
  }
  dst->playedCardCount = src->playedCardCount;
  for(i = 0; i < src->playedCardCount; i++)
    dst->playedCards[i] = src->playedCards[i];
}


*/

int checkSmithy(int p, struct gameState *post){
  struct gameState pre;
  int r, i;
  //printf("Going into setup\n");
  memcpy(&pre, post, sizeof(struct gameState));
 // printf("Going into setup\n");
  for(i = 0; i < pre.handCount[p]; i++){
    r = -50;
    if(pre.hand[p][i] == smithy){
      //printf("Found Card \n");
      r = smithy_effect(p, post, i);
      break;
    }
  }  
  if(pre.handCount[p] == 0){
    return 0;
  }
    //printf("handCount: %i  %i Deck count: %i %i\n", pre.handCount[p], post->handCount[p], (pre.discardCount[p] + pre.deckCount[p]), (post->discardCount[p] + post->deckCount[p]));
    assertStandardDom(r <= 0, "smithy Returned more than 0");
    assertStandardDom(post->handCount[p]==(pre.handCount[p] + 2),"rand smithy: Hand Count incorrect");
    assertStandardDom((pre.discardCount[p] + pre.deckCount[p] - 2)  == (post->discardCount[p] + post->deckCount[p]), "rand smithy: incorrect deck/discard counts");
  
  return 0;
}


int main(){

  int i, n, p,j, numCards, smithyFlag = 0;
  struct gameState G;

  printf ("Testing smithy effect.\n");

  printf ("RANDOM TESTS.\n");

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * MAX_PLAYERS);
    numCards = floor(Random() * MAX_DECK);
    G.deckCount[p] = numCards - floor(Random() * numCards);
    G.discardCount[p] = floor(Random() * (numCards - G.deckCount[p]));
    G.handCount[p] = numCards - G.deckCount[p] - G.discardCount[p];
    G.numActions = floor(Random() * 100);
    //printf("INITIAL: nc: %i dec: %i dic: %i hc: %i na: %i\n",numCards, G.deckCount[p], G.discardCount[p],G.handCount[p],G.numActions );
    if(G.handCount[p] < 1){
        G.handCount[p] = 1;
        if(G.discardCount[p] < 1)
            G.discardCount[p]--;
        else 
            G.deckCount[p]--;
    }

    for(i = 0; i < G.deckCount[p]; i++){
        G.deck[p][i] = floor(Random() * treasure_map);
    }

    for(i = 0; i < G.discardCount[p]; i++){
      G.discard[p][i] = floor(Random() * treasure_map);
    }

    for(i = 0; i < G.handCount[p]; i++){
      j = floor(Random() * (treasure_map+1));
      G.hand[p][i]=j;
      if(smithy == j){
        smithyFlag = 1;
      }
    }

    G.playedCardCount = 0;
    if(!smithyFlag){
      i = floor(Random() * G.handCount[p]);
      G.hand[p][i] = smithy;
    }
    checkSmithy(p, &G);

  }

  printf ("ALL TESTS OK\n");

  return 0;
}