#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"

//#define DEBUG 0
#define NOISY_TEST 1

int checkDrawCard(int p, struct gameState *post) {
  int r;
    
  r = drawCard (p, post);

  return 0;
}

int main (int argc, char ** argv) {

  int i, n, p;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  initializeGame(MAX_PLAYERS, k, atoi(argv[1]), &G);

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 1000);
    checkDrawCard(p, &G);
  }

  printf ("ALL TESTS OK\n");

  exit(0);
}
