// PicDLg.cpp : 实现文件
//

#include "stdafx.h"
#include "DesktopSnow.h"
#include "PicDLg.h"



// CPicDLg 对话框

IMPLEMENT_DYNAMIC(CPicDLg, CDialog)

CPicDLg::CPicDLg(bool isBig,CWnd* pParent /*=NULL*/)
	: CDialog(CPicDLg::IDD, pParent)
{
	isBigSnow = isBig ;
	
	state = 0;
}

CPicDLg::CPicDLg(CWnd* pParent /*=NULL*/)
	: CDialog(CPicDLg::IDD, pParent)
{
	state = 0;
}
CPicDLg::~CPicDLg()
{

}


void CPicDLg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPicDLg, CDialog)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPicDLg 消息处理程序

BOOL CPicDLg::UpdateDisplay(  int Transparent )
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
//	static int m_state=0;
		
		if ( isBigSnow )
		{
				graph.DrawImage( theApp.m_pImageBigSnow[state%BIG_SNOW_KINDS], points, 3); 
				//graph.DrawImage( theApp.m_pImageSmallSnow[state%SMALL_SNOW_KINDS], points, 3); 
				TRACE("aaaaaaa\n");
		}
		else
		{
			//graph.DrawImage( theApp.m_pImageBigSnow[state%BIG_SNOW_KINDS], points, 3); 
			graph.DrawImage( theApp.m_pImageSmallSnow[state%SMALL_SNOW_KINDS], points, 3); 
			TRACE("dddddd\n");

		}


	SIZE sizeWindow={m_BakWidth,m_BakHeight};
	POINT ptSrc={0,0};
	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	if((dwExStyle&0x80000)!=0x80000)
		SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle^0x80000);
	
	BOOL bRet=FALSE;
	bRet= theApp.UpdateLayeredWindow( m_hWnd,hdcScreen,&ptWinPos,&sizeWindow,m_hdcMemory,&ptSrc,0,&m_Blend,2);
	
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

/*
BOOL CPicDLg::ImageFromIDResource(UINT nID, LPCTSTR sTR,Image * &pImg)
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

*/
int CPicDLg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Initialize GDI+.
	m_Blend.BlendOp=0; //theonlyBlendOpdefinedinWindows2000
	m_Blend.BlendFlags=0; //nothingelseisspecial...
	m_Blend.AlphaFormat=1; //...
	m_Blend.SourceConstantAlpha=255;//AC_SRC_ALPHA
// 
// 
// 	ImageFromIDResource(IDR_PNG_BIG_SNOW1,"PNG",m_pImageSnow1);
// 	ImageFromIDResource(IDR_PNG_BIG_SNOW2,"PNG",m_pImageSnow2);
	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle|WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED );
if ( isBigSnow)
{
	m_BakWidth  =theApp.m_pImageBigSnow[0]->GetWidth();
	m_BakHeight =theApp.m_pImageBigSnow[0]->GetHeight();
} 
else
{
	m_BakWidth  =theApp.m_pImageSmallSnow[0]->GetWidth();
	m_BakHeight =theApp.m_pImageSmallSnow[0]->GetHeight();
}

	::SetWindowPos( m_hWnd, HWND_TOPMOST,posX , posY ,m_BakWidth,m_BakHeight,SWP_NOSIZE|SWP_NOMOVE); 

	return 0;
}

void CPicDLg::OnDestroy()
{
	CDialog::OnDestroy();
	if ( timer)
	{
		KillTimer( timer );
		timer = 0;
	}
	if ( timer_change )
	{
		KillTimer( timer_change);
		timer_change = 0;
	}
	if ( timer_next_state )
	{
		KillTimer( timer_next_state);
		timer_next_state = 0;
	}
	


}

BOOL CPicDLg::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateDisplay( 100 );
	InitState( true );
	::SetWindowPos( m_hWnd, HWND_TOPMOST,posX , posY ,m_BakWidth,m_BakHeight,SWP_NOSIZE); 
	//雪花下落定时器
	timer =SetTimer(ID_TIMER_BIG_SNOW_FALL,40,NULL);
	//雪花开始变化定时器
	timer_change = SetTimer( ID_TIMER_SNOW_CHANGE, (unsigned)rand()%3000 ,NULL);
	return TRUE; 
}

void CPicDLg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( nIDEvent == timer)
	{
		Piao();
	} 
	else if( nIDEvent == timer_change )
	{
		KillTimer( timer_change );
		timer_change = 0 ;
		timer_next_state = SetTimer( ID_TIMER_SNOW_NEXT_STATE, 300,NULL) ;	
	}
	else if( nIDEvent == timer_next_state)
	{
		NextState();
	}

	CDialog::OnTimer(nIDEvent);
}

void CPicDLg::NextState( )
{
	
	if ( state<endState )
	{
		++state;
	}
	else
	{
		KillTimer( timer_next_state )	;
		timer_next_state = 0;
		timer_change = SetTimer( ID_TIMER_SNOW_CHANGE, 500+(unsigned)rand()%3000 ,NULL);
		state =  rand()%3;
		if ( isBigSnow )
		{
			endState = state+BIG_SNOW_KINDS;
		} 
		else
		{
			endState = state+SMALL_SNOW_KINDS;
		}

	}
	UpdateDisplay( 100 );
}

void CPicDLg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	posX = x;
	posY = y;
}

void CPicDLg::InitState( bool firstInit)
{
   //srand ((int) GetCurrentTime ()) ; //初始化随机数发生器
	posX =  (unsigned)rand()%theApp.cxScreen;
	if ( firstInit )
	{
		posY = - rand()%theApp.cyScreen;
	}
	else
	{
		posY = -50;
	}
	int kind = isBigSnow ? BIG_SNOW_KINDS :SMALL_SNOW_KINDS ;
	state =  rand()%kind;
	endState = state+kind;
	speedX = rand()%7-3;
	speedY = rand()%3+2;
	MoveWindow( posX , posY  ,sizeX ,sizeY);
}

void CPicDLg::Piao(  )
{
		MoveWindow( posX+speedX ,posY+speedY  , sizeX,sizeY );
		
		if ( posX < -sizeX || posX >theApp.cxScreen || posY> theApp.cyScreen )
		{
			InitState();
		}
}

void CPicDLg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	sizeX = cx;
	sizeY = cy;
}

BOOL CPicDLg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	//cs.style = ;
	return CDialog::PreCreateWindow(cs);
}

BOOL CPicDLg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialog::OnEraseBkgnd(pDC);
	return TRUE;
}
