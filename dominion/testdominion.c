#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CHOICES 3
#define MIN_PLAYERS 2
#define NUM_KCARDS 10
#define MAX_TRIES 20
#define NUM_GAMES 100
#define MAX_TURNS 1000000
#define VERBOSE 1

int printState (int who, struct gameState * state)
{
	printf("\t\tHand - %d cards: ", state->handCount[who]);
	for (int i = 0; i < state->handCount[who]; i++)
		printf("/%d", state->hand[who][i]);
	printf("/\n");

	printf("\t\tDeck - %d cards: ", state->deckCount[who]);
	for (int i = 0; i < state->deckCount[who]; i++)
		printf("/%d", state->deck[who][i]);
	printf("/\n");

	printf("\t\tDiscard - %d cards: ", state->discardCount[who]);
	for (int i = 0; i < state->discardCount[who]; i++)
		printf("/%d", state->discard[who][i]);
	printf("/\n");

	return 0;
}

int hasActionCard(int player, struct gameState * state)
{
	for (int i = 0; i < state->handCount[player]; i++) {
		if (state->hand[player][i] >= adventurer && state->hand[player][i] <= treasure_map)
			return 1;
	}

	return 0;
}

int isUnique (int ind, int * k, int size)
{
	for (int i = 0; i < size; i++) {
		if (i != ind && k[ind] == k[i])
			return 0;
	}
	return 1;
}

int randKCards (int * k) {

	for (int i = 0; i < NUM_KCARDS; i++) {
		do {
			k[i] = rand() % (treasure_map - gold + 1) + gold;
		} while (!isUnique(i, k, NUM_KCARDS));
	}
	return 0;
}

int playGame ()
{
	int k_arr[NUM_KCARDS];
	struct gameState * state;
	int winners[MAX_PLAYERS], player, randCardPos, randBuy;
	int choice[3], counter = 0, turns = 0, num_players;

	state = newGame();
	memset(winners, 0, MAX_PLAYERS);
	memset(k_arr, -1, NUM_KCARDS);
	randKCards(k_arr);
	srand(time(NULL));

	num_players = rand() % (MAX_PLAYERS - 1) + MIN_PLAYERS;
	initializeGame( num_players, k_arr, rand(), state);

	printf("\tNumber of players: %d.\n", num_players);
	printf("\tKingdom Cards: /");
	for (int i = 0; i < NUM_KCARDS; i++)
		printf("%d/", k_arr[i]);
	printf("\n");

	while (!isGameOver(state)) {

		player = whoseTurn(state);

		if (state->handCount[player] + state->deckCount[player] + state->discardCount[player] <= 0) {
			printf("\tPlayer %d is out of cards. Game ended.\n", player);
			break;
		}

		if (VERBOSE) {
			printf("\tPlayer %d:\n", player);
			printState(player, state);
		}

		//ACTION PHASE
		state->phase = 0;
		counter = 0;
		while (state->numActions > 0 && hasActionCard(player, state)) {
			
			do {
				randCardPos = rand() % numHandCards(state);
			} while (handCard(randCardPos, state) < adventurer);

			choice[0] = rand() % MAX_CHOICES;
			choice[1] = rand() % numHandCards(state);
			choice[2] = rand() % numHandCards(state);

			if (playCard(randCardPos, choice[0], choice[1], choice[2], state) == 0 && VERBOSE)
				printf("\t\tPlayed card %d from position %d in hand with choices %d, %d, %d.\n", state->hand[player][randCardPos], randCardPos, choice[0], choice[1], choice[2]);

			if (counter > MAX_TRIES) {
				if (VERBOSE) printf("\t\tNo cards played this turn.\n");
				break;
			}
			counter++;
		}

		//BUY PHASE
		state->phase = 1;
		counter = 0;
		while (state->numBuys > 0 && state->coins > 1) {

			randBuy = rand() % (treasure_map+1);
			if (buyCard(randBuy, state) == 0 && VERBOSE)
				printf("\t\tBought Card %d and placed it in hand.\n", randBuy);

			if (counter > MAX_TRIES) {
				if (VERBOSE) printf("\t\tNo cards bought this turn.\n");
				break;
			}
			counter++;
		}

		//CLEAN-UP PHASE
		state->phase = 2;
		endTurn(state);
		if (VERBOSE) printf("\t\tEnded turn. Hand discarded and redrawn.\n");

		turns++;
		if (turns >= num_players*MAX_TURNS) {
			if (VERBOSE) printf("\tAmount of turns exceeded (%d). Forced Ending.\n", MAX_TURNS);
			break;
		}
	}

	printf("\n\t--- RESULTS ---\n");
	getWinners( winners, state);
	for (int i = 0; i < state->numPlayers; i++) {
		if (winners[i])
			printf("\tPlayer %d wins with %d estates, %d duchys, %d provinces and %d gardens\n",i,fullDeckCount(i, estate, state),fullDeckCount(i, duchy, state),fullDeckCount(i, province, state),fullDeckCount(i, gardens, state));
		else
			printf("\tPlayer %d lost with %d estates, %d duchys, %d provinces and %d gardens\n",i,fullDeckCount(i, estate, state),fullDeckCount(i, duchy, state),fullDeckCount(i, province, state),fullDeckCount(i, gardens, state));
		if (VERBOSE) printState(i, state);
	}		

	return 0;
}

int main() 
{
	printf("********* DOMINION TEST: %d GAMES **********\n", NUM_GAMES);

	for (int i = 0; i < NUM_GAMES; i++) {
		printf("\n------------ GAME %i -------------\n", i+1);
		if (playGame() == -1) {
			printf("Something is wrong, test failed at runtime.\n");
			return(EXIT_FAILURE);
		}
	}

	return(EXIT_SUCCESS);
}
