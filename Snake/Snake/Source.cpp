#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool GameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction { Stop = 0, Left, Right, Up, Down };
Direction dir;

void Setup() {
	GameOver = false;
	dir = Stop;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

}

void Input()
{
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = Up;
			break;
		case 's':
			dir = Down;
			break;
		case 'q':
			GameOver = true;
			break;
		}
	}
}


void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case Left:
		x--;
		break;
	case Right:
		x++;
		break;
	case Up:
		y--;
		break;
	case Down:
		y++;
		break;
	}

	if (x > width || x < 0 || y > height || y < 0)
		GameOver = true;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			GameOver = true;
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;


	}
}

int main() {
	Setup();
	while (!GameOver) {
		Draw();
		Input();
		Logic();
		Sleep(200);
	}

	return 0;
}