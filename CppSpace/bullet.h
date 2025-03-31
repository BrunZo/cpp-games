/*
 * File:   rock.h
 * Author: Bruno
 *
 * Created on 17 de febrero de 2018, 21:26
 */

#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"

class Bullet
{
    public:
        Sprite sprite;
        
        int width, height;
        int x, y;
        int vel;
        bool destroyed;
        
        void initBullet(RECT* prc, int xParam, int yParam)
        {
            sprite.loadSpriteBitmap(IDB_BULLET);
            sprite.loadSpriteMask(RGB(0, 0, 0));
            width = 4;
            height = 4;
            x = xParam;
            y = yParam;
            vel = 2;
            destroyed = false;
        }
        void updateBullet(RECT* prc)
        {
            y -= 2;
            
            if(y < 0)
                destroyed = true;
        }
        void drawBullet(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x, y, width, height);
        }
}; 

#endif /* BULLET_H */

