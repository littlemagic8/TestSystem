#pragma once
#include"examSystemDlg.h"

// CRegisterUser 对话框

class CRegisterUser : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterUser)

public:
	CRegisterUser(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegisterUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Register };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedReturnlogin();
	CEdit userPwd;
	afx_msg void OnBnClicked1();
	CEdit m_ruser;
	CEdit m_rruser;
	CComboBox m_userDep;
	CEdit m_userEmail;
	CButton m_Mr;
	CButton mWr;
	CEdit m_brithR;
	CEdit m_Rsch;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit4();
};
