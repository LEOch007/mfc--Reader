// MysqlHelper.h: interface for the MysqlHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSQLHELPER_H__7A85F39D_B172_4B68_9C98_6B17B46F76FE__INCLUDED_)
#define AFX_MYSQLHELPER_H__7A85F39D_B172_4B68_9C98_6B17B46F76FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import "./libs/msado15.dll" no_namespace rename("EOF","ADOEOF") rename("BOF","ADOBOF")

class cardRecord
{
public:
	CString stunum; //学号
	CString cardnum; //卡号
	CString pwd; //密码
	CString stuname; //学生姓名
	CString stusex; //性别
	CString grade; //年级
	CString college; //学院
	CString money; //余额
	CString flag; //标记

	cardRecord(){}

	cardRecord(CString stunum1,CString cardnum1,CString pwd1,CString stuname1,CString stusex1,CString grade1,CString college1,CString money1,CString flag1){
		stunum = stunum1;
		cardnum = cardnum1;
		pwd = pwd1;	
		stuname = stuname1;
		stusex = stusex1;
		grade = grade1;
		college = college1;
		money = money1;
		flag = flag1;
	}
};

class MysqlHelper  
{
public:
	MysqlHelper();
	virtual ~MysqlHelper();

	
	BOOL MySQL_Connect(); //连接数据库
	void MySQL_Close(); //关闭数据库

	BOOL MySQL_insert(cardRecord rr); //插入数据
	BOOL MySQL_delete(CString stunumber); //删除数据

	BOOL MySQL_update_money(CString cardnumber,CString cur_money); //根据卡号更新余额
	BOOL MySQL_update_flag(CString stunumber, CString cur_flag); //根据学号更新标记

	cardRecord MySQL_query(CString stunumber); //查询数据
	cardRecord MySQL_querybycard(CString cardnumber); //查询数据

	BOOL GetMd5Hash(CONST BYTE *pbData, DWORD dwDataLen, CString &strHash, DWORD &err);
	CString GetHash(CString sin); //哈希 

private:
	//数据库连接智能指针
	_ConnectionPtr m_pConnection;

};

#endif // !defined(AFX_MYSQLHELPER_H__7A85F39D_B172_4B68_9C98_6B17B46F76FE__INCLUDED_)
