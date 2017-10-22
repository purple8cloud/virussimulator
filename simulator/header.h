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
	// DC�� ����
	HDC hdc = GetDC(NULL);

	// bitmap info �� ����
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	GetDIBits(hdc, hBitmap, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS);
	if (bmpInfo.bmiHeader.biSizeImage <= 0)
		bmpInfo.bmiHeader.biSizeImage = bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount + 7) / 8;

	// ���� image ������ ������
	LPVOID pBuf = NULL;
	if ((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage)) == NULL)
	{
		
	}
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	GetDIBits(hdc, hBitmap, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS);

	// bitmap file header �����
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpInfo.bmiHeader.biSizeImage;
	bmpFileHeader.bfType = 'MB';
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// ������ ���� ����
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
	int index;//objects�迭�� ��� ����Ǿ��ִ���
	
	virtual void Draw(HDC& hdc);
	virtual void Move();
	virtual inline bool Remove();//�����κ��� �Լ��� �Ȼ��� delete�ϰ� �Ҹ��ڿ��� ó�������ν� ������� ��밡��

};

class Unit : public Object {
public:
	//�̵��� ������ġ�� �����ϰ� �̵��� ������ȵǴ� ��ġ�� �ö󰥰�� ������ġ�� �����̵�
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
		//S sity �� T town ����
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

unordered_multimap<pair<int, int>, Object*, pair_hash> boxmap;//x.0 ~ x+1.0 �� x�� ��

namespace GameStruct {

	enum State { MENU, INGAME, END }state;
	/*
	��ũ��� �þߺ��� ��ũ��
	360�� ź������
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
			bool visit[120]; /* �湮 ���� */
			int dis[120], prev[120]; /* �Ÿ��� ���� ǥ�ÿ� ���� */
			int i, j, s = _s, e = _e, k, min; /* �ݺ�, ���� ����, �ӽú��� */
			int stack[120], tmp, top; /* ��� ǥ������ ���� */

			for (i = 0; i < 120; i++) { /* �ʱ�ȭ */
				dis[i] = M;
				prev[i] = 0;
				visit[i] = false;
			}
			dis[s] = 0; /* �������� �Ÿ��� 0 */

			for (i = 0; i < 120; i++) {
				min = M;
				for (j = 0; j < 120; j++) { /* ������ ����ŭ �ݺ� */
					if (visit[j] == false && dis[j] < min) { /* Ȯ������ �ʰ� �Ÿ��� ª�� ������ ã�� */
						k = j;
						min = dis[j];
					}
				}
				visit[k] = true; /* �ش� ���� Ȯ�� üũ */
				if (min == M) break; /* ã�� �������� ���� */
				for (j = 0; j < 120; j++) { /* ������ ����ŭ �ݺ� */
					if (dis[k] + roadmatrix[k][j] < dis[j]) {
						dis[j] = dis[k] + roadmatrix[k][j]; /* ���� */
						prev[j] = k; /* J�� ���� ���ؼ��� K�� ���ľ� �� */
					}
				}
				
			}

			
				top = -1;
				tmp = e; /* ������ �������κ��� ������ */
				while (true) {
					stack[++top] = tmp;
					if (tmp == s) break; /* �������� �̸������� ���� */
					tmp = prev[tmp];
				}

			
			int cnt = 0;
			for (int i = 0; i < 120; ++i)
				u->path[i] = -1;
			for (i = top-1; i > -1; i--) { /* ��� */
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
		//1cm = 3800m,  ���� : 288,800m,���� : 197,600m 1�ȼ� = 38.10529m; 1m = 0.02524�ȼ�
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
	//ĳ����,�淿,��,Ű,Ÿ�� ������ Ŭ������ ���θ���� ����
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

		Object * objects[MAXOBJECT];//�����͹迭�� �ƴϿ��� �θ�Ŭ������ �ڽ�Ŭ������ �������ֳ� �޸�����ȭ ���

		queue<int> avaliableindex;


		bool MakeObject(Object * object);//���Լ��ϳ��� ���ź�������� ź�������� ������Լ� �ٲ���
		


		bool DeleteObject(int index)//������Ʈ �Ҹ��ڿ� ����������?
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


	namespace TimeMaster {//ȭ�鰻���ֱ�� ���Ӽӵ��� ������
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

		inline void UpdateTime()//delta_t�� ������ ���� �������ð��� �����ؾ���
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

	namespace MathMaster//TODO �� ����̶� �پ��� ��� �� ����ֱ�
	{
		
		bool Ptin4Pts(D_COORD& B, const D_COORD P[])
		{
			
			//crosses�� ��q�� ������ �������� �ٰ������� ������ ����
			int crosses = 0;
			for (int i = 0; i < 4; i++) {
				int j = (i + 1) % 4;
				//�� B�� ���� (p[i], p[j])�� y��ǥ ���̿� ����
				if ((P[i].y > B.y) != (P[j].y > B.y)) {
					//atX�� �� B�� ������ ���򼱰� ���� (p[i], p[j])�� ����
					float atX = (P[j].x - P[i].x)*(B.y - P[i].y) / (P[j].y - P[i].y) + P[i].x;
					//atX�� ������ ���������� ������ ������ ������ ������ ������Ų��.
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



