#pragma once


// CThankDlg �Ի���

class CThankDlg : public CDialog
{
	DECLARE_DYNAMIC(CThankDlg)

public:
	CThankDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThankDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_THANKS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
