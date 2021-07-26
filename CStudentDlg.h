#pragma once
#include "examSystemDlg.h"
#include "COnlineTest.h"
#include "CEditUserInfo.h"
#include "CEditStuInfo.h"
// CStudentDlg 对话框

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)
public:
	CString curUserName;
	CString curUserId;
	CString userrole;
public:
	CStudentDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CStudentDlg};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedExitstu();
	
	virtual BOOL OnInitDialog();
	CEdit curUserEdit;
	afx_msg void OnBnClickedStutest();
	afx_msg void OnBnClickedSturesult();
	afx_msg void OnBnClickeduserdetailbtn();
};
