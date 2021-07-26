// CTeacherDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CTeacherDlg.h"
#include "ManagerStu.h"
// CTeacherDlg 对话框

IMPLEMENT_DYNAMIC(CTeacherDlg, CDialogEx)

CTeacherDlg::CTeacherDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(TeacherDlg, pParent)
{

}

CTeacherDlg::~CTeacherDlg()
{
}

void CTeacherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CurUser, curUserEdit);
}


BEGIN_MESSAGE_MAP(CTeacherDlg, CDialogEx)
	ON_BN_CLICKED(IDC_InTest, &CTeacherDlg::OnBnClickedIntest)
	ON_BN_CLICKED(IDC_TeacExit, &CTeacherDlg::OnBnClickedTeacexit)
	ON_BN_CLICKED(IDC_teachDetailBtn, &CTeacherDlg::OnBnClickedteachdetailbtn)
	ON_BN_CLICKED(IDC_managerStu, &CTeacherDlg::OnBnClickedmanagerstu)
END_MESSAGE_MAP()


// CTeacherDlg 消息处理程序


void CTeacherDlg::OnBnClickedIntest()
{
	CDialog::OnOK();
	// TODO: 在此添加控件通知处理程序代码
	CInputSingleTest inputsingleTest;
	inputsingleTest.curUserId = (_T(this->curUserId));
	inputsingleTest.curUserName = (_T(this->curUserName));
	inputsingleTest.DoModal();
}


BOOL CTeacherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	curUserEdit.SetWindowTextA(_T(this->curUserName));
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTeacherDlg::OnBnClickedTeacexit()
{
	CDialog::OnOK();
	CexamSystemDlg  loginIn;
	loginIn.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CTeacherDlg::OnBnClickedteachdetailbtn()
{
	CDialog::OnOK();
	CEditStuInfo   techInfo;
	techInfo.studentId = (_T(this->curUserId));
	techInfo.studentNamedlg = (_T(this->curUserName));
	techInfo.DoModal();
}


void CTeacherDlg::OnBnClickedmanagerstu()
{
	CDialog::OnOK();
	ManagerStu managerStu;
	managerStu.curUserId = (_T(this->curUserId));
	managerStu.curUserName = (_T(this->curUserName));
	managerStu.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
