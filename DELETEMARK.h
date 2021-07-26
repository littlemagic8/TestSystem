#pragma once


// DELETEMARK 对话框

class DELETEMARK : public CDialogEx
{
	DECLARE_DYNAMIC(DELETEMARK)

public:
	DELETEMARK(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DELETEMARK();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString stuDelete2;
};
