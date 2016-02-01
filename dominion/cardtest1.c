#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "assert.h"
#include "dominion.c"

int main (int argc, char** argv)
{
  struct gameState state;

  state.whoseTurn = 0;
  state.numActions = 1;
  state.handCount[0] = 1;
  state.hand[0][0] = great_hall;
  state.deckCount[0] = 1;
  state.deck[0][0] = province;

  cardEffect( great_hall, 0, 0, 0, &state, 0, NULL);
  printf("Checking hand count... ");
  assert(state.handCount[0] == 1);
  printf("PASSED.\n");
  printf("Checking # of actions... ");
  assert(state.numActions == 2);
  printf("PASSED.\n");
  printf("Checking deck size... ");
  assert(state.deckCount[0] == 0);
  printf("PASSED.\n");
  printf("Checking hand cards... ");
  assert(state.hand[0][0] == province);
  printf("PASSED.\n");

  return 0;
}
