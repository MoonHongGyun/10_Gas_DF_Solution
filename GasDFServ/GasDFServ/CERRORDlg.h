#pragma once


// CERRORDlg 대화 상자

class CERRORDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CERRORDlg)

public:
	CERRORDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CERRORDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CERRORDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ERROR_PICTURE;
	CString m_strFilePath;
	afx_msg void OnPaint();
};
