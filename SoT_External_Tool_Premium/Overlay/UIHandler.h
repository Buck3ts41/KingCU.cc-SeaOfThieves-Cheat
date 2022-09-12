#pragma once
#include "../Core/main.h"

class cUIHandler
{
public:
	cUIHandler();
	~cUIHandler();

	void loadUIStyles();
	void pushColorForButton(bool active);
	void drawButton(const char* buttonName, int buttonID, const char* buttonType, bool active, float width, float height, bool* change_opositive = nullptr);
	void spaceBetweenElements(float x_space, float y_space);
	void spaceFromHeader(bool nextColumn);
	void nextColumn();
	void HelpMarker(const char* desc, bool useImage, const char* imageName, float imageXSize = 0.f, float imageYSize = 0.f);
	void UIChildHeaderSingle(const char* text, bool spaceFromHeader, float width);
	void UIChildHeaderDouble(const char* text_1, const char* text_2, bool spaceFromHeader);
	void drawItemESP(int itemID, const char* PDName, const char* SDKName, const unsigned int RenderMinDistance, const unsigned int RenderMaxDistance, const char* Category, const char* Rarity, const float HighDistance, const float MediumDistance, const float LowDistance);
	void utilityBeacon(int beaconID, bool remove);
	void utilityBeaconSetKey(int beaconID);
};

extern cUIHandler* UIHandler;