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

class Mino
{
    public:
        Sprite sprite;
   
        bool state;
        int x, y;
        
        void init(int posx, int posy, bool newstate)
        {
            sprite.loadSprite(IDB_MINO, 0, 0, 16, 16);
            x = posx;
            y = posy;
            state = newstate;
        }
        void move(int transx, int transy)
        {
            x += transx;
            y += transy;
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            if(state)
                sprite.drawSprite(hdc, hdcBuffer, x*16, y*16);
        }
};

class Polimino
{   
    public:
        int x, y, count, orientation;
        
        Mino parts[4];
        Mino undo;
        
        void init(int posx, int posy, int neworientation)
        {
            x = posx;
            y = posy;
            count = 4;
            orientation = neworientation;
            
            for(int i = 0; i < count; i++)
            {
                Mino newpart;
                newpart.init(x, y, true);
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
            
            undo = parts[count-1];
            
            for(int i = count; i > 1; i--)
                parts[i-1] = parts[i-2];
                
            Mino newpart;
            newpart.init(parts[0].x + movx, parts[0].y + movy, true);
            parts[0] = newpart;
        }
        void back()
        {
            for(int i = 0; i < count; i++)
            {
                parts[i] = parts[i+1];
            }
                
            parts[count-1] = undo;
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
            count++;
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            for(int i = 0; i < count; i++)
                parts[i].draw(hdc, hdcBuffer);
        }
};

#endif /* MINO_H */

