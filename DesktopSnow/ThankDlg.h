#pragma once


// CThankDlg 对话框

class CThankDlg : public CDialog
{
	DECLARE_DYNAMIC(CThankDlg)

public:
	CThankDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThankDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_THANKS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
