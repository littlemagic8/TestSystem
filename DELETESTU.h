#pragma once


// DELETESTU 对话框

class DELETESTU : public CDialogEx
{
	DECLARE_DYNAMIC(DELETESTU)

public:
	DELETESTU(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DELETESTU();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString stuDelete;
	afx_msg void OnBnClickedButton1();
};
