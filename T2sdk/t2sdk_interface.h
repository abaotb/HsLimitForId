/** @file
* T2_SDKͷ�ļ�
* @author  T2С��
* @author  �������ӹɷ����޹�˾
* @version 1.0.0.2
* @date    20090327
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef _T2SDK_INTERFACE_H
# define _T2SDK_INTERFACE_H

#ifdef _WIN32
	#if !defined( FUNCTION_CALL_MODE )
	#define FUNCTION_CALL_MODE		__stdcall
	#endif
#else
	#define FUNCTION_CALL_MODE
#endif

struct IKnown
{
    virtual unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv) = 0;

    virtual unsigned long  FUNCTION_CALL_MODE AddRef() = 0;

    virtual unsigned long  FUNCTION_CALL_MODE Release() =  0;
};

///������ӿ�
struct IF2ResultSet : public IKnown
{

	///ȡ�ֶ���
    /**@return �����ֶ���.
      */
    virtual int FUNCTION_CALL_MODE GetColCount()=0;

    ///ȡ�ֶ���
    /** @param column:�ֶ����(��0Ϊ����)
      * @return �����ֶ���  �±�Խ�� ����NULL
      */
    virtual const char * FUNCTION_CALL_MODE GetColName(int column)=0;

    //ȡ�ֶ���������
    /** @param column:�ֶ����(��0Ϊ����)
      * @return:�����泣������;�±�Խ�� ����-1
      */
    virtual char FUNCTION_CALL_MODE GetColType(int column)=0;


   ///ȡ�������ֶ�С��λ��
   /** @param column:�ֶ����(��0Ϊ����)
     * @return int �����ֶ�����С��λ�� �±�Խ�� ����-1
     */
   virtual int FUNCTION_CALL_MODE GetColScale(int column)=0;
  
   //ȡ�ֶ����������ݵ������.
   /** @param column:�ֶ����(��0Ϊ����)
     * @return int �����ֶο�� �±�Խ�� ����-1
     */
   virtual int FUNCTION_CALL_MODE GetColWidth(int column) = 0;

   ///ȡ�ֶ�����Ӧ���ֶ����
   /**@param columnName: �ֶ���
     *@return �����ֶ����. �����ڷ���-1
     */
   virtual int  FUNCTION_CALL_MODE FindColIndex(const char * columnName)=0;

    //
    //���ֶ����(��0Ϊ����)��ȡ�ֶ�ֵ(�ַ���)
    /**@param column:�ֶ����(��0Ϊ����)
      *@return �ַ������ֶ�ֵ,�±�Խ�緵��NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStrByIndex(int column)=0;

    //���ֶ�����ȡ�ֶ�ֵ(�ַ���)
    /**@param columnName: �ֶ���
      *@return �ַ������ֶ�ֵ,�����ڷ���NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStr(const char * columnName)=0;

    //���ֶ����(��0Ϊ����)��ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return �ַ����ֶ�ֵ,�±�Խ�緵��'\0'.
      */
     virtual char  FUNCTION_CALL_MODE  GetCharByIndex(int column)=0;

    //���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName: �ֶ���
     *@return �ַ����ֶ�ֵ,�����ڷ���'\0'
     */
    virtual char   FUNCTION_CALL_MODE GetChar(const char * columnName)=0;

    //���ֶ���ţ�ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return double���ֶ�ֵ,�±�Խ�緵��0
      */
    virtual double  FUNCTION_CALL_MODE GetDoubleByIndex( int column)=0;
    
	///���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName:�ֶ���
      *@return double���ֶ�ֵ,�����ڷ���0
      */
    virtual double  FUNCTION_CALL_MODE GetDouble(const char * columnName)=0;

    ///���ֶ���ţ�ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return int���ֶ�ֵ,�±�Խ�緵��0
      */
    virtual int  FUNCTION_CALL_MODE GetIntByIndex(int column)=0;

    ///���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName:�ֶ���
      *@return int���ֶ�ֵ,�����ڷ���0
      */
    virtual int FUNCTION_CALL_MODE GetInt(const char * columnName)=0;

	///���ֶ���Ż���ֶ�ֵ,����������
	/**@param column: �ֶ����(��0Ϊ����)
	*@param   lpRawLen: [out]���ݳ���
	*@return : �����׵�ַ
	*/
	virtual void *  FUNCTION_CALL_MODE GetRawByIndex(int column,int * lpRawLen) = 0;

	///���ֶ�����ȡ�ֶ�ֵ
	/**@param columnName:�ֶ���
	*@param   lpRawLen: [out]���ݳ���
	*@return : �����׵�ַ
	*/
	virtual void *  FUNCTION_CALL_MODE GetRaw(const char * columnName,int * lpRawLen) = 0;


	///���һ��ȡ���ֶ�ֵ�Ƿ�ΪNULL
   /**@return 0 �ǣ� 1����
   */
    virtual int  FUNCTION_CALL_MODE WasNull()=0;

    ///ȡ��һ����¼
    virtual void  FUNCTION_CALL_MODE Next()=0;

    ///�ж��Ƿ�Ϊ��β
    /**@return 1 �ǣ�0 ����;
      */
    virtual int  FUNCTION_CALL_MODE IsEOF()=0;
   
	///�ж��Ƿ�Ϊ��
    /**@return 1 �ǣ�0 ����;
      */
    virtual int  FUNCTION_CALL_MODE IsEmpty()=0;
    
    virtual void * FUNCTION_CALL_MODE Destroy() = 0;
};

struct IF2UnPacker;

///����������ӿ�(һ�������ж���칹�����)
/**ִ������:
 *
 * 0��׼��(��ѡ, �������иò���, ����IF2Packer�ڲ������ڴ滺��)�� SetBuffer(),�������������ɵ������ṩ,�������BeginPack()֮ǰ׼��;
 *
 * 1����ʼ:  BeginPack(),�������λ;
 *
 * 2����һ������������
 *
 *(a)����ֶ����б���AddField()
 *
 *(b)���ս������ά��˳�����ֶΣ�������¼���ֶ�����������ݣ�AddStr() {AddInt(), AddDouble(), AddRaw()}
 *
 * 3�����ý�����ķ�����(��ѡ����������, �򷵻���Ϊ0) SetReturnCode()
 *
 * 4������һ�������(��ѡ) NewDataSet()���˴�ͬʱ�����˸ý�����ķ����룻
 * 
 * 5���ο���2��ʵ����һ����������(��ѡ)��
 *
 * 6��������EndPack(),�ظ����ûᵼ�¼���ս����;
 *
 * 7��ȡ������(����������������С�����ݳ���)
 *    ������Ҳ����ֱ�ӽ��UnPack()���ؽ���ӿ�
 *
 *ʹ��ע������:IF2Packer��ʹ�õ��ڴ滺�������ɵ����߸�����գ�
 *             ����������ķ����룬ֻ���ڰ���ʽ�汾0x21������ʱ��Ч��
 */
struct IF2Packer : public IKnown
{
    ///�������ʼ��(ʹ�õ����ߵĻ�����)
	/** ��һ��ʹ�ô����ʱ������ʹ�ñ��������úû�����(���ݳ��ȱ���ΪiDataLen)
	 *@param  char * pBuf  ��������ַ
 	 *@param  int iBufSize  �������ռ�
 	 *@param  int iDataLen  �������ݳ��ȣ��������ݼ�����������֮��ֻ��V1.0��ʽ�İ���Ч�� 	 
 	 */
	virtual void FUNCTION_CALL_MODE SetBuffer(void * pBuf,int iBufSize,int iDataLen=0 )=0;

	///��λ�����¿�ʼ����һ����(�ֶ������¼����Ϊ0��0��)
	/**
	 * ���ܣ���ʼ������Ѱ���������(�ظ�ʹ�����еĻ������ռ�)
	 *@return ��
	 */
	virtual void FUNCTION_CALL_MODE BeginPack(void)=0;

	///��ʼ��һ�������
	/**�ڴ򵥽�����İ�ʱ�����Բ����ñ�����,��ȡĬ��ֵ
	 *@param const char *szDatasetName 0x20������Ҫָ�����������
	 *@param int iReturnCode           0x20������ҪΪÿ�������ָ������ֵ
	 */
	virtual int FUNCTION_CALL_MODE NewDataset(const char *szDatasetName, int iReturnCode = 0)=0;

	/**
	 * ���ܣ��������ֶ�
	 *
	 *��ִ�д���Ҫ��:�� NewDataset()��Reset(),SetBuffer()֮��,����ֶΰ�˳�����;
	 *
	 *@param szFieldName���ֶ���
	 *@param cFieldType ���ֶ�����:I������F��������C�ַ���S�ַ�����R�������������
	 *@param iFieldWidth ���ֶο�ȣ���ռ����ֽ�����
	 *@param iFieldScale ���ֶξ���,��cFieldType='F'ʱ��С��λ��(ȱʡΪ4λС��)
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddField(const char *szFieldName,char cFieldType ='S',int iFieldWidth=255,int iFieldScale=4)=0;

	/**
	 * ���ܣ��������ַ�������
     * ��ִ�д���Ҫ��:�����������ֶ�������֮��,����ֶΰ�˳�����;
	 *@param       szValue���ַ�������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddStr(const char *szValue)=0;

	/**
     * ���ܣ���������������
 	 *@param       iValue����������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddInt(int iValue)=0;
	
    /**
	 * ���ܣ������Ӹ�������
	 *@param       fValue����������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddDouble(double fValue)=0;

	/**
	 * ���ܣ�������һ���ַ�
	 *@param		 cValue���ַ�
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddChar(char cValue)=0;

	/**
	 * ���ܣ�������һ�������
	 *@param	void * lpBuff ������
	 *@param	int iLen  ���ݳ���	 
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddRaw(void * lpBuff,int iLen)=0;

    ///�������
	virtual void FUNCTION_CALL_MODE EndPack()=0;
 
	/**
     * ���ܣ�ȡ������ָ��
	 *@return ������ָ��
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;
	
	/**
     * ���ܣ�ȡ����������
     *@return ����������
	 */
	virtual int FUNCTION_CALL_MODE GetPackLen(void) = 0;
	
	/**
	 * ���ܣ�ȡ��������������С
     *@return ��������������С
	 */
	virtual int FUNCTION_CALL_MODE GetPackBufSize(void) = 0;
	
	/**
	 * ���ܣ�ȡ�����ʽ�汾
     *@return �汾
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;
	
	///���ý�����ķ�����(0x20������Ҫ��)������������Ҫ����
	/**������ȡȱʡֵ0�������ã�������ã��������EndPack()֮ǰ����
     *@return �汾
	 */
	virtual void FUNCTION_CALL_MODE SetReturnCode(unsigned long dwRetCode) = 0;

	/**ֱ�ӷ��ص�ǰ�������Ľ���ӿ�,������EndPack()֮����ܵ���,�ڴ�����ͷ�ʱ��Ӧ�Ľ����ʵ��Ҳ�ͷ�
     *@return ������ӿڣ��˽���ӿڲ��ܵ��� destroy()���ͷ�
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE UnPack(void) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE ClearValue() = 0;
};

///������ӿ�
struct IF2UnPacker : public IF2ResultSet
{
	/**ȡ�����ʽ�汾
     *@return �汾
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;

	/**ȡ������ݳ���
     *@return 							0 ��ʾ�ɹ��� ����Ϊʧ��
	 */
	virtual int FUNCTION_CALL_MODE Open(void * lpBuffer,unsigned int iLen) = 0;

    ///ȡ���������(0x20���ϰ汾֧��)
    virtual int FUNCTION_CALL_MODE GetDatasetCount()=0;

    ///���õ�ǰ�����(0x20���ϰ汾֧��)
    /**
	 *@param  int nIndex				��������
	 *@return int						0��ʾ�ɹ�������Ϊʧ��
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDatasetByIndex(int nIndex)=0;

    ///���õ�ǰ����� (0x20���ϰ汾֧��)
    /**
	 *@param  const char *szDatasetName	���������
	 *@return int						0 ��ʾ�ɹ�������Ϊʧ��
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDataset(const char *szDatasetName)=0;

	/** ȡ���������ָ��
	 *@return ������ָ��
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;

	/** ȡ������ݳ���
     *@return ������ݳ���
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetPackLen(void) = 0;

	/**ȡ������ݼ�¼����,20051207�Ժ�汾֧��
     *@return ��¼����
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetRowCount(void) = 0;
};

///���Ӷ��� CConnectionInterface �Ĳ������ö���CConfigInterface
/**
* �������ļ����ء����浽�ļ�����д����
*/
class CConfigInterface: public IKnown
{
public:
	/**
    * ���ļ�����
    * @param szFileName �ļ�������ʽ����ini������ο�������ʾ��
    * @return ����0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE Load(const char *szFileName) = 0;

    /**
    * ���浽�ļ�
    * @param szFileName �ļ���
    * @return ����0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE Save(const char *szFileName) = 0;

    /**
    * ȡ�ַ���ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param szDefault ȱʡֵ
    * @return �ַ���ֵ��û���ҵ�ʱ����szDefault
    */
    virtual const char * FUNCTION_CALL_MODE GetString(const char *szSection, const char *szEntry, const char *szDefault) = 0;

    /**
    * ȡ����ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param iDefault  ȱʡֵ
    * @return ����ֵ��û���ҵ�ʱ����iDefault
    */
    virtual int FUNCTION_CALL_MODE GetInt(const char *szSection, const char *szEntry, int iDefault) = 0;

    /**
    * �����ַ���ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param szValue   ֵ
    * @return 0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE SetString(const char *szSection, const char *szEntry, const char *szValue) = 0;

    /**
    * ��������ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param iValue    ֵ
    * @return 0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE SetInt(const char *szSection, const char *szEntry, int iValue) = 0;
};

class CConnectionInterface;

///���Ӷ��� CConnectionInterface ��Ҫ�Ļص�����ӿڶ���
/**
* �������ӳɹ������ӶϿ���������ɡ��յ����ݵ��¼�    
*/
class CCallbackInterface: public IKnown
{
public:
    /**
    * �׽������ӳɹ�
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * ��ɰ�ȫ����
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * ���ע��
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection) = 0;

    /**
    * ���ӱ��Ͽ�
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection) = 0;

    /**
    * �������
    * @param lpConnection �������¼������Ӷ���
    * @param hSend        ���;��
    * @param reserved1    �����ֶ�
    * @param reserved2    �����ֶ�
    * @param nQueuingData ���Ͷ�����ʣ�������ʹ���߿����ô���ֵ���Ʒ��͵��ٶȣ���С��ĳֵʱ���з���
    * @see Send()
    */
    virtual void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData) = 0;

    virtual void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d) = 0;

    virtual void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d) = 0;

    virtual int  FUNCTION_CALL_MODE Reserved3() = 0;

    virtual void FUNCTION_CALL_MODE Reserved4() = 0;

    virtual void FUNCTION_CALL_MODE Reserved5() = 0;

    virtual void FUNCTION_CALL_MODE Reserved6() = 0;

    virtual void FUNCTION_CALL_MODE Reserved7() = 0;

    /**
    * �յ�SendBiz�첽���͵������Ӧ��
    * @param lpConnection    �������¼������Ӷ���
    * @param hSend           ���;��
    * @param lpUnPackerOrStr ָ������ָ����ߴ�����Ϣ
    * @param nResult         �հ����
    * ���nResult����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���lpUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�lpUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����2����ʾ�յ���ҵ�������Ϣ��lpUnPackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    * ���nResult����3����ʾҵ������ʧ�ܡ�lpUnPackerOrStrָ��NULL��
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult) = 0;
};

///T2_SDK���Ӷ���ӿ�
/**
* �������ӡ��Ͽ������͡����յ�
*/
class CConnectionInterface: public IKnown
{
public:
    ///����״̬�������
    enum ConnectionStatus
    {
        Disconnected	= 0x0000, /**< δ���� */
        Connecting		= 0x0001, /**< socket�������� */
        Connected		= 0x0002, /**< socket������ */
        SafeConnecting	= 0x0004, /**< ���ڽ�����ȫ���� */
        SafeConnected	= 0x0008, /**< �ѽ�����ȫ���� */
        Registering		= 0x0010, /**< ��ע�� */
        Registered		= 0x0020, /**< ��ע�� */
        Rejected		= 0x0040  /**< ���ܾ��������ر� */
    };

    ///����ѡ�����ϣ�0��ʾ���ճ�ʱʱ����ɾ����ID���Կ��ٴε���RecvBiz���������Խ��գ�
    enum RecvFlags
    {
        JustRemoveHandle = 0x0001   /**< �����ճ�ʱʱ����packet_idɾ�� */
    };

    /**
    * ��ʼ�����Ӷ���
    * @param lpCallback �ص�����
    * @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
    */
    virtual int FUNCTION_CALL_MODE Create(CCallbackInterface *lpCallback) = 0;

    /**
    * ��ʼ����/ע��
    * @param uiTimeout ��ʱʱ�䣬��λ���룬0��ʾ���ȴ���ʹ�ô������ӷ�����ʱ���ò����������ã�
    * @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE Connect(unsigned int uiTimeout) = 0;

    /**
    * �Ͽ�����
    * @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE Close() = 0;

    virtual int FUNCTION_CALL_MODE Reserved1() = 0;

    virtual int FUNCTION_CALL_MODE Reserved2() = 0;

    virtual int FUNCTION_CALL_MODE Reserved3() = 0;

    virtual int FUNCTION_CALL_MODE Reserved4() = 0;

    virtual int FUNCTION_CALL_MODE Reserved5() = 0;

    virtual int FUNCTION_CALL_MODE Reserved6() = 0;

    /**
    * ȡ��������ַ
    * @param lpPort ����ķ������˿ڣ�����ΪNULL
    * @return ���ط�������ַ
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;

    /**
    * ȡ����״̬
    * @return ��������״̬
    */
    virtual int FUNCTION_CALL_MODE GetStatus() = 0;

    /**
    * ȡ���������أ�ʹ���߿���ͬʱ�����������ʵ��ͬʱ���Ӳ�ͬ�ķ�����������������ӵ�ʱ���Լ����ؾ���ʹ���ĸ�������
    * @return ���ط��������أ��Ǹ�������Խ���ʾԽ��æ�������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE GetServerLoad() = 0;

    /**
    * ȡ�������Ӧ�Ĵ�����Ϣ��Ŀǰ֧�ּ������ĺ�Ӣ�ģ�֧���������Կ���ͨ�����Ӷ�������errormsg
    * @param nErrorCode ������
    * @return ���ش�����Ϣ
    */
    virtual const char * FUNCTION_CALL_MODE GetErrorMsg(int nErrorCode) = 0;

    /**
    * ȡ���Ӵ���ţ��������޷����������ע��ʱ���ȿ�ͨ��Connect�ķ���ֵ��ȡ����ţ�
    * Ҳ��ͨ�����ñ���������ȡ����ţ�Ȼ���øô���ŵ���GetErrorMsg�ɻ�ȡ�ɶ��Ĵ�����Ϣ
    * @return �������Ӵ����
    */
    virtual int FUNCTION_CALL_MODE GetConnectError() = 0;

    /**
    * ����ҵ������
    * @param iFunID      ���ܺ�
    * @param lpPacker    �����ָ��
    * @param nAsy        0��ʾͬ���������ʾ�첽
    * @param iSystemNo   ���iSystemNo > 0������ϵͳ��
    * @param nCompressID ��ҵ��������ѹ����ѹ���㷨ID��Ŀǰֻ֧��ID = 1��ѹ���㷨��
    * ID = 0��ʾ��ѹ����ע�⣬ѹ��ֻ����SDK������飬�Ƿ�����ѹ����ȡ���ڰ���ʵ�ʴ�С��
    * ͬ�����͵İ���ͨ������RecvBiz�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBiz��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

    /**
    * ����ҵ������
    * @param hSend            ���;����SendBiz�ĳɹ�����ֵ��
    * @param lppUnPackerOrStr �������ֵ����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����2����ʾ�յ���ҵ�������Ϣ��*lppUnPackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    *                         �������ֵ����3����ʾҵ������ʧ�ܡ�*lppUnPackerOrStrԭ����ָ������ݲ��ᱻ�ı䡣
    * @param uiTimeout        ��ʱʱ�䣬��λ���롣
    * @param uiFlag           ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������RecvBiz�����գ�
    *                         JustRemoveHandle��ʾ�����ճ�ʱ�󣬰�hSend�������ɾ��
    * @return С��0��ʾRecvBiz��������ʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ע�⣡�ⲿָ����ָ��Ľ�������ڴ���SDK�ڲ������ⲿ�����ͷţ�
    */
    virtual int FUNCTION_CALL_MODE RecvBiz(int hSend, void **lppUnPackerOrStr, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;
};

extern "C"
{
    /**
	* ��ȡT2_SDK�İ汾��
	* @return ��ǰT2_SDK�İ汾�ţ�Ŀǰ�汾Ϊ0x01000002����ʾ1.0.0.2
	*/
    int FUNCTION_CALL_MODE GetVersionInfo();

    /**
	* ��ȡһ��ʵ��CConfigInterface�ӿڵ����ָ��
	* @return ʵ��CConfigInterface�ӿڵ����ָ��
	*/
CConfigInterface* FUNCTION_CALL_MODE NewConfig();

    /**
	* ��ȡһ��ʵ��CConnectionInterface�ӿڵ����ָ��
	* @param CConfigInterface ʵ��CConfigInterface�ӿڵ����ָ��
	* @returnʵ��CConnectionInterface�ӿڵ����ָ��
	*/
CConnectionInterface* FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig);

/**
* @param int iVersion ҵ�����ʽ�汾(ȡֵ:1 �ִ���,����ֵ 0x20��)
* �Ƽ�ʹ��0x20��
* @return IPacker * ������ӿ�ָ��
*/
IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);

/**
* @param void * lpBuffer Ҫ��������ݣ�����ARͨ�Ű�ͷ��
* @param unsigned int iLen ���ݳ���
* @return IUnPacker * ����������ӿ�ָ��
*/
IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);

/**
* @param char *EncodePass ������ɢ�н�����ַ��������Ȳ�����16������'\0'��
* @param const char* Password ����Ĵ�ɢ�е�����
* @param int Key Ӱ��ɢ�н����һ������
* @return char * ������ɢ�н����ַ��ͬEncodePass
*/
char * FUNCTION_CALL_MODE Encode(char *EncodePass, const char* Password, int Key);
}

#endif
