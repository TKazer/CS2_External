#include "OS-ImGui_External.h"
#include "..\MenuConfig.hpp"
/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui_External.cpp
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/6/18	11:21
****************************************************/

// D3D11 Device
namespace OSImGui
{
#ifdef _CONSOLE
    bool D3DDevice::CreateDeviceD3D(HWND hWnd)
    {
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        HRESULT res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
        if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
            res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_WARP, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
        if (res != S_OK)
            return false;

        CreateRenderTarget();
        return true;
    }

    void D3DDevice::CleanupDeviceD3D()
    {
        CleanupRenderTarget();
        if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
        if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
        if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    }

    void D3DDevice::CreateRenderTarget()
    {
        ID3D11Texture2D* pBackBuffer;
        g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        if (pBackBuffer == nullptr)
            return;
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
        pBackBuffer->Release();
    }

    void D3DDevice::CleanupRenderTarget()
    {
        if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
    }
#endif
}

// OSImGui External
namespace OSImGui
{

    LRESULT WINAPI WndProc_External(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void OSImGui_External::NewWindow(std::string WindowName, Vec2 WindowSize, std::function<void()> CallBack)
    {
        if (!CallBack)
            throw OSException("CallBack is empty");
        if (WindowName.empty())
            Window.Name = "Window";

        Window.Name = WindowName;
        Window.wName = StringToWstring(Window.Name);
        Window.ClassName = "WindowClass";
        Window.wClassName = StringToWstring(Window.ClassName);
        Window.Size = WindowSize;

        Type = NEW;
        CallBackFn = CallBack;

        if (!CreateMyWindow())
            throw OSException("CreateMyWindow() call failed");

        try {
            InitImGui(g_Device.g_pd3dDevice, g_Device.g_pd3dDeviceContext);
        }
        catch (OSException& e)
        {
            throw e;
        }

        MainLoop();
    }

    void  OSImGui_External::AttachAnotherWindow(std::string DestWindowName, std::string DestWindowClassName, std::function<void()> CallBack)
    {
        if (!CallBack)
            throw OSException("CallBack is empty");
        if (DestWindowName.empty() && DestWindowClassName.empty())
            throw OSException("DestWindowName and DestWindowClassName are empty");

        Window.Name = "Window";
        Window.wName = StringToWstring(Window.Name);
        Window.ClassName = "WindowClass";
        Window.wClassName = StringToWstring(Window.ClassName);
        Window.BgColor = ImColor(0, 0, 0, 0);

        DestWindow.hWnd = FindWindowA(
            (DestWindowClassName.empty() ? NULL : DestWindowClassName.c_str()),
            (DestWindowName.empty() ? NULL : DestWindowName.c_str()));
        if (DestWindow.hWnd == NULL)
            throw OSException("DestWindow isn't exist");
        DestWindow.Name = DestWindowName;
        DestWindow.ClassName = DestWindowClassName;

        Type = ATTACH;
        CallBackFn = CallBack;

        if (!CreateMyWindow())
            throw OSException("CreateMyWindow() call failed");

        try {
            InitImGui(g_Device.g_pd3dDevice,g_Device.g_pd3dDeviceContext);
        }
        catch (OSException& e)
        {
            throw e;
        }

        MainLoop();
    }

    bool OSImGui_External::PeekEndMessage()
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                return true;
        }
        return false;
    }

    void OSImGui_External::MainLoop()
    {
        while (!EndFlag)
        {
            if (PeekEndMessage())
                break;
            if (Type == ATTACH)
            {
                if (!UpdateWindowData())
                    break;
            }
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            this->CallBackFn();

            ImGui::Render();
            const float clear_color_with_alpha[4] = { Window.BgColor.Value.x, Window.BgColor.Value.y , Window.BgColor.Value.z, Window.BgColor.Value.w };
            g_Device.g_pd3dDeviceContext->OMSetRenderTargets(1, &g_Device.g_mainRenderTargetView, NULL);
            g_Device.g_pd3dDeviceContext->ClearRenderTargetView(g_Device.g_mainRenderTargetView, clear_color_with_alpha);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            g_Device.g_pSwapChain->Present(1, 0); // Present with vs
        }
        CleanImGui();
    }

    bool OSImGui_External::CreateMyWindow()
    {
        WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc_External, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, Window.wClassName.c_str(), NULL };
        RegisterClassExW(&wc);
        if (Type == ATTACH)
        {
			Window.hWnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW, Window.wClassName.c_str(), Window.wName.c_str(), WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, NULL, NULL, GetModuleHandle(NULL), NULL);
			SetLayeredWindowAttributes(Window.hWnd, 0, 255, LWA_ALPHA);
        }
        else
        {
            Window.hWnd = CreateWindowW(Window.wClassName.c_str(), Window.wName.c_str(), WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, (int)Window.Pos.x, (int)Window.Pos.y, (int)Window.Size.x, (int)Window.Size.y, NULL, NULL, wc.hInstance, NULL);
        }
        Window.hInstance = wc.hInstance;

        if (!g_Device.CreateDeviceD3D(Window.hWnd))
        {
            g_Device.CleanupDeviceD3D();
            UnregisterClassW(wc.lpszClassName, wc.hInstance);
            return false;
        }

        ShowWindow(Window.hWnd, SW_SHOWDEFAULT);
        UpdateWindow(Window.hWnd);

        return Window.hWnd != NULL;
    }

    bool OSImGui_External::UpdateWindowData()
    {
        POINT Point{};
        RECT Rect{};

        DestWindow.hWnd = FindWindowA(
            (DestWindow.ClassName.empty() ? NULL : DestWindow.ClassName.c_str()),
            (DestWindow.Name.empty() ? NULL : DestWindow.Name.c_str()));
        if (DestWindow.hWnd == NULL)
            return false;

        GetClientRect(DestWindow.hWnd, &Rect);
        ClientToScreen(DestWindow.hWnd, &Point);

        Window.Pos = DestWindow.Pos = Vec2(static_cast<float>(Point.x), static_cast<float>(Point.y));
        Window.Size = DestWindow.Size = Vec2(static_cast<float>(Rect.right), static_cast<float>(Rect.bottom));

        SetWindowPos(Window.hWnd, HWND_TOPMOST, (int)Window.Pos.x, (int)Window.Pos.y, (int)Window.Size.x, (int)Window.Size.y, SWP_SHOWWINDOW);

        // ¿ØÖÆ´°¿Ú×´Ì¬ÇÐ»»
        POINT MousePos;
        GetCursorPos(&MousePos);
        ScreenToClient(Window.hWnd, &MousePos);
        ImGui::GetIO().MousePos.x = static_cast<float>(MousePos.x);
        ImGui::GetIO().MousePos.y = static_cast<float>(MousePos.y);

        if(MenuConfig::OBSBypass)
            SetWindowDisplayAffinity(Window.hWnd, WDA_EXCLUDEFROMCAPTURE);
        else
            SetWindowDisplayAffinity(Window.hWnd, WDA_NONE);

        if (ImGui::GetIO().WantCaptureMouse)
            SetWindowLong(Window.hWnd, GWL_EXSTYLE, GetWindowLong(Window.hWnd, GWL_EXSTYLE) & (~WS_EX_LAYERED));
        else
            SetWindowLong(Window.hWnd, GWL_EXSTYLE, GetWindowLong(Window.hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        return true;
    }

    LRESULT WINAPI WndProc_External(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_CREATE:
        {
            MARGINS     Margin = { -1 };
            DwmExtendFrameIntoClientArea(hWnd, &Margin);
            break;
        }
        case WM_SIZE:
            if (g_Device.g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
            {
                g_Device.CleanupRenderTarget();
                g_Device.g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                g_Device.CreateRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU)
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        }
        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }

}