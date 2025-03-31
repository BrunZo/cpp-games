/* 
 * File:   class.h
 * Author: Bruno
 *
 * Created on 28 de febrero de 2018, 18:29
 */

#ifndef PACMAN_H
#define PACMAN_H

#include "resources.h"
#include "sprite.h"

class Pacman
{
    public:
        Sprite sprite[4];
        
        int x, y, orientation, draworientation;
        
        void init(int posx, int posy, int side)
        {
            for(int i = 0; i < 4; i++)
                sprite[i].loadSprite(IDB_PACMAN, i*16, 0, 16, 16);
            x = posx;
            y = posy;
            orientation = side;
            draworientation = orientation;
        }
        void rotate(int side)
        {
            switch(orientation)
            {
                case UP:
                    if(side != DOWN)
                        orientation = side;
                break;
                case RIGHT:
                    if(side != LEFT)
                        orientation = side;
                break;
                case DOWN:
                    if(side != UP)
                        orientation = side;
                break;
                case LEFT:
                    if(side != RIGHT)
                        orientation = side;
                break;
                default:
                    orientation = side;
            }
            
            draworientation = orientation;
        }
        void move()
        {
            switch(orientation)
            {
                case UP:
                    y -= 1;
                break;
                case RIGHT:
                    x += 1;
                break;
                case DOWN:
                    y += 1;
                break;
                case LEFT:
                    x -= 1;
                break;
            }
        }
        void back()
        {
            switch(orientation)
            {
                case UP:
                    y += 1;
                break;
                case RIGHT:
                    x -= 1;
                break;
                case DOWN:
                    y -= 1;
                break;
                case LEFT:
                    x += 1;
                break;
            }

            orientation = NODIRECTION;
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            sprite[draworientation].drawSprite(hdc, hdcBuffer, x*16, y*16);
        }
};

#endif /* CLASS_H */

