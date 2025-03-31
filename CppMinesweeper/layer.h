/* 
 * File:   layer.h
 * Author: Bruno
 *
 * Created on 21 de febrero de 2018, 21:23
 */

#ifndef LAYER_H
#define LAYER_H

#include <windows.h>
#include <math.h>
#include "box.h"
#include "sprite.h"

class Layer
{  
    public:
        int map[MAPWIDTH*MAPHEIGHT];
        Box boxes[MAPWIDTH*MAPHEIGHT];
        
        void init()
        {
            for(int x = 0; x < MAPWIDTH; x++)
                for(int y = 0; y < MAPHEIGHT; y++)
                {
                    if(rand() % 8 == 0)
                        map[x + y * MAPWIDTH] = true;
                    else
                        map[x + y * MAPWIDTH] = false;
                }
                    
            for(int x = 0; x < MAPWIDTH; x++)
                for(int y = 0; y < MAPHEIGHT; y++)
                {
                    bool bomb = map[x + y * MAPWIDTH];
                        
                    int bombs = 0;
                    for(int px = -1; px <= 1; px++)
                        for(int py = -1; py <= 1; py++)
                            if(!(px == 0 && py == 0))
                                if(!(x + px < 0 || x + px >= MAPWIDTH || y + py < 0 || y + py >= MAPHEIGHT))
                                    if(map[(x + px) + (y + py) * MAPWIDTH])
                                        bombs++;
                            
                    Box newbox;
                    newbox.init(x, y, bomb, bombs);
                    boxes[x + y * MAPWIDTH] = newbox;
                }
        }
        void update(RECT* prc)
        {
            POINT p;
            
            if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
                if (GetCursorPos(&p))
                {
                    int x = floor((p.x - X - 9) / 16);
                    int y = floor((p.y - Y - 33) / 16);
                    
                    if(!(x < 0 || x >= MAPWIDTH || y < 0 || y >= MAPHEIGHT))
                        unlock(x, y);
                }
        }
        void unlock(int x, int y)
        {
            boxes[x + y * MAPWIDTH].unlock();
            
            bool lose;
            if(boxes[x + y * MAPWIDTH].bomb)
                lose = true;
            
            for(int px = -1; px <= 1; px++)
                for(int py = -1; py <= 1; py++)
                    if(!(px == 0 && py == 0))
                        if(!(x + px < 0 || x + px >= MAPWIDTH || y + py < 0 || y + py >= MAPHEIGHT))
                            if(!boxes[x + y * MAPWIDTH].number)
                                if(boxes[(x + px) + (y + py) * MAPWIDTH].locked)
                                    unlock(x + px, y + py);
                           
            bool win = true;
            for(int x = 0; x < MAPWIDTH; x++)
                for(int y = 0; y < MAPHEIGHT; y++)
                    if(boxes[x + y * MAPWIDTH].locked)
                        if(!boxes[x + y * MAPWIDTH].bomb)
                            win = false;
            
            if(lose)
                for(int x = 0; x < MAPWIDTH; x++)
                    for(int y = 0; y < MAPHEIGHT; y++)
                        if(boxes[x + y * MAPWIDTH].locked)
                            unlock(x, y);
            else if(win)
                MessageBox(NULL, "Finish", "Message", MB_ICONASTERISK | MB_OK);
        }
        void draw(RECT* prc, HDC hdc)
        {
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);
            
            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            
            for(Box box : boxes)
                box.draw(hdc, hdcBuffer);
            
            BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);
            
            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteDC(hdcBuffer);
            DeleteObject(hbmBuffer);
        }
};

#endif /* LAYER_H */

