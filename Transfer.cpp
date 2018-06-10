// Transfer.cpp : implementation file
//

#include "stdafx.h"
#include "RFID.h"
#include "Transfer.h"
#include "ZM124U.h"
#include "MysqlHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransfer dialog



CTransfer::CTransfer(CWnd* pParent /*=NULL*/)
	: CDialog(CTransfer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransfer)
	//}}AFX_DATA_INIT
}


void CTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransfer)
	DDX_Control(pDX, IDC_CARDID, m_cardid);
	DDX_Control(pDX, IDC_SEXUAL, m_sexual);
	DDX_Control(pDX, IDC_PASSWORD1, m_password);
	DDX_Control(pDX, IDC_EDIT_NUMVER2, m_studentid);
	DDX_Control(pDX, IDC_EDIT_NUMVER, m_edit_number);
	DDX_Control(pDX, IDC_EDIT_STATE, m_edit_state);
	DDX_Control(pDX, IDC_COLLEGE, m_college);
	DDX_Control(pDX, IDC_GRADE, m_grade);
	DDX_Control(pDX, IDC_NAME, m_name);
	DDX_Control(pDX, IDC_MONEY, m_money);
	DDX_Control(pDX, IDC_LOSE, m_lose);
	DDX_Control(pDX, IDC_TRANSFER, m_transfer);
	DDX_Control(pDX, IDC_StartCard2, m_startcard2);
	DDX_Control(pDX, IDC_StartCard, m_startcard);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_FIND3, m_find3);
	DDX_Control(pDX, IDC_FIND2, m_find2);
	DDX_Control(pDX, IDC_FIND1, m_find1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransfer, CDialog)
	//{{AFX_MSG_MAP(CTransfer)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_FIND1, OnFind1)
	ON_BN_CLICKED(IDC_FIND2, OnFind2)
	ON_BN_CLICKED(IDC_FIND3, OnFind3)
	ON_BN_CLICKED(IDC_TRANSFER, OnTransfer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransfer message handlers

CString getState(int state) {
	CString res = "";
	switch(state) {
	case 0:
		 res = "ִ�гɹ�";
		 break;
	case -1:
		 res = "��Ƭ���Ͳ���";
		 break;
	case -2:
		 res = "�޿�";
		 break;
	case -3:
		 res = "�п�δ�ϵ�";
		 break;
	case -4:
		 res = "��Ƭ��Ӧ��";
		 break;
	case -5:
		 res = "BCCУ�����";
		 break;
	case -6:
		 res = "���ճ�ʱ";
		 break;
	case -7:
		 res = "ִ��ʧ��";
		 break;
	case -8:
		 res = "��Ƭλ�ô���";
		 break;
	case -9:
		 res = "����ʧ��";
		 break;
	case -10:
		 res = "�޿�";
		 break;
	case -11:
		 res = "���������Ӵ�";
		 break;
	case -12:
		 res = "δ��������";
		 break;
	case -13:
		 res = "��֧�ָ�����";
		 break;
	case -14:
		 res = "���������";
		 break;
	case -15:
		 res = "��ϢУ��ͳ���";
		 break;
	case -16:
		 res = "��Ƭ�ϵ�ʧ��";
		 break;
	case -17:
		 res = "��Ƭ��λʧ��";
		 break;
	case -18:
		 res = "��Ƭ�µ�ʧ��";
		 break;
	default:
		break;
	}
	return res;
}


void CTransfer::OnStart() 
{
	// TODO: Add your control notification handler code here
	int state = IDD_PowerOn();
	CString str = getState(state);
	m_edit_state.SetWindowText(str);
}

void CTransfer::OnFind1() 
{
	// TODO: Add your control notification handler code here
	unsigned char uid[10];
	int uid_len;
	int state = find_14443(uid, &uid_len);

	// State
	CString str = getState(state);
	m_edit_state.SetWindowText(str);

	// Number
	CString number;
	CString res;
	for(int i = 0; i < uid_len; i++) {
		number.Format(_T("%.2x"), uid[i]);
		res += number;
	}
	m_edit_number.SetWindowText(res);
	this->cid = res;
}

bool CTransfer::login()
{
	CString sid = ""; m_studentid.GetWindowText(sid);
	CString pw = ""; m_password.GetWindowText(pw);
	MysqlHelper helper;
	cardRecord info = helper.MySQL_query(sid);

	pw = helper.GetHash(pw);

	/*if(info) {
		MessageBox("�û������ڣ�", "��ʾ");
		return false;
	}*/
	/*if(info.flag == "1") {
		MessageBox("�ÿ��ѹ�ʧ��", "��ʾ");
		return false;
	}*/
	if(info.pwd == pw) return true;
	else {
		MessageBox("��¼ʧ�ܣ�", "��ʾ");
		return false;
	}
}

void CTransfer::OnFind2() 
{
	// TODO: Add your control notification handler code here
	if(login()) {
		CString sid = ""; m_studentid.GetWindowText(sid);
		MysqlHelper helper;
		cardRecord info = helper.MySQL_query(sid);
		CString lose = info.flag;
		m_lose.SetWindowText(lose);
	}
}

void CTransfer::OnFind3() 
{
	// TODO: Add your control notification handler code here
	if(login()) {
		CString sid = ""; m_studentid.GetWindowText(sid);
		MysqlHelper helper;
		cardRecord info = helper.MySQL_query(sid);
		m_name.SetWindowText(info.stuname);
		m_cardid.SetWindowText(info.cardnum);
		m_sexual.SetWindowText(info.stusex);
		m_college.SetWindowText(info.college);
		m_money.SetWindowText(info.money);
		m_grade.SetWindowText(info.grade);
	}
}

void CTransfer::OnTransfer() 
{
	// TODO: Add your control notification handler code here
	if(login()) {
		CString sid = ""; m_studentid.GetWindowText(sid);
		MysqlHelper helper;
		cardRecord info = helper.MySQL_query(sid);
		m_edit_number.GetWindowText(info.cardnum);
		info.flag = "0";
		if(info.cardnum == "") {
			MessageBox("δ��⵽��Ƭ��", "��ʾ");
			return;
		}
		bool state = helper.MySQL_delete(sid);
		state = helper.MySQL_insert(info);
		if(state) MessageBox("��Ƭ��Ϣת�Ƴɹ���", "��ʾ");
		else MessageBox("��Ƭ��Ϣת��ʧ�ܣ�", "��ʾ");
	}
}
