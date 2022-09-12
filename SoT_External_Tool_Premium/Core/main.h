#pragma once
#include <Windows.h>
#include <Process.h>
#include <dwmapi.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#pragma comment(lib, "dwmapi.lib")

//-> DX
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-> ImGUI
#include "../Overlay/imgui.h"
#include "../Overlay/imgui_impl_dx9.h"
#include "../Overlay/imgui_internal.h"

//-> GENERAL
#include "../Core/globals.h"
#include "../Others/user_settings.h"
#include "../Overlay/D3DRenderer.h"
#include "../Overlay/UIRenderer.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
void WINAPI UpdateSurface(HWND hWnd);
HWND WINAPI InitializeWindow(HINSTANCE hInst);
void UpdateWindowPosition();
