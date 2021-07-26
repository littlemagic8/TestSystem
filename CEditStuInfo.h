#pragma once
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"
#include <list>
#include "examSystemDlg.h"
#include "CManagerDlg.h"
// CEditStuInfo 对话框

class CEditStuInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CEditStuInfo)

public:
	CEditStuInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditStuInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EditstuInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString studentId;
	int is_admin = 1;
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
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClickedstusavebtn();
	CStatic brithOrProf;
	
	CStatic brithOrprof15;
	CStatic brithOrprof16;
	CStatic brithOrprof17;
};
