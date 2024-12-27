#ifndef __ENEMYPLANE_H__
#define  __ENEMYPLANE_H__

#include "../../framework/framework.h"
#include "global.h"

class EnemyPlane {
protected:
    string current;
    State state;
    //int deltaX;
    int width, height;
    int posX, posY;
    int duration;
    int blowingDuratoin;
    int direction;
public:
    EnemyPlane(int x0, int y0);

    //void Update(int delta);

    void Draw();

    void OnCollision();

    State GetState();

    Rect GetBoundingBox();
};

#endif