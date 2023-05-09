
// KeyboadHookDllUseDlg.h : header file
//

#pragma once


// CKeyboadHookDllUseDlg dialog
class CKeyboadHookDllUseDlg : public CDialogEx
{
// Construction
public:
	CKeyboadHookDllUseDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEYBOADHOOKDLLUSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedHookonBnt();
	afx_msg void OnBnClickedHookoffBtn();
	bool ReleaseRes(CString strFileName, WORD wResID, CString strFileType);
};
