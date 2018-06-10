#if !defined(AFX_DEBUGGER_H__0FC70054_19F7_4DE7_8346_46DBDD0E7238__INCLUDED_)
#define AFX_DEBUGGER_H__0FC70054_19F7_4DE7_8346_46DBDD0E7238__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Debugger.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebugger dialog

class CDebugger : public CDialog
{
// Construction
public:
	CDebugger(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDebugger)
	enum { IDD = IDD_DEBUGGER };
	CComboBox	m_select_block;
	CComboBox	m_select_section;
	CEdit	m_block3_3;
	CEdit	m_block3_2;
	CEdit	m_block3_1;
	CEdit	m_block2;
	CEdit	m_block1;
	CEdit	m_block0;
	CEdit	m_password;
	CButton	m_readsection;
	CButton	m_readblock;
	CButton	m_writeblock;
	CButton	m_default_password;
	CEdit	m_edit_state;
	CEdit	m_edit_number;
	//}}AFX_DATA
	unsigned char* CStringToHex(CString psw);
	CString getState(int state);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebugger)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDebugger)
	afx_msg void OnStart();
	afx_msg void OnFind();
	afx_msg void OnDefaultPw();
	afx_msg void clearView();
	afx_msg void OnApw();
	afx_msg void OnBpw();
	afx_msg void OnReadblock();
	afx_msg void OnReadsection();
	afx_msg void OnWriteblock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUGGER_H__0FC70054_19F7_4DE7_8346_46DBDD0E7238__INCLUDED_)
