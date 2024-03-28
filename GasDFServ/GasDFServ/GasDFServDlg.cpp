
// GasDFServDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GasDFServ.h"
#include "GasDFServDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string.h>
#include <mysql.h>

#define DB_IP "127.0.0.1"
#define DB_ID "root"
#define DB_PASS "1111"
#define DB_NAME "gasdf"

#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"ws2_32.lib")

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define new DEBUG_NEW
#endif

MYSQL_ROW row;
MYSQL_RES* m_res;
MYSQL *connection = NULL,mysql;

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
public:
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


// CGasDFServDlg 대화 상자



CGasDFServDlg::CGasDFServDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GASDFSERV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGasDFServDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_BEFORE, m_PicBefore);
	DDX_Control(pDX, IDC_PIC_AFTER, m_PicAfter);
	DDX_Control(pDX, IDC_PIC_LIST, m_PicList);
	DDX_Control(pDX, IDC_ERROR_LIST, m_ErrorList);
	DDX_Control(pDX, IDC_ONOFF_LIST, m_OnoffList);
}

BEGIN_MESSAGE_MAP(CGasDFServDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_USER_DRAW_BEFORE, OnDrawPictureBefore)
	ON_MESSAGE(WM_USER_DRAW_AFTER, OnDrawPictureAfter)
	ON_MESSAGE(WM_USER_UPDATE_LIST, OnUpdateList)
	ON_NOTIFY(NM_DBLCLK, IDC_ERROR_LIST, &CGasDFServDlg::OnNMDblclkErrorList)
END_MESSAGE_MAP()

LRESULT CGasDFServDlg::OnDrawPictureBefore(WPARAM wParam, LPARAM lParam)
{
	DrawPictureBefore();
	return 0;
}

LRESULT CGasDFServDlg::OnDrawPictureAfter(WPARAM wParam, LPARAM lParam)
{
	DrawPictureAfter();
	return 0;
}

LRESULT CGasDFServDlg::OnUpdateList(WPARAM wParam, LPARAM lParam)
{
	char* strData = (char*)lParam;
	UpdateList(strData);
	return 0;
}
// CGasDFServDlg 메시지 처리기

BOOL CGasDFServDlg::OnInitDialog()
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
	if (m_ListenSocket.Create(21000, SOCK_STREAM)) { // 소켓생성
		if (!m_ListenSocket.Listen()) {
			AfxMessageBox(_T("ERROR:Listen() return False"));
		}
	}
	else {
		AfxMessageBox(_T("ERROR:Failed to create server socket!"));
	}

	m_PicList.InsertColumn(0, _T("CODE"), LVCFMT_CENTER, 100);
	m_PicList.InsertColumn(1, _T("TIME"), LVCFMT_CENTER, 200);
	m_ErrorList.InsertColumn(0, _T("CODE"), LVCFMT_CENTER, 100);
	m_OnoffList.InsertColumn(0, _T("CODE"), LVCFMT_CENTER, 100);
	m_OnoffList.InsertColumn(1, _T("ONOFF"), LVCFMT_CENTER, 100);
	m_OnoffList.InsertColumn(2, _T("ANGLE"), LVCFMT_CENTER, 100);


	mysql_init(&mysql);
	
	connection = mysql_real_connect(&mysql, DB_IP, DB_ID, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (connection == NULL)
	{
		AfxMessageBox(_T("DB NOT OPEN"));
	}
	m_ErrorList.InsertItem(0, _T("asdqw"));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGasDFServDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGasDFServDlg::OnPaint()
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
HCURSOR CGasDFServDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGasDFServDlg::DrawPictureBefore()
{
	static int imageCount = 1;
	CString strFilePath;
	strFilePath.Format(_T("C:\\Users\\IOT\\Desktop\\Gasimage\\%d.jpg"), imageCount++);
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_PicBefore.GetWindowRect(rect); //GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_PicBefore.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage  
	image.Load(strFilePath);//이미지 로드
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);
}

void CGasDFServDlg::DrawPictureAfter()
{
	static int ImageCount = 1;
	CString strFilePath;
	strFilePath.Format(_T("C:\\Users\\IOT\\Desktop\\Gasimg\\%d.jpg"), ImageCount);
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_PicAfter.GetWindowRect(rect); //GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_PicAfter.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage  
	image.Load(strFilePath);//이미지 로드
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);
	CString strImageCount;
	strImageCount.Format(_T("%d"), ImageCount);
	CString strDate;
	SYSTEMTIME stime;
	::GetSystemTime(&stime);
	strDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		stime.wYear,
		stime.wMonth,
		stime.wDay,
		(stime.wHour + 9) % 24,
		stime.wMinute,
		stime.wSecond);
	m_PicList.InsertItem(ImageCount-1, strImageCount);
	m_PicList.SetItemText(ImageCount-1, 1, strDate);
	ImageCount++;
}

void CGasDFServDlg::UpdateList(char* strData)
{
	CString strMsg = CString(strData); //제품코드,불량,개폐여부,각도
	CStringArray strMsgList;
	static int ErrorListCount = 0;
	static int ListCount = 0;
	strMsgList.SetSize(4);
	for (int i = 0; i < 5; i++)
	{
		AfxExtractSubString(strMsgList[i], strMsg, i, '#');
	}

	if (strMsgList[4] == "X")
	{
		m_ErrorList.InsertItem(ErrorListCount++, strMsgList[0]);
		CString invertquery = _T("insert into result(CODE,ERROR,ONOFF,ANGLE) values('") + strMsgList[0] + _T("','") + strMsgList[3] +_T("','") + strMsgList[1] + _T("','") + strMsgList[2] + _T("')");
		CStringA queryBuffer = (CStringA)invertquery;
		const char* query;
		query = queryBuffer.GetBuffer();
		mysql_query(&mysql, query);
	}
	m_OnoffList.InsertItem(ListCount, strMsgList[0]);
	m_OnoffList.SetItemText(ListCount, 1, strMsgList[1]);
	m_OnoffList.SetItemText(ListCount++, 2, strMsgList[2]);


}

void CGasDFServDlg::OnNMDblclkErrorList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int row = pNMItemActivate->iItem;
	int col = pNMItemActivate->iSubItem;
	CString strCode = m_ErrorList.GetItemText(row, col);
	
	*pResult = 0;
}
