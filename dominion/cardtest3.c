#include "myassert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;

  state.whoseTurn = 0;
  state.numActions = 1;
  state.handCount[0] = 1;
  state.hand[0][0] = village;
  state.deckCount[0] = 1;
  state.deck[0][0] = province;

  printf("Playing Village card.\n");
  playCard(0,0,0,0, &state);
  printf("Checking # of actions... ");
  myassert(state.numActions == 2);
  printf("Checking deck count... ");
  myassert(state.deckCount[0] == 0);
  printf("Checking hand count... ");
  myassert(state.handCount[0] == 1);
  printf("Checking hand cards... ");
  myassert(state.hand[0][0] == province);

  return 0;
}
