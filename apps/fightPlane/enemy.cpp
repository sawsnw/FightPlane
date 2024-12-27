#include "enemy.h"
#include  <time.h>
#include  <stdlib.h>

void EnemyPlane::Draw() {
    Rect src, dest;
    src.x = src.y = 0;
    src.width = this->width;
    src.height = this->height;
    dest.x = posX;
    dest.y = posY;
    dest.width = this->width;
    dest.height = this->height;
    DrawImage(current, src, dest);
}
EnemyPlane::EnemyPlane(int x0,int y0)
{
    state = ALIVE;
    posX = x0;
    posY = y0;
    blowingDuratoin = 0;
    duration = 0;

}

void EnemyPlane::OnCollision() {
    if (state == ALIVE) {//alive
        state = BLOWING;//blowing
        blowingDuratoin = 0;
    }
}

Rect EnemyPlane::GetBoundingBox() {
    Rect rect;
    rect.x = posX;
    rect.y = posY;
    rect.width = width;
    rect.height = height;
    return rect;
}

State EnemyPlane::GetState() {
    return state;
}