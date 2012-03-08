// DesktopSnow.h : DesktopSnow Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "PicDLg.h"
#include<dmusici.h> 
#pragma comment(lib,"dxguid.lib") 

#define UM_ICONNOTIFY WM_USER+1009


#define  BIG_SNOW_NUM 14 // ��Ƭѩ��������
#define  SMALL_SNOW_NUM 16 //СƬѩ������

#define BIG_SNOW_KINDS						4 //��ѩ������̬����
#define SMALL_SNOW_KINDS					4 //Сѩ������̬����

#define ID_TIMER_MAIN_WND_CLOCK	1
#define ID_TIMER_BIG_SNOW_FALL			2
#define ID_TIMER_SMALL_SNOW_FALL	3
#define ID_TIMER_SNOW_CHANGE			4
#define ID_TIMER_SNOW_NEXT_STATE	5

#define SNOWNUM      500  // ѩ������
#define CONTRAST     30    // �Աȶ�
#define YSTART       5     // ����ȷ��ѩ����ʼʱ��y����
#define SNOWCR       RGB(0xFF, 0xFF, 0xFF) //ѩ������ɫ����ɫ
#define SNOWGATHERCR RGB(0xDB, 0xDB, 0xFF) //�ѻ�ѩ������ɫ


typedef struct tagSnow
{
	POINT ptSnowsPos[SNOWNUM]; //���ڱ������ѩ��������
	COLORREF crOrg[SNOWNUM]; //���ڻ�ѩ��ǰ��Ļԭ������ɫ
	int iVx, iVy, iAllVx, iAllVy;
	//iVxѩ����xƮ���ٶ�,iAllVxѩ������ˮƽƮ���ٶ�
}Snow;

// CDesktopSnowApp:
// �йش����ʵ�֣������ DesktopSnow.cpp
//

class CDesktopSnowApp : public CWinApp
{
public:
	CDesktopSnowApp();
~CDesktopSnowApp();

// ��д
public:
	virtual BOOL InitInstance();
	bool isNT;
// ʵ��

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
	//���ֲ���
	bool 	PlayMIDI(unsigned char* data,unsigned int size) ;
	void StopMIDI() ;
};

extern CDesktopSnowApp theApp;
//extern unsigned char midiMCData[0x9D5];

extern void initSnow(HDC hdc, Snow *sn, int iSnow, int cxScreen); // ��ʼ��ѩ��
extern int GetContrast(HDC hdc, Snow *sn, int iSnow); // ��ȡ�Աȶ�
extern void drawSnow(HDC hdc, Snow *sn, int cxScreen); // ��ѩ��
extern BOOL ImageFromIDResource(UINT nID, LPCTSTR sTR,Image * &pImg);