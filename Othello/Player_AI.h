#pragma once
#include "Player.h"

class Player_AI : public Player
{
public:
	Player_AI(vector<vector<string>>* NewBoard, int CurrentLevel);
	~Player_AI() override;

	virtual void MyTurn() override;

	// ���̵� �� 
	void Easy();
	void Normal();
	void Hard();

	// ���� �� �ִ� �� ǥ��
	virtual bool CheckBoard() override;

	// ���� �� �ִ� �� �˻�
	virtual bool CanPlace(pair<int, int> Position) override;

	// ���� ������Ʈ
	virtual void UpdateBoard(pair<int, int> Position) override;
	void UpdateBoard(pair<int, int> Position, vector<vector<string>>* OtherBoard);

	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual void UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);




	// ���� üũ
	virtual bool CheckRange(int x, int y) override;

	// �����¿� �밢�� üũ
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY) override;
	virtual int CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard);

	// ���� ���� ���� �� �ִ� �� ã��
	virtual int FindBestPosition(pair<int, int> Position) override;

	void Clear();

private:
	int Level;



	vector<vector<string>> HardCopyBoard;
};

