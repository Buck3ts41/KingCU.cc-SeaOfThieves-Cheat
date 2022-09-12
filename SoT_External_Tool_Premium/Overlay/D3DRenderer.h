#pragma once
#include "../Drawings/drawing_manager_utilities.h"
#include "../Drawings//drawing_manager.h"
#include "../Core//process_manager.h"
#include "../Core/main.h"
#include <thread>
#include <vector>
#include <array>

struct sFont
{
	ID3DXFont* Font;
	std::string Name;
};

class cD3DRenderer
{
public:
	cD3DRenderer();
	~cD3DRenderer();

	IDirect3DDevice9Ex* pDevice;
	IDirect3D9Ex* pInstance;
	D3DPRESENT_PARAMETERS pParams;
	ID3DXLine* pLine;

	//-> UI Fonts
	ID3DXFont* pFontUILarge;
	ID3DXFont* pFontUIMedium;
	ID3DXFont* pFontUISmall;

	//-> Drawings Fonts
	ID3DXFont* pFontDrawingsLarge;
	ID3DXFont* pFontDrawingsMedium;
	ID3DXFont* pFontDrawingsSmall;

	//-> Render
	void D3DRender();
	BOOL D3DInitialize(HWND hWnd);
	void GetFPS(int* fps);

	//-> Drawing Handler
	void DrawStringOutline(const char* string, float x, float y, int r, int g, int b, int a, ID3DXFont* pFont);
	void Line(float X, float Y, float X2, float Y2, D3DCOLOR color);
	void GameBox(int boxType, int x, int y, int width, int height, D3DCOLOR color);
	void HealthBar(int health, float maxhealth, int x, int y, int width, int height);
	void OxygenInfo(float oxygenLevel);
	void Circle(int X, int Y, int radius, int numSides, D3DCOLOR color);
	void FilledBox(int x, int y, int width, int height, D3DCOLOR color);
	void FilledCircle(int x, int y, int radius, int points, D3DCOLOR color);
	void GradientRect(float x, float y, float width, float height, D3DCOLOR startCol, D3DCOLOR endCol, const char* orientation);
	void DrawStringGame(const char* string, float x, float y, int r, int g, int b, int a, bool centered, bool outline, ID3DXFont* pFont);
	void DrawStringGameOutline(const char* string, float x, float y, int r, int g, int b, int a, bool centered, ID3DXFont* pFont);
	void DrawGameObject(const char* objectName, float x, float y, float objectDistance, float colorR, float colorG, float ColorB, float colorA);
	void DrawGameObjectDebug(const char* objectName, float x, float y, float objectDistance, float colorR, float colorG, float ColorB, float colorA);
	void DrawGameShip(const char* objectName, float x, float y, float objectDistance, float colorR, float colorG, float colorB, float colorA, bool IsShipAllied);

	std::tuple<int, int, int, int> getTreasureColor(std::string treasureName);
	std::tuple<int, int, int, int> getShipColor(std::string shipType);
};

extern cD3DRenderer* D3DRenderer;
