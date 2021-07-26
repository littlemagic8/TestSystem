// CstuMarkManager.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CstuMarkManager.h"
#include "afxdialogex.h"
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"
#include <list>
using namespace std;
//分页
int pageNum2MM = 1; //页数编号
int pageSize2MM = 5; // 每页显示条数
int intStart2MM; // 开始记录
int intEnd2MM; // 结束记录
int max_page2MM; // 记录最大页数
int recordCout2MM;//总记录数
CString curpageNum1;//设置当前的个数
CString curPage2MM;
//初始化数据库对象
MYSQL m_sqlCon2MM;
MYSQL_RES* res2MM;
MYSQL_ROW  row2MM;
CString sql2MM;
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
stuMark stuMark1MM;
list<stuMark> stuMarkInforMM;

// CstuMarkManager 对话框

IMPLEMENT_DYNAMIC(CstuMarkManager, CDialogEx)

CstuMarkManager::CstuMarkManager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ManagerStuMark, pParent)
	, size2(_T(""))
	, stuNum2(_T(""))
	, currentPage2(_T(""))
	, term(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
}

CstuMarkManager::~CstuMarkManager()
{
}

void CstuMarkManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ManagerStuLIST2, mList);
	DDX_Control(pDX, IDC_EDIT4, queryMark);
	DDX_Control(pDX, IDC_EDIT10, viewNum);
	DDX_Control(pDX, IDC_EDIT3, curpage);
}


BEGIN_MESSAGE_MAP(CstuMarkManager, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON10, &CstuMarkManager::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON1, &CstuMarkManager::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CstuMarkManager::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CstuMarkManager::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CstuMarkManager::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON8, &CstuMarkManager::OnBnClickedButton8)
	///ON_BN_CLICKED(IDC_BUTTON11, &CstuMarkManager::OnBnClickedButton11)
	//ON_BN_CLICKED(IDC_BUTTON5, &CstuMarkManager::OnBnClickedButton5)
	//ON_BN_CLICKED(IDC_BUTTON6, &CstuMarkManager::OnBnClickedButton6)
	//ON_BN_CLICKED(IDC_BUTTON9, &CstuMarkManager::OnBnClickedButton9)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CstuMarkManager::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDC_BUTTON12, &CstuMarkManager::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON7, &CstuMarkManager::OnBnClickedButton7)
	ON_EN_CHANGE(IDC_EDIT3, &CstuMarkManager::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT10, &CstuMarkManager::OnEnChangeEdit10)
END_MESSAGE_MAP()
//首页
void CstuMarkManager::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//首页
	if (pageNum2MM == 1)
	{
		AfxMessageBox(_T("已是第一页"));
	}
	else
	{
		pageNum2MM = 1;
		mList.DeleteAllItems();
		listShow();
	}
}
//上一页
void CstuMarkManager::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pageNum2MM == 1)
	{
		AfxMessageBox(_T("已是第一页"));
	}
	if (pageNum2MM > 1)
	{
		pageNum2MM--;
		mList.DeleteAllItems();
		listShow();
	}
}
//下一页
void CstuMarkManager::OnBnClickedButton3()
{

	// TODO: 在此添加控件通知处理程序代码
	pageNum2MM++;
	if (pageNum2MM > max_page2MM)
	{
		pageNum2MM--;
		AfxMessageBox("已是最后一页");
		return;
	}
	mList.DeleteAllItems();
	listShow();
}
//尾页
void CstuMarkManager::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pageNum2MM == max_page2MM)
	{
		AfxMessageBox("已是最后一页");
		return;
	}
	else
	{
		pageNum2MM = max_page2MM;
		mList.DeleteAllItems();
		listShow();
	}
}

void CstuMarkManager::listShow()
{
	// TODO: 在此处添加实现代码.
	mList.DeleteAllItems();
	UpdateData(true);
	// TODO: 在此处添加实现代码.
	intStart2MM = pageSize2MM * (pageNum2MM - 1);
	intEnd2MM = pageSize2MM * pageNum2MM;
	mysql_init(&m_sqlCon2MM);
	if (this->userrole == "" || this->userrole == "学生")
	{
		if (!mysql_real_connect(&m_sqlCon2MM, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));
			return;
		}
		else {
			//AfxMessageBox(_T("数据库连接成功!"));
			mysql_query(&m_sqlCon2MM, "SET NAMES GB2312");
			sql2MM.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark GROUP by id,studentId having studentId = %s LIMIT %d,%d", this->curUserId,intStart2MM, pageSize2MM);
			int ress = mysql_query(&m_sqlCon2MM, (char*)(LPCSTR)sql2MM);
			if (ress == 0) {//检测成功
				res2MM = mysql_store_result(&m_sqlCon2MM);
				mysql_close(&m_sqlCon2MM);//关闭Mysql连接

				while ((row2MM = mysql_fetch_row(res2MM)))
				{
					//mysql_display(&mysql,sqlrow);
					stuMark1MM.setId(row2MM[0]);
					stuMark1MM.setsId(row2MM[1]);
					stuMark1MM.setsObjectOriented(row2MM[2]);
					stuMark1MM.setsEnglish(row2MM[3]);
					stuMark1MM.setsMatrixAnalysis(row2MM[4]);
					stuMark1MM.setTerm(row2MM[5]);
					stuMark1MM.setSumMark(row2MM[6]);
					stuMark1MM.setAverage(row2MM[7]);
					stuMarkInforMM.push_back(stuMark1MM);
				}
				list<stuMark>::iterator it;
				int i = 1;
				for (it = stuMarkInforMM.begin(); it != stuMarkInforMM.end(); it++)
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
				stuMarkInforMM.clear();
				curPage2MM.Format("%d", pageNum2MM);
				curPage2MM = "第" + curPage2MM + "页";
				SetDlgItemText(IDC_EDIT3, curPage2MM);

			}

		}
	}
	else
	{

		if (!mysql_real_connect(&m_sqlCon2MM, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));
			return;
		}
		else {
			//AfxMessageBox(_T("数据库连接成功!"));
			mysql_query(&m_sqlCon2MM, "SET NAMES GB2312");
			sql2MM.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark GROUP by id LIMIT %d,%d", intStart2MM, pageSize2MM);
			int ress = mysql_query(&m_sqlCon2MM, (char*)(LPCSTR)sql2MM);
			if (ress == 0) {//检测成功
				res2MM = mysql_store_result(&m_sqlCon2MM);
				mysql_close(&m_sqlCon2MM);//关闭Mysql连接

				while ((row2MM = mysql_fetch_row(res2MM)))
				{
					//mysql_display(&mysql,sqlrow);
					stuMark1MM.setId(row2MM[0]);
					stuMark1MM.setsId(row2MM[1]);
					stuMark1MM.setsObjectOriented(row2MM[2]);
					stuMark1MM.setsEnglish(row2MM[3]);
					stuMark1MM.setsMatrixAnalysis(row2MM[4]);
					stuMark1MM.setTerm(row2MM[5]);
					stuMark1MM.setSumMark(row2MM[6]);
					stuMark1MM.setAverage(row2MM[7]);
					stuMarkInforMM.push_back(stuMark1MM);
				}
				list<stuMark>::iterator it;
				int i = 1;
				for (it = stuMarkInforMM.begin(); it != stuMarkInforMM.end(); it++)
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
				stuMarkInforMM.clear();
				curPage2MM.Format("%d", pageNum2MM);
				curPage2MM = "第" + curPage2MM + "页";
				SetDlgItemText(IDC_EDIT3, curPage2MM);

			}

		}
	}
}

// CstuMarkManager 消息处理程序
BOOL CstuMarkManager::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwStyle = mList.GetExtendedStyle(); //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	mList.SetExtendedStyle(dwStyle);



	mList.InsertColumn(0, "ID", LVCFMT_LEFT, 80); //添加列标题！！！！? 这里的80,40,90用以设置列的宽度。！！！LVCFMT_LEFT用来设置对齐方式！！！
	mList.InsertColumn(1, "学号", LVCFMT_LEFT, 120);
	mList.InsertColumn(2, "选择题", LVCFMT_LEFT, 120);
	mList.InsertColumn(3, "单选题", LVCFMT_LEFT, 100);
	mList.InsertColumn(4, "简答题", LVCFMT_LEFT, 100);
	mList.InsertColumn(5, "时间", LVCFMT_LEFT, 100);
	mList.InsertColumn(6, "平均分", LVCFMT_LEFT, 110);
	mList.InsertColumn(7, "总分", LVCFMT_LEFT, 110);
	if (this->userrole == "" || this->userrole == "学生")
	{
		mysql_init(&m_sqlCon2MM);
		if (!mysql_real_connect(&m_sqlCon2MM, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else {
			//AfxMessageBox(_T("数据库连接成功!"));
			mysql_query(&m_sqlCon2MM, "SET NAMES GB2312");
			sql2MM.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark GROUP by id having studentId =%s", this->curUserId);
			int ress = mysql_query(&m_sqlCon2MM, (char*)(LPCSTR)sql2MM);
			if (ress == 0)
			{//检测成功
				res2MM = mysql_store_result(&m_sqlCon2MM);
				//int recordCout;//总记录数
				recordCout2MM = res2MM->row_count;//总记录数
				max_page2MM = recordCout2MM / pageSize2MM + 1;
				mysql_close(&m_sqlCon2MM);//关闭Mysql连接
			}
			listShow();
		}
	}
	else
	{

		mysql_init(&m_sqlCon2MM);
		if (!mysql_real_connect(&m_sqlCon2MM, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else {
			//AfxMessageBox(_T("数据库连接成功!"));
			mysql_query(&m_sqlCon2MM, "SET NAMES GB2312");
			sql2MM.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark GROUP by id ");
			int ress = mysql_query(&m_sqlCon2MM, (char*)(LPCSTR)sql2MM);
			if (ress == 0)
			{//检测成功
				res2MM = mysql_store_result(&m_sqlCon2MM);
				//int recordCout;//总记录数
				recordCout2MM = res2MM->row_count;//总记录数
				max_page2MM = recordCout2MM / pageSize2MM + 1;
				mysql_close(&m_sqlCon2MM);//关闭Mysql连接
			}
			listShow();
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
//返回
void CstuMarkManager::OnBnClickedButton12()
{
	CDialog::OnOK();
	if (this->userrole == "" || this->userrole == "学生")
	{
		CStudentDlg teacDlg;
		teacDlg.curUserName = _T(this->curUserName);
		teacDlg.curUserId = _T(this->curUserId);
		teacDlg.userrole = _T(this->userrole);
		teacDlg.DoModal();
	}
	if (is_admin == 0)
	{
		CManagerDlg ret;
		ret.DoModal();
	}	
	// TODO: 在此添加控件通知处理程序代码
	CTeacherDlg teacDlg;
	teacDlg.curUserName = _T(this->curUserName);
	teacDlg.curUserId = _T(this->curUserId);
	teacDlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

//
void CstuMarkManager::OnBnClickedButton7()
{
	UpdateData(false);
	mList.DeleteAllItems();
	CString stuName1;
	GetDlgItemText(IDC_EDIT4, stuName1);
	// TODO: 在此处添加实现代码.
	intStart2MM = pageSize2MM * (pageNum2MM - 1);
	intEnd2MM = pageSize2MM * pageNum2MM;
	if (stuName1 == "")
	{
		listShow();

	}
	else
	{
		mysql_init(&m_sqlCon2MM);
		if (!mysql_real_connect(&m_sqlCon2MM, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));
			return;
		}
		else {
			//AfxMessageBox(_T("数据库连接成功!"));
			mysql_query(&m_sqlCon2MM, "SET NAMES GB2312");
			sql2MM.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark  GROUP by id having id = %s LIMIT %d,%d", stuName1,intStart2MM, pageSize2MM);
			int ress = mysql_query(&m_sqlCon2MM, (char*)(LPCSTR)sql2MM);
			if (ress == 0) {//检测成功
				res2MM = mysql_store_result(&m_sqlCon2MM);
				mysql_close(&m_sqlCon2MM);//关闭Mysql连接

				while ((row2MM = mysql_fetch_row(res2MM)))
				{
					//mysql_display(&mysql,sqlrow);
					stuMark1MM.setId(row2MM[0]);
					stuMark1MM.setsId(row2MM[1]);
					stuMark1MM.setsObjectOriented(row2MM[2]);
					stuMark1MM.setsEnglish(row2MM[3]);
					stuMark1MM.setsMatrixAnalysis(row2MM[4]);
					stuMark1MM.setTerm(row2MM[5]);
					stuMark1MM.setSumMark(row2MM[6]);
					stuMark1MM.setAverage(row2MM[7]);
					stuMarkInforMM.push_back(stuMark1MM);
				}
				list<stuMark>::iterator it;
				int i = 1;
				for (it = stuMarkInforMM.begin(); it != stuMarkInforMM.end(); it++)
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
				stuMarkInforMM.clear();
				curPage2MM.Format("%d", pageNum2MM);
				curPage2MM = "第" + curPage2MM + "页";
				SetDlgItemText(IDC_EDIT3, curPage2MM);

			}

		}
	}
	

	// TODO: 在此添加控件通知处理程序代码
}


void CstuMarkManager::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//设置每页显示的个数
void CstuMarkManager::OnEnChangeEdit10()
{
	UpdateData(false);
	CString curnum;
	GetDlgItemText(IDC_EDIT10, curnum);
	this->size2 = curnum;
	/*if(atoi(size2) > max_page2MM)
	{
		CString str;
		str.Format("%d", max_page2MM);
		str = "当前最多有" + str + "页，请重新输入";
		AfxMessageBox(_T() + _T(str));
	}*/
	if (this->size2 == "")
	{
		AfxMessageBox(_T("不要设置显示个数为空!"));
	}
	else
	{
		pageSize2MM = atoi(size2);
	}
	UpdateData(true);
	// TODO: 在此处添加实现代码.
	intStart2MM = pageSize2MM * (pageNum2MM - 1);
	intEnd2MM = pageSize2MM * pageNum2MM;
	mysql_init(&m_sqlCon2MM);
	if (!mysql_real_connect(&m_sqlCon2MM, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else {
		mList.DeleteAllItems();
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon2MM, "SET NAMES GB2312");
		sql2MM.Format("SELECT id,studentId,objectOriented,english,matrixAnalysis,term,SUM(objectOriented+english+matrixAnalysis) AS markSum,AVG((objectOriented+english+matrixAnalysis)/3) AS average FROM t_mark GROUP by id LIMIT %d,%d", intStart2MM, pageSize2MM);
		int ress = mysql_query(&m_sqlCon2MM, (char*)(LPCSTR)sql2MM);
		if (ress == 0) {//检测成功
			res2MM = mysql_store_result(&m_sqlCon2MM);
			mysql_close(&m_sqlCon2MM);//关闭Mysql连接
			while ((row2MM = mysql_fetch_row(res2MM)))
			{
				//mysql_display(&mysql,sqlrow);

				stuMark1MM.setId(row2MM[0]);
				stuMark1MM.setsId(row2MM[1]);
				stuMark1MM.setsObjectOriented(row2MM[2]);
				stuMark1MM.setsEnglish(row2MM[3]);
				stuMark1MM.setsMatrixAnalysis(row2MM[4]);
				stuMark1MM.setTerm(row2MM[5]);
				stuMark1MM.setSumMark(row2MM[6]);
				stuMark1MM.setAverage(row2MM[7]);
				stuMarkInforMM.push_back(stuMark1MM);
			}
			list<stuMark>::iterator it;
			int i = 1;
			for (it = stuMarkInforMM.begin(); it != stuMarkInforMM.end(); it++)
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
			stuMarkInforMM.clear();
			max_page2MM = recordCout2MM / pageSize2MM + 1;
			mysql_close(&m_sqlCon2MM);//关闭Mysql连接

			listShow();
		}
	}
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


