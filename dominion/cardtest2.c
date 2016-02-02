#include "myassert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;

  state.numActions = 1;
  state.whoseTurn = 0;
  state.handCount[0] = 1;
  state.hand[0][0] = smithy;
  state.deckCount[0] = 3;
  state.deck[0][0] = province;  
  state.deck[0][1] = province;  
  state.deck[0][2] = province;  

  printf("Playing Smithy card.\n");
  playCard(0,0,0,0,&state);

  printf("Checking hand count... ");
  myassert(state.handCount[0] == 3);
  printf("Checking deck count... ");
  myassert(state.deckCount[0] == 0);
  printf("Checking hand cards... ");
  myassert(state.hand[0][0] == province);
  printf("Checking hand cards... ");
  myassert(state.hand[0][1] == province);
  printf("Checking hand cards... ");
  myassert(state.hand[0][2] == province);
  printf("Checking action count... ");
  myassert(state.numActions == 0);

  return 0;
}
