#ifndef __SINGLEBULLET_H__
#define __SINGLEBULLET_H__
#include "../../framework/framework.h"

class SingleBullet{
    string bullet;
    int width, height;
    int posX, posY;
public:
	SingleBullet(int x0, int y0);
	void Draw();
    void Update();
    Rect GetBoundingBox();
};
#endif

