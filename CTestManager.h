#pragma once


// CTestManager 对话框

class CTestManager : public CDialogEx
{
	DECLARE_DYNAMIC(CTestManager)

public:
	CTestManager(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTestManager();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TestManager};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl testList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
