
// GasDFServDlg.h: 헤더 파일
//
#include "CListenSocket.h"
#include "CERRORDlg.h"
#define WM_USER_DRAW_BEFORE WM_USER+1
#define WM_USER_DRAW_AFTER WM_USER+2
#define WM_USER_UPDATE_LIST WM_USER+3

#pragma once


// CGasDFServDlg 대화 상자
class CGasDFServDlg : public CDialogEx
{
	// 생성입니다.
public:
	CGasDFServDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CListenSocket m_ListenSocket;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GASDFSERV_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_PicBefore;
	CStatic m_PicAfter;
	void DrawPictureBefore();
	void DrawPictureAfter();
	void UpdateList(char* strData);
	LRESULT OnDrawPictureBefore(WPARAM wParam, LPARAM lParam);
	LRESULT OnDrawPictureAfter(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateList(WPARAM wParam, LPARAM lParam);
	CListCtrl m_PicList;
	CListCtrl m_ErrorList;
	CListCtrl m_OnoffList;
	afx_msg void OnNMDblclkErrorList(NMHDR* pNMHDR, LRESULT* pResult);
	CERRORDlg* m_pErrorDlg;
};
