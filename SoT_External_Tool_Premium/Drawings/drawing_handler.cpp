#include "../Drawings/drawing_handler.h"

void cD3DRenderer::DrawStringOutline(const char* string, float x, float y, int r, int g, int b, int a, ID3DXFont* pFont)
{
	RECT rPosition;
	
	rPosition.left = x + 1.0f;
	rPosition.top = y;
	
	pFont->DrawTextA(NULL, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	rPosition.left = x - 1.0f;
	rPosition.top = y;
	
	pFont->DrawTextA(NULL, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	rPosition.left = x;
	rPosition.top = y + 1.0f;
	
	pFont->DrawTextA(NULL, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	rPosition.left = x;
	rPosition.top = y - 1.0f;
	
	pFont->DrawTextA(NULL, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	rPosition.left = x;
	rPosition.top = y;
	
	pFont->DrawTextA(NULL, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(r, g, b, a));
}

struct D3DTLVERTEX
{
	float fX, fY, fZ, fRHW;
	D3DCOLOR Color;
	float fU, fV;
};

D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v =
	{
		X, Y, Z, RHW, color, U, V
	};

	return v;
}

void cD3DRenderer::Line(float x, float y, float x2, float y2, D3DCOLOR color)
{
	D3DTLVERTEX Line[2];

	Line[0] = CreateD3DTLVERTEX(x, y, 0.0f, 0.0f, color, 0.0f, 0.0f);
	Line[1] = CreateD3DTLVERTEX(x2, y2, 0.0f, 0.0f, color, 0.0f, 0.0f);

	D3DRenderer->pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	D3DRenderer->pDevice->SetTexture(0, NULL);
	D3DRenderer->pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, &Line[0], sizeof(Line[0]));
}

void cD3DRenderer::GameBox(int boxType, int x, int y, int width, int height, D3DCOLOR color)
{
	D3DCOLOR whiteOutline = D3DCOLOR_XRGB((int)(0.85f * 255), (int)(0.85f * 255), (int)(0.85f * 255), (int)(0.85f * 255));
	if (boxType == 1) //-> 2D Full
	{
		D3DRenderer->Line(x, y, x + width, y, color);
		D3DRenderer->Line(x + width, y, x + width, y + height, color);
		D3DRenderer->Line(x, y, x, y + height, color);
		D3DRenderer->Line(x, y + height, x + width, y + height, color);
	}
	else if (boxType == 2) //-> 2D Full - BLACK OUTLINE
	{
		D3DRenderer->FilledBox(x - 2, y - 2, 4, height + 2, (1, 1, 1));
		D3DRenderer->FilledBox(x - 2, y - 2, width + 2, 4, (1, 1, 1));
		D3DRenderer->FilledBox(x + width - 2, y - 2, 4, height + 2, (1, 1, 1));
		D3DRenderer->FilledBox(x - 2, y + height - 2, width + 2, 4, (1, 1, 1));
		D3DRenderer->Line(x, y, x + width, y, color);
		D3DRenderer->Line(x + width, y, x + width, y + height, color);
		D3DRenderer->Line(x, y, x, y + height, color);
		D3DRenderer->Line(x, y + height, x + width, y + height, color);
	}
	else if (boxType == 3) //-> 2D Full - WHITE OUTLINE
	{
		D3DRenderer->FilledBox(x - 2, y - 2, 4, height + 2, whiteOutline);
		D3DRenderer->FilledBox(x - 2, y - 2, width + 2, 4, whiteOutline);
		D3DRenderer->FilledBox(x + width - 2, y - 2, 4, height + 2, whiteOutline);
		D3DRenderer->FilledBox(x - 2, y + height - 2, width + 2, 4, whiteOutline);
		D3DRenderer->Line(x, y, x + width, y, color);
		D3DRenderer->Line(x + width, y, x + width, y + height, color);
		D3DRenderer->Line(x, y, x, y + height, color);
		D3DRenderer->Line(x, y + height, x + width, y + height, color);
	}
	else if (boxType == 4) // 2D-> Corners
	{
		D3DRenderer->Line(x, y, x + (width / 4), y, color);
		D3DRenderer->Line(x, y, x, y + (height / 4), color);
		D3DRenderer->Line(x, y + height, x + (width / 4), y + height, color);
		D3DRenderer->Line(x, y + height, x, (y + height) - (height / 4), color);
		D3DRenderer->Line(x + width, y, (x + width) - (width / 4), y, color);
		D3DRenderer->Line(x + width, y, x + width, y + (height / 4), color);
		D3DRenderer->Line(x + width, y + height, (x + width) - (width / 4), y + height, color);
		D3DRenderer->Line(x + width, y + height, x + width, (y + height) - (height / 4), color);
	}
	else if (boxType == 5) //-> 2D Corners - BLACK OUTLINE
	{
		D3DRenderer->FilledBox(x - 2, y - 2, (width / 8) * 2 + 2, 4, (1, 1, 1));
		D3DRenderer->FilledBox(x - 2, y - 2, 4, (height / 8) * 2 + 2, (1, 1, 1));
		D3DRenderer->FilledBox(x - 2, y + height - 2, (width / 8) * 2 + 2, 4, (1, 1, 1));
		D3DRenderer->FilledBox(x - 2, (y + height) - (height / 4) - 2, 4, (height / 8) * 2 + 2, (1, 1, 1));
		D3DRenderer->FilledBox((x + width) - (width / 4) - 2, y - 2, (width / 8) * 2 + 2, 4, (1, 1, 1));
		D3DRenderer->FilledBox(x + width - 2, y - 2, 4, (height / 8) * 2 + 2, (1, 1, 1));
		D3DRenderer->FilledBox((x + width) - (width / 4) - 2, y + height - 2, (width / 8) * 2 + 2, 4, (1, 1, 1));
		D3DRenderer->FilledBox(x + width - 2, (y + height) - (height / 4) - 2, 4, (height / 8) * 2 + 2, (1, 1, 1));

		D3DRenderer->Line(x, y, x + (width / 4), y, color);
		D3DRenderer->Line(x, y, x, y + (height / 4), color);
		D3DRenderer->Line(x, y + height, x + (width / 4), y + height, color);
		D3DRenderer->Line(x, y + height, x, (y + height) - (height / 4), color);
		D3DRenderer->Line(x + width, y, (x + width) - (width / 4), y, color);
		D3DRenderer->Line(x + width, y, x + width, y + (height / 4), color);
		D3DRenderer->Line(x + width, y + height, (x + width) - (width / 4), y + height, color);
		D3DRenderer->Line(x + width, y + height, x + width, (y + height) - (height / 4), color);
	}
	else if (boxType == 6) //-> 2D Corners - WHITE OUTLINE
	{
		D3DRenderer->FilledBox(x - 2, y - 2, (width / 8) * 2 + 2, 4, whiteOutline);
		D3DRenderer->FilledBox(x - 2, y - 2, 4, (height / 8) * 2 + 2, whiteOutline);
		D3DRenderer->FilledBox(x - 2, y + height - 2, (width / 8) * 2 + 2, 4, whiteOutline);
		D3DRenderer->FilledBox(x - 2, (y + height) - (height / 4) - 2, 4, (height / 8) * 2 + 2, whiteOutline);
		D3DRenderer->FilledBox((x + width) - (width / 4) - 2, y - 2, (width / 8) * 2 + 2, 4, whiteOutline);
		D3DRenderer->FilledBox(x + width - 2, y - 2, 4, (height / 8) * 2 + 2, whiteOutline);
		D3DRenderer->FilledBox((x + width) - (width / 4) - 2, y + height - 2, (width / 8) * 2 + 2, 4, whiteOutline);
		D3DRenderer->FilledBox(x + width - 2, (y + height) - (height / 4) - 2, 4, (height / 8) * 2 + 2, whiteOutline);

		D3DRenderer->Line(x, y, x + (width / 4), y, color);
		D3DRenderer->Line(x, y, x, y + (height / 4), color);
		D3DRenderer->Line(x, y + height, x + (width / 4), y + height, color);
		D3DRenderer->Line(x, y + height, x, (y + height) - (height / 4), color);
		D3DRenderer->Line(x + width, y, (x + width) - (width / 4), y, color);
		D3DRenderer->Line(x + width, y, x + width, y + (height / 4), color);
		D3DRenderer->Line(x + width, y + height, (x + width) - (width / 4), y + height, color);
		D3DRenderer->Line(x + width, y + height, x + width, (y + height) - (height / 4), color);
	}
}

void cD3DRenderer::HealthBar(int health, float maxhealth, int x, int y, int width, int height)
{
	if (health > maxhealth)
		health = maxhealth;

	int r = 255 - health * 2.55;
	int g = health * 2.55;
	float healthPercentage = health / maxhealth;
	float healthBarFillPercentage = height * healthPercentage;
	int healthBarDelta = height - healthBarFillPercentage;

	D3DRenderer->FilledBox(x - width / 2 - 6, y - 1, 5, height + 1, D3DCOLOR_XRGB(10, 10, 10));
	D3DRenderer->FilledBox(x - width / 2 - 5, y + healthBarDelta, 3, healthBarFillPercentage, D3DCOLOR_XRGB(r, g, 0));
}

void cD3DRenderer::OxygenInfo(float oxygenLevel)
{
	int oxygenPercentage = oxygenLevel * 100;
	int x = 40;
	int y = (ProcessManager->Size[1] - (ProcessManager->Size[1] / 4.25));

	D3DRenderer->FilledBox(x - 1, y - 1, 20 + 2, 100 + 2, D3DCOLOR_XRGB(35, 35, 35));
	D3DRenderer->FilledBox(x, y - (oxygenPercentage - 100), 20, oxygenPercentage, D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenColor[0] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenColor[1] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenColor[2] * 255)));
	D3DRenderer->DrawStringGame("O2", x + 10, y + 102, 255, 255, 255, 255, true, true, D3DRenderer->pFontDrawingsMedium);
	if (oxygenPercentage <= 90)
		D3DRenderer->DrawStringGame(std::string(std::to_string((int)oxygenPercentage) + "%").c_str(), x + 10, y + (90 - oxygenPercentage), 255, 255, 255, 255, true, true, D3DRenderer->pFontDrawingsSmall);

	if (SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarning)
		if (oxygenPercentage > 0 && oxygenPercentage <= 15)
		{
			D3DRenderer->DrawStringGameOutline("LOW OXYGEN LEVEL!", (ProcessManager->Size[0] / 2), (ProcessManager->Size[1] / 2) - (ProcessManager->Size[1] / 5), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[0] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[1] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[2] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[3] * 255), true, D3DRenderer->pFontDrawingsLarge);
			D3DRenderer->DrawStringGameOutline(std::string(std::to_string((int)oxygenPercentage) + "% LEFT!").c_str(), (ProcessManager->Size[0] / 2), (ProcessManager->Size[1] / 2) - (ProcessManager->Size[1] / 5) + 15, (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[0] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[1] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[2] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[3] * 255), true, D3DRenderer->pFontDrawingsLarge);
		}
		else if (oxygenPercentage == 0)
		{
			D3DRenderer->DrawStringGameOutline("OUT OF OXYGEN!", (ProcessManager->Size[0] / 2), (ProcessManager->Size[1] / 2) - (ProcessManager->Size[1] / 5), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[0] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[1] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[2] * 255), (int)(SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor[3] * 255), true, D3DRenderer->pFontDrawingsLarge);
		}
}

void cD3DRenderer::Circle(int X, int Y, int radius, int numSides, D3DCOLOR color)
{
	if (!D3DRenderer->pLine)
		D3DXCreateLine(D3DRenderer->pDevice, &D3DRenderer->pLine);
	else
	{
		D3DXVECTOR2 Line[128];
		float Step = D3DX_PI * 2.0 / numSides;
		int Count = 0;

		for (float a = 0; a < D3DX_PI * 2.0; a += Step)
		{
			float X1 = radius * cos(a) + X;
			float Y1 = radius * sin(a) + Y;
			float X2 = radius * cos(a + Step) + X;
			float Y2 = radius * sin(a + Step) + Y;
			Line[Count].x = X1;
			Line[Count].y = Y1;
			Line[Count + 1].x = X2;
			Line[Count + 1].y = Y2;
			Count += 2;
		}

		D3DRenderer->pLine->Begin();
		D3DRenderer->pLine->Draw(Line, Count, color);
		D3DRenderer->pLine->End();
	}
}

void cD3DRenderer::FilledBox(int x, int y, int width, int height, D3DCOLOR color)
{
	cDrawingHandler::sD3DVertex pVertex[4] = { { x, y + height, 0.0f, 1.0f, color }, { x, y, 0.0f, 1.0f, color }, { x + width, y + height, 0.0f, 1.0f, color }, { x + width, y, 0.0f, 1.0f, color } };
	D3DRenderer->pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	D3DRenderer->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(cDrawingHandler::sD3DVertex));
}

void cD3DRenderer::GradientRect(float x, float y, float width, float height, D3DCOLOR startCol, D3DCOLOR endCol, const char* orientation)
{
	cDrawingHandler::sD3DVertex vertices[4] = {{ 0, 0, 0, 1.0f, 0 }, { 0, 0, 0, 1.0f, 0 }, { 0, 0, 0, 1.0f, 0 }, { 0, 0, 0, 1.0f, 0 }};
	vertices[0].x = x;
	vertices[0].y = y + height;
	vertices[0].color = startCol;

	vertices[1].x = x;
	vertices[1].y = y;
	vertices[1].color = orientation == "HORIZONTAL" ? endCol : startCol;

	vertices[2].x = x + width;
	vertices[2].y = y + height;
	vertices[2].color = orientation == "HORIZONTAL" ? startCol : endCol;

	vertices[3].x = x + width;
	vertices[3].y = y;
	vertices[3].color = endCol;


	static LPDIRECT3DVERTEXBUFFER9 pVertexObject = NULL;
	static void* pVertexBuffer = NULL;

	D3DRenderer->pDevice->CreateVertexBuffer(sizeof(vertices), 0,
		D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVertexObject, NULL);

	pVertexObject->Lock(0, sizeof(vertices), &pVertexBuffer, 0);

	memcpy(pVertexBuffer, vertices, sizeof(vertices));
	pVertexObject->Unlock();

	D3DRenderer->pDevice->SetStreamSource(0, pVertexObject, 0, sizeof(cDrawingHandler::sD3DVertex));
	D3DRenderer->pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	D3DRenderer->pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	if (pVertexObject != NULL)
		pVertexObject->Release();
}

void cD3DRenderer::DrawStringGame(const char* string, float x, float y, int r, int g, int b, int a, bool centered, bool outline, ID3DXFont* pFont)
{

	RECT Center = { 0, 0, 0, 0 }, Position = { 0, 0, 0, 0 };
	
	if (centered)
		pFont->DrawTextA(NULL, string, (INT)strlen(string), &Center, DT_CALCRECT, NULL);
	
	if (!SETTINGS::MENU::LowEndPCMode || !outline)
	{
		Position.left = ((LONG)x + 1) - (Center.right / 2);
		Position.top = ((LONG)y + 1);
	
		pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
		Position.left = ((LONG)x - 1) - (Center.right / 2);
		Position.top = ((LONG)y + 1);
	
		pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
		Position.left = ((LONG)x - 1) - (Center.right / 2);
		Position.top = ((LONG)y - 1);
	
		pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
		Position.left = ((LONG)x + 1) - (Center.right / 2);
		Position.top = ((LONG)y - 1);
	
		pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	}
	
	Position.left = (LONG)x - (Center.right / 2);
	Position.top = (LONG)y;
	
	pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(r, g, b, a));
}

void cD3DRenderer::DrawStringGameOutline(const char* string, float x, float y, int r, int g, int b, int a, bool centered, ID3DXFont* pFont)
{

	RECT Center = { 0, 0, 0, 0 }, Position = { 0, 0, 0, 0 };
	
	if (centered)
		pFont->DrawTextA(NULL, string, (INT)strlen(string), &Center, DT_CALCRECT, NULL);
	
	Position.left = ((LONG)x + 1) - (Center.right / 2);
	Position.top = ((LONG)y + 1);
	
	pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	Position.left = ((LONG)x - 1) - (Center.right / 2);
	Position.top = ((LONG)y + 1);
	
	pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	Position.left = ((LONG)x - 1) - (Center.right / 2);
	Position.top = ((LONG)y - 1);
	
	pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	Position.left = ((LONG)x + 1) - (Center.right / 2);
	Position.top = ((LONG)y - 1);
	
	pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));
	
	Position.left = (LONG)x - (Center.right / 2);
	Position.top = (LONG)y;
	
	pFont->DrawTextA(NULL, string, (INT)strlen(string), &Position, DT_NOCLIP, D3DCOLOR_RGBA(r, g, b, a));
}

void cD3DRenderer::DrawGameObject(const char* objectName, float x, float y, float objectDistance, float colorR, float colorG, float colorB, float colorA)
{
	int objectLowDistnace, objectMediumDistance, objectHighDistance;

	if (SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistance) {
		objectLowDistnace = SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistanceLow;
		objectMediumDistance = SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistanceMedium;
	} else {
		objectLowDistnace = 150;
		objectMediumDistance = 500;
		objectHighDistance = 20000;
	}

	if (objectDistance >= 0 && objectDistance < objectLowDistnace)
	{
		D3DRenderer->DrawStringGame(objectName, x, y, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsLarge);
		D3DRenderer->DrawStringGame(std::string(std::to_string((int)objectDistance) + "m").c_str(), x, y + 13, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsLarge);
	}
	else if (objectDistance >= objectLowDistnace && objectDistance < objectMediumDistance)
	{
		D3DRenderer->DrawStringGame(objectName, x, y, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsMedium);
		D3DRenderer->DrawStringGame(std::string(std::to_string((int)objectDistance) + "m").c_str(), x, y + 11, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsMedium);
	}
	else if (objectDistance >= objectMediumDistance)
	{
		D3DRenderer->DrawStringGame(objectName, x, y, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsSmall);
		D3DRenderer->DrawStringGame(std::string(std::to_string((int)objectDistance) + "m").c_str(), x, y + 9, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsSmall);
	}
}

void cD3DRenderer::DrawGameObjectDebug(const char* objectName, float x, float y, float objectDistance, float colorR, float colorG, float colorB, float colorA)
{
	D3DRenderer->DrawStringGame(objectName, x, y, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsSmall);
	D3DRenderer->DrawStringGame(std::string(std::to_string((int)objectDistance) + "m").c_str(), x, y + 9, colorR, colorG, colorB, colorA, true, false, D3DRenderer->pFontDrawingsSmall);
}

void cD3DRenderer::DrawGameShip(const char* objectName, float x, float y, float objectDistance, float colorR, float colorG, float colorB, float colorA, bool IsShipAllied)
{
	D3DRenderer->DrawStringGame(objectName, x, y, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsSmall);
	if ((IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Distance) || (!IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Distance))
		D3DRenderer->DrawStringGame(std::string(std::to_string((int)objectDistance) + "m").c_str(), x, y + 9, colorR, colorG, colorB, colorA, true, true, D3DRenderer->pFontDrawingsSmall);
}

std::tuple<int, int, int, int> cD3DRenderer::getTreasureColor(std::string treasureName)
{
	int r, g, b, a;

	if (treasureName.find("Common") != std::string::npos)
	{
		r = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresCommonColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresCommonColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresCommonColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresCommonColor[3] * 255.f);
	}
	else if (treasureName.find("Rare") != std::string::npos)
	{
		r = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresRareColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresRareColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresRareColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresRareColor[3] * 255.f);
	}
	else if (treasureName.find("Fort") != std::string::npos
	|| treasureName.find("Stronghold") != std::string::npos
	|| treasureName.find("PirateLegend") != std::string::npos
	|| treasureName.find("Drunken") != std::string::npos
	|| treasureName.find("Weeping") != std::string::npos
	|| treasureName.find("AIShip") != std::string::npos
	|| treasureName.find("Ashen") != std::string::npos
	|| treasureName.find("DVR") != std::string::npos) // epic
	{
		r = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresEpicColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresEpicColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresEpicColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresEpicColor[3] * 255.f);
	}
	else if (treasureName.find("Mythical") != std::string::npos)
	{
		r = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresMythicalColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresMythicalColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresMythicalColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresMythicalColor[3] * 255.f);
	}
	else if (treasureName.find("Legendary") != std::string::npos)
	{
		r = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresLegendaryColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresLegendaryColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresLegendaryColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresLegendaryColor[3] * 255.f);
	}
	else
	{
		r = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresOthersColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresOthersColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresOthersColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresOthersColor[3] * 255.f);
	}

	return std::make_tuple(r, g, b, a );
}

std::tuple<int, int, int, int> cD3DRenderer::getShipColor(string shipType)
{
	int r, g, b, a;

	if (shipType.find("azure") != string::npos)
	{
		r = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::AzureScoutColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::AzureScoutColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::AzureScoutColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::AzureScoutColor[2] * 255.f);
	}
	else if (shipType.find("regal") != string::npos)
	{
		r = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::RegalHoundColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::RegalHoundColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::RegalHoundColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::RegalHoundColor[2] * 255.f);
	}
	else if (shipType.find("lucky") != string::npos)
	{
		r = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::LuckyRoverColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::LuckyRoverColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::LuckyRoverColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::LuckyRoverColor[2] * 255.f);
	}
	else if (shipType.find("flaming") != string::npos)
	{
		r = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::FlamingJackalColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::FlamingJackalColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::FlamingJackalColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::FlamingJackalColor[2] * 255.f);
	}
	else if (shipType.find("golden") != string::npos)
	{
		r = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::GoldenChaserColor[0] * 255.f);
		g = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::GoldenChaserColor[1] * 255.f);
		b = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::GoldenChaserColor[2] * 255.f);
		a = (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::GoldenChaserColor[2] * 255.f);
	}
	else
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	return std::make_tuple(r, g, b, a);
}