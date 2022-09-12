#pragma once
#include "../Others/treasures_manager.h"
#include "../Overlay/UIHandler.h"
#include "../Core/main.h"

class cUIRenderer
{
public:
	cUIRenderer();
	~cUIRenderer();

	void DrawInfo(IDirect3DDevice9* pDevice);
	void DrawMenu(IDirect3DDevice9* pDevice);

	HHOOK hMouseHook;
	HHOOK MouseHook;
};

extern cUIRenderer* UIRenderer;

void UpdateOverlay();
