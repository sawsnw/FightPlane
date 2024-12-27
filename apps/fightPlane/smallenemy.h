
#ifndef __SMALLENEMYPLANE_H__
#define  __SMALLENEMYPLANE_H__

#include "../../framework/framework.h"
#include "global.h"
#include "enemy.h"

class SmallEnemyPlane :public EnemyPlane
{
private:
	string smallEnemy1, smallEnemy2, smallEnemy3;
	int deltaX;
public:
	SmallEnemyPlane(int x0, int y0);
	void Update(int delta);
};

#endif
