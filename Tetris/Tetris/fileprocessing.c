#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileprocessing.h"
#include "playFunc.h"

void Rank(char * name, int score)
{
	FILE *f;
	RankInfo curRanking; // curRanking:���� ���� ���� ������ �̸�, ��ŷ ����ü
	RankInfo data[100]; // ���� ���忡 �ö� ���
	char line[100]; // �ӽ� �Է¹��� ���ڿ� ���� ����
	
	// �ʱⰪ ����
	int cnt = 0, i, j;
	strcpy_s(curRanking.name, 50, name);
	curRanking.score = score;
	curRanking.ranking = 1;

	if (fopen_s(&f, "score.txt", "r"))
	{
		cnt = 1;
		data[0] = curRanking;
		/*
		������ ���ٸ�(������ ó��) ��������迭�� 0������ curRanking���� �ΰ� ��������
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
		������ ���������� �˻�
		���� curRanking�� ������ ���ٸ�
		curRanking�� ���Ұ� ranking�� �迭�� + 1�� ����(����)
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
		�������� ���� �������� ��� ó��
		*/
		if (i == cnt)
		{
			data[cnt] = curRanking;
			data[cnt].ranking++;
			curRanking.score = data[cnt].ranking;
		}
		else
			/*
			�������� �߰��� curRanking�� �����Ҷ� �迭 ������ �˰���
			*/
		{
			for (j = cnt; j > i; j--) // i�� ranking�� ���� �Ǵ� �κ�
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
		printf("������ ������ �ʽ��ϴ�.\n");
	}
	// ���ϰ� �ֿܼ� ����� ���
	printf("����� score\n");
	puts("===============================================================");
	printf("%4s%10s%6s\n", "��ŷ", "�̸�", "����" );
	puts("===============================================================");
	printf("%4d%10s%6d\n", curRanking.ranking, curRanking.name, curRanking.score);
	puts("\n\n\n\n");
	puts("���� ����\n");
	puts("===============================================================");
	printf("%4s%10s%6s\n", "��ŷ", "�̸�", "����");
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