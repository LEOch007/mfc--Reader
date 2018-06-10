// Find.cpp : implementation file
//

#include "stdafx.h"
#include "RFID.h"
#include "Find.h"
#include "ZM124U.h"
#include "MysqlHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFind dialog


CFind::CFind(CWnd* pParent /*=NULL*/)
	: CDialog(CFind::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFind)
	//}}AFX_DATA_INIT
}


void CFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFind)
	DDX_Control(pDX, IDC_LOSE, m_lose);
	DDX_Control(pDX, IDC_STUDENTID, m_studentid);
	DDX_Control(pDX, IDC_SEXUAL, m_sexual);
	DDX_Control(pDX, IDC_NAME, m_name);
	DDX_Control(pDX, IDC_MONEY, m_money);
	DDX_Control(pDX, IDC_GRADE, m_grade);
	DDX_Control(pDX, IDC_COLLEGE, m_college);
	DDX_Control(pDX, IDC_PASSWORD1, m_password);
	DDX_Control(pDX, IDC_EDIT_NUMVER, m_edit_number);
	DDX_Control(pDX, IDC_StartCard2, m_startcard2);
	DDX_Control(pDX, IDC_StartCard, m_startcard);
	DDX_Control(pDX, IDC_LOSE_S, m_lose_s);
	DDX_Control(pDX, IDC_LOSE_J, m_lose_j);
	DDX_Control(pDX, IDC_FIND2, m_find2);
	DDX_Control(pDX, IDC_FIND1, m_find1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFind, CDialog)
	//{{AFX_MSG_MAP(CFind)
	ON_BN_CLICKED(IDC_FIND1, OnFind1)
	ON_BN_CLICKED(IDC_LOSE_S, OnLoseS)
	ON_BN_CLICKED(IDC_LOSE_J, OnLoseJ)
	ON_BN_CLICKED(IDC_FIND2, OnFind2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFind message handlers

bool CFind::login()
{
	CString sid = ""; m_edit_number.GetWindowText(sid);
	CString pw = ""; m_password.GetWindowText(pw);
	MysqlHelper helper;
	cardRecord info = helper.MySQL_query(sid);

	pw = helper.GetHash(pw);
	/*if(info) {
		MessageBox("用户不存在！", "提示");
		return false;
	}*/
	/*if(info.flag == "1") {
		MessageBox("该卡已挂失！", "提示");
		return false;
	}*/
	if(info.pwd == pw) return true;
	else {
		MessageBox("登录失败！", "提示");
		return false;
	}
}

void CFind::OnFind1() 
{
	// TODO: Add your control notification handler code here
	if(login()) {
		CString sid = ""; m_edit_number.GetWindowText(sid);
		MysqlHelper helper;
		cardRecord info = helper.MySQL_query(sid);
		CString lose = info.flag;
		m_lose.SetWindowText(lose);
	}
}

void CFind::OnLoseS() 
{
	// TODO: Add your control notification handler code here
	if(login()) {
		CString sid = ""; m_edit_number.GetWindowText(sid);
		MysqlHelper helper;
		bool state = helper.MySQL_update_flag(sid, "1");
		if(state) MessageBox("挂失成功！", "提示");
		else MessageBox("挂失失败！", "提示");
	}
}

void CFind::OnLoseJ() 
{
	// TODO: Add your control notification handler code here
	if(login()) {
		CString sid = ""; m_edit_number.GetWindowText(sid);
		MysqlHelper helper;
		bool state = helper.MySQL_update_flag(sid, "0");
		if(state) MessageBox("挂失取消成功！", "提示");
		else MessageBox("挂失取消失败！", "提示");
	}
}

void CFind::OnFind2() 
{
	// TODO: Add your control notification handler code here
	if(login()) {
		CString sid = ""; m_edit_number.GetWindowText(sid);
		MysqlHelper helper;
		cardRecord info = helper.MySQL_query(sid);
		m_name.SetWindowText(info.stuname);
		m_studentid.SetWindowText(info.cardnum);
		m_sexual.SetWindowText(info.stusex);
		m_college.SetWindowText(info.college);
		m_money.SetWindowText(info.money);
		m_grade.SetWindowText(info.grade);
	}
}
