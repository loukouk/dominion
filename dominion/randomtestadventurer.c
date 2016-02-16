#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define MAX_TESTS 1000
#define DEBUG 0

//This randomly tests Adventurer

int main() {

	int k_arr[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

	struct gameState state, original;
	int seed, adventurerPos[MAX_PLAYERS], treasureCount, revealCount, treasurePos[2] = {-1,-1};

	srand(time(NULL));
	printf("Running Random Adventurer Test\n\n");

	for (int i = 0; i < MAX_TESTS; i++) {

		seed = rand();		//pick random seed
		initializeGame(MAX_PLAYERS, k_arr, seed, &state);	//initialize Gamestate 

		for (int j = 0; j < MAX_PLAYERS; j++) {

			state.deckCount[j]    = rand() % MAX_DECK;
			state.discardCount[j] = rand() % MAX_DECK;
			state.handCount[j]    = rand() % MAX_HAND;

			for (int k = 0; k < state.deckCount[j]; k++)
				state.deck[j][k] = rand() % treasure_map + 1;
			for (int k = 0; k < state.handCount[j]; k++)
				state.hand[j][k] = rand() % treasure_map + 1;
			for (int k = 0; k < state.discardCount[j]; k++)
				state.discard[j][k] = rand() % treasure_map + 1;

			if (state.handCount[j] > 0)
				adventurerPos[j] = rand() % state.handCount[j];
			else {
				adventurerPos[j] = 0;
				state.handCount[j] = 1;
			}
			state.hand[j][adventurerPos[j]] = adventurer;
		}
		memcpy(&original, &state, sizeof(struct gameState));

		for (int j = 0; j < MAX_PLAYERS; j++) {
			state.numActions = 1;
			state.whoseTurn = j;

			treasureCount = 0;
			revealCount = 0;
			treasurePos[0] = -1;
			treasurePos[1] = -1;
			for (int k = state.deckCount[j] - 1; k >= 0; k--) {
				revealCount++;
				if (state.deck[j][k] >= copper && state.deck[j][k] <= gold){
					treasurePos[treasureCount] = k;
					treasureCount++;
					if (treasureCount >= 2)
						break;
				}
			}

			if (treasurePos[1] == -1) {
				if (DEBUG) printf("There aren't 2 treasures in the deck! Next iteration...\n");
			}
			else {
				if (playCard(adventurerPos[j], 0, 0, 0, &state) < 0) {
					printf("playCard() failed to execute. Exiting...\n");
					exit(EXIT_FAILURE);
				}

				if (state.deckCount[j] != original.deckCount[j] - revealCount)
					printf("TEST FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", j, original.deckCount[j] - revealCount, state.deckCount[j]);
				if (state.handCount[j] != original.handCount[j] + treasureCount)
					printf("TEST FAILURE FOR PLAYER %d: handCount should be %d but it is %d.\n", j, original.handCount[j] + treasureCount, state.handCount[j]);
				if (state.discardCount[j] != original.discardCount[j] + revealCount - treasureCount)
					printf("TEST FAILURE FOR PLAYER %d: discardCount should be %d but it is %d.\n", j, original.discardCount[j] + revealCount - treasureCount, state.discardCount[j]);

				for (int k = 0; k < original.deckCount[j] - revealCount; k++)
					if (original.deck[j][k] != state.deck[j][k])
						printf("TEST FAILURE FOR PLAYER %d: deck[%d] should be %d but is %d.\n", j, k, original.deck[j][k], state.deck[j][k]);

				for (int k = 0; k < original.handCount[j]; k++)
					if (original.hand[j][k] != state.hand[j][k])
						printf("TEST FAILURE FOR PLAYER %d: hand[%d] should be %d from old hand but is %d.\n", j, k, original.hand[j][k], state.deck[j][k]);
				for (int k = original.handCount[j], l = 0; k < original.handCount[j] + treasureCount; k++, l++)
					if (original.deck[j][treasurePos[l]] != state.hand[j][k])
						printf("TEST FAILURE FOR PLAYER %d: hand[%d] should be %d from old deck but is %d.\n", j, k, original.deck[j][l], state.hand[j][treasurePos[l]]);

				for (int k = 0; k < original.discardCount[j]; k++) {
					if (original.discard[j][k] != state.discard[j][k]){
//						printf("TEST FAILURE FOR PLAYER %d: discard[%d] should be %d from old discard but is %d.\n", j, k, original.discard[j][k], state.discard[j][k]);
					}
				}

				for (int k = state.discardCount[j] - 1, l = original.deckCount[j]-1, m = 0, c = 0; k >= original.discardCount[j]; k--, l--, c++) {
//printf("state discard: %d %d    original deck: %d %d\n", k, state.discard[j][k], l, original.deck[j][l]);

					if (l == treasurePos[m]) {
						l--;
						m++;
					}
					if (state.discard[j][k] != original.deck[j][l]) {
						printf("TEST FAILURE FOR PLAYER %d: discard[%d] should be %d from old deck but is %d.\n", j, k, original.deck[j][l], state.discard[j][k]);
					}
				}						
			}
		}
	}
	
	printf("\nTests Complete\n");

	return 0;
}
