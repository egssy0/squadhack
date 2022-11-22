#include "function.h"
#include "driverloading.h"
#include "overlay.h"
#include "menucycle.h"
#include "allnames.h"
namespace OverlayWindow
{
	WNDCLASSEX WindowClass;
	HWND Hwnd;
	LPCSTR Name;
}
typedef struct _EntityList
{
	uintptr_t actor_camp;
	uintptr_t actor_pawn;
	uintptr_t actor_mesh;
	string PLNAME;
	string actor_name;
	uintptr_t actor_state;
	int actor_id;

}EntityList;
std::vector<EntityList> entityList;












class textx
{
public:
	wchar_t word[64];
};



auto CallHacks()->VOID
{
	while (true)
	{
		if (CFG.b_NOrecoil)
		{

			auto ACVAD = maxread<float>(GameVars.dwProcess_Base + 0x82EC03);
	
			if (ACVAD!=0)
			{
				write<float>(GameVars.dwProcess_Base + 0x82EC03, 0); // HorizontalCurve
			}




		}
		if (CFG.b_firerate)
		{
			write<float>(GameVars.equipped_weapon_type + 0x5B0, 0.01);
		}



		if (CFG.b_accelerate)
		{
			if (GetAsyncKeyState(VK_LSHIFT) != 0)
			{
				write<double>(GameVars.local_player_pawn + 0xBC, 30);
			}
			else
			{
				write<double>(GameVars.local_player_pawn + 0xBC, 0.0078125);

			}
		}




		if (CFG.b_track)
		{

		}


		Sleep(10);
	}
}


auto CallAimbot()->VOID
{
	while (true)
	{
		auto EntityList_Copy = entityList;	
		bool isAimbotActive = CFG.b_aiming;


		if (isAimbotActive)
		{
			float target_dist = FLT_MAX;
			EntityList target_entity = {};
			if (GetAsyncKeyState(VK_RBUTTON) != 0)
			{
				for (int index = 0; index < EntityList_Copy.size(); ++index)
				{
					auto Entity = EntityList_Copy[index];
					if (!Entity.actor_mesh || !Game::isVisible(Entity.actor_mesh)) continue;

					auto head_pos = Game::GetBoneWithRotation(Entity.actor_mesh, 9);
					auto targethead = Game::ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z + 15));
					float x = targethead.x - GetSystemMetrics(SM_CXSCREEN) / 2.0f;
					float y = targethead.y - GetSystemMetrics(SM_CYSCREEN) / 2.0f;
					float crosshair_dist = sqrtf((x * x) + (y * y));

					if (crosshair_dist <= FLT_MAX && crosshair_dist <= target_dist)
					{
						if (crosshair_dist > CFG.AimbotFOV) // FOV
							continue;

						target_dist = crosshair_dist;
						target_entity = Entity;

					}
				}

				if (target_entity.actor_mesh != 0 || target_entity.actor_pawn != 0 || target_entity.actor_id != 0)
				{

					auto head_pos = Game::GetBoneWithRotation(target_entity.actor_mesh, 9);
					auto targethead = Game::ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z + 15));
					auto HOOKpos = maxread<DWORD_PTR>(GameVars.dwProcess_Base + 0x503A370) +0x220;
					//if (CFG.b_track)
					//{
					//	write<float>(HOOKpos, head_pos.x);
					//	write<float>(HOOKpos + 4, head_pos.y);
					//	write<float>(HOOKpos + 8, head_pos.z);
					//}
					//else
					//{
					//	write<float>(HOOKpos,0);
					//	write<float>(HOOKpos + 4, 0);
					//	write<float>(HOOKpos + 8, 0);
					//}


					auto pypos = maxread<Vector3>(GameVars.local_player + 0x88);

					Vector3 OppPos; //取坐标差
					OppPos.x = head_pos.x - pypos.x;
					OppPos.y = head_pos.y - pypos.y;
					OppPos.z = head_pos.z - pypos.z;


					vec2 AimAngle;
					AimAngle.x = atan2f(OppPos.y, OppPos.x) * 180 / M_PI;
					AimAngle.y = atan2f(OppPos.z, (sqrt(OppPos.x * OppPos.x + OppPos.y * OppPos.y))) * 180 / M_PI;



					write<float>(GameVars.local_player_controller + GameOffset.offset_last_submit_time, AimAngle.y);
					write<float>(GameVars.local_player_controller + GameOffset.offset_last_render_time, AimAngle.x);

					//move_to(targethead.x, targethead.y);

				}

			}

		}


		Sleep(10);
	}
}



auto GameCache()->VOID
{
	while (true)
	{

		
		std::vector<EntityList> tmpList;




		

		GameVars.u_world = maxread<DWORD_PTR>(GameVars.dwProcess_Base + GameOffset.offset_u_world);	
		GameVars.game_instance = maxread<DWORD_PTR>(GameVars.u_world + GameOffset.offset_game_instance);
		GameVars.local_player_array = maxread<DWORD_PTR>(GameVars.game_instance + GameOffset.offset_local_players_array);
		GameVars.local_player = maxread<DWORD_PTR>(GameVars.local_player_array);
		GameVars.local_player_controller = maxread<DWORD_PTR>(GameVars.local_player + GameOffset.offset_player_controller);
		GameVars.local_player_pawn = maxread<DWORD_PTR>(GameVars.local_player_controller + GameOffset.offset_apawn);
		GameVars.local_player_root = maxread<DWORD_PTR>(GameVars.local_player_pawn + GameOffset.offset_root_component);
		GameVars.local_player_state = maxread<DWORD_PTR>(GameVars.local_player_pawn + GameOffset.offset_player_state);
		GameVars.persistent_level = maxread<DWORD_PTR>(GameVars.u_world + GameOffset.offset_persistent_level);
		GameVars.actors = maxread<DWORD_PTR>(GameVars.persistent_level + GameOffset.offset_actor_array);
		GameVars.actor_count = maxread<int>(GameVars.persistent_level + GameOffset.offset_actor_count);
		GameVars.equipped_weapon_type=maxread<DWORD_PTR>(GameVars.local_player_pawn + 0x150);
		GameVars.equipped_weapon_type = maxread<DWORD_PTR>(GameVars.equipped_weapon_type);


		for (int i = 0; i < GameVars.actor_count; i++)
		{

			auto actor_pawn = maxread<DWORD_PTR>(GameVars.actors + i * 0x8);
			if (actor_pawn == 0x00)
				continue;

			auto actor_id = maxread<int>(actor_pawn + GameOffset.offset_actor_id);
			auto actor_state = maxread<DWORD_PTR>(actor_pawn + GameOffset.offset_player_state);
			auto actor_mesh = maxread<DWORD_PTR>(actor_pawn + GameOffset.offset_actor_mesh);
			auto health = maxread<DWORD_PTR>(actor_pawn + GameOffset.offset_player_health);
			auto name = Game::GetNameFromFName(actor_id);
			auto tema = maxread<int>(actor_state + 0x420);
			auto pytema = maxread<int>(GameVars.local_player_state + 0x420);//或者是8A0
			if (actor_pawn == GameVars.local_player_pawn || tema == pytema || health<=0)continue;


			string result = findTargetString(name, "BP_Soldier_");//类似寻找文本

			if (name == result )
			{

				DWORD_PTR camp = maxread<BYTE>(actor_state + GameOffset.offset_player_Teme);

				DWORD_PTR playercamp = maxread<BYTE>(GameVars.local_player_pawn + GameOffset.offset_player_ATeme);



				auto Aname = Game::read_wstring(maxread<DWORD_PTR>(actor_state + GameOffset.offset_player_name));



		
				if (actor_pawn != NULL || actor_id != NULL || actor_state != NULL || actor_mesh != NULL)
				{

					EntityList Entity{ };

					Entity.PLNAME = name;
					Entity.actor_name = Aname;
					Entity.actor_camp =camp;
					Entity.actor_mesh = actor_mesh;
					Entity.actor_pawn = actor_pawn;
					Entity.actor_id = actor_id;
					Entity.actor_state = actor_state;
					tmpList.push_back(Entity);

				}
			}


		}
		entityList = tmpList;

		
		Sleep(10);
	}

}




auto RenderVisual()->VOID
{


	auto EntityList_Copy = entityList;



	for (int i = 0; i < EntityList_Copy.size(); i++)
	{
		auto Entity = EntityList_Copy[i];


		auto local_pos = maxread<Vector3>(GameVars.local_player_root + GameOffset.offset_relative_location);


		auto head_pos = Game::GetBoneWithRotation(Entity.actor_mesh, 9);
		auto bone_pos = Game::GetBoneWithRotation(Entity.actor_mesh, 0);
		auto BottomBox = Game::ProjectWorldToScreen(bone_pos);
		auto TopBox = Game::ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z + 15));
		auto entity_distance = local_pos.Distance(bone_pos);
		auto CornerHeight = abs(TopBox.y - BottomBox.y);
		auto CornerWidth = CornerHeight * 0.55;
		auto bVisible = Game::isVisible(Entity.actor_mesh);




		char dist[64];
		sprintf_s(dist, "Dist:%.fm", entity_distance);
		if (CFG.b_EspBox)
		{
			if (Entity.actor_state == 0)
			{
				DrawBox(TopBox.x - (CornerWidth / 1.9), TopBox.y, CornerWidth, CornerHeight, D2D1::ColorF::Yellow);
				DrawRenderTextA(BottomBox.x, BottomBox.y - 20, "载具上的人", D2D1::ColorF::Yellow, pTextFormatKaiTi, 11.0f);
				DrawRenderTextA(BottomBox.x, BottomBox.y, dist, D2D1::ColorF::Yellow, pTextFormatKaiTi, 11.0f);
			}
			if (Entity.actor_state != 0)
			{
				DrawBox(TopBox.x - (CornerWidth / 1.9), TopBox.y, CornerWidth, CornerHeight, D2D1::ColorF::Red);
				DrawRenderTextA(BottomBox.x, BottomBox.y - 20, Entity.actor_name.c_str(), D2D1::ColorF::Red, pTextFormatKaiTi, 11.0f);
				DrawRenderTextA(BottomBox.x, BottomBox.y, dist, D2D1::ColorF::Red, pTextFormatKaiTi, 11.0f);
			}

			//cout << Entity.actor_name.c_str() << "//" << Entity.actor_pawn<< "//"<< GameVars.local_player_pawn << endl;



		}



		


	}

}


int APIENTRY  main(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char* lpCmdLine, _In_ int nCmdShow)
{

	GameVars.dwProcessName = "SquadGame.exe";

	HWND gameHwnd = FindWindowA("UnrealWindow", "SquadGame  ");

	GetWindowThreadProcessId(gameHwnd, &GameVars.PID);
	GameVars.dwProcess_Base= GetModuleAddress(L"SquadGame.exe");
	//cout << GameVars.dwProcess_Base << endl;
	//printf("[+] ProcessName: %s ID: (%d) base: %llx\n", GameVars.dwProcessName, GameVars.dwProcessId, GameVars.dwProcess_Base);

	////ProtectProcess(GetCurrentProcessId());

	auto H = GameVars.dwProcess_Base + 0x93A4DC;
	cout << H << endl;
	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(GameCache), nullptr, NULL, nullptr);
	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(CallHacks), nullptr, NULL, nullptr);
	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(CallAimbot), nullptr, NULL, nullptr);

}
