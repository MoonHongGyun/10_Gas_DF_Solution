// CAISocket.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFServ.h"
#include "CAISocket.h"
#include "GasDFServDlg.h"
#include <iostream>

// CAISocket

CAISocket::CAISocket()
{
}

CAISocket::~CAISocket()
{
}

void CAISocket::setAISocket(CAsyncSocket* pClient)
{
	m_pAIClient = pClient;
}

void CAISocket::connectCamClient(CAsyncSocket* pClient)
{
	m_pCamClient = pClient;
}
// CAISocket 멤버 함수

void CAISocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	static int ImageCount = 1;
	int nFileLength;
	Receive(&nFileLength, 4);
	//std::cout << "3" << std::endl;
	CString strFilePath;
	strFilePath.Format(_T("C:\\Users\\IOT\\Desktop\\Gasimg\\%d.jpg"),ImageCount++);
	CFile targetFile;
	targetFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	int nFilelength = ntohl(nFileLength);
	byte* data = new byte[nFilelength];

	DWORD dwRead;
	dwRead = Receive(data, nFilelength);
	//std::cout << "4" << std::endl;
	targetFile.Write(data, dwRead);

	targetFile.Close();
	delete data;
	char* strFilecheck = "ok";
	Send(strFilecheck, strlen(strFilecheck));

	char* strMsg = new char[1024];
	int nMsglen = Receive(strMsg, sizeof(strMsg));
	strMsg[nMsglen] = 0;
	//std::cout << "5" << std::endl;

	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_USER_DRAW_AFTER, 0, 0);
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USER_UPDATE_LIST, 0, (LPARAM)strMsg);

	m_pCamClient->Send(strMsg, nMsglen);
	delete strMsg;
	CSocket::OnReceive(nErrorCode);
}
