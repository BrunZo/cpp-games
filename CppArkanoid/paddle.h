/* 
 * File:   paddle.h
 * Author: Bruno
 *
 * Created on 13 de febrero de 2018, 17:33
 */

#ifndef PADDLE_H
#define PADDLE_H

#include <windows.h>
#include "resources.h"
#include "sprite.h"

class Paddle
{
    public:
        Sprite sprite;
        
        int width, height;
        int x, y;
        int vel;
        
        void initPaddle(RECT* prc)
        {
            sprite.loadSpriteBitmap(IDB_PADDLE);
            sprite.loadSpriteMask(RGB(0, 0, 0));
            width = 64;
            height = 16;
            vel = 2;
            x = (prc->right - prc->left) / 2;
            y = (prc->bottom - prc->top) / 10 * 9;
        }
        void updatePaddle(RECT* prc)
        {
            if(GetKeyState(VK_LEFT) & 0x8000)
            {
                x -= vel;
            }
            if(GetKeyState(VK_RIGHT) & 0x8000)
            {
                x += vel;
            }
            
            if(x < 0)
            {
                x = 0;
            }
            else if(x + width > prc->right)
            {
                x = prc->right - width;
            }
        }
        void drawPaddle(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x, y, width, height);
        }
};

#endif /* PADDLE_H */

