// CManagerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CManagerDlg.h"
#include "afxdialogex.h"
#include "CstuMarkManager.h"
#include "CTestManager.h"

// CManagerDlg 对话框

IMPLEMENT_DYNAMIC(CManagerDlg, CDialogEx)

CManagerDlg::CManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ManagerDlg, pParent)
{

}

CManagerDlg::~CManagerDlg()
{
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(2, &CManagerDlg::OnBnClicked2)
	ON_BN_CLICKED(IDC_BUTTON2, &CManagerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CManagerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CManagerDlg 消息处理程序

//查询所有用户
void CManagerDlg::OnBnClickedButton1()
{
	CDialog::OnOK();
	/*MAINLOG  onlineTest;
	onlineTest.DoModal();*/
	CallUser  manlog;
	manlog.DoModal();
}


void CManagerDlg::OnBnClicked2()
{
	CDialog::OnOK();
    CexamSystemDlg stuMark;
	stuMark.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

//成绩管理
void CManagerDlg::OnBnClickedButton2()
{
	CDialog::OnOK();
	CstuMarkManager manaManager;
	manaManager.is_admin = 0;
	manaManager.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

//试题管理
void CManagerDlg::OnBnClickedButton3()
{
	CDialog::OnOK();
	CTestManager testManager;
	testManager.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
