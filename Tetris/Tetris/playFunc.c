#define _CRT_NONSTDC_NO_WARNINGS
//Ű���尪��
#define LEFT 75 //�·� �̵� 
#define RIGHT 77 //��� �̵� 
#define UP 72 //ȸ�� 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop


#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "fileprocessing.h"
#include "playFunc.h"

int tetrimino[7][4][4][4] = {
	// ù ��° �Ķ���� : ����� ����, �� ��° �Ķ���� : ȸ������
	// �� ��° �Ķ���� : ��Ʈ���̳��� Y�� �� ��° �Ķ���� : ��Ʈ���̳��� X��
	// 0�� �� ���� 1�� ��
	// I�̳�
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,

	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,

	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	// O�̳�
	0,1,1,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,1,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,1,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,1,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	// Z�̳�
	0,0,1,0,
	0,1,1,0,
	0,1,0,0,
	0,0,0,0,

	0,1,1,0,
	0,0,1,1,
	0,0,0,0,
	0,0,0,0,

	0,0,1,0,
	0,1,1,0,
	0,1,0,0,
	0,0,0,0,

	0,1,1,0,
	0,0,1,1,
	0,0,0,0,
	0,0,0,0,

	// S�̳�
	0,1,0,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,

	0,0,1,1,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,

	0,0,1,1,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	// J�̳�
	0,1,0,0,
	0,1,1,1,
	0,0,0,0,
	0,0,0,0,

	0,1,1,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,

	1,1,1,0,
	0,0,1,0,
	0,0,0,0,
	0,0,0,0,

	0,0,1,0,
	0,0,1,0,
	0,1,1,0,
	0,0,0,0,

	// L�̳�
	0,0,1,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	0,1,1,0,
	0,0,0,0,

	0,1,1,1,
	0,1,0,0,
	0,0,0,0,
	0,0,0,0,

	0,1,1,0,
	0,0,1,0,
	0,0,1,0,
	0,0,0,0,

	// T�̳�
	0,1,1,1,
	0,0,1,0,
	0,0,0,0,
	0,0,0,0,

	0,0,1,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,

	0,0,1,0,
	0,1,1,1,
	0,0,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,1,0,
	0,1,0,0,
	0,0,0,0
};
//��Ʈ���̳� 4�����迭
int tetrisGameBoard[23][13]; // ����:23 ����:13
// stackedBlock+���� ������ ���Ӻ���迭
int stackedBlock[21][11];
// ���� �� ������� �迭

void Login(gameInfo * GameInfo)
{
	printf("\n\n");
	printf("\t\t��Ʈ������ ���Ű� ȯ���մϴ�!!!\n\t\t\t copyright DEU 20183016 ������\n");
	printf("\n\t\t����� �̸��� �����ּ���! : ");
	scanf_s("%s", GameInfo->name, 50);
	system("cls");
}

/*
���� �ʱ�ȭ
X:4 Y:0
����� ����
diff(���̵�) 200
direction(����) : 0
isGameover(���ӿ��� ����) : 0
score : 0
stackedBlock 0���� �ʱ�ȭ
*/
void Init(gameInfo * GameInfo)
{
	int i, j;
	
	GameInfo->curX = 4, GameInfo->curY = 0,
	GameInfo->curShape = RandomShape(),
	GameInfo->isStart = 1, GameInfo->diff = 200, GameInfo->direction = 0,
	GameInfo->isGameover = 0;
	GameInfo->score = 0;
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 11; j++)
		{
			stackedBlock[i][j] = 0;
		}
	}
}

/*
�� ���
*/
void PrintWall()
{
	int i;
	for (i = 0; i < 13; i++)
		printf("��");
	puts("");
	for (i = 1; i < 22; i++)
	{
		printf("��                      ��\n");
	}
	for (i = 0; i < 13; i++)
		printf("��");
	puts("");
	
}

/*
Ŀ�� ����� �Լ�
CONSOLE_CURSOR_INFO ����ü ����
dwSize �β� : 1, bVisible : FALSE (�����)
SetConsoleCursorInfo�Լ��� �ڵ鰪�� ����
*/
void CursorDelete() // CONSOLE_CURSOR_INFO ��� ����ü�� �̿�, Ŀ���� ������.  
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, }; // ����ü�� �����Ѵ�.
	cursorInfo.dwSize = 1;	// �β� 1~100 Ŭ���� �β���
	cursorInfo.bVisible = FALSE;	// FALSE : �����, TRUE : ���̱�
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/*
MakeTetrisBoard(); -> ��Ʈ���̳��� �̵��� ���� ���� tetrisGameBoard�� ���� �����ϰ� 0���� �ʱ�ȭ
isNoDownBlock -> �ٴڿ� �� ������ Ȯ��. �浹 ó���� ���� ���
CopyToGameBoard -> 1������ �� �ٲ� ��Ʈ���̳븦 tetrisGameBoard�� ����

*/
void TetrisOneFrame(gameInfo * GameInfo)
{

	if (GameInfo->isStart == 1)//�� �����̸�
	{

		MakeTetrisBoard();
		// �� ������ Ȯ��
		if (isNoDownblock(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
			, GameInfo->curX, GameInfo->curY))
		{
			GameInfo->isGameover = 1;
			return;
		}

		CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
			, GameInfo->curX, GameInfo->curY);
		GameInfo->isStart = 0;

	}
	else // �� ������ �ƴϸ�
	{

		MakeTetrisBoard();

		// �� ������ Ȯ��
		if (isNoDownblock(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
			, GameInfo->curX, GameInfo->curY))
		{

			//GameInfo->curY++;
			CopyToStacked(stackedBlock, tetrimino[GameInfo->curShape][GameInfo->direction]
				, GameInfo->curX, GameInfo->curY);
			//GameInfo->isStart = 1;
			GameInfo->score += 4;
			MakeTetrisBoard();
			LineClearCheck(GameInfo); // ���� Ŭ���� �Ǵ��� Ȯ��
			Print();
			RestartInit(GameInfo);
		
			return;


		}

		CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
			, GameInfo->curX, GameInfo->curY);
	}

	Print();
}

/*
���� ���� �ӵ� ��� (Sleep Ư¡�� ū ��ȭ�� ����)
*/
void Speed(gameInfo * GameInfo)
{
	if (GameInfo->score > 50)
		GameInfo->diff = 100; // LEVEL 1
	else if (GameInfo->score > 100)
		GameInfo->diff = 50;
	else if (GameInfo->score > 150)
		GameInfo->diff = 25;
	else if (GameInfo->score > 200)
		GameInfo->diff = 1;
}
/*
���� ���
*/
void ScorePrint(gameInfo * GameInfo)
{
	gotoxy(34, 1);
	printf("����� �̸� : %s", GameInfo->name);
	gotoxy(34, 2);
	printf("���� : %d��", GameInfo->score);
}

int Keyboard(gameInfo * GameInfo)
{
	int key;

	if (kbhit())  //Ű�Է��� �ִ� ���  
	{
		key = getch(); //Ű���� ����
		if (key == 224)//����Ű�ΰ�� 
		{
			do { key = getch(); } while (key == 224);//����Ű���ð��� ���� 
			switch (key)
			{
			case LEFT: //����Ű ��������  
				--GameInfo->curX;
				if (IsCrashCheck(GameInfo, tetrimino[GameInfo->curShape][GameInfo->direction]))
				{
					++GameInfo->curX;
					break;
				}
				MakeTetrisBoard();
				CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
					, GameInfo->curX, GameInfo->curY);
				Print();
				break;
			case RIGHT: //������ ����Ű ��������
				++GameInfo->curX;
				if (IsCrashCheck(GameInfo, tetrimino[GameInfo->curShape][GameInfo->direction]))
				{
					--GameInfo->curX;
					break;
				}
				MakeTetrisBoard();
				CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
					, GameInfo->curX, GameInfo->curY);
				Print();
				break;
			case DOWN: //�Ʒ��� ����Ű �������� 
				++GameInfo->curY;
				if (isNoDownblock(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
					, GameInfo->curX, GameInfo->curY))
				{
					--GameInfo->curY;
					break;
				}
				if (IsCrashCheck(GameInfo, tetrimino[GameInfo->curShape][GameInfo->direction]))
				{
					--GameInfo->curY;
					break;
				}
				MakeTetrisBoard();
				CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
					, GameInfo->curX, GameInfo->curY);
				Print();
				break;
			case UP: //���� ����Ű �������� 
				MakeTetrisBoard();
				if (isNoDownblock(tetrisGameBoard, tetrimino[GameInfo->curShape][(GameInfo->direction + 1) % 4]
					, GameInfo->curX, GameInfo->curY))
				{
					break;
				}
				if (IsCrashCheck(GameInfo, tetrimino[GameInfo->curShape][(GameInfo->direction + 1) % 4]))
				{
					break;
				}
				CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][(GameInfo->direction + 1) % 4]
					, GameInfo->curX, GameInfo->curY);
				Print();
				GameInfo->direction = (GameInfo->direction + 1) % 4;
				break;
			}
			Sleep(5);
		}
		else//����Ű�� �ƴѰ�� 
		{
			switch (key)
			{
			case SPACE: //�����̽�Ű �������� 
				/*
				�ٴ� �浹 �ϱ� ������ Y���� ���ѹݺ����� ������Ŵ
				*/
				while (!isNoDownblock(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction],
					GameInfo->curX, GameInfo->curY))
				{
					++GameInfo->curY;
					MakeTetrisBoard();
					CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
						, GameInfo->curX, GameInfo->curY);
				}
				MakeTetrisBoard();
				CopyToStacked(stackedBlock, tetrimino[GameInfo->curShape][GameInfo->direction]
					, GameInfo->curX, GameInfo->curY);
				CopyToGameBoard(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
					, GameInfo->curX, GameInfo->curY);
				GameInfo->score += 4;
				return 1;
				break;
			}
		}
	}

	while (kbhit()) getch(); //Ű���۸� ��� 
	return 0;
}

void MakeTetrisBoard() // ��Ʈ���� ���� ���� 1:�� 0:�� ����
{
	int i, j;

	for (i = 0; i < 23; i++)
	{
		for (j = 0; j < 13; j++)
		{
			tetrisGameBoard[i][j] = 0;
		}
	}


	for (i = 0; i < 13; i++)
	{
		tetrisGameBoard[0][i] = 1;
	}
	for (i = 1; i < 22; i++)
	{
		tetrisGameBoard[i][0] = 1;
		tetrisGameBoard[i][12] = 1;
	}
	for (i = 0; i < 13; i++)
	{
		tetrisGameBoard[22][i] = 1;
	}

	/*
	int tetrisGameBoard[23][13]; // ����:23 ����:13
	int stackedBlock[21][11] = { 0 };
	*/

	for (i = 1; i < 22; i++)
	{
		for (j = 1; j < 12; j++)
		{
			if (stackedBlock[i-1][j-1] == 1)
				tetrisGameBoard[i][j]= 1;
		}

	}

}

/*
���� ���� �̻��� ��ǥ���϶� �浹 ó���� �ϴ� �Լ�
*/
int IsCrashCheck(gameInfo *GameInfo, int tetrimino[][4])
{
	int i, j;
	int n = 0, m = 0;

	DeleteTetrimino(tetrisGameBoard, tetrimino, GameInfo->curX, GameInfo->curY);

	for (i = GameInfo->curY; i < GameInfo->curY + 4; i++)
	{
		for (j = GameInfo->curX; j < GameInfo->curX + 4; j++)
		{

			if (tetrimino[n][m] == 1 && (tetrisGameBoard[i][j] == 1 || stackedBlock[i - 1][j - 1] == 1 ||
				i <= 0 || i >= 22 || j <= 0 || j >= 12))
			{
				CopyToGameBoard(tetrisGameBoard, tetrimino, GameInfo->curX, GameInfo->curY);
				return 1;
			}

			m++;
		}
		m = 0;
		n++;
	}

	CopyToGameBoard(tetrisGameBoard, tetrimino, GameInfo->curX, GameInfo->curY);
	return 0;
}

/*
�ٴ� �浹 ���� Ȯ��
*/
int isNoDownblock(int gameboard[][13], int tetrimino[][4], int curX, int curY)
{
	int i, j;
	int m = 0, n = 0;
	DeleteTetrimino(gameboard, tetrimino, curX, curY);

	for (i = curY; i < curY + 4; i++)
	{
		for (j = curX; j < curX + 4; j++)
		{
			if (tetrimino[n][m] == 1 && (tetrisGameBoard[i][j] == 1 || stackedBlock[i - 1][j - 1] == 1 ||
				i <= 0 || i >= 22 || j <= 0 || j >= 12))
			{
				CopyToGameBoard(gameboard, tetrimino, curX, curY);
				return 1;
			}

			m++;
		}
		m = 0;
		n++;
	}

	CopyToGameBoard(gameboard, tetrimino, curX, curY);
	return 0;
}

/*
��Ʈ���̳븦 tetrisGameBoard�� ����
*/
void CopyToGameBoard(int gameboard[][13], int tetrimino[][4],
	int curX, int curY)
{
	int i, j;
	int m = 0, n = 0;

	for (i = curY; i < curY + 4; i++)
	{
		for (j = curX; j < curX + 4; j++)
		{
			if (tetrimino[m][n] == 1)
				gameboard[i][j] = 1;
			++n;
		}
		++m;
		n = 0;
	}
}

/*
StackedBlock�� ��Ʈ���̳븦 ����
*/
void CopyToStacked(int stackedBlock[][11], int tetrimino[][4], int curX, int curY)
{
	int i, j;
	int m = 0, n = 0;
	for (i = curY - 2; i < curY + 2; i++)
	{
		for (j = curX - 1; j < curX + 3; j++)
		{
			if ((i < 0 || i >= 21) || (j < 0 || j >= 11))
			{
				n++;
				continue;
			}

			if (tetrimino[m][n] == 1)
				stackedBlock[i][j] = 1;
			n++;
		}
		n = 0;
		m++;
	}
}

/*
���� Ŭ���� Ȯ�� �Լ�
*/
void LineClearCheck(gameInfo * GameInfo)
{
	int i, j;
	int check = 0, combo = 0;
	for (i = 20; i >= 0; i--)
	{
		for (j = 0; j < 11; j++)
		{
			if (stackedBlock[i][j] == 1)
			{
				check++;
			}
		}
		if (check == 11) // �� �� ���� Ŭ�����
		{
			combo++;
			LineClear(i, combo);
			GameInfo->score += combo * 30; // �޺��� ���� �߰� ����
			i++; // ���� �������Ƿ� �ٽ� �˻縦 ���� i�� 1 ������Ŵ

		}
		check = 0;
	}
}

/*
parameter�� Ŭ���� ���� �޾Ƽ� �� �ٿ� stackedBlock�� 0���� �ʱ�ȭ
*/
void LineClear(int row, int combo)
{
	int i;
	for (i = 0; i < 11; i++)
	{
		stackedBlock[row][i] = 0;
	}

	MakeTetrisBoard();
	Print();

	gotoxy(7, row + 1);
	printf("combo : %d", combo); // �޺� ���
	Sleep(200);
	stackedArrange(row);
}

void stackedArrange(int row)
{
	int i, j;
	int temp[11];
	for (i = 0; i < 11; i++)
	{
		temp[i] = stackedBlock[row - 1][i];
	}
	for (i = row; i >= 0; i--)
	{
		for (j = 0; j < 11; j++)
		{
			stackedBlock[i][j] = temp[j];
			temp[j] = stackedBlock[i - 2][j];
		}
	}
	MakeTetrisBoard();
}

//tetrisGameBoard�� 1�Ͻ� �� 0 �Ͻ� ���� ���
void Print()
{
	int i, j;
	for (i = 1; i < 22; i++)
	{
		gotoxy(2, i);
		for (j = 1; j < 12; j++)
		{
			if (tetrisGameBoard[i][j] == 1)
			{
				printf("��");
			}
			else
			{
				printf("  ");
			}
		}
	}
}

void RestartInit(gameInfo *GameInfo)
{
	GameInfo->curX = 4, GameInfo->curY = 0,
		GameInfo->curShape = RandomShape(),
		GameInfo->direction = 0,
		GameInfo->isGameover = 0,
		GameInfo->isStart = 1;
}

int RandomShape()
{
	srand((unsigned)time(NULL)); // srand(time(NULL))�ϸ� ������
	return rand() % 7;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
tetrisGameBoard���� tetrimino�� ����
*/
void DeleteTetrimino(int gameboard[][13], int tetrimino[][4],
	int curX, int curY)
{
	int i, j;
	int m = 0, n = 0;

	for (i = curY; i < curY + 4; i++)
	{
		for (j = curX; j < curX + 4; j++)
		{
			if (tetrimino[m][n] == 1)
				gameboard[i][j] = 0;
			++n;
		}
		++m;
		n = 0;
	}
}
