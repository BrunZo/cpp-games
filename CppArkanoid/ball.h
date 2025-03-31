/* 
 * File:   ball.h
 * Author: Bruno
 *
 * Created on 13 de febrero de 2018, 17:33
 */

#ifndef BALL_H
#define BALL_H

#include <windows.h>
#include "resources.h"
#include "sprite.h"

class Ball
{
    public:
        Sprite sprite;
        
        int width, height;
        int vel;
        int x, y;
        int dx, dy;
        
        void initBall(RECT* prc)
        {
            sprite.loadSpriteBitmap(IDB_BALL);
            sprite.loadSpriteMask(RGB(0, 0, 0));
            
            width = 32;
            height = 32;
            vel = 2;
            x = (prc->right - prc->left) / 2;
            y = (prc->bottom - prc->top) / 2;
            dx = vel;
            dy = vel;
        }
        void updateBall(RECT* prc)
        {
            x += dx;
            y += dy;

            if(x < 0)
            {
                x = 0;
                dx = -dx;
            }
            else if(x + width > prc->right)
            {
                x = prc->right - width;
                dx = -dx;
            }

            if(y < 0)
            {
                y = 0;
                dy = -dy;
            }
            else if(y + height > prc->bottom)
            {
                x = (prc->right - prc->left) / 2;
                y = (prc->bottom - prc->top) / 2;
                dx = vel;
                dy = vel;
            }
        }
        void drawBall(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x, y, width, height);
        }
};

#endif /* BALL_H */

