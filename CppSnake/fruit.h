/* 
 * File:   fruit.h
 * Author: Bruno
 *
 * Created on 27 de febrero de 2018, 15:05
 */

#ifndef FRUIT_H
#define FRUIT_H

#include <windows.h>
#include "sprite.h"

class Fruit
{
    public:
        Sprite sprite;
        
        int x, y;
        
        void init()
        {
            sprite.loadSprite(IDB_FRUIT, 0, 0, 16, 16);
            x = rand() % 30 + 1;
            y = rand() % 30 + 1;
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x*16, y*16);
        }
};

#endif /* FRUIT_H */

