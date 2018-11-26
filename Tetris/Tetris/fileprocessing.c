#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileprocessing.h"
#include "playFunc.h"

void Rank(char * name, int score)
{
	FILE *f;
	RankInfo curRanking; // curRanking:현재 내가 받은 점수와 이름, 랭킹 구조체
	RankInfo data[100]; // 점수 보드에 올라갈 사람
	char line[100]; // 임시 입력받은 문자열 저장 공간
	
	// 초기값 지정
	int cnt = 0, i, j;
	strcpy_s(curRanking.name, 50, name);
	curRanking.score = score;
	curRanking.ranking = 1;

	if (fopen_s(&f, "score.txt", "r"))
	{
		cnt = 1;
		data[0] = curRanking;
		/*
		파일이 없다면(게임이 처음) 점수보드배열에 0번지를 curRanking으로 두고 빠져나옴
		*/
	}
	else
	{
		fgets(line, 100, f);
		while (!feof(f))
		{
			sscanf(line, "%d%s%d", &data[cnt].ranking, data[cnt].name, &data[cnt].score);
			fgets(line, 100, f);
			cnt++;
		}

		/*
		점수가 높은순으로 검색
		만약 curRanking의 점수가 높다면
		curRanking의 원소값 ranking을 배열값 + 1로 저장(순위)
		*/
		for (i = 0; i < cnt; i++)
		{
			if (data[i].score < curRanking.score) 
			{
				curRanking.ranking = i + 1;
				break;
			}
		}
		/*
		점수보드 제일 마지막인 경우 처리
		*/
		if (i == cnt)
		{
			data[cnt] = curRanking;
			data[cnt].ranking++;
			curRanking.score = data[cnt].ranking;
		}
		else
			/*
			점수보드 중간에 curRanking이 들어가야할때 배열 재정리 알고리즘
			*/
		{
			for (j = cnt; j > i; j--) // i가 ranking이 들어가야 되는 부분
			{
				data[j] = data[j - 1];
				data[j].ranking++;
			}
			data[i] = curRanking;
		}
		cnt++;
		fclose(f);
	}

	if (fopen_s(&f, "score.txt", "w"))
	{
		printf("파일이 열리지 않습니다.\n");
	}
	// 파일과 콘솔에 결과값 출력
	printf("당신의 score\n");
	puts("===============================================================");
	printf("%4s%10s%6s\n", "랭킹", "이름", "점수" );
	puts("===============================================================");
	printf("%4d%10s%6d\n", curRanking.ranking, curRanking.name, curRanking.score);
	puts("\n\n\n\n");
	puts("점수 보드\n");
	puts("===============================================================");
	printf("%4s%10s%6s\n", "랭킹", "이름", "점수");
	puts("===============================================================");
	for (i = 0; i < cnt; i++)
	{
		printf("%4d%10s%6d\n", data[i].ranking, data[i].name, data[i].score);
	}
	for (i = 0; i < cnt; i++)
	{
		fprintf(f,"%4d%10s%6d\n", data[i].ranking, data[i].name, data[i].score);
	}
	fclose(f);
	system("pause>null");
}