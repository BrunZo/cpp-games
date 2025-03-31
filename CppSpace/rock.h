/*
 * File:   rock.h
 * Author: Bruno
 *
 * Created on 17 de febrero de 2018, 21:26
 */

#ifndef ROCK_H
#define ROCK_H

#include "sprite.h"


class Rock
{
    public:
        Sprite sprite;
        
        int width, height;
        int x, y;
        int vel;
        bool destroyed;
        
        void initRock(RECT* prc, int xParam, int yParam)
        {
            sprite.loadSpriteBitmap(IDB_ROCK);
            sprite.loadSpriteMask(RGB(0, 0, 0));
            width = 32;
            height = 32;
            x = xParam;
            y = yParam;
            vel = 2;
            destroyed = false;
        }
        void updateRock(RECT* prc)
        {
            y += 2;
            
            if(y + height > prc->bottom)
                destroyed = true;
        }
        void drawRock(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x, y, width, height);
        }
}; 

#endif /* ROCK_H */

