// DesktopSnow.h : DesktopSnow 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "PicDLg.h"
#include<dmusici.h> 
#pragma comment(lib,"dxguid.lib") 

#define UM_ICONNOTIFY WM_USER+1009


#define  BIG_SNOW_NUM 14 // 大片雪花的数量
#define  SMALL_SNOW_NUM 16 //小片雪花数量

#define BIG_SNOW_KINDS						4 //大雪花的形态种类
#define SMALL_SNOW_KINDS					4 //小雪花的形态种类

#define ID_TIMER_MAIN_WND_CLOCK	1
#define ID_TIMER_BIG_SNOW_FALL			2
#define ID_TIMER_SMALL_SNOW_FALL	3
#define ID_TIMER_SNOW_CHANGE			4
#define ID_TIMER_SNOW_NEXT_STATE	5

#define SNOWNUM      500  // 雪花数量
#define CONTRAST     30    // 对比度
#define YSTART       5     // 用于确定雪花初始时的y坐标
#define SNOWCR       RGB(0xFF, 0xFF, 0xFF) //雪花的颜色—白色
#define SNOWGATHERCR RGB(0xDB, 0xDB, 0xFF) //堆积雪花的颜色


typedef struct tagSnow
{
	POINT ptSnowsPos[SNOWNUM]; //用于保存各个雪花的坐标
	COLORREF crOrg[SNOWNUM]; //用于画雪花前屏幕原来的颜色
	int iVx, iVy, iAllVx, iAllVy;
	//iVx雪花的x飘动速度,iAllVx雪花总体水平飘行速度
}Snow;

// CDesktopSnowApp:
// 有关此类的实现，请参阅 DesktopSnow.cpp
//

class CDesktopSnowApp : public CWinApp
{
public:
	CDesktopSnowApp();
~CDesktopSnowApp();

// 重写
public:
	virtual BOOL InitInstance();
	bool isNT;
// 实现

public:
	CWnd *pWnd;
	afx_msg void OnAppAbout();
public:
	afx_msg void OnMenuThanks();
	DECLARE_MESSAGE_MAP()
protected:
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
public:
	int cxScreen;
	int cyScreen;
	HINSTANCE hFuncInst ;
	typedef BOOL (WINAPI *MYFUNC)(HWND,HDC,POINT*,SIZE*,HDC,POINT*,COLORREF,BLENDFUNCTION*,DWORD);          
	MYFUNC UpdateLayeredWindow;


	//MIDI
	IDirectMusicPerformance*    performance; 
	IDirectMusicSegment*        segment    ; 
	IDirectMusicLoader*         loader     ; 


	//BLENDFUNCTION m_Blend;
	Image * m_pImageBigSnow[BIG_SNOW_KINDS];
	Image *m_pImageSmallSnow[SMALL_SNOW_KINDS];


	CPicDLg* BigSnow[ BIG_SNOW_NUM ];
	CPicDLg* SmallSnow[ SMALL_SNOW_NUM ];
	//音乐播放
	bool 	PlayMIDI(unsigned char* data,unsigned int size) ;
	void StopMIDI() ;
};

extern CDesktopSnowApp theApp;
//extern unsigned char midiMCData[0x9D5];

extern void initSnow(HDC hdc, Snow *sn, int iSnow, int cxScreen); // 初始化雪花
extern int GetContrast(HDC hdc, Snow *sn, int iSnow); // 获取对比度
extern void drawSnow(HDC hdc, Snow *sn, int cxScreen); // 画雪花
extern BOOL ImageFromIDResource(UINT nID, LPCTSTR sTR,Image * &pImg);