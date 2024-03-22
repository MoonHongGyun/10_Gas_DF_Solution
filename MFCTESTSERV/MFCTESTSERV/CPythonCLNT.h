#pragma once

// CPythonCLNT 명령 대상

class CPythonCLNT : public CSocket
{
public:
	CPythonCLNT();
	virtual ~CPythonCLNT();
	void SelSocket(CAsyncSocket* pClient);
	CPythonCLNT* m_pClnt;
	virtual void OnReceive(int nErrorCode);
};


