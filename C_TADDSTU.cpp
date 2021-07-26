// C_TADDSTU.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "C_TADDSTU.h"
#include "afxdialogex.h"


// C_TADDSTU 对话框
class studentInfoClass {
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
MYSQL m_sqlCon_EditstuTADD;
MYSQL_RES* res1_EditstuTADD;
MYSQL_ROW  row_EditstuTADD;
CString sql_EditstuTADD;
CString sql_EditteaTADD;
IMPLEMENT_DYNAMIC(C_TADDSTU, CDialogEx)

C_TADDSTU::C_TADDSTU(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AddstuInfo, pParent)
{

}

C_TADDSTU::~C_TADDSTU()
{
}

void C_TADDSTU::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, stuNameEdit);
	DDX_Control(pDX, IDC_EDIT2, stuNameREdit);
	DDX_Control(pDX, IDC_EDIT4, stuBrithEdit);
	DDX_Control(pDX, IDC_RADIO2, Sex_Men);
	DDX_Control(pDX, IDC_RADIO1, Sex_women);
	DDX_Control(pDX, IDC_COMBO1, stuProf);
	DDX_Control(pDX, IDC_EDIT9, stuEmailEdit);
	DDX_Control(pDX, IDC_EDIT12, stuSchoolEdit);
}


BEGIN_MESSAGE_MAP(C_TADDSTU, CDialogEx)
	
	ON_BN_CLICKED(stuSaveBtn, &C_TADDSTU::OnBnClickedstusavebtn)
	ON_BN_CLICKED(2, &C_TADDSTU::OnBnClicked2)
END_MESSAGE_MAP()


// C_TADDSTU 消息处理程序


BOOL C_TADDSTU::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	/*mysql_init(&m_sqlCon_EditstuTADD);
	if (!mysql_real_connect(&m_sqlCon_EditstuTADD, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}

	else {*/
		//AfxMessageBox(_T("数据库连接成功!"));
		//mysql_query(&m_sqlCon_EditstuTADD, "SET NAMES GB2312");
		//sql_EditstuTADD.Format("SELECT StuID,stuName,StuSex,StuProfession,StuBirth,StuSchool,StuEmail FROM tb_studentinfo where StuID =" + this->studentId);
		//sql_EditteaTADD.Format("SELECT TeacherID,TeacherName,TeacherSex,TeacherDepart,TeacherTitle,TeacherPlace,TeacherEmail FROM tb_teacherinfo where TeacherID =" + this->studentId);
		//int ress = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditstuTADD);
	//	if (ress == 0)
	//	{//检测成功
	//		res1_EditstuTADD = mysql_store_result(&m_sqlCon_EditstuTADD);
	//		if (mysql_num_rows(res1_EditstuTADD) == 0)
	//		{
	//			ress = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditteaTADD);
	//			if (ress == 0)
	//			{
	//				isStu = 0;
	//				res1_EditstuTADD = mysql_store_result(&m_sqlCon_EditstuTADD);
	//				row_EditstuTADD = mysql_fetch_row(res1_EditstuTADD);
	//				stuNameREdit.SetWindowTextA(row_EditstuTADD[1]);
	//				SetDlgItemText(brithOrprof5_, _T("教师系别:"));
	//				stuBrithEdit.SetWindowTextA(row_EditstuTADD[4]);
	//				if (row_EditstuTADD[2] == (CString)"男")
	//				{
	//					Sex_Men.SetCheck(1);
	//				}
	//				else if (row_EditstuTADD[2] == (CString)"女")
	//				{
	//					Sex_women.SetCheck(1);
	//				}
	//				SetDlgItemText(brithOrprof7_, _T("教师职称:"));
	//				stuProf.SetWindowTextA(row_EditstuTADD[3]);
	//				SetDlgItemText(brithOrprof9_, _T("教师办公地点:"));
	//				stuSchoolEdit.SetWindowTextA(row_EditstuTADD[5]);
	//				stuEmailEdit.SetWindowTextA(row_EditstuTADD[6]);
	//				if (EditFlag == 0) {
	//					stuNameEdit.SetWindowTextA(this->studentNamedlg);
	//				}
	//				else
	//				{
						//sql_EditstuTADD.Format("SELECT userName FROM t_user where id =" + this->studentId);
						//int ress = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditstuTADD);
						//if (ress == 0)
						//{
						//	res1_EditstuTADD = mysql_store_result(&m_sqlCon_EditstuTADD);
						//	row_EditstuTADD = mysql_fetch_row(res1_EditstuTADD);
						//	this->studentNamedlg = row_EditstuTADD[0];
						//	EditFlag = 0;
						//}

	//				}
	//			}


	//		}
	//		else
	//		{
	//			isStu = 1;
	//			row_EditstuTADD = mysql_fetch_row(res1_EditstuTADD);
	//			stuNameREdit.SetWindowTextA(row_EditstuTADD[1]);
	//			stuBrithEdit.SetWindowTextA(row_EditstuTADD[4]);
	//			if (row_EditstuTADD[2] == (CString)"男")
	//			{
	//				Sex_Men.SetCheck(1);
	//			}
	//			else if (row_EditstuTADD[2] == (CString)"女")
	//			{
	//				Sex_women.SetCheck(1);
	//			}
	//			stuProf.SetWindowTextA(row_EditstuTADD[3]);
	//			stuSchoolEdit.SetWindowTextA(row_EditstuTADD[5]);
	//			stuEmailEdit.SetWindowTextA(row_EditstuTADD[6]);
	//			if (EditFlag == 0) {
	//				stuNameEdit.SetWindowTextA(this->studentNamedlg);
	//			}
	//			else
	//			{
	//				sql_EditstuTADD.Format("SELECT userName FROM t_user where id =" + this->studentId);
	//				int ress = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditstuTADD);
	//				if (ress == 0)
	//				{
	//					res1_EditstuTADD = mysql_store_result(&m_sqlCon_EditstuTADD);
	//					row_EditstuTADD = mysql_fetch_row(res1_EditstuTADD);
	//					this->studentNamedlg = row_EditstuTADD[0];
	//					EditFlag = 0;
	//				}

	//			}
	//		}


	//		//int recordCout;//总记录数
	//		//recordCout = res->row_count;//总记录数
	//		//max_page = recordCout / pageSize + 1;
	//		mysql_close(&m_sqlCon_EditstuTADD);//关闭Mysql连接
	//	}
	//}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void C_TADDSTU::OnBnClickedstusavebtn()
{
	this->UpdateData(true);
	mysql_init(&m_sqlCon_EditstuTADD);
	if (!mysql_real_connect(&m_sqlCon_EditstuTADD, "localhost", "root", "", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else
	{
		UpdateData(true);
		CString sex;
		if (Sex_Men.GetCheck())
		{
			sex = "男";
		}
		else if (Sex_women.GetCheck())
		{
			sex = "女";
		}
		mysql_query(&m_sqlCon_EditstuTADD, "SET NAMES GB2312");
		//char insert[1000];
		UpdateData(true);
		studentInfoClass stuinfoc;
		stuNameEdit.GetWindowTextA(stuinfoc.name);
		stuNameREdit.GetWindowTextA(stuinfoc.nameR);
		stuProf.GetWindowTextA(stuinfoc.stuProf);
		stuEmailEdit.GetWindowTextA(stuinfoc.email);
		stuSchoolEdit.GetWindowTextA(stuinfoc.college);
		stuBrithEdit.GetWindowTextA(stuinfoc.stuBrith);
		//当前登录的是学生
		/*if (isStu == 1)
		{*/
			sql_EditstuTADD.Format("insert into t_user(userName) values(\'%s\')" ,(CString)stuinfoc.name);//(char*)stuNameEdit);
			int ress1 = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditstuTADD); //+ stuNameREdit +
			sql_EditstuTADD.Format("insert into tb_studentinfo(stuName, StuSex,StuProfession,StuBirth,StuSchool,StuEmail)values(\'%s\' , \'%s\',\'%s\', \'%s\', \'%s\', \'%s\')" ,
				stuinfoc.nameR, sex, stuinfoc.stuProf, stuinfoc.stuBrith, stuinfoc.college, stuinfoc.email);
			/*+ Sex_Men.GetCheck,StuProfession,StuBirth,StuSchool,StuEmail)VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')", studentNumber1, studentName1,
			/*studentSex1, studentAge1, studClass1, telephone1, stuQQ1, college1);*/
			//sql_EditstuTADD.Format("UPDATE tb_studentinfo set stuName= "张三1" , StuSex =" + sex + ", StuProfession = "软件工程1", StuSchool = "北京大学1" where StuID = 2");
			/*+ Sex_Men.GetCheck,StuProfession,StuBirth,StuSchool,StuEmail)VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')", studentNumber1, studentName1,*/
			int ress = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditstuTADD);
			if (ress == 0 && ress1 == 0)
			{
				AfxMessageBox(_T("插入数据成功!"));
				//CDialog::OnOK();
				mysql_close(&m_sqlCon_EditstuTADD);//关闭Mysql连接
				EditFlag = 1;
				OnInitDialog();
				//	UpdateData(false);

			}
			else {
				AfxMessageBox(_T("插入数据失败!"));
			}
		//}
		//else
		//{
		//	sql_EditstuTADD.Format("insert into t_user(id,userName)values(%s,\'%s\')", this->studentId, (CString)stuinfoc.name);//  where id = " + this->studentId, (CString)stuinfoc.name);//(char*)stuNameEdit);
		//	int ress1 = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditstuTADD); //+ stuNameREdit +
		//	sql_EditstuTADD.Format("UPDATE tb_teacherinfo set TeacherName= \'%s\' , TeacherSex = \'%s\',TeacherDepart = \'%s\', TeacherTitle = \'%s\',TeacherPlace = \'%s\',TeacherEmail = \'%s\' where TeacherID = " + this->studentId,
		//		stuinfoc.nameR, sex, stuinfoc.stuProf, stuinfoc.stuBrith, stuinfoc.college, stuinfoc.email);
		//	int ress = mysql_query(&m_sqlCon_EditstuTADD, (char*)(LPCSTR)sql_EditstuTADD);
		//	if (ress == 0 && ress1 == 0)
		//	{
		//		AfxMessageBox(_T("插入数据成功!"));
		//		//CDialog::OnOK();
		//		mysql_close(&m_sqlCon_EditstuTADD);//关闭Mysql连接
		//		EditFlag = 1;
		//		OnInitDialog();
		//		//	UpdateData(false);
		//	}
		//	else {
		//		AfxMessageBox(_T("插入数据失败!"));
		//	}
		//}
	}
	// TODO: 在此添加控件通知处理程序代码
	studentInfoClass stuinfoc;
	stuNameEdit.SetWindowTextA("");
	stuNameREdit.SetWindowTextA("");
	stuProf.SetWindowTextA("");
	stuEmailEdit.SetWindowTextA("");
	stuSchoolEdit.SetWindowTextA("");
	stuBrithEdit.SetWindowTextA("");
}


void C_TADDSTU::OnBnClicked2()
{
	CDialog::OnOK();
	ManagerStu stulog;
	stulog.curUserName = (_T(this->studentNamedlg));
	stulog.curUserId = (_T(this->studentId));
	stulog.DoModal();
}
