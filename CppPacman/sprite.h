/* 
 * File:   sprite.h
 * Author: Bruno
 *
 * Created on 13 de febrero de 2018, 17:34
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <windows.h>
#include "resources.h"

class Sprite
{
    public:
        HBITMAP bitmap, mask;
        int x, y, width, height;
        
        void loadSprite(UINT src, int transx, int transy, int bmpwidth, int bmpheight)
        {   
            HDC hdcMem, hdcMem2;
            HBITMAP hbm, hbmMask;

            hbm = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(src));
            hbmMask = CreateBitmap(bmpwidth, bmpheight, 1, 1, NULL);

            hdcMem = CreateCompatibleDC(0);
            hdcMem2 = CreateCompatibleDC(0);

            SelectObject(hdcMem, hbm);
            SelectObject(hdcMem2, hbmMask);

            SetBkColor(hdcMem, RGB(0, 0, 0));

            BitBlt(hdcMem2, 0, 0, bmpwidth, bmpheight, hdcMem, 0, 0, SRCCOPY);

            BitBlt(hdcMem, 0, 0, bmpwidth, bmpheight, hdcMem2, 0, 0, SRCINVERT);

            DeleteDC(hdcMem);
            DeleteDC(hdcMem2);

            bitmap = hbm;
            mask = hbmMask;
            x = transx;
            y = transy;
            width = bmpwidth;
            height = bmpheight;
        }
        void drawSprite(HDC hdc, HDC hdcBuffer, int winx, int winy)
        {
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmMask = (HBITMAP)SelectObject(hdcMem, mask);

            BitBlt(hdcBuffer, winx, winy, width, height, hdcMem, 0, 0, SRCAND);

            SelectObject(hdcMem, bitmap);
            BitBlt(hdcBuffer, winx, winy, width, height, hdcMem, x, y, SRCPAINT);

            SelectObject(hdcMem, hbmMask);
            DeleteDC(hdcMem);
        }
};

#endif /* SPRITE_H */

