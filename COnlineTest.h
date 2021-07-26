#pragma once
#include"CStudentDlg.h"

// COnlineTest 对话框

class COnlineTest : public CDialogEx
{
	DECLARE_DYNAMIC(COnlineTest)

public:
	COnlineTest(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COnlineTest();
	CString studentOnlineId;
	CString studentOnlineNamedlg;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OnlineTest };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClicked2();
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTestlist(NMHDR* pNMHDR, LRESULT* pResult);
	CTreeCtrl m_TestTree;
	CEdit m_testNum;
	CEdit m_testInfo;
	CEdit m_answerinfo;
	CEdit m_detailinfo;
	afx_msg void OnTvnSelchangedTesttree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
};
