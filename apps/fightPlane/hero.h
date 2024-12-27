#include "../../framework/framework.h"
#include "global.h"
#ifndef __HEROPLANE_H__
#define  __HEROPLANE_H__
#define INIT_LIFE 100
#define DELTA_DISTANCE2 20

class HeroPlane {
private:
    string hero1, hero2, hero3, hero4,current;
    State state;
    int width, height;
    int screenWidth, screenHeight;
    int posX, posY;
	int life;
    int blowingDuratoin;

public:
    HeroPlane(int w, int h, int x0, int y0);
    void Draw();

    void Move(KeyCode key);

	void Update(int delta);

	void OnCollision();

	void SetLife(int life);

	int GetLife();

	State GetState();

    Rect GetBoundingBox();
};

#endif


