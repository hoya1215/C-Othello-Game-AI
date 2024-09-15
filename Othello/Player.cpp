#include "Player.h"

Player::Player(vector<vector<string>>* NewBoard)
{
	Board = NewBoard;

	Column = Board->size();
	Row = (*Board).size();
}

Player::~Player()
{
}

void Player::MyTurn()
{
}


bool Player::CheckBoard()
{
	return false;
}

bool Player::CanPlace(pair<int, int> Position)
{

	return false;
}

void Player::UpdateBoard(pair<int, int> Position)
{

}

void Player::UpdateNear(pair<int, int> Position, int DirX, int DirY)
{

}

void Player::UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard)
{
}

void Player::RemovePlaceMark()
{

}


bool Player::CheckRange(int x, int y)
{

	return false;
}

int Player::CheckNear(pair<int, int> Position, int DirX, int DirY)
{
	return 0;
}

int Player::CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard)
{
	return 0;
}

int Player::FindBestPosition(pair<int, int> Position)
{
	return 0;
}

void Player::ShowBoard()
{

	int num = 1;
	cout << " " << " ";

	// 윗줄 크기 조정
	for (int i = 0; i < Row; ++i)
	{
		if (num <= 10)
		{
			cout << " ";
		}
		cout << num;
		num++;
	}
	cout << endl;

	num = 1;

	for (int Col = 0; Col < Column; ++Col)
	{
		cout << num;
		if (num >= 10)
		{
			cout << " ";
		}
		else
		{
			cout << " " << " ";
		}

		for (int R = 0; R < Row; ++R)
		{
			cout << (*Board)[Col][R];
		}
		cout << endl;
		num++;
	}
}

void Player::ShowBoard(vector<vector<string>> NewBoard)
{
	int num = 1;
	cout << " " << " ";

	// 윗줄 크기 조정
	for (int i = 0; i < Row; ++i)
	{
		if (num <= 10)
		{
			cout << " ";
		}
		cout << num;
		num++;
	}
	cout << endl;

	num = 1;

	for (int Col = 0; Col < Column; ++Col)
	{
		cout << num;
		if (num >= 10)
		{
			cout << " ";
		}
		else
		{
			cout << " " << " ";
		}

		for (int R = 0; R < Row; ++R)
		{
			cout << NewBoard[Col][R];
		}
		cout << endl;
		num++;
	}
}
