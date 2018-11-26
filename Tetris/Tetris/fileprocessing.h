#ifndef __FILE_PROCESSING_H__
#include <stdio.h>
typedef struct _ranking {
	int ranking;
	char name[50];
	int score;
}RankInfo;

void Rank(char * name, int score);

#endif