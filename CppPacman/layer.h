/* 
 * File:   layer.h
 * Author: Bruno
 *
 * Created on 21 de febrero de 2018, 21:23
 */

#ifndef LAYER_H
#define LAYER_H

#include <windows.h>
#include "tile.h"
#include "pacman.h"
#include "sprite.h"

class Layer
{
    int time = 0;
    
    public:
        Pacman pacman;
        Tile tiles[MAPWIDTH*MAPHEIGHT];
        
        void init(RECT* prc)
        {
            for(int x = 0; x < MAPWIDTH; x++)
                for(int y = 0; y < MAPHEIGHT; y++)
                {
                    int usset = NOTHING;
                    
                    if(x == 0 || x == MAPWIDTH-1 || y == 0 || y == MAPHEIGHT-1)
                        usset = WALL;
                    for(int i = 0; i < 2; i++)
                        for(int j = 0; j < 2; j++)
                            if(x > 1 + i*9 && x < 5 + i*9 && y > 1 + j*9 && y < 5 + j*9 && !(x == 3 + i*9 && y == 3 + j*9))
                                usset = WALL;
                    for(int i = 0; i < 2; i++)
                        if(x > 5 && x < 10 && y > 1 + i*9 && y < 5 + i*9 && !(x > 6 && x < 9 && y > 2 + i*9 && y < 4 + i*9))
                            usset = WALL;
                    if(x > 1 && x < 14 && y > 5 && y < 10 && !(x > 2 && x < 13 && y > 6 && y < 9))
                        usset = WALL;
                    if(!((x == 3 && y == 3) || (x == 3 && y == 12) || (x == 12 && y == 3) || (x == 12 && y == 12)) && !(x > 6 && x < 9 && ((y > 2 && y < 4) || (y > 11 && y < 13))) && !(x > 2 && x < 13 && y > 6 && y < 9))
                        if(usset != WALL)
                            usset = FOOD;
                        
                    Tile newmino;
                    newmino.init(x, y, usset);
                    tiles[x + y * MAPWIDTH] = newmino;
                }
            
            pacman.init(1, 1, DOWN);
        }
        void update(RECT* prc)
        {
            time++;
            
            //Rotate
            if(GetKeyState(VK_UP) & 0x8000)
                pacman.rotate(UP);
            
            if(GetKeyState(VK_RIGHT) & 0x8000)
                pacman.rotate(RIGHT);
            
            if(GetKeyState(VK_DOWN) & 0x8000)
                pacman.rotate(DOWN);
            
            if(GetKeyState(VK_LEFT) & 0x8000)
                pacman.rotate(LEFT);
            
            if(GetKeyState(VK_ESCAPE) & 0x8000)
                init(prc);
            
            //Move foward
            if(time > 7)
            {
                pacman.move();
                
                if(tiles[pacman.x + pacman.y * MAPWIDTH].tile == WALL)
                    pacman.back();
                if(tiles[pacman.x + pacman.y * MAPWIDTH].tile == FOOD)
                    tiles[pacman.x + pacman.y * MAPWIDTH].init(pacman.x, pacman.y, NOTHING);
                
                time = 0;
            }
            
            bool finished = true;
            for(Tile tile : tiles)
                if(tile.tile == FOOD)
                    finished = false;
            if(finished)
                init(prc);
        }
        void draw(RECT* prc, HDC hdc)
        {
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);
            
            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(BLACK_BRUSH));
            
            pacman.draw(hdc, hdcBuffer);
            for(Tile mino : tiles)
                mino.draw(hdc, hdcBuffer);
            
            BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);
            
            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteDC(hdcBuffer);
            DeleteObject(hbmBuffer);
        }
};

#endif /* LAYER_H */

