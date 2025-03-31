/* 
 * File:   layer.h
 * Author: Bruno
 *
 * Created on 19 de febrero de 2018, 20:59
 */

#ifndef LAYER_H
#define LAYER_H

#include "rock.h"
#include "bullet.h"

class Layer
{
    public:
        Rock rocks[256];
        Bullet bullets[256];
        
        void initLayer(RECT* prc)
        {
            for(int i = 0; i < 256; i++)
            {
                Rock newrock;
                newrock.initRock(prc, rand() % 480, -128*i);
                rocks[i] = newrock;
                i++;
            }
        }
        void updateLayer(RECT* prc)
        {
            for(int i = 0; i < 256; i++)
                if(!rocks[i].destroyed)
                    rocks[i].updateRock(prc);
            for(int i = 0; i < 256; i++)
                if(!bullets[i].destroyed)
                    bullets[i].updateBullet(prc);
        }
        void drawLayer(HDC hdc, HDC hdcBuffer)
        {
            for(int i = 0; i < 256; i++)
                if(!rocks[i].destroyed)
                    rocks[i].drawRock(hdc, hdcBuffer);
            for(int i = 0; i < 256; i++)
                if(!bullets[i].destroyed)
                    bullets[i].drawBullet(hdc, hdcBuffer);
        }
};

#endif /* LAYER_H */

