#pragma once
#include <vector>
#include <string>

using namespace std;

class Player_Me;
class Player_AI;

class Othello
{
public:
	Othello(int Column, int Row, int CurrentMode, int CurrentLevel);
	~Othello();

	void Play();

	void CreateWall();

	// 게임 끝 체크
	void EndGame();

	// 현재 보드판 상황 보여주기
	void ShowBoard();

private:
	vector<vector<string>> Board;

	int Level;

	int Column;
	int Row;

	string BoardSymbol = "□";
	string MarkSymbol = "※";
	string PlayerSymbol = "●";
	string AISymbol = "○";

	string WallSymbol = "■";

	Player_Me* me;
	Player_AI* AI;
};

