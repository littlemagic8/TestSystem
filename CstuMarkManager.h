#pragma once
#include"CTeacherDlg.h"

// CstuMarkManager 对话框

class CstuMarkManager : public CDialogEx
{
	DECLARE_DYNAMIC(CstuMarkManager)
	CString curUserName;
	CString curUserId;
	CString userrole = "管理员";
public:
	CstuMarkManager(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CstuMarkManager();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ManagerStuMark};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int is_admin = 1;
	virtual BOOL OnInitDialog();
	void listShow();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	CString size2;
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton5();
	CString stuNum2;
	CString currentPage2;
	afx_msg void OnBnClickedButton6();
	CString term;
	afx_msg void OnBnClickedButton9();
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl mList;
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton7();
	CEdit queryMark;
	afx_msg void OnEnChangeEdit3();
	CEdit viewNum;
	afx_msg void OnEnChangeEdit10();
	CEdit curpage;
};
