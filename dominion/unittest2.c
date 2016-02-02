#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;

  printf("Testing buyCard() function\n");

  state.whoseTurn = 0;
  state.discardCount[0] = 0;
  state.supplyCount[estate] = 0;
  state.supplyCount[province] = 4;
  state.numBuys = 3;
  state.coins = 9999;

  assert(!buyCard(province, &state));
  assert(state.coins == (9991));
  assert(state.numBuys == 2);
  assert(state.supplyCount[province] == 3);
  assert(state.discardCount[0] == 1);
  assert(state.discard[0][0] == province);
  printf("SUCCESS: province is bought.\n");

  assert(buyCard(estate, &state));
  printf("SUCCESS: estate purchase failed.\n");

  state.coins = 0;

  assert(buyCard(province, &state));
  printf("SUCCESS: province purchase failed (not enough coins).\n");

  state.numBuys = 0;
  state.coins = 9999;

  assert(buyCard(province, &state));
  printf("SUCCESS: province purchase failed (no buys left).\n");

  return 0;
}
