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
        
        bool cpu;
        int width, height;
        int x, y;
        int vel;
        
        void initPaddle(RECT* prc, BOOL side)
        {
            sprite.LoadSpriteBitmap(IDB_PADDLE);
            sprite.LoadSpriteMask(RGB(0, 0, 0));
            width = 16;
            height = 64;
            vel = 2;
            
            switch(side)
            {
                case LEFT:
                {
                    x = (prc->right - prc->left) / 10;
                    y = (prc->bottom - prc->top) / 2;
                    cpu = false;
                }
                break;
                case RIGHT:
                {
                    x = (prc->right - prc->left) / 10 * 9;
                    y = (prc->bottom - prc->top) / 2;
                    cpu = true;
                }
                break;
            }
        }
        void updatePaddle(RECT* prc)
        {
            if(!cpu)
            {
                if(GetKeyState(VK_UP) & 0x8000)
                {
                    y -= vel;
                }
                if(GetKeyState(VK_DOWN) & 0x8000)
                {
                    y += vel;
                }
            }
            
            if(y < 0)
            {
                y = 0;
            }
            else if(y + height > prc->bottom)
            {
                y = prc->bottom - height;
            }
        }
        void drawPaddle(HDC hdc, HDC hdcBuffer)
        {
            sprite.DrawSprite(hdc, hdcBuffer, x, y, width, height);
        }
};

#endif /* PADDLE_H */

