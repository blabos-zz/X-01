/*
 * Game.cpp
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */

#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Godzilla.h"
#include "MajinBoo.h"
#include "BlackDragon.h"
#include "RedDragon.h"

using namespace std;


Game::Game() {
	srand(time(NULL));
	
	_dungeon[0] = new Godzilla();
	_dungeon[1] = new BlackDragon();
	_dungeon[2] = new MajinBoo();
	_dungeon[3] = new RedDragon();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::monsterAttack() {
	int i = random();
	
	_dungeon[3]->attack();
}

int Game::random() {
	return rand() % 4;
}
