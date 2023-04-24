#include "board.h"

void Test_is_tie()
{
	Board b;

	_ASSERT(!b.is_tie());

	for (int r = 1; r < 4; r++)
	{
		for (int c = 1; c < 4; c++)
		{
			b.set_move('X', r, c);
		}
	}
	_ASSERT(b.is_tie());

	b.clear_board();
	for (int r = 1; r < 4; r++)
	{
		for (int c = 1; c < 4; c++)
		{
			if ((r != 2) && (c != 2))
				b.set_move('X', r, c);
		}
	}

	_ASSERT(!b.is_tie());

	// Add more unfilled combinations - TBD
}