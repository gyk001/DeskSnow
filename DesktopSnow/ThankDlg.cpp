// ThankDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DesktopSnow.h"
#include "ThankDlg.h"


// CThankDlg 对话框

IMPLEMENT_DYNAMIC(CThankDlg, CDialog)

CThankDlg::CThankDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThankDlg::IDD, pParent)
{

}

CThankDlg::~CThankDlg()
{
}

void CThankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CThankDlg, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CThankDlg 消息处理程序
void CThankDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnOK();
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CThankDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	OnOK();
	CDialog::OnRButtonDown(nFlags, point);
}