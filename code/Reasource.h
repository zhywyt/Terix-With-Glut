#ifndef REASOURCE_H
#define REASOURCE_H
#define GLUT_KEY_ESCAPE 27
#define RGB(a,b,c) (a/255.0),(b/255.0),(c/255.0)			//����255ת0.0-1.0
#define BCR_COLOR RGB(0,0,0)								//������ɫ

//���ж���˹�������ɫ
#define LL_COLOR RGB(0,255,0)									
#define OO_COLOR RGB(255,0,0)
#define DOT_COLOR RGB(255,255,255)
#define II_COLOR RGB(0,255,255)
#define TT_COLOR RGB(164, 225, 202)
#define ELSE_COLOR RGB(0,0,0)
#define WALL_COLOR RGB(100,255,0)

//״̬��ɫ
#define TEXT_COLOR RGB(255,255,255)
#define GAMEOVER_TEXT_COLOR RGB(255,0,0)
#define PB_TEXT_COLOR RGB(0,255,0)

//��������
#define INFO_FONT GLUT_BITMAP_TIMES_ROMAN_24

#endif