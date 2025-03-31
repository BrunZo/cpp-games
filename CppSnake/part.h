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

#ifndef MINO_H
#define MINO_H

#include <windows.h>
#include "sprite.h"

class Part
{
    public:
        Sprite sprite;
        
        bool state;
        int x, y;
        
        void init(int posx, int posy)
        {
            sprite.loadSprite(IDB_PART, 0, 0, 16, 16);
            x = posx;
            y = posy;
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

class Snake
{   
    public:
        Part parts[256];
        
        int x, y, count, orientation;
        
        void init(int posx, int posy)
        {
            x = posx;
            y = posy;
            count = 4;
            orientation = UP;
            
            for(int i = 0; i < 256; i++)
            {
                Part newpart;
                newpart.init(x + i, y);
                newpart.state = i < 4 ? true : false;
                parts[i] = newpart;
            }
        }
        void move()
        {
            int movx = 0;
            int movy = 0;
            
            switch(orientation)
            {
                case UP:
                    movy -= 1;
                break;
                case RIGHT:
                    movx += 1;
                break;
                case DOWN:
                    movy += 1;
                break;
                case LEFT:
                    movx -= 1;
                break;
            }
            
            for(int i = count; i > 1; i--)
            {
                parts[i-1].state = true;
                parts[i-1] = parts[i-2];
            }
                
            Part newpart;
            newpart.init(parts[0].x + movx, parts[0].y + movy);
            parts[0] = newpart;
        }
        void rotate(int side)
        {
            switch(side)
            {
                case UP:
                    if(orientation != DOWN)
                        orientation = UP;
                break;
                case LEFT:
                    if(orientation != RIGHT)
                        orientation = LEFT;
                break;
                case DOWN:
                    if(orientation != UP)
                        orientation = DOWN;
                break;
                case RIGHT:
                    if(orientation != LEFT)
                        orientation = RIGHT;
                break;
            }
        }
        void grow()
        {
            if(count < 256)
                count++;
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            for(int i = 0; i < 256; i++)
                if(parts[i].state)
                    parts[i].draw(hdc, hdcBuffer);
        }
};

#endif /* MINO_H */

