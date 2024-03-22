﻿// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "GasDFServ.h"
#include "CListenSocket.h"
#include "CClientSocket.h"
#include "GasDFServDlg.h"

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
		pClient->Receive(&nWhoClient, 4);
		if (nWhoClient == 1)
		{
			m_pAIClient = pClient;
			m_pAIClient->SetListenSocket(m_pAIClient, nWhoClient);
		}
		else
		{
			m_pCamClient = pClient;
			m_pCamClient->SetListenSocket(m_pCamClient, nWhoClient);
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
