#include "middleenemy.h"
#include  <time.h>
#include  <stdlib.h>
MiddleEnemyPlane::MiddleEnemyPlane(int x0, int y0) :EnemyPlane(x0, y0)
{
	middleEnemy1 = "../resources/images/fightPlane/m_enemy_1.png";
	middleEnemy2 = "../resources/images/fightPlane/m_enemy_2.png";
	middleEnemy3 = "../resources/images/fightPlane/m_enemy_3.png";
	middleEnemy4 = "../resources/images/fightPlane/m_enemy_4.png";
	middleEnemy5 = "../resources/images/fightPlane/m_enemy_blow.png";
	LoadImage(middleEnemy1, width, height);
	current = middleEnemy1;
	srand(time(NULL));
	deltaX = rand() % 5;
	direction = rand() % 2 == 0 ? 1 : -1;
}

void MiddleEnemyPlane::Update(int delta) 
{
	if (state == ALIVE)
	{
		posY += 6;
	}
	else if (state == BLOWING) {//blowing??
		blowingDuratoin += delta;
		if ((blowingDuratoin >= 100) && (blowingDuratoin < 200)) {//100????
			LoadImage(middleEnemy2, width, height);
			current = middleEnemy2;
		}
		else if ((blowingDuratoin >= 200) && (blowingDuratoin < 300)) {
			LoadImage(middleEnemy3, width, height);
			current = middleEnemy3;
		}
		else if ((blowingDuratoin >= 300) && (blowingDuratoin < 400)) {
			LoadImage(middleEnemy4, width, height);
			current = middleEnemy4;
		}
		else if (blowingDuratoin >= 400 && (blowingDuratoin < 500)) {
			LoadImage(middleEnemy5, width, height);
			current = middleEnemy5;
		}
		else if (blowingDuratoin >= 500) {
			state = DEAD;//dead??
		}
	}
}