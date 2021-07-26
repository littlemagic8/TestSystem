// LOGIN.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "LOGIN.h"
#include "afxdialogex.h"


// LOGIN 对话框

IMPLEMENT_DYNAMIC(LOGIN, CDialogEx)

LOGIN::LOGIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMSYSTEM_DIALOG, pParent)
{

}

LOGIN::~LOGIN()
{
}

void LOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LOGIN, CDialogEx)
END_MESSAGE_MAP()


// LOGIN 消息处理程序
