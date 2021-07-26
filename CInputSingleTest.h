#pragma once
#include "mysql.h"

#include "examSystem.h"

#include "afxdialogex.h"
#include "CTeacherDlg.h"
// CInputSingleTest 对话框

class CInputSingleTest : public CDialogEx
{
	DECLARE_DYNAMIC(CInputSingleTest)
public:
	CString curUserName;
	CString curUserId;
	CString strinputTest = "";
public:
	CInputSingleTest(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInputSingleTest();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_InputSingleTest };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedIncourse(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	CTreeCtrl courseName;
	CEdit courseNameInTest;
	CListCtrl m_testList;
	afx_msg void OnNMClickTestedlist(NMHDR* pNMHDR, LRESULT* pResult);
	CComboBox courseNameI;
	CComboBox testTypeI;
	CEdit TestValueI;
	CComboBox QDiffI;
	CEdit UploadI;
	CEdit QCententI;
	CEdit QAnswerI;
	CEdit QDetailI;
	afx_msg void OnBnClickedCheck2();
	CButton checkI1;
	afx_msg void OnBnClickedTestsinglefind();
	CButton comboxChexk3;
	CButton comboxcheck4;
	CButton comboxcheck5;
	CButton comboxcheck7;
	CButton comboxcheck8;
	CButton comboxcheck9;
	CString KPContent;
	CString courseID_combox = "";
	CString ChapterID_combox = "";
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnCbnSelchangecoursenamei();
	afx_msg void OnTvnGetInfoTipIncourse(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangetesttypei();
	afx_msg void OnLvnItemchangedTestedlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedNexttest();
	afx_msg void OnBnClickeduploadsingletest();
	afx_msg void OnBnClickedexitinputtest();
	afx_msg void OnBnClickedSaveedittestsingle();
	afx_msg void OnBnClickedTestsingledel();
	afx_msg void OnBnClickedViewothertest();
};
