#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
using namespace std;

const int MAXROW   = 100;
const int MAXCOL   = 100;
const int Capacity = 100;

// ============================================================
//   MENU
// ============================================================
void showMenu()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n";
	cout << "  ==========================================\n";
	cout << "          GENERALIZED TIC-TAC-TOE\n";
	cout << "  ==========================================\n\n";
	SetConsoleTextAttribute(hConsole, 14);
	cout << "  Select Game Mode:\n\n";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "  1. Human vs Human\n";
	cout << "  2. Human vs Computer\n";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "  3. Exit\n\n";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "  Enter your choice (1/2/3): ";
}

// ============================================================
//   SHARED UTILITY FUNCTIONS (used by both modes)
// ============================================================
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==
			FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOutput, scrn);
}

void color(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

// ============================================================
//   MODE 1 : HUMAN vs HUMAN  (original Part-A code, untouched)
// ============================================================
namespace HvH
{
	void printbox(int rows, int cols)
	{
		color(3);
		char sym = -37;
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (r == 0 or c == 0 or r == rows - 1 or c == cols - 1)
				{
					gotoRowCol(r, c);
					cout << sym;
				}
			}
		}
	}

	bool HL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		// Check right direction
		int countR = 0;
		if (c + winC <= C)
		{
			for (int ri = 0; ri < winC; ri++)
			{
				if (Board[r][c + ri] == PSYM)
					countR++;
			}
		}
		// Check left direction (start from 1 to avoid double-counting center cell)
		int countL = 0;
		if (c - winC >= -1)
		{
			for (int ri = 1; ri < winC; ri++)
			{
				if (c - ri >= 0 && Board[r][c - ri] == PSYM)
					countL++;
			}
			// count the center cell once
			if (Board[r][c] == PSYM) countL++;
		}
		if (countR == winC or countL == winC)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool VL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		// Check downward direction
		int countR = 0;
		if (r + winC <= R)
		{
			for (int ri = 0; ri < winC; ri++)
			{
				if (Board[r + ri][c] == PSYM)
					countR++;
			}
		}
		// Check upward direction (start from 1 to avoid double-counting center cell)
		int countL = 0;
		if (r - winC >= -1)
		{
			for (int ri = 1; ri < winC; ri++)
			{
				if (r - ri >= 0 && Board[r - ri][c] == PSYM)
					countL++;
			}
			// count the center cell once
			if (Board[r][c] == PSYM) countL++;
		}
		if (countR == winC or countL == winC)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DUL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		// Check down-right diagonal
		int countR = 0;
		if (r + winC <= R and c + winC <= C)
		{
			for (int ri = 0; ri < winC; ri++)
			{
				if (Board[r + ri][c + ri] == PSYM)
					countR++;
			}
		}
		// Check up-left diagonal (start from 1 to avoid double-counting center cell)
		int countL = 0;
		if (r - winC >= -1 and c - winC >= -1)
		{
			for (int ri = 1; ri < winC; ri++)
			{
				if (r - ri >= 0 && c - ri >= 0 && Board[r - ri][c - ri] == PSYM)
					countL++;
			}
			// count the center cell once
			if (Board[r][c] == PSYM) countL++;
		}
		if (countR == winC or countL == winC)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DLL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		// Check down-left diagonal
		int countR = 0;
		if (r + winC <= R and c - winC >= -1)
		{
			for (int ri = 0; ri < winC; ri++)
			{
				if (c - ri >= 0 && Board[r + ri][c - ri] == PSYM)
					countR++;
			}
		}
		// Check up-right diagonal (start from 1 to avoid double-counting center cell)
		int countL = 0;
		if (r - winC >= -1 and c + winC <= C)
		{
			for (int ri = 1; ri < winC; ri++)
			{
				if (r - ri >= 0 && Board[r - ri][c + ri] == PSYM)
					countL++;
			}
			// count the center cell once
			if (Board[r][c] == PSYM) countL++;
		}
		if (countR == winC or countL == winC)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool iswin(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		return(HL(Board, R, C, r, c, PSYM, winC) or VL(Board, R, C, r, c, PSYM, winC) or DUL(Board, R, C, r, c, PSYM, winC) or DLL(Board, R, C, r, c, PSYM, winC));
	}

	bool isDraw(char Board[][MAXCOL], int R, int C)
	{
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (Board[i][j] == '-')
				{
					return false;
				}
			}
		}
		return true;
	}

	bool isvalid(char Board[][MAXCOL], int r, int c, int R, int C)
	{
		if (r >= 0 and r < R and c >= 0 and c < C and Board[r][c] == '-')
			return true;
		return false;
	}

	void turnchange(int& turn, int NOP)
	{
		turn++;
		if (turn == NOP)
		{
			turn = 0;
		}
	}

	void displayturnmsg(char PSYM, char PNAME[MAXCOL], int R, int C)
	{
		color(5);
		cout << PNAME << " (" << PSYM << ")'s turn     ";
	}

	void positionofplayer(int& r, int& c, int C)
	{
		getRowColbyLeftClick(r, c);
	}

	void displayboard(char Board[][MAXCOL], int R, int C)
	{
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				cout << Board[i][j];
			}
			cout << endl;
		}
	}

	void updatetheboard(char b[][MAXCOL], char PSYM, int r, int c)
	{
		color(4);
		b[r][c] = PSYM;
	}

	void input(char Board[][MAXCOL], char PSYM[Capacity], char PNAME[MAXROW][MAXCOL], int& NOP, int& R, int& C, int& turn, int& winC)
	{
		cout << "(Enter NOP,WinConnt,DimensionROW,DimensionCOL)";
		cin >> NOP >> winC >> R >> C;
		for (int ci = 0; ci < NOP; ci++)
		{
			cout << "Enter player" << ci + 1 << " Name : ";
			if (ci == 0)
			{
				cin.ignore();
			}
			cin.getline(PNAME[ci], 200);
		}
		for (int ci = 0; ci < NOP; ci++)
		{
			color(ci + 3);
			cout << "Enter player" << ci + 1 << " sym :";
			cin >> PSYM[ci];
		}
		for (int ri = 0; ri < R; ri++)
		{
			color(9);
			for (int ci = 0; ci < C; ci++)
			{
				Board[ri][ci] = '-';
			}
			cout << endl;
		}
		turn = rand() % NOP;
		system("cls");
	}

	void run()
	{
		int turn, NOP, winC, R, C, c, r;
		char Board[MAXROW][MAXCOL], PSYM[Capacity], PNAME[MAXROW][MAXCOL];
		input(Board, PSYM, PNAME, NOP, R, C, turn, winC);
		displayboard(Board, R, C);
		do {
			do {
				displayturnmsg(PSYM[turn], PNAME[turn], R, C);
				positionofplayer(r, c, C);
			} while (!(isvalid(Board, r, c, R, C)));
			updatetheboard(Board, PSYM[turn], r, c);
			system("cls");
			displayboard(Board, R, C);
			if (isDraw(Board, R, C))
			{
				system("cls");
				cout << "Game Draw";
				break;
			}
			if (iswin(Board, R, C, r, c, PSYM[turn], winC))
			{
				color(12);
				system("cls");
				cout << PNAME[turn] << "(" << PSYM[turn] << ")" << " is win the game !";
				break;
			}
			turnchange(turn, NOP);
		} while (true);
	}
} // end namespace HvH

// ============================================================
//   MODE 2 : HUMAN vs COMPUTER  (original Phase-2 code, untouched)
// ============================================================
namespace HvC
{
	bool isvalid(char Board[][MAXCOL], int r, int c, int R, int C);
	bool iswin  (char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC);

	// Phase-2 uses a different getRowColbyLeftClick (divides X by 2, offsets Y by 1)
	void getRowColbyLeftClick(int& rpos, int& cpos)
	{
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD Events;
		INPUT_RECORD InputRecord;
		SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
		do
		{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
			if (InputRecord.EventType == MOUSE_EVENT &&
				InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				cpos = InputRecord.Event.MouseEvent.dwMousePosition.X / 2;
				rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y - 1;
				break;
			}
		} while (true);
	}

	bool HL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		int countR = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (c + ri >= C) break;
			if (Board[r][c + ri] == PSYM) countR++;
			else break;
		}
		if (countR == winC) return true;

		int countL = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (c - ri < 0) break;
			if (Board[r][c - ri] == PSYM) countL++;
			else break;
		}
		if (countL == winC) return true;

		return false;
	}

	bool VL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		int countD = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (r + ri >= R) break;
			if (Board[r + ri][c] == PSYM) countD++;
			else break;
		}
		if (countD == winC) return true;

		int countU = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (r - ri < 0) break;
			if (Board[r - ri][c] == PSYM) countU++;
			else break;
		}
		if (countU == winC) return true;

		return false;
	}

	bool DUL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		int countDR = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (r + ri >= R || c + ri >= C) break;
			if (Board[r + ri][c + ri] == PSYM) countDR++;
			else break;
		}
		if (countDR == winC) return true;

		int countUL = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (r - ri < 0 || c - ri < 0) break;
			if (Board[r - ri][c - ri] == PSYM) countUL++;
			else break;
		}
		if (countUL == winC) return true;

		return false;
	}

	bool DLL(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		int countDL = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (r + ri >= R || c - ri < 0) break;
			if (Board[r + ri][c - ri] == PSYM) countDL++;
			else break;
		}
		if (countDL == winC) return true;

		int countUR = 0;
		for (int ri = 0; ri < winC; ri++)
		{
			if (r - ri < 0 || c + ri >= C) break;
			if (Board[r - ri][c + ri] == PSYM) countUR++;
			else break;
		}
		if (countUR == winC) return true;

		return false;
	}

	bool iswin(char Board[][MAXCOL], int R, int C, int r, int c, char PSYM, int winC)
	{
		return (HL (Board, R, C, r, c, PSYM, winC) ||
		        VL (Board, R, C, r, c, PSYM, winC) ||
		        DUL(Board, R, C, r, c, PSYM, winC) ||
		        DLL(Board, R, C, r, c, PSYM, winC));
	}

	void computer(char board[][MAXCOL], char sym[], int R, int C, int& r, int& c, int turn, int winC)
	{
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (isvalid(board, i, j, R, C))
				{
					board[i][j] = sym[1];
					if (iswin(board, R, C, i, j, sym[1], winC))
					{
						r = i; c = j;
						board[i][j] = '-';
						return;
					}
					board[i][j] = '-';
				}
			}
		}
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (isvalid(board, i, j, R, C))
				{
					board[i][j] = sym[0];
					if (iswin(board, R, C, i, j, sym[0], winC))
					{
						r = i; c = j;
						board[i][j] = '-';
						return;
					}
					board[i][j] = '-';
				}
			}
		}
		do {
			r = rand() % R;
			c = rand() % C;
		} while (!isvalid(board, r, c, R, C));
	}

	void displayboard(char Board[][MAXCOL], int R, int C)
	{
		cout << "\n";
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (j > 0) cout << ' ';
				cout << Board[i][j];
			}
			cout << '\n';
		}
	}

	void updatetheboard(char b[][MAXCOL], char PSYM, int r, int c)
	{
		color(4);
		b[r][c] = PSYM;
	}

	bool isDraw(char Board[][MAXCOL], int R, int C)
	{
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				if (Board[i][j] == '-') return false;
		return true;
	}

	bool isvalid(char Board[][MAXCOL], int r, int c, int R, int C)
	{
		return (r >= 0 && r < R && c >= 0 && c < C && Board[r][c] == '-');
	}

	void turnchange(int& turn, int NOP)
	{
		turn = (turn + 1) % NOP;
	}

	void displayturnmsg(char PSYM, char PNAME, int R, int C)
	{
		color(5);
		cout << PNAME << " (" << PSYM << ")'s turn - click a cell\n";
	}

	void positionofplayer(int& r, int& c, int C)
	{
		getRowColbyLeftClick(r, c);
	}

	void input(char Board[][MAXCOL], char PSYM[Capacity], char PNAME[Capacity],
	           int& NOP, int& R, int& C, int& turn, int& winC)
	{
		srand((unsigned)time(NULL));
		cout << "(Enter WinCount,DimensionROW,DimensionCOL)";
		cin >> winC >> R >> C;
		int minDim = (R < C) ? R : C;
		if (winC > minDim) winC = minDim;
		if (winC < 2) winC = 2;
		NOP = 2;
		PNAME[0] = 'P';
		PNAME[1] = 'C';
		PSYM[0] = 'O';
		PSYM[1] = 'X';
		for (int ri = 0; ri < R; ri++)
			for (int ci = 0; ci < C; ci++)
				Board[ri][ci] = '-';
		turn = rand() % NOP;
		system("cls");
	}

	void run()
	{
		int turn, NOP, winC, R, C, c = 0, r = 0;
		char Board[MAXROW][MAXCOL], PSYM[Capacity], PNAME[Capacity];
		input(Board, PSYM, PNAME, NOP, R, C, turn, winC);
		displayboard(Board, R, C);
		do
		{
			if (turn == 0)
			{
				do {
					displayturnmsg(PSYM[turn], PNAME[0], R, C);
					positionofplayer(r, c, C);
				} while (!isvalid(Board, r, c, R, C));
				updatetheboard(Board, PSYM[turn], r, c);
			}
			else
			{
				displayturnmsg(PSYM[turn], PNAME[1], R, C);
				computer(Board, PSYM, R, C, r, c, turn, winC);
				updatetheboard(Board, PSYM[turn], r, c);
			}
			system("cls");
			displayboard(Board, R, C);
			if (iswin(Board, R, C, r, c, PSYM[turn], winC))
			{
				color(12);
				system("cls");
				cout << PNAME[turn] << "(" << PSYM[turn] << ")" << " wins the game!";
				break;
			}
			if (isDraw(Board, R, C))
			{
				system("cls");
				cout << "Game Draw";
				break;
			}
			turnchange(turn, NOP);
		} while (true);
		color(7);
		cout << "\nPress any key to exit...\n";
		_getch();
	}
} // end namespace HvC

// ============================================================
//   MAIN  –  menu + switch/case
// ============================================================
int main()
{
	int choice;
	do
	{
		showMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			HvH::run();
			break;
		case 2:
			HvC::run();
			break;
		case 3:
			color(7);
			cout << "\nGoodbye!\n";
			return 0;
		default:
			color(12);
			cout << "\n  Invalid choice! Press any key to try again...\n";
			_getch();
			break;
		}
		color(7);
		cout << "\n\nPress any key to return to menu...\n";
		_getch();
	} while (true);

	return 0;
}
