#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileprocessing.h"
#include "playFunc.h"

// 파일 출력 서식 : "%10s%20s%10s\n"
void AdminSession()
{
	int input;
	int ranking; char name[50]; int score;
	RankInfo DB[100];
	int DBsize = 0;
	printf("\n\t관리자 모드로 들어갈까요? 0:예 / 그 외 : 아니오    input : ");
	scanf_s("%d", &input);
	while (getchar() != '\n');
	if (input)
	{
		system("cls");
		return; // 관리자 모드 실행 안함. 바로 실행
	}
	else
	{	// 관리자 모드
		PrintFILE();
		FILEToDB(DB, &DBsize);
		puts("");
		puts("");
		puts("1. 정보 추가");
		puts("2. 정보 수정");
		puts("3. 정보 삭제");
		printf("입력 : ");
		scanf_s("%d", &input);
		system("cls");
		switch (input)
		{
		case 1: // 추가
			printf("이름 : ");
			scanf_s("%s", name, 50);
			printf("점수 : ");
			scanf_s("%d", &score);
			strcpy_s(DB[DBsize].name, 50, name);
			DB[DBsize].score = score;
			
			DBsize++;
			Arrange(DB, &DBsize);
			FindandPrint(DB, &DBsize, name, score);
			PrintDB(DB, &DBsize);
			DBToFILE(DB, &DBsize);
			break;
		case 2: // 수정
			printf("랭킹 입력 : ");
			scanf_s("%d", &ranking);
			printf("이름 : ");
			scanf_s("%s", name, 50);
			printf("점수 : ");
			scanf_s("%d", &score);
			strcpy_s(DB[ranking - 1].name, 50, name);
			DB[ranking - 1].score = score; // 수정
			Arrange(DB, &DBsize);
			FindandPrint(DB, &DBsize, name, score);
			PrintDB(DB, &DBsize);
			DBToFILE(DB, &DBsize);
			break;
		case 3: // 삭제
			printf("랭킹 입력 : ");
			scanf_s("%d", &ranking);
			FindandRemove(DB, &DBsize, ranking);
			Arrange(DB, &DBsize);
			PrintDB(DB, &DBsize);
			DBToFILE(DB, &DBsize);
			break;
		default:
			printf("잘못 입력하셨습니다.\n");
			break;
		}

	}

	printf("게임을 시작합니다!");
	system("pause>null");
	system("cls");
}

void PrintFILE()
{
	FILE *f;
	char line[100]; // 스트림

	if (fopen_s(&f, "score.txt", "r"))
	{
		printf("파일을 열 수가 없습니다.");
		fclose(f);
		return;
	}
	puts("===============================================");
	printf("%10s%20s%10s\n", "랭킹", "이름", "점수");
	puts("===============================================");
	fgets(line, 100, f);
	while (!feof(f))
	{
		fputs(line, stdout);
		fgets(line, 100, f);
	}
	fclose(f);
}

void FILEToDB(RankInfo *DB, int *DBsize)
{
	char line[100];
	FILE *f;

	if (fopen_s(&f, "score.txt", "r"))
	{
		DBsize = 0;
		return;
	}

	fgets(line, 100, f);
	while (!feof(f))
	{
		sscanf_s(line, "%d %s %d", &DB[*DBsize].ranking, DB[*DBsize].name, 50, &DB[*DBsize].score);
		(*DBsize)++;
		fgets(line, 100, f);
	}
	fclose(f);
}

void Arrange(RankInfo *DB, int *DBsize)
{
	int i, j;
	RankInfo temp;
	// 버블정렬
	for (i = 0; i < *DBsize; i++)
	{
		for (j = 0; j < *DBsize - 1; j++)
		{
			if (DB[j].score < DB[j + 1].score)
			{
				temp = DB[j];
				DB[j] = DB[j + 1];
				DB[j + 1] = temp;
			}
		}
	}

	for (i = 0; i < *DBsize; i++) // 랭킹 정리
	{
		DB[i].ranking = i + 1;
	}
}

void DBToFILE(RankInfo *DB, int *DBsize)
{
	FILE *f;
	if (fopen_s(&f, "score.txt", "w"))
	{
		printf("파일이 열리지 않습니다.\n");
	}
	int i;
	char line[100];
	for (i = 0; i < *DBsize; i++)
	{
		sprintf(line, "%10d%20s%10d\n", DB[i].ranking, DB[i].name, DB[i].score);
		fputs(line, f);
	}
	fclose(f);
}

void FindandPrint(RankInfo *DB,int *DBsize, char * name, int score)
{
	int i;
	for (i = 0; i < *DBsize; i++)
	{
		if (strcmp(DB[i].name, name) == 0 && DB[i].score == score)
		{
			puts("===============================================");
			printf("%10d%20s%10d\n",DB[i].ranking, DB[i].name, DB[i].score);
			puts("===============================================");
		}

	}
}

void PrintDB(RankInfo *DB, int *DBsize)
{
	int i;
	puts("===============================================");
	printf("%10s%20s%10s\n", "랭킹", "이름", "점수");
	puts("===============================================");
	for (i = 0; i < *DBsize; i++)
	{
		printf("%10d%20s%10d\n", DB[i].ranking, DB[i].name, DB[i].score);
	}
}

void FindandRemove(RankInfo *DB, int *DBsize, int ranking)
{
	int i;
	if (ranking > *DBsize)
		return;
	for (i = ranking - 1; i < *DBsize - 1; i++)
	{
		DB[i] = DB[i + 1];
	}
	--(*DBsize);
}

void RankSession(char * curName, int curScore)
{
	RankInfo DB[100];
	int DBsize = 0;

	FILEToDB(DB, &DBsize);
	strcpy_s(DB[DBsize].name, 50, curName);
	DB[DBsize].score = curScore;
	DBsize++;

	Arrange(DB, &DBsize);
	FindandPrint(DB, &DBsize, curName, curScore);
	PrintDB(DB, &DBsize);
	DBToFILE(DB, &DBsize);

	system("pause>null");
}