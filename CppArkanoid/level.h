/* 
 * File:   level.h
 * Author: Bruno
 *
 * Created on 16 de febrero de 2018, 15:35
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <windows.h>
#include "brick.h"

int levels[256][256] = {{0, 128, 32, 128, 64, 128, 96, 128, 128, 128, 160, 128, 192, 128, 224, 128, 256, 128,
                        288, 128, 320, 128, 352, 128, 384, 128, 416, 128, 448, 128, 480, 128, 512, 128}};

class Level
{
    public:
        int count;
        Brick bricks[];

        void initLevel(RECT* prc, UINT levelParam)
        {
            count = 16;
            bricks[count];
            
            for(int i = 0; i < count; i++)
            {
                Brick brick;
                brick.initBrick(prc, levels[0][i*2], levels[0][i*2+1]);
                bricks[i] = brick;
            }
        }
        void drawLevel(HDC hdc, HDC hdcBuffer)
        {
            for(int i = 0; i < count; i++)
            {
                if(!bricks[i].destroyed)
                {
                    bricks[i].drawBrick(hdc, hdcBuffer);
                }
            }
        }
};

#endif /* LEVEL_H */

