// COnlineTest.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "COnlineTest.h"
#include "afxdialogex.h"


// COnlineTest 对话框

IMPLEMENT_DYNAMIC(COnlineTest, CDialogEx)

COnlineTest::COnlineTest(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OnlineTest, pParent)
{

}

COnlineTest::~COnlineTest()
{
}

void COnlineTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TestTree, m_TestTree);
    DDX_Control(pDX, IDC_TestNum, m_testNum);
    DDX_Control(pDX, IDC_EDIT2, m_testInfo);
    DDX_Control(pDX, IDC_EDIT3, m_answerinfo);
    DDX_Control(pDX, IDC_EDIT7, m_detailinfo);
}


BEGIN_MESSAGE_MAP(COnlineTest, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &COnlineTest::OnBnClickedCancel)
	ON_BN_CLICKED(2, &COnlineTest::OnBnClicked2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TestList, &COnlineTest::OnTvnSelchangedTestlist)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TestTree, &COnlineTest::OnTvnSelchangedTesttree)
    ON_BN_CLICKED(IDC_BUTTON3, &COnlineTest::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON5, &COnlineTest::OnBnClickedButton5)
END_MESSAGE_MAP()


// COnlineTest 消息处理程序

//退出题目自测界面，回到学生登录界面
void COnlineTest::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	CStudentDlg  stuDlg;
	stuDlg.DoModal();
	CDialogEx::OnCancel();
}


void COnlineTest::OnBnClicked2()
{
	CDialog::OnOK();
	CStudentDlg  stulog;
	stulog.curUserName = (_T(this->studentOnlineNamedlg));
	stulog.curUserId = (_T(this->studentOnlineId));/**/
	stulog.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


BOOL COnlineTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//curUserEdit.SetWindowTextA(_T(this->curUserName));
	// TODO:  在此添加额外的初始化
    m_TestTree.DeleteAllItems();
    //m_testList.DeleteAllItems();
   // KPContent = "";
    HTREEITEM hRoot;     // 树的根节点的句柄   
    HTREEITEM hCataItem=NULL; // 可表示任一分类节点的句柄   
    HTREEITEM hArtItem;  // 可表示任一文章节点的句柄 
    // TODO:  在此添加额外的初始化
    // 插入根节点   
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1;
    MYSQL_ROW rowInputSingle;
    MYSQL_ROW rowInputSingle1;
    mysql_init(&m_sqlConInputSingle);
    hRoot = m_TestTree.InsertItem(_T("题目列表"), 0, 0);
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
        query.Format("select DISTINCT type from question");
        // query3.Format("select CourseID,m_TestTree,CourseType from tb_courseinfo");
        int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query);
        if (ress == 0) //检测查询成功
        {
            resInputSingle = mysql_store_result(&m_sqlConInputSingle);
            if (mysql_num_rows(resInputSingle) == 0) //查询结果为空
            {
                AfxMessageBox("请维护试题相关类型！");
            }
            else
            {

                // rowInputSingle = mysql_next_result(&m_sqlConInputSingle);
                int i = 1;
                int j = 2;
                int k = 1;

                rowInputSingle = mysql_fetch_row(resInputSingle);
                CString testType = "";
                switch (atoi(rowInputSingle[0]))
                {
                case 0:
                    hCataItem = m_TestTree.InsertItem(_T("判断题"), i, i++, hRoot, TVI_LAST);
                    testType = "判断题";
                    break;
                case 1:
                    hCataItem = m_TestTree.InsertItem(_T("单选题"), i, i++, hRoot, TVI_LAST);
                    testType = "单选题";
                    break;
                case 2:
                    hCataItem = m_TestTree.InsertItem(_T("多选题"), i, i++, hRoot, TVI_LAST);
                    testType = "多选题";
                    break;
                case 3:
                    hCataItem = m_TestTree.InsertItem(_T("简答题"), i, i++, hRoot, TVI_LAST);
                    testType = "简答题";
                    break;
                }
                //courseID_combox = rowInputSingle[1];
               // hCataItem = m_TestTree.InsertItem(_T(rowInputSingle[0]), i, i++, hRoot, TVI_LAST);
                //  m_TestTree.SetItemData(hCataItem, k++);
                  // 节点添加附加的编号数据，在鼠标划过该节点时显示   
                  //m_TestTree.SetItemData(hCataItem, (DWORD_PTR)rowInputSingle[1]);
                query2.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question where QType like \'%s\'", testType); 
                int ress1 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query2);
                if (ress1 == 0)
                {
                    resInputSingle1 = mysql_store_result(&m_sqlConInputSingle);
                    if (mysql_num_rows(resInputSingle1) != 0) //查询结果为空
                    {
                        rowInputSingle1 = mysql_fetch_row(resInputSingle1);

                        hArtItem = m_TestTree.InsertItem(_T(rowInputSingle1[1]), j, j, hCataItem, TVI_LAST);
                        m_TestTree.SetItemData(hArtItem, k++);
                    
                        while (resInputSingle1->data_cursor)
                        {
                            rowInputSingle1 = mysql_fetch_row(resInputSingle1);
                            hArtItem = m_TestTree.InsertItem(_T(rowInputSingle1[1]), j, j, hCataItem, TVI_LAST);
                            m_TestTree.SetItemData(hArtItem, k++);
                        }
                    }
                }

                while (resInputSingle->data_cursor)
                {
                    switch (atoi(rowInputSingle[0]))
                    {
                    case 0:
                        hCataItem = m_TestTree.InsertItem(_T("判断题"), i, i++, hRoot, TVI_LAST);
                        testType = "判断题";
                        break;
                    case 1:
                        hCataItem = m_TestTree.InsertItem(_T("单选题"), i, i++, hRoot, TVI_LAST);
                        testType = "单选题";
                        break;
                    case 2:
                        hCataItem = m_TestTree.InsertItem(_T("多选题"), i, i++, hRoot, TVI_LAST);
                        testType = "多选题";
                        break;
                    case 3:
                        hCataItem = m_TestTree.InsertItem(_T("简答题"), i, i++, hRoot, TVI_LAST);
                        testType = "简答题";
                        break;
                    }
                    rowInputSingle = mysql_fetch_row(resInputSingle);
                   // hCataItem = m_TestTree.InsertItem(_T(rowInputSingle[0]), i, i++, hRoot, TVI_LAST);
                    m_TestTree.SetItemData(hCataItem, k++);
                    query2.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question where QType like \'%s\';", testType);
                    int ress1 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query2);
                    if (ress1 == 0)
                    {
                        resInputSingle1 = mysql_store_result(&m_sqlConInputSingle);
                        if (mysql_num_rows(resInputSingle1) != 0) //查询结果为空
                        {
                            rowInputSingle1 = mysql_fetch_row(resInputSingle1);
                            hArtItem = m_TestTree.InsertItem(_T(rowInputSingle1[1]), j, j, hCataItem, TVI_LAST);
                            m_TestTree.SetItemData(hArtItem, k++);
                        
                            while (resInputSingle1->data_cursor)
                            {
                                rowInputSingle1 = mysql_fetch_row(resInputSingle1);
                                hArtItem = m_TestTree.InsertItem(_T(rowInputSingle1[1]), j, j, hCataItem, TVI_LAST);
                                m_TestTree.SetItemData(hArtItem, k++);
                            }
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
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void COnlineTest::OnTvnSelchangedTestlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
    CString strText; // 树节点的标签文本字符串   
    // 获取当前选中节点的句柄   
    HTREEITEM hItem = m_TestTree.GetSelectedItem();
    // 获取选中节点的标签文本字符串   
    strText = m_TestTree.GetItemText(hItem);
    // 将字符串显示到编辑框中   
    SetDlgItemText(IDC_TestNum, strText);
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
    query3.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question where QContent like \'%s\'", strText);
    int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    if (ress == 0)
    {
        resInputSingle = mysql_store_result(&m_sqlConInputSingle);
        if (mysql_num_rows(resInputSingle) != 0) //查询结果为空
        {
            rowInputSingle = mysql_fetch_row(resInputSingle);
            strText = rowInputSingle[1];
            SetDlgItemText(IDC_EDIT2, strText);
            mysql_free_result(resInputSingle);
        }
    }
    //query3.Format("select ChapterID,ChapterName from tb_chapterinfo where CourseID = " + _T(courseID_combox));
    ////  query3 = "select ChapterID,ChapterName from tb_chapterinfo where CourseID = "+
    //ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    //if (ress == 0)
    //{
    //    resInputSingle = mysql_store_result(&m_sqlConInputSingle);
    //    if (mysql_num_rows(resInputSingle) == 0) //查询结果为空
    //    {
    //        AfxMessageBox("请维护该科目章节信息！");
    //        courseNameI.ResetContent();
    //    }
    //    else
    //    {

    //        rowInputSingle = mysql_fetch_row(resInputSingle);
    //        ChapterID_combox = rowInputSingle[0];
    //        courseNameI.AddString(rowInputSingle[1]);

    //        while (resInputSingle->data_cursor)
    //        {
    //            rowInputSingle = mysql_fetch_row(resInputSingle);
    //            courseNameI.AddString(rowInputSingle[1]);
    //        }
    //        courseNameI.SetCurSel(0);
    //        mysql_free_result(resInputSingle);
    //    }
    //}
    mysql_close(&m_sqlConInputSingle);
}


void COnlineTest::OnTvnSelchangedTesttree(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
    
}


void COnlineTest::OnBnClickedButton3()
{
    CString strText, strText1;
    GetDlgItemText(IDC_EDIT2, strText);
    if (strText =="")
    {
        AfxMessageBox(_T("答案为空，请填写答案"));
    }
    else
    {
        MYSQL m_sqlConInputSingle;
        MYSQL_RES* resInputSingle;
        MYSQL_RES* resInputSingle1=NULL;
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
        query3.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question where QContent like \'%s\'", strText);
        int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
        if (ress == 0)
        {
            resInputSingle = mysql_store_result(&m_sqlConInputSingle);
            if (mysql_num_rows(resInputSingle) != 0) //查询结果为空
            {
                rowInputSingle = mysql_fetch_row(resInputSingle);
               
                strText = rowInputSingle[3];
                GetDlgItemText(IDC_EDIT3, strText1);
                if (strText1 == strText)
                {
                    AfxMessageBox("恭喜您，答案正确");
                    query3.Format("insert into tb_doquestion(QID,QContent,QAnswer,Qdetail,UserAnswer)values(%s,\'%s\',\'%s\',\'%s\',\'%s\')", rowInputSingle[0],rowInputSingle[1],rowInputSingle[2],rowInputSingle[11],strText1);
                    query3.Format("select id studentId,choose,judge,term,more,jianda ,type from t_mark1");
                    int ress1 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
                    if (ress == 0)
                    {                       
                        resInputSingle1 = mysql_store_result(&m_sqlConInputSingle);
                        if (mysql_num_rows(resInputSingle1) != 0) //查询结果为空
                        {
                            rowInputSingle1 = mysql_fetch_row(resInputSingle1);
                            if ( rowInputSingle1[6]=="单选题")
                            {
                                rowInputSingle1[2] = rowInputSingle1[2] + atoi(rowInputSingle[5]);
                                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[2],this->studentOnlineId);
                            }
                            if (rowInputSingle1[6] == "多选题")
                            {
                                rowInputSingle1[5] = rowInputSingle1[5] + atoi(rowInputSingle[5]);
                                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[5], this->studentOnlineId);
                            }
                            if (rowInputSingle1[6] == "判断题")
                            {
                                rowInputSingle1[3] = rowInputSingle1[3] + atoi(rowInputSingle[5]);
                                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[3], this->studentOnlineId);
                            }
                            if (rowInputSingle1[6] == "简单题")
                            {
                                rowInputSingle1[7] = rowInputSingle1[7] + atoi(rowInputSingle[5]);
                                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[7], this->studentOnlineId);
                            }
                            
                        }
                    }
                    mysql_free_result(resInputSingle1);
                    
                }
                else
                {
                    AfxMessageBox("答案错误，您可以查看答案详情");
                }
                mysql_free_result(resInputSingle);
            }
        }
        mysql_close(&m_sqlConInputSingle);

    }
    // TODO: 在此添加控件通知处理程序代码
}


void COnlineTest::OnBnClickedButton5()
{

    CString strText, strText1;
    GetDlgItemText(IDC_EDIT2, strText);
    MYSQL m_sqlConInputSingle;
    MYSQL_RES* resInputSingle;
    MYSQL_RES* resInputSingle1 = NULL;
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
    query3.Format("select QID,QContent,QType,QRightAnswer,QDifficulty,QScore,QChapterID,QKnowPoint,QUploadID,QUpTime,QUse,QDetailed,QCourseID from tb_question where QContent like \'%s\'", strText);
    int ress = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
    if (ress == 0)
    {
        resInputSingle = mysql_store_result(&m_sqlConInputSingle);
        if (mysql_num_rows(resInputSingle) != 0) //查询结果为空
        {
            rowInputSingle = mysql_fetch_row(resInputSingle);

            strText1 = rowInputSingle[11];
            SetDlgItemText(IDC_EDIT7, strText1);
            //if (strText1 == strText)
            //{
            //    AfxMessageBox("恭喜您，答案正确");
            //    query3.Format("insert into tb_doquestion(QID,QContent,QAnswer,Qdetail,UserAnswer)values(%s,\'%s\',\'%s\',\'%s\',\'%s\')", rowInputSingle[0], rowInputSingle[1], rowInputSingle[2], rowInputSingle[11], strText1);
            //    query3.Format("select id studentId,choose,judge,term,more,jianda ,type from t_mark1");
            //    int ress1 = mysql_query(&m_sqlConInputSingle, (char*)(LPCSTR)query3);
            //    if (ress == 0)
            //    {
            //        resInputSingle1 = mysql_store_result(&m_sqlConInputSingle);
            //        if (mysql_num_rows(resInputSingle1) != 0) //查询结果为空
            //        {
            //            rowInputSingle1 = mysql_fetch_row(resInputSingle1);
            //            if (rowInputSingle1[6] == "单选题")
            //            {
            //                rowInputSingle1[2] = rowInputSingle1[2] + atoi(rowInputSingle[5]);
            //                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[2], this->studentOnlineId);
            //            }
            //            if (rowInputSingle1[6] == "多选题")
            //            {
            //                rowInputSingle1[5] = rowInputSingle1[5] + atoi(rowInputSingle[5]);
            //                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[5], this->studentOnlineId);
            //            }
            //            if (rowInputSingle1[6] == "判断题")
            //            {
            //                rowInputSingle1[3] = rowInputSingle1[3] + atoi(rowInputSingle[5]);
            //                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[3], this->studentOnlineId);
            //            }
            //            if (rowInputSingle1[6] == "简单题")
            //            {
            //                rowInputSingle1[7] = rowInputSingle1[7] + atoi(rowInputSingle[5]);
            //                query3.Format("update t_mark set (choose = %s)where studentid = %s", rowInputSingle1[7], this->studentOnlineId);
            //            }

            //        }
            //    }
            //    mysql_free_result(resInputSingle1);

            //}
            //else
            //{
            //    AfxMessageBox("答案错误，您可以查看答案详情");
            //}
            mysql_free_result(resInputSingle);
        }
    }
    mysql_close(&m_sqlConInputSingle);
    SetDlgItemText(IDC_EDIT7, strText);
   
   


}
