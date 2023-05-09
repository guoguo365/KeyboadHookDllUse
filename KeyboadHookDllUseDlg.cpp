
// KeyboadHookDllUseDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "KeyboadHookDllUse.h"
#include "KeyboadHookDllUseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �ӑB���ddll�ļ�
typedef int (WINAPI *FUNC)(void);
FUNC func;

// �o�B���ddll�ļ�
//#pragma comment(lib, "KeyboadHookDll.lib")
//extern "C" VOID SetHookOn();
//extern "C" VOID SetHookOff();

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKeyboadHookDllUseDlg dialog



CKeyboadHookDllUseDlg::CKeyboadHookDllUseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KEYBOADHOOKDLLUSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyboadHookDllUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyboadHookDllUseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_HOOKON_BNT, &CKeyboadHookDllUseDlg::OnBnClickedHookonBnt)
	ON_BN_CLICKED(ID_HOOKOFF_BTN, &CKeyboadHookDllUseDlg::OnBnClickedHookoffBtn)
END_MESSAGE_MAP()


// CKeyboadHookDllUseDlg message handlers

BOOL CKeyboadHookDllUseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// ጷ�dll�YԴ
	ReleaseRes("Kb.dll", (WORD)IDR_DLL1, "DLL");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeyboadHookDllUseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyboadHookDllUseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyboadHookDllUseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKeyboadHookDllUseDlg::OnBnClickedHookonBnt()
{
	// TODO: Add your control notification handler code here
	// SetHookOn();

	// �ӑB���ddll�ļ�
	HMODULE hModule = LoadLibrary("Kb.dll");
	func = (FUNC) GetProcAddress(hModule, "SetHookOn");
	func();
}


void CKeyboadHookDllUseDlg::OnBnClickedHookoffBtn()
{
	// TODO: Add your control notification handler code here
	//SetHookOff();

	// �ӑB���ddll�ļ�
	HMODULE hModule = LoadLibrary("Kb.dll");
	func = (FUNC) GetProcAddress(hModule, "SetHookOff");
	func();
}


/*
ጷ��YԴ
@param:strFileName
@param:wResID
@param:strFileType
*/
bool CKeyboadHookDllUseDlg::ReleaseRes(CString strFileName, WORD wResID, CString strFileType)
{
	
	// �YԴ��С
	DWORD dwWrite = 0;

	// �����ļ�
	HANDLE hFile = CreateFile(
		strFileName,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	// �����YԴ�ļ�
	HRSRC hrsc = FindResource(NULL, MAKEINTRESOURCE(wResID), strFileType);

	// �YԴ���d���ڴ�
	HGLOBAL hG = LoadResource(NULL, hrsc);

	// �@ȡ�YԴ��С
	DWORD dwSize = SizeofResource(NULL, hrsc);

	// �����ļ�
	WriteFile(hFile, hG, dwSize, &dwWrite, NULL);

	CloseHandle(hFile);
	return true;
}
