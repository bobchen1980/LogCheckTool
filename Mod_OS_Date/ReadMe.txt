================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : Mod_OS_Date Project Overview
===============================================================================

The application wizard has created this Mod_OS_Date application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your Mod_OS_Date application.

Mod_OS_Date.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

Mod_OS_Date.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CMod_OS_DateApp application class.

Mod_OS_Date.cpp
    This is the main application source file that contains the application
    class CMod_OS_DateApp.

Mod_OS_Date.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\Mod_OS_Date.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file Mod_OS_Date.rc.

res\Mod_OS_Date.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.


/////////////////////////////////////////////////////////////////////////////

The application wizard creates one dialog class:

Mod_OS_DateDlg.h, Mod_OS_DateDlg.cpp - the dialog
    These files contain your CMod_OS_DateDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's template is
    in Mod_OS_Date.rc, which can be edited in Microsoft Visual C++.


/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Mod_OS_Date.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

Mod_OS_Date.manifest
	Application manifest files are used by Windows XP to describe an applications 
	dependency on specific versions of Side-by-Side assemblies. The loader uses this 
	information to load the appropriate assembly from the assembly cache or private 
	from the application. The Application manifest  maybe included for redistribution 
	as an external .manifest file that is installed in the same folder as the application 
	executable or it may be included in the executable in the form of a resource. 
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need 
to redistribute the MFC DLLs. If your application is in a language 
other than the operating system's locale, you will also have to 
redistribute the corresponding localized resources MFC80XXX.DLL. 
For more information on both of these topics, please see the section on 
redistributing Visual C++ applications in MSDN documentation. 

/////////////////////////////////////////////////////////////////////////////
