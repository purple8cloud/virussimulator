#pragma once
#include <opencv2\core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>
#include <stdio.h>
#include <chrono>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <unordered_map>
#include <mutex>
#include <direct.h>
using namespace cv;
using namespace std;
using namespace chrono;
mutex boxmap_mtx;
#define MAXOBJECT 1564615
//#define MAXOBJECT 1564

void SaveBitmap(char *szFilename, HBITMAP hBitmap)
{
	// DC를 얻어옴
	HDC hdc = GetDC(NULL);

	// bitmap info 를 얻어옴
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	GetDIBits(hdc, hBitmap, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS);
	if (bmpInfo.bmiHeader.biSizeImage <= 0)
		bmpInfo.bmiHeader.biSizeImage = bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount + 7) / 8;

	// 실제 image 내용을 얻어오기
	LPVOID pBuf = NULL;
	if ((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage)) == NULL)
	{
		
	}
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	GetDIBits(hdc, hBitmap, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS);

	// bitmap file header 만들기
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpInfo.bmiHeader.biSizeImage;
	bmpFileHeader.bfType = 'MB';
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// 파일을 열고 쓰기
	FILE* fp = fopen(szFilename, "wb");
	
	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pBuf, bmpInfo.bmiHeader.biSizeImage, 1, fp);

	if (hdc) ReleaseDC(NULL, hdc);
	if (pBuf) free(pBuf);
	if (fp) fclose(fp);
}


template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct pair_hash {


	template<class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2> &p)const {
		auto h1 = std::hash<T1>()(p.first);
		auto h2 = std::hash<T2>()(p.second);
		//return h1^h2;
		std::size_t seed = 0;
		hash_combine(seed, h1);
		hash_combine(seed, h2);
		return seed;
	}
};

typedef struct _INFECTION_DATA
{
	bool positive;
	bool active;
	double infect_radius;
	int64_t fatal_time;
	int64_t incubation_period;
}INFECTION_DATA;

typedef struct _D_COORD
{
	double x;
	double y;
}D_COORD;
class Object {
public:
	Object() {};
	Object(int x, int y, float _speed, float _angle)
	{
		coord.x = x;

		coord.y = y;
		
		speed = _speed;
	}
	~Object()
	{
		//GameStruct::ObjectMaster::avaliableindex.push(index);
	};
	D_COORD coord = { 100,100 };

	float angle = 0;
	
	double speed = 0;
	
	bool invisible = false;
	int index;//objects배열의 어디에 저장되어있는지
	
	virtual void Draw(HDC& hdc);
	virtual void Move();
	virtual inline bool Remove();//삭제부분을 함수를 안빼고 delete하고 소멸자에서 처리함으로써 성능향상 기대가능

};

class Unit : public Object {
public:
	//이동은 직전위치를 저장하고 이동후 있으면안되는 위치에 올라갈경우 이전위치로 강제이동
	D_COORD pre_coord;
	INFECTION_DATA infection_data;
	int regionnum;
	int origin_regionnum;
	int unitnumber;
	enum _pattern{
		sSsT,
		sSdT,
		dS,
		otherplace,
		unknown,
		nomove,
		underage
		//S sity 시 T town 읍면
	};
	_pattern pattern;
	bool migrating = false;
	int destination;
	int movetime;
	int path[120];
	int dis[120];
	bool vanish = false;
	bool alive = true;
	Unit(int unum,int rnum,_pattern pat, INFECTION_DATA& ifd, double x, double y);

	void Move();
	void Draw(HDC& hdc);
};

unordered_multimap<pair<int, int>, Object*, pair_hash> boxmap;//x.0 ~ x+1.0 은 x에 들어감

namespace GameStruct {

	enum State { MENU, INGAME, END }state;
	/*
	맵크기는 시야보다 더크게
	360도 탄막게임
	*/
	unsigned int seed;
	HWND g_hWnd;
	RECT client_rect;
	int rendersize = 20;
	bool lastrender = false;
	bool render_on = false;
	bool capture_on = false;
	thread  renderthread;
	thread  movethread;
	POINT renderpos = { 0,0 };
	HBITMAP ready_bitmap;

	/*static HWND gethWnd()
	{
	return GameStruct::hWnd;
	};*/
	namespace VirusSimulator {
		int roadmatrix[120][120];
		int roadrank_posi[120][120] = { 0 };
		int roadrank_acti[120][120] = { 0 };
		int roadrank_nega[120][120] = { 0 };

		double infectionradius = 0; int incubateperiod = 0; int start_space; int fataltime;
		int infectionout = 0;
		int infectedpopulation =1;
		int unborn = 1;
		int outbreaker = 0;
		int dead = 0;
		int normal = MAXOBJECT-1;
		int infection_by_posi = 0;
		int infection_by_acti = 0;
		int infectionpercent[9] = { -1 ,-1,-1,-1,-1,-1,-1,-1,-1};
		int population_movement[19][11];
		POINT centerpos[120];
		int regionarea[120];
		pair<int, int> city[18];

		inline void Path_finder(int _s, int _e,Unit* u)
		{
			int M = 2000;
			bool visit[120]; /* 방문 여부 */
			int dis[120], prev[120]; /* 거리와 정점 표시용 변수 */
			int i, j, s = _s, e = _e, k, min; /* 반복, 시작 종료, 임시변수 */
			int stack[120], tmp, top; /* 경로 표시위한 변수 */

			for (i = 0; i < 120; i++) { /* 초기화 */
				dis[i] = M;
				prev[i] = 0;
				visit[i] = false;
			}
			dis[s] = 0; /* 시작점의 거리는 0 */

			for (i = 0; i < 120; i++) {
				min = M;
				for (j = 0; j < 120; j++) { /* 정점의 수만큼 반복 */
					if (visit[j] == false && dis[j] < min) { /* 확인하지 않고 거리가 짧은 정점을 찾음 */
						k = j;
						min = dis[j];
					}
				}
				visit[k] = true; /* 해당 정점 확인 체크 */
				if (min == M) break; /* 찾지 못했으면 종료 */
				for (j = 0; j < 120; j++) { /* 정점의 수만큼 반복 */
					if (dis[k] + roadmatrix[k][j] < dis[j]) {
						dis[j] = dis[k] + roadmatrix[k][j]; /* 갱신 */
						prev[j] = k; /* J로 가기 위해서는 K를 거쳐야 함 */
					}
				}
				
			}

			
				top = -1;
				tmp = e; /* 마지막 정점으로부터 역추적 */
				while (true) {
					stack[++top] = tmp;
					if (tmp == s) break; /* 시작점에 이르렀으면 종료 */
					tmp = prev[tmp];
				}

			
			int cnt = 0;
			for (int i = 0; i < 120; ++i)
				u->path[i] = -1;
			for (i = top-1; i > -1; i--) { /* 출력 */
				u->path[cnt] = stack[i];
				++cnt;
			}
			for (i = 0; i < 120; ++i)
				u->dis[i] = dis[i];
			
			
			
			
		}
		bool Setup()
		{
			city[0].first = 0; city[0].second = 10;
			city[1].first = 11; city[1].second = 15;
			city[2].first = 16; city[2].second = 21;
			city[3].first = 22; city[3].second = 26;
			city[4].first = 27; city[4].second = 32;
			city[5].first = 33; city[5].second = 37;
			city[6].first = 38; city[6].second = 38;
			city[7].first = 39; city[7].second = 44;
			city[8].first = 45; city[8].second = 53;
			city[9].first = 54; city[9].second = 63;
			city[10].first = 64; city[10].second = 73;
			city[11].first = 74; city[11].second = 81;
			city[12].first = 82; city[12].second = 90;
			city[13].first = 91; city[13].second = 99;
			city[14].first = 100; city[14].second = 108;
			city[15].first = 109; city[15].second = 117;
			city[16].first = 118; city[16].second = 118;
			city[17].first = 119; city[17].second = 119;



			ifstream inFile("roadgraph.txt");
			int weight;
			for (int i = 0; i < 120; ++i)
			{
				for (int j = 0; j < 120; ++j)
				{
					inFile >> weight;
					VirusSimulator::roadmatrix[i][j] = weight;
				}
			}
			for (int i = 0; i < 120; ++i)
			{
				for (int j = 0; j < 120; ++j)
				{
					if (VirusSimulator::roadmatrix[i][j] == -1 && VirusSimulator::roadmatrix[j][i] == -1)
					{
						VirusSimulator::roadmatrix[i][j] = 1000;
						VirusSimulator::roadmatrix[j][i] = 1000;
					}
					else if (VirusSimulator::roadmatrix[i][j] == -1)
					{
						VirusSimulator::roadmatrix[i][j] = VirusSimulator::roadmatrix[j][i];
					}
					else VirusSimulator::roadmatrix[j][i] = VirusSimulator::roadmatrix[i][j];
				}
			}
			for (int i = 0; i < 120; ++i)
				VirusSimulator::roadmatrix[i][i] = 0;

			inFile.close();
			inFile.open("Population_movement.txt");
			for (int i = 0; i < 19; ++i)
			{
				for (int j = 0; j < 11; ++j)
				{
					inFile >> VirusSimulator::population_movement[i][j];
				}
			}
			inFile.close();

			inFile.open("setting.txt");
			inFile >>GameStruct::seed>>VirusSimulator::infectionradius >> VirusSimulator::incubateperiod >> VirusSimulator::start_space >> VirusSimulator::fataltime;
			inFile.close();

			return true;
		}
	};
	namespace MapMaster {
		RECT map;
		//1cm = 3800m,  가로 : 288,800m,세로 : 197,600m 1픽셀 = 38.10529m; 1m = 0.02524픽셀
		Mat image = imread("testimg.bmp");
		int box_in_horizenline = image.cols;
		int box_in_verticalline = image.rows;

		int boxwidth = image.cols / box_in_horizenline;
		int boxheight = image.rows / box_in_verticalline;
		Vec3b mRed(0, 0, 255);
		Vec3b mBlue(255, 0, 0);
		Vec3b mGreen(0, 255, 0);
		Vec3b mWhite(0, 0, 0);

		int ** boxs;
		
		
		
		
		bool Setup()
		{
			//MapMaster::boxmap.insert(pair<pair<int, int>, Object*>(make_pair(1, 1), nullptr));
			client_rect.right = GetSystemMetrics(SM_CXSCREEN);
			client_rect.bottom = GetSystemMetrics(SM_CYSCREEN);
			map.right = image.cols;
			map.bottom = image.rows;
			map.left = 0;
			map.top = 0;

			int percent = 0, maxpercent = box_in_horizenline*box_in_verticalline / 100, tmp = 0;
			int redN = 0, blueN = 0, greenN = 0, whiteN = 0;
			boxs = new int*[image.rows];//(int*) malloc(sizeof (int)*box_in_horizenline);
			for (int i = 0; i < image.cols; i++)
				boxs[i] = new int[image.cols];
			
			for (int boxnum_horizen = 0; boxnum_horizen < image.cols; ++boxnum_horizen)
			{
				for (int boxnum_vertical = 0; boxnum_vertical < image.rows; ++boxnum_vertical)
				{
					int bcolor = image.at<Vec3b>(boxnum_vertical, boxnum_horizen)[0];
					int gcolor = image.at<Vec3b>(boxnum_vertical, boxnum_horizen)[1];
					int rcolor = image.at<Vec3b>(boxnum_vertical, boxnum_horizen)[2];


					//uchar bcolor = image.at<Vec3b>(boxnum_horizen, boxnum_vertical)[0];
					
					//boxs[boxnum_horizen][boxnum_vertical] = bcolor;

					if (bcolor >=136 && bcolor <=255 && gcolor == 0 && rcolor == 0)
					{
						VirusSimulator::centerpos[255 - bcolor].x += boxnum_horizen;
						VirusSimulator::centerpos[255 - bcolor].y += boxnum_vertical;
						++VirusSimulator::regionarea[255 - bcolor];
						boxs[boxnum_vertical][boxnum_horizen] = bcolor;
						
						
					}
					else boxs[boxnum_vertical][boxnum_horizen] = 0;
					//else boxs[boxnum_vertical][boxnum_horizen] = white;
					++percent;
					if (percent == maxpercent)
					{
						++tmp;
						percent = 0;
						/*wchar_t ch[255];
						::swprintf(ch, 255, L"percent:%d\n", tmp);
						OutputDebugString(ch);*/
					}
				}
			}
			for (int i = 0; i < 120; ++i)
			{
				VirusSimulator::centerpos[i].x /= VirusSimulator::regionarea[i];
				VirusSimulator::centerpos[i].y /= VirusSimulator::regionarea[i];

			}
			
			return true;
		}
	};
	//캐릭터,뷸렛,맵,키,타임 마스터 클래스를 따로만들어 관리
	namespace KeyMaster {
		bool input[256];
		bool clicked[256];
		bool Setup()
		{
			for (int i = 0; i < 256; i++)
			{
				input[i] = false;
				clicked[i] = false;
			}
		}

		void Keydown(WPARAM wParam)
		{
			input[wParam] = true;

		}

		void Keyup(WPARAM wParam)
		{
			input[wParam] = false;
			clicked[wParam] = true;
		}

		void Resetclicked()
		{
			for (int i = 0; i < 256; i++)
			{
				clicked[i] = false;
			}
		}
	};

	namespace MouseMaster {
		POINT coord;

		typedef struct _mouse {
			int downedX = -1, upedX = -1;
			int downedY = -1, upedY = -1;
			bool downed = false;
			bool clicked = false;
		}mouse;
		mouse Lbtn;
		mouse Rbtn;

		void Resetclicked()
		{
			Lbtn.clicked = false;
			Rbtn.clicked = false;
		}
		void LButtonDown(LPARAM lParam)
		{
			Lbtn.downed = true;
			Lbtn.downedX = LOWORD(lParam)*MapMaster::map.right / client_rect.right;
			Lbtn.downedY = HIWORD(lParam)*MapMaster::map.bottom / client_rect.bottom;
		}
		void LButtonUp(LPARAM lParam)
		{
			Lbtn.downed = false;
			Lbtn.upedX = LOWORD(lParam)*MapMaster::map.right / client_rect.right;
			Lbtn.upedY = HIWORD(lParam)*MapMaster::map.bottom / client_rect.bottom;
			if (abs(Lbtn.downedX - Lbtn.upedX) < 10 && abs(Lbtn.downedY - Lbtn.upedY) < 10)
				Lbtn.clicked = true;
		}
		void RButtonDown(LPARAM lParam)
		{
			Rbtn.downed = true;
			Rbtn.downedX = LOWORD(lParam)*MapMaster::map.right / client_rect.right;
			Rbtn.downedY = HIWORD(lParam)*MapMaster::map.bottom / client_rect.bottom;
		}
		void RButtonUp(LPARAM lParam)
		{
			Rbtn.downed = false;
			Rbtn.upedX = LOWORD(lParam)*MapMaster::map.right / client_rect.right;
			Rbtn.upedY = HIWORD(lParam)*MapMaster::map.bottom / client_rect.bottom;
			if (abs(Rbtn.downedX - Rbtn.upedX) < 10 && abs(Rbtn.downedY - Rbtn.upedY) < 10)
				Rbtn.clicked = true;
		}
		void MouseMove(LPARAM lParam)
		{
			coord.x = LOWORD(lParam)*MapMaster::map.right / client_rect.right;
			coord.y = HIWORD(lParam)*MapMaster::map.bottom / client_rect.bottom;
		}
		void MouseChange(UINT iMessage, LPARAM lParam)
		{
			switch (iMessage)
			{
			case WM_LBUTTONDOWN:
				GameStruct::MouseMaster::LButtonDown(lParam);
				return;
			case WM_RBUTTONDOWN:
				GameStruct::MouseMaster::RButtonDown(lParam);
				return;
			case WM_LBUTTONUP:
				GameStruct::MouseMaster::LButtonUp(lParam);
				return;
			case WM_RBUTTONUP:
				GameStruct::MouseMaster::RButtonUp(lParam);
				return;
			case WM_MOUSEMOVE:
				GameStruct::MouseMaster::MouseMove(lParam);
				return;
			}
		}
	}



	namespace ObjectMaster {

		Object * objects[MAXOBJECT];//포인터배열이 아니여도 부모클래스가 자식클래스를 담을수있나 메모리파편화 우려

		queue<int> avaliableindex;


		bool MakeObject(Object * object);//이함수하나로 모든탄막만들지 탄막에따라 만드는함수 바꿀지
		


		bool DeleteObject(int index)//오브젝트 소멸자에 끼워넣을까?
		{

			delete objects[index];
			avaliableindex.push(index);
			objects[index] = NULL;
			return true;
		}
		bool Setup()
		{
			for (int i = 0; i < MAXOBJECT; i++)
				avaliableindex.push(i);
			return true;
		};
	};


	namespace TimeMaster {//화면갱신주기와 게임속도는 무관계
		double gamespeed = 0.01;
		double invers_gamespeed = 1 / gamespeed;
		duration<double> delta_time;
		duration<double> delta_tmp;

		duration<double> current_time;
		system_clock::time_point prev_t = system_clock::from_time_t(0);

		system_clock::time_point now_t = system_clock::from_time_t(0);

		system_clock::time_point start_t = system_clock::from_time_t(0);

		bool paused = false;
		int movecount = 0;
		int hour = 0;
		int day = 0;
		bool Setup()
		{
			prev_t = now_t = start_t = system_clock::now();
			delta_time = duration<double>(0);
			current_time = duration<double>(0);

			return true;
		};

		inline void UpdateTime()//delta_t중 계산되지 않은 나머지시간은 보류해야함
		{
			if (!paused) {

				now_t = system_clock::now();
				current_time += now_t - prev_t;
				delta_time += now_t - prev_t;
				delta_tmp = delta_time;
				while (delta_time.count() >= gamespeed)
				{
					delta_time -= std::chrono::duration<double>(gamespeed);
				}
				prev_t = now_t;
			}
		};

		inline double Getdeltatime() {
			return delta_time.count();
		};

		inline double Getcurrenttime() {
			return current_time.count();
		}
		void Pause();
		void Restart();
	};

	namespace MathMaster//TODO 눈 모양이랑 다양한 모양 더 집어넣기
	{
		
		bool Ptin4Pts(D_COORD& B, const D_COORD P[])
		{
			
			//crosses는 점q와 오른쪽 반직선과 다각형과의 교점의 개수
			int crosses = 0;
			for (int i = 0; i < 4; i++) {
				int j = (i + 1) % 4;
				//점 B가 선분 (p[i], p[j])의 y좌표 사이에 있음
				if ((P[i].y > B.y) != (P[j].y > B.y)) {
					//atX는 점 B를 지나는 수평선과 선분 (p[i], p[j])의 교점
					float atX = (P[j].x - P[i].x)*(B.y - P[i].y) / (P[j].y - P[i].y) + P[i].x;
					//atX가 오른쪽 반직선과의 교점이 맞으면 교점의 개수를 증가시킨다.
					if (B.x < atX)
						++crosses;
				}
			}
			return crosses % 2 > 0;


		}



		template<typename T>
		inline double DegreeToRadian(T angle)
		{
			return angle * 0.01745;
		}

		template<typename T>
		inline double RadianToDegree(T angle)
		{
			return angle *  57.29577;
		}

		
		bool Setup()
		{
			return true;
		}
	}


	bool Setup(HWND hWnd);

	bool ClearAll();
	void Menu_Process();
	void Ingame_Process();

	void Render();
	void View() {};
};
//



