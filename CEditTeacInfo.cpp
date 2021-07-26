// CEditTeacInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CEditTeacInfo.h"
#include "afxdialogex.h"


// CEditTeacInfo 对话框

IMPLEMENT_DYNAMIC(CEditTeacInfo, CDialogEx)

CEditTeacInfo::CEditTeacInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EditstuInfo1, pParent)
{

}

CEditTeacInfo::~CEditTeacInfo()
{
}

void CEditTeacInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditTeacInfo, CDialogEx)
END_MESSAGE_MAP()


// CEditTeacInfo 消息处理程序
