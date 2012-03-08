// DesktopSnowWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DesktopSnow.h"
#include "DesktopSnowWnd.h"


// CDesktopSnowWnd

IMPLEMENT_DYNAMIC(CDesktopSnowWnd, CWnd)

CDesktopSnowWnd::CDesktopSnowWnd()
{

}

CDesktopSnowWnd::~CDesktopSnowWnd()
{

}


BEGIN_MESSAGE_MAP(CDesktopSnowWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_MESSAGE(UM_ICONNOTIFY, OnIconNotify)
	ON_COMMAND(ID_MENU_ABOUT, &CDesktopSnowApp::OnAppAbout)
	ON_COMMAND(ID_MENU_THANKS, &CDesktopSnowApp::OnMenuThanks)
	ON_COMMAND(ID_MENU_EXIT, &CDesktopSnowWnd::OnMenuExit)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()

	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CDesktopSnowWnd ��Ϣ�������



int CDesktopSnowWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
//////////////////////////////////////////////////////////////////////////
	BOOL bRet=FALSE;

	//��ʼ��gdiplus�Ļ���
	// Initialize GDI+.
	m_Blend.BlendOp=0; //theonlyBlendOpdefinedinWindows2000
	m_Blend.BlendFlags=0; //nothingelseisspecial...
	m_Blend.AlphaFormat=1; //...
	m_Blend.SourceConstantAlpha=255;//AC_SRC_ALPHA

	ImageFromIDResource(IDR_PNGNUM,"PNG",m_pImageNum);
	ImageFromIDResource(IDR_PNGBAK1,"PNG",m_pImageClock1);
	ImageFromIDResource(IDR_PNGBAK,"PNG",m_pImageClock);
	ImageFromIDResource(IDR_PNGHOUR,"PNG",m_pImageHHour);
	ImageFromIDResource(IDR_PNGMIN,"PNG",m_pImageHMinu);
	ImageFromIDResource(IDR_PNGSEC,"PNG",m_pImageHSec);
	m_BakWidth  =m_pImageClock->GetWidth();
	m_BakHeight =m_pImageClock->GetHeight();
	m_HourWidth =m_pImageHHour->GetWidth();
	m_HourHeight=m_pImageHHour->GetHeight();
	m_MinuWidth =m_pImageHMinu->GetWidth();
	m_MinuHeight=m_pImageHMinu->GetHeight();
	m_SecWidth  =m_pImageHSec->GetWidth();
	m_SecHeight =m_pImageHSec->GetHeight();
	::SetWindowPos(m_hWnd, HWND_TOPMOST,0,0,m_BakWidth,m_BakHeight,SWP_NOSIZE|SWP_NOMOVE);  
	//////////////////////////////////////////////////////////////////////////


	srand ((int) GetCurrentTime ()) ; //��ʼ�������������
	
	HDC hdc = ::GetDC(NULL); //����������Ļ���豸�����Ļ���
	
	//XP ��2000 ϵͳ����ѩ���ѻ�Ч��
	if( theApp.isNT)
	{
		snowDream.iAllVx = (unsigned)rand()%3 - 1; //ѩ������ˮƽƮ���ٶ�(-1,0,1)
		snowDream.iAllVy = (unsigned)rand()%2 + 1; //ѩ�����崹ֱ�����ٶ�(1,2)
		for(int i=0; i<SNOWNUM; i++)
		{
			snowDream.ptSnowsPos[i].x = rand() % theApp.cxScreen; //һ��ѩ����ʼ�����x����
			snowDream.ptSnowsPos[i].y = rand() % YSTART; //һ��ѩ����ʼ�����y����
			snowDream.crOrg[i] = ::GetPixel(hdc, snowDream.ptSnowsPos[i].x,
				snowDream.ptSnowsPos[i].y); //��ȡ�������ԭ������ɫֵ
		}
		timer_snow =SetTimer( ID_TIMER_SMALL_SNOW_FALL, 10, NULL); //��ʱ����10����
	}

	AddNotifyIcon();
	::ReleaseDC(NULL, hdc);

	timer_clock =  SetTimer( ID_TIMER_MAIN_WND_CLOCK, 500, NULL); //��ʱ����10����


	return 0;
}

void CDesktopSnowWnd::OnDestroy()
{
	CWnd::OnDestroy();

//////////////////////////////////////////////////////////////////////////
	if (m_pImageClock)
	{
		delete m_pImageClock;
	}
	if ( m_pImageHHour )
	{	
		delete m_pImageHHour;
	}

	if ( m_pImageHMinu )
	{	
		delete m_pImageHMinu;
	}

	if ( m_pImageHSec )
	{	
		delete m_pImageHSec;
	}
	//////////////////////////////////////////////////////////////////////////

	DeleteIcon();
	KillTimer( timer_clock); // ��ֹ��ʱ��
	KillTimer( timer_snow);
	::InvalidateRect(NULL, NULL, TRUE); // ˢ������
}

void CDesktopSnowWnd::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == timer_snow)
	{
		HDC hdc = ::GetDC( NULL ); //����������Ļ���豸�����Ļ���
	//	CDC* pDesktop = CDC::FromHandle(hdc);
		//pDesktop->BitBlt(500,600,bpDC.GetDeviceCaps(HORZRES),bpDC.GetDeviceCaps(VERTRES), &bpDC,0,0,SRCCOPY);

		if(iTimes > iLoopTimes)
		{
			iTimes = 0;
			iLoopTimes = 50 + (unsigned)rand()%50;
			if(snowDream.iAllVx != 0)
				snowDream.iAllVx = 0;
			else                  
				snowDream.iAllVx = (unsigned)rand()%3 - 1; //ѩ������ˮƽƮ���ٶ�(-1,0,1)
			snowDream.iAllVy = (unsigned)rand()%2 + 1; //ѩ�����崹ֱ�����ٶ�(1,2)
		}
		else
			iTimes++;
		drawSnow(hdc, &snowDream, theApp.cxScreen);
		::ReleaseDC(NULL, hdc);
	} 
	else if( nIDEvent == timer_clock )
	{
		UpdateClockDisplay();
	}
	CWnd::OnTimer(nIDEvent);
}


void CDesktopSnowWnd::AddNotifyIcon(void)
{
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; 
	nid.uID = IDR_MAINFRAME; 
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP|NIF_INFO;
	nid.dwInfoFlags = NIIF_USER| NIIF_NOSOUND;
	nid.uCallbackMessage = UM_ICONNOTIFY;
	nid.hIcon =  theApp.LoadIcon( IDR_MAINFRAME );

	CString str = "ʥ�����֣�";
	lstrcpyn(nid.szTip, (LPCSTR)str, 
		sizeof(nid.szTip) / sizeof(nid.szTip[0]));
	lstrcpyn(nid.szInfoTitle, (LPCSTR)str, 
		sizeof(nid.szInfoTitle) / sizeof(nid.szInfoTitle[0]));
	str ="ף��:\nԸ����ʵ��\n����ÿһ�죡";
	lstrcpyn(nid.szInfo, (LPCSTR)str, 
		sizeof(nid.szInfo) / sizeof(nid.szInfo[0]));
	Shell_NotifyIcon(NIM_ADD, &nid);
}


void CDesktopSnowWnd::DeleteIcon(void)
{
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


LRESULT CDesktopSnowWnd::OnIconNotify(WPARAM wParam, LPARAM lParam)
{
	switch ((UINT)lParam)
	{
		// ��굥������
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		{
			// װ��ͼ������˵�
			CMenu menu;
			menu.LoadMenu(IDR_MENU_NOTIFIY);
			CMenu *pPopup=menu.GetSubMenu(0);
			// ��굥��λ��
			CPoint point;
			GetCursorPos(&point);

			// ���������ڼ���
			SetForegroundWindow();
			// ��ʾͼ��˵�
			pPopup->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_VERTICAL, 
				point.x, point.y, this, NULL); 

			// ����һ��������Ϣ��ʹ�˵�������ȷ
			PostMessage(WM_USER, 0, 0);
			break;
		}
	}
	return 0;
}


void CDesktopSnowWnd::OnMenuExit()
{
	PostMessage( WM_CLOSE );
}

BOOL CDesktopSnowWnd::UpdateClockDisplay(int Transparent)
{
	HDC hdcTemp=GetDC()->m_hDC;
	m_hdcMemory=CreateCompatibleDC(hdcTemp);
	HBITMAP hBitMap=CreateCompatibleBitmap(hdcTemp,m_BakWidth,m_BakHeight);
	SelectObject(m_hdcMemory,hBitMap);
	if(Transparent<0||Transparent>100)
		Transparent=100;

	m_Blend.SourceConstantAlpha=int(Transparent*2.55);//1~255
	HDC hdcScreen=::GetDC (m_hWnd);
	RECT rct;
	GetWindowRect(&rct);
	POINT ptWinPos={rct.left,rct.top};
	Graphics graph(m_hdcMemory);

	Point points[] = { Point(0, 0), 
		Point(m_BakWidth, 0), 
		Point(0, m_BakHeight)
	};
	static bool bFly=false;
	bFly?graph.DrawImage(m_pImageClock, points, 3): graph.DrawImage(m_pImageClock1, points, 3); 
	bFly=!bFly;

	REAL OxyX=140;//m_BakWidth/2+8;
	REAL OxyY=90;//m_BakHeight/2+10;
	SYSTEMTIME SystemTime;   // address of system time structure
	GetLocalTime(&SystemTime);

	Matrix matrixH(1,0,0,1,OxyX,OxyY); // ����һ����λ��������ԭ���ڱ�������
	matrixH.Rotate( ( REAL)( SystemTime.wHour*30+SystemTime.wMinute/2.0-180 )); // ʱ����ת�ĽǶȶ�
	Point pointsH[] = { Point(0, 0),Point(m_HourWidth, 0),Point(0, m_HourHeight)};
	matrixH.Translate(( REAL)( -m_HourWidth/2 ) , ( REAL)(  -m_HourHeight/6 ) );
	matrixH.TransformPoints( pointsH, 3); // �øþ���ת��points
	graph.DrawImage (m_pImageHHour,pointsH, 3);

	Matrix matrixM(1,0,0,1,OxyX,OxyY); // ����һ����λ��������ԭ���ڱ�������
	matrixM.Rotate( ( REAL)(  SystemTime.wMinute*6-180 ) ); // ������ת�ĽǶȶ�
	Point pointsM[] = { Point(0, 0),Point(m_MinuWidth, 0),Point(0, m_MinuHeight)};
	matrixM.Translate( ( REAL)( -m_MinuWidth/2 ) , ( REAL)(  -m_MinuHeight/6 ) );
	matrixM.TransformPoints( pointsM, 3); // �øþ���ת��pointsM
	graph.DrawImage (m_pImageHMinu,pointsM, 3);

	Matrix matrix(1,0,0,1,OxyX,OxyY); // ����һ����λ��������ԭ���ڱ�������
	matrix.Rotate( ( REAL)(  SystemTime.wSecond*6-180 ) ); // ������ת�ĽǶȶ�
	Point pointsS[] = { Point(0, 0),Point( m_SecWidth,0),Point(0,m_SecHeight )};
	matrix.Translate( ( REAL)(  -m_SecWidth/2 ) , ( REAL)( -m_SecHeight/7 ) );
	matrix.TransformPoints( pointsS, 3); // �øþ���ת��pointsS
	graph.DrawImage (m_pImageHSec,pointsS, 3);
	//H
	graph.DrawImage(m_pImageNum,0, 0, 14*(SystemTime.wHour/10), 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��
	graph.DrawImage(m_pImageNum,20,0, 14*(SystemTime.wHour%10), 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��
	//:
	graph.DrawImage(m_pImageNum,20*2,0, 140, 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��
	//M
	graph.DrawImage(m_pImageNum,20*3, 0, 14*(SystemTime.wMinute/10), 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��
	graph.DrawImage(m_pImageNum,20*4,0, 14*(SystemTime.wMinute%10), 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��
	//:
	graph.DrawImage(m_pImageNum,20*5,0, 140, 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��
	//S
	graph.DrawImage(m_pImageNum,20*6, 0, 14*(SystemTime.wSecond/10), 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��
	graph.DrawImage(m_pImageNum,20*7,0, 14*(SystemTime.wSecond%10), 0,14,23,UnitPixel); //�ú�����m_pImageClock�м���ָ��rect�е�����draw��ָ��λ��

	SIZE sizeWindow={m_BakWidth,m_BakHeight};
	POINT ptSrc={0,0};
	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	if((dwExStyle&0x80000)!=0x80000)
		SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle^0x80000);

	BOOL bRet=FALSE;
	bRet= theApp.UpdateLayeredWindow( m_hWnd,hdcScreen,&ptWinPos,
		&sizeWindow,m_hdcMemory,&ptSrc,0,&m_Blend,2);
	graph.ReleaseHDC(m_hdcMemory);
	::ReleaseDC(m_hWnd,hdcScreen);
	hdcScreen=NULL;
	::ReleaseDC(m_hWnd,hdcTemp);
	hdcTemp=NULL;
	DeleteObject(hBitMap);
	DeleteDC(m_hdcMemory);
	m_hdcMemory=NULL;
	return bRet;
}


BOOL CDesktopSnowWnd::ImageFromIDResource(UINT nID, LPCTSTR sTR,Image * &pImg)
{

	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),sTR); // type
	if (!hRsrc)
		return FALSE;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;

	// Allocate global memory on which to create stream
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
	memcpy(pmem,lpRsrc,len);
	IStream* pstm;
	HRESULT hr = CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);
	if (FAILED( hr ))
	{
		return FALSE;
	}

	// load from stream
	pImg=Gdiplus::Image::FromStream( pstm);
	if ( !pImg )
	{
		return FALSE;
	}
	// free/release stuff
	GlobalUnlock(m_hMem);
	pstm->Release();
	return FreeResource(lpRsrc);
}

void CDesktopSnowWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	//��ֹ��ʾ�ƶ����δ����
	::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,TRUE,NULL,0);
	//�Ǳ������ƶ���������
	SendMessage(WM_SYSCOMMAND,0xF012,0);   
	CWnd::OnLButtonDown(nFlags, point);
}

BOOL CDesktopSnowWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}


void CDesktopSnowWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnRButtonDown(nFlags, point);

	CMenu menu;
	menu.LoadMenu(IDR_MENU_NOTIFIY);
	CMenu *pPopup=menu.GetSubMenu(0);
	
	CPoint pt= point ;
	ClientToScreen( &pt );

	// ��ʾͼ��˵�
	pPopup->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_VERTICAL, 
		pt.x, pt.y, this, NULL); 
}
