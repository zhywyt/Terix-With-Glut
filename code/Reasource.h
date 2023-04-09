#ifndef REASOURCE_H
#define REASOURCE_H
#define GLUT_KEY_ESCAPE 27
#define RGB(a,b,c) (a/255.0),(b/255.0),(c/255.0)			//用于255转0.0-1.0
#define BCR_COLOR RGB(0,0,0)								//背景颜色

//所有俄罗斯方块的颜色
#define LL_COLOR RGB(0,255,0)									
#define OO_COLOR RGB(255,0,0)
#define DOT_COLOR RGB(255,255,255)
#define II_COLOR RGB(0,255,255)
#define TT_COLOR RGB(164, 225, 202)
#define ELSE_COLOR RGB(0,0,0)
#define WALL_COLOR RGB(100,255,0)

//状态颜色
#define TEXT_COLOR RGB(255,255,255)
#define GAMEOVER_TEXT_COLOR RGB(255,0,0)
#define PB_TEXT_COLOR RGB(0,255,0)

//字体设置
#define INFO_FONT GLUT_BITMAP_TIMES_ROMAN_24

#endif