#include "../Overlay/UIHandler.h"

cUIHandler* UIHandler = new cUIHandler();

cUIHandler::cUIHandler()
{
}

cUIHandler::~cUIHandler()
{
}

void cUIHandler::loadUIStyles()
{
	ImGui::GetStyle().GrabRounding = 2.f;
	ImGui::GetStyle().ChildRounding = 2.f;
	ImGui::GetStyle().FrameRounding = 2.f;
	ImGui::GetStyle().PopupRounding = 2.f;
	ImGui::GetStyle().WindowRounding = 10.f;
	ImGui::GetStyle().FrameBorderSize = 1.f;
	ImGui::GetStyle().WindowBorderSize = 1.f;
	ImGui::GetStyle().ScrollbarRounding = 2.f;
	ImGui::GetStyle().WindowTitleAlign = { 0.5f, 0.4f };
	//ImGui::GetStyle().ButtonTextAlign = { 0.5f, 0.35f };
	ImGui::GetStyle().WindowPadding = { 7.f, 8.f };
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4{ 1.f, 1.f, 1.f, 1.f };
	colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_Header] = ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f };
	colors[ImGuiCol_CheckMark] = ImVec4{ 1.f, 1.f, 1.f, 1.f };
	colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 54.f / 255.f, 54.f / 255.f, 54.f / 255.f, 1.f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f };
	colors[ImGuiCol_Button] = ImVec4{ 54.f / 255.f, 54.f / 255.f, 54.f / 255.f, 1.f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f };
	colors[ImGuiCol_Border] = ImVec4{ 80.f / 255.f, 80.f / 255.f, 80.f / 255.f, 138.f / 255.f };
	colors[ImGuiCol_FrameBg] = ImVec4{ 83.f / 255.f, 83.f / 255.f, 83.f / 255.f, 100.f / 255.f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f };
	colors[ImGuiCol_SliderGrab] = ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f };
	colors[ImGuiCol_SliderGrabActive] = ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f };
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f };
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f };
}

void cUIHandler::drawButton(const char* buttonName, int buttonID, const char* buttonType, bool active, float width, float height, bool* change_opositive)
{
	if (active)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f });
	} else {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 54.f / 255.f, 54.f / 255.f, 54.f / 255.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 55.f / 255.f, 126.f / 255.f, 226.f / 255.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 33.f / 255.f, 104.f / 255.f, 203.f / 255.f, 1.f });
	}

	if (ImGui::Button(buttonName, { width, height }))
	{
		//-> CATEGORY TABS
		if (buttonType == "GENERAL_TAB")
			SETTINGS::MENU::activeMenuTab = buttonID;
		//-> SIDE-CATEGORY TABS
		else if (buttonType == "SIDE_TAB_TREASURES")
			SETTINGS::MENU::activeMenuTab_treasures = buttonID;
		else if (buttonType == "SIDE_TAB_OBJECTS")
			SETTINGS::MENU::activeMenuTab_objects = buttonID;
		//-> IN-CATEGORY TABS
		else if (buttonType == "TREASURES_TAB_1_1")
			SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresCommonActiveTab = buttonID;
	}
	ImGui::PopStyleColor(3);
}

void cUIHandler::spaceBetweenElements(float x_space, float y_space)
{
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(x_space, y_space));
	ImGui::SameLine();
}

void cUIHandler::spaceFromHeader(bool nextColumn)
{
	ImGui::Dummy(ImVec2(0.f, 2.5f));
	if (nextColumn)
		ImGui::NextColumn();
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.f, 4.f));
}

void cUIHandler::nextColumn()
{
	ImGui::NextColumn();
	ImGui::Dummy(ImVec2(0.f, 4.f));
}

void cUIHandler::HelpMarker(const char* desc, bool useImage, const char* imageName, float imageXSize, float imageYSize)
{
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2.f);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 3.f);
	ImGui::TextDisabled("( ? )");

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(desc);
		ImGui::Dummy(ImVec2(0.f, 5.f));
		if (useImage)
		{
			IDirect3DTexture9* additionalImage = nullptr;
			D3DXCreateTextureFromFile(D3DRenderer->pDevice, imageName, &additionalImage);
			ImGui::Image(additionalImage, ImVec2(imageXSize, imageYSize));
		}
		ImGui::EndTooltip();
	}
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
}

void cUIHandler::UIChildHeaderSingle(const char* text, bool spaceFromHeader, float width)
{
	std::string UIChildHeader = text;
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (width / 2) - (ImGui::CalcTextSize(UIChildHeader.c_str()).x / 2)
		- ImGui::GetScrollX() - 2 * (ImGui::GetStyle().ItemSpacing.x / 2));
	ImGui::Text(text);
	UIHandler->spaceFromHeader(spaceFromHeader);
	
}

void cUIHandler::UIChildHeaderDouble(const char* text_1, const char* text_2, bool spaceFromHeader)
{
	ImGui::Columns(2);
	std::string UiChildHeader_1 = text_1;
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() / 2) - (ImGui::CalcTextSize(UiChildHeader_1.c_str()).x / 2)
		- ImGui::GetScrollX() - 2 * (ImGui::GetStyle().ItemSpacing.x / 2));
	ImGui::Text(text_1);
	ImGui::NextColumn();
	std::string UiChildHeader_2 = text_2;
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() / 2) - (ImGui::CalcTextSize(UiChildHeader_2.c_str()).x / 2)
		- ImGui::GetScrollX() - 2 * (ImGui::GetStyle().ItemSpacing.x / 2));
	ImGui::Text(text_2);
	UIHandler->spaceFromHeader(spaceFromHeader);
}

void cUIHandler::utilityBeacon(int beaconID, bool remove)
{
	auto world = MemoryManager->Read<cUWorld>(MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::UWorld));
	auto localplayer = world.GetGameInstance().GetLocalPlayer();
	auto localplayer_controller = localplayer.GetPlayerController();

	if (!remove)
	{
		if (beaconID == 1)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[0] = localplayer_controller.GetActor().GetRootComponent().GetPosition().x;
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[1] = localplayer_controller.GetActor().GetRootComponent().GetPosition().y;
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[2] = localplayer_controller.GetActor().GetRootComponent().GetPosition().z - 50;
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconEnabled = true;
		}
		else if (beaconID == 2)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[0] = localplayer_controller.GetActor().GetRootComponent().GetPosition().x;
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[1] = localplayer_controller.GetActor().GetRootComponent().GetPosition().y;
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[2] = localplayer_controller.GetActor().GetRootComponent().GetPosition().z - 50;
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconEnabled = true;
		}
		else if (beaconID == 3)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[0] = localplayer_controller.GetActor().GetRootComponent().GetPosition().x;
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[1] = localplayer_controller.GetActor().GetRootComponent().GetPosition().y;
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[2] = localplayer_controller.GetActor().GetRootComponent().GetPosition().z - 50;
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconEnabled = true;
		}
		else if (beaconID == 4)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[0] = localplayer_controller.GetActor().GetRootComponent().GetPosition().x;
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[1] = localplayer_controller.GetActor().GetRootComponent().GetPosition().y;
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[2] = localplayer_controller.GetActor().GetRootComponent().GetPosition().z - 50;
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconEnabled = true;
		}
		else if (beaconID == 5)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[0] = localplayer_controller.GetActor().GetRootComponent().GetPosition().x;
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[1] = localplayer_controller.GetActor().GetRootComponent().GetPosition().y;
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[2] = localplayer_controller.GetActor().GetRootComponent().GetPosition().z - 50;
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconEnabled = true;
		}
	}
	else
	{
		if (beaconID == 1)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[0] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[1] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[2] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconEnabled = false;
		}
		else if (beaconID == 2)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[0] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[1] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[2] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconEnabled = false;
		}
		else if (beaconID == 3)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[0] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[1] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[2] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconEnabled = false;
		}
		else if (beaconID == 4)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[0] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[1] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[2] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconEnabled = false;
		}
		else if (beaconID == 5)
		{
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[0] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[1] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[2] = 0;
			SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconEnabled = false;
		}
	}
}

void cUIHandler::utilityBeaconSetKey(int beaconID)
{
}
