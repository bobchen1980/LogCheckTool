// Mod_OS_DateDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CMod_OS_DateDlg dialog
class CMod_OS_DateDlg : public CDialog
{
// Construction
public:
	CMod_OS_DateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MOD_OS_DATE_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonmod();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	int ReadPhysicalDriveInNTUsingSmart();
public:
	CListCtrl ctlOSRecord;
	CEdit ceInstall;
	CDateTimeCtrl ceDateTime;
public:
	void GetDiskSerial(void);
	void GetAllLocalAdapterMacAddr(void);
public:
	CListCtrl ctlDiskNO;
public:
	CListCtrl ctlMACList;
public:
	void GetOSStartInfo(void);
public:
	afx_msg void OnBnClickedCancel();
};
