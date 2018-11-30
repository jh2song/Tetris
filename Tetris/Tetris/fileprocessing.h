#ifndef __FILE_PROCESSING_H__
#include <stdio.h>
typedef struct _ranking {
	int ranking;
	char name[50];
	int score;
}RankInfo;
void AdminSession();

void PrintFILE(); // FILE�� ���
void FILEToDB(RankInfo *DB, int * DBsize);
void Arrange(RankInfo *DB, int *DBsize);
void DBToFILE(RankInfo *DB, int *DBsize);
void FindandPrint(RankInfo *DB,int *DBsize, char * name,int score); // ������ 2 parameter�� Ž���� ���� ���ǵ��̴�.
void FindandRemove(RankInfo *DB, int *DBsize, int ranking);
void PrintDB(RankInfo *DB, int *DBsize);

void RankSession(char * curName,int curScore);
#endif