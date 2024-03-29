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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CERRORDlg 메시지 처리기


void CERRORDlg::OnPaint()
{
	CImage ErrorPic;
	ErrorPic.Load(m_strFilePath);
	CDC* dc = m_ERROR_PICTURE.GetDC();
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_ERROR_PICTURE.GetWindowRect(rect);
	ErrorPic.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);
}
