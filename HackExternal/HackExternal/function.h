#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <dwmapi.h>
#include <string>
#include <vector>
#include "offset.h"
#include "cfg.h"
#include "Driver/driver.h"
#include "fon_font.hpp"
#include <algorithm>
#include "win_utils.h"
#include <corecrt_io.h>
#include <iostream>
#include <codecvt>




template <class T>
bool write(unsigned long long address, T buffer)
{
	return  Writeto(address, reinterpret_cast<void*>(&buffer), sizeof(T));

}






bool isVisible(DWORD_PTR mesh)//这个游戏是鼠标XY在本人下面那么他这个地方是在30这个地方那就
{
	auto sub=maxread<DWORD_PTR>(mesh + + GameOffset.offset_apawn);

	float fLastSubmitTime = maxread<float>(sub + GameOffset.offset_last_submit_time);
	float fLastRenderTimeOnScreen = maxread<float>(sub + GameOffset.offset_last_render_time);
	const float fVisionTick = 0.06f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
	return bVisible;
}

std::string RandomString(int len)
{
	srand(time(NULL));
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}



namespace Game
{


	std::string GetNameFromFName(int key)
	{
		auto chunkOffset = (UINT)((int)(key) >> 16);
		auto nameOffset = (USHORT)key;

		auto namePoolChunk = maxread<UINT64>(GameVars.dwProcess_Base + GameOffset.offset_g_names + ((chunkOffset + 2) * 8));
		auto entryOffset = namePoolChunk + (ULONG)(2 * nameOffset);
		auto nameEntry = maxread<INT16>(entryOffset);
		auto nameLength = nameEntry >> 6;
		char buff[1028];
		if ((DWORD)nameLength && nameLength > 0)
		{

			RedByte(entryOffset + 2, buff, nameLength);
			buff[nameLength] = '\0';
			return std::string(buff);
		}
		else return "";
	}

	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}



	FTransform GetBoneIndex(DWORD_PTR mesh, int index)
	{
		DWORD_PTR bonearray = maxread<DWORD_PTR>(mesh + GameOffset.offset_bone_array);
		//if(!bonearray)
		//	bonearray = maxread<DWORD_PTR>(mesh + GameOffset.offset_bone_array + 0x10);
		return maxread<FTransform>(bonearray + (index * 0x30));
	}
	bool isVisible(DWORD_PTR mesh)//这个游戏是鼠标XY在本人下面那么他这个地方是在30这个地方那就
	{
		auto sub = maxread<DWORD_PTR>(mesh + +GameOffset.offset_apawn);

		float fLastSubmitTime = maxread<float>(sub + GameOffset.offset_last_submit_time);
		float fLastRenderTimeOnScreen = maxread<float>(sub + GameOffset.offset_last_render_time);
		const float fVisionTick = 0.06f;
		bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
		return bVisible;
	}

	Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
	{
		FTransform bone = GetBoneIndex(mesh, id);
		FTransform ComponentToWorld = maxread<FTransform>(mesh + GameOffset.offset_component_to_world);
		D3DMATRIX Matrix;
		Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
		return Vector3(Matrix._41, Matrix._42, Matrix._43);
	}



	D3DMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
	{
		float radPitch = (rot.x * float(M_PI) / 180.f);
		float radYaw = (rot.y * float(M_PI) / 180.f);
		float radRoll = (rot.z * float(M_PI) / 180.f);

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix._11 = CP * CY;
		matrix._12 = CP * SY;
		matrix._13 = SP;
		matrix._14 = 0.f;

		matrix._21 = SR * SP * CY - CR * SY;
		matrix._22 = SR * SP * SY + CR * CY;
		matrix._23 = -SR * CP;
		matrix._24 = 0.f;

		matrix._31 = -(CR * SP * CY + SR * SY);
		matrix._32 = CY * SR - CR * SP * SY;
		matrix._33 = CR * CP;
		matrix._34 = 0.f;

		matrix._41 = origin.x;
		matrix._42 = origin.y;
		matrix._43 = origin.z;
		matrix._44 = 1.f;

		return matrix;
	}

	struct FMinimalViewInfo
	{
		Vector3 Location; // 0x00(0x0c)
		Vector3 Rotation; // 0x0c(0x0c)
		float FOV; // 0x18(0x04)
		float DesiredFOV; // 0x1c(0x04)
		float OrthoWidth; // 0x20(0x04)
		float OrthoNearClipPlane; // 0x24(0x04)
		float OrthoFarClipPlane; // 0x28(0x04)
		float AspectRatio; // 0x2c(0x04)
	};

	struct FCameraCacheEntry
	{
		float Timestamp; // 0x00(0x04)
		char pad_4[0xc]; // 0x04(0x0c)
		FMinimalViewInfo POV; // 0x10(0x5e0)
	};
	Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
	{
		Vector3 Screenlocation = Vector3(0, 0, 0);

		auto CameraManager = maxread<uintptr_t>(GameVars.local_player_controller + GameOffset.offset_camera_manager);
		auto CameraCache = maxread<FCameraCacheEntry>(CameraManager + GameOffset.offset_camera_cache);

		D3DMATRIX tempMatrix = Matrix(CameraCache.POV.Rotation);

		Vector3 vAxisX, vAxisY, vAxisZ;

		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 vDelta = WorldLocation - CameraCache.POV.Location;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		float FovAngle = CameraCache.POV.FOV;

		float ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2.0f;;
		float ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2.0f;;

		Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

		return Screenlocation;
	}




	const char* OperatorNames[29][6] =
	{
		// Credits Dude on UC for opnames. 
		{"AI","SMOKE","MUTE","SLEDGE","THATCHER"}, //0
		{"RECRUIT","CASTLE","ASH","PULSE","THERMITE"}, //1
		{"","DOC","ROOK","TWITCH","MONTAGNE"}, //2
		{"","GLAZ","FUZE","KAPKAN","TACHANKA"}, //3
		{"","BLITZ","IQ","JAGER","BANDIT"}, //4
		{"","BUCK","FROST"}, //5
		{"","BLACKBEARD","VALKYRIE"}, //6
		{"","CAPITAO","CAVEIRA"}, //7
		{"","HIBANA","ECHO"}, //8
		{"","JACKAL","MIRA"}, //9
		{"","YING","LESION"}, //10
		{"","ELA","ZOFIA"}, //11
		{"","DOKKAEBI","VIGIL"}, //12
		{"","","LION","FINKA"}, //13
		{"","MAESTRO","ALIBI"}, //14
		{"","MAVERICK","CLASH"}, //15
		{"","NOMAD","KAID", ""}, //16
		{"","MOZZIE","GRIDLOCK"}, //17
		{"","NOKK"}, //18
		{"","WARDEN"}, //19
		{"","GOYO"}, //20
		{"","AMARU"}, //21
		{"","KALI","WAMAI", "ACE", "ARUNI", "OSA"}, //22
		{"","ORYX", "FLORES"}, //23
		{"","IANA"}, //24
		{"","MELUSI"}, //25
		{"ZERO"}, //26
		{"THUNDERBIRD"}, //26
		{"THORN"}, // 27
	};
	//auto OpName(uintptr_t player) -> const char*
	//{
	//	uintptr_t replicationInfo = Game::ReplicationInfo(player);
	//	auto ctu = maxread<uint8_t>(replicationInfo + 0x1C0);
	//	auto op = maxread<uint8_t>(replicationInfo + 0x1C1);
	//	return OperatorNames[ctu][op];
	//}



};







DWORD GetProcessIDByName(const char* pName)//取自己ID
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {

		char tmpStr[800];
		sprintf_s(tmpStr, "%S", pe.szExeFile);
		if (strcmp(tmpStr, pName) == 0) {
			CloseHandle(hSnapshot);
			return pe.th32ProcessID;
		}
		//printf("%-6d %s\n", pe.th32ProcessID, pe.szExeFile);
	}
	CloseHandle(hSnapshot);
	return 0;
}




void move_to(float x, float y)
{
	float center_x = GameVars.ScreenWidth / 2;
	float center_y = GameVars.ScreenHeight / 2;

	float smooth = CFG.Smoothing;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(target_x), static_cast<DWORD>(target_y), 0, 0);
}
