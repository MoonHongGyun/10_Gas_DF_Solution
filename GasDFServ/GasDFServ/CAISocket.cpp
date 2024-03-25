// CAISocket.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFServ.h"
#include "CAISocket.h"


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

// CAISocket 멤버 함수


void CAISocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int nFileLength;
	Receive(&nFileLength, 4);
	CString strFilePath = _T("C:\\Users\\IOT\\Desktop\\GasImage\\shape.jpg");
	CFile targetFile;
	targetFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	byte* data = new byte[nFileLength];

	DWORD dwRead;
	dwRead = Receive(data, nFileLength);
	targetFile.Write(data, dwRead);

	delete data;
	targetFile.Close();

	CSocket::OnReceive(nErrorCode);
}
