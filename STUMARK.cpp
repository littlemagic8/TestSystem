// STUMARK.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "STUMARK.h"
#include "afxdialogex.h"
#include "MAINLOG.h"
#include "INFORADD.h"
#include "DELETESTU.h"
#include "examSystemDlg.h"
#include "ADDSTUMARK.h"
#include "DELETEMARK.h"
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"
#include <list>
using namespace std;
CString iden2;
//分页
int pageNum2 = 1; //页数编号
int pageSize2 = 2; // 每页显示条数
int intStart2; // 开始记录
int intEnd2; // 结束记录
int max_page2; // 记录最大页数
int recordCout2;//总记录数
int fileldCout2;//字段数
CString curPage2;
//初始化数据库对象
MYSQL m_sqlCon2;
MYSQL_RES *res2;
MYSQL_ROW  row2;
CString sql2;
class stuMark {
public:
	CString id;
	CString sId;
	CString sObjectOriented;
	CString sEnglish;
	CString sMatrixAnalysis;
	CString term;
	CString sumMark;
	CString average;
	
	CString getId() {
		return id;
	}

	void setId(CString id) {
		this->id = id;
	}
	CString getsId() {
		return sId;
	}

	void setsId(CString sId) {
		this->sId = sId;
	}
		CString getsObjectOriented() {
		return sObjectOriented;
	}

	void setsObjectOriented(CString sObjectOriented) {
		this->sObjectOriented = sObjectOriented;
	}
	CString getsEnglish() {
		return sEnglish;
	}

	void setsEnglish(CString sEnglish) {
		this->sEnglish = sEnglish;
	}
	CString getsMatrixAnalysis() {
		return sMatrixAnalysis;
	}

	void setsMatrixAnalysis(CString sMatrixAnalysis) {
		this->sMatrixAnalysis = sMatrixAnalysis;
	}
	CString getTerm() {
		return term;
	}

	void setTerm(CString term) {
		this->term = term;
	}
	 CString getSumMark() {
		return sumMark;
	}

	 void setSumMark(CString sumMark) {
		this->sumMark = sumMark;
	}

	 CString getAverage() {
		return average;
	}

	 void setAverage(CString average) {
		this->average = average;
	}
	
};
stuMark stuMark1;
list<stuMark> stuMarkInfor;

// STUMARK 对话框

IMPLEMENT_DYNAMIC(STUMARK, CDialogEx)

STUMARK::STUMARK(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, size2(_T(""))
	, stuNum2(_T(""))
	, currentPage2(_T(""))
	, term(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

STUMARK::~STUMARK()
{
}

void STUMARK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, mList);
	DDX_Text(pDX, IDC_EDIT10, size2);
	DDX_Text(pDX, IDC_EDIT5, stuNum2);
	DDX_Text(pDX, IDC_EDIT3, currentPage2);
	DDX_Text(pDX, IDC_EDIT7, term);
}


BEGIN_MESSAGE_MAP(STUMARK, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON10, &STUMARK::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON1, &STUMARK::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &STUMARK::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &STUMARK::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &STUMARK::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &STUMARK::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON11, &STUMARK::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON5, &STUMARK::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &STUMARK::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &STUMARK::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON9, &STUMARK::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON12, &STUMARK::OnBnClickedButton12)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &STUMARK::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// STUMARK 消息处理程序
void STUMARK::listShow()
{
	// TODO: 在此处添加实现代码.
	UpdateData(true);
	// TODO: 在此处添加实现代码.
	intStart2 = pageSize2 * (pageNum2 - 1);
	intEnd2 = pageSize2 * pageNum2;
	mysql_init(&m_sqlCon2);
	if (!mysql_real_connect(&m_sqlCon2, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon2, "SET NAMES GB2312");
		sql2.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark GROUP by id LIMIT %d,%d", intStart2, pageSize2);
		int ress = mysql_query(&m_sqlCon2, (char*)(LPCSTR)sql2);
		if (ress == 0) {//检测成功
			res2 = mysql_store_result(&m_sqlCon2);
			mysql_close(&m_sqlCon2);//关闭Mysql连接

			while ((row2 = mysql_fetch_row(res2)))
			{
				//mysql_display(&mysql,sqlrow);
				stuMark1.setId(row2[0]);
				stuMark1.setsId(row2[1]);
				stuMark1.setsObjectOriented(row2[2]);
				stuMark1.setsEnglish(row2[3]);
				stuMark1.setsMatrixAnalysis(row2[4]);
				stuMark1.setTerm(row2[5]);
				stuMark1.setSumMark(row2[6]);
				stuMark1.setAverage(row2[7]);
				stuMarkInfor.push_back(stuMark1);
			}
			list<stuMark>::iterator it;
			int i = 1;
			for (it = stuMarkInfor.begin(); it != stuMarkInfor.end(); it++)
			{
				int nRow = mList.InsertItem(i, it->getId());//插入行 
				mList.SetItemText(i, 0, it->getId());
				mList.SetItemText(nRow, 1, it->getsId());
				mList.SetItemText(nRow, 2, it->getsObjectOriented());
				mList.SetItemText(nRow, 3, it->getsEnglish());
				mList.SetItemText(nRow, 4, it->getsMatrixAnalysis());
				mList.SetItemText(nRow, 5, it->getTerm());
				mList.SetItemText(nRow, 6, it->getAverage());
				mList.SetItemText(nRow, 7, it->getSumMark());
				i++;
			}

			i = 1;
			stuMarkInfor.clear();
			curPage2.Format("%d", pageNum2);
			curPage2 = "第" + curPage2 + "页";
			SetDlgItemText(IDC_EDIT3, curPage2);

		}

	}
}


BOOL STUMARK::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwStyle = mList.GetExtendedStyle(); //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	mList.SetExtendedStyle(dwStyle);



	mList.InsertColumn(0, "ID", LVCFMT_LEFT, 80); //添加列标题！！！！? 这里的80,40,90用以设置列的宽度。！！！LVCFMT_LEFT用来设置对齐方式！！！
	mList.InsertColumn(1, "学号", LVCFMT_LEFT, 120);
	mList.InsertColumn(2, "面向对象", LVCFMT_LEFT, 120);
	mList.InsertColumn(3, "英语", LVCFMT_LEFT, 100);
	mList.InsertColumn(4, "矩阵", LVCFMT_LEFT, 100);
	mList.InsertColumn(5, "时间", LVCFMT_LEFT, 100);
	mList.InsertColumn(6, "平均分", LVCFMT_LEFT, 110);
	mList.InsertColumn(7, "总分", LVCFMT_LEFT, 110);

	mysql_init(&m_sqlCon2);
	if (!mysql_real_connect(&m_sqlCon2, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon2, "SET NAMES GB2312");
		sql2.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark GROUP by id");
		int ress = mysql_query(&m_sqlCon2, (char*)(LPCSTR)sql2);
		if (ress == 0)
		{//检测成功
			res2 = mysql_store_result(&m_sqlCon2);
			//int recordCout;//总记录数
			recordCout2 = res2->row_count;//总记录数
			max_page2 = recordCout2 / pageSize2 + 1;
			mysql_close(&m_sqlCon2);//关闭Mysql连接
		}
		listShow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void STUMARK::OnBnClickedButton10()//确定
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (this->size2 == "")
	{
		AfxMessageBox(_T("不能为空!"));
	}
	else
	{
		pageSize2 = atoi(size2);
	}
}


void STUMARK::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//首页
	if (pageNum2 == 1)
	{
		AfxMessageBox(_T("已是第一页"));
	}
	else
	{
		pageNum2 = 1;
		mList.DeleteAllItems();
		listShow();
	}
}


void STUMARK::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pageNum2 == 1)
	{
		AfxMessageBox(_T("已是第一页"));
	}
	if (pageNum2 > 1)
	{
		pageNum2--;
		mList.DeleteAllItems();
		listShow();
	}
}


void STUMARK::OnBnClickedButton3()
{

	// TODO: 在此添加控件通知处理程序代码
	pageNum2++;
	if (pageNum2 > max_page2)
	{
		pageNum2--;
		AfxMessageBox("已是最后一页");
		return;
	}
	mList.DeleteAllItems();
	listShow();
}


void STUMARK::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pageNum2 == max_page2)
	{
		AfxMessageBox("已是最后一页");
		return;
	}
	else
	{
		pageNum2 = max_page2;
		mList.DeleteAllItems();
		listShow();
	}
}

//刷新
void STUMARK::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	//刷新
	UpdateData(true);
	mList.DeleteAllItems();

	// TODO: 在此添加控件通知处理程序代码
	mysql_init(&m_sqlCon2);
	if (!mysql_real_connect(&m_sqlCon2, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon2, "SET NAMES GB2312");
		sql2.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark group by id");
		int ress = mysql_query(&m_sqlCon2, (char*)(LPCSTR)sql2);
		if (ress == 0)
		{//检测成功
			res2 = mysql_store_result(&m_sqlCon2);
			//int recordCout;//总记录数
			recordCout2 = res2->row_count;//总记录数
			max_page2 = recordCout2 / pageSize2 + 1;
			listShow();
			mysql_close(&m_sqlCon2);//关闭Mysql连接
		}
	}
}


void STUMARK::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CexamSystemDlg dialog;
	iden2 = dialog.identifyRole();
	if (iden2 == str[0])
	{
		DELETEMARK deleteStu;
		deleteStu.DoModal();
	}
	else
	{
		AfxMessageBox(_T("您没有该权限!"));
	}
}


void STUMARK::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CexamSystemDlg dialog;
	iden2 = dialog.identifyRole();
	if (iden2 == str[0])
	{
		ADDSTUMARK inforAdd;
		inforAdd.DoModal();
	}
	else
	{
		AfxMessageBox(_T("您没有该权限!"));
	}
}


void STUMARK::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	// TODO: 在此处添加实现代码.
	intStart2 = pageSize2 * (pageNum2 - 1);
	intEnd2 = pageSize2 * pageNum2;
	mysql_init(&m_sqlCon2);
	if (!mysql_real_connect(&m_sqlCon2, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else {
		mList.DeleteAllItems();
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon2, "SET NAMES GB2312");
		sql2.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark WHERE studentId=\'%s\'", this->stuNum2);
		int ress = mysql_query(&m_sqlCon2, (char*)(LPCSTR)sql2);
		if (ress == 0) {//检测成功
			res2 = mysql_store_result(&m_sqlCon2);
			mysql_close(&m_sqlCon2);//关闭Mysql连接
			while ((row2 = mysql_fetch_row(res2)))
			{
				//mysql_display(&mysql,sqlrow);

				stuMark1.setId(row2[0]);
				stuMark1.setsId(row2[1]);
				stuMark1.setsObjectOriented(row2[2]);
				stuMark1.setsEnglish(row2[3]);
				stuMark1.setsMatrixAnalysis(row2[4]);
				stuMark1.setTerm(row2[5]);
				stuMark1.setSumMark(row2[6]);
				stuMark1.setAverage(row2[7]);
				stuMarkInfor.push_back(stuMark1);
			}
			list<stuMark>::iterator it;
			int i = 1;
			for (it = stuMarkInfor.begin(); it != stuMarkInfor.end(); it++)
			{
				int nRow = mList.InsertItem(i, it->getId());//插入行 
				mList.SetItemText(i, 0, it->getId());
				mList.SetItemText(nRow, 1, it->getsId());
				mList.SetItemText(nRow, 2, it->getsObjectOriented());
				mList.SetItemText(nRow, 3, it->getsEnglish());
				mList.SetItemText(nRow, 4, it->getsMatrixAnalysis());
				mList.SetItemText(nRow, 5, it->getTerm());
				mList.SetItemText(nRow, 6, it->getAverage());
				mList.SetItemText(nRow, 7, it->getSumMark());
				i++;

			}
			i = 1;
			stuMarkInfor.clear();
			mysql_close(&m_sqlCon2);//关闭Mysql连接

		}
	}
}


void STUMARK::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	MAINLOG mainLog;
	mainLog.DoModal();
}


void STUMARK::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	mList.DeleteAllItems();
	// TODO: 在此处添加实现代码.
	intStart2 = pageSize2 * (pageNum2 - 1);
	intEnd2 = pageSize2 * pageNum2;
	mysql_init(&m_sqlCon2);
	if (!mysql_real_connect(&m_sqlCon2, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon2, "SET NAMES GB2312");
		sql2.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark WHERE YEAR(term)=\'%s\' GROUP by id", this->term);
		int ress = mysql_query(&m_sqlCon2, (char*)(LPCSTR)sql2);
		if (ress == 0) {//检测成功
			res2 = mysql_store_result(&m_sqlCon2);
			mysql_close(&m_sqlCon2);//关闭Mysql连接
			while ((row2 = mysql_fetch_row(res2)))
			{
				//mysql_display(&mysql,sqlrow);

				stuMark1.setId(row2[0]);
				stuMark1.setsId(row2[1]);
				stuMark1.setsObjectOriented(row2[2]);
				stuMark1.setsEnglish(row2[3]);
				stuMark1.setsMatrixAnalysis(row2[4]);
				stuMark1.setTerm(row2[5]);
				stuMark1.setSumMark(row2[6]);
				stuMark1.setAverage(row2[7]);
				stuMarkInfor.push_back(stuMark1);
			}
			list<stuMark>::iterator it;
			int i = 1;
			for (it = stuMarkInfor.begin(); it != stuMarkInfor.end(); it++)
			{
				int nRow = mList.InsertItem(i, it->getId());//插入行 
				mList.SetItemText(i, 0, it->getId());
				mList.SetItemText(nRow, 1, it->getsId());
				mList.SetItemText(nRow, 2, it->getsObjectOriented());
				mList.SetItemText(nRow, 3, it->getsEnglish());
				mList.SetItemText(nRow, 4, it->getsMatrixAnalysis());
				mList.SetItemText(nRow, 5, it->getTerm());
				mList.SetItemText(nRow, 6, it->getAverage());
				mList.SetItemText(nRow, 7, it->getSumMark());
				i++;

			}
			i = 1;
			stuMarkInfor.clear();
			//mysql_close(&m_sqlCon2);//关闭Mysql连接

		}
	}

}

//回到登录页面
void STUMARK::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	// TODO: 在此添加控件通知处理程序代码
	CexamSystemDlg newCin;
	newCin.DoModal();
}


void STUMARK::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
