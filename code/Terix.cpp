#define GLUT_DISABLE_ATEXIT_HACK
#define _CRT_SECURE_NO_WARNINGS
#include <gl/glut.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "Game.h"
#include "Reasource.h"
//�رտ���̨
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

Game myGame;
void onReshape(int w, int h)
{
	// �����ӿڴ�С
	glViewport(0, 0, w, h);
	// �л�����ģʽΪͶӰ����
	glMatrixMode(GL_PROJECTION);
	// ���뵥λ����
	glLoadIdentity();
	// ���ж�άƽ��ͶӰ
	gluOrtho2D(0, w, h, 0);
	// �л�����ģʽΪģ�;���
	glMatrixMode(GL_MODELVIEW);
	// �����ػ�
	glutPostRedisplay();
}
void onDisplay()
{
	// ����������ɫ
	glClearColor(BCR_COLOR,1);
	// ��ָ����ɫ���֡����
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw Normal Info
	if (myGame.status!=PRESTART&&myGame.status!=GAMEOVER&&myGame.status!=GAMEWIN) {
		//Draw BackGroud
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
		//Draw Info
		const char points[20] = "Points:", PBpoints[20] = "PB:", Diff[20] = "Rank:",zhywyt[]="zhywyt:";
		char points_num[20], PBpoints_num[20], Diff_num[20],zhywyt_num[20];
		sprintf(points_num, "%d", myGame._points);
		sprintf(PBpoints_num, "%d", myGame.PB_points);
		sprintf(Diff_num, "%d", myGame.Diff);
		sprintf(zhywyt_num, "%d", myGame.zhywyt);

		const char* strinfo[] = { points,PBpoints,Diff,zhywyt };
		char* str_num[] = { points_num,PBpoints_num,Diff_num ,zhywyt_num};
		if (!myGame.PB)
			glColor3f(TEXT_COLOR);
		else 
			glColor3f(PB_TEXT_COLOR);
		for (int i = 0; i < 4; i++) {
			if (i == 3)glColor3f(PB_TEXT_COLOR);
			glRasterPos2d(Game::infoPx * NodeSize, (Game::infoPy + 5 * i) * NodeSize);
			for (int j = 0; strinfo[i][j] != '\0'; j++)glutBitmapCharacter(INFO_FONT, strinfo[i][j]);
			glRasterPos2d(Game::infoPx * NodeSize, (Game::infoPy + 5 * i + 2) * NodeSize);
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
		else {
			const char helpInfo1[] = "Your Can Press the Space to stop Game.";
			const char helpInfo2[] = "And you can click the right butttom to-";
			const char helpInfo21[] = "-open the emun";
			const char helpInfo3[] = "You should use the emnu \"exit\" to exit-";
			const char helpInfo31[] = "-not close the window";
			const char PrestartInfo[30] = "Press Space to start.";
			const char LuckInfo[] = "Have Good Time!";
			const char* str[] = {PrestartInfo,helpInfo31,helpInfo3,helpInfo21,helpInfo2,helpInfo1 };
			glColor3f(TEXT_COLOR);
			for (int j = 5; j >=0; j--) {
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
//�򵥼�������
void Input(unsigned char nchar, int x, int y) {
	if (nchar == GLUT_KEY_ESCAPE) {
		//�˳�ǰ��������
		myGame.GameOver();
		myGame.Save("AutoSave.zhywyt");
		exit(0);
	}
	//ȫ��ת��Ϊ��д���д���
	if (nchar >= 'a' && nchar <= 'z')nchar += 'A' - 'a';
		Input((int)nchar, x, y);
}
//�����������
void Input( int nchar, int x, int y){
	//������Ϸʱ������
	if (myGame.status == RUN) {	
		if (nchar == GLUT_KEY_UP || nchar == GLFW_KEY_W) {
			myGame.Rotate();
		}
		else if (nchar == GLFW_KEY_S || nchar == GLUT_KEY_DOWN) {
			myGame.Drop();
		}
		else if (nchar == GLFW_KEY_A || nchar == GLUT_KEY_LEFT) {
			if (myGame.CangetMoveLeft())
				myGame.m_tool.MoveLeft();
		}
		else if (nchar == GLFW_KEY_D || nchar == GLUT_KEY_RIGHT) {
			if (myGame.CangetMoveRight())
				myGame.m_tool.MoveRight();
		}
		else if (nchar == GLFW_KEY_SPACE) {
			if (myGame.status == GAMEOVER) {
				myGame.status = PRESTART;
				myGame.reset();
			}
			else if (myGame.status == RUN) {
				myGame.status = STOP;
			}
		}
	}	
	//������ͣʱ������
	else if (myGame.status == STOP ) {
		if (nchar == GLFW_KEY_SPACE) {
			myGame.status = RUN;
		}
	}
	//������Ϸ��ʼǰ������
	else if (myGame.status == PRESTART) {
		if (nchar == GLFW_KEY_SPACE) {
			myGame.Start();
		}
	}
	//��������Ĳ���
	else if (myGame.status == GAMEOVER) {
		if(nchar==GLFW_KEY_SPACE)
		myGame.reset();
	}
	else if (myGame.status == GAMEWIN) {
		if (nchar)exit(0);
	}
}
void Ontime(int timeid) {
	timeid++;
	timeid %= 1000;
	if(myGame.getStatus() == RUN)
		myGame.Drop();
	int Deltatime = 150 - 3 * myGame.getDiff();
	//It is imposible!!!
	if (Deltatime <= 50)myGame.ChangeStatus(GAMEWIN) ;
	onDisplay();
	glutTimerFunc(Deltatime, Ontime, 1);
}
void processMenuEvents(int option) {
	switch (option) {
	//case CHECKBEST:
	//	//�Ժ������ɡ�
	//	break;
	case RUN:
		if (myGame.status == PRESTART)myGame.Start();
		myGame.status = RUN;
		break;
	case GAMEOVER:
		myGame.GameOver();
		myGame.Save("AutoSave.zhywyt");
		exit(0);
		break;
	case PRESTART:
		myGame.status = PRESTART;
		myGame.GameOver();
		myGame.reset();
		//������õĲ���
		break;
	case STOP:
		if(myGame.status!=PRESTART)
		myGame.status = STOP;
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
}
void createGLUTMenus() {
	//�˵�ID
	int menu,submenu, Savemenu, Loadmenu;
	//���ûص�����processMenuEvents()����ȡ��֮���ڵĲ˵�ID
	submenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Start", RUN);
	glutAddMenuEntry("Reset", PRESTART);
	//�Ժ�����
	//glutAddMenuEntry("Check My Best", CHECKBEST);
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
	//���ø��˵�
	glutAddMenuEntry("Stop", STOP);
	glutAddSubMenu("Option", submenu);
	glutAddSubMenu("Save", Savemenu);
	glutAddSubMenu("LoadSave", Loadmenu);
	glutAddMenuEntry("Exit", GAMEOVER);
	//�������
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char* argv[])
{
	// ��ʼ�� glut
	glutInit(&argc, argv);
	// ���� OpenGL ��ʾģʽ(˫����, RGB ��ɫģʽ)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// ���ô��ڳ�ʼ�ߴ�
	glutInitWindowSize(Row*NodeSize, Cow*NodeSize);
	// ���ô��ڳ�ʼλ��
	glutInitWindowPosition(100, 100);
	// ���ô��ڱ���
	glutCreateWindow("Terix");
	//��������ص�����
	glutKeyboardFunc(Input);
	glutSpecialFunc(Input);
	// ������ʾ�ص�����
	glutDisplayFunc(onDisplay);
	//���ü�ʱ��
	glutTimerFunc(150-3*myGame.getDiff(), Ontime, 1);
	// ���ô��ڳߴ�仯�ص�����
	glutReshapeFunc(onReshape);
	// ���ò˵�
	createGLUTMenus();
	// ���� glut �¼�ѭ��
	glutMainLoop();
	return 0;
}

