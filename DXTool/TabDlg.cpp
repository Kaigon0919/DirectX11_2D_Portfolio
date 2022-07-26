// TabDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DXTool.h"
#include "TabDlg.h"
#include "afxdialogex.h"


// TabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabDlg, CDialogEx)

TabDlg::TabDlg(UINT nID, CWnd* pParent /*=NULL*/)
	: CDialogEx(nID, pParent)
{

}

TabDlg::~TabDlg()
{
}

void TabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabDlg, CDialogEx)
END_MESSAGE_MAP()


// TabDlg 메시지 처리기입니다.
