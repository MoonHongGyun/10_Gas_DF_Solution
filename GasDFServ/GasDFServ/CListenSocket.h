#pragma once

// CListenSocket 명령 대상
#include "CClientSocket.h"
#include "CAISocket.h"

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	CClientSocket* m_pCamClient;
	CAISocket* m_pAIClient;
	void ClienttoAI(CString strFilePath, int nFileSize);
	void AItoClient(CString strMsg, CString strFilePath, int nFileSize);
};


