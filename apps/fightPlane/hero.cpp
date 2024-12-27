#include "hero.h"
#include <stdio.h>

HeroPlane::HeroPlane(int screenWidth, int screenHeight, int x0, int y0) {
	state = ALIVE;
	life = INIT_LIFE;
    hero1 = "../resources/images/fightPlane/hero1.png";
	hero2 = "../resources/images/fightPlane/hero2.png";
	hero3 = "../resources/images/fightPlane/hero3.png";
	hero4 = "../resources/images/fightPlane/hero4.png";
	current = hero1;
    LoadImage(hero1, this->width, this->height);
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
     
    posX = x0 - width / 2;
    posY = y0 - height;
}

void HeroPlane::Draw() {
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

void HeroPlane::Move(KeyCode key) {
    if (key == KEY_LEFT) {
        posX -= 20;
        if (posX < 0)
            posX = 0;
    } else if (key == KEY_RIGHT) {
        posX += DELTA_DISTANCE2;
        if (posX > (screenWidth - width))
            posX = screenWidth - width;
    } else if (key == KEY_UP) {
        posY -= DELTA_DISTANCE2;
        if (posY < 0)
            posY = 0;
    } else if (key == KEY_DOWN) {
        posY += DELTA_DISTANCE2;
        if (posY > (screenHeight - height))
            posY = screenHeight - height;
    }
}
void HeroPlane::Update(int delta) {
    if (state == ALIVE) {//alive??
     
    }
    else if (state == BLOWING) {//blowing??
        blowingDuratoin += delta;
        if ((blowingDuratoin >= 100) && (blowingDuratoin < 250)) {
            LoadImage(hero2, width, height);
            current = hero2;
        }
        else if ((blowingDuratoin >= 250) && (blowingDuratoin < 400)) {
            LoadImage(hero3, width, height);
            current = hero3;
        }
        else if ((blowingDuratoin >= 450) && (blowingDuratoin < 600)) {
            LoadImage(hero4, width, height);
            current = hero4;
        }
        else if (blowingDuratoin >= 800) {
            state = DEAD;//dead??
        }
    }
}

void HeroPlane::OnCollision() {
    if (state == ALIVE) {//alive
        state = BLOWING;//blowing
        blowingDuratoin = 0;
    }
}

int HeroPlane::GetLife() {
	return life;
}

void HeroPlane::SetLife(int life) {
	this->life = life;
}

State HeroPlane::GetState() {
	return state;
}

Rect HeroPlane::GetBoundingBox(){
    Rect rect;
    rect.x=posX;
    rect.y=posY;
    rect.width=width;
    rect.height=height;
    return rect;
}

