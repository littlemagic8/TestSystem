#pragma once


// CEditTeacInfo 对话框

class CEditTeacInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CEditTeacInfo)

public:
	CEditTeacInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditTeacInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EditstuInfo1 };
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
};
