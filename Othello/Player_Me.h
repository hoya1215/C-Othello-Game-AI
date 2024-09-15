#pragma once
#include "Player.h"

class Player_Me : public Player
{
public:
	Player_Me(vector<vector<string>>* NewBoard);
	~Player_Me() override;

	virtual void MyTurn() override;

	// ���� �� �ִ� �� ǥ��
	virtual bool CheckBoard() override;

	// ���� �� �ִ� �� �˻�
	virtual bool CanPlace(pair<int, int> Position) override;

	// ���� ������Ʈ
	virtual void UpdateBoard(pair<int, int> Position) override;

	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// ���� �� �ִ� �� ǥ�� ����
	virtual void RemovePlaceMark() override;


	// ���� üũ
	virtual bool CheckRange(int x, int y) override;

	// �����¿� �밢�� üũ
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// ���� ���� ���� �� �ִ� �� ã��
	virtual int FindBestPosition(pair<int, int> Position) override;
};

