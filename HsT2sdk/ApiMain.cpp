/*************************************************************************************************************/
/*	HsT2SDK���׽ӿڷ�װ                 																		*/
/*	�޸ļ�¼�� 			*/
/*			   		*/
/*																											*/
/*																											*/
/*																											*/
/*																											*/
/************************************************************************************************************/
#include "stdafx.h"
#include "HsT2sdk.h"


// UserApi����
//CThostFtdcTraderApi* pUserApi;

//�ص�����
//CBOnFrontConnected cbOnFrontConnected=0;		///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
/*
TRADEAPI_API int WINAPI Connect(char* FRONT_ADDR, char *FLOW_PATH)
{
	// ��ʼ��UserApi
	char szFlowPath[1024]={0};
	strcpy(szFlowPath, FLOW_PATH);
	strcat(szFlowPath, "\\");
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(szFlowPath);			// ����UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// ע���¼���
	pUserApi->SubscribePublicTopic(THOST_TERT_RESUME);					// ע�ṫ����
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESUME);					// ע��˽����
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();
	return 0;
	//pUserApi->Join();
}*/

#pragma region ����
void PackCopy(IF2UnPacker *lpUnPacker,char* sOutBuff,char* sName)
{
    int i = 0, t = 0, j = 0, k = 0;
	char sTemp[100]={0};	
	if(strcmp(sName,"")==0)
	{
		for (i = 0; i < lpUnPacker->GetDatasetCount(); ++i)
		{
			// ���õ�ǰ�����
			lpUnPacker->SetCurrentDatasetByIndex(i);
			
				// ��ӡ�ֶ�
			for (t = 0; t < lpUnPacker->GetColCount(); ++t)
			{
				memset(sTemp, 0, 100);
				sprintf(sTemp,"%20s|", lpUnPacker->GetColName(t));
				strcat(sOutBuff,sTemp);
			}			
			// ��ӡ���м�¼
			for (j = 0; j < (int)lpUnPacker->GetRowCount(); ++j)
			{
				
				// ��ӡÿ����¼
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

							// ��2�������ݽ��д���
							break;
						}

					default:
						// δ֪��������
						printf("δ֪�������͡�\n");
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
			// ���õ�ǰ�����
			lpUnPacker->SetCurrentDatasetByIndex(i);
			
			// ��ӡ���м�¼
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

CConfigInterface * lpConfig; //����
IF2Packer* pack; //���
IF2UnPacker *lpUnPacker; //���
CConnectionInterface *lpConnection; //����
#pragma region ����
/*
HST2SDK_API int WINAPI ConfigInit(char *sServer, char *sLiceFile)
{
	lpConfig = NewConfig();
	lpConfig->AddRef();

    //[t2sdk] serversָ����Ҫ���ӵ�IP��ַ���˿ڣ������ö�����м��ԡ�;�����
    lpConfig->SetString("t2sdk", "servers", sServer);

    //[t2sdk] license_fileָ�����֤�ļ�·��
    lpConfig->SetString("t2sdk", "license_file", sLiceFile);

    //[t2sdk] langָ��������Ϣ�����Ժţ�ȱʡΪ��������2052����1033ΪӢ��
    lpConfig->SetString("t2sdk", "lang", "1033");

    //[t2sdk] send_queue_sizeָ��T2_SDK�ķ��Ͷ��д�С
    lpConfig->SetString("t2sdk", "send_queue_size", "100");

    //[safe] safe_levelָ�����ӵİ�ȫģʽ����Ҫ��T2ͨ���İ�ȫģʽһ�£���������ʧ��
    lpConfig->SetString("safe", "safe_level", "none");
	return 0;
}
HST2SDK_API int WINAPI ConfigRelease()
{
	lpConfig->Release();
	return 0;
}*/
#pragma endregion
#pragma region ���
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
//*@param cFieldType ���ֶ�����:I������F��������C�ַ���S�ַ�����R�������������
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
	 * ���ܣ�ȡ��������������С
     *@return ��������������С
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
#pragma region ���


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
#pragma region ����
HST2SDK_API int WINAPI Connect(char *sLiceFile, char* sPwd, char *sErrInfo)
{
	lpConfig = NewConfig();
	lpConfig->AddRef();
	/*
    //[t2sdk] serversָ����Ҫ���ӵ�IP��ַ���˿ڣ������ö�����м��ԡ�;�����
    lpConfig->SetString("t2sdk", "servers", sServer);

    //[t2sdk] license_fileָ�����֤�ļ�·��
    lpConfig->SetString("t2sdk", "license_file", sLiceFile);

    //[t2sdk] langָ��������Ϣ�����Ժţ�ȱʡΪ��������2052����1033ΪӢ��
    lpConfig->SetString("t2sdk", "lang", "2052");

    //[t2sdk] send_queue_sizeָ��T2_SDK�ķ��Ͷ��д�С
    lpConfig->SetString("t2sdk", "send_queue_size", "100");
	
	
    //[safe] safe_levelָ�����ӵİ�ȫģʽ����Ҫ��T2ͨ���İ�ȫģʽһ�£���������ʧ��
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
//����ֵ������Ϊ���;��
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
            strcpy(sErrInfo, "ҵ������ɹ���");
			lpUnPacker = (IF2UnPacker *)Pointer;
            PackCopy(lpUnPacker,sBuffer,sName);
            break;
        }

    case 1:
        {
			strcpy(sErrInfo, "ҵ�����ʧ�ܡ�");    
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
			strcpy(sErrInfo, "ҵ������ʧ�ܡ�");         
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
