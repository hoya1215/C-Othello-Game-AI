#pragma once
#include "Player.h"

class Player_AI : public Player
{
public:
	Player_AI(vector<vector<string>>* NewBoard, int CurrentLevel);
	~Player_AI() override;

	virtual void MyTurn() override;

	// 난이도 별 
	void Easy();
	void Normal();
	void Hard();

	// 놓을 수 있는 곳 표시
	virtual bool CheckBoard() override;

	// 놓을 수 있는 곳 검사
	virtual bool CanPlace(pair<int, int> Position) override;

	// 보드 업데이트
	virtual void UpdateBoard(pair<int, int> Position) override;
	void UpdateBoard(pair<int, int> Position, vector<vector<string>>* OtherBoard);

	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);




	// 범위 체크
	virtual bool CheckRange(int x, int y) override;

	// 상하좌우 대각선 체크
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// 제일 많이 놓을 수 있는 곳 찾기
	virtual int FindBestPosition(pair<int, int> Position) override;

	void Clear();

private:
	int Level;



	vector<vector<string>> HardCopyBoard;
};

