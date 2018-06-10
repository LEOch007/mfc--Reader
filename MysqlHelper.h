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
	CString stunum; //ѧ��
	CString cardnum; //����
	CString pwd; //����
	CString stuname; //ѧ������
	CString stusex; //�Ա�
	CString grade; //�꼶
	CString college; //ѧԺ
	CString money; //���
	CString flag; //���

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

	
	BOOL MySQL_Connect(); //�������ݿ�
	void MySQL_Close(); //�ر����ݿ�

	BOOL MySQL_insert(cardRecord rr); //��������
	BOOL MySQL_delete(CString stunumber); //ɾ������

	BOOL MySQL_update_money(CString cardnumber,CString cur_money); //���ݿ��Ÿ������
	BOOL MySQL_update_flag(CString stunumber, CString cur_flag); //����ѧ�Ÿ��±��

	cardRecord MySQL_query(CString stunumber); //��ѯ����
	cardRecord MySQL_querybycard(CString cardnumber); //��ѯ����

	BOOL GetMd5Hash(CONST BYTE *pbData, DWORD dwDataLen, CString &strHash, DWORD &err);
	CString GetHash(CString sin); //��ϣ 

private:
	//���ݿ���������ָ��
	_ConnectionPtr m_pConnection;

};

#endif // !defined(AFX_MYSQLHELPER_H__7A85F39D_B172_4B68_9C98_6B17B46F76FE__INCLUDED_)
