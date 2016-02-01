#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main (int argc, char** argv) {
	struct gameState state;
	int firstDeck[MAX_PLAYERS][MAX_DECK];
	int numSame[MAX_PLAYERS];

	for (int j = 0; j < MAX_PLAYERS; j++)
		numSame[j] = 0;

	for (int j = 0; j < MAX_PLAYERS; j++) {	
		srand(time(NULL) + (100*j) );

		state.deckCount[j] = rand()%(MAX_DECK-1) + 2;

		for (int i = 0; i < state.deckCount[j]; i++)
			firstDeck[j][i] = i;

		memcpy(state.deck[j], firstDeck[j], state.deckCount[j]);
			
		shuffle(j, &state);

		for (int i = 0; i < state.deckCount[j]; i++)
			if (firstDeck[j][i] == state.deck[j][i])
				numSame[j]++;

		printf("player %d deck size is %d. ", j, state.deckCount[j]);
		assert(numSame[j] != state.deckCount[j]);
		printf("Success with %d card(s) in the same spot.\n",numSame[j]);
	}

	return 0;
}
