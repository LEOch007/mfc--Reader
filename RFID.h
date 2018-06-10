// RFID.h : main header file for the RFID application
//

#if !defined(AFX_RFID_H__23DD5102_D9DD_48D6_859B_90F34DA6BABD__INCLUDED_)
#define AFX_RFID_H__23DD5102_D9DD_48D6_859B_90F34DA6BABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRFIDApp:
// See RFID.cpp for the implementation of this class
//

class CRFIDApp : public CWinApp
{
public:
	CRFIDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRFIDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRFIDApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFID_H__23DD5102_D9DD_48D6_859B_90F34DA6BABD__INCLUDED_)
