#define GLUT_DISABLE_ATEXIT_HACK
#define _CRT_SECURE_NO_WARNINGS
#include <gl/glut.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "Game.h"
#include "Reasource.h"
#include <math.h>
using namespace irrklang;

//关闭控制台
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
ISoundEngine* SoundEngine = createIrrKlangDevice();
ISound* RunSound=nullptr;


Game myGame;
void onReshape(int w, int h)
{
	// 设置视口大小
	glViewport(0, 0, w, h);
	// 切换矩阵模式为投影矩阵
	glMatrixMode(GL_PROJECTION);
	// 载入单位矩阵
	glLoadIdentity();
	// 进行二维平行投影
	gluOrtho2D(0, w, h, 0);
	// 切换矩阵模式为模型矩阵
	glMatrixMode(GL_MODELVIEW);
	// 发送重绘
	glutPostRedisplay();
}
void onDisplay()
{
	// 设置清屏颜色
	glClearColor(BCR_COLOR,1);
	// 用指定颜色清除帧缓存
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw Normal Info
	if (myGame.status == RUN || myGame.status == STOP) {
		//Draw BackGroud
		///Draw Dots
		for (int i = 0; i < Row; i++) {
			bool flag = true;
			for (int j = 0; j < Cow; j++) {
				switch (myGame.m_map[i][j]) {
				case 0:
					flag = false;
					break;
				case Game::LL:
					glColor3f(LL_COLOR);
					break;
				case Game::OO:
					glColor3f(OO_COLOR);
					break;
				case Game::DOT:
					glColor3f(DOT_COLOR);
					break;
				case Game::II:
					glColor3f(II_COLOR);
					break;
				case Game::TT:
					glColor3f(TT_COLOR);
					break;
				case Game::WALL:
					glColor3f(WALL_COLOR);
					break;
				default:
					glColor3f(ELSE_COLOR);
				}
				if (flag)
					glRectd(i * NodeSize, j * NodeSize, (i + 1) * NodeSize, (j + 1) * NodeSize);
				
				flag = true;
			}
		}

		//Draw Active Terix
		switch (myGame.m_tool._type) {
		case Game::LL:
			glColor3f(LL_COLOR);
			break;
		case Game::OO:
			glColor3f(OO_COLOR);
			break;
		case Game::DOT:
			glColor3f(DOT_COLOR);
			break;
		case Game::II:
			glColor3f(II_COLOR);
			break;
		case Game::TT:
			glColor3f(TT_COLOR);
			break;
		default:
			glColor3f(ELSE_COLOR);
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (myGame.m_tool._data[i][j])
					glRectd((myGame.m_tool._x + i) * NodeSize, (myGame.m_tool._y + j) * NodeSize, (myGame.m_tool._x + i + 1) * NodeSize, (myGame.m_tool._y + j + 1) * NodeSize);
			}
		}
		//Draw Waiting Terix
		switch (myGame.m_next._type) {
		case Game::LL:
			glColor3f(LL_COLOR);
			break;
		case Game::OO:
			glColor3f(OO_COLOR);
			break;
		case Game::DOT:
			glColor3f(DOT_COLOR);
			break;
		case Game::II:
			glColor3f(II_COLOR);
			break;
		case Game::TT:
			glColor3f(TT_COLOR);
			break;
		default:
			glColor3f(ELSE_COLOR);
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (myGame.m_next._data[i][j])
					glRectd((myGame.m_next._x + i) * NodeSize, (myGame.m_next._y + j) * NodeSize, (myGame.m_next._x + i + 1) * NodeSize, (myGame.m_next._y + j + 1) * NodeSize);
			}
		}
		///Drw Mesh
		glPointSize(LineSize);
		glColor3f(LINE_COLOR);
		for (int i = Game::dx; i <= GameRow; i++) {
			for (int j = 0; j <= GameCow * NodeSize; j += LineSize) {
				glBegin(GL_POINTS);
				glVertex2d(i * NodeSize, j);
				glEnd();
			}
		}
		for (int i = Game::dx; i <= GameCow; i++) {
			for (int j = Game::dx * NodeSize; j <= (GameRow + Game::dx) * NodeSize; j += LineSize) {
				glBegin(GL_POINTS);
				glVertex2d(j, i * NodeSize);
				glEnd();
			}
		}

		//Draw Info
		const char points[20] = "Points:", PBpoints[20] = "PB:", Diff[20] = "Rank:",zhywyt[]="zhywyt:",DiffMode[20]="Diff Mode:";
		char points_num[20], PBpoints_num[20], Diff_num[20],zhywyt_num[20],DiffMode_num[20];
		sprintf(points_num, "%d", myGame._points);
		sprintf(PBpoints_num, "%d", myGame.PB_points);
		sprintf(Diff_num, "%d", myGame.Diff);
		sprintf(zhywyt_num, "%d", myGame.zhywyt);
		string str;
		switch (myGame.getDiffMode()) {
		case EASY:
			str = "Easy";
			break;
		case NORMAL:
			str = "Normal";
			break;
		case HARD:
			str = "Hard";
			break;
		default: {
				str = " ";
				break;
			}
		}
		sprintf(DiffMode_num, "%s",str.c_str());
		const char* strinfo[] = { points,PBpoints,DiffMode,Diff,zhywyt};
		char* str_num[] = { points_num,PBpoints_num,Diff_num ,DiffMode_num,zhywyt_num };
		if (!myGame.PB)
			glColor3f(TEXT_COLOR);
		else 
			glColor3f(PB_TEXT_COLOR);
		for (int i = 0; i < 5; i++) {
			if (i == 4)glColor3f(PB_TEXT_COLOR);
			if (i == 3) {
				switch (myGame.getDiffMode()) {
				case NORMAL:
					glColor3f(RGB(0,0,255));
					break;
				case HARD:
					glColor3f(RGB(255, 0, 0));
					break;
				}
			}
			glRasterPos2d(Game::infoPx * NodeSize, (Game::infoPy + 4 * i) * NodeSize);
			for (int j = 0; strinfo[i][j] != '\0'; j++)glutBitmapCharacter(INFO_FONT, strinfo[i][j]);
			glRasterPos2d(Game::infoPx * NodeSize, (Game::infoPy + 4 * i + 2) * NodeSize);
			for (int j = 0; str_num[i][j] != '\0'; j++)glutBitmapCharacter(INFO_FONT, str_num[i][j]);
		}
		//Draw Stop Info
		if (myGame.status == STOP) {
			const char PrestartInfo[30] = "Press Space to start.";
			glRasterPos2d((Game::dx)*NodeSize, (GameCow + 3 * Game::dx) / 2 * NodeSize);
			glColor3f(TEXT_COLOR);
			for (int i = 0; PrestartInfo[i] != '\0'; i++)
				glutBitmapCharacter(INFO_FONT, PrestartInfo[i]);
		}
	}
	//Draw Prestart info
	else {
		if (myGame.status == GAMEOVER) {
			//Draw gameover info
			const char GameOverinfo[30] = "Game Over!";
			char Score[30], Points[30];
			sprintf(Points, "%d", myGame._points);
			const char* VAO[3] = { GameOverinfo,Score,Points };
			if (!myGame.PB) {
				glColor3f(GAMEOVER_TEXT_COLOR);
				sprintf(Score, "Your score is ");
			}
			else {
				glColor3f(PB_TEXT_COLOR);
				sprintf(Score, "WoW!! PB! ");
			}
			for (int i = 0; i < 3; i++) {
				glRasterPos2d((Game::dx * 2) * NodeSize, ((GameCow - 4 * Game::dx) / 2+i*2*Game::dx) * NodeSize);
				for (int j = 0; VAO[i][j] != '\0'; j++)
					glutBitmapCharacter(INFO_FONT, VAO[i][j]);
			}
			char Good[40];
			if (myGame.exZhywyt) {
				sprintf(Good, "You are great ! You over the zhywyt!!");
			}
			else {
				sprintf(Good, "Git Gud.");
			}
			glRasterPos2d((Game::dx * 2)* NodeSize, ((GameCow-4*Game::dx ) / 2+6*Game::dx) * NodeSize);
			for (int j = 0;Good[j] != '\0'; j++)
				glutBitmapCharacter(INFO_FONT, Good[j]);

		}
		else if (myGame.status == GAMEWIN) {
			//It is imposible!!!!!
			const char Info1[30] = "You may use something else", Info2[30] = "To do this imposible task.";
			const char* str[] = { Info1,Info2 };
			glColor3f(RGB(255, 0, 255));
			for (int i = 0; i < 2; i++) {
				glRasterPos2d((Game::dx * 2) * NodeSize, (GameCow + (i * 3 + 1) * Game::dx) / 2 * NodeSize);
				for (int j = 0;str[i][j] != '\0'; j++)
					glutBitmapCharacter(INFO_FONT, str[i][j]);
			}
		}
		else if (myGame.status == GAMERANKLIST) {
			const unsigned char YourInfo[] = "Your Rank List";
			int length = glutBitmapLength(INFO_FONT, YourInfo) / 14;
			char YourScore[12][15];
			int YourScoreLength[30];
			auto ibeg = myGame.RankList.rbegin();
			int len;
			for (len = 0; len < 12 && ibeg != myGame.RankList.rend(); len++, ibeg++) {
				string str;;
				switch (ibeg->second) {
				case EASY:
					str = "Easy";
					break;
				case NORMAL:
					str = "Normal";
					break;
				case HARD:
					str = "Hard";
					break;
				}
				sprintf(YourScore[len], "%d    %s", ibeg->first,str.c_str());
				YourScoreLength[len] = length * strlen(YourScore[len]);
			}
			//Draw Title
			glRasterPos2d((Row * NodeSize - length * 14) / 2, Game::dx * NodeSize);
			for (int i = 0; YourInfo[i] != '\0'; i++) {
				glutBitmapCharacter(INFO_FONT, YourInfo[i]);
			}
			//Draw Number
			for (int i = 0; i < len; i++) {
				glRasterPos2d((Row * NodeSize - YourScoreLength[i]) / 2, (i * 2 + 3 * Game::dx) * NodeSize);
				for (int j = 0; YourScore[i][j] != '\0'; j++) {
					glutBitmapCharacter(INFO_FONT, YourScore[i][j]);
				}
			}
		}
		else {
			const char helpInfo1[] = "Your Can Press the Space to stop Game.";
			const char helpInfo2[] = "And you can click the right butttom to-";
			const char helpInfo21[] = "-open the emun";
			const char helpInfo3[] = "You should use the emnu \"exit\" to exit-";
			const char helpInfo31[] = "-not close the window";
			const char PrestartInfo[30] = "Press Space to start.";
			const char LuckInfo[] = "Have Good Time!";
			char DiffMode_num[20];
			string str1;
			switch (myGame.getDiffMode()) {
			case EASY:
				str1 = "Easy";
				break;
			case NORMAL:
				str1 = "Normal";
				break;
			case HARD:
				str1 = "Hard";
				break;
			default: {
				str1 = " ";
				break;
			}
			}
			sprintf(DiffMode_num, "DiffMode : % s" ,str1.c_str());
			const char* DiffMode = DiffMode_num;
			const char* str[] = { DiffMode,PrestartInfo,helpInfo31,helpInfo3,helpInfo21,helpInfo2,helpInfo1 };
			glColor3f(TEXT_COLOR);
			for (int j = 6; j >=0; j--) {
				if (j == 0) {
					switch (myGame.getDiffMode()) {
					case NORMAL:
						glColor3f(RGB(0, 0, 255));
						break;
					case HARD:
						glColor3f(RGB(255, 0, 0));
						break;
					}
				}
			glRasterPos2d((Game::dx)*NodeSize, ((GameCow + 9 * Game::dx) / 2-j*2 )* NodeSize);
				for (int i = 0; str[j][i] != '\0'; i++)
					glutBitmapCharacter(INFO_FONT, str[j][i]);
			}
			glColor3f(PB_TEXT_COLOR);
			glRasterPos2d((Game::dx)*NodeSize, ((GameCow + 12 * Game::dx)/2* NodeSize));
			for (int i = 0; LuckInfo[i] != '\0'; i++)
				glutBitmapCharacter(INFO_FONT, LuckInfo[i]);
		}
	}
	//Clear Buffer
	glutSwapBuffers();
}
//简单键盘输入
void Input(unsigned char nchar, int x, int y) {
	if (nchar == GLUT_KEY_ESCAPE) {
		//退出前保存数据
		myGame.GameOver();
		int status, cleartimes;
		ifstream ifs("AutoSace.zhywyt", ifstream::in);
		if (ifs) {
			ifs >> status >> cleartimes;
			if (cleartimes < myGame.clearTimes) {
				myGame.Save("AutoSave.zhywyt"); 
			}
			ifs.close();
		}
		SoundEngine->drop();
		exit(0);
	}
	//全部转化为大写进行处理
	if (nchar >= 'a' && nchar <= 'z')nchar += 'A' - 'a';
		Input((int)nchar, x, y);
}
//特殊键盘输入
void Input( int nchar, int x, int y){
	//处理游戏时的输入
	if (myGame.status == RUN) {	
		if (nchar == GLUT_KEY_UP || nchar == GLFW_KEY_W) {
			if (myGame.Rotate()) {
				if (myGame.getMusicStatus())
					SoundEngine->play2D(MUSIC_ROTATE, GL_FALSE);
			}
		}
		else if (nchar == GLFW_KEY_S || nchar == GLUT_KEY_DOWN) {
			if (myGame.Drop()) {
				//为了让自动下坠的时候不发出声音
				if (myGame.getMusicStatus())
					SoundEngine->play2D(MUSIC_DROP, GL_FALSE);
			}
		}
		else if (nchar == GLFW_KEY_A || nchar == GLUT_KEY_LEFT) {
			if (myGame.CanMoveLeft())
			{
				myGame.m_tool.MoveLeft();
				if (myGame.getMusicStatus())
				SoundEngine->play2D(MUSIC_MOVE, GL_FALSE);
			}
		}
		else if (nchar == GLFW_KEY_D || nchar == GLUT_KEY_RIGHT) {
			if (myGame.CanMoveRight()) {
				myGame.m_tool.MoveRight();
				if (myGame.getMusicStatus())
				SoundEngine->play2D(MUSIC_MOVE, GL_FALSE);
			}
		}
		else if (nchar == GLFW_KEY_SPACE) {
			if (myGame.status == GAMEOVER) {
				myGame.status = PRESTART;
				myGame.reset();
			}
			else if (myGame.status == RUN) {
				myGame.status = STOP;
				if (RunSound) {
					RunSound->setIsPaused(GL_TRUE);
				}
			}
		}
	}	
	//处理暂停时的输入
	else if (myGame.status == STOP ) {
		if (nchar == GLFW_KEY_SPACE) {
			myGame.status = RUN;
			if(RunSound)
			RunSound->setIsPaused(GL_FALSE);
		}
	}
	//处理游戏开始前的输入
	else if (myGame.status == PRESTART) {
		if (nchar == GLFW_KEY_SPACE) {
			myGame.Start();
		}
	}
	//处理结束的操作
	else if (myGame.status == GAMEOVER) {
		if(nchar==GLFW_KEY_SPACE)
		myGame.reset();
	}
	else if (myGame.status == GAMEWIN) {
		if (nchar)exit(0);

	}
	else if (myGame.status == GAMERANKLIST) {
		if (nchar == GLFW_KEY_SPACE) {
			myGame.ChangeStatus(PRESTART);
		}
	}
}
void Ontime(int timeid) {
	timeid++;
	timeid %= 1000;
	int Deltatime;
	if(myGame.getStatus() == RUN)
		myGame.Drop();
	switch (myGame.getDiffMode()) {
	case EASY: {
		Deltatime = 200 - static_cast<int>(4.5 *pow(myGame.getDiff(),2/3.0));
		break;
	}
	case NORMAL: {
		Deltatime = 150 - static_cast<int>(4.5 * pow(myGame.getDiff(), 2 / 3.0));
		break;
	}
	case HARD: {
		Deltatime = 150 - 3 * myGame.getDiff();
	}
	default:
		Deltatime = 150;
	}
	//It is imposible!!!
	if (Deltatime <= 50)myGame.ChangeStatus(GAMEWIN) ;
	onDisplay();
	glutTimerFunc(Deltatime, Ontime, 1);
}
void processMenuEvents(int option) {
	switch (option) {
	case CHECKBEST:
		//Version2
		myGame.ChangeStatus(GAMERANKLIST);
		break;
	case RUN:
		if (myGame.status == PRESTART)myGame.Start();
		myGame.status = RUN;
		break;
	case GAMEOVER: {
		myGame.GameOver();
		int status, cleartimes;
		ifstream ifs("AutoSace.zhywyt", ifstream::in);
		if (ifs) {
			ifs >> status >> cleartimes;
			if (cleartimes < myGame.clearTimes) {
				myGame.Save("AutoSave.zhywyt");
			}
			ifs.close();
		}
		SoundEngine->drop();
		exit(0);
		break;
	}
	case PRESTART:
		myGame.status = PRESTART;
		myGame.GameOver();
		myGame.reset();
		//添加重置的操作
		break;
	case STOP:
		if(myGame.status!=PRESTART)
		myGame.status = STOP;
		break;
	case MUSICON:
		myGame.setMusicStatus(GL_TRUE);
		if (RunSound) {
			RunSound->stop();
		}
		RunSound = SoundEngine->play2D(MUSIC_RUN, GL_TRUE, GL_FALSE, GL_TRUE);
		if (myGame.getStatus() == STOP&&RunSound)RunSound->setIsPaused(GL_TRUE);
		break;
	case MUSICOFF:
		myGame.setMusicStatus(GL_FALSE);
		if (RunSound) {
			RunSound->drop();
		}
		break;
	}
	if (option >= SAVE1 && option <= SAVE3) {
		if (myGame.getStatus() != PRESTART) {
			int index = option - SAVE1 + 1;
			char FileName[30];
			sprintf(FileName, "Save%d.zhywyt", index);
			string name(FileName);
			if (myGame.Save(name))
				myGame.ChangeStatus(STOP);
		}
	}
	else if (option >= LOAD1 && option <= LOAD3) {
		int index = option - LOAD1 + 1;
		char FileName[30];
		sprintf(FileName, "Save%d.zhywyt", index);
		string name(FileName);
		if(myGame.Load(name))
			myGame.ChangeStatus(STOP);
		else {
			myGame.reset();
			myGame.ChangeStatus(PRESTART);
		}
	}
	else if (option == LOADAUTOSAVE) {
		if(myGame.Load("AutoSave.zhywyt"))
			myGame.ChangeStatus(STOP);
	}
	else if (option >= EASY && option <= HARD) {
		if(myGame.getStatus()!=RUN&&myGame.getStatus()!=STOP)
		myGame.setDiffMode(DIFFMODE(option));
	}
}
void createGLUTMenus() {
	//菜单ID
	int menu,Optionmenu, Savemenu, Loadmenu,Diffmenu,Musicmenu;
	//设置回调函数processMenuEvents()，获取与之对于的菜单ID

	//Opetion Sub Menu
	Musicmenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("On", MUSICON);
	glutAddMenuEntry("Off", MUSICOFF);
	Diffmenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Easy", EASY);
	glutAddMenuEntry("Normal", NORMAL);
	glutAddMenuEntry("Hard!", HARD);

	Optionmenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Start", RUN);
	glutAddMenuEntry("Reset", PRESTART);
	glutAddSubMenu("setDiff",Diffmenu);
	glutAddSubMenu("Music", Musicmenu);
	glutAddMenuEntry("RankList", CHECKBEST);

	Savemenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Save1", SAVE1);
	glutAddMenuEntry("Save2", SAVE2);
	glutAddMenuEntry("Save3", SAVE3);
	Loadmenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Load1", LOAD1);
	glutAddMenuEntry("Load2", LOAD2);
	glutAddMenuEntry("Load3", LOAD3);
	glutAddMenuEntry("LoadAutoSave", LOADAUTOSAVE);
	menu = glutCreateMenu(processMenuEvents);
	//设置父菜单
	glutAddMenuEntry("Stop", STOP);
	glutAddSubMenu("Option", Optionmenu);
	glutAddSubMenu("Save", Savemenu);
	glutAddSubMenu("LoadSave", Loadmenu);
	glutAddMenuEntry("Exit", GAMEOVER);
	//绑定鼠标点击
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char* argv[])
{
	// 初始化 glut
	glutInit(&argc, argv);
	// 设置 OpenGL 显示模式(双缓存, RGB 颜色模式)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// 设置窗口初始尺寸
	glutInitWindowSize(Row*NodeSize, Cow*NodeSize);
	// 设置窗口初始位置
	glutInitWindowPosition(100, 100);
	// 设置窗口标题
	glutCreateWindow("Terix");


	//设置输入回调函数
	glutKeyboardFunc(Input);
	glutSpecialFunc(Input);
	// 设置显示回调函数
	glutDisplayFunc(onDisplay);
	//设置计时器
	glutTimerFunc(150-3*myGame.getDiff(), Ontime, 1);
	// 设置窗口尺寸变化回调函数
	glutReshapeFunc(onReshape);
	// 设置菜单
	createGLUTMenus();
	// 进入 glut 事件循环
	glutMainLoop();
	SoundEngine->drop();
	return 0;
}

