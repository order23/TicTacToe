#include "board.h"

void Test_player(Player p);

void Test_is_winner()
{
	Player p;

	p.set_player_info('X', "test", 1000);
	Test_player(p);

	p.set_player_info('O', "test", 1000);
	Test_player(p);
}

void Test_player(Player p)
{
	// Create board
	Board b;

	// Horizontal check all rows
	for (int r = 1; r < 4; r++)
	{
		for (int c = 1; c < 4; c++)
			b.set_move(p.get_marker(), r, c);

		_ASSERT(b.is_winner(p));
		b.clear_board();
	}

	// Vertical check all columns
	for (int c = 1; c < 4; c++)
	{
		for (int r = 1; r < 4; r++)
			b.set_move(p.get_marker(), r, c);

		_ASSERT(b.is_winner(p));
		b.clear_board();
	}

	// Check diagonals
	b.set_move(p.get_marker(), 1, 1);
	b.set_move(p.get_marker(), 2, 2);
	b.set_move(p.get_marker(), 3, 3);
	_ASSERT(b.is_winner(p));
	b.clear_board();

	b.set_move(p.get_marker(), 3, 1);
	b.set_move(p.get_marker(), 2, 2);
	b.set_move(p.get_marker(), 1, 3);
	_ASSERT(b.is_winner(p));
	b.clear_board();

	// Check non-winning configurations
	_ASSERT(!b.is_winner(p));
	b.set_move(' ', 1, 1);
	b.set_move(' ', 2, 1);
	_ASSERT(!b.is_winner(p));

	// Add other non-winning combinations TBD
}