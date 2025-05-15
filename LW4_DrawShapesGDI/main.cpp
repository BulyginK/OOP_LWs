#include <windows.h>
#include <vector>
#include <cstdint>
#include "Canvas.h"
#include "ShapeMenu.h"

// Главная оконная процедура
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    CShapeMenu* menu = reinterpret_cast<CShapeMenu*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    switch (uMsg) {
    case WM_CREATE: {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreate->lpCreateParams));
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (menu) 
        {
            CCanvas drawer(hdc);
            menu->DrawAllShapes(drawer);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) 
{
    CShapeMenu menu;
    std::string command;
    try {
        while (std::getline(std::cin, command)) 
        {
            menu.ReadShape(command);
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }


    // Регистрируем класс окна
    const wchar_t CLASS_NAME[] = L"GDI Canvas Window";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Создаем окно
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"GDI Canvas Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr,
        nullptr,
        hInstance,
        &menu
    );

    if (hwnd == nullptr) 
    {
        return 0;
    }

    // Показываем окно
    ShowWindow(hwnd, nCmdShow);

    // Цикл сообщений
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}