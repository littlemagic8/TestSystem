#pragma once


// INFORADD 对话框

class INFORADD : public CDialogEx
{
	DECLARE_DYNAMIC(INFORADD)

public:
	INFORADD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~INFORADD();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString studentNumber;
	CString studentName;
	CString studentSex;
//	CString studentAge;
	CString studClass;
	CString telephone;
	CString stuQQ;
	CString college;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
//	int studentAge;
	CString studentAge;
	CButton queding;
	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	void showButton();
};
