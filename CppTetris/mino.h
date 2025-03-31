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
#include <ctime>
#include <math.h>
#include "sprite.h"

class Mino
{
    public:
        Sprite sprite;
        
        bool state;
        int x, y;
        
        void init(bool newstate, int posx, int posy, int color)
        {
            sprite.loadSprite(IDB_MINO, color*16, 0, 16, 16);
            state = newstate;
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

class Polimino
{
    int O[4] = {52224, 52224, 52224, 52224};
    int S[4] = {27648, 17952, 1728, 35904};
    int Z[4] = {50688, 9792, 3168, 19584};
    int L[4] = {11776, 17504, 3712, 50240};
    int J[4] = {36352, 25664, 3616, 17600};
    int T[4] = {58368, 9760, 1248, 35968};
    int I[4] = {17476, 3840, 8738, 240};
    
    public:
        Mino minos[4];
        
        int x, y, variant, form, orientation;
        
        void init(int posx, int posy)
        {
            x = posx;
            y = posy;
            variant = rand() % 7;
            orientation = UP;
            
            switch(variant)
            {
                case 0: 
                    form = Z[orientation];
                break;
                case 1: 
                    form = L[orientation];
                break;
                case 2: 
                    form = O[orientation];
                break;
                case 3: 
                    form = S[orientation];
                break;
                case 4: 
                    form = J[orientation];
                break;
                case 5: 
                    form = T[orientation];
                break;
                case 6: 
                    form = I[orientation];
                break;
            }
        }
        void construct()
        {
            int pos = 0;
            for(int i = 0; i < 16; i++)
                if(form >> i & 1)
                {
                    Mino mino;
                    mino.init(true, x + 3 - (i % 4), y + 3 - (i - (i % 4)) / 4, variant);
                    minos[pos++] = mino;
                }
        }
        void move(int posx, int posy)
        {
            x += posx;
            y += posy;
            
            for(int i = 0; i < 4; i++)
                minos[i].move(posx, posy);
        }
        void rotate(int side)
        {
            if(side == RIGHT)
                ++orientation %= 4;
            else if(side == LEFT)
            {
                rotate(RIGHT);
                rotate(RIGHT);
                rotate(RIGHT);
            }
            
            switch(variant)
            {
                case 0: 
                    form = Z[orientation];
                break;
                case 1: 
                    form = L[orientation];
                break;
                case 2: 
                    form = O[orientation];
                break;
                case 3: 
                    form = S[orientation];
                break;
                case 4: 
                    form = J[orientation];
                break;
                case 5: 
                    form = T[orientation];
                break;
                case 6: 
                    form = I[orientation];
                break;
            }
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            for(int i = 0; i < 4; i++)
                minos[i].draw(hdc, hdcBuffer);
        }
};

#endif /* MINO_H */

