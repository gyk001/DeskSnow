#pragma once
#include "DesktopSnow.h"
#include <atlimage.h>
// CDesktopSnowWnd

class CDesktopSnowWnd : public CWnd
{
	DECLARE_DYNAMIC(CDesktopSnowWnd)

public:
	CDesktopSnowWnd();
	virtual ~CDesktopSnowWnd();

protected:
	DECLARE_MESSAGE_MAP()

	RECT         rect ;
	int iTimes;
	int iLoopTimes;
	Snow snowDream;
	UINT_PTR timer_snow;
	UINT_PTR timer_clock;

	//CPicDLg* DlgArray[BIG_SNOW_SIZE];

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnIconNotify(WPARAM wParam, LPARAM lParam);
	void DeleteIcon(void);
	void AddNotifyIcon(void);

public:
	afx_msg void OnMenuExit();
public:
	afx_msg void OnPaint();
public:
	BOOL ImageFromIDResource(UINT nID,LPCTSTR sTR,Image * &pImg);
	BOOL UpdateClockDisplay(int Transparent=255);

	BLENDFUNCTION m_Blend;
	HDC m_hdcMemory;
	Image *m_pImageClock;
	Image *m_pImageClock1;
	Image *m_pImageHHour;
	Image *m_pImageHMinu;
	Image *m_pImageHSec;
	Image *m_pImageNum;
	int m_BakWidth , m_BakHeight ;
	int m_HourWidth, m_HourHeight;
	int m_MinuWidth , m_MinuHeight;
	int m_SecWidth  , m_SecHeight ;
	HINSTANCE hFuncInst ;
	typedef BOOL (WINAPI *MYFUNC)(HWND,HDC,POINT*,SIZE*,HDC,POINT*,COLORREF,BLENDFUNCTION*,DWORD);          
	MYFUNC UpdateLayeredWindow;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


