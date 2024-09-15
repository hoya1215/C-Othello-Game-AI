#pragma once
#include "Player.h"

class Player_Me : public Player
{
public:
	Player_Me(vector<vector<string>>* NewBoard);
	~Player_Me() override;

	virtual void MyTurn() override;

	// 놓을 수 있는 곳 표시
	virtual bool CheckBoard() override;

	// 놓을 수 있는 곳 검사
	virtual bool CanPlace(pair<int, int> Position) override;

	// 보드 업데이트
	virtual void UpdateBoard(pair<int, int> Position) override;

	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// 놓을 수 있는 곳 표시 제거
	virtual void RemovePlaceMark() override;


	// 범위 체크
	virtual bool CheckRange(int x, int y) override;

	// 상하좌우 대각선 체크
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// 제일 많이 놓을 수 있는 곳 찾기
	virtual int FindBestPosition(pair<int, int> Position) override;
};

