// CStudentDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CStudentDlg.h"
#include "afxdialogex.h"
#include "MAINLOG.h"
#include "STUMARK.h"
#include "CstuMarkManager.h"

// CStudentDlg 对话框

IMPLEMENT_DYNAMIC(CStudentDlg, CDialogEx)

CStudentDlg::CStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CStudentDlg, pParent)
{

}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_CurUser, curUserName);
	DDX_Control(pDX, IDC_CurUser, curUserEdit);
}


BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	//ON_BN_CLICKED(IDCANCEL, &CStudentDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ExitStu, &CStudentDlg::OnBnClickedExitstu)
	ON_BN_CLICKED(IDC_StuTest, &CStudentDlg::OnBnClickedStutest)
	ON_BN_CLICKED(IDC_StuResult, &CStudentDlg::OnBnClickedSturesult)
	ON_BN_CLICKED(IDC_userDetailBtn, &CStudentDlg::OnBnClickeduserdetailbtn)
END_MESSAGE_MAP()


// CStudentDlg 消息处理程序


//void CStudentDlg::OnBnClickedCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	//CDialogEx::OnCancel();
//	//MAINLOG  mianlog;
//	//mianlog.DoModal();
//}


void CStudentDlg::OnBnClickedExitstu()
{
	CDialog::OnOK();
	CexamSystemDlg  loginIn;
	loginIn.DoModal();
	//exit(0);
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CStudentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//curUserEdit.SetWindowRgn(HRGN(this->curUserId));
	curUserEdit.SetWindowTextA(_T(this->curUserName));
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CStudentDlg::OnBnClickedStutest()
{
	CDialog::OnOK();
	COnlineTest  onlineTest;
	onlineTest.studentOnlineId = (_T(this->curUserId));
	onlineTest.studentOnlineNamedlg = (_T(this->curUserName));
	onlineTest.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CStudentDlg::OnBnClickedSturesult()
{
	CDialog::OnOK();
	CstuMarkManager stuMark;
	stuMark.curUserId = this->curUserId;
	stuMark.curUserName = this->curUserName;
	stuMark.userrole = this->userrole;
	stuMark.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CStudentDlg::OnBnClickeduserdetailbtn()
{
	CDialog::OnOK();
	CEditStuInfo  userInfo;
	userInfo.studentId = (_T(this->curUserId));
	userInfo.studentNamedlg = (_T(this->curUserName));
	userInfo.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
