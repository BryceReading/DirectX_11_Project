#include "WindowContainer.h"

bool RenderWin::initialize(WindowContainer* pwindowContainer, HINSTANCE hInstance, string window_Title, string window_Class, int width, int height)
{
    this->hInstance = hInstance;
    this->width = width;
    this->height = height;
    this->window_Title = window_Title;
    this->window_Title_Wide = Converter::stringToWide(this->window_Title);
    this->window_Class = window_Class;
    this->window_Class_wide = Converter::stringToWide(this->window_Class);

    this->registerWindowClass();

    int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - this->width / 2;
    int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - this->height / 2;

    RECT wr; // Win Rect
    wr.left = centerScreenX;
    wr.top = centerScreenY;
    wr.right = wr.left + this->width;
    wr.bottom = wr.top + this->height;

    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    this->handle = CreateWindowEx(0,
        this->window_Class_wide.c_str(),
        this->window_Title_Wide.c_str(),
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        wr.left, // Window X pos
        wr.top, // Window Y pos
        wr.right - wr.left,
        wr.bottom - wr.top,
        NULL, // Handle to window parent, since first window it has no parents
        NULL, // Handle to menu or child window identifier 
        this->hInstance,
        pwindowContainer);

    if (this->handle == NULL)
    {
        ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for Window: " + this->window_Title);
        return false;
    }

    // Show the window on the screen 
    ShowWindow(this->handle, SW_SHOW);
    SetForegroundWindow(this->handle);
    SetFocus(this->handle);

    return true;
}

bool RenderWin::processMsg()
{
    // Handle the windows msgs
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Check if window was closed
    if (msg.message == WM_NULL)
    {
        if (!IsWindow(this->handle))
        {
            this->handle = NULL;
            UnregisterClass(this->window_Class_wide.c_str(), this->hInstance);
            return false;
        }
    }
    return true;
}

HWND RenderWin::GetHWND() const
{
    return this->handle;
}

RenderWin::~RenderWin()
{
    if (this->handle != NULL)
    {
        UnregisterClass(this->window_Class_wide.c_str(), this->hInstance);
        DestroyWindow(handle);
    }
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)
{
    switch (uMsg)
    {
        // All other messages
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    default:
    {
        // Retrieve ptr to window class
        WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        // Forward message to window class handler
        return pWindow->WindowProc(hwnd, uMsg, wParam, lparam);
    }
    }
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_NCCREATE:
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
        if (pWindow == nullptr)
        {
            ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
            exit(-1);
        }
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));        
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
        return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void RenderWin::registerWindowClass()
{
    WNDCLASSEX wc; // the window class / extended vertion
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = HandleMessageSetup; // pointer to window procsesser function 
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = this->hInstance;
    wc.hIcon = NULL;
    wc.hIconSm = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = this->window_Class_wide.c_str();
    wc.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);
}
