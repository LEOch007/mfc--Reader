// MysqlHelper.cpp: implementation of the MysqlHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RFID.h"
#include "MysqlHelper.h"
#include "windows.h"
#include "Wincrypt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MysqlHelper::MysqlHelper()
{
	this->MySQL_Connect();
}

MysqlHelper::~MysqlHelper()
{
	this->MySQL_Close();
}

BOOL MysqlHelper::MySQL_Connect(){
	CoInitialize(NULL); //初始化OLE/COM库环境
	try{
		// 通过名字创建Connection对象
		HRESULT hr = this->m_pConnection.CreateInstance("ADODB.Connection");
		if (FAILED(hr)){
			AfxMessageBox(_T("创建_ConnectionPtr智能指针失败"));
			return false;
		}
		// 连接数据库
		this->m_pConnection->Open("DSN=mysql_server_rfid;Server=128.199.80.196;Database=rfid_card",
			"rfid",
			"rfidrfid",
			adModeUnknown);
	}
	catch (_com_error &e){
		// 若连接打开，需要在异常处理中关闭和释放连接
		if ((NULL != this->m_pConnection) && this->m_pConnection->State){
			this->m_pConnection->Close();
			this->m_pConnection.Release();
			this->m_pConnection = NULL;
		}
		AfxMessageBox(e.Description());
		return false;
	}
	return true;
}

void MysqlHelper::MySQL_Close(){
	if ((NULL != this->m_pConnection) && (this->m_pConnection->State)){
		this->m_pConnection->Close(); // 关闭连接
		this->m_pConnection.Release();// 释放连接
		this->m_pConnection = NULL;
	}

	CoUninitialize(); //访问完COM库后，卸载COM库
}

BOOL MysqlHelper::MySQL_insert(cardRecord rr){
	_CommandPtr m_pCommand;
	try{
		m_pCommand.CreateInstance("ADODB.Command");
		
		//定义为无参数
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;
		
		//sql语句
		m_pCommand->CommandText = "insert into card_info values(\'" + (_bstr_t)rr.stunum +"\',"
			+"\'"+ (_bstr_t)rr.cardnum +"\'," +"\'"+ (_bstr_t)rr.pwd +"\',"
			+"\'"+ (_bstr_t)rr.stuname +"\'," +"\'"+ (_bstr_t)rr.stusex +"\',"
			+"\'"+ (_bstr_t)rr.grade +"\'," +"\'"+ (_bstr_t)rr.college +"\',"
			+"\'"+ (_bstr_t)rr.money +"\'," +"\'"+ (_bstr_t)rr.flag +"\');";

		m_pCommand->ActiveConnection = this->m_pConnection; //将建立的连接与对象绑定
		m_pCommand->Execute(&vNULL, &vNULL, adCmdText); //执行sql语句
	}
	catch (_com_error &e){
		// 若连接打开，需要在异常处理中关闭和释放连接
		if ((NULL != this->m_pConnection) && this->m_pConnection->State){
			this->m_pConnection->Close();
			this->m_pConnection.Release();
			this->m_pConnection = NULL;
		}
		AfxMessageBox(e.Description());
		return false;
	}
	return true;
}

BOOL MysqlHelper::MySQL_delete(CString stunumber){
	_CommandPtr m_pCommand;
	try{
		m_pCommand.CreateInstance("ADODB.Command");

		//定义为无参数
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;

		//sql语句
		m_pCommand->CommandText = "delete from card_info where stunum=\'" +(_bstr_t)stunumber+ "\'";

		m_pCommand->ActiveConnection = this->m_pConnection; //将建立的连接与对象绑定
		m_pCommand->Execute(&vNULL, &vNULL, adCmdText); //执行sql语句
	}
	catch (_com_error &e){
		// 若连接打开，需要在异常处理中关闭和释放连接
		if ((NULL != this->m_pConnection) && this->m_pConnection->State){
			this->m_pConnection->Close();
			this->m_pConnection.Release();
			this->m_pConnection = NULL;
		}
		AfxMessageBox(e.Description());
		return false;
	}
	return true;
}

BOOL MysqlHelper::MySQL_update_money(CString cardnumber,CString cur_money){
	_CommandPtr m_pCommand;
	try{
		m_pCommand.CreateInstance("ADODB.Command");

		//定义为无参数
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;

		//sql语句
		m_pCommand->CommandText = "update card_info set money=\'" +(_bstr_t)cur_money+ "\' where cardnum=\'" +(_bstr_t)cardnumber+ "\';";

		m_pCommand->ActiveConnection = this->m_pConnection; //将建立的连接与对象绑定
		m_pCommand->Execute(&vNULL, &vNULL, adCmdText); //执行sql语句
	}
	catch (_com_error &e){
		// 若连接打开，需要在异常处理中关闭和释放连接
		if ((NULL != this->m_pConnection) && this->m_pConnection->State){
			this->m_pConnection->Close();
			this->m_pConnection.Release();
			this->m_pConnection = NULL;
		}
		AfxMessageBox(e.Description());
		return false;
	}
	return true;
}

BOOL MysqlHelper::MySQL_update_flag(CString stunumber, CString cur_flag){
	_CommandPtr m_pCommand;
	try{
		m_pCommand.CreateInstance("ADODB.Command");

		//定义为无参数
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;

		//sql语句
		m_pCommand->CommandText = "update card_info set flag=\'" +(_bstr_t)cur_flag+ "\' where stunum=\'" +(_bstr_t)stunumber+ "\';";

		m_pCommand->ActiveConnection = this->m_pConnection; //将建立的连接与对象绑定
		m_pCommand->Execute(&vNULL, &vNULL, adCmdText); //执行sql语句
	}
	catch (_com_error &e){
		// 若连接打开，需要在异常处理中关闭和释放连接
		if ((NULL != this->m_pConnection) && this->m_pConnection->State){
			this->m_pConnection->Close();
			this->m_pConnection.Release();
			this->m_pConnection = NULL;
		}
		AfxMessageBox(e.Description());
		return false;
	}
	return true;
}

cardRecord MysqlHelper::MySQL_query(CString stunumber){
	//SQL语句
	_variant_t sql = "select * from card_info where stunum=\'" +(_bstr_t)stunumber+ "\';";
	
	cardRecord record;
	try{
		//定义_RecordsetPtr智能指针
		_RecordsetPtr m_pRecordset;
		HRESULT hr = m_pRecordset.CreateInstance(__uuidof(Recordset));
		if (FAILED(hr)){
			AfxMessageBox(_T("创建_RecordsetPtr智能指针失败"));
			return record; //终止退出
		}

		//打开连接，获取数据集
		m_pRecordset->Open(sql,
			_variant_t((IDispatch*)(this->m_pConnection), true),
			adOpenForwardOnly,
			adLockReadOnly,
			adCmdText);
		
		if (!m_pRecordset->ADOEOF){ //确定表不为空
			m_pRecordset->MoveFirst(); //游标移动到最前
			
			//学号
			_variant_t varstunum = m_pRecordset->Fields->GetItem(_T("stunum"))->GetValue();
			varstunum.ChangeType(VT_BSTR);
			CString stunum = varstunum.bstrVal;
			//卡号
			_variant_t varcardnum = m_pRecordset->Fields->GetItem(_T("cardnum"))->GetValue();
			varcardnum.ChangeType(VT_BSTR);
			CString cardnum = varcardnum.bstrVal;
			//密码
			_variant_t varpwd = m_pRecordset->Fields->GetItem(_T("pwd"))->GetValue();
			varpwd.ChangeType(VT_BSTR);
			CString pwd = varpwd.bstrVal;
			//姓名
			_variant_t varstuname = m_pRecordset->Fields->GetItem(_T("stuname"))->GetValue();
			varstuname.ChangeType(VT_BSTR);
			CString stuname = varstuname.bstrVal;
			//性别
			_variant_t varstusex = m_pRecordset->Fields->GetItem(_T("stusex"))->GetValue();
			varstusex.ChangeType(VT_BSTR);
			CString stusex = varstusex.bstrVal;
			//年级
			_variant_t vargrade = m_pRecordset->Fields->GetItem(_T("grade"))->GetValue();
			vargrade.ChangeType(VT_BSTR);
			CString grade = vargrade.bstrVal;
			//学院
			_variant_t varcollege = m_pRecordset->Fields->GetItem(_T("college"))->GetValue();
			varcollege.ChangeType(VT_BSTR);
			CString college = varcollege.bstrVal;
			//余额
			_variant_t varmoney = m_pRecordset->Fields->GetItem(_T("money"))->GetValue();
			varmoney.ChangeType(VT_BSTR);
			CString money = varmoney.bstrVal;
			//标记
			_variant_t varflag = m_pRecordset->Fields->GetItem(_T("flag"))->GetValue();
			varflag.ChangeType(VT_BSTR);
			CString flag = varflag.bstrVal;
				
			record = cardRecord(stunum,cardnum,pwd,stuname,stusex,grade,college,money,flag);
			return record;
		}
		else{
			AfxMessageBox(_T("查询为空"));	
			return record;
		}
	}
	catch(_com_error &e){
		AfxMessageBox(e.Description());
		return record;
	}
}

//根据卡号查询
cardRecord MysqlHelper::MySQL_querybycard(CString cardnumber){
	//SQL语句
	_variant_t sql = "select * from card_info where cardnum=\'" +(_bstr_t)cardnumber+ "\';";

	cardRecord record;
	try{
		//定义_RecordsetPtr智能指针
		_RecordsetPtr m_pRecordset;
		HRESULT hr = m_pRecordset.CreateInstance(__uuidof(Recordset));
		if (FAILED(hr)){
			AfxMessageBox(_T("创建_RecordsetPtr智能指针失败"));
			return record; //终止退出
		}

		//打开连接，获取数据集
		m_pRecordset->Open(sql,
			_variant_t((IDispatch*)(this->m_pConnection), true),
			adOpenForwardOnly,
			adLockReadOnly,
			adCmdText);
		
		if (!m_pRecordset->ADOEOF){ //确定表不为空
			m_pRecordset->MoveFirst(); //游标移动到最前
			
			//学号
			_variant_t varstunum = m_pRecordset->Fields->GetItem(_T("stunum"))->GetValue();
			varstunum.ChangeType(VT_BSTR);
			CString stunum = varstunum.bstrVal;
			//卡号
			_variant_t varcardnum = m_pRecordset->Fields->GetItem(_T("cardnum"))->GetValue();
			varcardnum.ChangeType(VT_BSTR);
			CString cardnum = varcardnum.bstrVal;
			//密码
			_variant_t varpwd = m_pRecordset->Fields->GetItem(_T("pwd"))->GetValue();
			varpwd.ChangeType(VT_BSTR);
			CString pwd = varpwd.bstrVal;
			//姓名
			_variant_t varstuname = m_pRecordset->Fields->GetItem(_T("stuname"))->GetValue();
			varstuname.ChangeType(VT_BSTR);
			CString stuname = varstuname.bstrVal;
			//性别
			_variant_t varstusex = m_pRecordset->Fields->GetItem(_T("stusex"))->GetValue();
			varstusex.ChangeType(VT_BSTR);
			CString stusex = varstusex.bstrVal;
			//年级
			_variant_t vargrade = m_pRecordset->Fields->GetItem(_T("grade"))->GetValue();
			vargrade.ChangeType(VT_BSTR);
			CString grade = vargrade.bstrVal;
			//学院
			_variant_t varcollege = m_pRecordset->Fields->GetItem(_T("college"))->GetValue();
			varcollege.ChangeType(VT_BSTR);
			CString college = varcollege.bstrVal;
			//余额
			_variant_t varmoney = m_pRecordset->Fields->GetItem(_T("money"))->GetValue();
			varmoney.ChangeType(VT_BSTR);
			CString money = varmoney.bstrVal;
			//标记
			_variant_t varflag = m_pRecordset->Fields->GetItem(_T("flag"))->GetValue();
			varflag.ChangeType(VT_BSTR);
			CString flag = varflag.bstrVal;
				
			record = cardRecord(stunum,cardnum,pwd,stuname,stusex,grade,college,money,flag);
			return record;
		}
		else{
			AfxMessageBox(_T("查询为空"));	
			return record;
		}
	}
	catch(_com_error &e){
		AfxMessageBox(e.Description());
		return record;
	}
}

//哈希函数
BOOL MysqlHelper::GetMd5Hash(CONST BYTE *pbData, DWORD dwDataLen, CString &strHash, DWORD &err)
{
    HCRYPTPROV hProv;
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        err = GetLastError();
        return FALSE;
    }

    HCRYPTHASH hHash;
    if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) 
    {
        err = GetLastError();
        CryptReleaseContext(hProv, 0);
        return FALSE;
    }

    if(!CryptHashData(hHash, pbData, dwDataLen, 0))
    {
        err = GetLastError();
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return false;
    }

    DWORD dwSize;
    DWORD dwLen = sizeof(dwSize);
    CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)(&dwSize), &dwLen, 0);

    BYTE* pHash = new BYTE[dwSize];
    dwLen = dwSize;
    CryptGetHashParam(hHash, HP_HASHVAL, pHash, &dwLen, 0);

    strHash = _T("");
    for(DWORD i=0; i<dwLen; i++){
		CString temp;
		temp.Format(_T("%02X"), pHash[i]);
		strHash += temp;
		//strHash.AppendFormat(_T("%02X"), pHash[i]);
	}    
    delete [] pHash;

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    
    return true;
}

//获取字符串的32位哈希值
CString MysqlHelper::GetHash(CString sin){
	TCHAR stchar[200] = {0};
	strcpy(stchar,sin);
	
	CString sout; //加密后字符串
	DWORD getHashErr = 0;
	BOOL getHashResult = GetMd5Hash((BYTE *)stchar, strlen(stchar), sout, getHashErr);

	return sout;
}