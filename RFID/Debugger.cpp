// Debugger.cpp : implementation file
//

#include "stdafx.h"
#include "RFID.h"
#include "Debugger.h"
#include "ZM124U.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebugger dialog


CDebugger::CDebugger(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugger::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDebugger)
	//}}AFX_DATA_INIT
}


void CDebugger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebugger)
	DDX_Control(pDX, IDC_EDIT2, m_number);
	DDX_Control(pDX, IDC_EDIT1, m_state);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebugger, CDialog)
	//{{AFX_MSG_MAP(CDebugger)
	ON_BN_CLICKED(IDC_BUTTON1, Onopenbtn)
	ON_BN_CLICKED(IDC_BUTTON2, Oncardbtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugger message handlers

void CDebugger::Onopenbtn() 
{
	// TODO: Add your control notification handler code here
	int state = IDD_PowerOn();
	CString str = "";
	if(state==0) str = "¶Á¿¨³É¹¦";
	else str = "¶Á¿¨Ê§°Ü";
	m_state.SetWindowText(str);
}

void CDebugger::Oncardbtn() 
{
	// TODO: Add your control notification handler code here
	unsigned char uid[100];
	int uid_len;
	int code = find_14443(uid, &uid_len);
	if(code==0){
		CString str = "";
		CString number = "";
		number.Empty();
		for(int i=0; i<uid_len; i++)
		{
			str.Format(_T("%.2x"),uid[i]);
			number += str;
		}
		m_number.SetWindowText(number); 
	}
	else{
		m_number.SetWindowText("haha"); 
	}
}
