/* 
 * File:   mainmenu.h
 * Author: Bruno
 *
 * Created on 6 de marzo de 2018, 18:31
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "state.h"
#include "sprite.h"
#include "button.h"

class Mainmenu : public State
{
    public:
        Sprite background;
        Button button;
        
        virtual void init(RECT* prc)
        {
            button.init(IDB_START, 224, 376, 64, 16);
        }
        virtual void update(RECT* prc, HWND hwnd)
        {
            if(button.press(hwnd))
            {
                MessageBox(NULL, "Window creation failed!", "Error!",
                    MB_ICONEXCLAMATION | MB_OK);
            }
        }
        virtual void draw(HDC hdc, HDC hdcBuffer)
        {
            button.draw(hdc, hdcBuffer);
        }
};

#endif /* MAINMENU_H */

