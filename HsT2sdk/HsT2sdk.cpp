// HsT2sdk.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "HsT2sdk.h"

// USER_API����
//extern CThostFtdcTraderApi* pUserApi;
//extern CBOnFrontConnected cbOnFrontConnected;		///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
//void CTraderSpi::OnFrontConnected(){ 	if(cbOnFrontConnected!=NULL) 		cbOnFrontConnected();}

extern CConfigInterface * lpConfig;
extern IF2Packer* pack;
extern IF2UnPacker *lpUnPacker;
extern CConnectionInterface *lpConnection;


