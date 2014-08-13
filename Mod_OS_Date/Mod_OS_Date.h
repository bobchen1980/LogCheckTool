// Mod_OS_Date.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMod_OS_DateApp:
// See Mod_OS_Date.cpp for the implementation of this class
//

class CMod_OS_DateApp : public CWinApp
{
public:
	CMod_OS_DateApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMod_OS_DateApp theApp;