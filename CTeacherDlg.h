#pragma once
#include "CInputSingleTest.h"

#include "examSystem.h"
#include "afxdialogex.h"
#include "examSystemDlg.h"
// CTeacherDlg 对话框

class CTeacherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacherDlg)
public:
	CString curUserName;
	CString curUserId;
public:
	CTeacherDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeacherDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = TeacherDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIntest();
	virtual BOOL OnInitDialog();
	CEdit curUserEdit;
	afx_msg void OnBnClickedTeacexit();
	afx_msg void OnBnClickedteachdetailbtn();
	afx_msg void OnBnClickedmanagerstu();
};
