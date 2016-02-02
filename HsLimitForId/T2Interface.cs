using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Runtime.InteropServices;

namespace HsLimitForId
{
    class HsT2sdk
    {
        private dld funs = new dld();
        public HsT2sdk( /*= "tcp://asp-sim2-front1.financial-trading-platform.com:26205"*/)
        {
            

            DirectoryInfo curDir = new DirectoryInfo(Directory.GetCurrentDirectory());
            //20130508 hujie 以资金帐号单独建立文件夹，保存TradeApi.dll




            funs.LoadDll(curDir.FullName + "\\" + "HsT2sdk.dll");	//使用绝对路径,解决需要拷贝官方dll到程序目录的问题
            Directory.SetCurrentDirectory(curDir.FullName);
        }
        #region 连接
        public int PsConnect( string strFile, string strPwd, StringBuilder sErrInfo )
        {
            
            return (funs.Invoke("Connect", typeof(connect)) as connect)( strFile, strPwd, sErrInfo);
        }
        delegate int connect(string strFile, string strPwd, StringBuilder sErrInfo);

        public int PsSendBiz(int iFundNo, StringBuilder sErrInfo)
        {

            return (funs.Invoke("SendBiz", typeof(SendBiz)) as SendBiz)(iFundNo,  sErrInfo);
        }
        delegate int SendBiz(int iFundNo, StringBuilder sErrInfo);

        public int PsRecvBiz(int hSend,  StringBuilder sBuffer, StringBuilder sErrInfo, string strName="")
        {

            return (funs.Invoke("RecvBiz", typeof(RecvBiz)) as RecvBiz)(hSend, sBuffer, sErrInfo, strName);
        }
        delegate int RecvBiz(int hSend, StringBuilder sBuffer,  StringBuilder sErrInfo, string strName = "");

        public int PsConnRelease()
        {

            return (funs.Invoke("ConnRelease", typeof(ConnRelease)) as ConnRelease)();
        }
        delegate int ConnRelease();
        #endregion
        #region 打包
        public int PsBeginPack()
        {

            return (funs.Invoke("BeginPack", typeof(BeginPack)) as BeginPack)();
        }
        delegate int BeginPack();
        public int PsEndpack()
        {

            return (funs.Invoke("Endpack", typeof(Endpack)) as Endpack)();
        }
        delegate int Endpack();

        public int PsPackFree()
        {

            return (funs.Invoke("Endpack", typeof(PackFree)) as PackFree)();
        }
        delegate int PackFree();
        //*@param cFieldType ：字段类型:I整数，F浮点数，C字符，S字符串，R任意二进制数据
        public int PsAddField(string szFieldName, char cFieldType = 'S')
        {

            return (funs.Invoke("AddField", typeof(AddField)) as AddField)(szFieldName, cFieldType);
        }
        delegate int AddField(string szFieldName,char cFieldType ='S');
        public int PsAddStr(string szValue)
        {

            return (funs.Invoke("AddStr", typeof(AddStr)) as AddStr)(szValue);
        }
        delegate int AddStr(string szValue);
        public int PsAddInt(int iValue)
        {

            return (funs.Invoke("AddInt", typeof(AddInt)) as AddInt)(iValue);
        }
        delegate int AddInt(int iValue);
        public int PsAddDouble(double fValue)
        {

            return (funs.Invoke("AddDouble", typeof(AddDouble)) as AddDouble)(fValue);
        }
        delegate int AddDouble(double fValue);
        public int PsAddChar(char cValue)
        {

            return (funs.Invoke("AddChar", typeof(AddChar)) as AddChar)(cValue);
        }
        delegate int AddChar(char cValue);

        public int PsNewDataSet(string strName)
        {

            return (funs.Invoke("NewDataSet", typeof(NewDataSet)) as NewDataSet)(strName);
        }
        delegate int NewDataSet(string strName);

        public int PsGetPackBufSize()
        {

            return (funs.Invoke("GetPackBufSize", typeof(GetPackBufSize)) as GetPackBufSize)();
        }
        delegate int GetPackBufSize();
        public int PsGetPackLen()
        {

            return (funs.Invoke("GetPackLen", typeof(GetPackLen)) as GetPackLen)();
        }
        delegate int GetPackLen();




        #endregion
        #region 解包
        public int PsGetDatasetCount()
        {

            return (funs.Invoke("GetDatasetCount", typeof(GetDatasetCount)) as GetDatasetCount)();
        }
        delegate int GetDatasetCount( );
        public int PsSetCurrentDatasetByIndex()
        {

            return (funs.Invoke("SetCurrentDatasetByIndex", typeof(SetCurrentDatasetByIndex)) as SetCurrentDatasetByIndex)();
        }
        delegate int SetCurrentDatasetByIndex();
        public int PsGetColCount()
        {

            return (funs.Invoke("GetColCount", typeof(GetColCount)) as GetColCount)();
        }
        delegate int GetColCount();
        public int PsGetColName(int iColumn)
        {

            return (funs.Invoke("GetColName", typeof(GetColName)) as GetColName)( iColumn);
        }
        delegate int GetColName(int iColumn);
        public int PsGetColType(int iColumn)
        {

            return (funs.Invoke("GetColType", typeof(GetColType)) as GetColType)( iColumn);
        }
        delegate int GetColType(int iColumn);
        public string PsGetStr(string strColName)
        {

            return (funs.Invoke("GetStr", typeof(GetStr)) as GetStr)(strColName);
        }
        delegate string GetStr(string strColName);

        public double PsGetDouble(string strColName)
        {

            return (funs.Invoke("GetDouble", typeof(GetDouble)) as GetDouble)(strColName);
        }
        delegate double GetDouble(string strColName);

        public int PsGetInt(string strColName)
        {

            return (funs.Invoke("GetInt", typeof(GetInt)) as GetInt)(strColName);
        }
        delegate int GetInt(string strColName);
        public char PsGetChar(string strColName)
        {

            return (funs.Invoke("GetChar", typeof(GetChar)) as GetChar)(strColName);
        }
        delegate char GetChar(string strColName);

        public void PsNext()
        {

            (funs.Invoke("Next", typeof(Next)) as Next)();
        }
        delegate void Next();
        public int PsIsEOF()
        {

            return  (funs.Invoke("IsEOF", typeof(IsEOF)) as IsEOF)();
        }
        delegate int IsEOF();
        public void PsUnPackerFree()
        {

            (funs.Invoke("UnPackerFree", typeof(UnPackerFree)) as UnPackerFree)();
        }
        delegate void UnPackerFree();

        #endregion


    }
}
