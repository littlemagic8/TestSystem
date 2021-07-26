// ListShow.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "ListShow.h"
#include "afxdialogex.h"


// ListShow 对话框

IMPLEMENT_DYNAMIC(ListShow, CDialogEx)

ListShow::ListShow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ADD_ABOUTBOX, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

ListShow::~ListShow()
{
}

void ListShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ListShow, CDialogEx)
END_MESSAGE_MAP()


// ListShow 消息处理程序
