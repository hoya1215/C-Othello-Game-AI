#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;



class Player
{
public:
	Player(vector<vector<string>>* NewBoard);
	virtual ~Player();

	virtual void MyTurn();

	// 놓을 수 있는 곳 표시
	virtual bool CheckBoard();

	// 놓을 수 있는 곳 검사
	virtual bool CanPlace(pair<int, int> Position);

	// 보드 업데이트
	virtual void UpdateBoard(pair<int, int> Position);

	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY);
	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// 놓을 수 있는 곳 표시 제거
	virtual void RemovePlaceMark();


	// 범위 체크
	virtual bool CheckRange(int x, int y);

	// 상하좌우 대각선 체크
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY);
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// 제일 많이 놓을 수 있는 곳 찾기
	virtual int FindBestPosition(pair<int, int> Position);

	void ShowBoard();
	void ShowBoard(vector<vector<string>> NewBoard);

public:
	vector<vector<string>>* Board;

	int Column;
	int Row;

	string BoardSymbol = "□";
	string MarkSymbol = "※";
	string PlayerSymbol = "●";
	string AISymbol = "○";

	vector<pair<int, int>> CanPlacePos;

	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, 1, -1 };

	int Diagonal_dx[4] = { 1, 1, -1, -1 };
	int Diagonal_dy[4] = { 1, -1, 1, -1 };
};

