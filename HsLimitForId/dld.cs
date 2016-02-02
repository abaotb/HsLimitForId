using System;
//2. 添加所需的命名空间及声明参数传递方式枚举：
using System.Runtime.InteropServices; // 用 DllImport 需用此 命名空间 
using System.Reflection; // 使用 Assembly 类需用此 命名空间 
using System.Reflection.Emit; // 使用 ILGenerator 需用此 命名空间 

namespace HsLimitForId
{
    class dld
    {
        //在“public class dld”上面添加如下代码声明参数传递方式枚举：
        /// <summary> 
        /// 参数传递方式枚举 ,ByValue 表示值传递 ,ByRef 表示址传递 
        /// </summary> 
        public enum ModePass
        {
            ByValue = 0x0001,
            ByRef = 0x0002
        }

        //3. 声明LoadLibrary、GetProcAddress、FreeLibrary及私有变量hModule和farProc：
        /// <summary> 
        /// 原型是 :HMODULE LoadLibrary(LPCTSTR lpFileName); 
        /// </summary> 
        /// <param name="lpFileName">DLL 文件名 </param> 
        /// <returns> 函数库模块的句柄 </returns> 
        [DllImport("kernel32.dll")]
        static extern IntPtr LoadLibrary(string lpFileName);

        /// <summary> 
        /// 原型是 : FARPROC GetProcAddress(HMODULE hModule, LPCWSTR lpProcName); 
        /// </summary> 
        /// <param name="hModule"> 包含需调用函数的函数库模块的句柄 </param> 
        /// <param name="lpProcName"> 调用函数的名称 </param> 
        /// <returns> 函数指针 </returns> 
        [DllImport("kernel32.dll")]
        static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);

        /// <summary> 
        /// 原型是 : BOOL FreeLibrary(HMODULE hModule); 
        /// </summary> 
        /// <param name="hModule"> 需释放的函数库模块的句柄 </param> 
        /// <returns> 是否已释放指定的 Dll</returns> 
        [DllImport("kernel32", EntryPoint = "FreeLibrary", SetLastError = true)]
        static extern bool FreeLibrary(IntPtr hModule);

        /// <summary> 
        /// Loadlibrary 返回的函数库模块的句柄 
        /// </summary> 
        private IntPtr hModule = IntPtr.Zero;

        /// <summary> 
        /// GetProcAddress 返回的函数指针 
        /// </summary> 
        private IntPtr farProc = IntPtr.Zero;

        //4. 添加LoadDll方法，并为了调用时方便，重载了这个方法：
        /// <summary> 
        /// 装载 Dll 
        /// </summary> 
        /// <param name="lpFileName">DLL 文件名 </param> 
        public void LoadDll(string lpFileName)
        {
            hModule = LoadLibrary(lpFileName);
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpFileName + "."));
        }

        //若已有已装载Dll的句柄，可以使用LoadDll方法的第二个版本：

        public void LoadDll(IntPtr HMODULE)
        {
            if (HMODULE == IntPtr.Zero)
                throw (new Exception(" 所传入的函数库模块的句柄 HMODULE 为空 ."));
            hModule = HMODULE;
        }

        public Delegate Invoke(string lpProcName, Type t)
        {// 若函数库模块的句柄为空，则抛出异常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函数库模块的句柄为空 , 请确保已进行 LoadDll 操作 !"));

            // 取得函数指针 
            farProc = GetProcAddress(hModule, lpProcName);

            // 若函数指针，则抛出异常 
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpProcName + " 这个函数的入口点 "));
            return (Delegate)Marshal.GetDelegateForFunctionPointer(farProc, t);
        }

        //5. 添加LoadFun方法，并为了调用时方便，也重载了这个方法，方法的具体代码及注释如下：
        /// <summary> 
        /// 获得函数指针 
        /// </summary> 
        /// <param name="lpProcName"> 调用函数的名称 </param> 
        public void LoadFun(string lpProcName)
        { // 若函数库模块的句柄为空，则抛出异常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函数库模块的句柄为空 , 请确保已进行 LoadDll 操作 !"));

            // 取得函数指针 
            farProc = GetProcAddress(hModule, lpProcName);

            // 若函数指针，则抛出异常 
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpProcName + " 这个函数的入口点 "));
        }

        /// <summary> 
        /// 获得函数指针 
        /// </summary> 
        /// <param name="lpFileName"> 包含需调用函数的 DLL 文件名 </param> 
        /// <param name="lpProcName"> 调用函数的名称 </param> 
        public void LoadFun(string lpFileName, string lpProcName)
        { // 取得函数库模块的句柄 
            hModule = LoadLibrary(lpFileName);

            // 若函数库模块的句柄为空，则抛出异常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpFileName + "."));

            // 取得函数指针 
            farProc = GetProcAddress(hModule, lpProcName);

            // 若函数指针，则抛出异常 
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpProcName + " 这个函数的入口点 "));
        }

        //6. 添加UnLoadDll及Invoke方法，Invoke方法也进行了重载：
        /// <summary> 
        /// 卸载 Dll 
        /// </summary> 
        public void UnLoadDll()
        {
            FreeLibrary(hModule);
            hModule = IntPtr.Zero;
            farProc = IntPtr.Zero;
        }

        //Invoke方法的第一个版本：
        /// <summary> 
        /// 调用所设定的函数 
        /// </summary> 
        /// <param name="ObjArray_Parameter"> 实参 </param> 
        /// <param name="TypeArray_ParameterType"> 实参类型 </param> 
        /// <param name="ModePassArray_Parameter"> 实参传送方式 </param> 
        /// <param name="Type_Return"> 返回类型 </param> 
        /// <returns> 返回所调用函数的 object</returns> 
        public object Invoke(object[] ObjArray_Parameter, Type[] TypeArray_ParameterType, ModePass[] ModePassArray_Parameter, Type Type_Return)
        {
            // 下面 3 个 if 是进行安全检查 , 若不能通过 , 则抛出异常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函数库模块的句柄为空 , 请确保已进行 LoadDll 操作 !"));

            if (farProc == IntPtr.Zero)
                throw (new Exception(" 函数指针为空 , 请确保已进行 LoadFun 操作 !"));

            if (ObjArray_Parameter.Length != ModePassArray_Parameter.Length)
                throw (new Exception(" 参数个数及其传递方式的个数不匹配 ."));

            // 下面是创建 MyAssemblyName 对象并设置其 Name 属性 
            AssemblyName MyAssemblyName = new AssemblyName();
            MyAssemblyName.Name = "InvokeFun";

            // 生成单模块配件 
            AssemblyBuilder MyAssemblyBuilder = AppDomain.CurrentDomain.DefineDynamicAssembly(MyAssemblyName, AssemblyBuilderAccess.Run);
            ModuleBuilder MyModuleBuilder = MyAssemblyBuilder.DefineDynamicModule("InvokeDll");

            // 定义要调用的方法 , 方法名为“ MyFun ”，返回类型是“ Type_Return ”参数类型是“ TypeArray_ParameterType ” 
            MethodBuilder MyMethodBuilder = MyModuleBuilder.DefineGlobalMethod("MyFun", MethodAttributes.Public | MethodAttributes.Static, Type_Return, TypeArray_ParameterType);

            // 获取一个 ILGenerator ，用于发送所需的 IL 
            ILGenerator IL = MyMethodBuilder.GetILGenerator();

            LocalBuilder[] locals = new LocalBuilder[TypeArray_ParameterType.Length];
            for (int i = 0; i < TypeArray_ParameterType.Length; i++)
            {
                locals[i] = IL.DeclareLocal(TypeArray_ParameterType[i], true);
            }
            for (int i = 0; i < ObjArray_Parameter.Length; i++)
            {// 用循环将参数依次压入堆栈 
                switch (ModePassArray_Parameter[i])
                {
                    case ModePass.ByValue:
                        IL.Emit(OpCodes.Ldarg, i);
                        break;
                    case ModePass.ByRef:
                        IL.Emit(OpCodes.Ldarga, i);
                        //IL.Emit(OpCodes.Ldarg_1);
                        //EmitFastInt(IL, i);
                        //IL.Emit(OpCodes.Ldelem_Ref);
                        //if (locals[i].LocalType.IsValueType)
                        //{
                        //    IL.Emit(OpCodes.Unbox_Any, TypeArray_ParameterType[i]);
                        //}
                        //else
                        //{
                        //    IL.Emit(OpCodes.Castclass, TypeArray_ParameterType[i]);
                        //}
                        //IL.Emit(OpCodes.Stloc, locals[i]);
                        break;
                    default:
                        throw (new Exception(" 第 " + (i + 1).ToString() + " 个参数没有给定正确的传递方式 ."));
                }
            }

            //if (!MyMethodBuilder.IsStatic)
            //    IL.Emit(OpCodes.Ldarg_0);

            //for (int i = 0; i < TypeArray_ParameterType.Length; i++)
            //{
            //    if (TypeArray_ParameterType[i].IsByRef)
            //        IL.Emit(OpCodes.Ldloca_S, locals[i]);
            //    else
            //        IL.Emit(OpCodes.Ldloc, locals[i]);
            //}

            //if (MyMethodBuilder.IsStatic)
            //    IL.EmitCall(OpCodes.Call, MyMethodBuilder, null);
            //else
            //    IL.EmitCall(OpCodes.Callvirt, MyMethodBuilder, null);

            //if (MyMethodBuilder.ReturnType == typeof(void))
            //    IL.Emit(OpCodes.Ldnull);
            //else if (Type_Return.IsValueType)
            //    IL.Emit(OpCodes.Box, MyMethodBuilder.ReturnType);

            //for (int i = 0; i < TypeArray_ParameterType.Length; i++)
            //{
            //    if (TypeArray_ParameterType[i].IsByRef)
            //    {
            //        IL.Emit(OpCodes.Ldarg_1);
            //        EmitFastInt(IL, i);
            //        IL.Emit(OpCodes.Ldloc, locals[i]);
            //        if (locals[i].LocalType.IsValueType)
            //            IL.Emit(OpCodes.Box, locals[i].LocalType);
            //        IL.Emit(OpCodes.Stelem_Ref);
            //    }
            //}

            if (IntPtr.Size == 4)
            {// 判断处理器类型 
                IL.Emit(OpCodes.Ldc_I4, farProc.ToInt32());
            }
            else if (IntPtr.Size == 8)
            {
                IL.Emit(OpCodes.Ldc_I8, farProc.ToInt64());
            }
            else
            {
                throw new PlatformNotSupportedException();
            }

            IL.EmitCalli(OpCodes.Calli, CallingConvention.StdCall, Type_Return, TypeArray_ParameterType);
            IL.Emit(OpCodes.Ret); // 返回值 
            MyModuleBuilder.CreateGlobalFunctions();

            // 取得方法信息 
            MethodInfo MyMethodInfo = MyModuleBuilder.GetMethod("MyFun");
            return MyMethodInfo.Invoke(null, ObjArray_Parameter);// 调用方法，并返回其值 
        }

        //Invoke方法的第二个版本，它是调用了第一个版本的：
        /// <summary> 
        /// 调用所设定的函数 
        /// </summary> 
        /// <param name="IntPtr_Function"> 函数指针 </param> 
        /// <param name="ObjArray_Parameter"> 实参 </param> 
        /// <param name="TypeArray_ParameterType"> 实参类型 </param> 
        /// <param name="ModePassArray_Parameter"> 实参传送方式 </param> 
        /// <param name="Type_Return"> 返回类型 </param> 
        /// <returns> 返回所调用函数的 object</returns> 
        public object Invoke(IntPtr IntPtr_Function, object[] ObjArray_Parameter, Type[] TypeArray_ParameterType, ModePass[] ModePassArray_Parameter, Type Type_Return)
        {
            // 下面 2 个 if 是进行安全检查 , 若不能通过 , 则抛出异常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函数库模块的句柄为空 , 请确保已进行 LoadDll 操作 !"));

            if (IntPtr_Function == IntPtr.Zero)
                throw (new Exception(" 函数指针 IntPtr_Function 为空 !"));

            farProc = IntPtr_Function;
            return Invoke(ObjArray_Parameter, TypeArray_ParameterType, ModePassArray_Parameter, Type_Return);
        }

        private void EmitFastInt(ILGenerator il, int value)
        {
            switch (value)
            {
                case -1:
                    il.Emit(OpCodes.Ldc_I4_M1);
                    return;
                case 0:
                    il.Emit(OpCodes.Ldc_I4_0);
                    return;
                case 1:
                    il.Emit(OpCodes.Ldc_I4_1);
                    return;
                case 2:
                    il.Emit(OpCodes.Ldc_I4_2);
                    return;
                case 3:
                    il.Emit(OpCodes.Ldc_I4_3);
                    return;
                case 4:
                    il.Emit(OpCodes.Ldc_I4_4);
                    return;
                case 5:
                    il.Emit(OpCodes.Ldc_I4_5);
                    return;
                case 6:
                    il.Emit(OpCodes.Ldc_I4_6);
                    return;
                case 7:
                    il.Emit(OpCodes.Ldc_I4_7);
                    return;
                case 8:
                    il.Emit(OpCodes.Ldc_I4_8);
                    return;
            }
        }
    }
}