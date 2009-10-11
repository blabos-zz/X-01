/*
 * BlackDragon.h
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */

#ifndef BLACKDRAGON_H_
#define BLACKDRAGON_H_

#include "Monster.h"

class BlackDragon: public Monster {
public:
	BlackDragon();
	virtual ~BlackDragon();
	
	virtual void attack();
};

#endif /* BLACKDRAGON_H_ */
