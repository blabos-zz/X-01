/*
 * Monster.h
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */

#ifndef MONSTER_H_
#define MONSTER_H_

#include <iostream>

using namespace std;


class Monster {
public:
	Monster() {};
	virtual ~Monster() {};
	
	virtual void attack() {
		cout << "I'm a Monster" << endl;
	};
	
	void deffend() {
		cout << "Monster don't deffend" << endl;
	}
};

#endif /* MONSTER_H_ */
