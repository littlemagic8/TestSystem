#pragma once
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"
#include "CTeacherDlg.h"
#include <list>
#include "DELETESTU.h"
#include "CEditStuInfo.h"
#include <string> 
#include"C_TADDSTU.h"
#include "CstuMarkManager.h"
#include<iostream>
#include "INFORADD.h"
// ManagerStu 对话框
class ManagerStu : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerStu)
public:
	CString curUserName;
	CString curUserId;
	CString strstuIDListS = "";    // 选择语言的名称字符串   

public:
	ManagerStu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ManagerStu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ManagerStu };
#endif

protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//	CListCtrl mListM;
	CListCtrl mListM;
	//afx_msg void OnBnClickedButton1();
	//	afx_msg void ListShow(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnBnClickedButton2();
	//afx_msg void OnBnClickedButton3();
	//afx_msg void OnBnClickedButton4();
	CString valueM;
	int ListShow1();
	void ListDataShow();
	CButton pageIdM;
	
	//afx_msg void OnBnClickedButton7();
	CString stuNumM;
//	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	//afx_msg void OnEnChangeEdit10();
	CString sizeM;
	afx_msg void OnBnClickedButton10();
//	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	CString currentPageM;
	//afx_msg void OnBnClickedButton14();
	//CButton pageIdM;
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnLvnItemchangedManagerstulist2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton7();
	CEdit StuName;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton6();
};
