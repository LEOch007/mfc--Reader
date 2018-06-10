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

#define N_BLOCK 4
#define N_SECTION 16
#define LEN_BLOCK3_1 12
#define LEN_BLOCK3_2 8
#define LEN_BLOCK3_3 12
unsigned char pswtype;


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
	DDX_Control(pDX, IDC_BLOCK, m_select_block);
	DDX_Control(pDX, IDC_SECTION, m_select_section);
	DDX_Control(pDX, IDC_BLOCK3_3, m_block3_3);
	DDX_Control(pDX, IDC_BLOCK3_2, m_block3_2);
	DDX_Control(pDX, IDC_BLOCK3_1, m_block3_1);
	DDX_Control(pDX, IDC_BLOCK2, m_block2);
	DDX_Control(pDX, IDC_BLOCK1, m_block1);
	DDX_Control(pDX, IDC_BLOCK0, m_block0);
	DDX_Control(pDX, IDC_EDIT_PW, m_password);
	DDX_Control(pDX, IDC_READSECTION, m_readsection);
	DDX_Control(pDX, IDC_READBLOCK, m_readblock);
	DDX_Control(pDX, IDC_WRITEBLOCK, m_writeblock);
	DDX_Control(pDX, IDC_DEFAULT_PW, m_default_password);
	DDX_Control(pDX, IDC_EDIT_STATE, m_edit_state);
	DDX_Control(pDX, IDC_EDIT_NUMVER, m_edit_number);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebugger, CDialog)
	//{{AFX_MSG_MAP(CDebugger)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_DEFAULT_PW, OnDefaultPw)
	ON_BN_CLICKED(IDC_APW, OnApw)
	ON_BN_CLICKED(IDC_BPW, OnBpw)
	ON_BN_CLICKED(IDC_READBLOCK, OnReadblock)
	ON_BN_CLICKED(IDC_READSECTION, OnReadsection)
	ON_BN_CLICKED(IDC_WRITEBLOCK, OnWriteblock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugger message handlers


CString CDebugger::getState(int state) {
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

void CDebugger::OnStart() 
{
	// TODO: Add your control notification handler code here
	int state = IDD_PowerOn();
	CString str = getState(state);
	m_edit_state.SetWindowText(str);
}

void CDebugger::OnFind() 
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

}

unsigned char* CDebugger::CStringToHex(CString psw)
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

void CDebugger::OnDefaultPw() 
{
	// TODO: Add your control notification handler code here
	m_password.SetWindowText("FFFFFFFFFFFF");

}
void CDebugger::clearView()
{
	m_block0.SetWindowText("");
	m_block1.SetWindowText("");
	m_block2.SetWindowText("");
	m_block3_1.SetWindowText("");
	m_block3_2.SetWindowText("");
	m_block3_3.SetWindowText("");
}

void CDebugger::OnApw() 
{
	// TODO: Add your control notification handler code here
	pswtype = 0x0A;
}

void CDebugger::OnBpw() 
{
	// TODO: Add your control notification handler code here
	pswtype = 0x0B;
}

void CDebugger::OnReadblock() 
{
	// TODO: Add your control notification handler code here
	
	//�����ʾ
	clearView(); 
	
	//��ȡ��������
	CString psw = "";
	m_password.GetWindowText(psw);
	
	//�ж��Ƿ�Ϊ��
	if(psw=="")
	{
		::MessageBox(NULL,_T("���벻��Ϊ��"),_T("����"),MB_OK);
	}
	else
	{
		//����ת��
		unsigned char *buff = CStringToHex(psw);
		
		//��ȡ���� ���
		int page = m_select_section.GetCurSel();
		int block = m_select_block.GetCurSel();

		//�ж��Ƿ�ѡ��
		if((page==-1)||(block==-1))
		{
			::MessageBox(NULL,_T("��ѡ�������Ϳ��"),_T("����"),MB_OK);
		}
		else //��ѡ��
		{
			//����
			unsigned char des_data[100];
			int des_len;
			int state = read_block(page, block, pswtype, buff, des_data, &des_len);
			
			//��ʾ������Ϣ
			CString str;
			if(state == 0) {
				if(block != 3) {
					for(int k = 0; k < des_len; k++) {
						CString s1;
						s1.Format("%02x", des_data[k]);
						str += s1;
					}
					if(block == 0) m_block0.SetWindowText(str);
					else if(block == 1) m_block1.SetWindowText(str);
					else if(block == 2) m_block2.SetWindowText(str);
				}
				else {
					for(int k = 0; k < des_len; k++) {
						CString s1;
						s1.Format("%02x", des_data[k]);
						str += s1;
						if(k == 5) {
							m_block3_1.SetWindowText(str);
							str.Empty();
						}
						if(k == 9) {
							m_block3_2.SetWindowText(str);
							str.Empty();
						}
					}
					m_block3_3.SetWindowText(str);
				}
			}
			else {
				CString temp = getState(state);
				m_block0.SetWindowText(temp);
			}
		}
	}
}

void CDebugger::OnReadsection() 
{
	// TODO: Add your control notification handler code here
	
	//�����ʾ
	clearView(); 
	
	//��ȡ��������
	CString psw = "";
	m_password.GetWindowText(psw);
	
	//�ж��Ƿ�Ϊ��
	if(psw=="")
	{
		::MessageBox(NULL,_T("���벻��Ϊ��"),_T("����"),MB_OK);
	}
	else
	{
		//����ת��
		unsigned char *buff = CStringToHex(psw);
		
		int page = m_select_section.GetCurSel();
		//�ж��Ƿ�ѡ��
		if((page==-1))
		{
			::MessageBox(NULL,_T("��ѡ�������Ϳ��"),_T("����"),MB_OK);
		}
		else //��ѡ��
		{
			//����������ȡ������Ϣ
			unsigned char des_data[100];
			int des_len;
		
			//��ʾ��Ϣ
			//CString shannum;
			//shannum.Format("%d",i);
			//::MessageBox(NULL,_T("��"+shannum+"��"),_T("����"),MB_OK); 

			for(int j=0;j<=3;j++) //��
			{
				int state = read_block(page, j, pswtype, buff, des_data, &des_len);
				//��ʾ������Ϣ
				CString str;
				if(state == 0) {
					if(j != 3) {
						for(int k = 0; k < des_len; k++) {
							CString s1;
							s1.Format("%02x", des_data[k]);
							str += s1;
						}
						if(j == 0) m_block0.SetWindowText(str);
						else if(j == 1) m_block1.SetWindowText(str);
						else if(j == 2) m_block2.SetWindowText(str);
					}
					else {
						for(int k = 0; k < des_len; k++) {
							CString s1;
							s1.Format("%02x", des_data[k]);
							str += s1;
							if(k == 5) {
								m_block3_1.SetWindowText(str);
								str.Empty();
							}
							if(k == 9) {
								m_block3_2.SetWindowText(str);
								str.Empty();
							}
						}
						m_block3_3.SetWindowText(str);
					}
				}
				else {
					CString temp = getState(state);
					m_block0.SetWindowText(temp);
				}

			}

		}
		
	}
}

void CDebugger::OnWriteblock() 
{
	// TODO: Add your control notification handler code here
	
	//��ȡ��������
	CString psw = "";
	m_password.GetWindowText(psw);

	//�ж��Ƿ�Ϊ��
	if(psw=="")
	{
		::MessageBox(NULL,_T("���벻��Ϊ��"),_T("����"),MB_OK);
	}
	else
	{
		//����ת��
		unsigned char *buff = CStringToHex(psw);
		
		//��ȡ���� ���
		int page = m_select_section.GetCurSel();
		int block = m_select_block.GetCurSel();

		//�ж��Ƿ�ѡ��
		if((page==-1)||(block==-1))
		{
			::MessageBox(NULL,_T("��ѡ�������Ϳ��"),_T("����"),MB_OK);
		}
		else
		{
			/* ��3 ���ֶ�*/
			if(block==3)
			{
				unsigned char des_data[1024];
				int des_len,count=0;
				//�ȶ�
				int flag = read_block(page,block,pswtype,buff,des_data,&des_len);
				if(flag!=0)
				{
					MessageBox("д��ʧ��");
					return;
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
				m_block3_1.GetWindowText(src_data0); //��ȡ����
				m_block3_2.GetWindowText(src_data1);
				m_block3_3.GetWindowText(src_data2);

				//���ֶεĴ���
				if(src_data0.IsEmpty()) src_data0 = msrc_data0;
				if(src_data1.IsEmpty()) src_data1 = msrc_data1;
				if(src_data2.IsEmpty()) src_data2 = msrc_data2;

				CString data = src_data0 + src_data1 + src_data2; //�ַ���
				while(data.GetLength()<32) data.Insert(0,"0");

				//����ת��
				unsigned char *src_data = CStringToHex(data);

				int src_len = data.GetLength()/2; //����

				int state = write_block(block,page,pswtype,buff, src_data, src_len);
				if(state==0) MessageBox("�ɹ�д��");
			}
			else
			{
				//��д
				CString data;
				if(block==0)m_block0.GetWindowText(data); //��ȡ����
				if(block==1)m_block1.GetWindowText(data);
				if(block==2)m_block2.GetWindowText(data);

				//���ֶδ���
				if(data.IsEmpty()) {
					MessageBox("������Ҫ������ݣ�", "��ʾ");
					return;
				}
				//����32λ��0
				while(data.GetLength()<32) data.Insert(0,"0");
				
				//����ת��
				unsigned char *src_data = CStringToHex(data);

				int src_len = data.GetLength()/2; //����

				int state = write_block(block, page, pswtype, buff, src_data, src_len);
				if(state==0) MessageBox("�ɹ�д��");
			}
		}
	}
}
