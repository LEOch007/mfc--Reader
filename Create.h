#if !defined(AFX_CREATE_H__B15DDF66_D84F_4DDA_8123_9CA9C34D3A43__INCLUDED_)
#define AFX_CREATE_H__B15DDF66_D84F_4DDA_8123_9CA9C34D3A43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Create.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreate dialog

class CCreate : public CDialog
{
// Construction
public:
	CCreate(CWnd* pParent = NULL);   // standard constructor
	void updatePSW(CString password);
	unsigned char* CStringToHex(CString psw);
// Dialog Data
	//{{AFX_DATA(CCreate)
	enum { IDD = IDD_CREATE };
	CEdit	m_sexual;
	CEdit	m_name;
	CEdit	m_grade;
	CEdit	m_college;
	CEdit	m_password2;
	CEdit	m_password1;
	CEdit	m_edit_number;
	CEdit	m_edit_state;
	CEdit	m_studentid;
	CEdit	m_money;
	CButton	m_write;
	CButton	m_startcard2;
	CButton	m_startcard;
	CButton	m_start;
	CButton	m_find;
	CButton	m_clear;
	//}}AFX_DATA
	CString getState(int state);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreate)
	afx_msg void OnWrite();
	afx_msg void OnClear();
	afx_msg void OnStart();
	afx_msg void OnFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATE_H__B15DDF66_D84F_4DDA_8123_9CA9C34D3A43__INCLUDED_)
