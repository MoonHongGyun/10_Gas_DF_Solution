// CConnectSocket.cpp: 구현 파일
//

#include "pch.h"
#include "MFCTESTCLNT.h"
#include "CConnectSocket.h"
#include "MFCTESTCLNTDlg.h"


// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket 멤버 함수


void CConnectSocket::OnClose(int nErrorCode)
{
    ShutDown();
    Close();

    CSocket::OnClose(nErrorCode);

    AfxMessageBox(_T("ERROR:Disconnected from server!"));
    ::PostQuitMessage(0);
}


void CConnectSocket::OnReceive(int nErrorCode)
{
    TCHAR szBuffer[1024];
    ::ZeroMemory(szBuffer, sizeof(szBuffer));

    if (Receive(szBuffer, sizeof(szBuffer)) > 0) {
        CMFCTESTCLNTDlg* pMain = (CMFCTESTCLNTDlg*)AfxGetMainWnd();
        pMain->m_List.AddString(szBuffer); // 리스트에 문자열을 추가한다.
        pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
    }
    CSocket::OnReceive(nErrorCode);
}
