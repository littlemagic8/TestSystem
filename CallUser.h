#pragma once
#include "CManagerDlg.h"
#include "CEditStuInfo.h"
// CallUser 对话框

class CallUser : public CDialogEx
{
	DECLARE_DYNAMIC(CallUser)
	CString strmanaIDListS;
	int is_admin = 0;
public:
	CallUser(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CallUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_allUser };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl allUserList;
	void ListallShow();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
