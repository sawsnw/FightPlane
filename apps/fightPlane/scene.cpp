#include "scene.h"

Scene::Scene(int w, int h) {
    width = w;
    height = h;
    score=0;
    SmallEnemyTimer = 0;
    gameOver=false;
}

Scene::~Scene() {
    delete bg;
    delete hero;
    for (set<SingleBullet *>::iterator iter = singlebullets.begin(); iter != singlebullets.end(); iter++) {
        SingleBullet *bullet = *iter;
        delete bullet;
    }
    for (set<SmallEnemyPlane *>::iterator iter = smallEnemys.begin(); iter != smallEnemys.end();iter++) {
        SmallEnemyPlane *enemy = *iter;
        delete enemy;
    }
}

void Scene::Init() {
    bg = new Background(width, height);
    hero = new HeroPlane(width, height, width / 2, height);
    bg->Draw();
    hero->Draw();
}

void Scene::outScreenDetection() {
    for (set<SingleBullet *>::iterator iter = singlebullets.begin(); iter != singlebullets.end();) {
        SingleBullet *bullet = *iter;
        Rect rect = bullet->GetBoundingBox();
        if (rect.y < 0) {
            delete bullet;
            iter = singlebullets.erase(iter);//从singlebullets中删除
        } else {
            iter++;
        }
    }
    for (set<SmallEnemyPlane *>::iterator iter = smallEnemys.begin(); iter != smallEnemys.end();) {
        SmallEnemyPlane *enemy = *iter;
        Rect rect = enemy->GetBoundingBox();
        if (rect.y >= height) {
            delete enemy;
            iter = smallEnemys.erase(iter);//从smallEnemys中删除
        } else {
            iter++;
        }
    }
}

void Scene::Update(int delta) {
    makeEnemyPlane();
    bg->Update();
    for (set<SingleBullet *>::iterator iter = singlebullets.begin(); iter != singlebullets.end(); iter++) {
        SingleBullet *bullet = *iter;
        bullet->Update();
    }
    for (set<SmallEnemyPlane *>::iterator iter = smallEnemys.begin(); iter != smallEnemys.end(); iter++) {
        SmallEnemyPlane *enemy = *iter;
        enemy->Update(delta);
    }
	hero->Update(delta);
    collisionDetection();
    outScreenDetection();
    stateDetection();
}

void Scene::OnPaint() {
    if(gameOver) {
        Rect rect;
        rect.x=rect.y=0;
        rect.width=320;
        rect.height=480;
        DrawImage("../resources/images/fightPlane/gameover.png",rect,rect);
    }else{
        bg->Draw();
        hero->Draw();
        for (set<SingleBullet *>::iterator iter = singlebullets.begin(); iter != singlebullets.end(); iter++) {
            SingleBullet *bullet = *iter;
            bullet->Draw();
        }
        for (set<SmallEnemyPlane *>::iterator iter = smallEnemys.begin(); iter != smallEnemys.end(); iter++) {
            SmallEnemyPlane *enemy = *iter;
            enemy->Draw();
        }
    }
    displayText();
}

void Scene::OnKeyEvent(KeyCode key) {
    if (key == KEY_SPACE) {
        Rect rect = hero->GetBoundingBox();
        SingleBullet *bullet = new SingleBullet(rect.x + rect.width / 2, rect.y);
        singlebullets.insert(bullet);
    }
    hero->Move(key);
}

void Scene::makeEnemyPlane() {
    SmallEnemyPlane *pEnemy;
    SmallEnemyTimer++;
    if (SmallEnemyTimer > 20) {
        srand(time(NULL));
        pEnemy = new SmallEnemyPlane(rand() % 280, 0);
        smallEnemys.insert(pEnemy);
        SmallEnemyTimer = 0;
    }
}

void Scene::displayText() {
    char text1[16], text2[16];
    sprintf(text1,"%s%d","Score:",score);
    DrawText(0,0,text1);
	sprintf(text2, "%s%d", "Life:", hero->GetLife());
	DrawText(0, 20, text2);
}

bool Scene::intersectsRect(Rect &rect1, Rect &rect2) {
    return !(rect1.x > rect2.x + rect2.width ||
        rect1.x + rect1.width < rect2.x ||
        rect1.y > rect2.y + rect2.height ||
        rect1.y + rect1.height < rect2.y);
}

void Scene::collisionDetection() {
    Rect rect1, rect2;
    for (set<SingleBullet *>::iterator iter = singlebullets.begin(); iter != singlebullets.end();) {
        bool collisoned = false;
        SingleBullet *bullet = *iter;
        rect1 = bullet->GetBoundingBox();
        for (set<SmallEnemyPlane *>::iterator iter = smallEnemys.begin(); iter != smallEnemys.end(); iter++) {
            SmallEnemyPlane *pEnemy = *iter;
            if (pEnemy->GetState() != ALIVE) {
                continue;
            }
            rect2 = pEnemy->GetBoundingBox();
            if (intersectsRect(rect1, rect2)) {
                    score += 100;
                pEnemy->OnCollision();
                collisoned = true;
                break;
            }
        }
        if (collisoned) {
            delete bullet;
            iter = singlebullets.erase(iter);
        } else {
            iter++;
        }
    }
    rect1 = hero->GetBoundingBox();
    for (set<SmallEnemyPlane *>::iterator iter = smallEnemys.begin(); iter != smallEnemys.end(); iter++) {
        SmallEnemyPlane *pEnemy = *iter;
        if (pEnemy->GetState() != ALIVE) {
            continue;
        }
        rect2 = pEnemy->GetBoundingBox();
        if (intersectsRect(rect1, rect2)) {
			pEnemy->OnCollision();
			if (hero->GetLife() == 1)
                hero->OnCollision();
			else
                hero->SetLife(hero->GetLife() - 1);
            break;
        }
    }
}

void Scene::stateDetection() {
	if (hero->GetState() == DEAD) {
		gameOver = true;
	}
    for (set<SmallEnemyPlane *>::iterator iter = smallEnemys.begin(); iter != smallEnemys.end();) {
        SmallEnemyPlane *pEnemy = *iter;
        if(pEnemy->GetState()==DEAD){
            delete pEnemy;
            iter=smallEnemys.erase(iter);
        }else{
            iter++;
        }
    }
}

 

