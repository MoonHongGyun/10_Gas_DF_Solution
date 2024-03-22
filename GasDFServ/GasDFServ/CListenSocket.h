#pragma once

// CListenSocket 명령 대상
#include "CClientSocket.h"

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	CClientSocket* m_pCamClient;
	CClientSocket* m_pAIClient;
};


