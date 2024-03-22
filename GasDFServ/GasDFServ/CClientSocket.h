#pragma once

// CClientSocket 명령 대상

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	void SetListenSocket(CAsyncSocket* pClient,int nWho);
	CAsyncSocket* m_pListenSocket;
	int nWhoClient;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};