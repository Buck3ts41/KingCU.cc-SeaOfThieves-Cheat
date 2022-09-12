#include "../Overlay/D3DRenderer.h"

cD3DRenderer* D3DRenderer = new cD3DRenderer();

cD3DRenderer::cD3DRenderer()
{
}

cD3DRenderer::~cD3DRenderer()
{
}

float flCurTick, flOldTick;
int iTempFPS, iRenderFPS;

BOOL cD3DRenderer::D3DInitialize(HWND hWnd)
{
	Direct3DCreate9Ex(D3D_SDK_VERSION, &pInstance);

	ZeroMemory(&D3DRenderer->pDevice, sizeof(D3DRenderer->pDevice));

	pParams.Windowed = TRUE;
	pParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	pParams.BackBufferHeight = GLOBAL_DEFINITION::rHeight;
	pParams.BackBufferWidth = GLOBAL_DEFINITION::rWidth;
	pParams.BackBufferCount = 2;
	pParams.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	pParams.MultiSampleQuality = DEFAULT_QUALITY;
	pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pParams.EnableAutoDepthStencil = TRUE;
	pParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	pParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(pInstance->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pParams, nullptr, &pDevice)))
		printf("pDevice startup error");


	if (ProcessManager->Size[0] > 2400) // big screens fix
	{
		if ((pFontDrawingsLarge == nullptr || pFontDrawingsMedium == nullptr || pFontDrawingsSmall == nullptr || pFontUILarge == nullptr || pFontUIMedium == nullptr || pFontUISmall == nullptr) && pDevice != nullptr)
		{
			D3DXCreateFont(pDevice, 28, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontDrawingsLarge);
			D3DXCreateFont(pDevice, 24, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontDrawingsMedium);
			D3DXCreateFont(pDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontDrawingsSmall);

			D3DXCreateFont(pDevice, 36, 0, FW_REGULAR, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontUILarge);
			D3DXCreateFont(pDevice, 28, 0, FW_REGULAR, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontUIMedium);
			D3DXCreateFont(pDevice, 20, 0, FW_REGULAR, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontUISmall);
		}
	} else {
		if ((pFontDrawingsLarge == nullptr || pFontDrawingsMedium == nullptr || pFontDrawingsSmall == nullptr || pFontUILarge == nullptr || pFontUIMedium == nullptr || pFontUISmall == nullptr) && pDevice != nullptr)
		{
			D3DXCreateFont(pDevice, 15, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontDrawingsLarge);
			D3DXCreateFont(pDevice, 13, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontDrawingsMedium);
			D3DXCreateFont(pDevice, 11, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontDrawingsSmall);

			D3DXCreateFont(pDevice, 24, 0, FW_REGULAR, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontUILarge);
			D3DXCreateFont(pDevice, 18, 0, FW_REGULAR, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontUIMedium);
			D3DXCreateFont(pDevice, 12, 0, FW_REGULAR, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Bahnschrift", &pFontUISmall);
		}
	}

	D3DXCreateLine(pDevice, &pLine);

	//-> ImGUI
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 14);
	io.FontGlobalScale = 0.9f;
	ImFontConfig fontCfg = ImFontConfig();
	io.DeltaTime = 1.0f / 60.0f;

	fontCfg.RasterizerFlags = 0x01;
	fontCfg.OversampleH = fontCfg.OversampleV = 1;
	fontCfg.PixelSnapH = true;

	ImGui_ImplDX9_Init(hWnd, pDevice);

	return TRUE;
}

void cD3DRenderer::D3DRender()
{
	pParams.BackBufferWidth = GLOBAL_DEFINITION::rWidth;
	pParams.BackBufferHeight = GLOBAL_DEFINITION::rHeight;
	pDevice->Reset(&pParams);

	pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	pDevice->BeginScene();

	if (GLOBAL_DEFINITION::tWnd == GetForegroundWindow() || GetActiveWindow() == GetForegroundWindow())
	{
		//-> OVERLAY RENDERING
		GetFPS(&GLOBAL_DEFINITION::FramesPerSecond);
		UIRenderer->DrawInfo(pDevice);

		//-> ESP RENDERING
		DrawingManager->objectsDataDraw();

		//-> DEBUG MODE ESP RENDERING
		if (SETTINGS::MENU::DebugMode)
			DrawingManager->objectsDebugDataDraw();

		//-> UTILITIES RENDERING
		DrawingManagerUtilities->DrawUtilities();

		//-> MENU RENDERING
		if (GLOBAL_DEFINITION::MenuShown)
			UIRenderer->DrawMenu(pDevice);
	}

	pDevice->EndScene();
	pDevice->PresentEx(0, 0, 0, 0, 0);
}

void cD3DRenderer::GetFPS(int* fps)
{
	flCurTick = clock() * 0.001f;
	iTempFPS++;

	if ((flCurTick - flOldTick) > 1.0f)
	{
		iRenderFPS = iTempFPS;

		iTempFPS = 0;
		flOldTick = flCurTick;
	}

	*(int*)fps = iRenderFPS;
}
