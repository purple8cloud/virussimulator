#pragma once
#include "header.h"

bool GameStruct::Setup(HWND hWnd)
{
	//seed = time(NULL);
	KeyMaster::Setup();
	MapMaster::Setup();
	MathMaster::Setup();
	ObjectMaster::Setup();
	TimeMaster::Setup();
	VirusSimulator::Setup();
	srand(seed);
	g_hWnd = hWnd;
	SetScrollRange(g_hWnd, SB_HORZ, 0, GameStruct::MapMaster::image.rows, false);
	SetScrollRange(g_hWnd, SB_VERT, 0, GameStruct::MapMaster::image.cols, false);
	SetScrollPos(GameStruct::g_hWnd, SB_HORZ, GameStruct::MapMaster::image.rows / 2, false);
	SetScrollPos(GameStruct::g_hWnd, SB_VERT, GameStruct::MapMaster::image.cols / 2, false);
	INFECTION_DATA ifd;
	ifd.active = false;
	ifd.fatal_time = VirusSimulator::fataltime;
	//ifd.incubation_period = 1*2*24;
	ifd.incubation_period = VirusSimulator::incubateperiod;
	//ifd.infect_radius = 0.2524;//10m
	//ifd.infect_radius = 1;//40m
	ifd.infect_radius = VirusSimulator::infectionradius;
	ifd.positive = false;
	renderpos.x = VirusSimulator::centerpos[VirusSimulator::start_space].x - client_rect.right/2;
	renderpos.y = VirusSimulator::centerpos[VirusSimulator::start_space].y- client_rect.bottom/2;

	double tx, ty;
	int cnt = 0;
	for (int _city = 0; _city < 18; ++_city)
	{

		for (int popu = 0; popu < VirusSimulator::population_movement[_city + 1][2]; ++popu)
		{
			tx = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.cols;
			if (tx == MapMaster::image.cols)
				--tx;
			ty = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.rows;
			if (ty == MapMaster::image.rows)
				--ty;
			if (MapMaster::boxs[(int)ty][(int)tx] == 0 || !(255 - MapMaster::boxs[(int)ty][(int)tx] >= VirusSimulator::city[_city].first && 255 - MapMaster::boxs[(int)ty][(int)tx] <= VirusSimulator::city[_city].second))
			{
				--popu; continue;
			}
			else {
				GameStruct::ObjectMaster::MakeObject(new Unit(cnt, 255 - MapMaster::boxs[(int)ty][(int)tx], Unit::_pattern::sSsT, ifd, tx, ty));
				++cnt;
			}
		}

		for (int popu = 0; popu < VirusSimulator::population_movement[_city + 1][3]; ++popu)
			//for (int popu = 0; popu < 1; ++popu)
		{
			tx = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.cols;
			if (tx == MapMaster::image.cols)
				--tx;
			ty = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.rows;
			if (ty == MapMaster::image.rows)
				--ty;
			if (MapMaster::boxs[(int)ty][(int)tx] == 0 || !(255 - MapMaster::boxs[(int)ty][(int)tx] >= VirusSimulator::city[_city].first && 255 - MapMaster::boxs[(int)ty][(int)tx] <= VirusSimulator::city[_city].second))
			{
				--popu; continue;
			}
			else {
				GameStruct::ObjectMaster::MakeObject(new Unit(cnt, 255 - MapMaster::boxs[(int)ty][(int)tx], Unit::_pattern::sSdT, ifd, tx, ty));
				++cnt;
			}
		}


		for (int popu = 0; popu < VirusSimulator::population_movement[_city + 1][4]; ++popu)
		{
			tx = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.cols;
			if (tx == MapMaster::image.cols)
				--tx;
			ty = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.rows;
			if (ty == MapMaster::image.rows)
				--ty;
			if (MapMaster::boxs[(int)ty][(int)tx] == 0 || !(255 - MapMaster::boxs[(int)ty][(int)tx] >= VirusSimulator::city[_city].first && 255 - MapMaster::boxs[(int)ty][(int)tx] <= VirusSimulator::city[_city].second))
			{
				--popu; continue;
			}
			else {
				GameStruct::ObjectMaster::MakeObject(new Unit(cnt, 255 - MapMaster::boxs[(int)ty][(int)tx], Unit::_pattern::dS, ifd, tx, ty));
				++cnt;
			}
		}

		for (int popu = 0; popu < VirusSimulator::population_movement[_city + 1][5]; ++popu)
		{
			tx = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.cols;
			if (tx == MapMaster::image.cols)
				--tx;
			ty = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.rows;
			if (ty == MapMaster::image.rows)
				--ty;
			if (MapMaster::boxs[(int)ty][(int)tx] == 0 || !(255 - MapMaster::boxs[(int)ty][(int)tx] >= VirusSimulator::city[_city].first && 255 - MapMaster::boxs[(int)ty][(int)tx] <= VirusSimulator::city[_city].second))
			{
				--popu; continue;
			}
			else {
				GameStruct::ObjectMaster::MakeObject(new Unit(cnt, 255 - MapMaster::boxs[(int)ty][(int)tx], Unit::_pattern::otherplace, ifd, tx, ty));
				++cnt;
			}
		}

		for (int popu = 0; popu < VirusSimulator::population_movement[_city + 1][6]; ++popu)
		{
			tx = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.cols;
			if (tx == MapMaster::image.cols)
				--tx;
			ty = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.rows;
			if (ty == MapMaster::image.rows)
				--ty;
			if (MapMaster::boxs[(int)ty][(int)tx] == 0 || !(255 - MapMaster::boxs[(int)ty][(int)tx] >= VirusSimulator::city[_city].first && 255 - MapMaster::boxs[(int)ty][(int)tx] <= VirusSimulator::city[_city].second))
			{
				--popu; continue;
			}
			else {
				GameStruct::ObjectMaster::MakeObject(new Unit(cnt, 255 - MapMaster::boxs[(int)ty][(int)tx], Unit::_pattern::unknown, ifd, tx, ty));
				++cnt;
			}
		}

		for (int popu = 0; popu < VirusSimulator::population_movement[_city + 1][7]; ++popu)
		{
			tx = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.cols;
			if (tx == MapMaster::image.cols)
				--tx;
			ty = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.rows;
			if (ty == MapMaster::image.rows)
				--ty;
			if (MapMaster::boxs[(int)ty][(int)tx] == 0 || !(255 - MapMaster::boxs[(int)ty][(int)tx] >= VirusSimulator::city[_city].first && 255 - MapMaster::boxs[(int)ty][(int)tx] <= VirusSimulator::city[_city].second))
			{
				--popu; continue;
			}
			else {
				GameStruct::ObjectMaster::MakeObject(new Unit(cnt, 255 - MapMaster::boxs[(int)ty][(int)tx], Unit::_pattern::nomove, ifd, tx, ty));
				++cnt;
			}
		}

		for (int popu = 0; popu < VirusSimulator::population_movement[_city + 1][9]; ++popu)
		{
			tx = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.cols;
			if (tx == MapMaster::image.cols)
				--tx;
			ty = ((double)rand() / RAND_MAX)*(double)GameStruct::MapMaster::image.rows;
			if (ty == MapMaster::image.rows)
				--ty;
			if (MapMaster::boxs[(int)ty][(int)tx] == 0 || !(255 - MapMaster::boxs[(int)ty][(int)tx] >= VirusSimulator::city[_city].first && 255 - MapMaster::boxs[(int)ty][(int)tx] <= VirusSimulator::city[_city].second))
			{
				--popu; continue;
			}
			else {
				GameStruct::ObjectMaster::MakeObject(new Unit(cnt, 255 - MapMaster::boxs[(int)ty][(int)tx], Unit::_pattern::underage, ifd, tx, ty));
				++cnt;
			}
		}


	}
	for (int i = 0; i < MAXOBJECT; i += 100)
	{
		if (((Unit*)GameStruct::ObjectMaster::objects[i])->regionnum == VirusSimulator::start_space)
		{
			((Unit*)GameStruct::ObjectMaster::objects[i])->infection_data.positive = true;
			break;
		}
	}

	

	GameStruct::renderthread = thread([&]() {GameStruct::Render();

	/*wchar_t ch[255];
	::swprintf(ch, 255, L"render end");
	OutputDebugString(ch); */});
	GameStruct::movethread = thread([&]() {

		while (GameStruct::state != GameStruct::State::END)
		{
			Sleep(10);
			++GameStruct::TimeMaster::movecount;
			if (TimeMaster::movecount % 2 == 0)
			{
				++TimeMaster::hour;
				if (TimeMaster::hour == 24)
				{
					TimeMaster::hour = 0;
					++TimeMaster::day;

				}
			}

			/*wchar_t ch[255];
			::swprintf(ch, 255, L"movecnt:%lld", GameStruct::TimeMaster::movecount);
			OutputDebugString(ch);*/
			boxmap_mtx.lock();
			for (int i = 0; i < MAXOBJECT; ++i)
			{
				if (GameStruct::ObjectMaster::objects[i] != NULL)
					GameStruct::ObjectMaster::objects[i]->Move();
			}
			boxmap_mtx.unlock();

			for (int i = 0; i < 9; ++i)
			{
				if (VirusSimulator::infectionpercent[i] == -1)
				{
					if (VirusSimulator::infectedpopulation >= MAXOBJECT*0.1*(i + 1))
						VirusSimulator::infectionpercent[i] = TimeMaster::movecount;
					break;
				}
			}
			if (TimeMaster::movecount % 48 == 0)
			{
				char fn[500];
				snprintf(fn, sizeof(fn), ".\\capture_%d_%lf_%d_%d_%d", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime);

				mkdir(fn);

				char file_name[256];
				sprintf(file_name, ".\\capture_%d_%lf_%d_%d_%d\\result_%d.txt", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime, time(NULL));
				ofstream outFile(file_name);
				outFile << "seed = " << GameStruct::seed << endl;
				outFile << "setting = " << GameStruct::VirusSimulator::infectionradius << " " << GameStruct::VirusSimulator::incubateperiod << " " << GameStruct::VirusSimulator::start_space << " " << GameStruct::VirusSimulator::fataltime << endl;
				outFile << "------roadrank_posi------\n";
				for (int i = 0; i < 120; ++i)
				{
					for (int j = 0; j < 120; ++j)
					{
						outFile << GameStruct::VirusSimulator::roadrank_posi[i][j] << " ";
					}
					outFile << endl;
				}
				outFile << "\n-----roadrank_acti-----\n";
				for (int i = 0; i < 120; ++i)
				{
					for (int j = 0; j < 120; ++j)
					{
						outFile << GameStruct::VirusSimulator::roadrank_acti[i][j] << " ";
					}
					outFile << endl;
				}
				outFile << "\n-----roadrank_nega-----\n";
				for (int i = 0; i < 120; ++i)
				{
					for (int j = 0; j < 120; ++j)
					{
						outFile << GameStruct::VirusSimulator::roadrank_nega[i][j] << " ";
					}
					outFile << endl;
				}
				outFile << "\n-----roadrank_current-----\n";
				for (int i = 0; i < 120; ++i)
				{
					for (int j = 0; j < 120; ++j)
					{
						outFile << GameStruct::VirusSimulator::roadrank_acti[i][j] + GameStruct::VirusSimulator::roadrank_posi[i][j] + GameStruct::VirusSimulator::roadrank_nega[i][j] << " ";
					}
					outFile << endl;
				}
				outFile << "\n---------------------\n";
				outFile << "movecount : " << GameStruct::TimeMaster::movecount << endl;
				outFile << "normal : " << GameStruct::VirusSimulator::normal << endl;
				outFile << "unborn : " << GameStruct::VirusSimulator::unborn << endl;
				outFile << "outbreaker : " << GameStruct::VirusSimulator::outbreaker << endl;
				outFile << "dead : " << GameStruct::VirusSimulator::dead << endl;
				outFile << "infectionout : " << GameStruct::VirusSimulator::infectionout << endl;
				outFile << "infectedpopulation : " << GameStruct::VirusSimulator::infectedpopulation << endl;
				outFile << "infection_by_acti : " << GameStruct::VirusSimulator::infection_by_acti << endl;
				outFile << "infection_by_posi : " << GameStruct::VirusSimulator::infection_by_posi << endl;
				outFile << "infectionpercent : " << endl;
				for (int i = 0; i < 9; ++i)
				{
					outFile << (i + 1) * 10 << "퍼센트 감염된 시간 : " << GameStruct::VirusSimulator::infectionpercent[i] << endl;
				}
				outFile.close();
			}


		}





	}

	);
	//GameStruct::movethread.detach();

	return 0;
};

bool GameStruct::ClearAll()
{
	for (int i = 0; i < MAXOBJECT; ++i)
	{
		if (GameStruct::ObjectMaster::objects[i] != NULL)
			GameStruct::ObjectMaster::objects[i]->Remove();
	}

	return true;
}


void GameStruct::Menu_Process()
{
	GameStruct::TimeMaster::UpdateTime();

	int loop = GameStruct::TimeMaster::delta_tmp.count() * GameStruct::TimeMaster::invers_gamespeed;
	for (int i = 0; i < loop; ++i)
	{
		GameStruct::TimeMaster::movecount++;
		for (int i = 0; i < MAXOBJECT; ++i)
		{
			if (GameStruct::ObjectMaster::objects[i] != NULL)
				GameStruct::ObjectMaster::objects[i]->Move();
		}

		if (GameStruct::KeyMaster::input[VK_BACK])
			DestroyWindow(GameStruct::g_hWnd);
	}

	GameStruct::MouseMaster::Resetclicked();
	InvalidateRect(GameStruct::g_hWnd, NULL, false);
}

void GameStruct::Ingame_Process()
{
	GameStruct::TimeMaster::UpdateTime();
	int loop = GameStruct::TimeMaster::delta_tmp.count() * GameStruct::TimeMaster::invers_gamespeed;
	if (GameStruct::KeyMaster::clicked[VK_LEFT])
		renderpos.x -= 100;
	if (GameStruct::KeyMaster::clicked[VK_RIGHT])
		renderpos.x += 100;
	if (GameStruct::KeyMaster::clicked[VK_UP])
		renderpos.y -= 100;
	if (GameStruct::KeyMaster::clicked[VK_DOWN])
		renderpos.y += 100;
	if (GameStruct::KeyMaster::clicked['R'])
	{
		if (render_on)
			render_on = false;
		else render_on = true;
	}
	if (GameStruct::KeyMaster::clicked['C'])
	{
		if (capture_on)
			capture_on = false;
		else capture_on = true;
	}
	if (GameStruct::KeyMaster::clicked['W'])
	{
		char fn[500];
		snprintf(fn, sizeof(fn), ".\\capture_%d_%lf_%d_%d_%d", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime);

		mkdir(fn);

		char file_name[256];
		sprintf(file_name, ".\\capture_%d_%lf_%d_%d_%d\\result_%d.txt", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime,time(NULL));
		ofstream outFile(file_name);
		outFile << "seed = " << GameStruct::seed << endl;
		outFile << "setting = " << GameStruct::VirusSimulator::infectionradius << " " << GameStruct::VirusSimulator::incubateperiod << " " << GameStruct::VirusSimulator::start_space << " " << GameStruct::VirusSimulator::fataltime << endl;
		outFile << "------roadrank_posi------\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_posi[i][j] << " ";
			}
			outFile << endl;
		}
		outFile << "\n-----roadrank_acti-----\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_acti[i][j] << " ";
			}
			outFile << endl;
		}
		outFile << "\n-----roadrank_nega-----\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_nega[i][j] << " ";
			}
			outFile << endl;
		}
		outFile << "\n-----roadrank_current-----\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_acti[i][j] + GameStruct::VirusSimulator::roadrank_posi[i][j] + GameStruct::VirusSimulator::roadrank_nega[i][j] << " ";
			}
			outFile << endl;
		}
		outFile << "\n---------------------\n";
		outFile << "movecount : " << GameStruct::TimeMaster::movecount << endl;
		outFile << "normal : " << GameStruct::VirusSimulator::normal << endl;
		outFile << "unborn : " << GameStruct::VirusSimulator::unborn << endl;
		outFile << "outbreaker : " << GameStruct::VirusSimulator::outbreaker << endl;
		outFile << "dead : " << GameStruct::VirusSimulator::dead << endl;
		outFile << "infectionout : " << GameStruct::VirusSimulator::infectionout << endl;
		outFile << "infectedpopulation : " << GameStruct::VirusSimulator::infectedpopulation << endl;
		outFile << "infection_by_acti : " << GameStruct::VirusSimulator::infection_by_acti << endl;
		outFile << "infection_by_posi : " << GameStruct::VirusSimulator::infection_by_posi << endl;
		outFile << "infectionpercent : " << endl;
		for (int i = 0; i < 9; ++i)
		{
			outFile << (i + 1) * 10 << "퍼센트 감염된 시간 : " << GameStruct::VirusSimulator::infectionpercent[i] << endl;
		}
		outFile.close();
	}
	//wchar_t ch[255];
	//swprintf(ch, 255, L"deltatime:%lf loop : %d\n", GameStruct::TimeMaster::delta_tmp.count(), loop);
	//OutputDebugString(ch);
	
	loop = 1;
	//if (!GameStruct::TimeMaster::paused)
		/*for (int i = 0; i < loop; ++i)
		{
		++GameStruct::TimeMaster::movecount;
		for (int i = 0; i < MAXOBJECT; ++i)
		{
		if (GameStruct::ObjectMaster::objects[i] != NULL)
		GameStruct::ObjectMaster::objects[i]->Move();
		}

		}*/
		
		/*if (GameStruct::KeyMaster::input[VK_BACK])
		{
		DestroyWindow(GameStruct::g_hWnd);
		}
		*/
		if ((VirusSimulator::infectedpopulation > MAXOBJECT*0.9) || (VirusSimulator::unborn == 0))
			DestroyWindow(g_hWnd);
		if (GameStruct::KeyMaster::clicked[VK_ESCAPE])
		{
			if (GameStruct::TimeMaster::paused)
				GameStruct::TimeMaster::Restart();
			else GameStruct::TimeMaster::Pause();
		}
	GameStruct::MouseMaster::Resetclicked();
	GameStruct::KeyMaster::Resetclicked();
	
	//InvalidateRect(GameStruct::g_hWnd, NULL, false);
};

void GameStruct::Render()
{
	PAINTSTRUCT ps;
	HDC hdc;
	HDC back_hdc;
	HBITMAP back_bitmap;
	HBITMAP old_back_bitmap;
	HPEN back_null_pen;
	HPEN old_pen;

	int start;
	wchar_t ch[255];
	
	bool capture = false;
	
	//renderpos.x = MapMaster::image.cols/2; 
	//renderpos.y = MapMaster::image.rows / 2;
	while (GameStruct::state != GameStruct::State::END || lastrender)
	{
		//Sleep(100);
		//renderpos.x = (GameStruct::MouseMaster::coord.x / client_rect.right)*MapMaster::image.cols;
		//renderpos.y = (GameStruct::MouseMaster::coord.y / client_rect.bottom)*MapMaster::image.rows;

		capture = (capture_on&&TimeMaster::hour == 0);
		
		hdc = BeginPaint(GameStruct::g_hWnd, &ps);
		back_hdc = CreateCompatibleDC(hdc);
		
		if (capture || lastrender)
		{
			back_bitmap = CreateCompatibleBitmap(hdc, MapMaster::image.cols, MapMaster::image.rows);
		}
		else back_bitmap = CreateCompatibleBitmap(hdc, client_rect.right, client_rect.bottom);
		
		
		old_back_bitmap = (HBITMAP)SelectObject(back_hdc, back_bitmap);
		//back_null_pen = CreatePen(PS_ENDCAP_MASK, 0, 0);
		//old_pen = (HPEN)SelectObject(back_hdc, back_null_pen);
		//SetROP2(back_hdc, R2_NOT);
		//SetROP2(back_hdc, SRCCOPY);

		GetClientRect(g_hWnd, &client_rect);
		//start = hsi.nPos;//릴리즈에서 작동X
		start = renderpos.x;
		if (start < 0) start = 0;
		//if (GameStruct::TimeMaster::movecount % (uint64_t)2 == 0)
		if (capture || lastrender)
		{
			boxmap_mtx.lock();
			for (int x = 0; x < GameStruct::MapMaster::image.cols; ++x)
			{

				//start = renderpos.y;
				for (int y = 0; y < GameStruct::MapMaster::image.rows; ++y)
				{
					SetPixel(back_hdc, x, y, RGB(0, 0, GameStruct::MapMaster::boxs[y][x]));

					auto itrange = boxmap.equal_range(make_pair(x, y));
					if (itrange.first == itrange.second)
						continue;

					SetPixel(back_hdc, x, y, RGB(255, 255, 0));
					for (auto it = itrange.first; it != itrange.second; ++it)
					{
						if (((Unit*)it->second)->vanish)
							SetPixel(back_hdc, x, y, RGB(0, 0, 0));
						else
							if (((Unit*)it->second)->infection_data.positive)
							{
								if (((Unit*)it->second)->infection_data.active)
								{
									if (((Unit*)it->second)->alive)
										SetPixel(back_hdc, x, y, RGB(255, 0, 0));
									else SetPixel(back_hdc, x , y , RGB(122, 122, 122));

								}
								else
									SetPixel(back_hdc, x, y , RGB(0, 255, 0));
								break;
							}
					}

				}
			}



			boxmap_mtx.unlock();
			lastrender = false;
		}
		else
		if (render_on)
		{
			boxmap_mtx.lock();
			for (int x = start; x < GameStruct::client_rect.right + renderpos.x &&x < GameStruct::MapMaster::image.cols; ++x)
			{

				//start = renderpos.y;
				start = renderpos.y;

				if (start < 0) start = 0;
				for (int y = start; y < GameStruct::client_rect.bottom + renderpos.y&& y < GameStruct::MapMaster::image.rows; ++y)
				{
					SetPixel(back_hdc, x - renderpos.x, y - renderpos.y, RGB(0, 0, GameStruct::MapMaster::boxs[y][x]));

					auto itrange = boxmap.equal_range(make_pair(x, y));
					if (itrange.first == itrange.second)
						continue;
					
					SetPixel(back_hdc, x - renderpos.x, y - renderpos.y, RGB(255, 255, 0));
					for (auto it = itrange.first; it != itrange.second; ++it)
					{
						if (((Unit*)it->second)->vanish)
							SetPixel(back_hdc, x - renderpos.x, y - renderpos.y, RGB(0, 0, 0));
						else
						if (((Unit*)it->second)->infection_data.positive)
						{
							if (((Unit*)it->second)->infection_data.active)
							{
								if (((Unit*)it->second)->alive)
									SetPixel(back_hdc, x - renderpos.x, y - renderpos.y, RGB(255, 0, 0));
								else SetPixel(back_hdc, x - renderpos.x, y - renderpos.y, RGB(122, 122, 122));

							}
							else
								SetPixel(back_hdc, x - renderpos.x, y - renderpos.y, RGB(0, 255, 0));
							break;
						}
					}

				}
			}
		
		
		
		boxmap_mtx.unlock();
		
		}
		::swprintf(ch, sizeof(ch), L"movecnt:%lld | day = %d | render : %d | capture : %d", GameStruct::TimeMaster::movecount,GameStruct::TimeMaster::day,GameStruct::render_on,GameStruct::capture_on);

		TextOut(back_hdc, 0, 0, ch, sizeof(ch));
		DeleteObject(ready_bitmap);
		ready_bitmap = (HBITMAP)CopyImage(back_bitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		SelectObject(back_hdc, old_back_bitmap);
		
		//SelectObject(back_hdc, old_pen);
		//DeleteObject(back_null_pen);
		DeleteObject(back_bitmap);
		DeleteDC(back_hdc);
		EndPaint(GameStruct::g_hWnd, &ps);
		
		if (capture||lastrender)
		{
			char fn[500];
			snprintf(fn, sizeof(fn), ".\\capture_%d_%lf_%d_%d_%d", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime);

			mkdir(fn);
			snprintf(fn, sizeof(fn), ".\\capture_%d_%lf_%d_%d_%d\\day_%d.bmp", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime, GameStruct::TimeMaster::day);
			
			SaveBitmap(fn, ready_bitmap);
			
		}
	}
};


void GameStruct::TimeMaster::Pause()
{
	delta_tmp = delta_time;
	paused = true;
};
void GameStruct::TimeMaster::Restart()
{

	prev_t = chrono::system_clock::now();
	//prev_t = system_clock::from_time_t(current_time.count());
	paused = false;
}

bool GameStruct::ObjectMaster::MakeObject(Object * object)
{
	if (avaliableindex.empty())
	{
		delete object;
		return false;
	}
	int unusingindex = avaliableindex.front();
	avaliableindex.pop();
	object->index = unusingindex;

	objects[unusingindex] = object;
	//MapMaster::boxmap.insert(boxmap_pair(coordpair(object->coord.x, object->coord.y), object));
	//MapMaster::boxmap.insert(make_pair(make_pair((int)object->coord.x, (int)object->coord.y), object));
	boxmap.insert(pair<pair<int, int>, Object*>(make_pair((int)object->coord.x, (int)object->coord.y), object));
	//MapMaster::boxmap.insert(pair<pair<int, int>, Object*>(make_pair(1, 1), nullptr));
	return true;
}


Unit::Unit(int unum,int rnum,Unit::_pattern pat, INFECTION_DATA& ifd, double x, double y)
{
	unitnumber = unum;
	infection_data = ifd;
	regionnum = rnum;
	origin_regionnum = rnum;
	pattern = pat;
	pre_coord.x = coord.x = x;
	pre_coord.y = coord.y = y;
	angle = rand() % 360;
	speed = 50;
}
void Unit::Move()
{
	//boxmap_mtx.lock();
	if (infection_data.positive && !infection_data.active)
	{
		--infection_data.incubation_period;
		if (infection_data.incubation_period < 0)
		{
			infection_data.active = true;
			--GameStruct::VirusSimulator::unborn;
			++GameStruct::VirusSimulator::outbreaker;
		}
	}

	if (infection_data.positive && !vanish)
	{
		if (!alive)
			return;
		if(infection_data.active)
			--infection_data.fatal_time;
		if (infection_data.fatal_time < 0)
		{
			alive = false;
			++GameStruct::VirusSimulator::dead;
			--GameStruct::VirusSimulator::outbreaker;
		}
		D_COORD Pts[4];
		/*
		coord.x += cos(GameStruct::MathMaster::DegreeToRadian(angle))*speed;
		coord.y += sin(GameStruct::MathMaster::DegreeToRadian(angle))*speed;
		*/
		Pts[0].x = coord.x + cos(GameStruct::MathMaster::DegreeToRadian(angle + 90))*infection_data.infect_radius;
		Pts[0].y = coord.y + sin(GameStruct::MathMaster::DegreeToRadian(angle + 90))*infection_data.infect_radius;
		Pts[1].x = coord.x + cos(GameStruct::MathMaster::DegreeToRadian(angle - 90))*infection_data.infect_radius;
		Pts[1].y = coord.y + sin(GameStruct::MathMaster::DegreeToRadian(angle - 90))*infection_data.infect_radius;
		Pts[2].x = pre_coord.x + cos(GameStruct::MathMaster::DegreeToRadian(angle - 90))*infection_data.infect_radius;
		Pts[2].y = pre_coord.y + sin(GameStruct::MathMaster::DegreeToRadian(angle - 90))*infection_data.infect_radius;
		Pts[3].x = pre_coord.x + cos(GameStruct::MathMaster::DegreeToRadian(angle + 90))*infection_data.infect_radius;
		Pts[3].y = pre_coord.y + sin(GameStruct::MathMaster::DegreeToRadian(angle + 90))*infection_data.infect_radius;


		for (int dx = -2; dx <= 2; ++dx)
			for (int dy = -2; dy <= 2; ++dy)
			{
				auto itrange = boxmap.equal_range(make_pair((int)floor(coord.x + dx), (int)floor(coord.y + dy)));
				for (auto it = itrange.first; it != itrange.second; ++it)
				{
					if (((Unit*)it->second)->vanish) continue;
					double length;
					length = sqrt(pow(it->second->coord.x - coord.x, 2) + pow(it->second->coord.y - coord.y, 2));
					if (length < infection_data.infect_radius)
					{

						if (((Unit*)it->second)->infection_data.positive == false)
						{
							((Unit*)it->second)->infection_data.positive = true;
							++GameStruct::VirusSimulator::infectedpopulation;
							++GameStruct::VirusSimulator::unborn;
							--GameStruct::VirusSimulator::normal;
							if (infection_data.active)
								++GameStruct::VirusSimulator::infection_by_acti;
							else ++GameStruct::VirusSimulator::infection_by_posi;
						}
						/*
						double percent = (length / infection_data.infect_radius) * 100;
						if (rand() % 100 > percent)
						{
							((Unit*)it->second)->infection_data.positive = true;
							++GameStruct::VirusSimulator::infectedpopulation;
						}
						*/
					}
					else {
						
						length = sqrt(pow(it->second->coord.x - pre_coord.x, 2) + pow(it->second->coord.y - pre_coord.y, 2));
						if (length < infection_data.infect_radius)
						{
							if (((Unit*)it->second)->infection_data.positive == false)
							{
								((Unit*)it->second)->infection_data.positive = true;
								++GameStruct::VirusSimulator::infectedpopulation;
								++GameStruct::VirusSimulator::unborn;
								--GameStruct::VirusSimulator::normal;
								if (infection_data.active)
									++GameStruct::VirusSimulator::infection_by_acti;
								else ++GameStruct::VirusSimulator::infection_by_posi;
							}
							/*
							double percent = (length / infection_data.infect_radius) * 100;
							if (rand() % 100 > percent)
							{
							((Unit*)it->second)->infection_data.positive = true;
							++GameStruct::VirusSimulator::infectedpopulation;
							}
							*/
						}
						else if(GameStruct::MathMaster::Ptin4Pts(it->second->coord, Pts))
						{
							if (((Unit*)it->second)->infection_data.positive == false)
							{
								((Unit*)it->second)->infection_data.positive = true;
								++GameStruct::VirusSimulator::infectedpopulation;
								++GameStruct::VirusSimulator::unborn;
								--GameStruct::VirusSimulator::normal;
								if (infection_data.active)
									++GameStruct::VirusSimulator::infection_by_acti;
								else ++GameStruct::VirusSimulator::infection_by_posi;
							}
						}
					}
				}
			}
	}
	
	
	

	auto itrange = boxmap.equal_range(make_pair((int)floor(coord.x), (int)floor(coord.y)));
	for (auto it = itrange.first; it != itrange.second; ++it)
	{
		if (((Unit*)(it->second))->unitnumber == unitnumber)
		{
			boxmap.erase(it);
			break;
		}
	}



	if (migrating == true)
	{
		++movetime;
		/*if (movetime == dis[destination])
		{
			migrating = false;
		}*/
		if (regionnum == destination)
			migrating = false;
		else
		for (int i = 0;path[i] != -1; ++i)
		{
			if (movetime == dis[path[i]])
			{
				if (infection_data.active)
				{
					++GameStruct::VirusSimulator::roadrank_acti[regionnum][path[i]];
					++GameStruct::VirusSimulator::roadrank_acti[path[i]][regionnum];

				}
				else
				if (infection_data.positive)
				{
					++GameStruct::VirusSimulator::roadrank_posi[regionnum][path[i]];
					++GameStruct::VirusSimulator::roadrank_posi[path[i]][regionnum];

				}
				else
				{
					++GameStruct::VirusSimulator::roadrank_nega[regionnum][path[i]];
					++GameStruct::VirusSimulator::roadrank_nega[path[i]][regionnum];
				}

				regionnum = path[i];
				pre_coord.x = coord.x = GameStruct::VirusSimulator::centerpos[regionnum].x + rand() % 30 - 15;
				pre_coord.y = coord.y = GameStruct::VirusSimulator::centerpos[regionnum].y + rand() % 30 - 15;
				break;
			}
		}
	}
	
	if (GameStruct::TimeMaster::movecount % 2 == 0)
	if (GameStruct::TimeMaster::hour == 7)
	{
		switch (pattern)
		{
		case _pattern::sSsT:
			angle = rand()%20 -10 + atan2(GameStruct::VirusSimulator::centerpos[regionnum].y - coord.y, GameStruct::VirusSimulator::centerpos[regionnum].x - coord.x) * 180 / 3.14;
			break;
		case _pattern::sSdT:
		{
			int _city;
			for (int i = 0; i < 18; ++i)
				if (regionnum >= GameStruct::VirusSimulator::city[i].first && regionnum <= GameStruct::VirusSimulator::city[i].second)
				{
					_city = i;
					break;
				}

			if (GameStruct::VirusSimulator::city[_city].second == GameStruct::VirusSimulator::city[_city].first)
				angle = rand() % 20 - 10 + atan2(GameStruct::VirusSimulator::centerpos[regionnum].y - coord.y, GameStruct::VirusSimulator::centerpos[regionnum].x - coord.x) * 180 / 3.14;
			else {
				migrating = true;

				do {
					destination = GameStruct::VirusSimulator::city[_city].first + rand() % (GameStruct::VirusSimulator::city[_city].second - GameStruct::VirusSimulator::city[_city].first);
				} while (destination == origin_regionnum);
				GameStruct::VirusSimulator::Path_finder(origin_regionnum, destination, this);
				movetime = 0;
			}
		}
			break;
		case _pattern::dS:
		{
			int _city;
			for (int i = 0; i < 18; ++i)
				if (regionnum >= GameStruct::VirusSimulator::city[i].first && regionnum <= GameStruct::VirusSimulator::city[i].second)
				{
					_city = i;
					break;
				}
			migrating = true;

			do {
				destination = rand() %120;
			} while (destination >= GameStruct::VirusSimulator::city[_city].first&&destination <= GameStruct::VirusSimulator::city[_city].second);
			GameStruct::VirusSimulator::Path_finder(origin_regionnum, destination, this);
			movetime = 0;

		}
			break;
		case _pattern::otherplace:
			if(infection_data.positive)
				++GameStruct::VirusSimulator::infectionout;
			vanish = true;
			break;
		case _pattern::unknown:
			break;
		case _pattern::nomove:
			break;
		case _pattern::underage:
			break;

		default:
			break;
		}
	}
	else if (GameStruct::TimeMaster::hour == 20)
	{

		switch (pattern)
		{
		case _pattern::sSsT:
			angle = rand() % 30 - 15 + atan2(GameStruct::VirusSimulator::centerpos[regionnum].y - coord.y, GameStruct::VirusSimulator::centerpos[regionnum].x - coord.x) * 180 / 3.14;
			break;
		case _pattern::sSdT:
		{

			migrating = true;

			destination = origin_regionnum;
			GameStruct::VirusSimulator::Path_finder(regionnum, destination, this);
			movetime = 0;

		}
		break;
		case _pattern::dS:
		{
			migrating = true;
      
			destination = origin_regionnum;
			GameStruct::VirusSimulator::Path_finder(regionnum, destination, this);
			movetime = 0;

		}
		break;
		case _pattern::otherplace:
			vanish = false;
			break;
		case _pattern::unknown:
			break;
		case _pattern::nomove:
			break;
		case _pattern::underage:
			break;

		default:
			break;
		}
	}
	else if (GameStruct::TimeMaster::hour == 24)
	{
		angle = rand() % 30 - 15 + atan2(GameStruct::VirusSimulator::centerpos[regionnum].y - coord.y, GameStruct::VirusSimulator::centerpos[regionnum].x - coord.x) * 180 / 3.14;
	}

	while (1)
	{
		pre_coord = coord;
		coord.x += cos(GameStruct::MathMaster::DegreeToRadian(angle))*speed;
		coord.y += sin(GameStruct::MathMaster::DegreeToRadian(angle))*speed;
		if (((coord.x < GameStruct::MapMaster::image.cols && coord.x >0) && (coord.y < GameStruct::MapMaster::image.rows && coord.y >0)))
		{

			if (GameStruct::MapMaster::boxs[(int)coord.y][(int)coord.x] != 255 - regionnum)
			{
				coord = pre_coord;
				angle = rand() % 360;
				/*
				angle += 180;
				if (angle > 360)
					angle -= 360;
					*/
			}
			else break;
		}
		else
		{
			coord = pre_coord;
			angle = rand() % 360;
		}
	}
	boxmap.insert(make_pair(make_pair<int,int>((int)floor(coord.x), (int)floor(coord.y)), this));
	//boxmap_mtx.unlock();
}

void Unit::Draw(HDC& hdc)
{
	if (vanish) return;
	SCROLLINFO vsi;
	SCROLLINFO hsi;
	GetScrollInfo(GameStruct::g_hWnd, SB_VERT, &vsi);
	GetScrollInfo(GameStruct::g_hWnd, SB_HORZ, &hsi);
	SetPixel(hdc, coord.x - hsi.nPos, coord.y - vsi.nPos, RGB(125, 125, 125));

}



inline bool Object::Remove()
{
	return GameStruct::ObjectMaster::DeleteObject(this->index);
}

void Object::Draw(HDC& hdc)
{
	//GetXform();
	//ApplyXform();
	//SetROP2(hdc, R2_NOT);
	//Polygon(hdc, points, shapedata->size);
	if (invisible)
		return;
	HBRUSH nbrush, obrush;
	SetROP2(hdc, R2_NOTMERGEPEN);
	nbrush = CreateSolidBrush(RGB(122, 255, 122));
	//nbrush = CreateSolidBrush(RGB(128, 0, 128));

	obrush = (HBRUSH)SelectObject(hdc, nbrush);

	//SetROP2(hdc, R2_NOT);


	SelectObject(hdc, obrush);
	DeleteObject(nbrush);
}

void Object::Move()
{
	coord.x += cos(GameStruct::MathMaster::DegreeToRadian(angle))*speed;
	coord.y += sin(GameStruct::MathMaster::DegreeToRadian(angle))*speed;
	POINT pnt = { coord.x,coord.y };
	if (!PtInRect(&GameStruct::MapMaster::map, pnt))
	{
		Remove();
		return;
	}
}





LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"virussimulator";//프로그램 이름
using namespace std;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;//프로그램핸들값을 전역변수에대입

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.hInstance = hInstance;//프로그램 핸들값
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = IpszClass;//클래스이름에 프로그램이름대입
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);//윈도우등록

	hWnd/*윈도우핸들*/ = CreateWindow(IpszClass/*클래스이름찾아서설정가져옴*/, IpszClass/*타이틀바*/, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, -10, 0, 1980, 1200, NULL, (HMENU)NULL, hInstance/*프로그램핸들*/, NULL);//윈도우생성
	ShowWindow(hWnd, nCmdShow);//윈도우화면출력
	bool done = false;
	GameStruct::state = GameStruct::State::INGAME;
	while (!done)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				done = true;
			else {
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
		{
			switch (GameStruct::state)
			{
			case GameStruct::State::MENU:
				GameStruct::Menu_Process();
				break;
			case GameStruct::State::INGAME:
				GameStruct::Ingame_Process();
				break;
			}
			InvalidateRect(GameStruct::g_hWnd, NULL, false);
			//if(GameStruct::TimeMaster::movecount % (uint64_t)2 == 0)
			//	GameStruct::Render();
		}
	}
	return (int)Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)

{

	HDC hdc;

	PAINTSTRUCT ps;
	HDC ready_hdc;
	HBITMAP old_ready_bit;
	switch (iMessage) {

	case WM_CREATE:
	{
		GameStruct::Setup(hWnd);
		return 0;
	}
	case WM_KEYDOWN:
		GameStruct::KeyMaster::Keydown(wParam);
		return 0;
	case WM_KEYUP:
		GameStruct::KeyMaster::Keyup(wParam);
		return 0;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		GameStruct::MouseMaster::MouseChange(iMessage, lParam);
		return 0;
	case WM_MOUSEWHEEL:               //마우스 휠 이벤트 발생시 들어오는 case문
		((short)HIWORD(wParam)<0) ? GameStruct::rendersize-- : GameStruct::rendersize++;
		return 0;

	case WM_SIZE:
		GetClientRect(GameStruct::g_hWnd, &GameStruct::client_rect);
		return 0;

	case WM_HSCROLL:
	{
		int TempPos = GetScrollPos(GameStruct::g_hWnd, SB_HORZ);
		int originpos = TempPos;
		switch (LOWORD(wParam)) {
		case SB_LINELEFT:
			TempPos = max(0, TempPos - 1);
			break;
		case SB_LINERIGHT:
			TempPos = min(255, TempPos + 1);
			break;
		case SB_PAGELEFT:
			TempPos = max(0, TempPos - 10);
			break;
		case SB_PAGERIGHT:
			TempPos = min(255, TempPos + 10);
			break;
		case SB_THUMBTRACK:
			TempPos = HIWORD(wParam);
			break;
		}
		/*SetScrollPos(GameStruct::g_hWnd, SB_HORZ, TempPos, false);
		SCROLLINFO vsi;
		SCROLLINFO hsi;
		GetScrollInfo(GameStruct::g_hWnd, SB_VERT, &vsi);
		GetScrollInfo(GameStruct::g_hWnd, SB_HORZ, &hsi);
		*/
		SetScrollPos(GameStruct::g_hWnd, SB_HORZ, TempPos, false);
		//ScrollWindow(GameStruct::g_hWnd, originpos, 0, NULL, NULL);
	}

	return 0;
	case WM_VSCROLL:
	{
		int TempPos = GetScrollPos(GameStruct::g_hWnd, SB_VERT);
		int originpos = TempPos;
		switch (LOWORD(wParam)) {
		case SB_LINELEFT:
			TempPos = max(0, TempPos - 1);
			break;
		case SB_LINERIGHT:
			TempPos = min(255, TempPos + 1);
			break;
		case SB_PAGELEFT:
			TempPos = max(0, TempPos - 10);
			break;
		case SB_PAGERIGHT:
			TempPos = min(255, TempPos + 10);
			break;
		case SB_THUMBTRACK:
			TempPos = HIWORD(wParam);
			break;
		}
		SetScrollPos(GameStruct::g_hWnd, SB_VERT, TempPos, false);
		//ScrollWindow(GameStruct::g_hWnd, 0,originpos, NULL, NULL);
	}
	return 0;
	case WM_PAINT:
		//GameStruct::Render();
		//GameStruct::View();l
		hdc = BeginPaint(GameStruct::g_hWnd, &ps);
		ready_hdc = CreateCompatibleDC(hdc);
		old_ready_bit = (HBITMAP)SelectObject(ready_hdc, GameStruct::ready_bitmap);
		BitBlt(hdc, 0, 0, GameStruct::client_rect.right, GameStruct::client_rect.bottom, ready_hdc, 0, 0, SRCCOPY);
		SelectObject(ready_hdc,old_ready_bit);
		//DeleteObject(old_ready_bit);
		DeleteDC(ready_hdc);
		EndPaint(GameStruct::g_hWnd, &ps);
		return 0;

	case WM_DESTROY:
	{
		GameStruct::lastrender = true;
		char fn[500];
		snprintf(fn, sizeof(fn), ".\\capture_%d_%lf_%d_%d_%d", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime);

		mkdir(fn);

		char file_name[256];
		sprintf(file_name, ".\\capture_%d_%lf_%d_%d_%d\\result_%d.txt", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime, time(NULL));
		ofstream outFile(file_name);
		outFile << "seed = " << GameStruct::seed << endl;
		outFile << "setting = " << GameStruct::VirusSimulator::infectionradius << " " << GameStruct::VirusSimulator::incubateperiod << " " << GameStruct::VirusSimulator::start_space <<" "<<GameStruct::VirusSimulator::fataltime<< endl;
		outFile << "------roadrank_posi------\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_posi[i][j] << " ";
			}
			outFile << endl;
		}
		outFile << "\n-----roadrank_acti-----\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_acti[i][j] << " ";
			}
			outFile << endl;
		}
		outFile << "\n-----roadrank_nega-----\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_nega[i][j]<< " ";
			}
			outFile << endl;
		}
		outFile << "\n-----roadrank_current-----\n";
		for (int i = 0; i < 120; ++i)
		{
			for (int j = 0; j < 120; ++j)
			{
				outFile << GameStruct::VirusSimulator::roadrank_acti[i][j] + GameStruct::VirusSimulator::roadrank_posi[i][j]+ GameStruct::VirusSimulator::roadrank_nega[i][j] << " ";
			}
			outFile << endl;
		}
		outFile << "\n---------------------\n";
		outFile << "movecount : " << GameStruct::TimeMaster::movecount << endl;
		outFile << "normal : " << GameStruct::VirusSimulator::normal<< endl;
		outFile << "unborn : " << GameStruct::VirusSimulator::unborn << endl;
		outFile << "outbreaker : " << GameStruct::VirusSimulator::outbreaker << endl;
		outFile << "dead : " << GameStruct::VirusSimulator::dead << endl;
		outFile << "infectionout : " << GameStruct::VirusSimulator::infectionout<<endl;
		outFile << "infectedpopulation : " << GameStruct::VirusSimulator::infectedpopulation << endl;
		outFile << "infection_by_acti : " << GameStruct::VirusSimulator::infection_by_acti << endl;
		outFile << "infection_by_posi : " << GameStruct::VirusSimulator::infection_by_posi << endl;
		outFile << "infectionpercent : "  << endl;
		for (int i = 0; i < 9; ++i)
		{
			outFile << (i+1)*10<<"퍼센트 감염된 시간 : " << GameStruct::VirusSimulator::infectionpercent[i]<< endl;
		}
		outFile.close();
		
		outFile.open("setting.txt");
		
		outFile << GameStruct::seed+1 <<" " << GameStruct::VirusSimulator::infectionradius << " "<< GameStruct::VirusSimulator::incubateperiod << " " << GameStruct::VirusSimulator::start_space <<" " <<GameStruct::VirusSimulator::fataltime << endl;
		//
		outFile.close();
		snprintf(fn, sizeof(fn), ".\\capture_%d_%lf_%d_%d_%d\\day_%d.bmp", GameStruct::seed, GameStruct::VirusSimulator::infectionradius, GameStruct::VirusSimulator::incubateperiod, GameStruct::VirusSimulator::start_space, GameStruct::VirusSimulator::fataltime, GameStruct::TimeMaster::day);
		
		GameStruct::state = GameStruct::State::END;
		GameStruct::renderthread.join();
		GameStruct::movethread.join();
		SaveBitmap(fn, GameStruct::ready_bitmap);
		GameStruct::ClearAll();
		//ShellExecute(NULL, L"open", L".\virussimulator.exe", NULL, NULL, SW_SHOW);
		PostQuitMessage(0);


		return 0;

	}

	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}



