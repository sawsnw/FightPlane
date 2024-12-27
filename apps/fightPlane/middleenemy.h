#ifndef __MIDDLEENEMYPLANE_H__
#define  __MIDDLEENEMYPLANE_H__

#include "../../framework/framework.h"
#include "global.h"
#include "enemy.h"

class MiddleEnemyPlane :public EnemyPlane
{
private:
	string middleEnemy1, middleEnemy2, middleEnemy3, middleEnemy4, middleEnemy5;
	int deltaX;
public:
	MiddleEnemyPlane(int x0, int y0);
	void Update(int delta);
};

#endif
