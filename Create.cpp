// Create.cpp : implementation file
//

#include "stdafx.h"
#include "RFID.h"
#include "Create.h"
#include "MysqlHelper.h"
#include "ZM124U.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreate dialog


CString cid = "";

CCreate::CCreate(CWnd* pParent /*=NULL*/)
	: CDialog(CCreate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreate)
	//}}AFX_DATA_INIT
}


void CCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreate)
	DDX_Control(pDX, IDC_SEXUAL, m_sexual);
	DDX_Control(pDX, IDC_NAME, m_name);
	DDX_Control(pDX, IDC_GRADE, m_grade);
	DDX_Control(pDX, IDC_COLLEGE, m_college);
	DDX_Control(pDX, IDC_PASSWORD2, m_password2);
	DDX_Control(pDX, IDC_PASSWORD1, m_password1);
	DDX_Control(pDX, IDC_EDIT_NUMVER, m_edit_number);
	DDX_Control(pDX, IDC_EDIT_STATE, m_edit_state);
	DDX_Control(pDX, IDC_STUDENTID, m_studentid);
	DDX_Control(pDX, IDC_MONEY, m_money);
	DDX_Control(pDX, IDC_WRITE, m_write);
	DDX_Control(pDX, IDC_StartCard2, m_startcard2);
	DDX_Control(pDX, IDC_StartCard, m_startcard);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_FIND, m_find);
	DDX_Control(pDX, IDC_CLEAR, m_clear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreate, CDialog)
	//{{AFX_MSG_MAP(CCreate)
	ON_BN_CLICKED(IDC_WRITE, OnWrite)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreate message handlers

unsigned char* CCreate::CStringToHex(CString psw)
{
	if(psw.GetLength() % 2) psw = "0" + psw;
	unsigned char *buf = (unsigned char*)malloc(psw.GetLength() * sizeof(unsigned char));
	unsigned char *buff = (unsigned char*)malloc(psw.GetLength() * sizeof(unsigned char) / 2);
	psw.MakeUpper();
	for(int i = 0; i < psw.GetLength(); i++) {
		char ch = psw[i];
		if(ch > 0x40) buf[i] = (unsigned char)ch - 0x37;
		else buf[i] = (unsigned char)atoi(&ch);
	}
	int j;
	for(i = 0, j = 0; j < psw.GetLength() / 2;) {
		buff[j] = (unsigned char)(buf[i++] << 4);
		buff[j++] |= buf[i++];
	}
	return buff;
}

void CCreate::updatePSW(CString password) 
{
	// TODO: Add your control notification handler code here
	int cnt = 16;
	//����ת��
	unsigned char *buff = CStringToHex("FFFFFFFFFFFF");
	int block = 3;
	for(int page = 0; page < 16; page++) {
		try{
			unsigned char des_data[1024];
			int des_len,count=0;
			//�ȶ�
			int flag = read_block(page,block,0x0B,buff,des_data,&des_len);
			if(flag!=0)
			{
				MessageBox("д��ʧ��");
				continue;
			}

			CString msrc_data0,msrc_data1,msrc_data2;
			for(int k=0;k<des_len;k++)
			{
				CString s1;
				s1.Format("%02x",des_data[k]);
				if(k<6) msrc_data0 += s1;
				else if(k<10) msrc_data1 += s1;
				else msrc_data2 += s1;
			}

			//��д
			CString src_data0, src_data1, src_data2;
			src_data0 = password;
			src_data1 = msrc_data1;
			src_data2 = msrc_data2;

			//���ֶεĴ���
			if(src_data0.IsEmpty()) src_data0 = msrc_data0;
			if(src_data1.IsEmpty()) src_data1 = msrc_data1;
			if(src_data2.IsEmpty()) src_data2 = msrc_data2;

			CString data = src_data0 + src_data1 + src_data2; //�ַ���
			while(data.GetLength()<32) data.Insert(0,"0");

			//����ת��
			unsigned char *src_data = CStringToHex(data);

			int src_len = data.GetLength()/2; //����

			int state = write_block(block,page,0x0B,buff, src_data, src_len);
			if(state==0) cnt--;
		}
		catch(...) {
		}
	}
	if(!cnt) MessageBox("����д��ɹ���");
	else MessageBox("����δȫ��д�룡");
}

//��ʼ��
/*void CCreate::OnInit() 
{
	// TODO: Add your control notification handler code here
	CString yue;
	m_money.GetWindowText(yue);
	if(yue == "") MessageBox("�������ʼ����", "��ʾ"); 
	else {
		int page = m_select_section.GetCurSel();
		int block = m_select_block.GetCurSel();
		unsigned char *psw = CStringToHex("FFFFFFFFFFFF");
		long account;
		_stscanf(yue, _T("%ld"), &account);
		int state = write_account(page, block, 0x0B, psw, account);
		if(state == 0){
			MessageBox("��ʼ���ɹ���", "��ʾ"); 
			CString ss = "��ʼ��"+yue+"Ԫ  "+getTime()+"\r\n";
			writeFile(ss); //��¼
		}
		else MessageBox("��ʼ��ʧ�ܣ�", "��ʾ"); 
	}
}*/

void CCreate::OnWrite() 
{
	// TODO: Add your control notification handler code here
	CString sid = ""; m_studentid.GetWindowText(sid);
	CString pw1 = ""; m_password1.GetWindowText(pw1);
	CString pw2 = ""; m_password2.GetWindowText(pw2);
	CString sname = ""; m_name.GetWindowText(sname);
	CString sgrade = ""; m_grade.GetWindowText(sgrade);
	CString scollege = ""; m_college.GetWindowText(scollege);
	CString ssex = ""; m_sexual.GetWindowText(ssex);
	CString money = ""; m_money.GetWindowText(money);
	
	if(pw1 == pw2 && pw1 != "") {
		//updatePSW(pw1); //������д�뿨Ƭ��3��
		MysqlHelper helper;
		cardRecord rr(sid, cid, helper.GetHash(pw2), sname, ssex, sgrade, scollege, money, "0"); //�洢��ϣ�������봮;
		bool state = helper.MySQL_insert(rr); //����Ϣ�������ݿ�
		if(state) MessageBox("�����ɹ���", "��ʾ");
		else MessageBox("����ʧ�ܣ�", "��ʾ");
	}
	else if(pw1 != pw2) MessageBox("�������벻һ�£�", "��ʾ");
	else MessageBox("������������Ϣ��", "��ʾ");
	

	/* �������� ��ɾ*/
	/*MysqlHelper helper;
	//cardRecord rr("14352110","003F5D60","12306","˹����","Ů","16","��ѧԺ","50.6","0");
	//helper.MySQL_insert(rr);
	//helper.MySQL_update_money("3A4F12FF","33.66");
	cardRecord rr = helper.MySQL_query("15352256");
	m_studentid.SetWindowText(rr.stunum);
	m_money.SetWindowText(rr.money);*/
}

void CCreate::OnClear() 
{
	// TODO: Add your control notification handler code here
	CString sid = ""; m_studentid.GetWindowText(sid);
	CString pw1 = ""; m_password1.GetWindowText(pw1);
	if(pw1 == "") {
		MessageBox("���������Ա���룡", "��ʾ");
		return;
	}
	if(sid == "") {
		MessageBox("������ѧ����Ϣ��", "��ʾ");
		return;
	}
	if(pw1 == "FFFFF") {
		MysqlHelper helper;
		bool state = helper.MySQL_delete(sid);
		if(state) MessageBox("ɾ����Ƭ�ɹ���", "��ʾ");
		else MessageBox("ɾ����Ƭʧ�ܣ�", "��ʾ");
	}
	else MessageBox("����Ա�������", "��ʾ");

	/* �������� ��ɾ*/
	//MysqlHelper helper;
	//helper.MySQL_delete("14352109");
	//helper.MySQL_update_flag("15352256","1");
	//helper.MySQL_update_money("3A4F12FF","33.66");
}

CString CCreate::getState(int state) {
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


void CCreate::OnStart() 
{
	// TODO: Add your control notification handler code here
	int state = IDD_PowerOn();
	CString str = getState(state);
	m_edit_state.SetWindowText(str);
}



void CCreate::OnFind() 
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
	cid = res;
}
