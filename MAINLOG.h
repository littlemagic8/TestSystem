#pragma once


// MAINLOG 对话框

class MAINLOG : public CDialogEx
{
	DECLARE_DYNAMIC(MAINLOG)

public:
	MAINLOG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MAINLOG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ADD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
//	CListCtrl mList;
	CListCtrl mList;
	afx_msg void OnBnClickedButton1();
//	afx_msg void ListShow(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CString value;
	int ListShow1();
	void ListDataShow();
	CButton pageId;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CString stuNum;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnEnChangeEdit10();
	CString size;
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	CString currentPage;
	afx_msg void OnBnClickedButton14();
};
