/*
main.c
rankalyzer
(c) Noah Wooten 2023, All Rights Reserved.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

const char* RankNames[36] = {
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
};

#pragma warning(disable: 6054)

int main(void) {
	// Declare variables
	int Ranks[10] = { 0 };
	char RankBuffer[64];
	
	// Per team, and per player, prompt for ranks.
	for (int t = 0; t < 2; t++) {
		printf("Team #%i:\n", t + 1);
		for (int p = 0; p < 5; p++) {
			printf("\tPlayer #%i: ", p + 1);
			int r = scanf("%s", RankBuffer);
			for (int i = 0; i < 36; i++) {
				if (!strcmp(RankBuffer, RankNames[i]))
					Ranks[(t * 5) + p] = (i - (i % 2)) / 2;
			}
		}
	}
	printf("\n");

	// Sum the ranks
	int RankSums[2] = { 0, 0 };
	for (int t = 0; t < 2; t++) {
		for (int p = 0; p < 5; p++)
			RankSums[t] += Ranks[(t * 5) + p];
	}

	// Divide by player count
	RankSums[0] /= 5;
	RankSums[1] /= 5;

	// Display per team
	for (int t = 0; t < 2; t++)
		printf("Team #%i Average Rank: %s (%i)\n", t + 1, RankNames[RankSums[t] * 2], RankSums[t]);

	return 0;
}