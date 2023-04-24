#include <iostream>
#include <string>

#include "player.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

// globals
static int count = 1;

// Default constructor
Player::Player()
{
}

void Player::set_player_info(char marker, std::string name, int time_limit) {
	this->marker = marker;
	this->name = name;
	this->time_limit = time_limit;
	this->timed_out = false;
	++count;
}

string Player::get_name() {
	return this->name;
}

char Player::get_marker() {
	return this->marker;
}	

void Player::set_player_move() {
	cout << "Enter a move (" << this->marker << ") " << this->name << ": ";
	getline(cin, this->move);
}

string Player::get_player_move() {
	return this->move;
}

bool Player::get_timed_out()
{
	return this->timed_out;
}

int Player::get_time_limit()
{
	return time_limit;
}

void Player::start_timer()
{
	start_move_time = time(nullptr);
}

bool Player::stop_timer()
{
	if (difftime(time(nullptr), start_move_time) > time_limit)
	{
		timed_out = true;
	}
	return timed_out;
}