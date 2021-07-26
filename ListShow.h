#pragma once


// ListShow 对话框

class ListShow : public CDialogEx
{
	DECLARE_DYNAMIC(ListShow)

public:
	ListShow(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ListShow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ADD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
