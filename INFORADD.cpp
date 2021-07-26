// INFORADD.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "INFORADD.h"
#include "afxdialogex.h"
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"
#include "MAINLOG.h"

// INFORADD 对话框

IMPLEMENT_DYNAMIC(INFORADD, CDialogEx)

INFORADD::INFORADD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, studentNumber(_T(""))
	, studentName(_T(""))
	, studentSex(_T(""))
	, studentAge(_T(""))
	, studClass(_T(""))
	, telephone(_T(""))
	, stuQQ(_T(""))
	, college(_T(""))
	//, studentAge(0)
	//, studentAge(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

INFORADD::~INFORADD()
{
}

void INFORADD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, studentNumber);
	DDX_Text(pDX, IDC_EDIT6, studentName);
	DDX_Text(pDX, IDC_EDIT2, studentSex);
	//  DDX_Text(pDX, IDC_EDIT7, studentAge);
	DDX_Text(pDX, IDC_EDIT3, studClass);
	DDX_Text(pDX, IDC_EDIT8, telephone);
	DDX_Text(pDX, IDC_EDIT4, stuQQ);
	DDX_Text(pDX, IDC_EDIT9, college);
	//  DDX_Text(pDX, IDC_EDIT7, studentAge);
	DDX_Text(pDX, IDC_EDIT7, studentAge);
	DDX_Control(pDX, IDC_BUTTON1, queding);
}


BEGIN_MESSAGE_MAP(INFORADD, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &INFORADD::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &INFORADD::OnEnChangeEdit1)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// INFORADD 消息处理程序


void INFORADD::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(true);
	MYSQL m_sqlCon;
	MYSQL_RES *res;
	MYSQL_ROW row;
	CString sql;
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon,"localhost","root","","exam",3306,NULL,0)) 
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}else
	{
		UpdateData(true);
		char* studentNumber1 = (char*)studentNumber.GetBuffer();
		char* studentName1 = (char*)studentName.GetBuffer();
		char* studentSex1 = (char*)studentSex.GetBuffer();
		char* studentAge1 = (char*)studentAge.GetBuffer();
		char* studClass1 = (char*)studClass.GetBuffer();
		char* telephone1 = (char*)telephone.GetBuffer();
		char* stuQQ1 = (char*)stuQQ.GetBuffer();
		char* college1 = (char*)college.GetBuffer();
		mysql_query(&m_sqlCon,"SET NAMES GB2312");
		//char insert[1000];
		sql.Format("INSERT INTO t_student(studentNumber,name,sex,age,class,phone,qq,college)VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",studentNumber1,studentName1,
			studentSex1,studentAge1,studClass1,telephone1,stuQQ1,college1);
		int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)sql);
		if (ress == 0)
		{
			AfxMessageBox(_T("插入数据成功!"));
			CDialog::OnOK();
			INFORADD inforAdd;
			inforAdd.DoModal();
			OnInitDialog();
			UpdateData(false);
			mysql_close(&m_sqlCon);//关闭Mysql连接
		}
		else {
			AfxMessageBox(_T("插入数据失败!"));
		}
	}
	
	
	
}


void INFORADD::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


HRESULT INFORADD::accDoDefaultAction(VARIANT varChild)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::accDoDefaultAction(varChild);
}


void INFORADD::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}


void INFORADD::showButton()
{
	// TODO: 在此处添加实现代码.
	CButton *button1 = (CButton*)GetDlgItem(IDC_BUTTON1);
	button1->EnableWindow(FALSE); //隐藏该控件

}
