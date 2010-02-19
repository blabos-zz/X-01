/*
 * MajinBoo.h
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */

#ifndef MAJINBOO_H_
#define MAJINBOO_H_

#include "Monster.h"

class MajinBoo: public Monster {
public:
	MajinBoo();
	virtual ~MajinBoo();
	
	virtual void attack();
};

#endif /* MAJINBOO_H_ */
