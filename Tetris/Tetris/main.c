/* Copyright.Dong-Eui univ. 1st grade 20183016 Jihoon Song
동의대학교 1학년 2학기 기초프로그래밍및실습Ⅱ (001)
C언어 프로젝트 (교수님 : 장성진 교수님)
테트리스


코딩 : 20183016 송지훈
*/

#include <stdio.h>
#include <Windows.h>
#include "playFunc.h"
#include "fileprocessing.h"

int main()
{
	gameInfo GameInfo;
	int i;
	MakeEmptyFile(); // score.txt가 없을 시 만들어주는 함수
	AdminSession();	// 관리자 세션
	Login(&GameInfo); // 로그인 세션
	Init(&GameInfo); // 초기화

	PrintWall(); // 벽 출력
	while (1)
	{
		CursorDelete(); // 커서 지우기
		GameInfo.curY++;
		TetrisOneFrame(&GameInfo);	// 테트리스 프레임 당 동작함수
		Speed(&GameInfo); // 스피드조절



		ScorePrint(&GameInfo); // 점수 프린트
		for (i = 0; i < 5; i++) // 키보드 5번 입력 받음
		{
			if (Keyboard(&GameInfo)) // 스페이스시 리턴 값 : 1
			{
				TetrisOneFrame(&GameInfo); // 충돌처리를 위해 한 프레임 이동 그 후 stackedBlock에 테트리미노 쌓음
				RestartInit(&GameInfo); // 재 초기화
				break;
			}
			Sleep(GameInfo.diff);
		}
		if (GameInfo.isGameover == 1) // 게임오버 값을 받을 시 무한반복 탈출
			break;
	}
	system("cls");
	RankSession(GameInfo.name, GameInfo.score); // 랭킹 처리 세션으로 넘어감
	system("cls");
	
	return 0;
}