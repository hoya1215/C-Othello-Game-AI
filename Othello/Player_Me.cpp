#include "Player_Me.h"

Player_Me::Player_Me(vector<vector<string>>* NewBoard) : Player(NewBoard)
{

}

Player_Me::~Player_Me()
{
	Board = nullptr;
}

void Player_Me::MyTurn()
{
	cout << endl;
	cout << "---- Your Turn ----" << endl << endl;
	ShowBoard();

	cout << endl;
	

	int Next_X, Next_Y;
	cout << "X : ";
	cin >> Next_X;

	cout << "Y : ";
	cin >> Next_Y;
	cout << endl;

	// Next 범위 체크 필요
	while (CheckRange(Next_X - 1, Next_Y - 1) || (*Board)[Next_X - 1][Next_Y - 1] != MarkSymbol)
	{
		cout << endl << "Cannot Place" << endl;

		cout << "X : ";
		cin >> Next_X;

		cout << "Y : ";
		cin >> Next_Y;
	}

	UpdateBoard({ Next_X - 1, Next_Y - 1 });
	cout << "---- Your Result ----" << endl << endl;
	ShowBoard();

	cout << endl;
}


bool Player_Me::CheckBoard()
{
	bool ReturnValue = false;

	for (int Col = 0; Col < Column; ++Col)
	{
		for (int R = 0; R < Row; ++R)
		{
			if (CanPlace({ Col, R }))
			{
				(*Board)[Col][R] = MarkSymbol;
				CanPlacePos.push_back({ Col, R });
				ReturnValue = true;
			}
		}
	}

	return ReturnValue;
}

bool Player_Me::CanPlace(pair<int, int> Position)
{
	if ((*Board)[Position.first][Position.second] != BoardSymbol)
		return false;

	// 상하좌우
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + dx[i];
		int y = Position.second + dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != AISymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second))
			return true;
	}

	// 대각
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + Diagonal_dx[i];
		int y = Position.second + Diagonal_dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != AISymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second))
			return true;
	}

	return false;
}

void Player_Me::UpdateBoard(pair<int, int> Position)
{
	(*Board)[Position.first][Position.second] = PlayerSymbol;

	// 상하좌우
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + dx[i];
		int y = Position.second + dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != AISymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second))
		{
			UpdateNear(Position, x - Position.first, y - Position.second);
		}

	}

	// 대각
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + Diagonal_dx[i];
		int y = Position.second + Diagonal_dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != AISymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second))
		{
			UpdateNear(Position, x - Position.first, y - Position.second);
		}
	}

	RemovePlaceMark();
}

void Player_Me::UpdateNear(pair<int, int> Position, int DirX, int DirY)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;

	while (!CheckRange(x, y))
	{
		if ((*Board)[x][y] == AISymbol)
		{
			(*Board)[x][y] = PlayerSymbol;

			x += DirX;
			y += DirY;
		}
		else if ((*Board)[x][y] == PlayerSymbol)
		{
			break;
		}
	}
}

void Player_Me::UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;

	while (!CheckRange(x, y))
	{
		if ((*NewBoard)[x][y] == AISymbol)
		{
			(*NewBoard)[x][y] = PlayerSymbol;

			x += DirX;
			y += DirY;
		}
		else if ((*NewBoard)[x][y] == PlayerSymbol)
		{
			break;
		}
	}
}

void Player_Me::RemovePlaceMark()
{
	for (int Col = 0; Col < Column; ++Col)
	{
		for (int R = 0; R < Row; ++R)
		{
			if ((*Board)[Col][R] == MarkSymbol)
			{
				(*Board)[Col][R] = BoardSymbol;
			}
		}
	}
}


bool Player_Me::CheckRange(int x, int y)
{
	if (x < 0 || y < 0 || x >= Column || y >= Column)
		return true;

	return false;
}

int Player_Me::CheckNear(pair<int, int> Position, int DirX, int DirY)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;
	int count = 0;

	while (!CheckRange(x, y))
	{
		if ((*Board)[x][y] == AISymbol)
		{
			count++;
			x += DirX;
			y += DirY;
		}
		else if ((*Board)[x][y] == PlayerSymbol)
		{
			return count;
		}
		else
			return 0;



	}

	return 0;
}

int Player_Me::CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;
	int count = 0;

	while (!CheckRange(x, y))
	{
		if ((*NewBoard)[x][y] == AISymbol)
		{
			count++;
			x += DirX;
			y += DirY;
		}
		else if ((*NewBoard)[x][y] == PlayerSymbol)
		{
			return count;
		}
		else
			return 0;



	}

	return 0;
}

int Player_Me::FindBestPosition(pair<int, int> Position)
{
	int TotalCount = 1;

	// 상하좌우
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + dx[i];
		int y = Position.second + dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != AISymbol)
			continue;

		int count = CheckNear(Position, x - Position.first, y - Position.second);
		TotalCount += count > 0 ? count : 0;

	}

	// 대각
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + Diagonal_dx[i];
		int y = Position.second + Diagonal_dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != AISymbol)
			continue;

		int count = CheckNear(Position, x - Position.first, y - Position.second);
		TotalCount += count > 0 ? count : 0;
	}

	return TotalCount;

}
