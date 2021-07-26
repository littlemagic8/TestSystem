// CEditUserInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "examSystem.h"
#include "CEditUserInfo.h"
#include "afxdialogex.h"


// CEditUserInfo 对话框

IMPLEMENT_DYNAMIC(CEditUserInfo, CDialogEx)

CEditUserInfo::CEditUserInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EditUserInfo, pParent)
{

}

CEditUserInfo::~CEditUserInfo()
{
}

void CEditUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditUserInfo, CDialogEx)
END_MESSAGE_MAP()


// CEditUserInfo 消息处理程序
