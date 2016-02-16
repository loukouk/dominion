#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_TESTS 3*100


int main() {

	int k_arr[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int numDiscard, choice2[MAX_PLAYERS], choice3[MAX_PLAYERS], seed, stewardHandPos[MAX_PLAYERS], bonus;

	struct gameState state;
	struct gameState original;

	srand(time(NULL));
	printf("Running Random Card Test for Steward...\n");
	printf("Test 1: draw 2 cards | Test 2: gain 2 coins | Test 3: discard 2 cards\n\n");

	for (int i = 0; i < MAX_TESTS; i++) {

		seed = rand();		//pick random seed	
		initializeGame(4, k_arr, seed, &state);	//initialize Gamestate
		for (int j = 0; j < state.numPlayers; j++) {

			memset((void *)state.deck[j], -1, sizeof(int)*MAX_DECK);
			memset((void *)state.hand[j], -1, sizeof(int)*MAX_HAND);
			memset((void *)state.discard[j], -1, sizeof(int)*MAX_DECK);

			state.deckCount[j] = rand() % MAX_DECK;
			state.handCount[j] = rand() % MAX_HAND;
			state.discardCount[j] = rand() % MAX_DECK;

			for (int k = 0; k < state.deckCount[j]; k++)
				state.deck[j][k] = rand() % treasure_map + 1;
			for (int k = 0; k < state.handCount[j]; k++)
				state.hand[j][k] = rand() % treasure_map + 1;
			for (int k = 0; k < state.discardCount[j]; k++)
				state.discard[j][k] = rand() % treasure_map + 1;

			choice2[j] = rand() % MAX_DECK;
			choice3[j] = rand() % MAX_DECK;
			if (state.handCount[j] > 10) {
				do {
					stewardHandPos[j] = rand() % state.handCount[j] - 1;
				} while (stewardHandPos[j] == choice2[j] || stewardHandPos[j] == choice3[j]);
				state.hand[j][stewardHandPos[j]] = steward;
			}
			else {
				stewardHandPos[j] = state.handCount[j];
				state.hand[j][state.handCount[j]] = steward;
				state.handCount[j]++;
			}
		}
		memcpy(&original, &state, sizeof(struct gameState));

		for (int j = 0; j < state.numPlayers; j++) {
			state.whoseTurn = j;
			state.numActions = 1;
			original.coins = 0;
			for (int k = 0; k < original.handCount[j]; k++) {
				if (original.hand[j][k] == copper)
					original.coins += 1;
				else if (original.hand[j][k] == silver)
					original.coins += 2;
				else if (original.hand[j][k] == gold)
					original.coins += 3;
			}
			
			if (i < MAX_TESTS / 3) {
				bonus = 0;
				for (int k = original.deckCount[j]; k >= original.deckCount[j] - 2; --k) {
					if (original.deck[j][k] == copper)
						bonus += 1;
					else if (original.deck[j][k] == silver)
						bonus += 2;
					else if (original.deck[j][k] == gold)
						bonus += 3;
				}
				playCard(stewardHandPos[j], 1, choice2[j], choice3[j], &state); 
				if (state.handCount[j] != original.handCount[j] + 1)
					printf("TEST 1 FAILURE FOR PLAYER %d: handCount should be %d but it is %d.\n", j, original.handCount[j] + 1, state.handCount[j]);

				if (original.deckCount[j] >= 2) {
					if (state.discardCount[j] != original.discardCount[j] + 1)
						printf("TEST 1 FAILURE FOR PLAYER %d: discardCount should be %d but it is %d.\n", j, original.discardCount[j] + 1, state.discardCount[j]);
				}
				else {
					if (state.discardCount[j] != 1) {
						printf("TEST 1 FAILURE FOR PLAYER %d: discardCount should be %d but it is %d.\n", j, 1, state.discardCount[j]);
					}
				}
					
				if (original.deckCount[j] >= 2) { 	
					if (state.deckCount[j] != original.deckCount[j] - 2)
						printf("TEST 1 FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", j, original.deckCount[j] - 2, state.deckCount[j]);
					for (int k = 0; k < original.deckCount[j] - 2; k++)
						if (original.deck[j][k] != state.deck[j][k])
							printf("TEST 1 FAILURE FOR PLAYER %d: deck[%d] should be %d but is %d.\n", j, k, original.deck[j][k], state.deck[j][k]);
				}
				else
					if (state.deckCount[j] != original.deckCount[j] + original.discardCount[j] - 2)
						printf("2TEST 1 FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", j, original.deckCount[j] + original.discardCount[j] - 2, state.deckCount[j]);

				if (original.deckCount[j] >= 2) {
					for (int k = 0, flag; k < state.handCount[j]; k++) {
						flag = 0;
						for (int l = 0; l < original.handCount[j]; l++) {
							if (state.hand[j][k] == original.hand[j][l]) {
								original.hand[j][l] = -1;
								flag = 1;
								break;
							}
						}
						if (!flag) {
							if (state.hand[j][k] == original.deck[j][original.deckCount[j]-1]) 
								original.deck[j][original.deckCount[j]-1] = -1;
							else if (state.hand[j][k] == original.deck[j][original.deckCount[j]-2]) 
								original.deck[j][original.deckCount[j]-2] = -1;
							else
								printf("TEST 1 FAILURE FOR PLAYER %d: hand[%d] is %d but cannot find that card in previous hand.\n", j, k, state.hand[j][k]);
						}
					}
				}

				if (state.discardCount[j] > original.discardCount[j]) {
					for (int k = 0; k < original.discardCount[j]; k++)
						if (original.discard[j][k] != state.discard[j][k])
							printf("TEST 1 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", j, k, original.discard[j][k], state.discard[j][k]);
				}
				if (state.discard[j][state.discardCount[j] - 1] != steward)
						printf("TEST 1 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", j, state.discardCount[j] - 1, steward, state.discard[j][state.discardCount[j] -1]);

	
				if (state.coins != original.coins + bonus)
					printf("TEST 1 FAILURE FOR PLAYER %d: Coins should be %d but are %d.\n", j, original.coins + bonus, state.coins);
				if (state.numActions != 0)
					printf("TEST 1 FAILURE FOR PLAYER %d: numActions should be %d but are %d.\n", j, 0, state.numActions);
			}


			else if (i < 2 * MAX_TESTS / 3) {
				bonus = 2;
				playCard(stewardHandPos[j], 2, choice2[j], choice3[j], &state); 

				if (state.deckCount[j] != original.deckCount[j])
					printf("TEST 2 FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", j, original.deckCount[j], state.deckCount[j]);
				if (state.handCount[j] != original.handCount[j] - 1)
					printf("TEST 2 FAILURE FOR PLAYER %d: handCount should be %d but it is %d.\n", j, original.handCount[j] - 1, state.handCount[j]);
				if (state.discardCount[j] != original.discardCount[j] + 1)
					printf("TEST 2 FAILURE FOR PLAYER %d: discardCount should be %d but it is %d.\n", j, original.discardCount[j] + 1, state.discardCount[j]);

				for (int k = 0; k < original.deckCount[j]; k++)
					if (original.deck[j][k] != state.deck[j][k])
						printf("TEST 2 FAILURE FOR PLAYER %d: deck[%d] should be %d but is %d.\n", j, k, original.deck[j][k], state.deck[j][k]);

				for (int k = 0, flag; k < state.handCount[j]; k++) {
					flag = 0;
					for (int l = 0; l < original.handCount[j]; l++) {
						if (state.hand[j][k] == original.hand[j][l]) {
							original.hand[j][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag)
						printf("TEST 2 FAILURE FOR PLAYER %d: hand[%d] is %d but cannot find that card in previous hand.\n", j, k, state.hand[j][k]);
				}

				for (int k = 0; k < original.discardCount[j]; k++)
					if (original.discard[j][k] != state.discard[j][k])
						printf("TEST 2 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", j, k, original.discard[j][k], state.discard[j][k]);

				if (state.discard[j][original.discardCount[j]] != steward)
						printf("TEST 2 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", j, original.discardCount[j], steward, state.discard[j][original.discardCount[j]]);

	
				if (state.coins != original.coins + bonus)
					printf("TEST 2 FAILURE FOR PLAYER %d: Coins should be %d but are %d.\n", j, original.coins + bonus, state.coins);
				if (state.numActions != 0)
					printf("TEST 2 FAILURE FOR PLAYER %d: numActions should be %d but are %d.\n", j, 0, state.numActions);
			}


			else {
				numDiscard = 1;

				if (choice2[j] < original.handCount[j]) numDiscard++;
				if (choice3[j] < original.handCount[j]) numDiscard++;

				if (choice2[j] < original.handCount[j]) {
					if (original.hand[j][choice2[j]] == copper)
						original.coins -= 1;
					else if (original.hand[j][choice2[j]] == silver)
						original.coins -= 2;
					else if (original.hand[j][choice2[j]] == gold)
						original.coins -= 3;
				}
				if (choice3[j] < original.handCount[j]) {
					if (original.hand[j][choice3[j]] == copper)
						original.coins -= 1;
					else if (original.hand[j][choice3[j]] == silver)
						original.coins -= 2;
					else if (original.hand[j][choice3[j]] == gold)
						original.coins -= 3;
				}


				if (playCard(stewardHandPos[j], 3, choice2[j], choice3[j], &state) < 0) {
					printf("playCard() failed on iteration %d, player %d, for TEST 3.\n", i, j);
					exit(EXIT_FAILURE);
				}

				if (state.deckCount[j] != original.deckCount[j])
					printf("TEST 3 FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", j, original.deckCount[j], state.deckCount[j]);
				if (state.handCount[j] != original.handCount[j] - numDiscard)
					printf("TEST 3 FAILURE FOR PLAYER %d: handCount should be %d but it is %d.\n", j, original.handCount[j] - numDiscard, state.handCount[j]);
				if (state.discardCount[j] != original.discardCount[j] + 1){
					printf("TEST 3 FAILURE FOR PLAYER %d: discardCount should be %d but it is %d.\n", j, original.discardCount[j] + 1, state.discardCount[j]);

printf("originalCount: %d, choice2: %d %d, choice3: %d %d, stewardPos: %d\n", original.handCount[j], choice2[j], original.hand[j][choice2[j]], choice3[j], original.hand[j][choice3[j]], stewardHandPos[j]);
}
				for (int k = 0; k < original.deckCount[j]; k++) {
					if (original.deck[j][k] != state.deck[j][k])
						printf("TEST 3 FAILURE FOR PLAYER %d: deck[%d] should be %d but is %d.\n", j, k, original.deck[j][k], state.deck[j][k]);
				}
				for (int k = 0; k < original.discardCount[j]; k++) {
					if (original.discard[j][k] != state.discard[j][k])
						printf("TEST 3 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", j, k, original.discard[j][k], state.discard[j][k]);
				}

				if (state.discard[j][state.discardCount[j] - 1] != steward)
						printf("TEST 3 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", j, state.discardCount[j] - 1, steward, state.discard[j][original.discardCount[j] - 1]);

				if (state.coins != original.coins ) {
					printf("TEST 3 FAILURE FOR PLAYER %d: Coins should be %d but are %d.\n", j, original.coins , state.coins);
				}
				if (state.numActions != 0)
					printf("TEST 3 FAILURE FOR PLAYER %d: numActions should be %d but are %d.\n", j, 0, state.numActions);

				for (int k = 0, flag; k < state.handCount[j]; k++) {
					flag = 0;
					for (int l = 0; l < original.handCount[j]; l++) {
						if (state.hand[j][k] == original.hand[j][l]) {
							original.hand[j][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag)
						printf("TEST 3 FAILURE FOR PLAYER %d: hand[%d] is %d but cannot find that card in previous hand.\n", j, k, state.hand[j][k]);
				}
			}
		}
	}

	printf("\nTests Complete\n");
	return 0;
}
