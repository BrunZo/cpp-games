/* 
 * File:   layer.h
 * Author: Bruno
 *
 * Created on 21 de febrero de 2018, 21:23
 */

#ifndef LAYER_H
#define LAYER_H

#include <windows.h>
#include "part.h"
#include "fruit.h"
#include "sprite.h"

class Layer
{
    int time = 0;
    int side;
    bool grow;
    
    public:
        Snake snake;
        Fruit fruit;
        
        void init(RECT* prc)
        {
            snake.init(16, 16);
            fruit.init();
            
            side = UP;
        }
        void update(RECT* prc)
        {
            time++;
            
            //Rotate
            if(GetKeyState(VK_UP) & 0x8000)
                side = UP;
            
            if(GetKeyState(VK_RIGHT) & 0x8000)
                side = RIGHT;
            
            if(GetKeyState(VK_DOWN) & 0x8000)
                side = DOWN;
            
            if(GetKeyState(VK_LEFT) & 0x8000)
                side = LEFT;
            
            //Move foward
            if(time > 5)
            {
                snake.rotate(side);
                snake.move();
                
                switch(collides())
                {
                    case BOUNDS:
                        init(prc);
                    break;
                    case INTERSECTS:
                        init(prc);
                    break;
                    case FRUIT:
                        snake.grow();
                        next();
                    break;
                }
                
                time = 0;
            }
        }
        void next()
        {
            Fruit newfruit;
            newfruit.init();
            fruit = newfruit;
        }
        int collides()
        {
            if(snake.parts[0].x < 0 || snake.parts[0].x > MAPWIDTH || snake.parts[0].y < 0 || snake.parts[0].y > MAPHEIGHT)
                return BOUNDS;
            for(int i = 1; i < snake.count; i++)
                if(snake.parts[0].x == snake.parts[i].x && snake.parts[0].y == snake.parts[i].y)
                    return INTERSECTS;
            if(snake.parts[0].x == fruit.x && snake.parts[0].y == fruit.y)
                return FRUIT;
            
            return 0;
        }
        void draw(RECT* prc, HDC hdc)
        {
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);
            
            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            
            snake.draw(hdc, hdcBuffer);
            fruit.draw(hdc, hdcBuffer);
            
            BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);
            
            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteDC(hdcBuffer);
            DeleteObject(hbmBuffer);
        }
};

#endif /* LAYER_H */

