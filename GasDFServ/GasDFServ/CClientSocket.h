#pragma once

// CClientSocket 명령 대상

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	void SetListenSocket(CAsyncSocket* pClient);
	CAsyncSocket* m_pListenSocket;
	CAsyncSocket* m_pAISocket;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void connectAI(CAsyncSocket* pClient);
};