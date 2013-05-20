#include "Team.h"


Team::Team(){
	camera = new FollowCamera(players);
}

Team::~Team(){

}

void Team::addPlayer(Player * p){
	players.push_back(p);
}



