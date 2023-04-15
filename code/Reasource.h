#ifndef REASOURCE_H
#define REASOURCE_H
#endif
//版本信息
#define TERIX_VERSION_2

#define GLUT_KEY_ESCAPE 27
#define RGB(a,b,c) (a/255.0),(b/255.0),(c/255.0)			//用于255转0.0-1.0

#ifdef TERIX_VERSION_1
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
#define LINE_COLOR RGB(200,200,200)

#endif

#ifdef TERIX_VERSION_2

//颜色
#define BCR_COLOR RGB(224,237,253)								//背景颜色

//所有俄罗斯方块的颜色
#define LL_COLOR RGB(250,210,229)									
#define OO_COLOR RGB(191,240,210)
#define DOT_COLOR RGB(251,185,207)
#define II_COLOR RGB(250,237,205)
#define TT_COLOR RGB(214, 204, 239)
#define ELSE_COLOR RGB(200,224,212)
#define WALL_COLOR RGB(120,197,227)

//状态颜色
#define TEXT_COLOR RGB(0,0,0)
#define GAMEOVER_TEXT_COLOR RGB(255,0,0)
#define PB_TEXT_COLOR RGB(120,197,227)
#define LINE_COLOR RGB(200,200,200)

#endif

//字体设置
#define INFO_FONT GLUT_BITMAP_TIMES_ROMAN_24
//Music
#define MUSIC_RUN "Reasourse//Music//Technotris.flac"
#define MUSIC_BREAK "Reasourse//Music//Break1.wav"
#define MUSIC_BREAK_2 "Reasourse//Music//Break2.mp3"

#define MUSIC_DROP "Reasourse//Music//Move.wav"
#define MUSIC_MOVE "Reasourse//Music//Move.wav"
#define MUSIC_ROTATE "Reasourse//Music//Rotate.wav"
#define MUSIC_GAMEOVER "Reasourse//Music//GameOver.mp3"




