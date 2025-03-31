/* 
 * File:   button.h
 * Author: Bruno
 *
 * Created on 6 de marzo de 2018, 18:54
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "sprite.h"

class Button
{
    public:
        Sprite sprite;
        int x, y, width, height;
        
        void init(int sprite, int x, int y, int width, int height)
        {
            this->sprite.load(sprite, 0, 0, width, height);
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }
        bool press(HWND hwnd)
        {
            POINT p;
            if(GetKeyState(VK_LBUTTON) & 0x80 != 0)
                if (GetCursorPos(&p))
                    if (ScreenToClient(hwnd, &p))
                        if(p.x > x && p.x < x + width && p.y > y && p.y < y + height)
                            return true;
            return false;
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            sprite.draw(hdc, hdcBuffer, x, y);
        }
};
#endif /* BUTTON_H */

