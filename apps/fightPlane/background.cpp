#include "background.h"
#include <stdio.h>

Background::Background(int w,int h){
    width=w;
    height=h;
    where_y1 = where_y2 = 0;
    bg1="../resources/images/fightPlane/background-320-480.png";
    bg2="../resources/images/fightPlane/background-320-480.png";
}

void Background::Update() {
    where_y1+=10;
    where_y2+=10;
    /**
     * 背景1已结移出了屏幕，那么就重置两个背景的位置
     */
    if(where_y1>=height){
        where_y1=where_y2=0;
    }
}
void Background::Draw(){
    Rect srcRect,destRect;
    /**
     *  渲染背景1
     */
    srcRect.x=0;
    srcRect.y=0;
    srcRect.width=width;
    srcRect.height=height-where_y1;
    destRect.x=0;
    destRect.y=where_y1;
    destRect.width=width;
    destRect.height=height-where_y1;
#if 0
    printf("(%d %d %d %d) (%d %d %d %d)\n",
            srcRect.x,srcRect.y,srcRect.width,srcRect.height,
	        destRect.x,destRect.y,destRect.width,destRect.height);
#endif
    if(destRect.height>0)
        DrawImage(bg1,srcRect,destRect);
    /**
     *  渲染背景2
     */
    srcRect.x=0;
    srcRect.y=height-where_y2;
    srcRect.width=width;
    srcRect.height=where_y2;
    destRect.x=0;
    destRect.y=0;
    srcRect.width=width;
    destRect.height=where_y2;
#if 0
    printf("(%d %d %d %d) (%d %d %d %d)\n",
            srcRect.x,srcRect.y,srcRect.width,srcRect.height,
	        destRect.x,destRect.y,destRect.width,destRect.height);
#endif
    if (destRect.height > 0)
        DrawImage(bg2,srcRect,destRect);
}