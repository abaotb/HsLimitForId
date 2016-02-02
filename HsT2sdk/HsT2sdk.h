// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 HST2SDK_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// HST2SDK_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef HST2SDK_EXPORTS
#define HST2SDK_API __declspec(dllexport)
#else
#define HST2SDK_API __declspec(dllimport)
#endif


#include "..\T2sdk\t2sdk_interface.h"

/*
// 此类是从 TradeApi.dll 导出的
class CTraderSpi : public CThostFtdcTraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
virtual void OnFrontConnected();

};
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
typedef int (WINAPI *CBOnFrontConnected)();
*/

