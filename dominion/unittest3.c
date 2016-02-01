#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;

  state.handCount[0] = 12;
  state.deckCount[0] = 53;
  state.discardCount[0] = 109;

  for (int i = 0; i < state.handCount[0]; i++)
	state.hand[0][i] = minion;
  for (int i = 0; i < state.deckCount[0]; i++)
	state.deck[0][i] = minion;
  for (int i = 0; i < state.discardCount[0]; i++)
	state.discard[0][i] = minion;

  state.hand[0][2] = estate;
  state.deck[0][6] = estate;
  state.discard[0][5] = estate;

  assert(fullDeckCount(0, estate, &state) == 3);
  printf("SUCCESS: 3 estates counted in hand, deck and discard.\n");

  state.hand[0][11] = estate;
  state.deck[0][16] = estate;
  state.deck[0][11] = estate;
  state.deck[0][36] = estate;
  state.deck[0][46] = estate;
  state.discard[0][15] = estate;
  state.discard[0][25] = estate;
  state.discard[0][50] = estate;
  state.discard[0][100] = estate;

  assert(fullDeckCount(0, estate, &state) == 12);
  printf("SUCCESS: 12 estates counted in hand, deck and discard.\n");

  return 0;

}
