/*
main.c
rankalyzer
(c) Noah Wooten 2023, All Rights Reserved.
*/

// v1.0.0: Initial release
// v1.0.1: Fix rank number calculation
// v1.1.0: Add error checking, acceptable inputs, and unrankeed players.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

const char* RankNames[38] = {
	"Silver I", "s1",
	"Silver II", "s2",
	"Silver II", "s3",
	"Silver IV", "s4",
	"Silver Elite", "se",
	"Silver Elite Master", "sem",
	"Gold Nova I", "gn1",
	"Gold Nova II", "gn2",
	"Gold Nova III", "gn3",
	"Gold Nova Master", "gnm",
	"Master Guardian I", "mg1",
	"Master Guardian II", "mg2",
	"Master Guardian Elite", "mge",
	"Distinguished Master Gardian", "dmg",
	"Legendary Eagle", "le",
	"Legendary Eagle Master", "lem",
	"Supreme Master First Class", "smfc",
	"The Global Elite", "ge",
	"Unranked", "u",
};

#pragma warning(disable: 6031 6054)

int main(void) {
	// Declare variables
	int Ranks[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	char RankBuffer[64];
	
	// Display acceptable inputs
	char Input;
	printf("Would you like a list of acceptable ranks? [y/n]: ");
	scanf("%c", &Input);
	printf("\n");
	if ((Input & ~0x20) == 'Y') {
		for (int i = 0; i < 18; i++) { // purposely not including all 19 (including unranked)
			printf("Rank %i: %s or %s.\n", i, RankNames[(2 * i) + 0], RankNames[(2 * i) + 1]);
		}
		printf("Unranked: unranked or u.\n");
		printf("\n");
	}

	// Per team, and per player, prompt for ranks.
	for (int t = 0; t < 2; t++) {
		printf("Team #%i:\n", t + 1);
		for (int p = 0; p < 5; p++) {
			printf("\tPlayer #%i: ", p + 1);
			scanf("%s", RankBuffer);
			for (int i = 0; i < 38; i++) {
				if (!strcmp(RankBuffer, RankNames[i]))
					Ranks[(t * 5) + p] = (i - (i % 2)) / 2;
			}
			// Could probably do better than this
			if ((Ranks[(t * 5)] + p) == -1) {
				do {
					printf("\tInvalid rank for player #%i, please try again: ", p + 1);
					scanf("%s", RankBuffer);
					for (int i = 0; i < 38; i++) {
						if (!strcmp(RankBuffer, RankNames[i]))
							Ranks[(t * 5) + p] = (i - (i % 2)) / 2;
					}
				} while ((Ranks[(t * 5)] + p) == -1);
			}
		}
	}
	printf("\n");

	// Sum the ranks
	int UnrankedCount[2] = { 0, 0 };
	int RankSums[2] = { 0, 0 };
	for (int t = 0; t < 2; t++) {
		for (int p = 0; p < 5; p++) {
			if (Ranks[(t * 5) + p] == 18)
				UnrankedCount[t]++;
			else
				RankSums[t] += Ranks[(t * 5) + p];
		}
	}

	// Divide by player count
	for (int t = 0; t < 2; t++) {
		if (UnrankedCount[t] < 5)
			RankSums[t] /= 5 - UnrankedCount[t];
	}

	// Display per team
	for (int t = 0; t < 2; t++) {
		if (UnrankedCount[t] == 5)
			printf("Team #%i Average Rank: Unranked\n", t + 1);
		else
			printf("Team #%i Average Rank: %s (%i)\n", t + 1, RankNames[RankSums[t] * 2], RankSums[t]);
	}
	return 0;
}