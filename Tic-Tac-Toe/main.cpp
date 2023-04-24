#include <iostream>
#include <string>

#include "player.h"
#include "board.h"
using namespace std;

using std::cout;
using std::endl;
using std::string;

#define TITLE "Tic-Tac-Toe"

void Test_is_winner();
void Test_is_tie();

int main() {
	Test_is_winner();
	Test_is_tie();

	char markers[] = { 'X', 'O' };

	// display title
	string padding = string(11, '*');
	cout << padding << endl << TITLE << endl << padding << endl;

	Player player1;
	Player player2;
	// Prompt for player information, and construct player objects
	for (int player_number = 1; player_number < 3; player_number++)
	{
		string name;
		int time_limit;
		char marker = markers[player_number - 1];

		cout << "Enter player " << player_number << "'s name: ";
		getline(cin, name);
		cout << name << "'s marker is " << marker << endl;

		cout << "Enter player " << player_number << "'s time limit (s): ";
		std::string limit;
		getline(cin, limit);
		time_limit = stoi(limit);
		cout << name << "'s time limit is " << time_limit << "s" << endl;

		if (player_number == 1)
			player1.set_player_info(marker, name, time_limit);
		else
			player2.set_player_info(marker, name, time_limit);
	}

	// initialise objects
	Board board;

	// game loop
	while (true) {
		board.print_board();
		// player 1's turn
		// has player 2 won the game or is the game a tie?
		if (board.is_winner(player2)) {
			cout << "Well done " << player2.get_name() << " you have won.";
			return 0;
		}
		if (board.is_tie()) {
			cout << "The game has been tied!";
			return 0;
		}
		if (board.hint(player1))
			cout << "Hint: placing " << player1.get_marker() << " at position ("
				<< board.hint_col << ", " << board.hint_row << ") will win the game!\n";

		// Start timer for player 1
		player1.start_timer();

		// check to see if player 1's move is legit then write it to the board
		while (!(board.submit_move(player1))) {
			continue;
		}

		// check if player 1 exceeded the time limit
		if (player1.stop_timer())
		{
			cout << "You lose " << player1.get_name() << ". You did not make a move within the allowed time "
				<< player1.get_time_limit() << "s";
			return 0;
		}
		
		board.print_board();

		// player 2's turn
		// has player 1 won the game or is the game a tie?
		if (board.is_winner(player1)) {
			cout << "Well done " << player1.get_name() << " you have won.";
			return 0;
		}
		if (board.is_tie()) {
			cout << "The game has been tied!";
			return 0;
		}
		if (board.hint(player2))
			cout << "Hint: placing " << player2.get_marker() << " at position ("
				<< board.hint_col << ", " << board.hint_row << ") will win the game!\n";

		// Start timer for player 2
		player2.start_timer();

		// check to see if player 2's move is legit then write it to the board
		while (!(board.submit_move(player2))) {
			continue;
		}

		// check if player 2 exceeded the time limit
		if (player2.stop_timer())
		{
			cout << "You lose " << player2.get_name() << ". You did not make a move within the allowed time "
				<< player2.get_time_limit() << "s";
			return 0;
		}

	}

	return 0;
}