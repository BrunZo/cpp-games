#include <windows.h>
#include "resources.h"
#include "ship.h"
#include "rock.h"
#include "layer.h"

bool pressed = false;
    
Ship player;
Layer layer;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {   
            UINT ret = SetTimer(hwnd, IDT_TIMER, 1000/FPS, NULL);
            RECT rct;

            GetClientRect(hwnd, &rct);

            player.initShip(&rct);
            layer.initLayer(&rct);
            
            if(ret == 0)
                MessageBox(hwnd, "Could not set timer!", "Error", MB_OK | MB_ICONEXCLAMATION);
            
            if(player.sprite.bitmap == NULL || player.sprite.mask == NULL)
                MessageBox(hwnd, "Could not load ship bitmap!", "Error", MB_OK | MB_ICONEXCLAMATION);
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_TIMER:
        {
            RECT rct;

            GetClientRect(hwnd, &rct);
            
            player.updateShip(&rct);
            layer.updateLayer(&rct);
            
            if(GetKeyState(VK_SPACE) & 0x8000)
            {
                if(!pressed)
                {
                    pressed = true;
                    for(int i = 0; i < 256; i++)
                    {
                        if(layer.bullets[i].destroyed || &layer.bullets[i] == NULL)
                        {
                            Bullet bullet;
                            bullet.initBullet(&rct, player.x + player.width / 2 - 2, player.y + player.height / 2);
                            layer.bullets[i] = bullet;
                            break;
                        }
                    }
                }
            }
            else
                pressed = false;
            
            for(int i = 0; i < 256; i++)
                for(int j = 0; j < 256; j++)
                    if(layer.bullets[i].x < layer.rocks[j].x + layer.rocks[j].width && layer.bullets[i].x + layer.bullets[i].width > layer.rocks[j].x && layer.bullets[i].y < layer.rocks[j].y + layer.rocks[j].height && layer.bullets[i].y + layer.bullets[i].height > layer.rocks[j].y)
                    {
                        layer.bullets[i].destroyed = true;
                        layer.rocks[j].destroyed = true;
                    }
                        
            
            bool rockdestroy = true;
            for(Rock rock : layer.rocks)
                if(!rock.destroyed)
                    rockdestroy = false;
            if(rockdestroy)
                layer.initLayer(&rct);
            
            RECT* prc = &rct;
            HDC hdc = GetDC(hwnd);
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));

            player.drawShip(hdc, hdcBuffer);
            layer.drawLayer(hdc, hdcBuffer);
            
            BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);

            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteDC(hdcBuffer);
            DeleteObject(hbmBuffer);
            
            ReleaseDC(hwnd, hdc);
        }
        break;
        case WM_DESTROY:
            KillTimer(hwnd, IDT_TIMER);

            DeleteObject(player.sprite.bitmap);
            DeleteObject(player.sprite.mask);

            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Window";
    wc.hIconSm= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window registration failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "Window",
        "Arkanoid",
        WS_OVERLAPPEDWINDOW,
        X, Y, WIDTH, HEIGHT,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window creation failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}