#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include "singleton.h"


DWORD keys[] = { VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON };
const char* keyItems[] = { "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse" };

inline namespace Configuration
{
	class Settings : public Singleton<Settings>
	{
	public:

		const char* BoxTypes[2] = { u8"方框类型1",u8"方框类型2" };
		const char* LineTypes[3] = { u8"屏幕底边",u8"屏幕顶部",u8"屏幕中间" };


		bool b_MenuShow = true;


		bool b_Visual = false;
		bool b_EspBox = false;
		bool b_EspNPC = false;
		bool b_monster = false;
		bool b_item = false;
		bool b_animalaiming = false;
        bool b_aiming = false;
		bool b_aimingpos = false;
		bool b_NOrecoil= false;
		bool b_SafeZoneShots = false;
		bool b_firerate = false;
		bool b_big = false;
		bool b_Brighten = false;
		bool b_track = false;
		bool b_filter = false;
		bool b_accelerate = false;
		

		float fl_VisibleColor[3] = { 0.f,255.f / 255,0.f };  //
		float fl_InvisibleColor[3] = { 255.f / 255,0.f,0.f };  //

		float fl_FovColor[3] = { 255.f / 255,0.f,0.f };  //
		int BoxType = 0;
		int LineType = 0;
		int tab_index = 0;
		int AimKey = 0;

		float Smoothing = 2.0f;
		float AimbotFOV = 90.0f;
		float max_distance = 500.0f;

	};
#define CFG Configuration::Settings::Get()
}
bool GetAimKey()
{
	return GetAsyncKeyState(keys[CFG.AimKey]);
}
