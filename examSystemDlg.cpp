
// examSystemDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "examSystemDlg.h"
#include "afxdialogex.h"
#include "string.h"
#include "MAINLOG.h"
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
//mysql头文件
#include "mysql.h"
//extern CString str[2] = { "学生","教师" };


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CexamSystemDlg 对话框



CexamSystemDlg::CexamSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMSYSTEM_DIALOG, pParent)
	, userPassword(_T(""))
	, userName(_T(""))

{
	m_Brush.CreateSolidBrush(RGB(166,243,248));
	//m_Brush.CreateSolidBrush(RGB(200, 88, 88));
	//m_font.CreatePointFont(200,(LPCTSTR)"黑体");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CexamSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT2, userPassword);
	//  DDX_Text(pDX, IDC_EDIT1, userName);
	DDX_Text(pDX, IDC_EDIT1, userName);
	DDX_Text(pDX, IDC_EDIT2, userPassword);
	//DDX_Control(pDX, IDC_COMBO1, identify);
}

BEGIN_MESSAGE_MAP(CexamSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CexamSystemDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CexamSystemDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CexamSystemDlg::OnBnClickedButton2)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_REGBTN, &CexamSystemDlg::OnBnClickedRegbtn)
END_MESSAGE_MAP()


// CexamSystemDlg 消息处理程序

BOOL CexamSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*identify.AddString(str[0]);
	identify.AddString(str[1]);
	identify.AddString(str[2]);*/
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	
	UpdateData(true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CexamSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CexamSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/*CImage* m_sLogInPic;//新建一个CImage的对象 用于储存图片
		m_sLogInPic = new CImage;
		m_sLogInPic->Load("exam.jpg");//使用m_sLogInPic读取图片引号中添加图片地址及图片名
		CPaintDC dc(this); // 建立一个矩形在矩形中画图
		CRect rect;
		GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);//规定矩形为你所创建的图片控件（括号内为控件ID）若是为整个窗口添加背景将矩形设为整个窗口即可
		ScreenToClient(&rect);
		dc.SetStretchBltMode(HALFTONE);
		m_sLogInPic->Draw(dc.m_hDC, rect);//通过画图 将图片paint出来 
		//CDialogEx::OnPaint();
		//注释该语句：防止重复调用重画函数*/
CDialog::OnPaint(); 
//添加代码对话框背景贴图
	/*	CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);    //获取对话框长宽      
		CDC   dcBmp;             //定义并创建一个内存设备环境
		dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
		CBitmap   bmpBackground;
		//bmpBackground.CreateCompatibleBitmap(&dcBmp, 20, 20);
		bmpBackground.LoadBitmap(IDB_BITMAP1);    //载入资源中图片
		BITMAP   m_bitmap;                         //图片变量   
		
		bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
		//将位图选入临时内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
		//调用函数显示图片StretchBlt显示形状可变
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	*/}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CexamSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

class User {
public:
	CString userId;
	CString userName;
	CString userPassword;
	CString role;
};
void CexamSystemDlg::OnBnClickedButton1()
{
	this->UpdateData(true);
	// TODO: 在此添加控件通知处理程序代码
	//初始化数据库对象
	MYSQL m_sqlCon;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	User user;
	mysql_init(&m_sqlCon);
	// TODO: 在此添加控件通知处理程序代码
	
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"", "exam", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
		return;
	}
	else//连接成功则继续访问数据库
	{
		//AfxMessageBox(_T("数据库连接成功!"));
		UpdateData(true);
		CString query;
		if (this->userPassword == "" || this->userName == "")
		{
			MessageBox("用户名或者密码不能为空!");
		}
		else
		{
			mysql_query(&m_sqlCon, "SET NAMES GB2312");
			query.Format("select userName,userPassword,role,id from t_user where userName = \'%s\' and userPassword=\'%s\'", this->userName, this->userPassword);
			int ress = mysql_query(&m_sqlCon, (char*)(LPCSTR)query);
			if (ress == 0) //检测查询成功
			{
				CString role = "";
				res = mysql_store_result(&m_sqlCon);
				if (mysql_num_rows(res) == 0) //查询结果为空
				{
					AfxMessageBox("用户或输入密码错误不存在");
				}
				else
				{
					row = mysql_fetch_row(res);
					//role = "学生";
					if (row[2] == (CString)"学生")
					{
						strIdentify = "学生";
						mysql_free_result(res);
						CDialog::OnOK();
						/*MAINLOG  mianlog;
						mianlog.DoModal();*/
						/**/CStudentDlg  stulog;
						stulog.curUserName = row[0];
						stulog.userrole = row[2];
						stulog.curUserId = row[3];
						stulog.DoModal();//让对话框对象以有模式形式显示出来
						UpdateData(false);
						mysql_close(&m_sqlCon);//关闭Mysql连接
					}
					//role = "教师";
					else if (row[2] == (CString)"教师")
					{
						strIdentify = "教师";
						mysql_free_result(res);
						//CDialog::OnOK();
						CDialog::OnOK();
						CTeacherDlg  teaclog;
						teaclog.curUserName = row[0];
						teaclog.curUserId = row[3];
						/*MAINLOG  onlineTest;
						onlineTest.DoModal();*/
						//让对话框对象以有模式形式显示出来
						teaclog.DoModal();
						UpdateData(false);
						mysql_close(&m_sqlCon);//关闭Mysql连接
					}
					else if (row[2] == (CString)"管理员")
					{
						strIdentify = "管理员";
						mysql_free_result(res);
						//CDialog::OnOK();//关闭当前对话框
						CDialog::OnOK();
						/*MAINLOG  onlineTest;
						onlineTest.DoModal();*/
						CManagerDlg  manlog;
						manlog.DoModal();//让对话框对象以有模式形式显示出来
						UpdateData(false);
						mysql_close(&m_sqlCon);//关闭Mysql连接
					}
					/*if (strIdentify==row[2])
					{
						mysql_free_result(res);
						CDialog::OnOK();

						MAINLOG  mianlog;
						mianlog.DoModal();//让对话框对象以有模式形式显示出来
						UpdateData(false);
						mysql_close(&m_sqlCon);//关闭Mysql连接
					}*/
					else
					{
						AfxMessageBox("用户名或密码错误!");
					}
				}
			}

		}
	}
}


void CexamSystemDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(true);
	int nIndex = identify.GetCurSel();
	strIdentify = str[nIndex];*/
}





CString CexamSystemDlg::identifyRole()
{
	// TODO: 在此处添加实现代码.
	return strIdentify;
}


void CexamSystemDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}





HBRUSH CexamSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return m_Brush;
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		//pDC->SetBkColor(RGB(110, 110, 110));
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)m_Brush;
	}
	//if(pWnd->GetS)
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}



void CexamSystemDlg::OnBnClickedRegbtn()
{
	CDialog::OnOK();
	/*MAINLOG  mianlog;
	mianlog.DoModal();*/
	/**/CRegisterUser  regUser;
	regUser.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
