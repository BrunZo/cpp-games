/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mino.h
 * Author: Bruno
 *
 * Created on 24 de febrero de 2018, 11:39
 */

#ifndef TILE_H
#define TILE_H

#include <windows.h>
#include "sprite.h"

class Tile
{
    public:
        Sprite sprite;
   
        int tile;
        int x, y;
        
        void init(int posx, int posy, int newtile)
        {
            switch(newtile)
            {
                case NOTHING:
                    sprite.loadSprite(IDB_VOID, 0, 0, 16, 16);
                break;
                case WALL:
                    sprite.loadSprite(IDB_WALL, 0, 0, 16, 16);
                break;
                case FOOD:
                    sprite.loadSprite(IDB_FOOD, 0, 0, 16, 16);
                break;
            }
            x = posx;
            y = posy;
            tile = newtile;
        }
        void move(int transx, int transy)
        {
            x += transx;
            y += transy;
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x*16, y*16);
        }
};

#endif /* MINO_H */

