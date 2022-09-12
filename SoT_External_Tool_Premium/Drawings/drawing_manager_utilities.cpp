#include "drawing_manager_utilities.h"

cDrawingManagerUtilities* DrawingManagerUtilities = new cDrawingManagerUtilities();

cDrawingManagerUtilities::cDrawingManagerUtilities()
{
}

cDrawingManagerUtilities::~cDrawingManagerUtilities()
{
}

void cDrawingManagerUtilities::DrawUtilities()
{
	auto world = MemoryManager->Read<cUWorld>(MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::UWorld));
	auto localplayer = world.GetGameInstance().GetLocalPlayer();
	auto localplayer_controller = localplayer.GetPlayerController();
	auto localplayer_cameramanager = localplayer_controller.GetCameraManager();

	SOT->localPlayer.name = W2S->wstringToString(localplayer_controller.GetActor().GetPlayerState().GetName());

	SOT->localPlayer.position = localplayer_controller.GetActor().GetRootComponent().GetPosition();
	SOT->localCamera.fov = localplayer_cameramanager.GetCameraFOV();
	SOT->localCamera.angles = localplayer_cameramanager.GetCameraRotation();
	SOT->localCamera.position = localplayer_cameramanager.GetCameraPosition();

	//-> CROSSHAIR
	if (SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairEnabled)
	{
		const int crosshair_width = SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairThickness;
		const int crosshair_height = (SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairSize * 2) + crosshair_width;
		D3DCOLOR crosshair_color = D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairColor[2] * 255.0f));

		bool crosshair_gradient = SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradient;
		D3DCOLOR crosshairStart_color, crosshairEnd_color;
		const char* crosshair_gradienttype;
		if (crosshair_gradient)
		{
			crosshair_gradienttype = SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradientType;
			crosshairStart_color = D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairStartColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairStartColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairStartColor[2] * 255.0f));
			crosshairEnd_color = D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairEndColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairEndColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairEndColor[2] * 255.0f));
		}

		Vector2 crossvert, crosshoriz, screenmiddle;
		int vertical_height, vertical_width, horiz_height, horiz_width;

		//-> Window Size
		screenmiddle.x = ProcessManager->Size[0] / 2;
		screenmiddle.y = ProcessManager->Size[1] / 2;
		//-> Vertical Position
		crossvert.x = screenmiddle.x - (crosshair_width / 2);
		crossvert.y = screenmiddle.y - (crosshair_height / 2);
		//-> Horizontal Position
		crosshoriz.x = screenmiddle.x - (crosshair_height / 2);
		crosshoriz.y = screenmiddle.y - (crosshair_width / 2);

		if (crosshair_gradient)
		{
			D3DRenderer->FilledBox(crossvert.x - 1, crossvert.y - 1, crosshair_width + 2, crosshair_height + 2, D3DCOLOR_XRGB(35, 35, 35));
			D3DRenderer->GradientRect(crossvert.x, crossvert.y, crosshair_width, crosshair_height, crosshairStart_color, crosshairEnd_color, crosshair_gradienttype);

			D3DRenderer->FilledBox(crosshoriz.x - 1, crosshoriz.y - 1, crosshair_height + 2, crosshair_width + 2, D3DCOLOR_XRGB(35, 35, 35));
			D3DRenderer->GradientRect(crosshoriz.x, crosshoriz.y, crosshair_height, crosshair_width, crosshairStart_color, crosshairEnd_color, crosshair_gradienttype);
		} else {
			D3DRenderer->FilledBox(crossvert.x - 1, crossvert.y - 1, crosshair_width + 2, crosshair_height + 2, D3DCOLOR_XRGB(35, 35, 35));
			D3DRenderer->FilledBox(crossvert.x, crossvert.y, crosshair_width, crosshair_height, crosshair_color);

			D3DRenderer->FilledBox(crosshoriz.x - 1, crosshoriz.y - 1, crosshair_height + 2, crosshair_width + 2, D3DCOLOR_XRGB(35, 35, 35));
			D3DRenderer->FilledBox(crosshoriz.x, crosshoriz.y, crosshair_height, crosshair_width, crosshair_color);
		}
	}

	//-> COMPASS
	if (SETTINGS::TOOLS::UTILITY::COMPASS::compassEnabled)
	{
		Vector2 compass_pos = { (float)(ProcessManager->Size[0] / 2), (float)(ProcessManager->Size[1] * 0.020f) };

		float compass = localplayer_cameramanager.GetCameraRotation().y;

		compass += 90.0f;

		if (compass < 1)
			compass += 360.0f;

		char* dir = "x";

		if (SETTINGS::TOOLS::UTILITY::COMPASS::compassFullName)
		{
			if (compass >= 337.5 || compass < 22.5)
				dir = "North";
			else if (compass >= 22.5 && compass < 67.5)
				dir = "North East";
			else if (compass >= 67.5 && compass < 112.5)
				dir = "East";
			else if (compass >= 112.5 && compass < 157.5)
				dir = "South East";
			else if (compass >= 157.5 && compass < 202.5)
				dir = "South";
			else if (compass >= 202.5 && compass < 247.5)
				dir = "South West";
			else if (compass >= 247.5 && compass < 292.5)
				dir = "West";
			else if (compass >= 292.5 && compass < 337.5)
				dir = "North West";
		} else {
			if (compass >= 337.5 || compass < 22.5)
				dir = "N";
			else if (compass >= 22.5 && compass < 67.5)
				dir = "NE";
			else if (compass >= 67.5 && compass < 112.5)
				dir = "E";
			else if (compass >= 112.5 && compass < 157.5)
				dir = "SE";
			else if (compass >= 157.5 && compass < 202.5)
				dir = "S";
			else if (compass >= 202.5 && compass < 247.5)
				dir = "SW";
			else if (compass >= 247.5 && compass < 292.5)
				dir = "W";
			else if (compass >= 292.5 && compass < 337.5)
				dir = "NW";
		}

		char SET_DirectionBuf[32];
		char SET_CompassBuf[3];
		sprintf(SET_DirectionBuf, "%s", dir);
		sprintf(SET_CompassBuf, "%u", (int)compass);
		if (SETTINGS::TOOLS::UTILITY::COMPASS::compassSize == 1) {
			D3DRenderer->DrawStringGameOutline(SET_DirectionBuf, compass_pos.x, compass_pos.y, (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[3] * 255.0f), true, D3DRenderer->pFontUISmall);
			D3DRenderer->DrawStringGameOutline(SET_CompassBuf, compass_pos.x, compass_pos.y + 10, (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[3] * 255.0f), true, D3DRenderer->pFontUISmall);
		} else if (SETTINGS::TOOLS::UTILITY::COMPASS::compassSize == 2) {
			D3DRenderer->DrawStringGameOutline(SET_DirectionBuf, compass_pos.x, compass_pos.y, (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[3] * 255.0f), true, D3DRenderer->pFontUIMedium);
			D3DRenderer->DrawStringGameOutline(SET_CompassBuf, compass_pos.x, compass_pos.y + 15, (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[3] * 255.0f), true, D3DRenderer->pFontUISmall);
		} else {
			D3DRenderer->DrawStringGameOutline(SET_DirectionBuf, compass_pos.x, compass_pos.y, (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[3] * 255.0f), true, D3DRenderer->pFontUILarge);
			D3DRenderer->DrawStringGameOutline(SET_CompassBuf, compass_pos.x, compass_pos.y + 20, (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::COMPASS::compassColor[3] * 255.0f), true, D3DRenderer->pFontUISmall);
		}
	}

	/*
	-> VECTOR
	vector<BeaconsList> tempBeconsList;
	
	if (!worldActors.IsValid() || worldActors.Length() == 0)
		return;
	
	
	BeaconsList Beacon{};
	Beacon.beaconName = x;
	Beacon.beaconLocation = <float*>{x, y, z};
	Beacon.beaconColor = <float*>{x, y, z};
	tempBeconsList.push_back(Beacon);
	
	-> and then just read data in another thread
	*/

	//-> BEACONS
	if (SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconEnabled) //-> First Beacon
	{
		std::string beaconName(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconName);
		std::transform(beaconName.begin(), beaconName.end(), beaconName.begin(), ::toupper);
	
		Vector2 Screen;
		Vector3 beaconLocation = { SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[2] };
		auto beaconDistance = SOT->localCamera.position.DistTo(beaconLocation) / 100.00f;
	
		if (W2S->WorldToScreen(beaconLocation, &Screen))
		{
			D3DRenderer->DrawStringGame(beaconName.c_str(), Screen.x, Screen.y, (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
			D3DRenderer->DrawStringGame(std::string(std::to_string((int)beaconDistance) + "m").c_str(), Screen.x, Screen.y + 13, (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
		}
	}

	if (SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconEnabled) //-> Second Beacon
	{
		std::string beaconName(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconName);
		std::transform(beaconName.begin(), beaconName.end(), beaconName.begin(), ::toupper);

		Vector2 Screen;
		Vector3 beaconLocation = { SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[2] };
		auto beaconDistance = SOT->localCamera.position.DistTo(beaconLocation) / 100.00f;

		if (W2S->WorldToScreen(beaconLocation, &Screen))
		{
			D3DRenderer->DrawStringGame(beaconName.c_str(), Screen.x, Screen.y, (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
			D3DRenderer->DrawStringGame(std::string(std::to_string((int)beaconDistance) + "m").c_str(), Screen.x, Screen.y + 13, (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
		}
	}

	if (SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconEnabled) //-> Third Beacon
	{
		std::string beaconName(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconName);
		std::transform(beaconName.begin(), beaconName.end(), beaconName.begin(), ::toupper);

		Vector2 Screen;
		Vector3 beaconLocation = { SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[2] };
		auto beaconDistance = SOT->localCamera.position.DistTo(beaconLocation) / 100.00f;

		if (W2S->WorldToScreen(beaconLocation, &Screen))
		{
			D3DRenderer->DrawStringGame(beaconName.c_str(), Screen.x, Screen.y, (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
			D3DRenderer->DrawStringGame(std::string(std::to_string((int)beaconDistance) + "m").c_str(), Screen.x, Screen.y + 13, (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
		}
	}

	if (SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconEnabled) //-> Fourth Beacon
	{
		std::string beaconName(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconName);
		std::transform(beaconName.begin(), beaconName.end(), beaconName.begin(), ::toupper);

		Vector2 Screen;
		Vector3 beaconLocation = { SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[2] };
		auto beaconDistance = SOT->localCamera.position.DistTo(beaconLocation) / 100.00f;

		if (W2S->WorldToScreen(beaconLocation, &Screen))
		{
			D3DRenderer->DrawStringGame(beaconName.c_str(), Screen.x, Screen.y, (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
			D3DRenderer->DrawStringGame(std::string(std::to_string((int)beaconDistance) + "m").c_str(), Screen.x, Screen.y + 13, (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
		}
	}

	if (SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconEnabled) //-> Fifth Beacon
	{
		std::string beaconName(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconName);
		std::transform(beaconName.begin(), beaconName.end(), beaconName.begin(), ::toupper);

		Vector2 Screen;
		Vector3 beaconLocation = { SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[2] };
		auto beaconDistance = SOT->localCamera.position.DistTo(beaconLocation) / 100.00f;

		if (W2S->WorldToScreen(beaconLocation, &Screen))
		{
			D3DRenderer->DrawStringGame(beaconName.c_str(), Screen.x, Screen.y, (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
			D3DRenderer->DrawStringGame(std::string(std::to_string((int)beaconDistance) + "m").c_str(), Screen.x, Screen.y + 13, (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[0] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[1] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[2] * 255.0f), (int)(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsMedium);
		}
	}
}