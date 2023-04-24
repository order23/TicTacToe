#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>

#include "board.h"
#include "player.h"

using std::cout;
using std::endl;
using std::cin;
using std::setw;
using std::string;
using std::stoi;
using std::isdigit;

#define X 'X'
#define O 'O'
#define TO_INDEX (-1)

Board::Board() :
	board{ { ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' } } {
	this->empty_tiles = 9;
}

void Board::print_board() {
	cout << endl;
	for (size_t row = 0; row < 3; ++row) {
		cout << setw(3);
		for (size_t column = 0; column < 3; ++column) {
			cout << "(" << this->board[row][column] << ")";
			if (column == 0 || column == 1) {
				cout << setw(3) << "|" << setw(3);
			}
		}
		if (row == 0 || row == 1) {
			cout << endl << string(23, '-') << endl;
		}
	}
	cout << endl;
	// clear screen
	cout << string(2, '\n');
}

// prompt user for input then write to board
bool Board::submit_move(Player player) {

	// prompt user for input
	player.set_player_move();

	// checks to see if input is size 3 and contains a space in the middle 1 1
	if (player.get_player_move().size() != 3 || player.get_player_move()[1] != ' ' || !(isdigit(player.get_player_move()[0])) || !(isdigit(player.get_player_move()[2]))) {
		cout << "Invalid Input " << player.get_name() << ": Please enter a column then a row (Example: 1 1)." << endl;
		return false;
	}

	// convert char input into string
	unsigned int column_move = stoi(string(1, player.get_player_move()[0])) + TO_INDEX;
	unsigned int row_move = stoi(string(1, player.get_player_move()[2])) + TO_INDEX;

	// check to see if integers are in bound
	if (row_move > 2 || column_move > 2) {
		cout << "Selected region out of bounds." << endl;
		return false;
	}

	// check to see if current sqaure is taken
	if (this->board[row_move][column_move] == X || this->board[row_move][column_move] == O) {
		cout << "This square is taken " << player.get_name() << "." << endl;
		return false;
	}

	this->board[row_move][column_move] = player.get_marker();

	// keep track of empty tiles for Board::is_tie() function
	--(this->empty_tiles);

	return true;
}

void Board::set_move(char marker, int r, int c)
{
	if ((r > 0) && (r < 4) && (c > 0) && (c < 4))
	{
		this->board[r - 1][c - 1] = marker;
		empty_tiles--;
	}
}

// check to see if player has a winning position
bool Board::is_winner(Player player) {
	// For every row
	for (int row = 0; row < 3; row++)
	{
		// check column
		for (int i = 0; i < 3; ++i) {
			if (this->board[row][i] != player.get_marker()) {
				break;
			}
			if (i == 2) {
				//cout << "Well done " << player.get_name() << " you have won.";
				return true;
			}
		}
	}

	// For every column
	for (int col = 0; col < 3; col++)
	{
		// check row
		for (int i = 0; i < 3; ++i) {
			if (this->board[i][col] != player.get_marker()) {
				break;
			}
			if (i == 2) {
				//cout << "Well done " << player.get_name() << " you have won.";
				return true;
			}
		}
	}

	// check diagonal
	for (int i = 0; i < 3; ++i) {
		if (this->board[i][i] != player.get_marker()) {
			break;
		}
		if (i == 2) {
			//cout << "Well done " << player.get_name() << " you have won.";
			return true;
		}
	}

	// check inverse diagonal
	for (int i = 0, j = 2; i < 3; ++i, --j) {
		if (this->board[j][i] != player.get_marker()) {
			break;
		}
		if (i == 2) {
			//cout << "Well done " << player.get_name() << " you have won.";
			return true;
		}
	}
	
	return false;
}

bool Board::is_tie() {
	// if there are no empty tiles then it is a tie
	if (this->empty_tiles == 0) {
		return true;
	}

	return false;
}

bool Board::hint(Player p)
{
	hint_row = 0;
	hint_col = 0;

	// For every avalable position, add player token and check if it wins
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (this->board[row][col] == ' ')
			{
				this->board[row][col] = p.get_marker();	// Make move

				// Check winner
				if (is_winner(p))
				{
					this->board[row][col] = ' ';	// Back out move

					// Record hint
					hint_row = row + 1;
					hint_col = col + 1;
					break;
				}

				this->board[row][col] = ' ';	// Back out move
			}
		}
	}

	return ((hint_row != 0) && (hint_col != 0));
}

void Board::clear_board()
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
			board[row][col] = ' ';
	}
	empty_tiles = 9;
}
