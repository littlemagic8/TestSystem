// CInputSingleTest.cpp: 实现文件
//

#include "stdafx.h"
#include "CInputSingleTest.h"
// CInputSingleTest 对话框

IMPLEMENT_DYNAMIC(CInputSingleTest, CDialogEx)

CInputSingleTest::CInputSingleTest(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_InputSingleTest, pParent)
{

}
class testInfoT
{
public:
    CString testid;
    CString testType;
    CString testDiff;
    CString update;
    CString updid;
    CString testscore;
    CString testChap;
    CString testKnow;
    CString testIsuse;
    CString testdetial;
    CString testCourse;
    CString testCont;
    CString testAns;
};
testInfoT testinfo;

CInputSingleTest::~CInputSingleTest()
{
}

void CInputSingleTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_InCourse, courseName);
    DDX_Control(pDX, IDC_courseNameInTest, courseNameInTest);
    DDX_Control(pDX, IDC_TestedList, m_testList);
    DDX_Control(pDX, IDC_courseNameI, courseNameI);
    DDX_Control(pDX, IDC_testTypeI, testTypeI);
    DDX_Control(pDX, IDC_testValueI, TestValueI);
    DDX_Control(pDX, IDC_QDiffI, QDiffI);
    DDX_Control(pDX, IDC_UpLoadI, UploadI);
    DDX_Control(pDX, IDC_QCententI, QCententI);
    DDX_Control(pDX, IDC_QAnswerI, QAnswerI);
    DDX_Control(pDX, IDC_QDetailI, QDetailI);
    DDX_Control(pDX, IDC_CHECK2, checkI1);
    DDX_Control(pDX, IDC_CHECK3, comboxChexk3);
    DDX_Control(pDX, IDC_CHECK4, comboxcheck4);
    DDX_Control(pDX, IDC_CHECK5, comboxcheck5);
    DDX_Control(pDX, IDC_CHECK7, comboxcheck7);
    DDX_Control(pDX, IDC_CHECK8, comboxcheck8);
    DDX_Control(pDX, IDC_CHECK9, comboxcheck9);
}


BEGIN_MESSAGE_MAP(CInputSingleTest, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_InCourse, &CInputSingleTest::OnTvnSelchangedIncourse)
    ON_NOTIFY(NM_CLICK, IDC_TestedList, &CInputSingleTest::OnNMClickTestedlist)
    ON_BN_CLICKED(IDC_CHECK2, &CInputSingleTest::OnBnClickedCheck2)
    ON_BN_CLICKED(TestSingleFind, &CInputSingleTest::OnBnClickedTestsinglefind)
    ON_BN_CLICKED(IDC_CHECK3, &CInputSingleTest::OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &CInputSingleTest::OnBnClickedCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &CInputSingleTest::OnBnClickedCheck5)
    ON_CBN_SELCHANGE(IDC_courseNameI, &CInputSingleTest::OnCbnSelchangecoursenamei)
    ON_NOTIFY(TVN_GETINFOTIP, IDC_InCourse, &CInputSingleTest::OnTvnGetInfoTipIncourse)
    ON_CBN_SELCHANGE(IDC_testTypeI, &CInputSingleTest::OnCbnSelchangetesttypei)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_TestedList, &CInputSingleTest::OnLvnItemchangedTestedlist)
    ON_BN_CLICKED(NextTest, &CInputSingleTest::OnBnClickedNexttest)
    ON_BN_CLICKED(uploadSingleTest, &CInputSingleTest::OnBnClickeduploadsingletest)
    ON_BN_CLICKED(exitInputTest, &CInputSingleTest::OnBnClickedexitinputtest)
    ON_BN_CLICKED(SaveEditTestSingle, &CInputSingleTest::OnBnClickedSaveedittestsingle)
    ON_BN_CLICKED(TestSingleDel, &CInputSingleTest::OnBnClickedTestsingledel)
    ON_BN_CLICKED(ViewOtherTest, &CInputSingleTest::OnBnClickedViewothertest)
END_MESSAGE_MAP()


// CInputSingleTest 消息处理程序


void CInputSingleTest::OnTvnSelchangedIncourse(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
    CString strText; // 树节点的标签文本字符串   
    // 获取当前选中节点的句柄   
    HTREEITEM hItem = courseName.GetSelectedItem();
    // 获取选中节点的标签文本字符串   
    strText = courseName.GetItemText(hItem);
    // 将字符串显示到编辑框中   
    SetDlgItemText(IDC_courseNameInTest, strText);
	*pResult = 0;
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConInputSingle);
    if (!mysql_real_connect(&m_sqlConInputSingle, "localhost", "root",
        "", "exam", 3306, NULL, 0))
    {
        AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
        return ;
    }
    CString query3;
    mysql_query(&m_sqlConInputSingle, "SET NAMES GB2312");
    query3.Format("select CourseName, CourseID, CourseType from tb_courseinfo where CourseName =  \'%s\'",(CString)strText);
    int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    if (ress == 0)
    {
        resInputSingle = mysql_store_result(&m_sqlConInputSingle);
        if (mysql_num_rows(resInputSingle) != 0) //查询结果为空
        {
            rowInputSingle = mysql_fetch_row(resInputSingle);
            courseID_combox = rowInputSingle[1];
            mysql_free_result(resInputSingle);
        }
    }
    query3.Format("select ChapterID,ChapterName from tb_chapterinfo where CourseID = " + _T(courseID_combox));
    //  query3 = "select ChapterID,ChapterName from tb_chapterinfo where CourseID = "+
    ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    if (ress == 0)
    {
        resInputSingle = mysql_store_result(&m_sqlConInputSingle);
        if (mysql_num_rows(resInputSingle) == 0) //查询结果为空
        {
            AfxMessageBox("请维护该科目章节信息！");
            courseNameI.ResetContent();
        }
        else
        {

            rowInputSingle = mysql_fetch_row(resInputSingle);
            ChapterID_combox = rowInputSingle[0];
            courseNameI.AddString(rowInputSingle[1]);
             
            while (resInputSingle->data_cursor)
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
                courseNameI.AddString(rowInputSingle[1]);
            }
            courseNameI.SetCurSel(0);
            mysql_free_result(resInputSingle);
        }
    }
    mysql_close(&m_sqlConInputSingle);
}


BOOL CInputSingleTest::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    courseName.DeleteAllItems();
    m_testList.DeleteAllItems();
    KPContent = "";
    HTREEITEM hRoot;     // 树的根节点的句柄   
    HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
    HTREEITEM hArtItem;  // 可表示任一文章节点的句柄 
    // TODO:  在此添加额外的初始化
    // 插入根节点   
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConInputSingle);
    hRoot = courseName.InsertItem(_T("课程列表"), 0, 0);
    if (!mysql_real_connect(&m_sqlConInputSingle, "localhost", "root",
        "", "exam", 3306, NULL, 0))
    {
        AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
        return FALSE;
    }
    else//连接成功则继续访问数据库
    {
        //AfxMessageBox(_T("数据库连接成功!"));
        UpdateData(true);
        CString query;
        CString query2;
        CString query3;
        mysql_query(&m_sqlConInputSingle, "SET NAMES GB2312");
        query.Format("select DISTINCT CourseType from tb_courseinfo");
       // query3.Format("select CourseID,CourseName,CourseType from tb_courseinfo");
        int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query);
        if (ress == 0) //检测查询成功
        {
            resInputSingle = mysql_store_result(&m_sqlConInputSingle);
            if (mysql_num_rows(resInputSingle) == 0) //查询结果为空
            {
                AfxMessageBox("请维护试题相关科目信息！");
            }
            else
            {

                // rowInputSingle = mysql_next_result(&m_sqlConInputSingle);
                int i = 1;
                int j = 2;
                int k = 1;
                
                rowInputSingle = mysql_fetch_row(resInputSingle);
                //courseID_combox = rowInputSingle[1];
                hCataItem = courseName.InsertItem(_T(rowInputSingle[0]), i, i++, hRoot, TVI_LAST);
              //  courseName.SetItemData(hCataItem, k++);
                // 节点添加附加的编号数据，在鼠标划过该节点时显示   
                //courseName.SetItemData(hCataItem, (DWORD_PTR)rowInputSingle[1]);
                query2.Format("select courseName from tb_courseinfo where CourseType = \'%s\'", (CString)rowInputSingle[0]);
                int ress1 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query2);
                if (ress1 == 0)
                {
                    resInputSingle1 = mysql_store_result(&m_sqlConInputSingle);
                    if (mysql_num_rows(resInputSingle1) != 0) 
                    {
                        rowInputSingle1 = mysql_fetch_row(resInputSingle1);

                        hArtItem = courseName.InsertItem(_T(rowInputSingle1[0]), j, j, hCataItem, TVI_LAST);
                        courseName.SetItemData(hArtItem, k++);
                    }
                    while (resInputSingle1->data_cursor)
                    {
                        rowInputSingle1 = mysql_fetch_row(resInputSingle1);
                        hArtItem = courseName.InsertItem(_T(rowInputSingle1[0]), j, j, hCataItem, TVI_LAST);
                        courseName.SetItemData(hArtItem, k++);
                    }
                }

                while (resInputSingle->data_cursor)
                {
                    // j++;
                    rowInputSingle = mysql_fetch_row(resInputSingle);
                    hCataItem = courseName.InsertItem(_T(rowInputSingle[0]), i, i++, hRoot, TVI_LAST);
                    courseName.SetItemData(hCataItem, k++);
                    query2.Format("select courseName from tb_courseinfo where CourseType = \'%s\'", (CString)rowInputSingle[0]);
                    int ress1 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query2);
                    if (ress1 == 0)
                    {
                        resInputSingle1 = mysql_store_result(&m_sqlConInputSingle);
                        if (mysql_num_rows(resInputSingle1) != 0) //查询结果为空
                        {
                            rowInputSingle1 = mysql_fetch_row(resInputSingle1);
                            hArtItem = courseName.InsertItem(_T(rowInputSingle1[0]), j, j, hCataItem, TVI_LAST);
                            courseName.SetItemData(hArtItem, k++);
                        }
                        while (resInputSingle1->data_cursor)
                        {
                            rowInputSingle1 = mysql_fetch_row(resInputSingle1);
                            hArtItem = courseName.InsertItem(_T(rowInputSingle1[0]), j, j, hCataItem, TVI_LAST);
                            courseName.SetItemData(hArtItem, k++);
                        }
                    }
                }

                //role = "学生";
                mysql_free_result(resInputSingle);
                //   mysql_close(&m_sqlConInputSingle);

            }
            UpdateData(true);
        }
    }
    CString query3;
    //难度系数
    for (int i = 1;i < 5;i++)
    {
        QDiffI.AddString(_T((LPCSTR)i));
    }
    QDiffI.SetCurSel(0);
    //题目类型
    query3.Format("select DISTINCT type from question");
    //  query3 = "select ChapterID,ChapterName from tb_chapterinfo where CourseID = "+
    int ress3 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    if (ress3 == 0)
    {
        resInputSingle = mysql_store_result(&m_sqlConInputSingle);
        if (mysql_num_rows(resInputSingle) == 0) //查询结果为空
        {
            AfxMessageBox("请维护该试题类型！");
        }
        else
        {

            rowInputSingle = mysql_fetch_row(resInputSingle);
            switch(atoi(rowInputSingle[0]))
            {
               case 0:
                   testTypeI.AddString("判断题");
                   break;
               case 1:
                   testTypeI.AddString("单选题");
                   break;
               case 2:
                   testTypeI.AddString("多选题");
                   break;
               case 3:
                   testTypeI.AddString("简答题");
                   break;
            }
               
                    
          //   testTypeI.AddString(rowInputSingle[0]);
            while (resInputSingle->data_cursor)
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
                switch (atoi(rowInputSingle[0]))
                {
                case 0:
                    testTypeI.AddString("判断题");
                    break;
                case 1:
                    testTypeI.AddString("单选题");
                    break;
                case 2:
                    testTypeI.AddString("多选题");
                    break;
                case 3:
                    testTypeI.AddString("简答题");
                    break;
                }
               // testTypeI.AddString(rowInputSingle[0]);
            }
            testTypeI.SetCurSel(0);
            mysql_free_result(resInputSingle);
        }
    }

    CRect rect;

        // 获取编程语言列表视图控件的位置和大小   
        m_testList.GetClientRect(&rect);

        // 为列表视图控件添加全行选中和栅格风格   
        m_testList.SetExtendedStyle(m_testList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

        // 为列表视图控件添加8列   
        m_testList.InsertColumn(0, _T("题目编号"), LVCFMT_CENTER, rect.Width() / 13, 0);
        m_testList.InsertColumn(2, _T("题目类型"), LVCFMT_CENTER, rect.Width() / 13, 2);
        m_testList.InsertColumn(4, _T("难度"), LVCFMT_CENTER, rect.Width() / 13, 4);
        m_testList.InsertColumn(9, _T("上传时间"), LVCFMT_CENTER, rect.Width() / 13, 9);
        m_testList.InsertColumn(8, _T("上传人"), LVCFMT_CENTER, rect.Width() / 13, 8);
        m_testList.InsertColumn(5, _T("题目分值"), LVCFMT_CENTER, rect.Width() / 13, 5);
        m_testList.InsertColumn(12, _T("所属章节"), LVCFMT_CENTER, rect.Width() / 13, 12);
        m_testList.InsertColumn(7, _T("涉及知识点"), LVCFMT_CENTER, rect.Width() / 13, 7);
        m_testList.InsertColumn(10, _T("是否使用"), LVCFMT_CENTER, rect.Width() / 13, 10);
        m_testList.InsertColumn(11, _T("详解"), LVCFMT_CENTER, rect.Width() / 13, 11);
        m_testList.InsertColumn(10, _T("所属科目"), LVCFMT_CENTER, rect.Width() / 13, 10);
        m_testList.InsertColumn(3, _T("正确答案"), LVCFMT_CENTER, rect.Width() / 13, 3);
        m_testList.InsertColumn(1, _T("题目内容"), LVCFMT_CENTER, rect.Width() / 13, 1);

        mysql_query(&m_sqlConInputSingle, "SET NAMES GB2312");
        CString query;
        
        query.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question where QUploadID=%s;", this->curUserId);
        //query.Format("select CourseID,CourseName,CourseType from tb_courseinfo");
        int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query);
        if (ress == 0) //检测查询成功
        {
            int i = 0, j = 1;
            resInputSingle = mysql_store_result(&m_sqlConInputSingle);
            if (mysql_num_rows(resInputSingle) != 0)
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
                m_testList.InsertItem(i, _T(rowInputSingle[0]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[1]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[2]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[3]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[4]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[5]));

                m_testList.SetItemText(i, j++, _T(rowInputSingle[6]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[7]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[8]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[9]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[10]));

                m_testList.SetItemText(i, j++, _T(rowInputSingle[11]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[12]));
                i++;
                j = 1;
                while (resInputSingle->data_cursor)
                {
                    rowInputSingle = mysql_fetch_row(resInputSingle);
                    m_testList.InsertItem(i, _T(rowInputSingle[0]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[1]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[2]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[3]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[4]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[5]));

                    m_testList.SetItemText(i, j++, _T(rowInputSingle[6]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[7]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[8]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[9]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[10]));

                    m_testList.SetItemText(i, j++, _T(rowInputSingle[11]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[12]));
                    j = 1;
                    i++;
                    //if (i >= 13)i = 0;
                }
            }
            mysql_free_result(resInputSingle);
        }
        // query.Format("select KPID,KPContent,ChapterID from TB_kownPoint where ChapterID = ")
        mysql_close(&m_sqlConInputSingle);
          // return TRUE  unless you set the focus to a control   
    
    return TRUE;
}



void CInputSingleTest::OnNMClickTestedlist(NMHDR* pNMHDR, LRESULT* pResult)
{
        LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
        // TODO: 在此添加控件通知处理程序代码
        *pResult = 0;
        CString strLangName;    // 选择语言的名称字符串   
        NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
        strLangName = m_testList.GetItemText(pNMListView->iItem, 12);
        MYSQL m_sqlConInputSingle;
        MYSQL_RES* resInputSingle;
        MYSQL_RES* resInputSingle1;
        MYSQL_ROW rowInputSingle;
        MYSQL_ROW rowInputSingle1;
        mysql_init(&m_sqlConInputSingle);
        if (!mysql_real_connect(&m_sqlConInputSingle, "localhost", "root",
            "", "exam", 3306, NULL, 0))
        {
            AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
            return;
        }
        CString query3;
        mysql_query(&m_sqlConInputSingle, "SET NAMES GB2312");
        query3.Format("select CourseName, CourseID, CourseType from tb_courseinfo where CourseID = %s", (CString)strLangName);
        int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
        if (ress == 0)
        {
            resInputSingle = mysql_store_result(&m_sqlConInputSingle);
            if (mysql_num_rows(resInputSingle) != 0) //查询结果为空
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
                strLangName = rowInputSingle[0];
                mysql_free_result(resInputSingle);
            }
            else
            {
                strLangName = "";
            }
        }
        SetDlgItemText(IDC_courseNameInTest, strLangName);
 /*       QID, QContent, QType, QRightAnswer, QDifficulty, 
            QScore, QChapterID, QKnowPoint, QUploadID, QUpTime, QUse, QDetailed, QCourseID*/
        strLangName = m_testList.GetItemText(pNMListView->iItem, 7);        
        SetDlgItemText(IDC_courseNameI, strLangName);
        strLangName = m_testList.GetItemText(pNMListView->iItem, 2);
        //课程  
        SetDlgItemText(IDC_testTypeI, strLangName);
        strLangName = m_testList.GetItemText(pNMListView->iItem, 5);
        SetDlgItemText(IDC_testValueI, strLangName);
        strLangName = m_testList.GetItemText(pNMListView->iItem, 4);
        SetDlgItemText(IDC_QDiffI, strLangName);
        strLangName = m_testList.GetItemText(pNMListView->iItem, 8);
        SetDlgItemText(IDC_UpLoadI, strLangName);
        strLangName = m_testList.GetItemText(pNMListView->iItem, 1);
        SetDlgItemText(IDC_QCententI, strLangName);
        strLangName = m_testList.GetItemText(pNMListView->iItem, 3);
        SetDlgItemText(IDC_QAnswerI, strLangName);
        strLangName = m_testList.GetItemText(pNMListView->iItem, 11);
        // 将选择的语言显示与编辑框中   
        SetDlgItemText(IDC_QDetailI, strLangName);

}


void CInputSingleTest::OnBnClickedCheck2()
{
    CButton* but = (CButton*)GetDlgItem(IDC_CHECK2);
    CString text_B;
        if (but->GetCheck() == 1)
        {
            but->GetWindowTextA(text_B);
        }
        KPContent += text_B + ",";
        SetDlgItemText(IDC_courseNameI, KPContent);
    
    // TODO: 在此添加控件通知处理程序代码
}


void CInputSingleTest::OnBnClickedTestsinglefind()
{
    // TODO: 在此添加控件通知处理程序代码

}


void CInputSingleTest::OnBnClickedCheck3()
{
    CButton* but = (CButton*)GetDlgItem(IDC_CHECK3);
    CString text_B;
    if (but->GetCheck() == 1)
    {
        but->GetWindowTextA(text_B);
    }
    KPContent += text_B + ",";
    SetDlgItemText(IDC_courseNameI, KPContent);
    // TODO: 在此添加控件通知处理程序代码
}


void CInputSingleTest::OnBnClickedCheck4()
{
    // TODO: 在此添加控件通知处理程序代码
    CButton* but = (CButton*)GetDlgItem(IDC_CHECK4);
    CString text_B;
    if (but->GetCheck() == 1)
    {
        but->GetWindowTextA(text_B);
    }
    KPContent += text_B + ",";
    SetDlgItemText(IDC_courseNameI, KPContent);
}


void CInputSingleTest::OnBnClickedCheck5()
{
    CButton* but = (CButton*)GetDlgItem(IDC_CHECK5);
    CString text_B;
    if (but->GetCheck() == 1)
    {
        but->GetWindowTextA(text_B);
    }
    KPContent += text_B + ",";
    SetDlgItemText(IDC_courseNameI, KPContent);
    // TODO: 在此添加控件通知处理程序代码
}
void CInputSingleTest::OnBnClickedCheck7()
{
    CButton* but = (CButton*)GetDlgItem(IDC_CHECK7);
    CString text_B;
    if (but->GetCheck() == 1)
    {
        but->GetWindowTextA(text_B);
    }
    KPContent += text_B + ",";
    SetDlgItemText(IDC_courseNameI, KPContent);
    // TODO: 在此添加控件通知处理程序代码
}
void CInputSingleTest::OnBnClickedCheck8()
{
    CButton* but = (CButton*)GetDlgItem(IDC_CHECK8);
    CString text_B;
    if (but->GetCheck() == 1)
    {
        but->GetWindowTextA(text_B);
    }
    KPContent += text_B + ",";
    SetDlgItemText(IDC_courseNameI, KPContent);
    // TODO: 在此添加控件通知处理程序代码
}
void CInputSingleTest::OnBnClickedCheck9()
{
    CButton* but = (CButton*)GetDlgItem(IDC_CHECK9);
    CString text_B;
    if (but->GetCheck() == 1)
    {
        but->GetWindowTextA(text_B);
    }
    KPContent += text_B + ",";
    SetDlgItemText(IDC_courseNameI, KPContent);
    // TODO: 在此添加控件通知处理程序代码
}

void CInputSingleTest::OnCbnSelchangecoursenamei()
{
    // TODO: 在此添加控件通知处理程序代码
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConInputSingle);
    if (!mysql_real_connect(&m_sqlConInputSingle, "localhost", "root",
        "", "exam", 3306, NULL, 0))
    {
        AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
        return ;
    }
    else//连接成功则继续访问数据库
    {
        //AfxMessageBox(_T("数据库连接成功!"));
        UpdateData(false);
        CString query;
        mysql_query(&m_sqlConInputSingle, "SET NAMES GB2312");
        query.Format("select KPID,KPContent from TB_knowPoint where ChapterID = "+ ChapterID_combox);
        //query.Format("select CourseID,CourseName,CourseType from tb_courseinfo");
        int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query);
        if (ress == 0) //检测查询成功
        {
            int i = 1;
            resInputSingle = mysql_store_result(&m_sqlConInputSingle);
            if (mysql_num_rows(resInputSingle) != 0) //查询结果为空
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
                checkI1.SetWindowText(_T(rowInputSingle[1]));
                
                while (resInputSingle->data_cursor)
                {
                    rowInputSingle = mysql_fetch_row(resInputSingle);
                    switch (i)
                    {
                        case 1:comboxChexk3.SetWindowText(_T(rowInputSingle[1]));break;
                        case 2:comboxcheck4.SetWindowText(_T(rowInputSingle[1]));break;
                        case 3:comboxcheck5.SetWindowText(_T(rowInputSingle[1]));break;
                        case 4:comboxcheck7.SetWindowText(_T(rowInputSingle[1]));break;
                        case 5:comboxcheck8.SetWindowText(_T(rowInputSingle[1]));break;
                        case 6:comboxcheck9.SetWindowText(_T(rowInputSingle[1]));break;
                    }
                    i++;
                }
            }
            
            mysql_free_result(resInputSingle);
            //   mysql_close(&m_sqlConInputSingle);
        }

    }
}


void CInputSingleTest::OnTvnGetInfoTipIncourse(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMTVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMTVGETINFOTIP>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
    NMTVGETINFOTIP* pTVTipInfo = (NMTVGETINFOTIP*)pNMHDR;   // 将传入的pNMHDR转换为NMTVGETINFOTIP指针类型   
    HTREEITEM hRoot = courseName.GetRootItem();      // 获取树的根节点   
    CString strText;     // 每个树节点的提示信息   

    if (pTVTipInfo->hItem == hRoot)
    {
        // 如果鼠标划过的节点是根节点，则提示信息为空   
        strText = _T("");
    }
    else
    {
        // 如果鼠标划过的节点不是根节点，则将该节点的附加32位数据格式化为字符串   
        strText.Format(_T("%d"), pTVTipInfo->lParam);
    }
    courseID_combox = strText;
    // 将strText字符串拷贝到pTVTipInfo结构体变量的pszText成员中，这样就能显示内容为strText的提示信息   
    //wcscpy(pTVTipInfo->pszText, (wchar_t)strText);
}


void CInputSingleTest::OnCbnSelchangetesttypei()
{
    // TODO: 在此添加控件通知处理程序代码
}


void CInputSingleTest::OnLvnItemchangedTestedlist(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
    NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
    if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
    {
        strinputTest = m_testList.GetItemText(pNMListView->iItem, 0);
    }
}


void CInputSingleTest::OnBnClickedNexttest()
{
    // TODO: 在此添加控件通知处理程序代码
    //OnInitDialog();
    SetDlgItemText(IDC_courseNameI, "");
   
    SetDlgItemText(IDC_TestedList, "");
  
    SetDlgItemText(IDC_testTypeI, "");
    
    SetDlgItemText(IDC_testValueI, "");

    SetDlgItemText(IDC_QDiffI, "");
   
    SetDlgItemText(IDC_UpLoadI, "");
     
    SetDlgItemText(IDC_QCententI, "");
    
    SetDlgItemText(IDC_QAnswerI, "");
      
    SetDlgItemText(IDC_QDetailI, "");
}


void CInputSingleTest::OnBnClickeduploadsingletest()
{
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConInputSingle);
    if (!mysql_real_connect(&m_sqlConInputSingle, "localhost", "root",
        "", "exam", 3306, NULL, 0))
    {
        AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
        return ;
    }
    // TODO: 在此添加控件通知处理程序代码
    CString query3;
    UpdateData(false);
    CString strLangName1;
    // 将选择的语言显示与编辑框中   
    GetDlgItemText(IDC_courseNameI, strLangName1);
    strLangName1 = "test";    
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 1);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_testTypeI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 5);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_testValueI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 2);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QDiffI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 4);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_UpLoadI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 12);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QCententI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 11);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QAnswerI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 9);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QDetailI, strLangName);
    CString strtime;
    CTime tm;
    tm = CTime::GetCurrentTime();
    strtime = tm.Format("%Y%m%d");
    if (courseID_combox == "" || ChapterID_combox == "")
    {
        AfxMessageBox("请配置章节和科目信息");
    }
    GetDlgItemText(IDC_QCententI, testinfo.testCont);
    GetDlgItemText(IDC_QAnswerI, testinfo.testAns);
    GetDlgItemText(IDC_QDiffI, testinfo.testDiff);
    GetDlgItemText(IDC_QDetailI, testinfo.testdetial);
    GetDlgItemText(IDC_testValueI, testinfo.testscore);
    GetDlgItemText(IDC_testTypeI, testinfo.testType);
    if (testinfo.testCont == "" || testinfo.testAns == "")
    {
        AfxMessageBox("请填写题目和答案");
    }
    //章节ID
  //  GetDlgItemText(IDC_courseNameI, testinfo.testChap);
    query3.Format("insert into tb_question(QContent,QRightAnswer,QDifficulty,QDetailed,QScore,QType,QChapterID, QUploadID, QKnowPoint,QUpTime,QCourseID,QUse)values('"+ testinfo.testCont+"', '"+ testinfo.testAns +"',"+ testinfo.testDiff+",'"+ testinfo.testdetial+ "',"+testinfo.testscore+",'"+ testinfo.testType+"'," + ChapterID_combox +"," + this->curUserId+",'"+"知识点" + "','"+ strtime+"',"+ courseID_combox+",1"+")");
    // query3.Format("insert into tb_question(QContent,QRightAnswer,QType,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed)"+ 
    //   " values (\'%s\',\'%s\',\'%s\',1,3,\'%s\',2,\'%s\',\'%s\',\'%s\')", strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1);
    ////  query3 = "select ChapterID,ChapterName from tb_chapterinfo where CourseID = "+
    int ress3 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    if (ress3==0)
    {

        AfxMessageBox("添加成功");
        OnInitDialog();
        //mysql_free_result(resInputSingle);
       
    }
    else
    {
        AfxMessageBox("添加失败");
    }
    mysql_close(&m_sqlConInputSingle);
}


void CInputSingleTest::OnBnClickedexitinputtest()
{
    // TODO: 在此添加控件通知处理程序代码
    CDialog::OnOK();
    CTeacherDlg  exitinputTest;
    exitinputTest.curUserName = (_T(this->curUserName));
    exitinputTest.curUserId = (_T(this->curUserId));
    exitinputTest.DoModal();
}


void CInputSingleTest::OnBnClickedSaveedittestsingle()
{
    // TODO: 在此添加控件通知处理程序代码
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConInputSingle);
    if (!mysql_real_connect(&m_sqlConInputSingle, "localhost", "root",
        "", "exam", 3306, NULL, 0))
    {
        AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
        return;
    }
    // TODO: 在此添加控件通知处理程序代码
    CString query3;
    UpdateData(false);
    CString strLangName1;
    // 将选择的语言显示与编辑框中   
    GetDlgItemText(IDC_courseNameI, strLangName1);
    strLangName1 = "test";
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 6);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_TestedList, strLangName);

    //strLangName = m_testList.GetItemText(pNMListView->iItem, 1);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_testTypeI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 5);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_testValueI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 2);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QDiffI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 4);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_UpLoadI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 12);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QCententI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 11);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QAnswerI, strLangName);
    //strLangName = m_testList.GetItemText(pNMListView->iItem, 9);
    //// 将选择的语言显示与编辑框中   
    //SetDlgItemText(IDC_QDetailI, strLangName);
    CString strtime;
    CTime tm;
    tm = CTime::GetCurrentTime();
    strtime = tm.Format("%Y%m%d%X");
    if (courseID_combox == "" || ChapterID_combox == "")
    {
        AfxMessageBox("请配置章节和科目信息");
    }
    if (testinfo.testCont == "" || testinfo.testAns == "")
    {
        AfxMessageBox("请填写题目和答案");
    }
    query3.Format("update tb_question set QContent = '" + strLangName1 + "', QRightAnswer='"+ strLangName1 + "',QDifficulty='"+ strLangName1 + "',QDetailed='"+ strLangName1+"',QScore='"+ strLangName1 + "',QType='"+ strLangName1 + "',QChapterID='"+ strLangName1 + "', QUploadID='"+ strLangName1 + "', QKnowPoint='"+ strLangName1 + "',QUpTime='"+ strLangName1 +"'");
    // query3.Format("insert into tb_question(QContent,QRightAnswer,QType,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed)"+ 
    //   " values (\'%s\',\'%s\',\'%s\',1,3,\'%s\',2,\'%s\',\'%s\',\'%s\')", strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1, strLangName1);
    ////  query3 = "select ChapterID,ChapterName from tb_chapterinfo where CourseID = "+
    int ress3 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    if (ress3 == 0)
    {
        OnInitDialog();
        AfxMessageBox("修改成功");
       
        //mysql_free_result(resInputSingle);

    }
    mysql_close(&m_sqlConInputSingle);
}


void CInputSingleTest::OnBnClickedTestsingledel()
{

    AfxMessageBox("将删除列表框中选中的行");
    if (strinputTest == "")
    {
        AfxMessageBox(_T("请选中一行数据进行删除"));
    }
    else
    {
        MYSQL m_sqlConMS;
        MYSQL_RES* res;
        MYSQL_ROW  row;
        CString sql, sql1;
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
            sql.Format("DElETE FROM tb_question WHERE QID=%s", strinputTest);
            int ress = mysql_query(&m_sqlConMS, (char*)(LPCSTR)sql);

            if (ress == 0)
            {
                AfxMessageBox(_T("删除成功!"));
                res = mysql_store_result(&m_sqlConMS);
                mysql_close(&m_sqlConMS);//关闭Mysql连接
            }
        }
        strinputTest = "";
    }
    OnInitDialog();
      //CDialog::OnOK();
}


void CInputSingleTest::OnBnClickedViewothertest()
{
   // OnInitDialog();
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConInputSingle);
    if (!mysql_real_connect(&m_sqlConInputSingle, "localhost", "root",
        "", "exam", 3306, NULL, 0))
    {
        AfxMessageBox(_T("数据库连接失败!请检查你的数据库是否打开"));
        return;
    }
    else
    {
        mysql_query(&m_sqlConInputSingle, "SET NAMES GB2312");
        CString query;
        query.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question;");
        //query.Format("select CourseID,CourseName,CourseType from tb_courseinfo");
        int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query);
        if (ress == 0) //检测查询成功
        {
            int i = 0, j = 1;
            resInputSingle = mysql_store_result(&m_sqlConInputSingle);
            if (mysql_num_rows(resInputSingle) != 0)
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
                m_testList.InsertItem(i, _T(rowInputSingle[0]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[1]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[2]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[3]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[4]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[5]));

                m_testList.SetItemText(i, j++, _T(rowInputSingle[6]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[7]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[8]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[9]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[10]));

                m_testList.SetItemText(i, j++, _T(rowInputSingle[11]));
                m_testList.SetItemText(i, j++, _T(rowInputSingle[12]));
                i++;
                j = 1;
                while (resInputSingle->data_cursor)
                {
                    rowInputSingle = mysql_fetch_row(resInputSingle);
                    m_testList.InsertItem(i, _T(rowInputSingle[0]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[1]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[2]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[3]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[4]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[5]));

                    m_testList.SetItemText(i, j++, _T(rowInputSingle[6]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[7]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[8]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[9]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[10]));

                    m_testList.SetItemText(i, j++, _T(rowInputSingle[11]));
                    m_testList.SetItemText(i, j++, _T(rowInputSingle[12]));
                    j = 1;
                    i++;
                    //if (i >= 13)i = 0;
                }
            }
            mysql_free_result(resInputSingle);
        }
        // query.Format("select KPID,KPContent,ChapterID from TB_kownPoint where ChapterID = ")
        mysql_close(&m_sqlConInputSingle);
    }
}
