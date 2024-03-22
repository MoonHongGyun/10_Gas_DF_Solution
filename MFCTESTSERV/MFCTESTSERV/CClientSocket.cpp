// CClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "MFCTESTSERV.h"
#include "CClientSocket.h"
#include "CListenSocket.h"
#include "MFCTESTSERVDlg.h"
#include <iostream>
#include <thread>



// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


void Handleclient1(CAsyncSocket* pClient)
{
    int nTest;
    pClient->Receive(&nTest, 4);
    AfxMessageBox(_T("asd"));
}

void Handleclient2(CAsyncSocket* pClient)
{
    int nTest;
    pClient->Receive(&nTest, 4);
    AfxMessageBox(_T("qwe"));
}

// CClientSocket 멤버 함수

void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}


void CClientSocket::OnReceive(int nErrorCode)
{
    int nNameLen;
    Receive(&nNameLen, 4);

    if (nNameLen == 123)
    {
        std::thread t1(&Handleclient1, m_pListenSocket);
        t1.detach();
    }
    else
    {
        std::thread t1(&Handleclient2, m_pListenSocket);
        t1.detach();
    }

    
    
    //CString strFilePath = _T("C:\\Users\\IOT\\Desktop\\testimage\\shape.jpg");

    //CFile targetfile;
    //targetfile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

    //int nFileLength;
    //Receive(&nFileLength, 4);

    //byte* data = new byte[nFileLength];
    //
    //DWORD dwRead;
    //dwRead = Receive(data, nFileLength);
    //targetfile.Write(data, dwRead);

    //delete data;
    //targetfile.Close();

    //CMFCTESTSERVDlg* pMain = (CMFCTESTSERVDlg*)AfxGetMainWnd();

    //pMain->ViewImage(strFilePath);

    //CString strTmp = _T(""), strIPAddress = _T("");
    //UINT uPortNumber = 0;
    //TCHAR strBuffer[1024];
    //::ZeroMemory(strBuffer, sizeof(strBuffer)); // :: 붙이고 안붙이고 차이 알아보기

    //GetPeerName(strIPAddress, uPortNumber);
    //if (Receive(strBuffer, sizeof(strBuffer)) > 0) 
    //{ // 전달된 데이터(문자열)가 있을 경우
    //    CMFCTESTSERVDlg* pMain = (CMFCTESTSERVDlg*)AfxGetMainWnd();
    //    strTmp.Format(_T("[%s:%d]: %s"), strIPAddress, uPortNumber, strBuffer);
    //    pMain->m_List.AddString(strTmp);  // 메시지 리스트(메시지창?)에 입력받은 메시지 띄우기
    //    pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

    //    CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
    //    pServerSocket->SendAllMessage(strBuffer); // 다른 클라이언트들에게 메시지 전달
    //}

	CSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
    CSocket::OnClose(nErrorCode);

    CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
    pServerSocket->CloseClientSocket(this);

}

