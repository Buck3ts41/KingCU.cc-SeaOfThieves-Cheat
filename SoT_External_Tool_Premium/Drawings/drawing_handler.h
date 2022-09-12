#pragma once
#include "../Overlay/D3DRenderer.h"
#include <wtypes.h>

class cDrawingHandler
{
public:
	cDrawingHandler();
	~cDrawingHandler();

	struct sD3DVertex
	{
		float x, y, z, rhw;
		DWORD color;
	};
};

cDrawingHandler* DrawingHandler;
