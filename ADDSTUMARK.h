#pragma once
//test

// ADDSTUMARK 对话框 testpush

class ADDSTUMARK : public CDialogEx
{
	DECLARE_DYNAMIC(ADDSTUMARK)

public:
	ADDSTUMARK(CWnd* pParent = nullptr)?;   // 标准构造函数
	virtual ~ADDSTUMARK();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString stuId;
	CString objectOriented;
	CString english;
	CString matrixAnalysis;
	afx_msg void OnBnClickedButton1();
};
