/* Copyright.Dong-Eui univ. 1st grade 20183016 Jihoon Song
���Ǵ��б� 1�г� 2�б� �������α׷��ֹ׽ǽ��� (001)
C��� ������Ʈ (������ : �强�� ������)
��Ʈ����


�ڵ� : 20183016 ������
*/

#include <stdio.h>
#include <Windows.h>
#include "playFunc.h"
#include "fileprocessing.h"

int main()
{
	gameInfo GameInfo;
	int i;
	MakeEmptyFile(); // score.txt�� ���� �� ������ִ� �Լ�
	AdminSession();	// ������ ����
	Login(&GameInfo); // �α��� ����
	Init(&GameInfo); // �ʱ�ȭ

	PrintWall(); // �� ���
	while (1)
	{
		CursorDelete(); // Ŀ�� �����
		GameInfo.curY++;
		TetrisOneFrame(&GameInfo);	// ��Ʈ���� ������ �� �����Լ�
		Speed(&GameInfo); // ���ǵ�����



		ScorePrint(&GameInfo); // ���� ����Ʈ
		for (i = 0; i < 5; i++) // Ű���� 5�� �Է� ����
		{
			if (Keyboard(&GameInfo)) // �����̽��� ���� �� : 1
			{
				TetrisOneFrame(&GameInfo); // �浹ó���� ���� �� ������ �̵� �� �� stackedBlock�� ��Ʈ���̳� ����
				RestartInit(&GameInfo); // �� �ʱ�ȭ
				break;
			}
			Sleep(GameInfo.diff);
		}
		if (GameInfo.isGameover == 1) // ���ӿ��� ���� ���� �� ���ѹݺ� Ż��
			break;
	}
	system("cls");
	RankSession(GameInfo.name, GameInfo.score); // ��ŷ ó�� �������� �Ѿ
	system("cls");
	
	return 0;
}