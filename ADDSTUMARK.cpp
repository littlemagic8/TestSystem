// ADDSTUMARK.cpp: 实现文件
//testcommit

#include "stdafx.h"
#include "examSystem.h"
#include "ADDSTUMARK.h"
#include "afxdialogex.h"
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"


// ADDSTUMARK 对话框

IMPLEMENT_DYNAMIC(ADDSTUMARK, CDialogEx)

ADDSTUMARK::ADDSTUMARK(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, stuId(_T(""))
	, objectOriented(_T(""))
	, english(_T(""))
	, matrixAnalysis(_T(""))
{

}

ADDSTUMARK::~ADDSTUMARK()
{
}

void ADDSTUMARK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, stuId);
	DDX_Text(pDX, IDC_EDIT1, objectOriented);
	DDX_Text(pDX, IDC_EDIT3, english);
	DDX_Text(pDX, IDC_EDIT4, matrixAnalysis);
}


BEGIN_MESSAGE_MAP(ADDSTUMARK, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ADDSTUMARK::OnBnClickedButton1)
END_MESSAGE_MAP()


// ADDSTUMARK 消息处理程序


void ADDSTUMARK::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(true);
	MYSQL m_sqlCon;
	MYSQL_RES *res;
	MYSQL_ROW row;
	CString sql;
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root", "", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else
	{
		UpdateData(true);
		char* stuId1 = (char*)stuId.GetBuffer();
		char* objectOriented1 = (char*)objectOriented.GetBuffer();
		char* english1 = (char*)english.GetBuffer();
		char* matrixAnalysis1 = (char*)matrixAnalysis.GetBuffer();
		mysql_query(&m_sqlCon, "SET NAMES GB2312");
		//char insert[1000];
		sql.Format("INSERT INTO t_mark(studentId,objectOriented,english,matrixAnalysis,term)VALUES(\'%s\',\'%s\',\'%s\',\'%s\',CURRENT_DATE)", stuId1, objectOriented1,
			english1, matrixAnalysis1);
		int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)sql);
		if (ress == 0)
		{
			AfxMessageBox(_T("插入数据成功!"));
			CDialog::OnOK();
			ADDSTUMARK inforAdd;
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











