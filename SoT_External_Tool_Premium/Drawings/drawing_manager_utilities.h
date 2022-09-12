#pragma once
#include "../Overlay/D3DRenderer.h"
#include "../Drawings/vector.h"
#include "../Core/globals.h"
#include <iostream>
#include <algorithm>

class cDrawingManagerUtilities
{
public:
	cDrawingManagerUtilities();
	~cDrawingManagerUtilities();

	void DrawUtilities();

private:

};

extern cDrawingManagerUtilities* DrawingManagerUtilities;