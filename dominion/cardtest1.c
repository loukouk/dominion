#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "myassert.h"
#include "dominion.h"

int main (int argc, char** argv)
{
  struct gameState state;

  state.whoseTurn = 0;
  state.numActions = 1;
  state.handCount[0] = 1;
  state.hand[0][0] = great_hall;
  state.deckCount[0] = 1;
  state.deck[0][0] = province;
  state.discardCount[0] = 0;

  printf("Playing Great hall card.\n");
  playCard( 0, 0, 0, 0, &state);
  printf("Checking hand count... ");
  myassert(state.handCount[0] == 1);
  printf("Checking # of actions... ");
  myassert(state.numActions == 1);
  printf("Next two tests should fail because the Great Hall card has purposely been changed\n");
  printf("Checking deck size... ");
  myassert(state.deckCount[0] == 0);
  printf("Checking hand cards... ");
  myassert(state.hand[0][0] == province);

  return 0;
}
