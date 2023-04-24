#ifndef GUARD_PLAYER_H
#define GUARD_PLAYER_H

#include <string>

class Player {
public:
	Player();
	void set_player_info(char marker, std::string name, int time_limit);
	std::string get_name();
	char get_marker();
	void set_player_move();
	std::string get_player_move();
	bool get_timed_out();
	int get_time_limit();
	void start_timer();
	bool stop_timer();

private:
	std::string name;
	char marker;
	std::string move;
	int time_limit;
	time_t start_move_time;
	bool timed_out;	// Forfeit game due to time limit
};

#endif