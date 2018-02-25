
#ifndef _ASSERTDOMINIONTEST_H
#define _ASSERTDOMINIONTEST_H

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int assertStandardDom(int, char*);
int assertGameStateDom(int, char*, struct gameState*, struct gameState*);
void printGameState(struct gameState *);

#endif
