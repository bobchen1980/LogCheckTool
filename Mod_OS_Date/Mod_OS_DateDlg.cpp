// Mod_OS_DateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Mod_OS_Date.h"
#include "Mod_OS_DateDlg.h"

#include "funcGetinfo.h"
#include   <Iphlpapi.h>  
#pragma comment(lib, "iphlpapi.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMod_OS_DateDlg dialog




CMod_OS_DateDlg::CMod_OS_DateDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMod_OS_DateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMod_OS_DateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, ceInstall);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, ceDateTime);
	DDX_Control(pDX, IDC_LIST2, ctlOSRecord);
	DDX_Control(pDX, IDC_LIST1, ctlDiskNO);
	DDX_Control(pDX, IDC_LIST3, ctlMACList);
}

BEGIN_MESSAGE_MAP(CMod_OS_DateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMod_OS_DateDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONMOD, &CMod_OS_DateDlg::OnBnClickedButtonmod)
	ON_BN_CLICKED(IDC_BUTTON2, &CMod_OS_DateDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMod_OS_DateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CMod_OS_DateDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMod_OS_DateDlg message handlers

BOOL CMod_OS_DateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	if ( UpdateProcessPrivilege( ::GetCurrentProcess(), SE_DEBUG_NAME ) ) {
		TRACE("UpdateProcessPrivilege Succeed!\r\n");
	}
	else {
		TRACE("Fail!");
	}

    DWORD dwStyle = ctlMACList.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    ctlMACList.SetExtendedStyle(dwStyle); //设置扩展风格
	ctlMACList.InsertColumn(0, "ID", LVCFMT_LEFT, 10 );
	ctlMACList.InsertColumn(1, "MAC", LVCFMT_LEFT, 110 );
	ctlMACList.InsertColumn(2, "IP", LVCFMT_LEFT, 100 );
	ctlMACList.InsertColumn(3, "Info", LVCFMT_LEFT, 180 );

	OnBnClickedButtonmod();
	OnBnClickedButton1();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMod_OS_DateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMod_OS_DateDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMod_OS_DateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMod_OS_DateDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	HANDLE hEventLog;
	EVENTLOGRECORD *pevlr;
	TCHAR eventBuf[4096];
	pevlr = (EVENTLOGRECORD *)&eventBuf;
	hEventLog=OpenEventLog(_T(""), _T("System"));// System
	if (hEventLog==NULL)
	{
		MessageBox(_T("open log error"));
		return;
	}


	ClearEventLog(hEventLog,NULL);

	MessageBox("Deleted all records!");

	ctlOSRecord.DeleteAllItems();

	//OnOK();
}

void CMod_OS_DateDlg::OnBnClickedButtonmod()
{
	// TODO: Add your control notification handler code here
	LONG lResult;
	HKEY hKey; 

	LPCTSTR lpSubKey = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

	DWORD cbData = 4;

	DWORD dwData = 0;

	/**////////

	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,lpSubKey,NULL,KEY_READ,&hKey);

	if (lResult != ERROR_SUCCESS) 
	{
		if (lResult == ERROR_FILE_NOT_FOUND) {
			MessageBox(_T("Key not found"));
			return;
		} 
		else {
			MessageBox(_T("Error opening key.\n"));
			return;
		}
	}


	lResult = RegQueryValueEx(hKey,_T("InstallDate"),NULL,NULL,(LPBYTE)&dwData,&cbData);

	if (lResult == ERROR_SUCCESS) 
	{
		CTime tInit(dwData);
		CTimeSpan tEight(8*3600);
		CTime tInstall;
		tInstall = tInit - tEight;
		CString szInstall = tInstall.Format("%Y-%m-%d %H:%M:%S %W-%A");
		ceDateTime.SetFormat(_T("yyyy-MM-dd   HH:mm:ss"));
		ceDateTime.SetTime(&tInstall);
		ceInstall.SetWindowText(szInstall);
		//MessageBox(szInstall);
	}

	RegCloseKey(hKey);

	/**////////


}

void CMod_OS_DateDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	LONG lResult;
	HKEY hKey; 

	LPCTSTR lpSubKey = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

	DWORD cbData = 4;

	DWORD dwData = 0;

	/**////////
	CTime tMod;
	ceDateTime.GetTime(tMod);
	CTimeSpan tValue;
	tValue = tMod - CTime();
	dwData = tValue.GetTotalSeconds() + 8*3600;

	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,lpSubKey,NULL,KEY_ALL_ACCESS,&hKey);

	if (lResult != ERROR_SUCCESS) 
	{
		if (lResult == ERROR_FILE_NOT_FOUND) {
			MessageBox(_T("Key not found"));
			return;
		} 
		else {
			MessageBox(_T("Error opening key.\n"));
			return;
		}
	}


	lResult = RegSetValueEx(hKey,_T("InstallDate"),NULL,REG_DWORD,(LPBYTE)&dwData,sizeof(DWORD));
	int errCode = GetLastError();
	if (lResult == ERROR_SUCCESS) 
	{

		DWORD cbDataR = 4;
		DWORD dwDataR = 0;		
		if (RegQueryValueEx(hKey,_T("InstallDate"),NULL,NULL,(LPBYTE)&dwDataR,&cbDataR) == ERROR_SUCCESS) 
		{
			CTime tInit(dwDataR);
			CTimeSpan tEight(8*3600);
			CTime tInstall;
			tInstall = tInit - tEight;
			CString szInstall = tInstall.Format("%Y-%m-%d %H:%M:%S");
			CString szTmp;
			szTmp.Format(_T("Successful. OS install date is %s"),szInstall);
			ceDateTime.SetTime(&tInstall);
			ceInstall.SetWindowText(szInstall);
			MessageBox(szTmp);
		}

	}
	else
	{
		if (lResult == ERROR_FILE_NOT_FOUND) {
			MessageBox(_T("Key not found"));
			return;
		} 
		else {	
			CString err;
			err.Format(_T("set error: %d"),errCode);
			MessageBox(err);
			return;
		}
	}

	RegCloseKey(hKey);

}

void CMod_OS_DateDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	ctlOSRecord.DeleteAllItems();
	ctlMACList.DeleteAllItems();
	ctlDiskNO.DeleteAllItems();

	GetOSStartInfo();

	GetDiskSerial();

	GetAllLocalAdapterMacAddr();

}


void CMod_OS_DateDlg::GetDiskSerial(void)
{
	CString szTmp;

	ReadPhysicalDriveInNTWithAdminRights();

	//MessageBox(szTmp);
	for(UINT i=0;i<m_DriveSerialList.size();i++)
	{
		szTmp.Format("%s %d:%s",DriveType(i),i+1,SerialNumber(i));
		ctlDiskNO.InsertItem(ctlDiskNO.GetItemCount(),szTmp);
	}

}

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

void CMod_OS_DateDlg::GetAllLocalAdapterMacAddr(void)
{

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    UINT i;

/* variables used to print DHCP time info */
    struct tm newtime;
    char buffer[32];
    errno_t error;

    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        MessageBox("Error allocating memory needed to call GetAdaptersinfo\n");
        return;
    }
// Make an initial call to GetAdaptersInfo to get
// the necessary size into the ulOutBufLen variable
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            MessageBox("Error allocating memory needed to call GetAdaptersinfo\n");
            return;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {

			CString szMAC,szTMP,szAdapterInfo,szTYPE;
            //printf("\tComboIndex: \t5d\n", pAdapter->ComboIndex);
            //printf("\tAdapter Name: \t%s\n", pAdapter->AdapterName);
            //printf("\tAdapter Desc: \t%s\n", pAdapter->Description);
            //printf("\tAdapter Addr: \t");
            for (i = 0; i < pAdapter->AddressLength; i++) {
                if (i == (pAdapter->AddressLength - 1))
                    szTMP.Format("%.2X\n", (int) pAdapter->Address[i]);
                else
                    szTMP.Format("%.2X-", (int) pAdapter->Address[i]);

				szMAC += szTMP;
            }

            switch (pAdapter->Type) {
            case MIB_IF_TYPE_OTHER:
                szTYPE = "Other";
                break;
            case MIB_IF_TYPE_ETHERNET:
                szTYPE = "Ethernet";
                break;
            case MIB_IF_TYPE_TOKENRING:
                szTYPE = "Token";
                break;
            case MIB_IF_TYPE_FDDI:
                szTYPE = "FDDI";
                break;
            case MIB_IF_TYPE_PPP:
                szTYPE = "PPP";
                break;
            case MIB_IF_TYPE_LOOPBACK:
                szTYPE = "Lookback";
                break;
            case MIB_IF_TYPE_SLIP:
                szTYPE = "Slip";
                break;
            default:
                szTYPE = "Unknown";
                break;
            }

            //printf("\tIP Address: \t%s\n",
            //       pAdapter->IpAddressList.IpAddress.String);
            //printf("\tIP Mask: \t%s\n", pAdapter->IpAddressList.IpMask.String);
            //printf("\tGateway: \t%s\n", pAdapter->GatewayList.IpAddress.String);

			szAdapterInfo.Format("%d:%s,%s,%s",pAdapter->ComboIndex,szMAC,pAdapter->IpAddressList.IpAddress.String, pAdapter->Description);
			int nRow =ctlMACList.InsertItem(ctlMACList.GetItemCount(),szAdapterInfo);
			ctlMACList.SetItemText(nRow, 1,szMAC);
			ctlMACList.SetItemText(nRow, 2,pAdapter->IpAddressList.IpAddress.String);
			ctlMACList.SetItemText(nRow, 3,pAdapter->Description);


            pAdapter = pAdapter->Next;

        }
    } else {
        MessageBox("GetAdaptersInfo failed\n");

    }
    if (pAdapterInfo)
        FREE(pAdapterInfo);

}
void CMod_OS_DateDlg::GetOSStartInfo(void)
{
	HANDLE hEventLog;
	EVENTLOGRECORD *pevlr;
	TCHAR eventBuf[4096];
	pevlr = (EVENTLOGRECORD *)&eventBuf;
	DWORD dwRead, dwNeeded;
	hEventLog=OpenEventLog(_T(""), _T("System"));// System
	if (hEventLog==NULL)
	{
		MessageBox(_T("open log error"));
		return;
	}

	while (ReadEventLog(hEventLog,  // event log handle 
		EVENTLOG_FORWARDS_READ |  // reads forward 
		EVENTLOG_SEQUENTIAL_READ, // sequential read 
		0,            // ignored for sequential reads 
		pevlr,        // pointer to buffer 
		sizeof(eventBuf),  // size of buffer 
		&dwRead,      // number of bytes read 
		&dwNeeded))   // bytes in next record 
	{

		while   (dwRead   >   0)     
		{   
			if (pevlr->EventType == EVENTLOG_INFORMATION_TYPE)
			{                                                             
				CString szSource,szTime,szID;
				szSource.Format(_T("%s"),(LPSTR)   ((LPBYTE)   pevlr   +     
					sizeof(EVENTLOGRECORD)));
				if(szSource.CompareNoCase(_T("EventLog")) == 0)
				{
					CTime tDate(pevlr->TimeGenerated);
					szTime = tDate.Format(_T("%Y-%m-%d %H:%M:%S"));
					DWORD enID = pevlr->EventID & 0xFFFF;
					if(enID == 6005)
					{
						szID.Format("%s:开机",szTime);
						ctlOSRecord.InsertItem(ctlOSRecord.GetItemCount(),szID);

					}
					if(enID == 6006)
					{
						szID.Format("%s:关机",szTime);
						ctlOSRecord.InsertItem(ctlOSRecord.GetItemCount(),szID);
					}

				}
			} 
			dwRead   -=   pevlr->Length;     
			pevlr = (EVENTLOGRECORD *)((LPBYTE)   pevlr   +   pevlr->Length);     
		}     

		pevlr   =   (EVENTLOGRECORD   *)   &eventBuf;     


	} 
}

void CMod_OS_DateDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	for(UINT i = 0; i< m_DriveSerialList.size(); i++)
		delete m_DriveSerialList[i];
	m_DriveSerialList.clear();
	OnCancel();
}

