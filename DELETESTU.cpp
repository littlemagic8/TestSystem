// DELETESTU.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "DELETESTU.h"
#include "afxdialogex.h"
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"

	//初始化数据库对象

// DELETESTU 对话框

IMPLEMENT_DYNAMIC(DELETESTU, CDialogEx)

DELETESTU::DELETESTU(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, stuDelete(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

DELETESTU::~DELETESTU()
{
}

void DELETESTU::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, stuDelete);
}


BEGIN_MESSAGE_MAP(DELETESTU, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DELETESTU::OnBnClickedButton1)
END_MESSAGE_MAP()


// DELETESTU 消息处理程序


void DELETESTU::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL m_sqlCon;
	MYSQL_RES *res;
	MYSQL_ROW  row;
	CString sql;
	UpdateData(true);
	if (this->stuDelete == "")
	{
		AfxMessageBox(_T("不能为空!"));
	}else
	{
		mysql_init(&m_sqlCon);
		if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else {
			//AfxMessageBox(_T("数据库连接成功!"));
			mysql_query(&m_sqlCon, "SET NAMES GB2312");
			sql.Format("DElETE FROM t_student WHERE studentNumber=\'%s\'",this->stuDelete);
			int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)sql);
			if (ress == 0)
			{//成功
				AfxMessageBox(_T("删除成功!"));
				res = mysql_store_result(&m_sqlCon);
				mysql_close(&m_sqlCon);//关闭Mysql连接
			}
		}
	}

}
