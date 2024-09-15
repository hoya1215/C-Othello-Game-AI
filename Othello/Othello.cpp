#include "Othello.h"
#include <iostream>
#include <random>
#include <ctime>
#include "Player_Me.h"
#include "Player_AI.h"



Othello::Othello(int Column, int Row, int CurrentMode, int CurrentLevel)
{
	this->Column = Column;
	this->Row = Row;

	//Board = new vector<vector<string>>;
	Board.resize(Column, vector<string>(Row, "□"));
	Level = CurrentLevel;

	int Column_First = Column / 2 - 1;
	int Row_First = Row / 2 - 1;

	me = new Player_Me(&Board);
	AI = new Player_AI(&Board, Level);

	Board[Column_First][Row_First] = me->PlayerSymbol;
	Board[Column_First][Row_First + 1] = me->AISymbol;

	Board[Column_First + 1][Row_First] = me->AISymbol;
	Board[Column_First + 1][Row_First + 1] = me->PlayerSymbol;

	switch (CurrentMode)
	{
	case 2:
		CreateWall();
		break;
	}

}

Othello::~Othello()
{
	delete me;
}

void Othello::Play()
{
	bool NoPlace_Me = false;
	bool NoPlace_AI = false;

	while (1)
	{
		NoPlace_Me = false;
		NoPlace_AI = false;

		if (me->CheckBoard())
		{
			me->MyTurn();
		}
		else
		{
			NoPlace_Me = true;
		}


		AI->Clear();
		if (AI->CheckBoard())
		{
			AI->MyTurn();
		}
		else
		{
			NoPlace_AI = true;
		}

		if (NoPlace_Me && NoPlace_AI)
		{
			EndGame();
			break;
		}
		
	}

	cout << "End Game" << endl;
}

void Othello::CreateWall()
{
	int count = 0;

	while (count < (Column + Row) / 4)
	{
		std::mt19937 generator(static_cast<unsigned int>(time(0)));
		std::uniform_int_distribution<int> ColumnRandom(0, Column - 1);
		std::uniform_int_distribution<int> RowRandom(0, Row - 1);

		int ColumnIndex = ColumnRandom(generator);
		int RowIndex = RowRandom(generator);

		if (Board[ColumnIndex][RowIndex] == BoardSymbol)
		{
			Board[ColumnIndex][RowIndex] = WallSymbol;
			count++;
		}
	}

}



void Othello::EndGame()
{
	int PlayerCount = 0;
	int AICount = 0;
	int BoardSymbolCount = 0;

	for (int Col = 0; Col < Column; ++Col)
	{
		for (int R = 0; R < Row; ++R)
		{
			if (Board[Col][R] == "□")
			{
				BoardSymbolCount++;
			}
			else if (Board[Col][R] == me->AISymbol)
			{
				AICount++;
			}
			else if (Board[Col][R] == me->PlayerSymbol)
			{
				PlayerCount++;
			}
		}
	}

	//if (AICount > 0 && PlayerCount > 0 && BoardSymbolCount > 0)
	//	return false;

	cout << "Player : " << PlayerCount << endl;
	cout << "AI : " << AICount << endl << endl;

	if (PlayerCount > AICount)
	{
		cout << "WIN !";
	}
	else if (PlayerCount == AICount)
	{
		cout << "DRAW";
	}
	else
	{
		cout << "LOSE";
	}

	cout << endl << endl;

}

void Othello::ShowBoard()
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
		cout <<num;
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
			cout << Board[Col][R];
		}
		cout << endl;
		num++;
	}
}
