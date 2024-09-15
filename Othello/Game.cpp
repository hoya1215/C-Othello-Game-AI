#include <iostream>
#include "Othello.h"

using namespace std;

int main()
{
	
	cout << "Set Size" << endl;
	int X, Y;
	cout << "X : ";
	cin >> X;
	cout << "Y : ";
	cin >> Y;

	while (X < 4 || Y < 4 || X > 99 || Y > 99)
	{
		cout << endl << "Size : 3 < X < 100 , 3 < Y < 100" << endl;
		cout << "X : ";
		cin >> X;
		cout << "Y : ";
		cin >> Y;
	}
	cout << endl << "Select Mode" << endl;
	int Mode;
	cout << "1 : Basic   2 : Wall" << endl;
	cin >> Mode;

	while (Mode < 1 || Mode > 2)
	{
		cout << endl << "There is No Mode" << endl;
		cout << "1 : Basic   2 : Wall" << endl;
		cin >> Mode;
	}


	cout << endl << "Select Level" << endl;
	int Level;
	cout << " " << " 1 : Easy   2 : Normal   3 : Hard" << endl;
	
	cin >> Level;
	

	while (Level < 1 || Level > 3)
	{
		cout << endl << "There is No Level" << endl;
		cout << " " << " 1 : Easy   2 : Normal   3 : Hard" << endl;

		cin >> Level;
	}

	cout << endl;

	Othello* othello = new Othello(X, Y, Mode, Level);

	othello->Play();

	delete othello;

	return 0;

}