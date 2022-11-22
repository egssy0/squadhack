#pragma once
int Function;


D3DCOLOR A;
const char* C;
int B;
bool CreateConsole = true;
void menu()
{
	  int Ainespacing = 191;
      int Linespacing =179;

	  int a = GameVars.Meshpoint;
	  char c[8];
	  _itoa(a, c, 10);



	if (CFG.b_MenuShow)
	{
	

		DrawCircle(GetSystemMetrics(SM_CXSCREEN) / 2.0f, GetSystemMetrics(SM_CYSCREEN) / 2.0f, CFG.AimbotFOV, 1, D2D1::ColorF::White, 11.0f);
		draw_boxnew(155, 191, 140,24, D2D1::ColorF::SkyBlue);
		DrawRenderTextA(115, Linespacing, "[Max 时钟]", D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);
		Ainespacing =Ainespacing + 25;
		Linespacing =Linespacing + 25;
		draw_boxnew(155, Ainespacing, 140, 24, D2D1::ColorF::SkyBlue);
		DrawRenderTextA(90, Linespacing , "玩家透视", D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);
		DrawRenderTextA(180, Linespacing, CFG.b_EspBox == 0 ? C = "[关闭]" : C = "[开启]", Function == 0 ? A = D2D1::ColorF::Red : A = D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);

		Ainespacing = Ainespacing + 25;
		Linespacing = Linespacing + 25;
		draw_boxnew(155, Ainespacing, 140, 24, D2D1::ColorF::SkyBlue);
		DrawRenderTextA(90, Linespacing, "骨骼自瞄", D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);
		DrawRenderTextA(180, Linespacing, CFG.b_aiming == 0 ? C = "[关闭]" : C = "[开启]", Function == 1 ? A = D2D1::ColorF::Red : A = D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);

		Ainespacing = Ainespacing + 25;
		Linespacing = Linespacing + 25;
		draw_boxnew(155, Ainespacing, 140, 24, D2D1::ColorF::SkyBlue);
		DrawRenderTextA(90, Linespacing, "无线子弹", D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);
		DrawRenderTextA(180, Linespacing, CFG.b_NOrecoil == 0 ? C = "[关闭]" : C = "[开启]", Function == 2 ? A = D2D1::ColorF::Red : A = D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);

		Ainespacing = Ainespacing + 25;
		Linespacing = Linespacing + 25;
		draw_boxnew(155, Ainespacing, 140, 24, D2D1::ColorF::SkyBlue);
		DrawRenderTextA(90, Linespacing, "一秒千发", D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);
		DrawRenderTextA(180, Linespacing, CFG.b_firerate == 0 ? C = "[关闭]" : C = "[开启]", Function ==3 ? A = D2D1::ColorF::Red : A = D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);


		Ainespacing = Ainespacing + 25;
		Linespacing = Linespacing + 25;
		draw_boxnew(155, Ainespacing, 140, 24, D2D1::ColorF::SkyBlue);
		DrawRenderTextA(90, Linespacing, "子弹追踪", D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);
		DrawRenderTextA(180, Linespacing, CFG.b_track == 0 ? C = "[关闭]" : C = "[开启]", Function == 4 ? A = D2D1::ColorF::Red : A = D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);


		Ainespacing = Ainespacing + 25;
		Linespacing = Linespacing + 25;
		draw_boxnew(155, Ainespacing, 140, 24, D2D1::ColorF::SkyBlue);
		DrawRenderTextA(90, Linespacing, "人物加速", D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);
		DrawRenderTextA(180, Linespacing, CFG.b_accelerate == 0 ? C = "[关闭]" : C = "[开启]", Function == 5 ? A = D2D1::ColorF::Red : A = D2D1::ColorF::White, pTextFormatKaiTi, 11.0f);


		Linespacing = Linespacing + 25;
		DrawRenderTextA(90, Linespacing, "[自瞄位置选择需要的位置会显示出数字自瞄就会瞄准那个位置，选择好后关闭自瞄位置即可]", D2D1::ColorF::Red, pTextFormatKaiTi, 11.0f);
		Linespacing = Linespacing + 25;
		DrawRenderTextA(90, Linespacing, "[O是增加,P是减少，选择好后关闭自瞄位置即可]", D2D1::ColorF::Red, pTextFormatKaiTi, 11.0f);
		Linespacing = Linespacing + 25;
		DrawRenderTextA(90, Linespacing, "[Home键显示/隐藏菜单]", D2D1::ColorF::Red, pTextFormatKaiTi, 11.0f);
		Linespacing = Linespacing + 25;
		DrawRenderTextA(90, Linespacing, "[小键盘的上下左右开启关闭功能]", D2D1::ColorF::Red, pTextFormatKaiTi, 11.0f);
		Linespacing = Linespacing + 25;
		DrawRenderTextA(90, Linespacing, "[End键安全退出 关闭游戏前请按END]", D2D1::ColorF::Red, pTextFormatKaiTi, 11.0f);

	}
	
}
//Draw_FullRect(5, 5, 300, 90, D3DCOLOR_ARGB(100, 255, 0, 0));
void functionhotkey()
{
	static int meshpoint = 1;

	if (GetAsyncKeyState(VK_UP) & 1)
	{
		if (Function <= 0)
		{
			Function = 0;
		}
		else
		{
			Function = Function - 1;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 1)
	{
		if (Function >=5)
		{
			Function = 0;
		}
		else
		{
			Function = Function + 1;
		}
	}
	if (GetAsyncKeyState(VK_HOME) & 1)
		CFG.b_MenuShow = !CFG.b_MenuShow;
	if (GetAsyncKeyState(VK_END) & 1)
	{
		Sleep(1000);//1秒
		exit(NULL);
	}
	
	if (GetAsyncKeyState(SPI_GETLOWPOWERTIMEOUT) & 1)
	{

		meshpoint = meshpoint + 1;

	}
	if (GetAsyncKeyState(SPI_GETPOWEROFFTIMEOUT) & 1)
	{

		meshpoint = meshpoint - 1;
	}
	GameVars.Meshpoint = meshpoint;

	//cout << Function << endl;
	if (GetAsyncKeyState(VK_LEFT) & 1 || GetAsyncKeyState(VK_RIGHT) & 1)
	{
		if (Function == 0)
		{
			CFG.b_EspBox = !CFG.b_EspBox;
		}
		if (Function == 1)
		{
			CFG.b_aiming = !CFG.b_aiming;
		}
		if (Function == 2)
		{
			CFG.b_NOrecoil = !CFG.b_NOrecoil;
		}
		if (Function == 3)
		{
			CFG.b_firerate = !CFG.b_firerate;
		}
		if (Function == 4)
		{
			CFG.b_track = !CFG.b_track;
		}
		if (Function == 5)
		{
			CFG.b_accelerate = !CFG.b_accelerate;
		}

		
		
	}




}
void cycle()
{


	menu();

	functionhotkey();



}


