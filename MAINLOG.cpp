// MAINLOG.cpp: 实现文件
//

#include "stdafx.h"

#include "examSystem.h"
#include "MAINLOG.h"
#include "afxdialogex.h"
#include "INFORADD.h"
#include "DELETESTU.h"
#include "examSystemDlg.h"
#include <string> 
#include<iostream>
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"
#include <list>
#include "STUMARK.h"
using namespace std;
CString h;
CString iden;
class studentClass {
public:
	CString studentId;
	CString studentNumber;
	CString name;
	CString sex;
	CString age;
	CString stuClass;
	CString phone;
	CString qq;
	CString college;
	CString getStudentId() {
		return studentId;
	}

	 void setStudentId(CString studentId) {
		this->studentId = studentId;
	}

	 CString getStudentNumber() {
		return studentNumber;
	}

	 void setStudentNumber(CString studentNumber) {
		this->studentNumber = studentNumber;
	}
	 CString getName() {
		 return name;
	 }
	 void setName(CString name) {
		this->name = name;
	}

	 CString getSex() {
		return sex;
	}

	 void setSex(CString sex) {
		this->sex = sex;
	}

	 CString getAge() {
		return age;
	}

	 void setAge(CString age) {
		this->age = age;
	}

	 CString getStuClass() {
		return stuClass;
	}

	 void setStuClass(CString stuClass) {
		this->stuClass = stuClass;
	}

	 CString getPhone() {
		return phone;
	}

	 void setPhone(CString phone) {
		this->phone = phone;
	}

	 CString getQq() {
		return qq;
	}

	 void setQq(CString qq) {
		this->qq = qq;
	}

	 CString getCollege() {
		return college;
	}

	 void setCollege(CString college) {
		this->college = college;
	}
};

// MAINLOG 对话框
//分页
int pageNum=1; //页数编号
int pageSize=2; // 每页显示条数
int intStart; // 开始记录
int intEnd; // 结束记录
int max_page; // 记录最大页数
int recordCout;//总记录数
int fileldCout;//字段数
int k;
CString curPage;
	//初始化数据库对象
MYSQL m_sqlCon;
MYSQL_RES *res;
MYSQL_ROW  row;
CString sql;
CString studentNum;
studentClass student;
list<studentClass> studentInfor;


IMPLEMENT_DYNAMIC(MAINLOG, CDialogEx)

MAINLOG::MAINLOG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ADD_ABOUTBOX, pParent)
	, value(_T(""))
	, stuNum(_T(""))
	, size(_T(""))
	, currentPage(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

MAINLOG::~MAINLOG()
{
}

void MAINLOG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, mList);
	//DDX_Text(pDX, IDC_EDIT3, value);
	DDX_Control(pDX, IDC_BUTTON1, pageId);
	DDX_Text(pDX, IDC_EDIT5, stuNum);
	DDX_Text(pDX, IDC_EDIT10, size);
	DDX_Text(pDX, IDC_EDIT3, currentPage);
}


BEGIN_MESSAGE_MAP(MAINLOG, CDialogEx)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &MAINLOG::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &MAINLOG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MAINLOG::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MAINLOG::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MAINLOG::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &MAINLOG::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &MAINLOG::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &MAINLOG::OnBnClickedButton8)
	ON_EN_CHANGE(IDC_EDIT10, &MAINLOG::OnEnChangeEdit10)
	ON_BN_CLICKED(IDC_BUTTON10, &MAINLOG::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &MAINLOG::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &MAINLOG::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON14, &MAINLOG::OnBnClickedButton14)
END_MESSAGE_MAP()


// MAINLOG 消息处理程序


void MAINLOG::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
void MAINLOG::ListDataShow()
{
	UpdateData(true);
	// TODO: 在此处添加实现代码.
	intStart = pageSize * (pageNum - 1);
	intEnd = pageSize * pageNum;
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon, "SET NAMES GB2312");
	    sql.Format("SELECT studentId,studentNumber,name,sex,age,class,phone,qq,college FROM t_student LIMIT %d,%d", intStart, pageSize);
		int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)sql);
		if (ress == 0) {//检测成功
			res = mysql_store_result(&m_sqlCon);
			mysql_close(&m_sqlCon);//关闭Mysql连接
			while ((row = mysql_fetch_row(res)))
			{
				//mysql_display(&mysql,sqlrow);

				student.setStudentId(row[0]);
				student.setStudentNumber(row[1]);
				student.setName(row[2]);
				student.setSex(row[3]);
				student.setAge(row[4]);
				student.setStuClass(row[5]);
				student.setPhone(row[6]);
				student.setQq(row[7]);
				student.setCollege(row[8]);
				studentInfor.push_back(student);
			}
			list<studentClass>::iterator it;
			int i = 1;
			for (it = studentInfor.begin(); it != studentInfor.end(); it++)
			{
				int nRow = mList.InsertItem(i, it->getStudentId());//插入行 
				mList.SetItemText(i, 0, it->getStudentId());
				mList.SetItemText(nRow, 1, it->getStudentNumber());
				mList.SetItemText(nRow, 2, it->getName());
				mList.SetItemText(nRow, 3, it->getSex());
				mList.SetItemText(nRow, 4, it->getAge());
				mList.SetItemText(nRow, 5, it->getStuClass());
				mList.SetItemText(nRow, 6, it->getPhone());
				mList.SetItemText(nRow, 7, it->getQq());
				mList.SetItemText(nRow, 8, it->getCollege());
				i++;

			}
			 i = 1;
			studentInfor.clear();
			curPage.Format("%d",pageNum);
			curPage = "第"+curPage + "页";
			SetDlgItemText(IDC_EDIT3, curPage);


		}

	}
}



BOOL MAINLOG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CexamSystemDlg dialog;
	iden = dialog.identifyRole();

	if (iden == str[2]) {
		CButton *edit = (CButton*)GetDlgItem(IDC_BUTTON14);
		edit->ShowWindow(FALSE); //隐藏该控件
	}
	//edit->ShowWindow(TRUE) ://显示该控件
	// TODO:  在此添加额外的初始化
	
	DWORD dwStyle = mList.GetExtendedStyle(); //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	mList.SetExtendedStyle(dwStyle);



	mList.InsertColumn(0, "ID", LVCFMT_LEFT, 80); //添加列标题！！！！? 这里的80,40,90用以设置列的宽度。！！！LVCFMT_LEFT用来设置对齐方式！！！
	mList.InsertColumn(1, "学号", LVCFMT_LEFT, 120);
	mList.InsertColumn(2, "名字", LVCFMT_LEFT, 120);
	mList.InsertColumn(3, "性别", LVCFMT_LEFT, 100);
	mList.InsertColumn(4, "年龄", LVCFMT_LEFT, 100);
	mList.InsertColumn(5, "班级", LVCFMT_LEFT, 100);
	mList.InsertColumn(6, "电话", LVCFMT_LEFT, 140);
	mList.InsertColumn(7, "QQ", LVCFMT_LEFT, 140);
	mList.InsertColumn(8, "学院", LVCFMT_LEFT, 160);
	mysql_init(&m_sqlCon);	
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		
	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon, "SET NAMES GB2312");
		sql.Format("SELECT studentId,studentNumber,name,sex,age,class,phone,qq,college FROM t_student");
		int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)sql);
			if (ress == 0) 
			{//检测成功
			res = mysql_store_result(&m_sqlCon);
			//int recordCout;//总记录数
			recordCout = res->row_count;//总记录数
			max_page = recordCout / pageSize + 1;
			mysql_close(&m_sqlCon);//关闭Mysql连接
			}
		}
	ListDataShow();

	return TRUE;  // return TRUE unless you set the focus to a control	异常: OCX 属性页应返回 FALSE
}



//void MAINLOG::ListShow(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}

	
	
	

void MAINLOG::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//首页
	if (pageNum == 1)
	{
		AfxMessageBox(_T("已是第一页"));
	}
	else
	{
		pageNum = 1;
		mList.DeleteAllItems();
		ListDataShow();
	}

}

void MAINLOG::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pageNum == 1)
	{
		AfxMessageBox(_T("已是第一页"));
	}
	if (pageNum > 1)
	{
		pageNum--;
		mList.DeleteAllItems();
		ListDataShow();
	}
}


void MAINLOG::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	pageNum++;
	if (pageNum > max_page)
	{
		pageNum--;
		AfxMessageBox("已是最后一页");
		return;
	}
	mList.DeleteAllItems();
	ListDataShow();
}


void MAINLOG::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pageNum == max_page)
	{
		AfxMessageBox("已是最后一页");
		return;
	}
	else
	{
		pageNum = max_page;
		mList.DeleteAllItems();
		ListDataShow();
	}
}





void MAINLOG::OnBnClickedButton7()
{
	this->UpdateData(true);
	// TODO: 在此添加控件通知处理程序代码
	if (this->stuNum == "") 
	{
		AfxMessageBox("不能为空");
		
	}
	else 
	{
		
		// TODO: 在此添加控件通知处理程序代码
		mysql_init(&m_sqlCon);
		if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else {
			 mList.DeleteAllItems();
			//AfxMessageBox(_T("数据库连接成功!"))
			mysql_query(&m_sqlCon, "SET NAMES GB2312");
			sql.Format("SELECT studentId,studentNumber,name,sex,age,class,phone,qq,college FROM t_student WHERE studentNumber=\'%s\'", this->stuNum);
			int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)sql);
			if (ress == 0)
			{//检测成功
				res = mysql_store_result(&m_sqlCon);
				while ((row = mysql_fetch_row(res)))
				{
					//mysql_display(&mysql,sqlrow);

					student.setStudentId(row[0]);
					student.setStudentNumber(row[1]);
					student.setName(row[2]);
					student.setSex(row[3]);
					student.setAge(row[4]);
					student.setStuClass(row[5]);
					student.setPhone(row[6]);
					student.setQq(row[7]);
					student.setCollege(row[8]);
					studentInfor.push_back(student);
				}
				list<studentClass>::iterator it;
				int i = 1;
				for (it = studentInfor.begin(); it != studentInfor.end(); it++)
				{
					int nRow = mList.InsertItem(i, it->getStudentId());//插入行 
					mList.SetItemText(i, 0, it->getStudentId());
					mList.SetItemText(nRow, 1, it->getStudentNumber());
					mList.SetItemText(nRow, 2, it->getName());
					mList.SetItemText(nRow, 3, it->getSex());
					mList.SetItemText(nRow, 4, it->getAge());
					mList.SetItemText(nRow, 5, it->getStuClass());
					mList.SetItemText(nRow, 6, it->getPhone());
					mList.SetItemText(nRow, 7, it->getQq());
					mList.SetItemText(nRow, 8, it->getCollege());
					i++;
				}
				i = 1;
				studentInfor.clear();
				mysql_close(&m_sqlCon);//关闭Mysql连接
			}
		}
	}

}


void MAINLOG::OnBnClickedButton5()
{
	//CDialog::OnOK();
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	CexamSystemDlg dialog;
	iden = dialog.identifyRole();
	if (iden == str[0]||iden==str[1])
	{
		INFORADD inforAdd;
		inforAdd.DoModal();
	}
	else
	{
		AfxMessageBox(_T("您没有该权限!"));
	}
}


void MAINLOG::OnBnClickedButton8()//刷新
{
	UpdateData(true);
	mList.DeleteAllItems();
	// TODO: 在此添加控件通知处理程序代码
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon, "SET NAMES GB2312");
		sql.Format("SELECT studentId,studentNumber,name,sex,age,class,phone,qq,college FROM t_student");
		int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)sql);
		if (ress == 0)
		{//检测成功
			res = mysql_store_result(&m_sqlCon);
			//int recordCout;//总记录数
			recordCout = res->row_count;//总记录数
			max_page = recordCout / pageSize + 1;
			ListDataShow();
			mysql_close(&m_sqlCon);//关闭Mysql连接
		}
	}
	
}


void MAINLOG::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void MAINLOG::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (this->size == "") 
	{
		AfxMessageBox(_T("不能为空!"));
	}
	else 
	{
		pageSize = atoi(size);
	}
}


void MAINLOG::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CexamSystemDlg dialog;
	iden = dialog.identifyRole();
	if (iden == str[0]||iden == str[1])
	{
		DELETESTU deleteStu;
		deleteStu.DoModal();
	}
	else
	{
		AfxMessageBox(_T("您没有该权限!"));
	}
	
}


void MAINLOG::OnBnClickedButton12()
{
	CDialog::OnOK();
	// TODO: 在此添加控件通知处理程序代码
	CexamSystemDlg newCin;
	newCin.DoModal();

}


void MAINLOG::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	
		CDialog::OnOK();
		STUMARK stuMark;
		stuMark.DoModal();

	
}

