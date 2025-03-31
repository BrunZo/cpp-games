#include <windows.h>
#include "resources.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "level.h"
#include <string> 

Ball ball;
Paddle player;
Level level;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {   
            UINT ret = SetTimer(hwnd, IDT_TIMER, 1000/FPS, NULL);
            RECT rct;

            GetClientRect(hwnd, &rct);

            ball.initBall(&rct);
            player.initPaddle(&rct);
            level.initLevel(&rct, 1);
            
            
            if(ret == 0)
                MessageBox(hwnd, "Could not set timer!", "Error", MB_OK | MB_ICONEXCLAMATION);
            
            if(ball.sprite.bitmap == NULL || ball.sprite.mask == NULL)
                MessageBox(hwnd, "Could not load ball bitmap!", "Error", MB_OK | MB_ICONEXCLAMATION);
            
            if(player.sprite.bitmap == NULL || player.sprite.mask == NULL)
                MessageBox(hwnd, "Could not load ball bitmap!", "Error", MB_OK | MB_ICONEXCLAMATION);
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_TIMER:
        {
            RECT rct;

            GetClientRect(hwnd, &rct);

            ball.updateBall(&rct);
            player.updatePaddle(&rct);
            
            if(ball.x < player.x + player.width && ball.x + ball.width > player.x && ball.y + ball.height < player.y + player.height && ball.y + ball.height > player.y)
            {
                ball.dy = -ball.vel;
            }
            
            bool destroyed = true;
                
            for(int i = 0; i < level.count; i++)
            {
                Brick brick = level.bricks[i];
                
                if(!brick.destroyed)
                {
                    destroyed = false;
                    
                    if(ball.x - 3 < brick.x + brick.width && ball.x > brick.x && ball.y < brick.y + brick.height && ball.y + ball.height > brick.y)
                    {
                        ball.dx = ball.vel;
                        level.bricks[i].destroyed = true;
                    }
                    if(ball.x + ball.width < brick.x + brick.width && ball.x + ball.width + 3 > brick.x && ball.y < brick.y + brick.height && ball.y + ball.height > brick.y)
                    {
                        ball.dx = -ball.vel;
                        level.bricks[i].destroyed = true;
                    }
                    if(ball.x < brick.x + brick.width && ball.x + ball.width > brick.x && ball.y - 3 < brick.y + brick.height && ball.y > brick.y)
                    {
                        ball.dy = ball.vel;
                        level.bricks[i].destroyed = true;
                    }
                    if(ball.x < brick.x + brick.width && ball.x + ball.width > brick.x && ball.y + ball.width + 3 > brick.y && ball.y + ball.width < brick.y)
                    {
                        ball.dy = -ball.vel;
                        level.bricks[i].destroyed = true;
                    }
                }
            }
            
            if(destroyed)
            {
               level.initLevel(&rct, level.count+1);
            }
            
            RECT* prc = &rct;
            HDC hdc = GetDC(hwnd);
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            
            ball.drawBall(hdc, hdcBuffer);
            player.drawPaddle(hdc, hdcBuffer);
            
            for(int i = 0; i < level.count; i++)
            {
                if(!level.bricks[i].destroyed)
                {
                    level.bricks[i].drawBrick(hdc, hdcBuffer);
                }
            }
            
            //level.drawLevel(hdc, hdcBuffer);
            
            BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);

            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteDC(hdcBuffer);
            DeleteObject(hbmBuffer);
            
            ReleaseDC(hwnd, hdc);
        }
        break;
        case WM_DESTROY:
            KillTimer(hwnd, IDT_TIMER);

            DeleteObject(ball.sprite.bitmap);
            DeleteObject(ball.sprite.mask);
            DeleteObject(player.sprite.bitmap);
            DeleteObject(player.sprite.mask);
            
            for(int i = 0; i < level.count; i++)
            {
                DeleteObject(level.bricks[i].sprite.bitmap);
                DeleteObject(level.bricks[i].sprite.mask);
            }

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