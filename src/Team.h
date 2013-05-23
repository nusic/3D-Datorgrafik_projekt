#ifndef TEAM
#define TEAM 

#include "Player.h"
#include "FollowCamera.h"

class Team{
public:
	Team();
	~Team();

	void addPlayer(Player*);
	
	std::vector<Player*> players;
	FollowCamera * camera;

};
#endif