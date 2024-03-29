#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define DIMENSION 5
#define DEBUG (true)

void display(char board[DIMENSION][DIMENSION][DIMENSION])
{
	int x, y, z;
	for (z = 0; z < DIMENSION; z++)
	{
		for (y = 0; y < DIMENSION; y++)
		{
			for (x = 0; x < DIMENSION-1; x++)
			{
				printf(" %c |", board[z][y][x] == ' ' ? '_' : board[z][y][x]);
			}
			printf(" %c \n", board[z][y][x] == ' ' ? '_' : board[z][y][x]);
		}
		printf("\n------------------------------------------\n");
	}
	printf("\n******************\n");
	printf("\n******************\n");
	printf("\n******************\n");

}
void init(char board[DIMENSION][DIMENSION][DIMENSION])
{
	int x, y, z;
	for (z = 0; z < DIMENSION; z++)
		for (y = 0; y < DIMENSION; y++)
			for (x = 0; x < DIMENSION; x++)
				board[z][y][x] = ' ';
}

char checkX(int z, int y, char board[DIMENSION][DIMENSION][DIMENSION])
{
	char winner = board[z][y][0];
	if (winner == ' ')
		return ' ';
	for (int x = 1; x < DIMENSION; x++)
	{
		if (board[z][y][x] != board[z][y][x-1])
			return ' ';
	}
	if (DEBUG) cout << "Winner horizontal z = " << z << ", y = " << y << endl;
	return winner;

}

char checkY(int z, int x, char board[DIMENSION][DIMENSION][DIMENSION])
{
	char winner = board[z][0][x];
	if (winner == ' ')
		return ' ';
	for (int y = 1; y < DIMENSION; y++)
	{
		if (board[z][y][x] != board[z][y-1][x])
			return ' ';
	}
	if (DEBUG) cout << "Winner vertical z = " << z << ", x = " << x << endl;
	return winner;

}

char checkZ(int y, int x, char board[DIMENSION][DIMENSION][DIMENSION])
{
	char winner = board[0][y][x];
	if (winner == ' ')
		return ' ';
	for (int z = 1; z < DIMENSION; z++)
	{
		if (board[z][y][x] != board[z-1][y][x])
			return ' ';
	}
	if (DEBUG) cout << "Winner layer y = " << y << ", x = " << x << endl;
	return winner;

}

char checkLevel(int z, char board[DIMENSION][DIMENSION][DIMENSION])
{
	for (int y = 0; y < DIMENSION; y++)
	{
		char winner = checkX(z, y, board);
		if (winner != ' ')
			return winner;

	}

	for (int x = 0; x < DIMENSION; x++)
	{
		char winner = checkY(z, x, board);
		if (winner != ' ')
			return winner;
	}

	return ' ';

}

char checkDiagonals(char board[DIMENSION][DIMENSION][DIMENSION])
{
	for (int z = 0; z < DIMENSION; z++)
	{
		if ((board[z][0][0] != ' ') && (board[z][0][0]==board[z][1][1]) && (board[z][1][1]==board[z][2][2]) && (board[z][2][2]==board[z][3][3]) && (board[z][3][3]==board[z][4][4]))
		{
			if (DEBUG) cout << "[1]Winner diagonal starting at " << z << ", 0, 0" << endl;
			return board[z][0][0];
		}
		if ((board[z][4][0] != ' ') && (board[z][4][0]==board[z][3][1]) && (board[z][3][1]==board[z][2][2]) && (board[z][2][2]==board[z][1][3]) && (board[z][1][3]==board[z][0][4]))
		{
			if (DEBUG) cout << "[2]Winner diagonal starting at " << z << ", 4, 0" << endl;
			return board[z][4][0];
		}
	}

	for (int x = 0; x < DIMENSION; x++)
	{
		if ((board[0][0][x] != ' ') && (board[0][0][x]==board[1][1][x]) && (board[0][0][x]==board[2][2][x]) && (board[0][0][x]==board[3][3][x]) && (board[0][0][x]==board[4][4][x]))
		{
			if (DEBUG) cout << "[3]Winner diagonal starting at 0, 0, " << x << endl;
			return board[0][0][x];
		}
		if ((board[4][0][x] != ' ') && (board[4][0][x]==board[3][1][x]) && (board[4][0][x]==board[2][2][x]) && (board[4][0][x]==board[1][3][x]) && (board[4][0][x]==board[0][4][x]))
		{
			if (DEBUG) cout << "[4]Winner diagonal starting at 4, 0, " << x << endl;
			return board[4][0][x];
		}
	}

	for (int y = 0; y < DIMENSION; y++)
	{
		if ((board[0][y][0] != ' ') && (board[0][y][0]==board[1][y][1]) && (board[0][y][0]==board[2][y][2]) && (board[0][y][0]==board[3][y][3]) && (board[0][y][0]==board[4][y][4]))
		{
			if (DEBUG) cout << "[5]Winner diagonal starting at 0, " << y << ", 0" << endl;
			return board[0][y][0];
		}
		if ((board[4][y][0] != ' ') && (board[4][y][0]==board[3][y][1]) && (board[4][y][0]==board[2][y][2]) && (board[4][y][0]==board[1][y][3]) && (board[4][y][0]==board[0][y][4]))
		{
			if (DEBUG) cout << "[6]Winner diagonal starting at 4, " << y << ", 0" << endl;
			return board[4][y][0];
		}
	}

	if ((board[0][0][0] != ' ') && (board[0][0][0]==board[1][1][1]) && (board[0][0][0]==board[2][2][2]) && (board[0][0][0]==board[3][3][3]) && (board[0][0][0]==board[4][4][4]))
	{
		if (DEBUG) cout << "[6]Winner diagonal starting at 0, 0, 0" << endl;
		return board[0][0][0];
	}
	if ((board[4][0][0] != ' ') && (board[4][0][0]==board[3][1][1]) && (board[4][0][0]==board[2][2][2]) && (board[4][0][0]==board[1][3][3]) && (board[4][0][0]==board[0][4][4]))
	{
		if (DEBUG) cout << "[7]Winner diagonal starting at 4, 0, 0" << endl;
		return board[4][0][0];
	}
	if ((board[0][4][0] != ' ') && (board[0][4][0]==board[1][3][1]) && (board[0][4][0]==board[2][2][2]) && (board[0][4][0]==board[3][1][3]) && (board[0][4][0]==board[4][0][4]))
	{
		if (DEBUG) cout << "[8]Winner diagonal starting at 0, 4, 0" << endl;
		return board[0][4][0];
	}
	if ((board[4][4][0] != ' ') && (board[4][4][0]==board[3][3][1]) && (board[4][4][0]==board[2][2][2]) && (board[4][4][0]==board[1][1][3]) && (board[4][4][0]==board[0][0][4]))
	{
		if (DEBUG) cout << "[9]Winner diagonal starting at 4, 4, 0" << endl;
		return board[4][4][0];
	}

	return ' ';
}

char checkWinner(char board[DIMENSION][DIMENSION][DIMENSION])
{
	// Check X & Y axis for each level
	for (int z = 0; z < DIMENSION; z++)
	{
		char winner = checkLevel(z, board);
		if (winner != ' ')
			return winner;
	}

	// Now check the Z runs
	for (int y = 0; y < DIMENSION; y++)
		for (int x = 0; x < DIMENSION; x++)
		{
			char winner = checkZ(y, x, board);
			if (winner != ' ')
				return winner;
		}

	return checkDiagonals(board);

}

// YOUR HEADER FILES WILL BE INCLUDED HERE
// USE THE SAMPLES TO UNDERSTAND THE INTERFACE
#include "mjc5134.h"
//#include "scs12.h"

int main()
{
	int counter = 0;
	static int NUMCELLS = DIMENSION * DIMENSION * DIMENSION;
	char board[DIMENSION][DIMENSION][DIMENSION];
	int moveX, moveY, moveZ;
	char winner = ' ';
	init(board);
	mjc5134 pX;
	pX.setUp('X');
	mjc5134 pO;
	pO.setUp('O');
	srand ( time(NULL) );

	while ((winner == ' ') && (counter <= NUMCELLS))
	{
		counter++;
		if (counter % 2 == 1)
		{
			pX.selectMove(moveZ, moveY, moveX);
			cout << "Player X moves [" << moveZ << "][" << moveY << "][" << moveX << "]" << endl;
			if (board[moveZ][moveY][moveX] == ' ')
			{
				board[moveZ][moveY][moveX] = 'X';
				pO.notifyMove(moveZ, moveY, moveX);
			}
			else
			{
				cout << "Player X makes an illegal move and loses!" << endl;
				winner = 'O';
				break;
			}
		}
		else
		{
			pO.selectMove(moveZ, moveY, moveX);
			cout << "Player O moves [" << moveZ << "][" << moveY << "][" << moveX << "]" << endl;
			if (board[moveZ][moveY][moveX] == ' ')
			{
				board[moveZ][moveY][moveX] = 'O';
				pX.notifyMove(moveZ, moveY, moveX);
			}
			else
			{
				cout << "Player O makes an illegal move and loses!" << endl;
				winner = 'X';
				break;
			}
		}

		display(board);
		winner = checkWinner(board);
		//{char scs[5]; gets(scs);}
	}

	display(board);
	if (counter > 125)
		cout << "Tie!" << endl;
	else
	{
		if (winner == 'X')
			cout << "Winner is X (" << pX.myUID() << ")" << endl;
		else
			cout << "Winner is O (" << pO.myUID() << ")" << endl;
	}
	cout << "Counter = " << counter << endl;

}
