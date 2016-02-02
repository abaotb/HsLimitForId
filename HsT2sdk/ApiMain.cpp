/*************************************************************************************************************/
/*	HsT2SDK交易接口封装                 																		*/
/*	修改记录： 			*/
/*			   		*/
/*																											*/
/*																											*/
/*																											*/
/*																											*/
/************************************************************************************************************/
#include "stdafx.h"
#include "HsT2sdk.h"


// UserApi对象
//CThostFtdcTraderApi* pUserApi;

//回调函数
//CBOnFrontConnected cbOnFrontConnected=0;		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
/*
TRADEAPI_API int WINAPI Connect(char* FRONT_ADDR, char *FLOW_PATH)
{
	// 初始化UserApi
	char szFlowPath[1024]={0};
	strcpy(szFlowPath, FLOW_PATH);
	strcat(szFlowPath, "\\");
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(szFlowPath);			// 创建UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	pUserApi->SubscribePublicTopic(THOST_TERT_RESUME);					// 注册公有流
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESUME);					// 注册私有流
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();
	return 0;
	//pUserApi->Join();
}*/

#pragma region 公用
void PackCopy(IF2UnPacker *lpUnPacker,char* sOutBuff,char* sName)
{
    int i = 0, t = 0, j = 0, k = 0;
	char sTemp[100]={0};	
	if(strcmp(sName,"")==0)
	{
		for (i = 0; i < lpUnPacker->GetDatasetCount(); ++i)
		{
			// 设置当前结果集
			lpUnPacker->SetCurrentDatasetByIndex(i);
			
				// 打印字段
			for (t = 0; t < lpUnPacker->GetColCount(); ++t)
			{
				memset(sTemp, 0, 100);
				sprintf(sTemp,"%20s|", lpUnPacker->GetColName(t));
				strcat(sOutBuff,sTemp);
			}			
			// 打印所有记录
			for (j = 0; j < (int)lpUnPacker->GetRowCount(); ++j)
			{
				
				// 打印每条记录
				for (k = 0; k < lpUnPacker->GetColCount(); ++k)
				{                
					switch (lpUnPacker->GetColType(k))
					{
					
					case 'I':
						memset(sTemp, 0, 100);
						sprintf(sTemp,"%20d|", lpUnPacker->GetIntByIndex(k));
						strcat(sOutBuff,sTemp);
						break;

					case 'C':
						memset(sTemp, 0, 100);
						sprintf(sTemp,"%20c|", lpUnPacker->GetCharByIndex(k));
						strcat(sOutBuff,sTemp);
						break;

					case 'S':
						memset(sTemp, 0, 100);
						sprintf(sTemp,"%20s|", lpUnPacker->GetStrByIndex(k));
						strcat(sOutBuff,sTemp);
						break;

					case 'F':
						memset(sTemp, 0, 100);
						sprintf(sTemp,"%20f|", lpUnPacker->GetDoubleByIndex(k));
						strcat(sOutBuff,sTemp);
						break;

					case 'R':
						{
							int nLength = 0;
							void *lpData = lpUnPacker->GetRawByIndex(k, &nLength);

							// 对2进制数据进行处理
							break;
						}

					default:
						// 未知数据类型
						printf("未知数据类型。\n");
						break;
					}
				}
				


			   // putchar('\n');

				lpUnPacker->Next();
			}
		}
	}
	else
	{
		for (i = 0; i < lpUnPacker->GetDatasetCount(); ++i)
		{
			// 设置当前结果集
			lpUnPacker->SetCurrentDatasetByIndex(i);
			
			// 打印所有记录
			for (j = 0; j < (int)lpUnPacker->GetRowCount(); ++j)
			{								
				memset(sTemp, 0, 100);
				sprintf(sTemp,"%s|", lpUnPacker->GetStr(sName));
				strcat(sOutBuff,sTemp);				
				lpUnPacker->Next();
			}
		}						
	}    
        //putchar('\n');
    
}
#pragma endregion

CConfigInterface * lpConfig; //设置
IF2Packer* pack; //打包
IF2UnPacker *lpUnPacker; //解包
CConnectionInterface *lpConnection; //连接
#pragma region 设置
/*
HST2SDK_API int WINAPI ConfigInit(char *sServer, char *sLiceFile)
{
	lpConfig = NewConfig();
	lpConfig->AddRef();

    //[t2sdk] servers指定需要连接的IP地址及端口，可配置多个，中间以“;”间隔
    lpConfig->SetString("t2sdk", "servers", sServer);

    //[t2sdk] license_file指定许可证文件路径
    lpConfig->SetString("t2sdk", "license_file", sLiceFile);

    //[t2sdk] lang指定错误信息的语言号（缺省为简体中文2052），1033为英文
    lpConfig->SetString("t2sdk", "lang", "1033");

    //[t2sdk] send_queue_size指定T2_SDK的发送队列大小
    lpConfig->SetString("t2sdk", "send_queue_size", "100");

    //[safe] safe_level指定连接的安全模式，需要和T2通道的安全模式一致，否则连接失败
    lpConfig->SetString("safe", "safe_level", "none");
	return 0;
}
HST2SDK_API int WINAPI ConfigRelease()
{
	lpConfig->Release();
	return 0;
}*/
#pragma endregion
#pragma region 打包
HST2SDK_API int WINAPI BeginPack()
{
	pack = NewPacker(2);
	pack->AddRef();
	pack->BeginPack();
	return 0;
}

HST2SDK_API int WINAPI Endpack()
{
	pack->EndPack();
	return 0;
}
HST2SDK_API int WINAPI PackFree()
{
	free(pack->GetPackBuf());
    pack->Release();
	return 0;
}
//*@param cFieldType ：字段类型:I整数，F浮点数，C字符，S字符串，R任意二进制数据
HST2SDK_API int WINAPI AddField(const char *szFieldName,char cFieldType ='S')
{	
	return pack->AddField(szFieldName, cFieldType);
}
HST2SDK_API int WINAPI AddStr(const char *szValue)
{
	return pack->AddStr(szValue);
}
HST2SDK_API int WINAPI AddInt(int iValue)
{
	return pack->AddInt(iValue);
}
HST2SDK_API int WINAPI AddDouble(double fValue)
{
	return pack->AddDouble(fValue);
}
HST2SDK_API int WINAPI AddChar(char cValue)
{
	return pack->AddChar(cValue);
}
//virtual int FUNCTION_CALL_MODE NewDataset(const char *szDatasetName, int iReturnCode = 0)=0;
HST2SDK_API int WINAPI NewDataSet(const char* strDatasetName)
{
	return pack->NewDataset(strDatasetName);
}
	//virtual int FUNCTION_CALL_MODE GetPackLen(void) = 0;
	
	/**
	 * 功能：取打包结果缓冲区大小
     *@return 打包结果缓冲区大小
	 */
//	virtual int FUNCTION_CALL_MODE GetPackBufSize(void) = 0;
HST2SDK_API int WINAPI GetPackLen()
{
	return pack->GetPackLen();
}
HST2SDK_API int WINAPI GetPackBufSize()
{
	return pack->GetPackBufSize();
}

#pragma endregion
#pragma region 解包


HST2SDK_API int WINAPI GetDatasetCount()
{
	return lpUnPacker->GetDatasetCount();
}
HST2SDK_API int WINAPI SetCurrentDatasetByIndex(int iIndex)
{
	return lpUnPacker->SetCurrentDatasetByIndex(iIndex);
}
HST2SDK_API int WINAPI GetColCount()
{
	return lpUnPacker->GetColCount();
}
HST2SDK_API const char* WINAPI GetColName( int iColumn)
{
	return lpUnPacker->GetColName(iColumn);
	
}
HST2SDK_API char WINAPI GetColType(int iColumn)
{
	return lpUnPacker->GetColType(iColumn);
}
//char *  FUNCTION_CALL_MODE GetStr(const char * columnName)
HST2SDK_API const char* WINAPI GetStr(const char * columnName)
{
	return lpUnPacker->GetStr(columnName);
}
HST2SDK_API double WINAPI GetDouble(const char * columnName)
{
	return lpUnPacker->GetDouble(columnName);
}
HST2SDK_API int WINAPI GetInt(const char * columnName)
{
	return lpUnPacker->GetInt(columnName);
}
HST2SDK_API char WINAPI GetChar(const char * columnName)
{
	return lpUnPacker->GetChar(columnName);
}

HST2SDK_API void WINAPI Next()
{
	lpUnPacker->Next();
}
HST2SDK_API int WINAPI IsEOF()
{
	return lpUnPacker->IsEOF();
}
HST2SDK_API void UnPackerFree()
{
	lpUnPacker->Destroy();
}

#pragma endregion
#pragma region 连接
HST2SDK_API int WINAPI Connect(char *sLiceFile, char* sPwd, char *sErrInfo)
{
	lpConfig = NewConfig();
	lpConfig->AddRef();
	/*
    //[t2sdk] servers指定需要连接的IP地址及端口，可配置多个，中间以“;”间隔
    lpConfig->SetString("t2sdk", "servers", sServer);

    //[t2sdk] license_file指定许可证文件路径
    lpConfig->SetString("t2sdk", "license_file", sLiceFile);

    //[t2sdk] lang指定错误信息的语言号（缺省为简体中文2052），1033为英文
    lpConfig->SetString("t2sdk", "lang", "2052");

    //[t2sdk] send_queue_size指定T2_SDK的发送队列大小
    lpConfig->SetString("t2sdk", "send_queue_size", "100");
	
	
    //[safe] safe_level指定连接的安全模式，需要和T2通道的安全模式一致，否则连接失败
	if(strcmp(sPwd, "none")==0)
	{
		lpConfig->SetString("safe", "safe_level", "none");
	}	
	else
	{
		lpConfig->SetString("safe", "safe_level", "pwd");
		lpConfig->SetString("safe", "comm_pwd", sPwd);
	}*/
	lpConfig->Load("t2sdk.ini");
	lpConnection = NewConnection(lpConfig);
	lpConnection->AddRef();
	int iRet = lpConnection->Create(NULL);
	if(iRet == 0)
	{
		iRet = lpConnection->Connect(1000);
		
	}
	if(iRet != 0)
	{
		strcpy(sErrInfo, lpConnection->GetErrorMsg(iRet));
	}
	
	return iRet;
}
//返回值大于零为发送句柄
HST2SDK_API int WINAPI SendBiz(int iFundNo,  char *sErrInfo)
{
	
	int iRet = lpConnection->SendBiz(iFundNo, pack);
	
	if(iRet <= 0)
	{
		strcpy(sErrInfo, lpConnection->GetErrorMsg(iRet));
	}
	return iRet;
}
HST2SDK_API int WINAPI RecvBiz(int hSend, char * sBuffer,char *sErrInfo,char *sName="")
{	
	int iRet;
	void *Pointer = NULL;
	iRet = lpConnection->RecvBiz(hSend, &Pointer);
	switch (iRet)
    {
    case 0:
        {
            strcpy(sErrInfo, "业务操作成功。");
			lpUnPacker = (IF2UnPacker *)Pointer;
            PackCopy(lpUnPacker,sBuffer,sName);
            break;
        }

    case 1:
        {
			strcpy(sErrInfo, "业务操作失败。");    
			lpUnPacker = (IF2UnPacker *)Pointer;
			//PackCopy(lpUnPacker,sBuffer);
			strcpy(sErrInfo, lpUnPacker->GetStrByIndex(1));
            //ShowPacket((IF2UnPacker *)Pointer);
            break;
        }

    case 2:
        {            
			strcpy(sErrInfo, (char *)Pointer);         
            break;
        }

    case 3:
        {           
			strcpy(sErrInfo, "业务包解包失败。");         
            break;
        }

    default:
        {
            strcpy(sErrInfo, lpConnection->GetErrorMsg(iRet));
            break;
        }
    }
	return iRet;
}

HST2SDK_API int WINAPI ConnRelease()
{
	lpConnection->Release();
	lpConfig->Release();
	return 0;
}
//lpConnection->Release();
    //lpConfig->Release();

#pragma endregion
