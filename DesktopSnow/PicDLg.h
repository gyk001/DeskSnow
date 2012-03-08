#pragma once


// CPicDLg 对话框

class CPicDLg : public CDialog
{
	DECLARE_DYNAMIC(CPicDLg)

public:
	CPicDLg(CWnd* pParent = NULL);   // 标准构造函数
	CPicDLg(bool isBig,CWnd* pParent =NULL);
	~CPicDLg();
// 对话框数据
	enum { IDD = IDD_PICDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//BOOL ImageFromIDResource(UINT nID,LPCTSTR sTR,Image * &pImg);
	BOOL UpdateDisplay( int Transparent=255 );

	bool isBigSnow;

	BLENDFUNCTION m_Blend;
	HDC m_hdcMemory;
// 	Image *m_pImageSnow1;
// 	Image *m_pImageSnow2;
	int m_BakWidth , m_BakHeight ;
	int speedX,speedY;
	int posX,posY;
	int sizeX ,sizeY;
	UINT_PTR timer;
	UINT_PTR timer_change;
	UINT_PTR timer_next_state;
	int state ;
	int endState;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnDestroy();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnMove(int x, int y);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void InitState( bool firstInit = false );
	void NextState( );
	void Piao(  );

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
