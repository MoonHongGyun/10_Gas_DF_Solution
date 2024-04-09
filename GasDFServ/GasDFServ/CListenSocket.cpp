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
	if (m_pCamClient == NULL && m_pAIClient == NULL)
	{
		m_pAIClient = new CAISocket;
		if(!Accept(*m_pAIClient))
			AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
		m_pAIClient->setAISocket(m_pAIClient);
	}
	else
	{
		m_pCamClient = new CClientSocket;
		if(!Accept(*m_pCamClient))
			AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
		m_pCamClient->SetListenSocket(m_pCamClient);
		m_pCamClient->connectAI(m_pAIClient);
		m_pAIClient->connectCamClient(m_pCamClient);
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
