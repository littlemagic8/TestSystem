// DELETEMARK.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "DELETEMARK.h"
#include "afxdialogex.h"
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"


// DELETEMARK 对话框

IMPLEMENT_DYNAMIC(DELETEMARK, CDialogEx)

DELETEMARK::DELETEMARK(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, stuDelete2(_T(""))
{

}

DELETEMARK::~DELETEMARK()
{
}

void DELETEMARK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, stuDelete2);
}


BEGIN_MESSAGE_MAP(DELETEMARK, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DELETEMARK::OnBnClickedButton1)
END_MESSAGE_MAP()


// DELETEMARK 消息处理程序


void DELETEMARK::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL m_sqlCon;
	MYSQL_RES *res;
	MYSQL_ROW  row;
	CString sql;
	UpdateData(true);
	if (this->stuDelete2 == "")
	{
		AfxMessageBox(_T("不能为空!"));
	}
	else
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
			sql.Format("DElETE FROM t_mark WHERE studentId=\'%s\'", this->stuDelete2);
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
