// RFIDDlg.h : header file
//

#if !defined(AFX_RFIDDLG_H__1A342A51_FF57_4B8C_A05E_DF42CBAECA4B__INCLUDED_)
#define AFX_RFIDDLG_H__1A342A51_FF57_4B8C_A05E_DF42CBAECA4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Debugger.h"
#include "AppDev.h"

/////////////////////////////////////////////////////////////////////////////
// CRFIDDlg dialog

class CRFIDDlg : public CDialog
{
// Construction
public:
	CRFIDDlg(CWnd* pParent = NULL);	// standard constructor
	// some added objects
	CDebugger m_MenuDebugger;
	CAppDev m_MenuAppDev;

// Dialog Data
	//{{AFX_DATA(CRFIDDlg)
	enum { IDD = IDD_RFID_DIALOG };
	CTabCtrl	m_MainMenu;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRFIDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRFIDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFIDDLG_H__1A342A51_FF57_4B8C_A05E_DF42CBAECA4B__INCLUDED_)
