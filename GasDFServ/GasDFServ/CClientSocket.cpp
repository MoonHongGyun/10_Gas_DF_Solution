// CClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFServ.h"
#include "CClientSocket.h"
#include "CListenSocket.h"
#include <thread>
#include "GasDFServDlg.h"
#include <iostream>


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

void CClientSocket::SetListenSocket(CAsyncSocket* pClient)
{
	m_pListenSocket = pClient;
}

void CClientSocket::connectAI(CAsyncSocket* pClient)
{
	m_pAISocket = pClient;
}
// CClientSocket 멤버 함수



void CClientSocket::OnReceive(int nErrorCode)
{	
	static int ImageCount = 1;
	int nFileLength;
	Receive(&nFileLength, 4);
	//std::cout << "1" << std::endl;
	CString strFilePath;
	strFilePath.Format(_T("C:\\Users\\IOT\\Desktop\\Gasimage\\%d.jpg"), ImageCount++);
	CFile targetFile;
	targetFile.Open((LPCTSTR)strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	byte* data = new byte[nFileLength];

	DWORD dwRead;
	dwRead = Receive(data, nFileLength);
	//std::cout << "2" << std::endl;
	targetFile.Write(data, dwRead);

	targetFile.Close();

	CFile sourceFile;
	sourceFile.Open((LPCTSTR)strFilePath, CFile::modeRead | CFile::typeBinary);

	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_USER_DRAW_BEFORE, 0, 0);

	int ntest = ntohl(nFileLength);
	m_pAISocket->Send(&ntest, 4);

	data = new byte[nFileLength];
	dwRead = sourceFile.Read(data, nFileLength);
	m_pAISocket->Send(data, dwRead);

	delete data;
	sourceFile.Close();
	CSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}
