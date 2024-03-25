#pragma once

// CAISocket 명령 대상

class CAISocket : public CSocket
{
public:
	CAISocket();
	virtual ~CAISocket();
	void setAISocket(CAsyncSocket* pClient);
	CAsyncSocket* m_pAIClient;
	CAsyncSocket* m_pCamClient;
	void connectCamClient(CAsyncSocket* pClient);
	virtual void OnReceive(int nErrorCode);
};
 