/*
 * Game.h
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */

#ifndef GAME_H_
#define GAME_H_

#include "Monster.h"

class Game {
public:
	Game();
	virtual ~Game();
	
	void monsterAttack();
	
private:
	int random();
	
private:
	Monster* _dungeon[4];
	
};

#endif /* GAME_H_ */
