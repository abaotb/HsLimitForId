// HsT2sdk.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HsT2sdk.h"

// USER_API参数
//extern CThostFtdcTraderApi* pUserApi;
//extern CBOnFrontConnected cbOnFrontConnected;		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
//void CTraderSpi::OnFrontConnected(){ 	if(cbOnFrontConnected!=NULL) 		cbOnFrontConnected();}

extern CConfigInterface * lpConfig;
extern IF2Packer* pack;
extern IF2UnPacker *lpUnPacker;
extern CConnectionInterface *lpConnection;


