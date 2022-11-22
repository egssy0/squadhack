
#pragma once

#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include  <d3dx9.h>
#include "singleton.h"
#include "vector.h"
inline HANDLE driver_handle;
inline LPCWSTR drivername = L"\\\\.\\n1ttld";
inline namespace RogueCompany
{
	class Variables : public Singleton<Variables>
	{
	public:
		//const char* dwProcessName = "WTL-Win64-Shipping.exe";

		DWORD PID;
		const char* dwProcessName = NULL;
		
		//



		//DWORD dwProcessId = NULL;
		uint64_t dwProcess_Base = NULL;
		//HWND gameHWND = NULL;

		int actor_count = NULL;
		int ScreenHeight = NULL;
		int ScreenWidth = NULL;
		int ScreenLeft = NULL;
		int ScreenRight = NULL;
		int ScreenTop = NULL;
		int ScreenBottom = NULL;
		int Meshpoint = NULL;

		float ScreenCenterX = ScreenWidth / 2;
		float ScreenCenterY = ScreenHeight / 2;

		int ste = NULL;


		DWORD_PTR game_instance = NULL;
		DWORD_PTR u_world = NULL;
		DWORD_PTR local_player_pawn = NULL;
		DWORD_PTR local_player_array = NULL;
		DWORD_PTR local_player = NULL;
		DWORD_PTR local_player_root = NULL;
		DWORD_PTR local_player_controller = NULL;
		DWORD_PTR local_player_state = NULL;
		DWORD_PTR local_player_Team = NULL;
		DWORD_PTR persistent_level = NULL;
		DWORD_PTR actors = NULL;
		DWORD_PTR equipped_flashlight = NULL;
		DWORD_PTR equipped_weapon_type = NULL;


	};
#define GameVars RogueCompany::Variables::Get()

	class Offsets : public Singleton<Offsets>
	{
	public:

		DWORD offset_u_world = 0x503A098;
		DWORD offset_g_names = 0x4F1CF40;
		DWORD offset_camera_manager = 0x2E0; // APlayerController->PlayerCameraManager
		DWORD offset_camera_cache = 0x1a40; //APlayerCameraManager->CameraCachePrivate
		DWORD offset_persistent_level = 0x30; //UWorld->PersistentLevel
		DWORD offset_actor_array = 0x98; //UNetConnection->OwningActor
		DWORD offset_actor_count = 0xA0; //UNetConnection->MaxPacket

		DWORD offset_game_instance = 0x170; //UWolrd->OwningGameInstance
		DWORD offset_local_players_array = 0x38; //UGameInstance->LocalPlayers
		DWORD offset_player_controller = 0x30; //UPlayer->PlayerController
		DWORD offset_apawn = 0x2C8;  //APlayerController->AcknowledgedPawn

		DWORD offset_root_component = 0x160; //AActor->RootComponent坐标入口
		DWORD offset_relative_location = 0x1D0; //USceneComponent->RelativeLocation坐标
		DWORD offset_actor_id = 0x18;


		DWORD offset_player_state = 0x268; //AController->PlayerState状态
		DWORD offset_player_Teme = 0x1188; //阵营
		DWORD offset_player_ATeme = 0x1188; //自己阵营
		DWORD offset_player_name = 0x350;//名字


		DWORD offset_actor_mesh = 0x2A8; //ACharacter->Mesh骨骼入口点
		DWORD offset_bone_array = 0x450;//骨骼子真
		DWORD offset_component_to_world = 0x1c0;//骨骼旋转


		DWORD offset_last_submit_time = 0x2B0;//鼠标X
		DWORD offset_last_render_time = 0x2B4;//鼠标Y
		DWORD offset_player_health = 0x1c18;//血量



	};

#define GameOffset RogueCompany::Offsets::Get()
}
