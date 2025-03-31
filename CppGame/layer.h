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
    int time = 0;
    int pieces, maxpieces;
    
    public:
        Polimino actual;
        Mino minos[MAPWIDTH*MAPHEIGHT];
        
        void init(RECT* prc)
        {
            for(int x = 0; x < MAPWIDTH; x++)
                for(int y = 0; y < MAPHEIGHT; y++)
                {
                    Mino newmino;
                    newmino.init(x, y, false);
                    minos[x + y * MAPWIDTH] = newmino;
                }
            
            Polimino newactual;
            newactual.init(8, 0, DOWN);
            actual = newactual;
            pieces++;
        }
        void update(RECT* prc)
        {
            time++;
            
            //Rotate
            if(GetKeyState(VK_RIGHT) & 0x8000)
                actual.rotate(RIGHT);
            
            if(GetKeyState(VK_DOWN) & 0x8000)
                actual.rotate(DOWN);
            
            if(GetKeyState(VK_LEFT) & 0x8000)
                actual.rotate(LEFT);
            
            if(GetKeyState(VK_ESCAPE) & 0x8000)
                init(prc, shape);
            
            //Move foward
            if(time > 5)
            {
                actual.move();
                
                if(collides())
                {
                    actual.back();
                    
                    next();
                    if(collides())
                        init(prc, shape);
                }
                
                time = 0;
            }
        }
        void next()
        {
            for(Mino mino : actual.parts)
                minos[mino.x + mino.y * MAPWIDTH].state = true;
            
            Polimino newactual;
            newactual.init(8, 0, DOWN);
            actual = newactual;
            pieces++;
        }
        bool collides()
        {
            if(actual.parts[0].x < 0 || actual.parts[0].x >= MAPWIDTH || actual.parts[0].y < 0 || actual.parts[0].y >= MAPHEIGHT)
                return true;
            for(Mino mino : minos)
                if(mino.state)
                    if(actual.parts[0].x == mino.x && actual.parts[0].y == mino.y)
                        return true;
            
            return false;
        }
        void draw(RECT* prc, HDC hdc)
        {
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);
            
            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            
            for(Mino mino : minos)
                mino.draw(hdc, hdcBuffer);
            actual.draw(hdc, hdcBuffer);
            
            BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);
            
            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteDC(hdcBuffer);
            DeleteObject(hbmBuffer);
        }
};

#endif /* LAYER_H */

