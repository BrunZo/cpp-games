/*/*
 * File:   box.h
 * Author: Bruno
 *
 * Created on 24 de febrero de 2018, 11:39
 */

#ifndef BOX_H
#define BOX_H

#include <windows.h>
#include "sprite.h"

class Box
{
    public:
        Sprite sprite;
   
        bool locked, bomb;
        int number;
        int x, y;
        
        void init(int posx, int posy, bool havebomb, int newnumber)
        {
            sprite.loadSprite(IDB_BOX, 0, 0, 16, 16);
            locked = true;
            bomb = havebomb;
            number = newnumber;
            x = posx;
            y = posy;
        }
        void unlock()
        {
            locked = false;
            
            if (!bomb)
                sprite.loadSprite(IDB_BOX, (number+1)*16, 0, 16, 16);
            else
                sprite.loadSprite(IDB_BOX, 160, 0, 16, 16);
        }
        void draw(HDC hdc, HDC hdcBuffer)
        {
            sprite.drawSprite(hdc, hdcBuffer, x*16, y*16);
        }
};

#endif /* MINO_H */