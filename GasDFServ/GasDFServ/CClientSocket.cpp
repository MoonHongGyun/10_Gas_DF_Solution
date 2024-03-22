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

void CClientSocket::SetListenSocket(CAsyncSocket* pClient,int nWho)
{
	m_pListenSocket = pClient;
	nWhoClient = nWho;
}
// CClientSocket 멤버 함수

void HandleClientCam(CAsyncSocket* pListenSocket)
{

	int nFileLength;
	pListenSocket->Receive(&nFileLength, 4);
	CString strFilePath = _T("C:\\Users\\IOT\\Desktop\\GasImage\\shape.jpg");
	CFile targetFile;
	targetFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	byte* data = new byte[nFileLength];

	DWORD dwRead;
	dwRead = pListenSocket->Receive(data, nFileLength);
	targetFile.Write(data, dwRead);

	delete data;
	targetFile.Close();

	CGasDFServDlg* pMain = (CGasDFServDlg*)AfxGetMainWnd;
	pMain->DrawPicture(strFilePath);
}

void HandleClientAI(CAsyncSocket* pListenSocket)
{
	int nFileLength;
	pListenSocket->Receive(&nFileLength, 4);
	CString strFilePath = _T("C:\\Users\\IOT\\Desktop\\GasImage\\shape.jpg");
	CFile targetFile;
	targetFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	byte* data = new byte[nFileLength];

	DWORD dwRead;
	dwRead = pListenSocket->Receive(data, nFileLength);
	targetFile.Write(data, dwRead);

	delete data;
	targetFile.Close();

	//char* strMsg{};
	//pListenSocket->Receive(strMsg, 1024);
	//std::cout << strMsg << std::endl;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	if (nWhoClient == 1)
	{
		std::thread AIthread(&HandleClientAI, m_pListenSocket);
		AIthread.join();
	}
	else
	{
		std::thread Camthread(&HandleClientCam, m_pListenSocket);
		Camthread.join();
	}

	
	CSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}
