// CRegisterUser.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CRegisterUser.h"
#include "afxdialogex.h"

class RstudentInfoClass {
public:
	CString studentId;
	CString studentNumber;
	CString name;
	CString nameR;
	CString sex;
	CString Pwd;
	CString stuProf;
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

	CString getPwd() {
		return Pwd;
	}

	void setPwd(CString Pwd) {
		this->Pwd = Pwd;
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
// CRegisterUser 对话框

IMPLEMENT_DYNAMIC(CRegisterUser, CDialogEx)

CRegisterUser::CRegisterUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Register, pParent)
{

}

CRegisterUser::~CRegisterUser()
{
}

void CRegisterUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, userPwd);
	DDX_Control(pDX, IDC_EDIT1, m_ruser);
	DDX_Control(pDX, IDC_EDIT2, m_rruser);
	DDX_Control(pDX, IDC_COMBO1, m_userDep);
	DDX_Control(pDX, IDC_EDIT9, m_userEmail);
	DDX_Control(pDX, IDC_RADIO2, m_Mr);
	DDX_Control(pDX, IDC_RADIO1, mWr);
	DDX_Control(pDX, IDC_EDIT3, m_brithR);
	DDX_Control(pDX, IDC_EDIT7, m_Rsch);
}


BEGIN_MESSAGE_MAP(CRegisterUser, CDialogEx)
	ON_BN_CLICKED(ReturnLogin, &CRegisterUser::OnBnClickedReturnlogin)
	ON_BN_CLICKED(1, &CRegisterUser::OnBnClicked1)
	ON_EN_CHANGE(IDC_EDIT4, &CRegisterUser::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CRegisterUser 消息处理程序


void CRegisterUser::OnBnClickedReturnlogin()
{
	CDialog::OnOK();
	CexamSystemDlg examLoginDlg;
	examLoginDlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CRegisterUser::OnBnClicked1()
{
	MYSQL m_sqlCon_Editstu;
	MYSQL_RES* res1_Editstu;
	MYSQL_ROW  row_Editstu;
	CString sql_R;
	mysql_init(&m_sqlCon_Editstu);
	if (!mysql_real_connect(&m_sqlCon_Editstu, "localhost", "root", "", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else
	{
		UpdateData(true);
		CString sex;
		if (m_Mr.GetCheck())
		{
			sex = "男";
		}
		else if (mWr.GetCheck())
		{
			sex = "女";
		}
		mysql_query(&m_sqlCon_Editstu, "SET NAMES GB2312");
		//char insert[1000];
		UpdateData(true);
		RstudentInfoClass stuinfoc;
		m_ruser.GetWindowTextA(stuinfoc.name);
		m_rruser.GetWindowTextA(stuinfoc.nameR);
		m_userDep.GetWindowTextA(stuinfoc.stuProf);
		m_userEmail.GetWindowTextA(stuinfoc.email);
		m_Rsch.GetWindowTextA(stuinfoc.college);
		m_brithR.GetWindowTextA(stuinfoc.stuBrith);
		userPwd.GetWindowTextA(stuinfoc.Pwd);
		if (stuinfoc.name == "" || stuinfoc.Pwd == "")
		{
			AfxMessageBox("用户名和密码是必填项");
			return;
		}
		//去重，根据用户名
		sql_R.Format("select * from t_user where userName like \'%s\'",stuinfoc.name);
		int ress2 = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_R);
		res1_Editstu = mysql_store_result(&m_sqlCon_Editstu);
		if (mysql_num_rows(res1_Editstu) != 0)
		{
			AfxMessageBox("用户名重复，请重新输入用户名");
			return;
		}
		sql_R.Format("insert into t_user(userName,role,userPassword)values(\'%s\','学生',\'%s\')", stuinfoc.name, stuinfoc.Pwd);
		int ress1 = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_R);
		
		sql_R.Format("insert into tb_studentinfo(stuName, StuSex, StuProfession, StuBirth, StuSchool, StuEmail) values(\'%s\' ,\'%s\', \'%s\',\'%s\',\'%s\',\'%s\')",
			stuinfoc.nameR, sex, stuinfoc.stuProf, stuinfoc.stuBrith, stuinfoc.college, stuinfoc.email);
		int ress = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_R);
		if (ress == 0 && ress1 == 0)
		{
			AfxMessageBox(_T("插入数据成功!"));
			//CDialog::OnOK();
			mysql_close(&m_sqlCon_Editstu);//关闭Mysql连接
			OnInitDialog();
			//	UpdateData(false);
		}
		else {
			AfxMessageBox(_T("插入数据失败!"));
		}
	}
	OnInitDialog();

}


BOOL CRegisterUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MYSQL m_sqlCon_Editstu;
	MYSQL_RES* res1_Editstu;
	MYSQL_ROW  row_Editstu;
	CString sql_R;
	mysql_init(&m_sqlCon_Editstu);
	if (!mysql_real_connect(&m_sqlCon_Editstu, "localhost", "root", "", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return true;
	}
	else
	{
		UpdateData(true);
		
		mysql_query(&m_sqlCon_Editstu, "SET NAMES GB2312");
		//char insert[1000];
		UpdateData(true);
		RstudentInfoClass stuinfoc;
		MYSQL_ROW stu_dept;
		sql_R.Format("select dept_name from tb_dept");
		int ress2 = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_R);
		res1_Editstu = mysql_store_result(&m_sqlCon_Editstu);

		while (res1_Editstu->data_cursor)
		{
			//m_userDep.AddString(_T((LPCSTR)res1_Editstu->data));
			stu_dept = mysql_fetch_row(res1_Editstu);
			m_userDep.AddString(stu_dept[0]);
			//m_userDep.AddString(_T("鸡啄米"));
		}
		//m_userDep.GetWindowTextA(stuinfoc.stuProf);
		m_userDep.SetCurSel(0);
		//去重，根据用户名
		
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CRegisterUser::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
