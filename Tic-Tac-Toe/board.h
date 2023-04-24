#ifndef GUARD_BOARD_H
#define GUARD_BOARD_H

#include "player.h"

class Board {
public:
	Board();
	void print_board();
	bool submit_move(Player player);
	void set_move(char marker, int r, int c);
	bool is_winner(Player player);
	bool is_tie();
	bool hint(Player p);
	void clear_board();

private:
	char board[3][3];
	unsigned int empty_tiles;

public:
	int hint_row;
	int hint_col;

};

#endif