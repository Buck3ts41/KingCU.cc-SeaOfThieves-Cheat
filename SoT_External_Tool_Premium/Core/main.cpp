//-> GENERAL
#include "../Core/main.h"
#include "../Core/memory_manager.h"
#include "../Core/process_manager.h"

char OVERLAY_WINDOW_NAME[24] = "SOT_EXTERNAL_TOOL";
char GAME_WINDOW_NAME[32] = "Sea of Thieves";

DWORD procID;
MARGINS MARGIN = { 0, 0, GLOBAL_DEFINITION::rWidth, GLOBAL_DEFINITION::rHeight };

uintptr_t address = 0;

BOOL GAME_NOT_FOUND = FALSE;
BOOL OVERLAY_UNLOADING = FALSE;
BOOL OVERLAY_INITIALIZED = FALSE;

WNDCLASSEX wndClass;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 

	//-> SOT_EXTERNAL_TOOL begin
	if (!ProcessManager->setWindow("Sea of Thieves"))
	{
		MessageBoxA(NULL, "Failed To Find The Window", "Failed To Find The Window", MB_OK);
		return 1;
	}

	if (!ProcessManager->attachProcess("SoTGame.exe"))
	{
		MessageBoxA(NULL, "Failed To Find The Process", "Failed To Find The Process", MB_OK);
		return 1;
	}

	if (!GLOBAL_DEFINITION::baseModule)
	{
		GLOBAL_DEFINITION::baseModule = MemoryManager->baseModuleAddress("SoTGame.exe");
		GLOBAL_DEFINITION::baseModuleSize = MemoryManager->baseModuleSize("SoTGame.exe");
	}

	/*
	-> Initialize cheat
		Rewrite code to check if its XBox or Steam version
	*/

	if (!GLOBAL_DEFINITION::UWorld)
	{
		address = MemoryManager->FindSignature(GLOBAL_DEFINITION::baseModule, GLOBAL_DEFINITION::baseModuleSize,
			(BYTE*)("\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x88\x00\x00\x00\x00\x48\x85\xC9\x74\x06\x48\x8B\x49\x70"),
			(char*)"xxx????xxx????xxxxxxxxx");
	
		auto uworldoffset = MemoryManager->Read<int32_t>(address + 3);
		GLOBAL_DEFINITION::UWorld = address + uworldoffset + 7;
	}
	
	if (!GLOBAL_DEFINITION::GNames)
	{
		address = MemoryManager->FindSignature(GLOBAL_DEFINITION::baseModule, GLOBAL_DEFINITION::baseModuleSize,
			(BYTE*)"\x48\x8B\x1D\x00\x00\x00\x00\x48\x85\x00\x75\x3A", (char*)"xxx????xx?xx");
		auto gnamesoffset = MemoryManager->Read<int32_t>(address + 3);
		GLOBAL_DEFINITION::GNames = MemoryManager->Read<uintptr_t>(address + gnamesoffset + 7);
	}
	
	if (!GLOBAL_DEFINITION::GObjects)
	{
		address = MemoryManager->FindSignature(GLOBAL_DEFINITION::baseModule, GLOBAL_DEFINITION::baseModuleSize,
			(BYTE*)"\x48\x8B\x15\x00\x00\x00\x00\x3B\x42\x1C", (char*)"xxx????xxx");
		auto gobjectsoffset = MemoryManager->Read<int32_t>(address + 3);
		auto offset = gobjectsoffset + 7;
		GLOBAL_DEFINITION::GObjects = MemoryManager->Read<uintptr_t>(address + gobjectsoffset + 7);
	}

	if (!GLOBAL_DEFINITION::baseThreadID)
		GLOBAL_DEFINITION::baseThreadID = GetCurrentThreadId();
	//-> SOT_EXTERNAL_TOOL end

	//-> OVERLAY BASE
	///-> Create base threads
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)UpdateOverlay, nullptr, NULL, &ThreadsManager::hOverlayRefreshID);
	//CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)UpdateOverlaySlow, nullptr, NULL, 0);
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)UpdateWindowPosition, nullptr, NULL, &ThreadsManager::hOverlayPositionID);
	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(objectsDataShare), nullptr, NULL, &ThreadsManager::hDataShareID);
	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(objectsDebugDataShare), nullptr, NULL, &ThreadsManager::hDebugDataShareID);

	///-> Find game window
	while (GLOBAL_DEFINITION::rWidth < 640 && GLOBAL_DEFINITION::rHeight < 480)
	{
		GLOBAL_DEFINITION::tWnd = FindWindow(NULL, GAME_WINDOW_NAME);
		GLOBAL_DEFINITION::rWidth = ProcessManager->Size[0];
		GLOBAL_DEFINITION::rHeight = ProcessManager->Size[1];
	}

	///-> Get all access
	GetWindowThreadProcessId(GLOBAL_DEFINITION::tWnd, &GLOBAL_DEFINITION::baseProcessID);
	GLOBAL_DEFINITION::hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GLOBAL_DEFINITION::baseProcessID);

	///-> Initialize overlay
	GLOBAL_DEFINITION::hWnd = InitializeWindow((HINSTANCE)hInst);
	MSG uMessage;

	if (GLOBAL_DEFINITION::hWnd == NULL) { ExitProcess(1); }
	
	ShowWindow(GLOBAL_DEFINITION::hWnd, SW_SHOW);

	OVERLAY_INITIALIZED = TRUE;

	while (!OVERLAY_UNLOADING)
	{
		// overlay position
		ProcessManager->getSize();

		GLOBAL_DEFINITION::PMrHeight = ProcessManager->Size[0];
		GLOBAL_DEFINITION::PMrWidth = ProcessManager->Size[1];

		if (PeekMessage(&uMessage, GLOBAL_DEFINITION::hWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&uMessage);
			TranslateMessage(&uMessage);
		}

		if (uMessage.message == WM_QUIT)
			break;

		if (OVERLAY_UNLOADING)
		{
			HWND hMsg = FindWindow(NULL, "SOT_EXTERNAL_TOOL Error");

			if (hMsg)
			{
				std::this_thread::sleep_for(std::chrono::seconds(2));
				SendMessageA(hMsg, WM_CLOSE, 0, 0);
			}
		}
	}

	///-> Cleanup overlay
	DestroyWindow(GLOBAL_DEFINITION::hWnd);
	UnregisterClass(OVERLAY_WINDOW_NAME, (HINSTANCE)hInst);
	FreeLibraryAndExitThread((HMODULE)hInst, 0);
	return 0;
}

HWND WINAPI InitializeWindow(HINSTANCE hInst)
{
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	wndClass.lpfnWndProc = WindowProcess;
	wndClass.hInstance = hInst;
	wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.lpszClassName = OVERLAY_WINDOW_NAME;
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wndClass.lpszMenuName = OVERLAY_WINDOW_NAME;

	if (!RegisterClassEx(&wndClass))
		ExitProcess(1);

	GLOBAL_DEFINITION::hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED, OVERLAY_WINDOW_NAME, OVERLAY_WINDOW_NAME, WS_POPUP, ProcessManager->Position[0], ProcessManager->Position[1], ProcessManager->Size[0], ProcessManager->Size[1], nullptr, nullptr, GetModuleHandle(0), nullptr);
	SetLayeredWindowAttributes(GLOBAL_DEFINITION::hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
	MARGINS Margin = { -1, -1, ProcessManager->Size[0], ProcessManager->Size[1] };
	DwmExtendFrameIntoClientArea(GLOBAL_DEFINITION::hWnd, &Margin);

	if (!D3DRenderer->D3DInitialize(GLOBAL_DEFINITION::hWnd))
		printf("Renderer Initialize error occured!");

	return GLOBAL_DEFINITION::hWnd;
}

void UpdateWindowPosition()
{
	while (!OVERLAY_UNLOADING)
	{
		UpdateSurface(GLOBAL_DEFINITION::hWnd);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	return;
}

void WINAPI UpdateSurface(HWND hWnd)
{
	RECT wSize;
	HWND tWnd;

	tWnd = FindWindow(NULL, GAME_WINDOW_NAME);
	if (!tWnd && hWnd && !OVERLAY_UNLOADING && !GAME_NOT_FOUND)
	{
		ShowWindow(hWnd, SW_HIDE);
		MessageBox(NULL, "Game window not found, the overlay will be closed! ", "SOT_EXTERNAL_TOOL Error", MB_OK | MB_ICONERROR);
		OVERLAY_UNLOADING = TRUE;
	}

	if (tWnd)
	{
		GetWindowRect(tWnd, &wSize);
		GLOBAL_DEFINITION::rWidth = wSize.right - wSize.left;
		GLOBAL_DEFINITION::rHeight = wSize.bottom - wSize.top;

		DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);
		if (dwStyle & WS_BORDER)
			wSize.top += 23; GLOBAL_DEFINITION::rHeight -= 23;

		if (hWnd)
			MoveWindow(hWnd, wSize.left, wSize.top, GLOBAL_DEFINITION::rWidth, GLOBAL_DEFINITION::rHeight, true);
	}
	return;
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		case WM_CREATE:
			break;

		case WM_PAINT:
			DwmExtendFrameIntoClientArea(hWnd, &MARGIN);
			D3DRenderer->D3DRender();
			break;

		case WM_DESTROY:
			ImGui::Shutdown();
			DeleteObject(wndClass.hbrBackground);
			DestroyCursor(wndClass.hCursor);
			DestroyIcon(wndClass.hIcon);
			DestroyIcon(wndClass.hIconSm);

			PostQuitMessage(1);
			break;

		default:
			ImGui_ImplWin32_WndProcHandler(hWnd, uMessage, wParam, lParam);
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
			break;
	}
	return 0;
}
