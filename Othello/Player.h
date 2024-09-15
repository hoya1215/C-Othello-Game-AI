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

	// ���� �� �ִ� �� ǥ��
	virtual bool CheckBoard();

	// ���� �� �ִ� �� �˻�
	virtual bool CanPlace(pair<int, int> Position);

	// ���� ������Ʈ
	virtual void UpdateBoard(pair<int, int> Position);

	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY);
	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// ���� �� �ִ� �� ǥ�� ����
	virtual void RemovePlaceMark();


	// ���� üũ
	virtual bool CheckRange(int x, int y);

	// �����¿� �밢�� üũ
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY);
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// ���� ���� ���� �� �ִ� �� ã��
	virtual int FindBestPosition(pair<int, int> Position);

	void ShowBoard();
	void ShowBoard(vector<vector<string>> NewBoard);

public:
	vector<vector<string>>* Board;

	int Column;
	int Row;

	string BoardSymbol = "��";
	string MarkSymbol = "��";
	string PlayerSymbol = "��";
	string AISymbol = "��";

	vector<pair<int, int>> CanPlacePos;

	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, 1, -1 };

	int Diagonal_dx[4] = { 1, 1, -1, -1 };
	int Diagonal_dy[4] = { 1, -1, 1, -1 };
};

