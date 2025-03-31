/* 
 * File:   brick.h
 * Author: Bruno
 *
 * Created on 16 de febrero de 2018, 15:13
 */

#ifndef BRICK_H
#define BRICK_H

#include <windows.h>
#include "resources.h"
#include "sprite.h"

class Brick
{
    public:
        Sprite sprite;
        
        bool destroyed;
        int width, height;
        int x, y;
        
        void initBrick(RECT* prc, UINT xParam, UINT yParam)
        {
            sprite.loadSpriteBitmap(IDB_BRICK);
            sprite.loadSpriteMask(RGB(0, 0, 0));
            destroyed = false;
            width = 32;
            height = 16;
            x = xParam;
            y = yParam;
        }
        void drawBrick(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x, y, width, height);
        }
};

#endif /* BRICK_H */

