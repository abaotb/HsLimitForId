
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Management;
using System.Threading;
using System.IO;
using System.Runtime.InteropServices;



namespace HsLimitForId
{
    public partial class Form1 : Form
    {
        [DllImport("kernel32.dll")]
        static extern uint GetTickCount();

        #region 写日志
        public void WriteLogFile(string input)
        {
            /**/
            ///指定日志文件的目录
            ///
            string Name = DateTime.Now.ToString("yyyyMMdd");
            string fname = Directory.GetCurrentDirectory() + "\\Log\\" + Name + ".txt";
            /**/
            ///定义文件信息对象

            FileInfo finfo = new FileInfo(fname);

            if (!finfo.Exists)
            {
                FileStream fs;
                fs = File.Create(fname);
                fs.Close();
                finfo = new FileInfo(fname);
            }

            /**/
            ///判断文件是否存在以及是否大于2K
            if (finfo.Length > 1024 * 1024 * 10)
            {
                /**/
                ///文件超过10MB则重命名
                File.Move(Directory.GetCurrentDirectory() + "\\Log\\" + Name + ".txt", Directory.GetCurrentDirectory() + DateTime.Now.TimeOfDay + "\\LogFile.txt");
                /**/
                ///删除该文件
                //finfo.Delete();
            }
            //finfo.AppendText();
            /**/
            ///创建只写文件流

            using (FileStream fs = finfo.OpenWrite())
            {
                /**/
                ///根据上面创建的文件流创建写数据流
                StreamWriter w = new StreamWriter(fs);

                /**/
                ///设置写数据流的起始位置为文件流的末尾
                w.BaseStream.Seek(0, SeekOrigin.End);

                /**/
                ///写入“Log Entry : ”
                w.Write("\n\rLog Entry : ");

                /**/
                ///写入当前系统时间并换行
                w.Write("{0} {1} \n\r", DateTime.Now.ToLongTimeString(),
                    DateTime.Now.ToLongDateString());

                /**/
                ///写入日志内容并换行
                w.Write(input + "\n\r");

                /**/
                ///写入------------------------------------“并换行
                w.Write("------------------------------------\n\r");

                /**/
                ///清空缓冲区内容，并把缓冲区内容写入基础流
                w.Flush();

                /**/
                ///关闭写数据流
                w.Close();
            }

        }
        #endregion

        #region 变量定义
        HsT2sdk hsClient = new HsT2sdk();
        public string sOper;
        public string sPwd;
        public Boolean bAdd;
        public Boolean bDel;
        public string sPreDate;
        #endregion
        #region 恒生接口 权限删除增加
        public int HsLimitAdd(String strFundAcc, char cLimit, out string strSerial, out string strErrInfo1)
        {

            int iRet = -1, iHandle;
            strSerial = "";
            strErrInfo1 = "";
            StringBuilder strErrInfo = new StringBuilder(2048);
            StringBuilder strBuffer = new StringBuilder(2048);
            hsClient.PsBeginPack();
            hsClient.PsAddField("op_branch_no", 'I');
            hsClient.PsAddField("menu_id", 'I');
            hsClient.PsAddField("user_type", 'C');
            hsClient.PsAddField("op_entrust_way", 'C');

            hsClient.PsAddField("function_id", 'I');
            hsClient.PsAddField("operator_no", 'I');
            hsClient.PsAddField("op_password", 'S');
            hsClient.PsAddField("op_station", 'S');
            hsClient.PsAddField("audit_action", 'C');
            hsClient.PsAddField("action_in", 'C');
            hsClient.PsAddField("client_id", 'I');
            hsClient.PsAddField("fund_account", 'I');
            hsClient.PsAddField("single_restriction", 'C');
            hsClient.PsAddField("remark", 'S');
            hsClient.PsAddInt(8888);
            hsClient.PsAddInt(200210);
            hsClient.PsAddChar(' ');
            hsClient.PsAddChar('4');
            hsClient.PsAddInt(200115);
            hsClient.PsAddInt(Convert.ToInt32(sOper));
            hsClient.PsAddStr(sPwd);
            hsClient.PsAddStr(GetHostMacAddress());
            hsClient.PsAddChar('0');
            hsClient.PsAddChar('0');

            hsClient.PsAddInt(Convert.ToInt32(strFundAcc));
            hsClient.PsAddInt(Convert.ToInt32(strFundAcc));
            hsClient.PsAddChar(cLimit);
            hsClient.PsAddStr("自动出入金限制增加K");
            hsClient.PsEndpack();
            iHandle = hsClient.PsSendBiz(200115, strErrInfo);
            if (iHandle <= 0)
            {
                textBox1.AppendText(strFundAcc + "添加限制失败K:" + strErrInfo.ToString() + "\r\n");
                strErrInfo1 = strErrInfo.ToString();
                Thread.Sleep(1000);
                return iRet;
            }
            else
            {
                iRet = hsClient.PsRecvBiz(iHandle, strBuffer, strErrInfo, "serial_no");
                if (iRet != 0)
                {
                    textBox1.AppendText(strFundAcc + "添加限制失败K:" + strErrInfo.ToString() + "\r\n");
                    strErrInfo1 = strErrInfo.ToString();

                }
                else
                {
                    strBuffer.Length = strBuffer.Length - 1;
                    strSerial = strBuffer.ToString();
                }

            }

            return iRet;
        }
        public int HsLimitDel(string strFundAcc, int iDate, int iSerial, out string strErrInfo1)
        {

            int iRet = -1;
            int iHandle;
            StringBuilder strErrInfo = new StringBuilder(2048);
            StringBuilder strBuffer = new StringBuilder(2048);
            hsClient.PsBeginPack();
            hsClient.PsAddField("op_branch_no", 'I');
            hsClient.PsAddField("menu_id", 'I');
            hsClient.PsAddField("user_type", 'C');
            hsClient.PsAddField("op_entrust_way", 'C');
            hsClient.PsAddField("function_id", 'I');
            hsClient.PsAddField("operator_no", 'I');
            hsClient.PsAddField("op_password", 'S');
            hsClient.PsAddField("op_station", 'S');
            hsClient.PsAddField("audit_action", 'C');
            hsClient.PsAddField("action_in", 'C');
            hsClient.PsAddField("client_id", 'I');
            hsClient.PsAddField("fund_account", 'I');
            hsClient.PsAddField("occur_date", 'I');
            hsClient.PsAddField("remark", 'S');
            hsClient.PsAddField("serial_no", 'I');
            hsClient.PsAddInt(8888);
            hsClient.PsAddInt(200210);
            hsClient.PsAddChar(' ');
            hsClient.PsAddChar('4');
            hsClient.PsAddInt(200116);
            hsClient.PsAddInt(Convert.ToInt32(sOper));
            hsClient.PsAddStr(sPwd);
            hsClient.PsAddStr(GetHostMacAddress());
            hsClient.PsAddChar('0');
            hsClient.PsAddChar('0');

            hsClient.PsAddInt(Convert.ToInt32(strFundAcc));
            hsClient.PsAddInt(Convert.ToInt32(strFundAcc));
            // iDate = 20140609;
            hsClient.PsAddInt(iDate);
            hsClient.PsAddStr("自动出入金限制删除");
            hsClient.PsAddInt(iSerial);
            hsClient.PsEndpack();
            iHandle = hsClient.PsSendBiz(200116, strErrInfo);
            if (iHandle <= 0)
            {
                textBox1.AppendText(strFundAcc + "删除限制失败:" + strErrInfo.ToString() + "\r\n");
                strErrInfo1 = strErrInfo.ToString();
                Thread.Sleep(1000);
                return iRet;
            }
            else
            {
                iRet = hsClient.PsRecvBiz(iHandle, strBuffer, strErrInfo, "serial_no");
                if (iRet != 0)
                {
                    textBox1.AppendText(strFundAcc + "删除限制失败:" + strErrInfo.ToString() + "\r\n");

                }
            }
            strErrInfo1 = strErrInfo.ToString();
            return iRet;
        }
        private int XmlLimitAdd()
        {

            #region 删流水             //20150827 tangb
            XmlDocument doc = new XmlDocument();
            doc.Load("palsword.xml");
            XmlElement root1 = doc.DocumentElement;
            XmlNode ListNode = root1.SelectSingleNode("SerialList");
            XmlNodeList nodelist = ListNode.ChildNodes;
            try
            {
                ListNode.RemoveAll();
            }
            catch (System.Exception ex)
            {
                WriteLogFile(DateTime.Now.ToString() + "自动删除本地节点有误，原因为" + ex.ToString());

            }
            finally
            {
                try
                {
                    doc.Save("palsword.xml");
                    WriteLogFile("日志保存成功");
                }
                catch (System.Exception ex)
                {
                    WriteLogFile("日志保存失败,原因为" + ex.ToString());
                }
            }
            #endregion


            string strSerial = "";
            string strErrInfo1 = "";
            string strFundAccount = "";
            string strList = "";
            int iRet = -1;
            XmlDocument myDoc = new XmlDocument();
            myDoc.Load("palsword.xml");
            XmlElement root = myDoc.DocumentElement;
            //XmlElement root = doc.DocumentElement;
            XmlNode IdNode = root.SelectSingleNode("FundAccountList");
            XmlNode SerialNode = root.SelectSingleNode("SerialList");

            strList = IdNode.Attributes["IdList"].Value;

            int iIndex = 0;
            int iCount = 0;
            //             //进度条
            //             this.progressBar1.Minimum = 0;
            //             this.progressBar1.Maximum = nodelist.Count; ;
            //             this.progressBar1.Value = 0;
            while (iIndex >= 0)
            {
                try
                {
                    WriteLogFile("自动开始添加流水记录");
                    iIndex = GetId(strList, iIndex, ref strFundAccount);
                    WriteLogFile("自动开始添加流水记录，资金帐号：" + strFundAccount);
                    if (strFundAccount == "")
                        continue;
                    iRet = -1;
                    for (int i = 0; i < 3; ++i)
                    {

                        iRet = HsLimitAdd(strFundAccount, 'K', out strSerial, out strErrInfo1);
                        if (iRet == 0)
                        {
                            WriteLogFile("自动添加流水记录成功，资金帐号：" + strFundAccount + "流水号：" + strSerial);
                            XmlAttribute fund_account = myDoc.CreateAttribute("fund_account");
                            fund_account.Value = strFundAccount;
                            XmlAttribute occur_date = myDoc.CreateAttribute("occur_date");
                            occur_date.Value = sPreDate;
                            XmlAttribute serial = myDoc.CreateAttribute("serial");
                            serial.Value = strSerial;

                            XmlNode newElem = myDoc.CreateNode("element", "element", "");
                            newElem.Attributes.Append(fund_account);
                            newElem.Attributes.Append(occur_date);
                            newElem.Attributes.Append(serial);
                            //将节点添加到文档中
                            SerialNode.AppendChild(newElem);
                            iCount++;
                            break;
                        }
                    }
                    /* for (int i = 0; i < 3; ++i)
                     {

                         iRet = HsLimitAdd(strFundAccount, 'L', out strSerial, out strErrInfo1);
                         if (iRet == 0)
                         {
                             WriteLogFile("自动添加流水记录成功，资金帐号：" + strFundAccount + "流水号：" + strSerial);
                             XmlAttribute fund_account = myDoc.CreateAttribute("fund_account");
                             fund_account.Value = strFundAccount;
                             XmlAttribute occur_date = myDoc.CreateAttribute("occur_date");
                             occur_date.Value = DateTime.Now.ToString("yyyyMMdd");
                             XmlAttribute serial = myDoc.CreateAttribute("serial");
                             serial.Value = strSerial;

                             XmlNode newElem = myDoc.CreateNode("element", "element", "");
                             newElem.Attributes.Append(fund_account);
                             newElem.Attributes.Append(occur_date);
                             newElem.Attributes.Append(serial);
                             //将节点添加到文档中
                             SerialNode.AppendChild(newElem);
                             iCount++;
                             break;
                         }
                     }*/

                    //     this.progressBar1.Value++;
                }
                catch (Exception ex)
                {

                }
                finally
                {
                    try
                    {
                        myDoc.Save("palsword.xml");
                        WriteLogFile("日志保存成功");
                    }
                    catch
                    {
                        WriteLogFile("日志保存失败");
                    }
                }
            }
            // this.progressBar1.Value = 0;
            return iCount;
        }
        private int XmlLimitDel()
        {
            string strDate = "";
            string strSerial = "";
            string strFundaccount = "";
            string strErrInfo1 = "";
            int iRet = -1;
            XmlDocument doc = new XmlDocument();
            doc.Load("palsword.xml");
            XmlElement root = doc.DocumentElement;
            XmlNode ListNode = root.SelectSingleNode("SerialList");
            XmlNodeList nodelist = ListNode.ChildNodes;
            int iIndex = 0;
            int iCount = 0;

            //进度条
            this.progressBar1.Minimum = 0;
            this.progressBar1.Maximum = nodelist.Count; ;
            this.progressBar1.Value = 0;

            //记录按钮可用性，删除时不可用
            bool aotu = BtnStart.Enabled;
            bool oper = btn_sgpl.Enabled;
            this.BtnStart.Enabled = false;
            this.btn_sgpl.Enabled = false;
            //批量删除
            foreach (XmlNode node in nodelist)
            {
                try
                {
                    WriteLogFile("自动开始删除流水记录");
                    strDate = node.Attributes["occur_date"].Value;
                    strSerial = node.Attributes["serial"].Value;
                    strFundaccount = node.Attributes["fund_account"].Value;
                    WriteLogFile("自动开始删除流水记录，资金帐号：" + strFundaccount + "流水号：" + strSerial);
                    iRet = -1;
                    // for (int i = 0; i < 3; ++i)
                    {
                        strErrInfo1 = "";
                        //Thread.Sleep(100);
                        Thread.Sleep(Convert.ToInt32(this.textBox3.Text.ToString().Trim()));
                        iRet = HsLimitDel(strFundaccount, Convert.ToInt32(strDate), Convert.ToInt32(strSerial), out strErrInfo1);

                    }
                    iCount++;

                }
                catch (Exception ex)
                {
                    WriteLogFile(DateTime.Now.ToString()
                        + strFundaccount + "流水号：" + strSerial
                        + " 没删   自动删除接口节点有误，原因为" + ex.ToString());
                    continue;                              //继续下一条
                }

                this.progressBar1.Value++;
            }  
            #region 注释
            //一次性删本地流水
           /*
            try
            {
                ListNode.RemoveAll();
            }
            catch (System.Exception ex)
            {
                WriteLogFile(DateTime.Now.ToString() + "自动删除本地节点有误，原因为" + ex.ToString());

            }
            finally
            {
                try
                {
                    doc.Save("palsword.xml");
                    WriteLogFile("日志保存成功");
                }
                catch (System.Exception ex)
                {
                    WriteLogFile("日志保存失败,原因为" + ex.ToString());
                }
            }
            */
            /*  while (nodelist.Count > 0 && iIndex < nodelist.Count)
              {
                  try
                  {
                      WriteLogFile("自动开始删除流水记录");
                      XmlNode node = nodelist.Item(iIndex);
                      strDate = node.Attributes["occur_date"].Value;
                      strSerial = node.Attributes["serial"].Value;
                      strFundaccount = node.Attributes["fund_account"].Value;
                      WriteLogFile("自动开始删除流水记录，资金帐号：" + strFundaccount + "流水号：" + strSerial);
                      iRet = -1;
                      for (int i = 0; i < 3; ++i)
                      {
                          strErrInfo1 = "";
                          iRet = HsLimitDel(strFundaccount, Convert.ToInt32(strDate), Convert.ToInt32(strSerial), out strErrInfo1);
                          //不看返回结果    tangb  20150717
                          //if (iRet == 0)
                          //{
                          //    ListNode.RemoveChild(nodelist.Item(iIndex));
                          //    iCount++;
                          //    break;
                          //}
                          //if (strErrInfo1.IndexOf("不存在") > 0)
                          //{
                          //    ListNode.RemoveChild(nodelist.Item(iIndex));
                          //    iCount++;
                          //    break;
                          //}
                      }
                      //nodelist.Item(iIndex).RemoveAll();
                      try
                      {
                          ListNode.RemoveChild(node);//nodelist.Item(iIndex));
                      }
                      catch (System.Exception ex)
                      {
                          WriteLogFile(DateTime.Now.ToString() + "删除节点有误，原因为"+ex.ToString());
                          continue;
                      }
                   
                      iCount++;
                      //if (iRet != 0)
                      //{
                      //    iIndex++;
                      //}
                  }
                  finally
                  {
                      try
                      {
                          doc.Save("palsword.xml");
                          WriteLogFile("日志保存成功");
                      }
                      catch (System.Exception ex)
                      {
                          WriteLogFile("日志保存失败,原因为"+ex.ToString());
                      }
                  }

                  this.progressBar1.Value++;
              }*/
            #endregion
            //还原可用性
            this.BtnStart.Enabled = aotu;
            this.btn_sgpl.Enabled = oper;
            this.progressBar1.Value = 0;
            return iCount;
        }
        private void SingleLimitDel(string strFundAccountIn)
        {
            string strDate = "";
            string strSerial = "";
            string strFundaccount = "";
            string strErrInfo1 = "";
            int iRet = -1;
            XmlDocument doc = new XmlDocument();
            doc.Load("palsword.xml");
            XmlElement root = doc.DocumentElement;
            XmlNode ListNode = root.SelectSingleNode("SerialList");
            XmlNodeList nodelist = ListNode.ChildNodes;
            int iIndex = 0;
            while (nodelist.Count > 0 && iIndex < nodelist.Count)
            {
                XmlNode node = nodelist.Item(iIndex);
                strDate = node.Attributes["occur_date"].Value;
                strSerial = node.Attributes["serial"].Value;
                strFundaccount = node.Attributes["fund_account"].Value;
                iRet = -1;
                if (strFundAccountIn == strFundaccount)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        iRet = HsLimitDel(strFundaccount, Convert.ToInt32(strDate), Convert.ToInt32(strSerial), out strErrInfo1);
                        if (iRet == 0)
                        {
                            WriteLogFile("手动删除流水记录成功，资金帐号：" + strFundaccount + "流水号：" + strSerial);
                            ListNode.RemoveChild(nodelist.Item(iIndex));
                            break;
                        }
                    }
                }
                if (iRet != 0)
                {
                    iIndex++;
                }

            }
            doc.Save("palsword.xml");
        }
        private void SingleLimitAdd(string strFundAccount)
        {
            string strSerial = "";
            string strErrInfo1 = "";
            // string strFundAccount = "";
            int iRet = -1;
            XmlDocument myDoc = new XmlDocument();
            myDoc.Load("palsword.xml");
            XmlElement root = myDoc.DocumentElement;
            //XmlElement root = doc.DocumentElement;
            //XmlNode IdNode = root.SelectSingleNode("FundAccountList");
            XmlNode SerialNode = root.SelectSingleNode("SerialList");
            //XmlNodeList nodelist = IdNode.ChildNodes;
            //foreach (XmlNode node in nodelist)
            {

                //   strFundAccount = node.Attributes["fund_account"].Value;

                for (int i = 0; i < 3; ++i)
                {

                    iRet = HsLimitAdd(strFundAccount, 'K', out strSerial, out strErrInfo1);
                    if (iRet == 0)
                    {
                        WriteLogFile("手动添加流水记录成功，资金帐号：" + strFundAccount + "流水号：" + strSerial);
                        XmlAttribute fund_account = myDoc.CreateAttribute("fund_account");
                        fund_account.Value = strFundAccount;
                        XmlAttribute occur_date = myDoc.CreateAttribute("occur_date");
                        occur_date.Value = sPreDate;
                        XmlAttribute serial = myDoc.CreateAttribute("serial");
                        serial.Value = strSerial;

                        XmlNode newElem = myDoc.CreateNode("element", "element", "");
                        newElem.Attributes.Append(fund_account);
                        newElem.Attributes.Append(occur_date);
                        newElem.Attributes.Append(serial);
                        //将节点添加到文档中
                        SerialNode.AppendChild(newElem);
                        break;
                    }
                }
                /*  for (int i = 0; i < 3; ++i)
                  {

                      iRet = HsLimitAdd(strFundAccount, 'L', out strSerial, out strErrInfo1);
                      if (iRet == 0)
                      {
                          WriteLogFile("手动添加流水记录成功，资金帐号：" + strFundAccount + "流水号：" + strSerial);
                          XmlAttribute fund_account = myDoc.CreateAttribute("fund_account");
                          fund_account.Value = strFundAccount;
                          XmlAttribute occur_date = myDoc.CreateAttribute("occur_date");
                          occur_date.Value = sPreDate;
                          XmlAttribute serial = myDoc.CreateAttribute("serial");
                          serial.Value = strSerial;

                          XmlNode newElem = myDoc.CreateNode("element", "element", "");
                          newElem.Attributes.Append(fund_account);
                          newElem.Attributes.Append(occur_date);
                          newElem.Attributes.Append(serial);
                          //将节点添加到文档中
                          SerialNode.AppendChild(newElem);
                          break;
                      }
                  }*/
            }

            myDoc.Save("palsword.xml");
        }
        #endregion



        public Form1()
        {
            InitializeComponent();

        }
        public string GetHostMacAddress()
        {
            string mac = "";// = string.Empty; 

            ManagementClass mc = new ManagementClass("Win32_NetworkAdapterConfiguration");

            ManagementObjectCollection moc = mc.GetInstances();

            foreach (ManagementObject mo in moc)
            {

                if (mo["IPEnabled"].ToString() == "True")
                {
                    mac = mo["MacAddress"].ToString();
                    break;
                }

            }
            string OutMac = string.Empty;
            OutMac = OutMac + mac.Substring(0, 2);
            OutMac = OutMac + mac.Substring(3, 2);
            OutMac = OutMac + mac.Substring(6, 2);
            OutMac = OutMac + mac.Substring(9, 2);
            OutMac = OutMac + mac.Substring(12, 2);
            OutMac = OutMac + mac.Substring(15, 2);
            return OutMac;

        }

        private int GetId(string IdList, int iIndex, ref string strId)
        {
            strId = "";
            int iEndIndex = iIndex;
            while (iIndex < IdList.Length && iEndIndex < IdList.Length)
            {
                if (IdList[iEndIndex] == ',')
                {
                    break;
                }
                else
                {
                    iEndIndex++;
                }
            }
            if (iEndIndex <= IdList.Length)
            {
                strId = IdList.Substring(iIndex, iEndIndex - iIndex);
                iIndex = iEndIndex + 1;
            }
            else
                iIndex = -1;
            return iIndex;
        }
        /// <summary>
        /// 是否是双休日和节假日
        /// </summary>
        /// <param name="date"></param>当天日期
        /// <returns></returns>是否是节假日
        public bool methodIsHoliday(string date)
        {

            if (DateTime.Now.DayOfWeek == DayOfWeek.Saturday || DateTime.Now.DayOfWeek == DayOfWeek.Sunday)
            {
                return true;
            }



            XmlDocument myDoc = new XmlDocument();
            myDoc.Load("节假日表.xml");

            XmlElement root = myDoc.DocumentElement;

            XmlNodeList holiday = root.ChildNodes;


            foreach (XmlNode xmlnode in holiday)
            {
                if (date.Equals(xmlnode.InnerText.ToString().Trim()))
                {
                    return true;
                }

            }
            return false;
        }
        //定时器
        private void timer1_Tick(object sender, EventArgs e)
        {
            //是否是双休日和节假日
            bool is_holiday = this.methodIsHoliday(DateTime.Now.ToString("yyyy-MM-dd"));

            //如果是新的一天，重置增加和删除标志
            if (!is_holiday && DateTime.Now.ToString("yyyyMMdd") == sPreDate)
            {

                //删除权限结束，更新删除标志
                if (Convert.ToInt32(DateTime.Now.ToString("HHmm")) > Convert.ToInt32(txtStartTime.Text.Trim()) && !bDel)
                {
                    //如果自动操作按钮不可用，说明现在是自动操作
                    if (BtnStart.Enabled == false)
                    {
                        //去重账号
                        this.methodCompareAcount();
                        try
                        {

                            //流水备份
                            if (!Directory.Exists(@"./备份"))
                                Directory.CreateDirectory(@"./备份");
                            string time = DateTime.Now.ToString("yyyyMMddHHmmss");
                            string filename = time /*DateTime.Now.ToString("yyyyMMdd")*/ + ".xml";
                            File.Copy("palsword.xml", @"./备份/" + filename, true);

                        }
                        catch (System.Exception ex)
                        {
                            WriteLogFile(DateTime.Now.ToString() + "备份文件有误");
                            return;
                        }

                        textBox1.AppendText(DateTime.Now.ToString() + " 批量 允许恒生出入金 开始\r\n");
                        int iRet = XmlLimitDel();
                        bDel = true;
                        textBox1.AppendText(DateTime.Now.ToString() + " 批量 允许恒生出入金 完成!删除记录数[" + iRet.ToString() + "]\r\n");


                    }
                }
                if (Convert.ToInt32(DateTime.Now.ToString("HHmm")) > Convert.ToInt32(txtEndTime.Text.Trim()) && bDel && !bAdd)
                {
                    textBox1.AppendText(DateTime.Now.ToString() + " 批量 禁止恒生出入金 开始\r\n");
                    int iRet = XmlLimitAdd();
                    bAdd = true;
                    textBox1.AppendText(DateTime.Now.ToString() + " 批量 禁止恒生出入金 完成!添加记录数[" + iRet.ToString() + "]\r\n");
                }
                //增加权限结束，更新增加标志

            }
            else
            {
                bAdd = false;
                bDel = false;
                sPreDate = DateTime.Now.ToString("yyyyMMdd");
            }



        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (textBox2.Text.Trim() == "")
            { }
            else
            {
                SingleLimitDel(textBox2.Text);
                textBox1.AppendText(DateTime.Now.ToString() + " 客户" + textBox2.Text + " 允许恒生出入金\r\n");
                WriteLogFile(DateTime.Now.ToString() + " 客户" + textBox2.Text + " 允许恒生出入金");

            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            if (textBox2.Text.Trim() == "")
            { }
            else
            {
                SingleLimitAdd(textBox2.Text);
                textBox1.AppendText(DateTime.Now.ToString() + " 客户" + textBox2.Text + " 禁止恒生出入金" + "\r\n");
                WriteLogFile(DateTime.Now.ToString() + " 客户" + textBox2.Text + " 禁止恒生出入金");
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {

            WriteLogFile(DateTime.Now.ToString() + "  点击启动");

            StringBuilder strErrInfo1 = new StringBuilder(200);
            StringBuilder strBuffer = new StringBuilder(2048);

            int iRet;

            iRet = hsClient.PsConnect("license.dat", "123456", strErrInfo1);
            if (iRet != 0)
                textBox1.AppendText(strErrInfo1.ToString() + "\n\r");

            else
            {

                btnOpen.Enabled = true;
                btnClose.Enabled = true;
                timer1.Enabled = true;
                sOper = txtOper.Text.Trim();
                sPwd = txtPwd.Text.Trim();
                txtOper.Enabled = false;
                txtPwd.Enabled = false;
                txtEndTime.Enabled = false;
                txtStartTime.Enabled = false;


                BtnStart.Enabled = false;
                btn_sgpl.Enabled = true;
            }

        }

        private void button1_Click_1(object sender, EventArgs e)
        {

            textBox1.AppendText(GetHostMacAddress());
        }

        //手工批量操作   tangb  20150717
        private void btn_sgpl_Click(object sender, EventArgs e)
        {
            WriteLogFile(DateTime.Now.ToString() + "  手工批量");

            StringBuilder strErrInfo1 = new StringBuilder(200);
            StringBuilder strBuffer = new StringBuilder(2048);

            int iRet;

            iRet = hsClient.PsConnect("license.dat", "123456", strErrInfo1);
            if (iRet != 0)
                textBox1.AppendText(strErrInfo1.ToString() + "\n\r");

            else
            {

                btnOpen.Enabled = true;
                btnClose.Enabled = true;
                sOper = txtOper.Text.Trim();
                sPwd = txtPwd.Text.Trim();
                txtOper.Enabled = false;
                txtPwd.Enabled = false;
                txtEndTime.Enabled = false;
                txtStartTime.Enabled = false;

                BtnStart.Enabled = true;
                btn_sgpl.Enabled = false;
            }


            //如果是新的一天，重置增加和删除标志
            if (DateTime.Now.ToString("yyyyMMdd") == sPreDate)
            {
                //如果手动操作按钮不可用，说明现在是手动操作
                if (btn_sgpl.Enabled == false)
                {

                    //删除权限结束，更新删除标志
                    if (Convert.ToInt32(DateTime.Now.ToString("HHmm")) > Convert.ToInt32(txtStartTime.Text.Trim()))
                    {
                        string filenamesource = DateTime.Now.ToString("yyyyMMdd") + ".xml";
                        //                         string filename = DateTime.Now.ToString("yyyyMMdd") + "_手动批量.xml";
                        //                         File.Copy(filenamesource, filename, true);

                        textBox1.AppendText(DateTime.Now.ToString() + " 手动批量 允许恒生出入金 开始\r\n");
                        iRet = BatchLimitDel("palsword.xml");//filenamesource);

                        textBox1.AppendText(DateTime.Now.ToString() + " 手动批量 允许恒生出入金 完成!删除记录数[" + iRet.ToString() + "]\r\n");
                    }

                }

            }
            else
            {
                sPreDate = DateTime.Now.ToString("yyyyMMdd");
            }

        }
        //手工批量操作   tangb  20150717
        public int BatchLimitDel(string file)
        {
            string strDate = "";
            string strSerial = "";
            string strFundaccount = "";
            string strErrInfo1 = "";
            int iRet = -1;
            XmlDocument doc = new XmlDocument();
            doc.Load(file);// ("palsword.xml");
            XmlElement root = doc.DocumentElement;
            XmlNode ListNode = root.SelectSingleNode("SerialList");
            XmlNodeList nodelist = ListNode.ChildNodes;
            int iIndex = 0;
            int iCount = 0;

            //进度条
            this.progressBar1.Minimum = 0;
            this.progressBar1.Maximum = nodelist.Count; ;
            this.progressBar1.Value = 0;

            //记录按钮可用性，删除时不可用
            bool aotu = BtnStart.Enabled;
            bool oper = btn_sgpl.Enabled;
            this.BtnStart.Enabled = false;
            this.btn_sgpl.Enabled = false;
            int CountTotal = nodelist.Count;
            while (nodelist.Count > 0 && iIndex < nodelist.Count)
            {
                try
                {
                    WriteLogFile("手工开始删除流水记录");
                    XmlNode node = nodelist.Item(iIndex);
                    strDate = node.Attributes["occur_date"].Value;
                    strSerial = node.Attributes["serial"].Value;
                    strFundaccount = node.Attributes["fund_account"].Value;
                    WriteLogFile("手工开始删除流水记录，资金帐号：" + strFundaccount + "流水号：" + strSerial);
                    iRet = -1;
                    //for (int i = 0; i < 3; ++i)
                    {
                        strErrInfo1 = "";
                        iRet = HsLimitDel(strFundaccount, Convert.ToInt32(strDate), Convert.ToInt32(strSerial), out strErrInfo1);

                    }
                    iIndex++;
                    iCount++;
                    //手工批量不删流水
                }
                catch (Exception ex)
                {
                    WriteLogFile("手工开始删除流水记录有误,原因是：" + ex.ToString());
                }

                this.progressBar1.Value++;
            }
            //还原可用性
            this.BtnStart.Enabled = aotu;
            this.btn_sgpl.Enabled = oper;
            this.progressBar1.Value = 0;
            return iCount;
        }
        //去重账号
        public void methodCompareAcount()
        {
            try
            {
                XmlDocument myDoc = new XmlDocument();
                myDoc.Load("palsword.xml");
                XmlElement root = myDoc.DocumentElement;
                //XmlElement root = doc.DocumentElement;
                XmlNode IdNode = root.SelectSingleNode("FundAccountList");

                string str = IdNode.Attributes["IdList"].Value;
                string[] strLists = str.Split(',');
                List<string> list = new List<string>();

                for (int i = 0; i < strLists.Length; i++)
                {
                    list.Add(strLists[i]);
                }
                //去重
                List<string> list2 = list.Distinct().ToList();

                str = "";
                for (int i = 0; i < list2.Count - 1; i++)
                {
                    str = str + list2[i] + ",";
                }
                str = str + list2[list2.Count - 1];

                IdNode.Attributes["IdList"].Value = str;
                myDoc.Save("palsword.xml");
            }
            catch (System.Exception ex)
            {

            }

        }
        //退出
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            WriteLogFile(DateTime.Now.ToString() + "  退出");

        }
        //开启
        private void Form1_Load(object sender, EventArgs e)
        {
            WriteLogFile(DateTime.Now.ToString() + "  开启");
        }
    }
}
