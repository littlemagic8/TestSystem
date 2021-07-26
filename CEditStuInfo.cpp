// CEditStuInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CEditStuInfo.h"
#include "afxdialogex.h"

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
MYSQL m_sqlCon_Editstu;
MYSQL_RES* res1_Editstu;
MYSQL_ROW  row_Editstu;
CString sql_Editstu;
CString sql_Edittea;
//CString studentNum;
studentInfoClass studentinfo;

IMPLEMENT_DYNAMIC(CEditStuInfo, CDialogEx)

CEditStuInfo::CEditStuInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EditstuInfo, pParent)
{

}

CEditStuInfo::~CEditStuInfo()
{
}

void CEditStuInfo::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CEditStuInfo, CDialogEx)
	ON_BN_CLICKED(2, &CEditStuInfo::OnBnClicked2)
	ON_BN_CLICKED(stuSaveBtn, &CEditStuInfo::OnBnClickedstusavebtn)
END_MESSAGE_MAP()


// CEditStuInfo 消息处理程序


BOOL CEditStuInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	mysql_init(&m_sqlCon_Editstu);	
	if (!mysql_real_connect(&m_sqlCon_Editstu, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}

	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon_Editstu, "SET NAMES GB2312");
		sql_Editstu.Format("SELECT StuID,stuName,StuSex,StuProfession,StuBirth,StuSchool,StuEmail FROM tb_studentinfo where StuID ="+this->studentId);
		sql_Edittea.Format("SELECT TeacherID,TeacherName,TeacherSex,TeacherDepart,TeacherTitle,TeacherPlace,TeacherEmail FROM tb_teacherinfo where TeacherID =" + this->studentId);
		int ress = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Editstu);
		if (ress == 0)
		{//检测成功
			res1_Editstu = mysql_store_result(&m_sqlCon_Editstu);
			if (mysql_num_rows(res1_Editstu) == 0)
			{
				ress = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Edittea);
				if (ress == 0)
				{
					isStu = 0;
					res1_Editstu = mysql_store_result(&m_sqlCon_Editstu);
					row_Editstu = mysql_fetch_row(res1_Editstu);
					stuNameREdit.SetWindowTextA(row_Editstu[1]);
					SetDlgItemText(brithOrprof5_, _T("教师系别:"));
					stuBrithEdit.SetWindowTextA(row_Editstu[4]);
					if (row_Editstu[2] == (CString)"男")
					{
						Sex_Men.SetCheck(1);
					}
					else if (row_Editstu[2] == (CString)"女")
					{
						Sex_women.SetCheck(1);
					}
					SetDlgItemText(brithOrprof7_, _T("教师职称:"));
					stuProf.SetWindowTextA(row_Editstu[3]);
					SetDlgItemText(brithOrprof9_, _T("教师办公地点:"));
					stuSchoolEdit.SetWindowTextA(row_Editstu[5]);
					stuEmailEdit.SetWindowTextA(row_Editstu[6]);
					if (EditFlag == 0) {
						stuNameEdit.SetWindowTextA(this->studentNamedlg);
					}
					else
					{
						sql_Editstu.Format("SELECT userName FROM t_user where id =" + this->studentId);
						int ress = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Editstu);
						if (ress == 0)
						{
							res1_Editstu = mysql_store_result(&m_sqlCon_Editstu);
							row_Editstu = mysql_fetch_row(res1_Editstu);
							this->studentNamedlg = row_Editstu[0];
							EditFlag = 0;
						}

					}
				}
				

			}
			else
			{
				isStu = 1;
				row_Editstu = mysql_fetch_row(res1_Editstu);
				stuNameREdit.SetWindowTextA(row_Editstu[1]);
				stuBrithEdit.SetWindowTextA(row_Editstu[4]);
				if (row_Editstu[2] == (CString)"男")
				{
					Sex_Men.SetCheck(1);
				}
				else if (row_Editstu[2] == (CString)"女")
				{
					Sex_women.SetCheck(1);
				}
				stuProf.SetWindowTextA(row_Editstu[3]);
				stuSchoolEdit.SetWindowTextA(row_Editstu[5]);
				stuEmailEdit.SetWindowTextA(row_Editstu[6]);
				if (EditFlag == 0) {
					stuNameEdit.SetWindowTextA(this->studentNamedlg);
				}
				else
				{
					sql_Editstu.Format("SELECT userName FROM t_user where id =" + this->studentId);
					int ress = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Editstu);
					if (ress == 0)
					{
						res1_Editstu = mysql_store_result(&m_sqlCon_Editstu);
						row_Editstu = mysql_fetch_row(res1_Editstu);
						this->studentNamedlg = row_Editstu[0];
						EditFlag = 0;
					}
				
				}
			}
		
			
			//int recordCout;//总记录数
			//recordCout = res->row_count;//总记录数
			//max_page = recordCout / pageSize + 1;
			mysql_close(&m_sqlCon_Editstu);//关闭Mysql连接
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CEditStuInfo::OnBnClicked2()
{
	CDialog::OnOK();
	if (is_admin == 0)
	{
		CallUser ret;
		ret.DoModal();
	}
	if (isStu == 1)
	{
		CStudentDlg  stulog;
		stulog.curUserName = (_T(this->studentNamedlg));
		stulog.curUserId = (_T(this->studentId));
		stulog.DoModal();
	}
	else
	{
		CTeacherDlg  exitinputTest;
		exitinputTest.curUserName = (_T(this->studentNamedlg));
		exitinputTest.curUserId = (_T(this->studentId));
		exitinputTest.DoModal();
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CEditStuInfo::OnBnClickedstusavebtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(true);
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
		if (Sex_Men.GetCheck())
		{
			sex = "男";
		}
		else if (Sex_women.GetCheck())
		{
			sex = "女";
		}	
		mysql_query(&m_sqlCon_Editstu, "SET NAMES GB2312");
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
		if (isStu == 1)
		{
			sql_Editstu.Format("UPDATE t_user set userName = \'%s\'  where id = " + this->studentId, (CString)stuinfoc.name);//(char*)stuNameEdit);
			int ress1 = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Editstu); //+ stuNameREdit +
			sql_Editstu.Format("UPDATE tb_studentinfo set stuName= \'%s\' , StuSex = \'%s\', StuProfession = \'%s\',StuBirth = \'%s\',StuSchool = \'%s\',StuEmail = \'%s\'where StuID = " + this->studentId,
				stuinfoc.nameR, sex, stuinfoc.stuProf, stuinfoc.stuBrith, stuinfoc.college, stuinfoc.email);
			/*+ Sex_Men.GetCheck,StuProfession,StuBirth,StuSchool,StuEmail)VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')", studentNumber1, studentName1,
			/*studentSex1, studentAge1, studClass1, telephone1, stuQQ1, college1);*/
			//sql_Editstu.Format("UPDATE tb_studentinfo set stuName= "张三1" , StuSex =" + sex + ", StuProfession = "软件工程1", StuSchool = "北京大学1" where StuID = 2");
			/*+ Sex_Men.GetCheck,StuProfession,StuBirth,StuSchool,StuEmail)VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')", studentNumber1, studentName1,*/
			int ress = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Editstu);
			if (ress == 0 && ress1 == 0)
			{
				AfxMessageBox(_T("修改数据成功!"));
				//CDialog::OnOK();
				mysql_close(&m_sqlCon_Editstu);//关闭Mysql连接
				EditFlag = 1;
				OnInitDialog();
				//	UpdateData(false);

			}
			else {
				AfxMessageBox(_T("插入数据失败!"));
			}
		}
		else
		{
			sql_Editstu.Format("UPDATE t_user set userName = \'%s\'  where id = " + this->studentId, (CString)stuinfoc.name);//(char*)stuNameEdit);
			int ress1 = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Editstu); //+ stuNameREdit +
			sql_Editstu.Format("UPDATE tb_teacherinfo set TeacherName= \'%s\' , TeacherSex = \'%s\',TeacherDepart = \'%s\', TeacherTitle = \'%s\',TeacherPlace = \'%s\',TeacherEmail = \'%s\' where TeacherID = " + this->studentId,
				stuinfoc.nameR, sex, stuinfoc.stuProf, stuinfoc.stuBrith, stuinfoc.college, stuinfoc.email);
			int ress = mysql_query(&m_sqlCon_Editstu, (char*)(LPCSTR)sql_Editstu);
			if (ress == 0 && ress1 == 0)
			{
				AfxMessageBox(_T("修改数据成功!"));
				//CDialog::OnOK();
				mysql_close(&m_sqlCon_Editstu);//关闭Mysql连接
				EditFlag = 1;
				OnInitDialog();
				//	UpdateData(false);
			}
			else {
				AfxMessageBox(_T("插入数据失败!"));
			}
		}
	}
	
}
