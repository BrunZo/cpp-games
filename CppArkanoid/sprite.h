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
        
        void loadSpriteBitmap(UINT src)
        {
            bitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(src));
        }
        void loadSpriteMask(COLORREF crTransparent)
        {
            HDC hdcMem, hdcMem2;
            HBITMAP hbmMask;
            BITMAP bm;

            GetObject(bitmap, sizeof(BITMAP), &bm);
            hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

            hdcMem = CreateCompatibleDC(0);
            hdcMem2 = CreateCompatibleDC(0);

            SelectObject(hdcMem, bitmap);
            SelectObject(hdcMem2, hbmMask);

            SetBkColor(hdcMem, crTransparent);

            BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

            BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

            DeleteDC(hdcMem);
            DeleteDC(hdcMem2);

            mask = hbmMask;
        }
        void drawSprite(HDC hdc, HDC hdcBuffer, UINT x, UINT y, UINT width, UINT height)
        {
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmMask = (HBITMAP)SelectObject(hdcMem, mask);

            BitBlt(hdcBuffer, x, y, width, height, hdcMem, 0, 0, SRCAND);

            SelectObject(hdcMem, bitmap);
            BitBlt(hdcBuffer, x, y, width, height, hdcMem, 0, 0, SRCPAINT);

            SelectObject(hdcMem, hbmMask);
            DeleteDC(hdcMem);
        }
};

#endif /* SPRITE_H */

