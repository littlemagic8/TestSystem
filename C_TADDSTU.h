#pragma once
#include"mysql.h"
#include "ManagerStu.h"
// C_TADDSTU 对话框

class C_TADDSTU : public CDialogEx
{
	DECLARE_DYNAMIC(C_TADDSTU)

public:
	C_TADDSTU(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_TADDSTU();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddstuInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString studentId;
	CString studentNamedlg;
	CEdit stuNameEdit;
	// 真实姓名
	CEdit stuNameREdit;
	CEdit stuBrithEdit;
	CButton Sex_Men;
	CButton Sex_women;
	CComboBox stuProf;
	CEdit stuEmailEdit;
	CEdit stuSchoolEdit;
	int EditFlag = 0;
	int isStu = 0;
	afx_msg void OnBnClickedstusavebtn();
	CStatic brithOrProf;

	CStatic brithOrprof15;
	CStatic brithOrprof16;
	CStatic brithOrprof17;
	afx_msg void OnBnClicked2();
};
