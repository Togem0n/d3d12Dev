#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    switch (umessage)
    {
    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE)
        {
            PostQuitMessage(0);
            return 0;
        }
        else
        {
            return DefWindowProc(hwnd, umessage, wparam, lparam);
        }

    case WM_DESTROY:
        [[fallthrough]];
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, umessage, wparam, lparam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    std::wstring applicationName = L"D3D12 Tutorial";
    //Uint2 windowSize = { 1920, 1080 };
    int width = 1920;
    int height = 1080;
    HINSTANCE moduleHandle = GetModuleHandle(nullptr);

    WNDCLASSEX wc = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = moduleHandle;
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = applicationName.c_str();
    wc.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);

    HWND windowHandle = CreateWindowEx(WS_EX_APPWINDOW, applicationName.c_str(), applicationName.c_str(),
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_SIZEBOX,
        (GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2, width, height,
        nullptr, nullptr, moduleHandle, nullptr);

    ShowWindow(windowHandle, SW_SHOW);
    SetForegroundWindow(windowHandle);
    SetFocus(windowHandle);
    ShowCursor(true);

    bool shouldExit = false;
    while (!shouldExit)
    {
        MSG msg{ 0 };
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
        {
            shouldExit = true;
        }
    }

    DestroyWindow(windowHandle);
    windowHandle = nullptr;

    UnregisterClass(applicationName.c_str(), moduleHandle);
    moduleHandle = nullptr;

    return 0;
}