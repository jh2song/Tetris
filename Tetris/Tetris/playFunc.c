#define _CRT_NONSTDC_NO_WARNINGS
//키보드값들
#define LEFT 75 //좌로 이동 
#define RIGHT 77 //우로 이동 
#define UP 72 //회전 
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
	// 첫 번째 파라미터 : 모양을 결정, 두 번째 파라미터 : 회전방향
	// 세 번째 파라미터 : 테트리미노의 Y축 네 번째 파라미터 : 테트리미노의 X축
	// 0은 빈 공간 1은 블럭
	// I미노
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

	// O미노
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

	// Z미노
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

	// S미노
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

	// J미노
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

	// L미노
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

	// T미노
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
//테트리미노 4차원배열
int tetrisGameBoard[23][13]; // 세로:23 가로:13
// stackedBlock+벽을 포함한 게임보드배열
int stackedBlock[21][11];
// 쌓인 벽 저장공간 배열

void Login(gameInfo * GameInfo)
{
	printf("\n\n");
	printf("\t\t테트리스에 오신걸 환영합니다!!!\n\t\t\t copyright DEU 20183016 송지훈\n");
	printf("\n\t\t사용자 이름을 적어주세요! : ");
	scanf_s("%s", GameInfo->name, 50);
	system("cls");
}

/*
시작 초기화
X:4 Y:0
모양은 랜덤
diff(난이도) 200
direction(방향) : 0
isGameover(게임오버 여부) : 0
score : 0
stackedBlock 0으로 초기화
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
벽 출력
*/
void PrintWall()
{
	int i;
	for (i = 0; i < 13; i++)
		printf("■");
	puts("");
	for (i = 1; i < 22; i++)
	{
		printf("■                      ■\n");
	}
	for (i = 0; i < 13; i++)
		printf("■");
	puts("");
	
}

/*
커서 지우는 함수
CONSOLE_CURSOR_INFO 구조체 선언
dwSize 두께 : 1, bVisible : FALSE (숨기기)
SetConsoleCursorInfo함수로 핸들값을 변경
*/
void CursorDelete() // CONSOLE_CURSOR_INFO 라는 구조체를 이용, 커서를 숨겼음.  
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, }; // 구조체를 선언한다.
	cursorInfo.dwSize = 1;	// 두께 1~100 클수록 두꺼움
	cursorInfo.bVisible = FALSE;	// FALSE : 숨기기, TRUE : 보이기
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/*
MakeTetrisBoard(); -> 테트리미노의 이동을 위해 현재 tetrisGameBoard을 벽을 제외하고 0으로 초기화
isNoDownBlock -> 바닥에 블럭 없는지 확인. 충돌 처리를 위해 사용
CopyToGameBoard -> 1프레임 후 바뀐 테트리미노를 tetrisGameBoard에 복사

*/
void TetrisOneFrame(gameInfo * GameInfo)
{

	if (GameInfo->isStart == 1)//블럭 시작이면
	{

		MakeTetrisBoard();
		// 블럭 끝인지 확인
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
	else // 블럭 시작이 아니면
	{

		MakeTetrisBoard();

		// 블럭 끝인지 확인
		if (isNoDownblock(tetrisGameBoard, tetrimino[GameInfo->curShape][GameInfo->direction]
			, GameInfo->curX, GameInfo->curY))
		{

			//GameInfo->curY++;
			CopyToStacked(stackedBlock, tetrimino[GameInfo->curShape][GameInfo->direction]
				, GameInfo->curX, GameInfo->curY);
			//GameInfo->isStart = 1;
			GameInfo->score += 4;
			MakeTetrisBoard();
			LineClearCheck(GameInfo); // 라인 클리어 되는지 확인
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
점수 별로 속도 향상 (Sleep 특징상 큰 변화는 없음)
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
점수 출력
*/
void ScorePrint(gameInfo * GameInfo)
{
	gotoxy(34, 1);
	printf("사용자 이름 : %s", GameInfo->name);
	gotoxy(34, 2);
	printf("점수 : %d점", GameInfo->score);
}

int Keyboard(gameInfo * GameInfo)
{
	int key;

	if (kbhit())  //키입력이 있는 경우  
	{
		key = getch(); //키값을 받음
		if (key == 224)//방향키인경우 
		{
			do { key = getch(); } while (key == 224);//방향키지시값을 버림 
			switch (key)
			{
			case LEFT: //왼쪽키 눌렀을때  
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
			case RIGHT: //오른쪽 방향키 눌렀을때
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
			case DOWN: //아래쪽 방향키 눌렀을때 
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
			case UP: //위쪽 방향키 눌렀을때 
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
		else//방향키가 아닌경우 
		{
			switch (key)
			{
			case SPACE: //스페이스키 눌렀을때 
				/*
				바닥 충돌 하기 전까지 Y값을 무한반복으로 증가시킴
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

	while (kbhit()) getch(); //키버퍼를 비움 
	return 0;
}

void MakeTetrisBoard() // 테트리스 벽을 만듬 1:벽 0:빈 공간
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
	int tetrisGameBoard[23][13]; // 세로:23 가로:13
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
벽을 포함 이상한 좌표값일때 충돌 처리를 하는 함수
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
바닥 충돌 여부 확인
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
테트리미노를 tetrisGameBoard에 복사
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
StackedBlock에 테트리미노를 복사
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
라인 클리어 확인 함수
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
		if (check == 11) // 한 줄 라인 클리어시
		{
			combo++;
			LineClear(i, combo);
			GameInfo->score += combo * 30; // 콤보에 따른 추가 점수
			i++; // 줄이 없어지므로 다시 검사를 위해 i를 1 증가시킴

		}
		check = 0;
	}
}

/*
parameter로 클리어 줄을 받아서 그 줄에 stackedBlock을 0으로 초기화
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
	printf("combo : %d", combo); // 콤보 출력
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

//tetrisGameBoard가 1일시 □ 0 일시 공백 출력
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
				printf("□");
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
	srand((unsigned)time(NULL)); // srand(time(NULL))하면 오류남
	return rand() % 7;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
tetrisGameBoard에서 tetrimino를 제거
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
