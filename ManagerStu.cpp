// ManagerStu.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "ManagerStu.h"
#include "afxdialogex.h"
#include<string>
using namespace std;
class studentInfoClassM {
public:
	CString studentId;
	CString studentNumber;
	CString name;
	CString nameR;
	CString sex;
	CString age;
	CString stuProf;
	CString teaPro;
	CString stuBrith;
	CString college;
	CString email;
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

	CString getNameR() {
		return nameR;
	}
	void setNameR(CString nameR) {
		this->nameR = nameR;
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

	CString getStuProf() {
		return stuProf;
	}

	void setStuProf(CString stuProf) {
		this->stuProf = stuProf;
	}

	CString getStuBrith() {
		return stuBrith;
	}

	void setStuBrith(CString stuBrith) {
		this->stuBrith = stuBrith;
	}

	CString getEmail() {
		return email;
	}

	void setEmail(CString email) {
		this->email = email;
	}

	CString getCollege() {
		return college;
	}

	void setCollege(CString college) {
		this->college = college;
	}
};
// CEditStuInfo 对话框
MYSQL m_sqlCon_EditstuM;
MYSQL_RES* res1_EditstuM;
MYSQL_ROW  row_EditstuM;
//CString sql_Editstu;
//CString sql_Edittea;
//CString studentNum;
studentInfoClassM studentinfo;
list<studentInfoClassM> studentInfor;


// ManagerStu 对话框
//分页
int pageNumM = 1; //页数编号
int pageSizeM = 2; // 每页显示条数
int intStartM; // 开始记录
int intEndM; // 结束记录
int max_pageM; // 记录最大页数
int recordCoutM;//总记录数
int fileldCoutM;//字段数
int kM;
CString curPageM;

IMPLEMENT_DYNAMIC(ManagerStu, CDialogEx)

ManagerStu::ManagerStu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ManagerStu, pParent)
	//, valueM(_T(""))
	//, stuNumM(_T(""))
	//, sizeM(_T(""))
	//, currentPageM(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
}

ManagerStu::~ManagerStu()
{
}

//void ManagerStu::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_LIST2, mListM);
//	//DDX_Text(pDX, IDC_EDIT3, valueM);
//
//	//DDX_Text(pDX, IDC_EDIT5, stuNumM);
//	/*DDX_Text(pDX, IDC_EDIT10, sizeM);
//	DDX_Text(pDX, IDC_EDIT3, currentPageM);
//	DDX_Control(pDX, IDC_BUTTON1, pageIdM);*/
//}


BEGIN_MESSAGE_MAP(ManagerStu, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON1, &ManagerStu::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON2, &ManagerStu::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, &ManagerStu::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON4, &ManagerStu::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON7, &ManagerStu::OnBnClickedButton7)
	//ON_BN_CLICKED(IDC_BUTTON5, &ManagerStu::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &ManagerStu::OnBnClickedButton8)
	//ON_EN_CHANGE(IDC_EDIT10, &ManagerStu::OnEnChangeEdit10)
	ON_BN_CLICKED(IDC_BUTTON10, &ManagerStu::OnBnClickedButton10)
//	ON_BN_CLICKED(IDC_BUTTON11, &ManagerStu::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &ManagerStu::OnBnClickedButton12)
	//ON_BN_CLICKED(IDC_BUTTON14, &ManagerStu::OnBnClickedButton14)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ManagerStuLIST2, &ManagerStu::OnLvnItemchangedManagerstulist2)
	ON_BN_CLICKED(IDC_BUTTON7, &ManagerStu::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &ManagerStu::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON11, &ManagerStu::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON6, &ManagerStu::OnBnClickedButton6)
END_MESSAGE_MAP()


// ManagerStu 消息处理程序


void ManagerStu::ListDataShow()
{
	UpdateData(true);
	//清空学生列表
	mListM.DeleteAllItems();
	// TODO: 在此处添加实现代码.
	intStartM = pageSizeM * (pageNumM - 1);
	intEndM = pageSizeM * pageNumM;
	CString sql;
	mysql_init(&m_sqlCon_EditstuM);
	if (!mysql_real_connect(&m_sqlCon_EditstuM, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon_EditstuM, "SET NAMES GB2312");
		sql.Format("SELECT StuID,stuName,StuSex,StuProfession,StuBirth,StuSchool,StuEmail FROM tb_studentinfo");
		//sql.Format("SELECT studentId,studentNumber,name,sex,age,class,phone,qq,college FROM t_student LIMIT %d,%d", intStartM, pageSizeM);
		int ress = mysql_query(&m_sqlCon_EditstuM, (char*)(LPCSTR)sql);
		if (ress == 0) {//检测成功
			res1_EditstuM = mysql_store_result(&m_sqlCon_EditstuM);
			mysql_close(&m_sqlCon_EditstuM);//关闭Mysql连接
			while ((row_EditstuM = mysql_fetch_row(res1_EditstuM)))
			{
				//mysql_display(&mysql,sqlrow);

				studentinfo.setStudentId(row_EditstuM[0]);
				studentinfo.setName(row_EditstuM[1]);
				studentinfo.setSex(row_EditstuM[2]);
				studentinfo.setStuProf(row_EditstuM[3]);
				studentinfo.setStuBrith(row_EditstuM[4]);
				studentinfo.setCollege(row_EditstuM[5]);
				studentinfo.setEmail(row_EditstuM[6]);
				studentInfor.push_back(studentinfo);
			}
			list<studentInfoClassM>::iterator it;
			int i = 1;
			for (it = studentInfor.begin(); it != studentInfor.end(); it++)
			{
				int nRow = mListM.InsertItem(i, it->getStudentId());//插入行 
				mListM.SetItemText(i, 0, it->getStudentId());
				
				mListM.SetItemText(nRow, 1, it->getName());
				mListM.SetItemText(nRow, 2, it->getSex());
				mListM.SetItemText(nRow, 3, it->getStuProf());
				mListM.SetItemText(nRow, 4, it->getStuBrith());
				mListM.SetItemText(nRow, 5, it->getCollege());
				mListM.SetItemText(nRow, 6, it->getEmail());
				i++;

			}
			i = 1;
			studentInfor.clear();
			curPageM.Format("%d", pageNumM);
			curPageM = "第" + curPageM + "页";
			SetDlgItemText(IDC_EDIT3, curPageM);


		}

	}
}
void ManagerStu::OnBnClickedButton8()//刷新
{
	UpdateData(true);
	mListM.DeleteAllItems();
	CString sql;
	// TODO: 在此添加控件通知处理程序代码
	mysql_init(&m_sqlCon_EditstuM);
	if (!mysql_real_connect(&m_sqlCon_EditstuM, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon_EditstuM, "SET NAMES GB2312");
		sql.Format("SELECT StuID,stuName,StuSex,StuProfession,StuBirth,StuSchool,StuEmail FROM tb_studentinfo ");
		int ress = mysql_query(&m_sqlCon_EditstuM, (char*)(LPCSTR)sql);
		if (ress == 0)
		{//检测成功
			res1_EditstuM = mysql_store_result(&m_sqlCon_EditstuM);
			//int recordCoutM;//总记录数
			recordCoutM = res1_EditstuM->row_count;//总记录数
			max_pageM = recordCoutM / pageSizeM + 1;
			ListDataShow();
			mysql_close(&m_sqlCon_EditstuM);//关闭Mysql连接
		}
	}

}
void ManagerStu::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (this->sizeM == "")
	{
		AfxMessageBox(_T("不能为空!"));
	}
	else
	{
		pageSizeM = atoi(sizeM);
	}
}
void ManagerStu::OnBnClickedButton12()
{
	CDialog::OnOK();
	// TODO: 在此添加控件通知处理程序代码
	CTeacherDlg teacDlg;
	teacDlg.curUserName =_T(this->curUserName);
	teacDlg.curUserId = _T(this->curUserId);
	teacDlg.DoModal();

}
BOOL ManagerStu::OnInitDialog()
{
	CString sql;
	CDialogEx::OnInitDialog();
	DWORD dwStyle = mListM.GetExtendedStyle(); //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	mListM.SetExtendedStyle(dwStyle);



	mListM.InsertColumn(0, "ID", LVCFMT_LEFT, 80); //添加列标题！！！！? 这里的80,40,90用以设置列的宽度。！！！LVCFMT_LEFT用来设置对齐方式！！！
	mListM.InsertColumn(1, "姓名", LVCFMT_LEFT, 120);
	mListM.InsertColumn(2, "性别", LVCFMT_LEFT, 120);
	mListM.InsertColumn(3, "专业", LVCFMT_LEFT, 100);
	mListM.InsertColumn(4, "出生日期", LVCFMT_LEFT, 100);
	mListM.InsertColumn(5, "学校", LVCFMT_LEFT, 100);
	mListM.InsertColumn(6, "邮箱", LVCFMT_LEFT, 140);
	mysql_init(&m_sqlCon_EditstuM);
	if (!mysql_real_connect(&m_sqlCon_EditstuM, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon_EditstuM, "SET NAMES GB2312");
		sql.Format("SELECT StuID,stuName,StuSex,StuProfession,StuBirth,StuSchool,StuEmail FROM tb_studentinfo");
		int ress = mysql_query(&m_sqlCon_EditstuM, (char*)(LPCSTR)sql);
		if (ress == 0)
		{//检测成功
			res1_EditstuM = mysql_store_result(&m_sqlCon_EditstuM);
			//int recordCoutM;//总记录数
			recordCoutM = res1_EditstuM->row_count;//总记录数
			max_pageM = recordCoutM / pageSizeM + 1;
			mysql_close(&m_sqlCon_EditstuM);//关闭Mysql连接
		}
	}
	ListDataShow();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ManagerStu::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类
	DDX_Control(pDX, IDC_ManagerStuLIST2, mListM);
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, StuName);
}


void ManagerStu::OnLvnItemchangedManagerstulist2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		strstuIDListS=mListM.GetItemText(pNMListView->iItem, 0);
	}
}


void ManagerStu::OnBnClickedButton7()//查询按钮
{
	UpdateData(false);
	CString sql;
	CString stuName1;
	GetDlgItemText(IDC_EDIT4, stuName1);
	if (stuName1 == "")
	{
		ListDataShow();

	}
	else
	{

		// TODO: 在此添加控件通知处理程序代码
		mysql_init(&m_sqlCon_EditstuM);
		if (!mysql_real_connect(&m_sqlCon_EditstuM, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else {
			mListM.DeleteAllItems();
			//AfxMessageBox(_T("数据库连接成功!"))
			mysql_query(&m_sqlCon_EditstuM, "SET NAMES GB2312");
		//	mysql_query(&m_sqlCon_EditstuM, "SET NAMES GB2312");
			sql.Format("SELECT StuID,stuName,StuSex,StuProfession,StuBirth,StuSchool,StuEmail FROM tb_studentinfo where stuName like \'%%%s%%\'",stuName1);
			
			int ress = mysql_query(&m_sqlCon_EditstuM, (char*)(LPCSTR)sql);
			if (ress == 0)
			{//检测成功
				res1_EditstuM = mysql_store_result(&m_sqlCon_EditstuM);
				while ((row_EditstuM = mysql_fetch_row(res1_EditstuM)))
				{
					//mysql_display(&mysql,sqlrow);
					studentinfo.setStudentId(row_EditstuM[0]);
					studentinfo.setName(row_EditstuM[1]);
					studentinfo.setSex(row_EditstuM[2]);
					studentinfo.setStuProf(row_EditstuM[3]);
					studentinfo.setStuBrith(row_EditstuM[4]);
					studentinfo.setCollege(row_EditstuM[5]);
					studentinfo.setEmail(row_EditstuM[6]);
					studentInfor.push_back(studentinfo);
				}
				list<studentInfoClassM>::iterator it;
				int i = 1;
				for (it = studentInfor.begin(); it != studentInfor.end(); it++)
				{
					int nRow = mListM.InsertItem(i, it->getStudentId());//插入行 
					mListM.SetItemText(i, 0, it->getStudentId());

					mListM.SetItemText(nRow, 1, it->getName());
					mListM.SetItemText(nRow, 2, it->getSex());
					mListM.SetItemText(nRow, 3, it->getStuProf());
					mListM.SetItemText(nRow, 4, it->getStuBrith());
					mListM.SetItemText(nRow, 5, it->getCollege());
					mListM.SetItemText(nRow, 6, it->getEmail());
					i++;
				}
				i = 1;
				studentInfor.clear();
				mysql_close(&m_sqlCon_EditstuM);//关闭Mysql连接
			}
		}
	}
	//ListDataShow();
}

//添加学生用户
void ManagerStu::OnBnClickedButton5()
{
	CDialog::OnOK();
	C_TADDSTU inforAdd;
	inforAdd.studentId = this->curUserId;
	inforAdd.studentNamedlg=this->curUserName;
	inforAdd.DoModal();

	/*INFORADD inforAdd;
	inforAdd.DoModal();*/
	// TODO: 在此添加控件通知处理程序代码
	//MYSQL m_sqlConMS1;
	//MYSQL_RES* res;
	//MYSQL_ROW  row;
	//CString sql, sql1;
	//UpdateData(true);
	//mysql_init(&m_sqlConMS1);
	//if (!mysql_real_connect(&m_sqlConMS1, "localhost", "root",
	//	"", "exam", 3306, NULL, 0))
	//{
	//	AfxMessageBox(_T("数据库连接失败!"));

	//}
	//else {
	//	//AfxMessageBox(_T("数据库连接成功!"));
	//	mysql_query(&m_sqlConMS1, "SET NAMES GB2312");
	//	sql.Format("DElETE FROM tb_studentinfo WHERE StuID=%s", strstuIDListS1);
	//	sql1.Format("DElETE FROM t_user WHERE id=%s", strstuIDListS1);
	//	int ress = mysql_query(&m_sqlConMS1, (char*)(LPCSTR)sql);
	//	int ress1 = mysql_query(&m_sqlConMS1, (char*)(LPCSTR)sql1);
	//	if (ress == 0 && ress1 == 0)
	//	{//成功
	//		AfxMessageBox(_T("添加成功!"));
	//		res = mysql_store_result(&m_sqlConMS1);
	//		mysql_close(&m_sqlConMS1);//关闭Mysql连接
	//	}
	//}

}

//删除学生信息
void ManagerStu::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	if (strstuIDListS == "")
	{
		AfxMessageBox(_T("请选中一行数据进行删除"));
	}
	else
	{
		MYSQL m_sqlConMS;
		MYSQL_RES* res;
		MYSQL_ROW  row;
		CString sql,sql1;
		UpdateData(true);
		mysql_init(&m_sqlConMS);
		if (!mysql_real_connect(&m_sqlConMS, "localhost", "root",
			"", "exam", 3306, NULL, 0))
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else {
			//AfxMessageBox(_T("数据库连接成功!"));
			mysql_query(&m_sqlConMS, "SET NAMES GB2312");
			sql.Format("DElETE FROM tb_studentinfo WHERE StuID=%s", strstuIDListS);
			sql1.Format("DElETE FROM t_user WHERE id=%s", strstuIDListS);
			int ress = mysql_query(&m_sqlConMS, (char*)(LPCSTR)sql);
			int ress1 = mysql_query(&m_sqlConMS, (char*)(LPCSTR)sql1);
			if (ress == 0 && ress1==0)
			{//成功
				AfxMessageBox(_T("删除成功!"));
				res = mysql_store_result(&m_sqlConMS);
				mysql_close(&m_sqlConMS);//关闭Mysql连接
			}
		}
		strstuIDListS = "";
	}
	ListDataShow();
}



void ManagerStu::OnBnClickedButton6()
{
	CDialog::OnOK();
	CstuMarkManager stuMark;
	stuMark.curUserName = _T(this->curUserName);
	stuMark.curUserId = _T(this->curUserId);
	stuMark.DoModal();
}
