#if !defined(AFX_TRANSFER_H__E53BA22F_A56A_4F1A_B025_8D31AA8BD6D4__INCLUDED_)
#define AFX_TRANSFER_H__E53BA22F_A56A_4F1A_B025_8D31AA8BD6D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Transfer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransfer dialog

class CTransfer : public CDialog
{
// Construction
public:
	CTransfer(CWnd* pParent = NULL);   // standard constructor
	bool login();
	CString cid;
// Dialog Data
	//{{AFX_DATA(CTransfer)
	enum { IDD = IDD_TRANSFER };
	CEdit	m_cardid;
	CEdit	m_sexual;
	CEdit	m_password;
	CEdit	m_studentid;
	CEdit	m_edit_number;
	CEdit	m_edit_state;
	CEdit	m_college;
	CEdit	m_grade;
	CEdit	m_name;
	CEdit	m_money;
	CEdit	m_lose;
	CButton	m_transfer;
	CButton	m_startcard2;
	CButton	m_startcard;
	CButton	m_start;
	CButton	m_find3;
	CButton	m_find2;
	CButton	m_find1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransfer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransfer)
	afx_msg void OnStart();
	afx_msg void OnFind1();
	afx_msg void OnFind2();
	afx_msg void OnFind3();
	afx_msg void OnTransfer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFER_H__E53BA22F_A56A_4F1A_B025_8D31AA8BD6D4__INCLUDED_)
