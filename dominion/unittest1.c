#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;
  int numSame = 0;

  printf("Testing shuffle() function\n");

  state.deckCount[0] = MAX_DECK;
  for (int i = 0; i < MAX_DECK; i++)
	state.deck[0][i] = i;

  shuffle(0, &state);

  for (int i = 0; i < MAX_DECK; i++)
	if (state.deck[0][i] == 1)
	  numSame++;

  printf("Deck size is %d. ", MAX_DECK);
  assert(numSame != state.deckCount[0]);
  printf("Successfull shuffle with %d cards in the same spot.\n", numSame);

  return 0;
}
