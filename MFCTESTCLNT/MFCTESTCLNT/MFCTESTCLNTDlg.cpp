
// MFCTESTCLNTDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTESTCLNT.h"
#include "MFCTESTCLNTDlg.h"
#include "afxdialogex.h"
#include <iostream>

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTESTCLNTDlg 대화 상자



CMFCTESTCLNTDlg::CMFCTESTCLNTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTESTCLNT_DIALOG, pParent)
	, m_sendMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTESTCLNTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT2, m_sendMsg);
}

BEGIN_MESSAGE_MAP(CMFCTESTCLNTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CMFCTESTCLNTDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_FILE, &CMFCTESTCLNTDlg::OnBnClickedBtnFile)
END_MESSAGE_MAP()


// CMFCTESTCLNTDlg 메시지 처리기

BOOL CMFCTESTCLNTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Socket.Create();
	if (m_Socket.Connect(_T("127.0.0.1"), 21000) == FALSE) {
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
		return FALSE;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTESTCLNTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTESTCLNTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCTESTCLNTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTESTCLNTDlg::OnBnClickedBtnSend()
{
	UpdateData(TRUE);
	m_Socket.Send((LPVOID)(LPCTSTR)m_sendMsg, m_sendMsg.GetLength() * 2);
	m_sendMsg.Format(_T(""));
	UpdateData(FALSE);
}


BOOL CMFCTESTCLNTDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{   // 위 VK_RETURN은 Enter, VK_ESCAPE는 ESC을 의미함. 필요시 하나만 사용.
			OnBnClickedBtnSend();
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCTESTCLNTDlg::OnBnClickedBtnFile()
{
	CFile sourceFile;
	CString strFilePath = _T("C:\\Users\\IOT\\Desktop\\testfile\\shape.jpg");

	sourceFile.Open((LPCTSTR)strFilePath, CFile::modeRead | CFile::typeBinary);

	DWORD dwRead;

	int nFileLength = sourceFile.GetLength();
	m_Socket.Send(&nFileLength, 4);

	byte* data = new byte[nFileLength];
	dwRead = sourceFile.Read(data, nFileLength);
	m_Socket.Send(data, dwRead);
	//do
	//{
	//	dwRead = sourceFile.Read(data, 4096);
	//	m_Socket.Send(data, dwRead);
	//} while (dwRead > 0);

	//delete data;
	sourceFile.Close();
}
