#pragma once


// STUMARK 对话框

class STUMARK : public CDialogEx
{
	DECLARE_DYNAMIC(STUMARK)

public:
	STUMARK(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~STUMARK();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void listShow();
	CListCtrl mList;
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	CString size2;
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	CString stuNum2;
	CString currentPage2;
	afx_msg void OnBnClickedButton6();
	CString term;
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
};
