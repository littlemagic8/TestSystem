
// examSystemDlg.h: 头文件
//

#pragma once
#include"CStudentDlg.h"
#include"CManagerDlg.h"
#include"CTeacherDlg.h"
#include"CRegisterUser.h"

static CString str[3] = { "管理员","教师","学生" };
static CString strIdentify;

// CexamSystemDlg 对话框
class CexamSystemDlg : public CDialogEx
{
public:
	CBrush m_Brush;
	CFont m_font;
// 构造
public:
	CexamSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_examSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CString userPassword;
//	CString userName;
	afx_msg void OnBnClickedButton1();
	CString userName;
	CString userPassword;
	//CComboBox identify;
	afx_msg void OnCbnSelchangeCombo1();
	//char identifyRole();
	CString identifyRole();
	afx_msg void OnBnClickedButton2();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRegbtn();
};
