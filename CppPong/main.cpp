#include <windows.h>
#include "resources.h"
#include "ball.h"
#include "paddle.h"

Ball ball;
Paddle player1;
Paddle player2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {   
            UINT ret = SetTimer(hwnd, IDT_TIMER, 1000/FPS, NULL);
            RECT rcClient;

            GetClientRect(hwnd, &rcClient);

            ball.initBall(&rcClient);
            player1.initPaddle(&rcClient, LEFT);
            player2.initPaddle(&rcClient, RIGHT);
            
            if(ret == 0)
                MessageBox(hwnd, "Could not set timer!", "Error", MB_OK | MB_ICONEXCLAMATION);
            
            if(ball.sprite.bitmap == NULL || ball.sprite.mask == NULL)
                MessageBox(hwnd, "Could not load ball bitmap!", "Error", MB_OK | MB_ICONEXCLAMATION);
            
            if(player1.sprite.bitmap == NULL || player1.sprite.mask == NULL || player2.sprite.bitmap == NULL || player2.sprite.mask == NULL)
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
            player1.updatePaddle(&rct);
            player2.updatePaddle(&rct);
            
            if(ball.dx > 0)
            {
                if(player2.y + player2.height / 2 < ball.y + ball.height / 2)
                {
                    player2.y += player2.vel;
                }
                else
                {
                    player2.y -= player2.vel;
                }
            }
            
            if(ball.x < player1.x + player1.width && ball.y < player1.y + player1.height && ball.y + ball.height > player1.y)
            {
                ball.dx = ball.vel;
            }
            else if(ball.x + ball.width > player2.x && ball.y < player2.y + player2.height && ball.y + ball.height > player2.y)
            {
                ball.dx = -ball.vel;
            }
            
            RECT* prc = &rct;
            HDC hdc = GetDC(hwnd);
            HDC hdcBuffer = CreateCompatibleDC(hdc);
            HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
            HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

            FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            
            ball.drawBall(hdc, hdcBuffer);
            player1.drawPaddle(hdc, hdcBuffer);
            player2.drawPaddle(hdc, hdcBuffer);
            
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
        "Pong",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
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