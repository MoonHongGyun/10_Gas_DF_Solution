// CConnectSocket.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFClnt.h"
#include "CConnectSocket.h"
#include <iostream>


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
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int nFileLength;
	Receive(&nFileLength, 4);
	CString strFilePath = _T("C:\\Users\\IOT\\Desktop\\testImage\\shape.jpg");
	CFile targetFile;
	targetFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	byte* data = new byte[nFileLength];

	DWORD dwRead;
	dwRead = Receive(data, nFileLength);
	targetFile.Write(data, dwRead);

	delete data;
	targetFile.Close();

	char* strMsg = new char[1024];
	int nMsglen = Receive(strMsg, sizeof(strMsg));
	strMsg[nMsglen] = 0;

	std::cout << strMsg << std::endl;
    CSocket::OnReceive(nErrorCode);
}
