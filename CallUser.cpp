// CallUser.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CallUser.h"
#include "afxdialogex.h"
#include<string>
using namespace std;
class allInfoClassM {
public:
	CString studentId;//uerid
	CString studentNumber;//username
	CString name;//role
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
};
// CallUser 对话框
MYSQL m_sqlCon_allM;
MYSQL_RES* res1_allM;
MYSQL_ROW  row_allM;
//CString sql_Editstu;
//CString sql_Edittea;
//CString studentNum;
allInfoClassM studentinfo;
list<allInfoClassM> studentInfor;
IMPLEMENT_DYNAMIC(CallUser, CDialogEx)

CallUser::CallUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_allUser, pParent)
{

}

CallUser::~CallUser()
{
}

void CallUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, allUserList);
}


BEGIN_MESSAGE_MAP(CallUser, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CallUser::OnNMDblclkList1)
	//ON_BN_CLICKED(IDCANCEL, &CallUser::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CallUser::OnBnClickedButton1)
END_MESSAGE_MAP()

void CallUser::ListallShow()
{
	UpdateData(true);
	//清空学生列表
	allUserList.DeleteAllItems();
	// TODO: 在此处添加实现代码.
	//intStartM = pageSizeM * (pageNumM - 1);
	//intEndM = pageSizeM * pageNumM;
	CString sql;
	mysql_init(&m_sqlCon_allM);
	if (!mysql_real_connect(&m_sqlCon_allM, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon_allM, "SET NAMES GB2312");
		sql.Format("SELECT id,userName,role FROM t_user");
		//sql.Format("SELECT studentId,studentNumber,name,sex,age,class,phone,qq,college FROM t_student LIMIT %d,%d", intStartM, pageSizeM);
		int ress = mysql_query(&m_sqlCon_allM, (char*)(LPCSTR)sql);
		if (ress == 0) {//检测成功
			res1_allM = mysql_store_result(&m_sqlCon_allM);
			mysql_close(&m_sqlCon_allM);//关闭Mysql连接
			while ((row_allM = mysql_fetch_row(res1_allM)))
			{
				//mysql_display(&mysql,sqlrow);

				studentinfo.setStudentId(row_allM[0]);
				studentinfo.setName(row_allM[1]);
				studentinfo.setStudentNumber(row_allM[2]);
				studentInfor.push_back(studentinfo);
			}
			list<allInfoClassM>::iterator it;
			int i = 1;
			for (it = studentInfor.begin(); it != studentInfor.end(); it++)
			{
				int nRow = allUserList.InsertItem(i, it->getStudentId());//插入行 
				allUserList.SetItemText(i, 0, it->getStudentId());

				allUserList.SetItemText(nRow, 1, it->getName());
				allUserList.SetItemText(nRow, 2, it->getStudentNumber());
				i++;

			}
			i = 1;
			studentInfor.clear();
		//	curPageM.Format("%d", pageNumM);
			//curPageM = "第" + curPageM + "页";
		//	SetDlgItemText(IDC_EDIT3, curPageM);


		}

	}
}
// CallUser 消息处理程序


void CallUser::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		strmanaIDListS = allUserList.GetItemText(pNMListView->iItem, 0);
	}
	CDialogEx::OnOK();
	CEditStuInfo detailInfo;
	detailInfo.is_admin = 0;
	detailInfo.studentId = strmanaIDListS;
	detailInfo.studentNamedlg = allUserList.GetItemText(pNMListView->iItem, 1);
	detailInfo.DoModal();
	
}


//void CallUser::OnBnClickedCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
//	CManagerDlg mamadlg;
//	mamadlg.DoModal();
//}


BOOL CallUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString sql;
	DWORD dwStyle = allUserList.GetExtendedStyle(); //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	allUserList.SetExtendedStyle(dwStyle);
	allUserList.InsertColumn(0, "ID", LVCFMT_LEFT, 80); //添加列标题！！！！? 这里的80,40,90用以设置列的宽度。！！！LVCFMT_LEFT用来设置对齐方式！！！
	allUserList.InsertColumn(1, "姓名", LVCFMT_LEFT, 120);
	allUserList.InsertColumn(2, "角色", LVCFMT_LEFT, 120);
	mysql_init(&m_sqlCon_allM);
	if (!mysql_real_connect(&m_sqlCon_allM, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else {
		//AfxMessageBox(_T("数据库连接成功!"));
		mysql_query(&m_sqlCon_allM, "SET NAMES GB2312");
		sql.Format("SELECT id,userName,role FROM t_user");
		int ress = mysql_query(&m_sqlCon_allM, (char*)(LPCSTR)sql);
		if (ress == 0)
		{//检测成功
			res1_allM = mysql_store_result(&m_sqlCon_allM);
			//int recordCoutM;//总记录数
			//recordCoutM = res1_EditstuM->row_count;//总记录数
			//max_pageM = recordCoutM / pageSizeM + 1;
			mysql_close(&m_sqlCon_allM);//关闭Mysql连接
		}
	}

	ListallShow();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CallUser::OnBnClickedButton1()
{
	CDialogEx::OnOK();
	CManagerDlg mamadlg;
	mamadlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
