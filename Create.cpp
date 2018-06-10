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
	//类型转换
	unsigned char *buff = CStringToHex("FFFFFFFFFFFF");
	int block = 3;
	for(int page = 0; page < 16; page++) {
		try{
			unsigned char des_data[1024];
			int des_len,count=0;
			//先读
			int flag = read_block(page,block,0x0B,buff,des_data,&des_len);
			if(flag!=0)
			{
				MessageBox("写块失败");
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

			//再写
			CString src_data0, src_data1, src_data2;
			src_data0 = password;
			src_data1 = msrc_data1;
			src_data2 = msrc_data2;

			//空字段的处理
			if(src_data0.IsEmpty()) src_data0 = msrc_data0;
			if(src_data1.IsEmpty()) src_data1 = msrc_data1;
			if(src_data2.IsEmpty()) src_data2 = msrc_data2;

			CString data = src_data0 + src_data1 + src_data2; //字符串
			while(data.GetLength()<32) data.Insert(0,"0");

			//类型转换
			unsigned char *src_data = CStringToHex(data);

			int src_len = data.GetLength()/2; //长度

			int state = write_block(block,page,0x0B,buff, src_data, src_len);
			if(state==0) cnt--;
		}
		catch(...) {
		}
	}
	if(!cnt) MessageBox("密码写入成功！");
	else MessageBox("密码未全部写入！");
}

//初始化
/*void CCreate::OnInit() 
{
	// TODO: Add your control notification handler code here
	CString yue;
	m_money.GetWindowText(yue);
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
		//updatePSW(pw1); //将密码写入卡片块3中
		MysqlHelper helper;
		cardRecord rr(sid, cid, helper.GetHash(pw2), sname, ssex, sgrade, scollege, money, "0"); //存储哈希过的密码串;
		bool state = helper.MySQL_insert(rr); //将信息插入数据库
		if(state) MessageBox("创建成功！", "提示");
		else MessageBox("创建失败！", "提示");
	}
	else if(pw1 != pw2) MessageBox("密码输入不一致！", "提示");
	else MessageBox("请输入密码信息！", "提示");
	

	/* 测试样例 可删*/
	/*MysqlHelper helper;
	//cardRecord rr("14352110","003F5D60","12306","斯嘉丽","女","16","法学院","50.6","0");
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
		MessageBox("请输入管理员密码！", "提示");
		return;
	}
	if(sid == "") {
		MessageBox("请输入学号信息！", "提示");
		return;
	}
	if(pw1 == "FFFFF") {
		MysqlHelper helper;
		bool state = helper.MySQL_delete(sid);
		if(state) MessageBox("删除卡片成功！", "提示");
		else MessageBox("删除卡片失败！", "提示");
	}
	else MessageBox("管理员密码错误！", "提示");

	/* 测试样例 可删*/
	//MysqlHelper helper;
	//helper.MySQL_delete("14352109");
	//helper.MySQL_update_flag("15352256","1");
	//helper.MySQL_update_money("3A4F12FF","33.66");
}

CString CCreate::getState(int state) {
	CString res = "";
	switch(state) {
	case 0:
		 res = "执行成功";
		 break;
	case -1:
		 res = "卡片类型不对";
		 break;
	case -2:
		 res = "无卡";
		 break;
	case -3:
		 res = "有卡未上电";
		 break;
	case -4:
		 res = "卡片无应答";
		 break;
	case -5:
		 res = "BCC校验错误";
		 break;
	case -6:
		 res = "接收超时";
		 break;
	case -7:
		 res = "执行失败";
		 break;
	case -8:
		 res = "卡片位置错误";
		 break;
	case -9:
		 res = "设置失败";
		 break;
	case -10:
		 res = "无卡";
		 break;
	case -11:
		 res = "读卡器连接错";
		 break;
	case -12:
		 res = "未建立连接";
		 break;
	case -13:
		 res = "不支持该命令";
		 break;
	case -14:
		 res = "命令参数错";
		 break;
	case -15:
		 res = "信息校验和出错";
		 break;
	case -16:
		 res = "卡片上电失败";
		 break;
	case -17:
		 res = "卡片复位失败";
		 break;
	case -18:
		 res = "卡片下电失败";
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
