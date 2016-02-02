#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;

  printf("Testing scoreFor() function\n");

  state.handCount[0] = 0;
  state.deckCount[0] = 0;
  state.discardCount[0] = 0;

  assert(!scoreFor(0, &state));

  state.handCount[0] = 100;
  state.deckCount[0] = 100;
  state.discardCount[0] = 100;

  for (int i = 0; i < 100; i++) {
	state.hand[0][i] = minion;
	state.deck[0][i] = minion;
	state.discard[0][i] = minion;
  }

  assert(!scoreFor(0, &state));
  state.hand[0][10] = curse;
  assert(scoreFor(0, &state) == -1);
  state.hand[0][20] = estate;
  assert(scoreFor(0, &state) == 0);
  state.hand[0][30] = duchy;
  assert(scoreFor(0, &state) == 3);
  state.hand[0][40] = province;
  assert(scoreFor(0, &state) == 9);
  state.hand[0][50] = great_hall;
  assert(scoreFor(0, &state) == 10);
  state.hand[0][60] = gardens;
  assert(scoreFor(0, &state) == 40);

  state.deck[0][10] = curse;
  assert(scoreFor(0, &state) == -1+40);
  state.deck[0][20] = estate;
  assert(scoreFor(0, &state) == 0+40);
  state.deck[0][30] = duchy;
  assert(scoreFor(0, &state) == 3+40);
  state.deck[0][40] = province;
  assert(scoreFor(0, &state) == 9+40);
  state.deck[0][50] = great_hall;
  assert(scoreFor(0, &state) == 10+40);
  state.deck[0][60] = gardens;
  assert(scoreFor(0, &state) == 40+40);

  state.discard[0][10] = curse;
  assert(scoreFor(0, &state) == -1+80);
  state.discard[0][20] = estate;
  assert(scoreFor(0, &state) == 0+80);
  state.discard[0][30] = duchy;
  assert(scoreFor(0, &state) == 3+80);
  state.discard[0][40] = province;
  assert(scoreFor(0, &state) == 9+80);
  state.discard[0][50] = great_hall;
  assert(scoreFor(0, &state) == 10+80);
  state.discard[0][60] = gardens;
  assert(scoreFor(0, &state) == 40+80);

  printf("Success. All scores checked and correct.\n");

  return 0;
}
