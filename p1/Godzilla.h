/*
 * Godzilla.h
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */

#ifndef GODZILLA_H_
#define GODZILLA_H_

#include "Monster.h"

class Godzilla: public Monster {
public:
	Godzilla();
	virtual ~Godzilla();
	
	virtual void attack();
};

#endif /* GODZILLA_H_ */
