#include "../../framework/framework.h"

#ifndef __SCENE_H__
#define  __SCENE_H__

#include "background.h"
#include "hero.h"
#include "singlebullet.h"
#include "smallenemy.h"
#include "middleenemy.h"
#include <set>
#include <random>

class Scene {
private:
    int width, height;//�����Ŀ���
    Background *bg;//����
    HeroPlane *hero;
    set<SingleBullet *> singlebullets;
    set<SmallEnemyPlane*> smallEnemys;
	set<MiddleEnemyPlane*> middleEnemys;
    int SmallEnemyTimer;
    int score;
    bool gameOver;

    void outScreenDetection(); //
    void stateDetection();
    void collisionDetection();
    void makeEnemyPlane();//
    bool intersectsRect(Rect &rect1, Rect &rect2);
    void displayText();
public:
    Scene(int w, int h);

    ~Scene();

    void Init();//��ʼ������
    void Update(int delta);//���³���
    void OnPaint();
    void OnKeyEvent(KeyCode key);//�¼�������

};

#endif
