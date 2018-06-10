#if !defined(AFX_FIND_H__F3AA0374_5031_4ECA_8491_89CF1829F7F6__INCLUDED_)
#define AFX_FIND_H__F3AA0374_5031_4ECA_8491_89CF1829F7F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Find.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFind dialog

class CFind : public CDialog
{
// Construction
public:
	CFind(CWnd* pParent = NULL);   // standard constructor
	bool login();
// Dialog Data
	//{{AFX_DATA(CFind)
	enum { IDD = IDD_FIND };
	CEdit	m_lose;
	CEdit	m_studentid;
	CEdit	m_sexual;
	CEdit	m_name;
	CEdit	m_money;
	CEdit	m_grade;
	CEdit	m_college;
	CEdit	m_password;
	CEdit	m_edit_number;
	CButton	m_startcard2;
	CButton	m_startcard;
	CButton	m_lose_s;
	CButton	m_lose_j;
	CButton	m_find2;
	CButton	m_find1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFind)
	afx_msg void OnFind1();
	afx_msg void OnLoseS();
	afx_msg void OnLoseJ();
	afx_msg void OnFind2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIND_H__F3AA0374_5031_4ECA_8491_89CF1829F7F6__INCLUDED_)
