/* 
 * File:   main.cpp
 * Author: Bruno
 *
 * Created on 21 de febrero de 2018, 21:15
 */

#include <windows.h>
#include <ctime>
#include "resources.h"
#include "layer.h"

Layer layer;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {   
            RECT rct;
            
            GetClientRect(hwnd, &rct);
            SetTimer(hwnd, IDT_TIMER, 1000/FPS, NULL);
            
            srand(time(NULL));
            layer.init(&rct);
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_TIMER:
        {
            RECT rct;
            HDC hdc = GetDC(hwnd);

            GetClientRect(hwnd, &rct);
            
            layer.update(&rct);
            layer.draw(&rct, hdc);
            
            ReleaseDC(hwnd, hdc);
        }
        break;
        case WM_DESTROY:
            KillTimer(hwnd, IDT_TIMER);
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
    wc.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window registration failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "Window",
        "Pacman",
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