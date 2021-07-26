// CTestManager.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CTestManager.h"
#include "afxdialogex.h"
#include "mysql.h"
#include "CManagerDlg.h"
// CTestManager 对话框

IMPLEMENT_DYNAMIC(CTestManager, CDialogEx)

CTestManager::CTestManager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TestManager, pParent)
{

}

CTestManager::~CTestManager()
{
}

void CTestManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, testList);
}


BEGIN_MESSAGE_MAP(CTestManager, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CTestManager::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestManager 消息处理程序


BOOL CTestManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();
   
    HTREEITEM hRoot;     // 树的根节点的句柄   
    HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
    HTREEITEM hArtItem;  // 可表示任一文章节点的句柄 
    // TODO:  在此添加额外的初始化
    // 插入根节点   
    MYSQL m_sqlConTestManager;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConTestManager);
   // hRoot = courseName.InsertItem(_T("课程列表"), 0, 0);
    //CString query3;
    //query3.Format("select DISTINCT QType from tb_question");
    ////  query3 = "select ChapterID,ChapterName from tb_chapterinfo where CourseID = "+
    //int ress3 = mysql_query(&m_sqlConTestManager, (char*)(LPCSTR)query3);
    //if (ress3 == 0)
    //{
    //    resInputSingle = mysql_store_result(&m_sqlConTestManager);
    //    if (mysql_num_rows(resInputSingle) == 0) //查询结果为空
    //    {
    //        AfxMessageBox("请维护该试题类型！");
    //    }
    //    else
    //    {

    //        rowInputSingle = mysql_fetch_row(resInputSingle);
    //       // testTypeI.AddString(rowInputSingle[0]);
    //        while (resInputSingle->data_cursor)
    //        {
    //            rowInputSingle = mysql_fetch_row(resInputSingle);
    //           // testTypeI.AddString(rowInputSingle[0]);
    //        }
    //       // testTypeI.SetCurSel(0);
    //        mysql_free_result(resInputSingle);
    //    }
    //}
    if (!mysql_real_connect(&m_sqlConTestManager, "localhost", "root",
        "", "exam", 3306, NULL, 0))
    {
        AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
        return FALSE;
    }
    else
    {

    
    CRect rect;

    // 获取编程语言列表视图控件的位置和大小   
    testList.GetClientRect(&rect);

    // 为列表视图控件添加全行选中和栅格风格   
    testList.SetExtendedStyle(testList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // 为列表视图控件添加8列   
    testList.InsertColumn(0, _T("题目编号"), LVCFMT_CENTER, rect.Width() / 13, 0);
    testList.InsertColumn(1, _T("题目类型"), LVCFMT_CENTER, rect.Width() / 13, 1);
    testList.InsertColumn(2, _T("难度"), LVCFMT_CENTER, rect.Width() / 13, 2);
    testList.InsertColumn(3, _T("上传时间"), LVCFMT_CENTER, rect.Width() / 13, 3);
    testList.InsertColumn(4, _T("上传人"), LVCFMT_CENTER, rect.Width() / 13, 4);
    testList.InsertColumn(5, _T("题目分值"), LVCFMT_CENTER, rect.Width() / 13, 5);
    testList.InsertColumn(6, _T("所属章节"), LVCFMT_CENTER, rect.Width() / 13, 6);
    testList.InsertColumn(7, _T("涉及知识点"), LVCFMT_CENTER, rect.Width() / 13, 7);
    testList.InsertColumn(8, _T("是否使用"), LVCFMT_CENTER, rect.Width() / 13, 8);
    testList.InsertColumn(9, _T("详解"), LVCFMT_CENTER, rect.Width() / 13, 9);
   testList.InsertColumn(10, _T("所属科目"), LVCFMT_CENTER, rect.Width() / 13, 10);
   testList.InsertColumn(11, _T("正确答案"), LVCFMT_CENTER, rect.Width() / 13, 11);
   testList.InsertColumn(12, _T("题目内容"), LVCFMT_CENTER, rect.Width() / 13, 12);

    mysql_query(&m_sqlConTestManager, "SET NAMES GB2312");
    CString query;
    query.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question;");
    //query.Format("select CourseID,CourseName,CourseType from tb_courseinfo");
    int ress = mysql_query(&m_sqlConTestManager, (char*)(LPCSTR)query);
    if (ress == 0) //检测查询成功
    {
        int i = 0, j = 1;
        resInputSingle = mysql_store_result(&m_sqlConTestManager);
        if (mysql_num_rows(resInputSingle) != 0)
        {
            rowInputSingle = mysql_fetch_row(resInputSingle);
            testList.InsertItem(i, _T(rowInputSingle[0]));
            testList.SetItemText(i, j++, _T(rowInputSingle[2]));
            testList.SetItemText(i, j++, _T(rowInputSingle[4]));
            testList.SetItemText(i, j++, _T(rowInputSingle[8]));
            testList.SetItemText(i, j++, _T(rowInputSingle[9]));
            testList.SetItemText(i, j++, _T(rowInputSingle[5]));

            testList.SetItemText(i, j++, _T(rowInputSingle[6]));
            testList.SetItemText(i, j++, _T(rowInputSingle[7]));
            testList.SetItemText(i, j++, _T(rowInputSingle[10]));
            testList.SetItemText(i, j++, _T(rowInputSingle[11]));
            testList.SetItemText(i, j++, _T(rowInputSingle[12]));

            testList.SetItemText(i, j++, _T(rowInputSingle[3]));
            testList.SetItemText(i, j++, _T(rowInputSingle[1]));
            i++;
            j = 1;
            while (resInputSingle->data_cursor)
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
                testList.InsertItem(i, _T(rowInputSingle[0]));
                testList.SetItemText(i, j++, _T(rowInputSingle[2]));
                testList.SetItemText(i, j++, _T(rowInputSingle[4]));
                testList.SetItemText(i, j++, _T(rowInputSingle[9]));
                testList.SetItemText(i, j++, _T(rowInputSingle[10]));
                testList.SetItemText(i, j++, _T(rowInputSingle[5]));

                testList.SetItemText(i, j++, _T(rowInputSingle[6]));
                testList.SetItemText(i, j++, _T(rowInputSingle[7]));
                j = 1;
            }
        }
        mysql_free_result(resInputSingle);
    }
    }
    // query.Format("select KPID,KPContent,ChapterID from TB_kownPoint where ChapterID = ")
    mysql_close(&m_sqlConTestManager);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CTestManager::OnBnClickedButton1()
{
    CDialogEx::OnOK();
    CManagerDlg manager;
    manager.DoModal();
    // TODO: 在此添加控件通知处理程序代码
}
