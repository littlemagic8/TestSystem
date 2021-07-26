#pragma once
#include "examSystemDlg.h"
#include "CallUser.h"
// CManagerDlg 对话框

class CManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManagerDlg)

public:
	CManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CManagerDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ManagerDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};