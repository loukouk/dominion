#include "myassert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;

  state.whoseTurn = 0;
  state.handCount[0] = 4;
  state.numActions = 3;
  state.hand[0][0] = steward;
  state.hand[0][1] = estate;
  state.hand[0][2] = estate;
  state.hand[0][3] = gardens;
  state.coins = 0;
  state.deckCount[0] = 2;
  state.deck[0][0] = steward;
  state.deck[0][1] = steward;

  printf("Playing Steward card #1.\n");
  playCard(0, 1, 0, 0, &state);
  printf("Checking hand count... ");
  myassert(state.handCount[0] == 5);
  printf("Checking hand cards... ");
  myassert(state.hand[0][0] == steward);
  myassert(state.hand[0][1] == estate);
  myassert(state.hand[0][2] == estate);
  myassert(state.hand[0][3] == gardens);
  myassert(state.hand[0][4] == steward);
  printf("Checking deck count... ");
  myassert(state.deckCount[0] == 0);
  printf("Checking coin count... ");
  myassert(state.coins == 0);

  printf("Playing Steward card #2.\n");
  playCard(0, 0, 1, 2, &state);
  printf("Checking hand count... ");
  myassert(state.handCount[0] == 2);
  printf("Checking hand cards... ");
  myassert(state.hand[0][0] == gardens);
  myassert(state.hand[0][1] == steward);
  printf("Checking deck count... ");
  myassert(state.deckCount[0] == 0);
  printf("Checking coin count... ");
  myassert(state.coins == 0);

  printf("Playing Steward card #3.\n");
  playCard(1, 2, 0, 0, &state);
  printf("Checking hand count... ");
  myassert(state.handCount[0] == 1);
  printf("Checking hand cards... ");
  myassert(state.hand[0][0] == gardens);
  printf("Checking deck count... ");
  myassert(state.deckCount[0] == 0);
  printf("Checking coin count... ");
  myassert(state.coins == 2);

  return 0;
}
