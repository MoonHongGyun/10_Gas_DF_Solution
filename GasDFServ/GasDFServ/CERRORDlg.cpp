// CERRORDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFServ.h"
#include "CERRORDlg.h"
#include "afxdialogex.h"

// CERRORDlg 대화 상자

IMPLEMENT_DYNAMIC(CERRORDlg, CDialogEx)

CERRORDlg::CERRORDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CERRORDlg, pParent)
{

}

CERRORDlg::~CERRORDlg()
{
}

void CERRORDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ERROR_PIC, m_ERROR_PICTURE);
}


BEGIN_MESSAGE_MAP(CERRORDlg, CDialogEx)
END_MESSAGE_MAP()


// CERRORDlg 메시지 처리기
