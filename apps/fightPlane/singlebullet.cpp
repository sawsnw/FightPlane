#include "singlebullet.h"

SingleBullet::SingleBullet(int x0, int y0) {
    bullet = "../resources/images/fightPlane/singlebullet.png";;
    LoadImage(bullet, this->width, this->height);

    posX = x0 - this->width / 2;
    posY = y0 - this->height;
}

void SingleBullet::Update() {
    posY-=30;
}

void SingleBullet::Draw() {
    Rect src, dest;
    src.x = src.y = 0;
    src.width = this->width;
    src.height = this->height;
    dest.x = posX;
    dest.y = posY;
    dest.width = this->width;
    dest.height = this->height;
    DrawImage(bullet, src, dest);
}

Rect SingleBullet::GetBoundingBox(){
    Rect rect;
    rect.x=posX;
    rect.y=posY;
    rect.width=width;
    rect.height=height;
    return rect;
}



