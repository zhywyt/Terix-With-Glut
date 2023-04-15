#ifndef GAME_HEAD
#define GAME_HEAD
#include <GL/glut.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include<string>
#include <map>
#include <vector>
#include <time.h>
#include <fstream>
#include <irr/irrKlang.h>
#include "Reasource.h"
using namespace irrklang;
using namespace std;

extern ISoundEngine* SoundEngine;
extern ISound* RunSound;

const int mapScre = 1;							//��������
const int  NodeSize = 20;						//���α߳�
const int LineSize = 1;
const int Cow = 30 * mapScre;				//��������  y
const int Row = 24 * mapScre;				//����  x
const int GameCow = 30 * mapScre;		//��Ϸ��������
const int GameRow = 16 * mapScre;		//����

class Game;
typedef enum {
	STOP,				//��Ϸ��ͣ
	PRESTART,		//��Ϸ��ʼǰ
	RUN,				//��Ϸ����ʱ
	GAMEOVER,		//��Ϸ����
	GAMERANKLIST,	//�鿴��Ϸ����
	GAMEWIN,		//��Ϸʤ��
}GameMode;
typedef enum {
	SAVE1=GAMEWIN+1,
	SAVE2,
	SAVE3,
	LOAD1,
	LOAD2,
	LOAD3,
	LOADAUTOSAVE,
	CHECKBEST
}SaveLoad;
typedef enum {
	EASY=CHECKBEST+1,
	NORMAL,
	HARD
}DIFFMODE;
typedef enum {
	MUSICON=HARD+1,
	MUSICOFF
}MUSICMODE;
extern void Input(int data, int x, int y);
extern void onDisplay();
extern void Input(unsigned char nchar, int x, int y);
extern void processMenuEvents(int option);

class Game {
public:
	typedef enum {
		LL = 1,		//His shape like a "L"
		OO,			//His shape like a "#"
		DOT,		//He is a dot
		II,				//His shape like a "I"
		TT,			//His shape like a "T"
		TTEnd,		//��ʵ�����壬Ϊ���������˹���������ʱ��ǽ�����
		WALL		//ǽ�棨�հף�
	}ToolType;

private:
	//����˹������
	struct Tool {
		Tool(int x, int y, ToolType type)
			:_x(x), _y(y), _type(type),run(false)
		{
			_data.resize(4, vector<int>(4));
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)_data[i][j] = 0;
			switch (type) {
			case LL:
				for (int i = 0; i <= 2; i++)_data[1][i] = LL;
				_data[2][2] = LL;
				break;
			case OO:
				for (int i = 1; i <= 2; i++)
					for (int j = 1; j <= 2; j++)
						_data[i][j] = OO;
				break;
			case DOT:
				_data[1][1] = DOT;
				break;
			case II:
				for (int i = 0; i < 4; i++)_data[1][i] = II;
				break;
			case TT:
				for (int i = 0; i < 3; i++)_data[2][i] = TT;
				_data[1][1] = TT;
				break;

			}

		}
		Tool()
			:run(false),_x(0),_y(0),_type(LL)
		{
			_data.resize(4, vector<int>(4));
		}
		void setPosition(int x, int y) {
			_x = x, _y = y;
		}
		//˳ʱ����ת
		Tool Rotate() {
			Tool NewOne (*this);
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					 NewOne._data[j][3 - i] = _data[i][j];
				}
			return  NewOne;
		}
		void MoveDown() {
			setPosition(_x, _y + 1);
		}
		void MoveLeft() {
			 setPosition(_x - 1, _y);
		}
		void MoveRight() {
			 setPosition(_x + 1, _y);
		}

		int _x, _y;
		ToolType _type;
		vector<vector<int>>_data;
		bool run;

	};

public:

	static const int dx, dy;					//�����ֲ������߿����
	static const int rePx, rePy;			//���ݵ�Tool�ĳ�ʼλ��
	static const int waitPx, waitPy;	//�ȴ���ʼλ��
	static const int infoPx, infoPy;		//��Ϣ�����Ƶ�λ��

	Game();
	void Start();
	bool Drop();
	int getDiff()const;
	GameMode getStatus()const;
	void ChangeStatus(GameMode);
	void setDiffMode(DIFFMODE);
	DIFFMODE getDiffMode();
	bool getMusicStatus();
	//Change The Music status
	void setMusicStatus(bool);

	friend void Input(int data, int x, int y);
	friend void onDisplay();
	friend void Input(unsigned char nchar, int x, int y);
	friend void processMenuEvents(int option);

private:
//���ݳ�Ա-------------------------

	GameMode status;
	int clearTimes;
	unsigned int zhywyt;
	//��Ϣ��Ա
	unsigned int _points;
	unsigned int PB_points;
	unsigned int Diff;
	map<int,DIFFMODE> RankList;
	DIFFMODE m_diffMode;

	unsigned int PB_Diff;
	bool PB;
	bool exZhywyt;
	//�����Ա
	Tool m_tool;							//��ǰ�ٿص�Toll
	Tool m_next;							//չʾ��Tool
	vector<vector<int>>m_map;	//������Ϣ
	//�ļ���
	ifstream _ifs;
	ofstream _ofs;

	bool MusicStatus;
//˽�к���-------------------------
void NextTool();
//status==Prestart
void reset();
bool CanMoveDown();
bool CanMoveRight();
bool CanMoveLeft();
bool Rotate();
void GameOver();
void AddToMap();
bool Save(string FileName);
bool Load(string FileName);
};
#endif