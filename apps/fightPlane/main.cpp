#include "../../framework/framework.h"
#include "scene.h"

char title[] = "Fight Plane";
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 480
#define REFRESH_FREQUENCY 50

Scene *scene;

void getConfig(struct Config *cfg) {
    strcpy(cfg->title, title);
    cfg->width = SCREEN_WIDTH;
    cfg->height = SCREEN_HEIGHT;
    cfg->frequency = REFRESH_FREQUENCY;
}

bool onInit() {
    scene = new Scene(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->Init();
    return true;
}

int onExit() {
    return 0;
}

void onKeyDown(KeyCode key) {
    scene->OnKeyEvent(key);
}

void onKeyUp(KeyCode key) {

}

void onTimer() {
    scene->Update(REFRESH_FREQUENCY);
    return;
}

void onPaint() {
    scene->OnPaint();
}