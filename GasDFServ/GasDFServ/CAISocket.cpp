// CAISocket.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFServ.h"
#include "CAISocket.h"
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
	int nFileLength;
	Receive(&nFileLength, 4);
	CString strFilePath = _T("C:\\Users\\IOT\\Desktop\\Gasimg\\shape.jpg");
	CFile targetFile;
	targetFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	int nFilelength = ntohl(nFileLength);
	byte* data = new byte[nFilelength];

	DWORD dwRead;
	dwRead = Receive(data, nFilelength);
	targetFile.Write(data, dwRead);

	targetFile.Close();

	
	char* strMsg = new char[1024];
	int nMsglen = Receive(strMsg, sizeof(strMsg));
	strMsg[nMsglen] = 0;
	
	CFile sourceFile;
	sourceFile.Open((LPCTSTR)strFilePath, CFile::modeRead | CFile::typeBinary);

	m_pCamClient->Send(&nFilelength, 4);

	data = new byte[nFilelength];
	dwRead = sourceFile.Read(data, nFilelength);
	m_pCamClient->Send(data, dwRead);

	m_pCamClient->Send(strMsg, sizeof(strMsg));
	delete strMsg;
	delete data;
	sourceFile.Close();
	CSocket::OnReceive(nErrorCode);
}
