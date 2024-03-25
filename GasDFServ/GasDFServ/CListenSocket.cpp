// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFServ.h"
#include "CListenSocket.h"
#include "CClientSocket.h"
#include "GasDFServDlg.h"
#include <iostream>
#include "CAISocket.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket;
	if (Accept(*pClient))
	{
		int nWhoClient;
		pClient->Receive(&nWhoClient, sizeof(int));
		std::cout << ntohl(nWhoClient) << std::endl;
		if (ntohl(nWhoClient) == 1)
		{
			m_pAIClient = (CAISocket*)pClient;
			m_pAIClient->setAISocket(m_pAIClient);
			if (m_pCamClient != NULL)
			{
				m_pCamClient->connectAI(m_pAIClient);
			}
		}
		else
		{
			m_pCamClient = pClient;
			m_pCamClient->SetListenSocket(m_pCamClient);
		}
	}
	else
	{
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::CloseClientSocket(CSocket* pClient)
{

    if (pClient != NULL) 
	{
        // 클라이언트 연결중지후 종료
        pClient->ShutDown();
        pClient->Close();
    }
        delete pClient;
}

void CListenSocket::ClienttoAI(CString strFilePath, int nFileLength)
{
	m_pAIClient->Send(&nFileLength, sizeof(int));

	CFile SourceFile;
	SourceFile.Open((LPCTSTR)strFilePath, CFile::modeRead | CFile::typeBinary);

	DWORD dwRead;
	byte* data = new byte[nFileLength];
	dwRead = SourceFile.Read(data, nFileLength);
	m_pAIClient->Send(data, dwRead);

	SourceFile.Close();
}

void CListenSocket::AItoClient(CString strMsg, CString strFilePath, int nFileSize)
{

}