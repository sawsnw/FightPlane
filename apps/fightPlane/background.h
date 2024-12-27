#include "../../framework/framework.h"
#ifndef __BACKGROUND_H__
#define  __BACKGROUND_H__
#include <string>
#define DELTA_DISTANCE 10

using namespace std;

class Background
{
private:
    int width,height;//����
    //����1����Ϣ
    int where_y1;//���϶����y���꣬�����Ǵ��ϵ��¹�����x����ʼ��Ϊ0
    string bg1,bg2;
    //����2����Ϣ
    int where_y2;//���¶����y���꣬�����Ǵ��ϵ��¹�����x����ʼ��Ϊ0
public:
    Background(int w,int h);
    void Update();
    void Draw();
};
#endif