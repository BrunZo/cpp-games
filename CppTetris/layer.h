/* 
 * File:   layer.h
 * Author: Bruno
 *
 * Created on 21 de febrero de 2018, 21:23
 */

#ifndef LAYER_H
#define LAYER_H

#include <windows.h>
#include "mino.h"
#include "sprite.h"

class Layer
{
    int left = 0;
    int right = 0;
    int down = 0;
    bool up = true;
    bool space = true;
    int time = 0;
    int fall = 0;
    
    public:
        Mino minos[MAPWIDTH*MAPHEIGHT];
        Polimino actual;
        
        void init(RECT* prc)
        {
            for(int x = 0; x < MAPWIDTH; x++)
                for(int y = 0; y < MAPHEIGHT; y++)
                {
                    Mino mino;
                    mino.init(true, x, y, 0);
                    minos[x + y * MAPWIDTH] = mino;
                }
            
            actual.init(3, 0);
            actual.construct();
        }
        void update(RECT* prc)
        {
            left++;
            right++;
            down++;
            time++;
            
            if(fall > 0)
                fall++;
            
            //Left
            if(GetKeyState(VK_LEFT) & 0x8000 && left > 10)
            {
                actual.move(-1, 0);
                left = 0;
                
                if(collides())
                    actual.move(1, 0);
            }
            
            //Right
            if(GetKeyState(VK_RIGHT) & 0x8000 && right > 10)
            {
                actual.move(1, 0);
                right = 0;
                
                if(collides())
                    actual.move(-1, 0);
            }
            
            //Fast down
            if(GetKeyState(VK_DOWN) & 0x8000 && down > 1)
            {
                actual.move(0, 1);
                down = 0;
                
                if(collides())
                    actual.move(0, -1);
            }
            
            //Auto fall
            if(GetKeyState(VK_SPACE) & 0x8000 && space)
            {
                int fall = true;
                
                while(fall)
                {
                    actual.move(0, 1);
                
                    if(collides())
                    {
                        actual.move(0, -1);
                        space = false;
                        fall = false;
                        next(prc);
                    }
                }
            }
            if(!(GetKeyState(VK_SPACE) & 0x8000))
                space = true;
            
            //Rotate
            if(GetKeyState(VK_UP) & 0x8000 && up)
            {
                actual.rotate(RIGHT);
                actual.construct();
                up = false;
                
                if(collides())
                {
                    actual.rotate(LEFT);
                    actual.construct();
                }
            }
            if(!(GetKeyState(VK_UP) & 0x8000))
                up = true;
            
            //Fall
            if(time > 50)
            {
                actual.move(0, 1);
                time = 0;
                
                if(collides())
                {
                    actual.move(0, -1);
                    next(prc);
                }
            }
            
            //Check row
            for(int y = 0; y < MAPHEIGHT; y++)
            {
                bool complete = true;
                for(int x = 0; x < MAPWIDTH; x++)
                    if(!minos[y * MAPWIDTH + x].state)
                        complete = false;
                if(complete)
                {
                    for(int x = 0; x < MAPWIDTH; x++)
                        minos[y * MAPWIDTH + x].state = false;
                    for(int i = 0; i < y; i++)
                        for(int x = 0; x < MAPWIDTH; x++)
                        {
                            int yi1 = y - i - 1;
                            minos[yi1 * MAPWIDTH + x].move(0, 1);
                            minos[(yi1 + 1) * MAPWIDTH + x] = minos[yi1 * MAPWIDTH + x];
                        }
                }
            }    
        }
        void next(RECT* prc)
        {
            for(Mino testmino : actual.minos)
                minos[testmino.y * MAPWIDTH + testmino.x] = testmino;
            
            actual.init(3, 0);
            actual.construct();
            
            if(collides())
                init(prc);
        }
        bool collides()
        {
            for(Mino testmino : actual.minos)
            {
                for(Mino mino : minos)
                    if(mino.state && testmino.x == mino.x && testmino.y == mino.y)
                        return true;
                if(testmino.x < 0 || testmino.x >= MAPWIDTH || testmino.y < 0 || testmino.y >= MAPHEIGHT)
                    return true;
            }
                
            return false;
        }
        void draw(RECT* prc, HDC hdc)
        {
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);
            
            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            
            for(Mino mino : minos)
                if(mino.state)
                    mino.draw(hdc, hdcBuffer);
            actual.draw(hdc, hdcBuffer);
            
            BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);
            
            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteDC(hdcBuffer);
            DeleteObject(hbmBuffer);
        }
};

#endif /* LAYER_H */

