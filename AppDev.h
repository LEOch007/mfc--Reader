#if !defined(AFX_APPDEV_H__D089FA15_E521_41B7_B3A2_EA09FEE0D0B9__INCLUDED_)
#define AFX_APPDEV_H__D089FA15_E521_41B7_B3A2_EA09FEE0D0B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppDev.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppDev dialog

class CAppDev : public CDialog
{
// Construction
public:
	CAppDev(CWnd* pParent = NULL);   // standard constructor
	bool is_lost();
	bool is_old_card();
	CString getCardID();
// Dialog Data
	//{{AFX_DATA(CAppDev)
	enum { IDD = IDD_APPDEV };
	CButton	m_yue_search;
	CEdit	m_yue;
	CButton	m_sub_money;
	CEdit	m_state;
	CComboBox	m_select_section;
	CButton	m_search;
	CEdit	m_record;
	CEdit	m_money2;
	CEdit	m_money1;
	CButton	m_init;
	CButton	m_clear;
	CComboBox	m_select_block;
	CButton	m_add_money;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppDev)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppDev)
	afx_msg void OnInit();
	afx_msg void OnYuesearch();
	afx_msg void OnAddmoney();
	afx_msg void OnSubmoney();
	afx_msg void OnClear();
	afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	unsigned char* CStringToHex(CString psw);
	void writeFile(CString s);
	CString getTime();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPDEV_H__D089FA15_E521_41B7_B3A2_EA09FEE0D0B9__INCLUDED_)
