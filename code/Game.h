#ifndef GAME_HEAD
#define GAME_HEAD
#include <GL/glut.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include<string>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;
const int mapScre = 1;							//场景缩放
const int  NodeSize = 20;						//方形边长
const int Cow = 30 * mapScre;				//窗口行数  y
const int Row = 24 * mapScre;				//列数  x
const int GameCow = 30 * mapScre;		//游戏场景行数
const int GameRow = 16 * mapScre;		//列数

class Game;
typedef enum {
	STOP,				//游戏暂停
	PRESTART,		//游戏开始前
	RUN,				//游戏进行时
	GAMEOVER,		//游戏结束
	GAMEWIN,		//游戏胜利
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
		TTEnd,		//无实际意义，为了随机俄罗斯方块的类型时与墙面分离
		WALL		//墙面（空白）
	}ToolType;

private:
	//俄罗斯方块类
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
		//顺时针旋转
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

	static const int dx, dy;					//用于弥补场景边框距离
	static const int rePx, rePy;			//操纵的Tool的初始位置
	static const int waitPx, waitPy;	//等待初始位置
	static const int infoPx, infoPy;		//信息所绘制的位置

	Game();
	void Start();
	void Drop();
	int getDiff()const;
	GameMode getStatus()const;
	void ChangeStatus(GameMode);

	friend void Input(int data, int x, int y);
	friend void onDisplay();
	friend void Input(unsigned char nchar, int x, int y);
	friend void processMenuEvents(int option);

private:
//数据成员-------------------------

	GameMode status;
	int clearTimes;
	unsigned int zhywyt;
	//信息成员
	unsigned int _points;
	unsigned int PB_points;
	unsigned int Diff;
	
	unsigned int PB_Diff;
	bool PB;
	bool exZhywyt;
	//方块成员
	Tool m_tool;							//当前操控的Toll
	Tool m_next;							//展示的Tool
	vector<vector<int>>m_map;	//场景信息
	//文件流
	ifstream _ifs;
	ofstream _ofs;
//私有函数-------------------------
void NextTool();
void reset();
bool CanMoveDown();
bool CangetMoveRight();
bool CangetMoveLeft();
bool Rotate();
void GameOver();
void AddToMap();
bool Save(string FileName);
bool Load(string FileName);

};
#endif