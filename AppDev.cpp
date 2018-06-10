// AppDev.cpp : implementation file
//

#include "stdafx.h"
#include "RFID.h"
#include "AppDev.h"
#include "ZM124U.h"
#include "MysqlHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppDev dialog


CAppDev::CAppDev(CWnd* pParent /*=NULL*/)
	: CDialog(CAppDev::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppDev)
	//}}AFX_DATA_INIT
}


void CAppDev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppDev)
	DDX_Control(pDX, IDC_YUESEARCH, m_yue_search);
	DDX_Control(pDX, IDC_YUE, m_yue);
	DDX_Control(pDX, IDC_SUBMONEY, m_sub_money);
	DDX_Control(pDX, IDC_STATE, m_state);
	DDX_Control(pDX, IDC_SECTION, m_select_section);
	DDX_Control(pDX, IDC_SEARCH, m_search);
	DDX_Control(pDX, IDC_RECORD, m_record);
	DDX_Control(pDX, IDC_MONEY2, m_money2);
	DDX_Control(pDX, IDC_MONEY1, m_money1);
	DDX_Control(pDX, IDC_INIT, m_init);
	DDX_Control(pDX, IDC_CLEAR, m_clear);
	DDX_Control(pDX, IDC_BLOCK, m_select_block);
	DDX_Control(pDX, IDC_ADDMONEY, m_add_money);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppDev, CDialog)
	//{{AFX_MSG_MAP(CAppDev)
	ON_BN_CLICKED(IDC_INIT, OnInit)
	ON_BN_CLICKED(IDC_YUESEARCH, OnYuesearch)
	ON_BN_CLICKED(IDC_ADDMONEY, OnAddmoney)
	ON_BN_CLICKED(IDC_SUBMONEY, OnSubmoney)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppDev message handlers

unsigned char* CAppDev::CStringToHex(CString psw)
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

//初始化
void CAppDev::OnInit() 
{
	// TODO: Add your control notification handler code here
	CString yue;
	m_yue.GetWindowText(yue);
	if(yue == "") MessageBox("请输入初始化金额！", "提示"); 
	else {
		int page = m_select_section.GetCurSel();
		int block = m_select_block.GetCurSel();
		unsigned char *psw = CStringToHex("FFFFFFFFFFFF");
		long account;
		_stscanf(yue, _T("%ld"), &account);
		int state = write_account(page, block, 0x0B, psw, account);
		if(state == 0){
			MessageBox("初始化成功！", "提示"); 
			CString ss = "初始化"+yue+"元  "+getTime()+"\r\n";
			writeFile(ss); //记录
		}
		else MessageBox("初始化失败！", "提示"); 
	}
}

//查询
void CAppDev::OnYuesearch() 
{
	// TODO: Add your control notification handler code here
	int page = m_select_section.GetCurSel();
	int block = m_select_block.GetCurSel();
	unsigned char *psw = CStringToHex("FFFFFFFFFFFF");
	long account;
	int state = read_account(page, block, 0x0B, psw, &account);
	if(state == 0) {
		CString yue;
		yue.Format("%ld", account);
		m_yue.SetWindowText(yue);
	}
	else MessageBox("余额查询失败！", "提示"); 
}

CString CAppDev::getCardID()
{
	unsigned char uid[10];
	int uid_len;
	int state = find_14443(uid, &uid_len);

	// Number
	CString number;
	CString res;
	for(int i = 0; i < uid_len; i++) {
		number.Format(_T("%.2x"), uid[i]);
		res += number;
	}
	return res;
}

bool CAppDev::is_lost() 
{
	// TODO: Add your control notification handler code here
	CString res = getCardID();
	MysqlHelper helper;
	cardRecord info = helper.MySQL_querybycard(res);
	if(info.flag == '1') return true;
	else return false;
}

bool CAppDev::is_old_card() 
{
	// TODO: Add your control notification handler code here
	CString res = getCardID();
	MysqlHelper helper;
	cardRecord info = helper.MySQL_querybycard(res);
	if(info.cardnum == "") return true;
	else return false;
}

//充值
void CAppDev::OnAddmoney() 
{
	// TODO: Add your control notification handler code here
	if(is_lost()) {
		MessageBox("该卡已挂失！", "提示"); 
	}
	else if(is_old_card()) {
		MessageBox("未查询到该卡信息！", "提示"); 
	}
	else {
		int page = m_select_section.GetCurSel();
		int block = m_select_block.GetCurSel();
		CString money;
		m_money1.GetWindowText(money);
		long addAccount;
		_stscanf(money, _T("%ld"), &addAccount);
		unsigned char *psw = CStringToHex("FFFFFFFFFFFF");
		int state = add_account(page, block, 0x0B, psw, addAccount);
		if(state == 0){ ////////////////////////////
			CString res = getCardID();
			MysqlHelper helper;
			cardRecord info = helper.MySQL_querybycard(res);
			float cur_money = atof(info.money);
			cur_money += addAccount;
			CString mm;
			mm.Format(_T("%f"),cur_money);
			helper.MySQL_update_money(res, mm);

			MessageBox("充值成功！", "提示");
			CString ss = "充值"+money+"元  "+getTime()+"\r\n";
			writeFile(ss); //记录
		}
		else MessageBox("充值失败！", "提示");
	}
}

//消费
void CAppDev::OnSubmoney() 
{
	if(is_lost()) {
		MessageBox("该卡已挂失！", "提示"); 
	}
	else {
		// TODO: Add your control notification handler code here
		int page = m_select_section.GetCurSel();
		int block = m_select_block.GetCurSel();
		CString money;
		m_money2.GetWindowText(money);
		long subAccount;
		_stscanf(money, _T("%ld"), &subAccount);
		unsigned char *psw = CStringToHex("FFFFFFFFFFFF");

		//判断是否足够支付;
		long account;
		int state = read_account(page, block, 0x0B, psw, &account);
		if(account < subAccount) {
			MessageBox("余额不足！", "提示"); 
			return;
		}

		state = sub_account(page, block, 0x0B, psw, subAccount);
		if(state == 0){
			CString res = getCardID();
			MysqlHelper helper;
			cardRecord info = helper.MySQL_querybycard(res);
			float cur_money = atof(info.money);
			cur_money -= subAccount;
			CString mm;
			mm.Format(_T("%f"),cur_money);
			helper.MySQL_update_money(res, mm);

			MessageBox("消费成功！", "提示"); 
			CString ss = "消费"+money+"元  "+getTime()+"\r\n";
			writeFile(ss); //记录
		}
		else MessageBox("消费失败！", "提示"); 
	}
}

//清空历史记录
void CAppDev::OnClear() 
{
	// TODO: Add your control notification handler code here
	CFile file("record.txt",CFile::modeCreate | CFile::modeReadWrite);
	file.Close();
	m_record.SetWindowText("");
}

//查询历史记录
void CAppDev::OnSearch() 
{
	// TODO: Add your control notification handler code here
	CFile file("record.txt",CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate); //打开文件
	int len = file.GetLength();
	char s[1000000];
	s[len] = 0;
	file.SeekToBegin(); //指针移到文件开头
	file.Read(s,len);
	m_record.SetWindowText(s);
	file.Close();
}

//写历史记录
void CAppDev::writeFile(CString s){
	CFile file("record.txt",CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate); //打开文件	
	file.SeekToEnd(); //指针移到文件末尾
	file.Write(s,s.GetLength()); //写入内容
	file.Close();
}

//获取系统时间
CString CAppDev::getTime(){
	CTime tm;
	tm = CTime::GetCurrentTime();
	CString stime = tm.Format("%Y年%m月%d日%X");
	return stime;
}