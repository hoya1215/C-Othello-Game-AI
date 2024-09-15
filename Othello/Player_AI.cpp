#include "Player_AI.h"
#include <random>
#include <ctime>
#include "Player_Me.h"

#define MIN_COUNT -99999999

Player_AI::Player_AI(vector<vector<string>>* NewBoard, int CurrentLevel) : Player(NewBoard)
{
	Level = CurrentLevel;
}

Player_AI::~Player_AI()
{
	Board = nullptr;
}

void Player_AI::MyTurn()
{
	// AI 놓을 수 있는 곳 찾기
	// Easy 는 둘 수 있는 곳 중에 랜덤
	// Normal 는 가장 많이 뒤집을 수 있는 곳
	// Hard 은 기대 비용 현재 뒤집는 개수 - 다음 플레이어가 뒤집을 수 있는 가장 많은 개수 제일 큰거

	switch (Level)
	{
	case 1:
		Easy();
		break;
	case 2:
		Normal();
		break;
	case 3:
		Hard();
		break;
	}


	cout << "---- AI Result ----" << endl << endl;
	ShowBoard();

	cout << endl;
}

void Player_AI::Easy()
{
	if (!CanPlacePos.empty())
	{
		std::mt19937 generator(static_cast<unsigned int>(time(0)));


		std::uniform_int_distribution<int> PositionRandom(0, CanPlacePos.size() - 1);

		// 난수 생성
		int Index = PositionRandom(generator);

		UpdateBoard(CanPlacePos[Index]);
	}



}

void Player_AI::Normal()
{
	int count = 0;
	pair<int, int> BestPos;

	for (int i = 0; i < CanPlacePos.size(); ++i)
	{
		int CurrentCount = FindBestPosition(CanPlacePos[i]);
		if (CurrentCount > count)
		{
			BestPos = CanPlacePos[i];
			count = CurrentCount;
		}
	}

	if (count > 0)
	{
		UpdateBoard(BestPos);
	}
}

void Player_AI::Hard()
{
	int cost = MIN_COUNT;
	pair<int, int> BestPos;

	for (int i = 0; i < CanPlacePos.size(); ++i)
	{
		HardCopyBoard = (*Board);
		int AIChangeCount = FindBestPosition(CanPlacePos[i]);
		UpdateBoard(CanPlacePos[i], &HardCopyBoard);

		//cout << "----- Debug -----" << endl;
		//ShowBoard(HardCopyBoard);


		// 플레이어가 뒤집을 수 있는 최대 개수 구하기
		int MeChangeCount = 0;
		Player_Me me(&HardCopyBoard);
		me.CheckBoard();
		for (int j = 0; j < me.CanPlacePos.size(); ++j)
		{
			int count = me.FindBestPosition(me.CanPlacePos[j]);
			if (MeChangeCount < count)
			{
				MeChangeCount = count;
			}
		}

		if (cost < AIChangeCount - MeChangeCount)
		{
			cost = AIChangeCount - MeChangeCount;
			BestPos = CanPlacePos[i];
		}
	}

	if (cost != MIN_COUNT)
	{
		UpdateBoard(BestPos);
	}
}


bool Player_AI::CheckBoard()
{
	bool ReturnValue = false;

	for (int Col = 0; Col < Column; ++Col)
	{
		for (int R = 0; R < Row; ++R)
		{
			if (CanPlace({ Col, R }))
			{
				CanPlacePos.push_back({ Col, R });
				ReturnValue = true;
			}
		}
	}

	return ReturnValue;
}

bool Player_AI::CanPlace(pair<int, int> Position)
{
	if ((*Board)[Position.first][Position.second] != BoardSymbol)
		return false;

	// 상하좌우
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + dx[i];
		int y = Position.second + dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != PlayerSymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second) > 0)
			return true;
	}

	// 대각
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + Diagonal_dx[i];
		int y = Position.second + Diagonal_dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != PlayerSymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second) > 0)
			return true;
	}

	return false;
}

void Player_AI::UpdateBoard(pair<int, int> Position)
{
	(*Board)[Position.first][Position.second] = AISymbol;

	// 상하좌우
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + dx[i];
		int y = Position.second + dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != PlayerSymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second) > 0)
		{
			UpdateNear(Position, x - Position.first, y - Position.second);
		}

	}

	// 대각
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + Diagonal_dx[i];
		int y = Position.second + Diagonal_dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != PlayerSymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second) > 0)
		{
			UpdateNear(Position, x - Position.first, y - Position.second);
		}
	}


}

void Player_AI::UpdateBoard(pair<int, int> Position, vector<vector<string>>* OtherBoard)
{
	(*OtherBoard)[Position.first][Position.second] = AISymbol;

	// 상하좌우
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + dx[i];
		int y = Position.second + dy[i];

		if (CheckRange(x, y) || (*OtherBoard)[x][y] != PlayerSymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second, OtherBoard) > 0)
		{
			UpdateNear(Position, x - Position.first, y - Position.second, OtherBoard);
		}

	}

	// 대각
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + Diagonal_dx[i];
		int y = Position.second + Diagonal_dy[i];

		if (CheckRange(x, y) || (*OtherBoard)[x][y] != PlayerSymbol)
			continue;

		if (CheckNear(Position, x - Position.first, y - Position.second, OtherBoard) > 0)
		{
			UpdateNear(Position, x - Position.first, y - Position.second, OtherBoard);
		}
	}
}

void Player_AI::UpdateNear(pair<int, int> Position, int DirX, int DirY)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;

	while (!CheckRange(x, y))
	{
		if ((*Board)[x][y] == PlayerSymbol)
		{
			(*Board)[x][y] = AISymbol;

			x += DirX;
			y += DirY;
		}
		else if ((*Board)[x][y] == AISymbol)
		{
			break;
		}
	}
}

void Player_AI::UpdateNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;

	while (!CheckRange(x, y))
	{
		if ((*NewBoard)[x][y] == PlayerSymbol)
		{
			(*NewBoard)[x][y] = AISymbol;

			x += DirX;
			y += DirY;
		}
		else if ((*NewBoard)[x][y] == AISymbol)
		{
			break;
		}
	}
}



bool Player_AI::CheckRange(int x, int y)
{
	if (x < 0 || y < 0 || x >= Column || y >= Column)
		return true;

	return false;
}

int Player_AI::CheckNear(pair<int, int> Position, int DirX, int DirY)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;
	int count = 0;

	while (!CheckRange(x, y))
	{
		if ((*Board)[x][y] == PlayerSymbol)
		{
			count++;
			x += DirX;
			y += DirY;
		}
		else if ((*Board)[x][y] == AISymbol)
		{

			return count;
		}
		else
			return 0;



	}

	return 0;
}

int Player_AI::CheckNear(pair<int, int> Position, int DirX, int DirY, vector<vector<string>>* NewBoard)
{
	int x = Position.first + DirX;
	int y = Position.second + DirY;
	int count = 0;

	while (!CheckRange(x, y))
	{
		if ((*NewBoard)[x][y] == PlayerSymbol)
		{
			count++;
			x += DirX;
			y += DirY;
		}
		else if ((*NewBoard)[x][y] == AISymbol)
		{

			return count;
		}
		else
			return 0;



	}

	return 0;
}

int Player_AI::FindBestPosition(pair<int, int> Position)
{
	int TotalCount = 1;

	// 상하좌우
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + dx[i];
		int y = Position.second + dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != PlayerSymbol)
			continue;

		int count = CheckNear(Position, x - Position.first, y - Position.second);
		TotalCount += count > 0 ? count : 0;

	}

	// 대각
	for (int i = 0; i < 4; ++i)
	{
		int x = Position.first + Diagonal_dx[i];
		int y = Position.second + Diagonal_dy[i];

		if (CheckRange(x, y) || (*Board)[x][y] != PlayerSymbol)
			continue;

		int count = CheckNear(Position, x - Position.first, y - Position.second);
		TotalCount += count > 0 ? count : 0;
	}

	return TotalCount;
}

void Player_AI::Clear()
{
	CanPlacePos.clear();
}
