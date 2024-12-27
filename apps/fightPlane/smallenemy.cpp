
#include "smallenemy.h"
#include  <time.h>
#include  <stdlib.h>
SmallEnemyPlane::SmallEnemyPlane(int x0, int y0) :EnemyPlane(x0,y0)
{
	smallEnemy1 = "../resources/images/fightPlane/s_enemy_1.png";
	smallEnemy2 = "../resources/images/fightPlane/s_enemy_2.png";
	smallEnemy3 = "../resources/images/fightPlane/s_enemy_blow.png";
	LoadImage(smallEnemy1, width, height);
	current = smallEnemy1;
	srand(time(NULL));
	deltaX = rand() % 5;
	direction = rand() % 2 == 0 ? 1 : -1;
}


void SmallEnemyPlane::Update(int delta) {
	    if (state == ALIVE) {//alive??
			if (posX <= 5 && direction == -1) {
				direction = 1;
			}
			if (posX >= 290 && direction == 1) {
				direction = -1;
			}
	        posY += 10;
			posX += direction * deltaX;
			duration += delta;
	    } else if (state == BLOWING) {//blowing??
	        blowingDuratoin += delta;
	        if ((blowingDuratoin >= 100) && (blowingDuratoin < 200)) {//100????
	            LoadImage(smallEnemy2, width, height);
	            current = smallEnemy2;
	        } else if ((blowingDuratoin >= 200) && (blowingDuratoin < 300)) {
	            LoadImage(smallEnemy3, width, height);
	            current = smallEnemy3;
	        } else if (blowingDuratoin >= 300) {
	            state = DEAD;//dead??
	        }
	    }
	}