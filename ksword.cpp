#include "ksword.h"

//Ksword规范消息函数=========================================
//信息提示[ * ]
void KMesInfo(const char* text) {
	cprint("[ * ]", 9, 15);
	std::cout << text << std::endl;
}
void KMesInfo(std::string text) {
	cprint("[ * ]", 9, 15);
	std::cout << text << std::endl;
}

//警告提示[ ! ]
void KMesWarn(std::string text) {
	cprint("[ * ]", 6, 0);
	std::cout << text << std::endl;
}
void KMesWarn(const char* text) {
	cprint("[ * ]", 6, 0);
	std::cout << text << std::endl;
}

//错误提示[ X ]
void KMesErr(std::string text) {
	cprint("[ X ]", 7, 4);
	std::cout << text << std::endl;
}
void KMesErr(const char* text) {
	cprint("[ X ]", 7, 4);
	std::cout << text << std::endl;
}

//控制台窗口属性操控函数=====================================
//置顶与取消置顶函数
bool SetTopWindow() {
	HWND hWnd = GetConsoleWindow(); // 获取控制台窗口句柄
	if (hWnd != NULL) {
		// 将窗口置顶
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(KSWORD_PRINT_DEBUG_INFO)KMesInfo("窗口已被置顶");
		return KSWORD_SUCCESS_EXIT;
	} else {
		if(KSWORD_PRINT_DEBUG_INFO)KMesErr("获取句柄失败");
		return KSWORD_ERROE_EXIT;
	}
}
bool UnTopWindow() {
	HWND hWnd = GetConsoleWindow(); // 获取控制台窗口句柄
	if (hWnd != NULL) {
		// 取消窗口置顶
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(KSWORD_PRINT_DEBUG_INFO)KMesInfo("置顶取消");
		return KSWORD_SUCCESS_EXIT;
	} else {
		if(KSWORD_PRINT_DEBUG_INFO)KMesErr("获取句柄失败");
		return KSWORD_ERROE_EXIT;
	}
}
bool KTopWindow() {
	HWND hWnd = ::GetForegroundWindow();
	HWND hForeWnd = NULL;
	DWORD dwForeID = 0;
	DWORD dwCurID = 0;

	hForeWnd = ::GetForegroundWindow();
	dwCurID = ::GetCurrentThreadId();
	dwForeID = ::GetWindowThreadProcessId(hForeWnd, NULL);
	::AttachThreadInput(dwCurID, dwForeID, TRUE);
	::ShowWindow(hWnd, SW_SHOWNORMAL);
	::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	::SetForegroundWindow(hWnd);
	// 将前台窗口线程贴附到当前线程（也就是程序A中的调用线程）
	::AttachThreadInput(dwCurID, dwForeID, FALSE);
	if (KSWORD_PRINT_DEBUG_INFO)KMesInfo("窗口成功置顶！");
	return KSWORD_SUCCESS_EXIT;
//原文链接：https://blog.csdn.net/weixin_45525272/article/details/116452142
}
//隐藏与取消隐藏函数
bool HideWindow() {
	HWND hWnd = GetConsoleWindow();
	if (hWnd != NULL) {
		ShowWindow(hWnd, SW_HIDE);
		KMesInfo("窗口已经隐藏");
		return KSWORD_SUCCESS_EXIT;
	} else {
		KMesErr("获取句柄失败！");
		return KSWORD_ERROE_EXIT;
	}
}
bool ShowWindow() {
	HWND hWnd = GetConsoleWindow();
	if (hWnd != NULL) {
		ShowWindow(hWnd, SW_SHOW);
		KMesInfo("窗口状态设置为显示");
		return KSWORD_SUCCESS_EXIT;
	} else {
		KMesErr("获取句柄失败!");
		return KSWORD_ERROE_EXIT;
	}
}
//隐藏窗口边框
bool HideSide() {
	// 获取控制台窗口的句柄
	HWND hWnd = GetConsoleWindow();
	// 获取窗口的当前样式
	LONG style = GetWindowLong(hWnd, GWL_STYLE);
	// 移除窗口样式中的窗口边框和标题栏标志
	style &= ~(WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU);
	// 应用新的样式
	SetWindowLong(hWnd, GWL_STYLE, style);
	// 更新窗口以反映新的样式
	SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	return KSWORD_SUCCESS_EXIT;
}
//窗口全屏
bool KFullScreen() {
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
	/* 设置窗口信息 最大化 取消标题栏及边框 */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
	KMesInfo("成功使用WindowsAPI全屏！");
	return KSWORD_SUCCESS_EXIT;
}
bool KResetWindow() {
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
    LONG l_WinExStyle = GetWindowLong(hwnd, GWL_EXSTYLE); /* 获取扩展窗口样式 */

    /* 恢复窗口样式，移除最大化样式，添加标题栏及边框 */
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle & ~WS_POPUP & ~WS_MAXIMIZE) | WS_CAPTION | WS_THICKFRAME | WS_BORDER);
    SetWindowLong(hwnd, GWL_EXSTYLE, l_WinExStyle | WS_EX_WINDOWEDGE); // 添加窗口边缘样式

    /* 恢复窗口到原始大小和位置，这里假设原始大小和位置是屏幕的一半 */
    SetWindowPos(hwnd, NULL, 0, 0, cx / 2, cy / 2, SWP_NOZORDER | SWP_FRAMECHANGED);

    KMesInfo("成功使用WindowsAPI脱离全屏！");
    return KSWORD_SUCCESS_EXIT;
}
//原文链接：https ://blog.csdn.net/linuxwuj/article/details/81165885
bool FullScreen() {
	COORD font_size;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	/* 字体信息 */
	struct CONSOLE_FONT
	{
		DWORD index;
		COORD dim;
	} cfi;
	typedef COORD(WINAPI* PROCGETCONSOLEFONTSIZE)(HANDLE, DWORD);
	typedef BOOL(WINAPI* PROCGETCURRENTCONSOLEFONT)(HANDLE, BOOL, struct CONSOLE_FONT*);

	HMODULE hKernel32 = GetModuleHandle("kernel32");
	PROCGETCONSOLEFONTSIZE GetConsoleFontSize = (PROCGETCONSOLEFONTSIZE)GetProcAddress(hKernel32, "GetConsoleFontSize");
	PROCGETCURRENTCONSOLEFONT GetCurrentConsoleFont = (PROCGETCURRENTCONSOLEFONT)GetProcAddress(hKernel32, "GetCurrentConsoleFont");

	GetCurrentConsoleFont(handle, FALSE, &cfi);             /* 获取当前字体索引信息 */
	font_size = GetConsoleFontSize(handle, cfi.index);      /* 获取当前字体宽高信息[字符宽度及高度所占像素数] */
//原文链接：https ://blog.csdn.net/linuxwuj/article/details/81165885
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 */
	char cmd[32] = { 0 };
	sprintf(cmd, "MODE CON: COLS=%d LINES=%d", cx / font_size.X, cy / font_size.Y);
	KMesInfo(cmd);
	system(cmd);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
	KMesInfo("成功全屏");
	return KSWORD_SUCCESS_EXIT;
}
//隐藏与显示指针
bool ShowCursor() {
	HANDLE h_GAME = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h_GAME != NULL) {
		CONSOLE_CURSOR_INFO cursor_info;
		GetConsoleCursorInfo(h_GAME, &cursor_info);
		cursor_info.bVisible = true;
		SetConsoleCursorInfo(h_GAME, &cursor_info);;
		return KSWORD_SUCCESS_EXIT;
	}
	else {
		KMesErr("获取句柄失败！");
		return KSWORD_ERROE_EXIT;
	}
}
//原文链接：https://blog.csdn.net/qq_43312665/article/details/86790176
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//原文链接：https://blog.csdn.net/qq_33866593/article/details/104597731

//更改指针位置（从左到右；从上往下）
void SetCursor(int x, int y) {
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
	return;
}
//彩色输出文本（文本内容，前景色，背景色）
//0 = 黑色 8 = 灰色
//1 = 蓝色 9 = 淡蓝色
//2 = 绿色 10 = 淡绿色
//3 = 浅绿色 11 = 淡浅绿色
//4 = 红色 12 = 淡红色
//5 = 紫色 13 = 淡紫色
//6 = 黄色 14 = 淡黄色
//7 = 白色 15 = 亮白色
void cprint(const char* text, int front_color, int back_color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | back_color * 16 | FOREGROUND_INTENSITY | front_color);
	printf(text);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
	return;
}
void cprint(std::string text, int front_color, int back_color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | back_color * 16 | FOREGROUND_INTENSITY | front_color);
	printf(text.c_str());
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
	return;
}
//相关函数来源：https://blog.csdn.net/qq_42885747/article/details/103835671

//修改控制台窗口标题内容
//void SetTitle(const char* text) {
//	SetConsoleTitleW(text);
//	return;
//}
//void SetTitle(std::string text) {
//	SetConsoleTitleW(text.c_str());
//	return;
//}

//环境探测函数===============================================
//探测Windows系统版本：
	// Win95:1;
	// Win98:2;
	// WinMe:3
	// Win2000:4;
	// WinXP:5;
	// Win Vista:6;
	// Win7:7;
	// Win8:8;
	// Win8.1:9;
	// Win10:10;
	// Win11:11;
int WinVer() {

	//首先判断是否是win11，如果不是再往后判断
	OSVERSIONINFOEX osvi = { sizeof(OSVERSIONINFOEX), 0, 0, 0, 0, {0}, 0, 0, 0, 0 };
	ULONGLONG condMask = VerSetConditionMask(
		VerSetConditionMask(
			VerSetConditionMask(
				0, VER_MAJORVERSION, VER_GREATER_EQUAL),
			VER_MINORVERSION, VER_GREATER_EQUAL),
		VER_BUILDNUMBER, VER_GREATER_EQUAL);

	osvi.dwMajorVersion = 10;
	osvi.dwMinorVersion = 0;
	osvi.dwBuildNumber = 22000;
	osvi.wServicePackMajor = 0;
	osvi.wServicePackMinor = 0;

	if (VerifyVersionInfo(
		&osvi,
		VER_MAJORVERSION | VER_MINORVERSION | VER_BUILDNUMBER | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
		condMask) != FALSE)
	if (KSWORD_PRINT_DEBUG_INFO) {
		KMesInfo("探测到该操作系统版本为"); KMesInfo("Win11 or later");
	}
	return 11;

	std::string vname;
	//先判断是否为win8.1或win10
	typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibrary("ntdll.dll");
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		vname = "Microsoft Windows 8.1";
		if (KSWORD_PRINT_DEBUG_INFO) {
			KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
		}
		return 9;
	}
	if (dwMajor == 10 && dwMinor == 0)	//win 10
	{
		vname = "Microsoft Windows 10";
		if (KSWORD_PRINT_DEBUG_INFO) {
			KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
		}
		return 10;
	}
	//判断win8.1以下的版本
	SYSTEM_INFO info;                //用SYSTEM_INFO结构判断64位AMD处理器  
	GetSystemInfo(&info);            //调用GetSystemInfo函数填充结构  
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((OSVERSIONINFO*)&os))
	{
		//下面根据版本信息判断操作系统名称  
		switch (os.dwMajorVersion)
		{                        //判断主版本号  
		case 4:
			switch (os.dwMinorVersion)
			{                //判断次版本号  
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					vname = "Microsoft Windows NT 4.0";  //1996年7月发布  
				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
					vname = "Microsoft Windows 95";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 1;
				break;
			case 10:
				vname = "Microsoft Windows 98";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 2;
				break;
			case 90:
				vname = "Microsoft Windows Me";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 3;
				break;
			}
			break;
		case 5:
			switch (os.dwMinorVersion)
			{               //再比较dwMinorVersion的值  
			case 0:
				vname = "Microsoft Windows 2000";    //1999年12月发布  
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 4;
				break;
			case 1:
				vname = "Microsoft Windows XP";      //2001年8月发布  
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 5;
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION &&
					info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					vname = "Microsoft Windows XP Professional x64 Edition";
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					vname = "Microsoft Windows Server 2003";   //2003年3月发布  
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
					vname = "Microsoft Windows Server 2003 R2";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}return 5;
				break;
			}
			break;
		case 6:
			switch (os.dwMinorVersion)
			{
			case 0:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows Vista";
				else
					vname = "Microsoft Windows Server 2008";   //服务器版本  
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 6;
				break;

			case 1:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 7";
				else
					vname = "Microsoft Windows Server 2008 R2";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 7;
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 8";
				else
					vname = "Microsoft Windows Server 2012";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("探测到该操作系统版本为"); KMesInfo(vname);
				}
				return 8;
				break;
			}
			break;
		default:
			vname = "未知操作系统";
			if (KSWORD_PRINT_DEBUG_INFO) {
				KMesErr(vname);
			}
			return 0;

		}
	}
	else {
		vname = "未知操作系统";
		if (KSWORD_PRINT_DEBUG_INFO) {
			KMesErr(vname);
		}
		return 0;
	}
	//原文链接：https ://blog.csdn.net/qq78442761/article/details/64440535
}
//探测CPU整体利用率，返回0~100整数作为当前百分比值
__int64 CompareFileTime(FILETIME time1, FILETIME time2)
{
	__int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
	__int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;

	return (b - a);
}
//WIN CPU使用情况  

int CPUUsage() {
	HANDLE hEvent;
	BOOL res;
	FILETIME preidleTime;
	FILETIME prekernelTime;
	FILETIME preuserTime;
	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;

	res = GetSystemTimes(&idleTime, &kernelTime, &userTime);
	preidleTime = idleTime;
	prekernelTime = kernelTime;
	preuserTime = userTime;

	hEvent = CreateEventA(NULL, FALSE, FALSE, NULL); // 初始值为 nonsignaled ，并且每次触发后自动设置为nonsignaled  

	
		WaitForSingleObject(hEvent, 1000);
		res = GetSystemTimes(&idleTime, &kernelTime, &userTime);

		__int64 idle = CompareFileTime(preidleTime, idleTime);
		__int64 kernel = CompareFileTime(prekernelTime, kernelTime);
		__int64 user = CompareFileTime(preuserTime, userTime);

		__int64 cpu = (kernel + user - idle) * 100 / (kernel + user);
		__int64 cpuidle = (idle) * 100 / (kernel + user);
		return cpu;

		preidleTime = idleTime;
		prekernelTime = kernelTime;
		preuserTime = userTime;
	
}

//探测内存百分比，返回0~100整数作为当前百分比值
int RAMUsage() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memInfo)) {
		DWORDLONG totalPhys = memInfo.ullTotalPhys;
		DWORDLONG availablePhys = memInfo.ullAvailPhys;
		DWORDLONG usedPhys = totalPhys - availablePhys;
		int memoryUsagePercent = static_cast<int>((usedPhys * 100) / totalPhys);
		return memoryUsagePercent;
	}
	else {
		if( KSWORD_PRINT_DEBUG_INFO )KMesErr("获取内存占用率失败");
		return -1;
	}
}
//探测内存容量，返回容量（GB）（向上取整）
int RAMSize() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memInfo)) {
		DWORDLONG totalPhys = memInfo.ullTotalPhys;
		// 转换为GB，1 GB = 1024 * 1024 * 1024字节
		double totalMemoryGB = totalPhys / 1073741824.0;
		// 向上取整
		return static_cast<int>(totalMemoryGB) + (totalMemoryGB - static_cast<int>(totalMemoryGB) > 0 ? 1 : 0);
	}
	else {
		if (KSWORD_PRINT_DEBUG_INFO)
			KMesErr("获取内存容量失败");
		return 0;
	}
	return 0;
}
//探测内存容量，返回容量（MB）（向下取整）
int RAMSizeMB() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memInfo)) {
		DWORDLONG totalPhys = memInfo.ullTotalPhys;
		// 转换为MB，1 MB = 1024 * 1024字节
		int totalMemoryMB = static_cast<int>(totalPhys / (1024 * 1024));
		return totalMemoryMB;
	}
	else {
		if (KSWORD_PRINT_DEBUG_INFO)
			KMesErr("获取内存容量失败");
		return 0;
	}
	return 0;
}
//获取系统盘盘符：返回盘符
char SystemDrive() {
	char systemDrive[3] = { 0 };
	GetEnvironmentVariableA("SYSTEMDRIVE", systemDrive, sizeof(systemDrive));
	std::string msgtmp;
	msgtmp += "探测到系统盘盘符：";
	msgtmp += systemDrive[0];
	if (KSWORD_PRINT_DEBUG_INFO)KMesErr(msgtmp);
	return systemDrive[0];
}
//获取指定盘可用空间（-1：该盘不存在）
int FreeSpaceOfDrive(char driveLetter) {
	ULARGE_INTEGER freeBytesAvailable;
	ULARGE_INTEGER totalNumberOfBytes;
	ULARGE_INTEGER totalNumberOfFreeBytes;
	// 构建驱动器路径，如 "C:\"
	char drivePath[4] = { driveLetter, ':', '\\', '\0' };
	// 获取驱动器的剩余空间
	if (GetDiskFreeSpaceEx(drivePath, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
		// 将字节转换为兆字节，1 MB = 1024 * 1024 字节
		return static_cast<int>(freeBytesAvailable.QuadPart / (1024 * 1024));
	}
	else {
		if (KSWORD_PRINT_DEBUG_INFO)KMesErr("找不到驱动器，无法计算可用空间");
		// 如果函数调用失败，返回-1
		return -1;
	}
}
//探测是否虚拟机
	//返回：0：非虚拟机
	// 1：VMware系列
	// 2：VPC系列
int IsVM() {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return 0;
}
bool IsInsideVPC() {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return 0;
}
bool IsInsideVMWare() {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return 0;
}


//操作函数==================================================
//异步执行cmd命令
void RunCmdAsyn(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void RunCmdAsyn(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
//实时回显执行cmd命令
int RunCmdNow(const char* cmd) {
	char MsgBuff[1024];
	int MsgLen = 1020;
	FILE* fp;
	if (cmd == NULL)
	{
		return -1;
	}
	if ((fp = _popen(cmd, "r")) == NULL){
		return -2;
	}
	else
	{
		memset(MsgBuff, 0, MsgLen);
		//读取命令执行过程中的输出
		while (fgets(MsgBuff, MsgLen, fp) != NULL){
			printf("%s\n", MsgBuff);
		}
		//关闭执行的进程
		if (_pclose(fp) == -1){
			return -3;
		}
	}
	return 0;
}
int RunCmdNow(std::string stringcmd) {
	const char * cmd = stringcmd.c_str();
	char MsgBuff[1024];
	int MsgLen = 1020;
	FILE* fp;
	if (cmd == NULL){
		return -1;
	}
	if ((fp = _popen(cmd, "r")) == NULL) {
		return -2;
	} else {
		memset(MsgBuff, 0, MsgLen);
		//读取命令执行过程中的输出
		while (fgets(MsgBuff, MsgLen, fp) != NULL) {
			printf("%s\n", MsgBuff);
		}
		//关闭执行的进程
		if (_pclose(fp) == -1) {
			return -3;
		}
	}
	return 0;
}
//请求管理员权限并启动自己（程序路径）
void RequestAdmin(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void RequestAdmin(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void RequestAdmin(wchar_t text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
//计算长MD5
class MD5 {
private:
	unsigned int tempKSWORD_MD5_A, tempKSWORD_MD5_B, tempKSWORD_MD5_C, tempKSWORD_MD5_D, strlength;
public:
	MD5() {
		tempKSWORD_MD5_A = KSWORD_MD5_A;
		tempKSWORD_MD5_B = KSWORD_MD5_B;
		tempKSWORD_MD5_C = KSWORD_MD5_C;
		tempKSWORD_MD5_D = KSWORD_MD5_D;
		strlength = 0;
	}
	// F函数
	unsigned int Ksword_Md5_F(unsigned int b, unsigned int c, unsigned int d) {
		return (b & c) | ((~b) & d);
	}
	// G函数
	unsigned int Ksword_Md5_G(unsigned int b, unsigned int c, unsigned int d) {
		return (b & d) | (c & (~d));
	}
	// H函数
	unsigned int Ksword_Md5_H(unsigned int b, unsigned int c, unsigned int d) {
		return b ^ c ^ d;
	}
	// I函数
	unsigned int Ksword_Md5_I(unsigned int b, unsigned int c, unsigned int d) {
		return c ^ (b | (~d));
	}
	// 移位操作函数
	unsigned int Ksword_Md5_shift(unsigned int a, unsigned int n) {
		return (a << n) | (a >> (32 - n));
	}
	// 编码函数
	std::string Ksword_Md5_encode(std::string src) {
		std::vector<unsigned int> rec = Ksword_Md5_padding(src);
		for (unsigned int i = 0; i < strlength / 16; i++) {
			unsigned int num[16];
			for (int j = 0; j < 16; j++) {
				num[j] = rec[i * 16 + j];
			}
			Ksword_Md5_iterateFunc(num, 16);
		}
		return Ksword_Md5_format(tempKSWORD_MD5_A) + Ksword_Md5_format(tempKSWORD_MD5_B) + Ksword_Md5_format(tempKSWORD_MD5_C) + Ksword_Md5_format(tempKSWORD_MD5_D);
	}
	// 循环压缩
	void Ksword_Md5_iterateFunc(unsigned int* X, int size = 16) {
		unsigned int a = tempKSWORD_MD5_A,
			b = tempKSWORD_MD5_B,
			c = tempKSWORD_MD5_C,
			d = tempKSWORD_MD5_D,
			rec = 0,
			g, k;
		for (int i = 0; i < 64; i++) {
			if (i < 16) {
				// F迭代
				g = Ksword_Md5_F(b, c, d);
				k = i;
			}
			else if (i < 32) {
				// G迭代
				g = Ksword_Md5_G(b, c, d);
				k = (1 + 5 * i) % 16;
			}
			else if (i < 48) {
				// H迭代
				g = Ksword_Md5_H(b, c, d);
				k = (5 + 3 * i) % 16;
			}
			else {
				// I迭代
				g = Ksword_Md5_I(b, c, d);
				k = (7 * i) % 16;
			}
			rec = d;
			d = c;
			c = b;
			b = b + Ksword_Md5_shift(a + g + X[k] + ksword_md5_T[i], ksword_md5_s[i]);
			a = rec;
		}
		tempKSWORD_MD5_A += a;
		tempKSWORD_MD5_B += b;
		tempKSWORD_MD5_C += c;
		tempKSWORD_MD5_D += d;
	}
	// 填充字符串
	std::vector<unsigned int> Ksword_Md5_padding(std::string src) {
		// 以512位,64个字节为一组
		unsigned int num = ((src.length() + 8) / 64) + 1;
		std::vector<unsigned int> rec(num * 16);
		strlength = num * 16;
		for (unsigned int i = 0; i < src.length(); i++) {
			// 一个unsigned int对应4个字节，保存4个字符信息
			rec[i >> 2] |= (int)(src[i]) << ((i % 4) * 8);
		}
		// 补充1000...000
		rec[src.length() >> 2] |= (0x80 << ((src.length() % 4) * 8));
		// 填充原文长度
		rec[rec.size() - 2] = (src.length() << 3);
		return rec;
	}
	// 整理输出
	std::string Ksword_Md5_format(unsigned int num) {
		std::string res = "";
		unsigned int base = 1 << 8;
		for (int i = 0; i < 4; i++) {
			std::string tmp = "";
			unsigned int b = (num >> (i * 8)) % base & 0xff;
			for (int j = 0; j < 2; j++) {
				tmp = ksword_md5_str16[b % 16] + tmp;
				b /= 16;
			}
			res += tmp;
		}
		return res;
	}
};

std::string LMD5(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
std::string LMD5(std::string text) {
	MD5 test;
	std::string MD5tmp=test.Ksword_Md5_encode(text);
	if (KSWORD_PRINT_DEBUG_INFO) {
		KMesInfo("完成MD5转换，转换后MD5值为");
		KMesInfo(MD5tmp);
	}
	return MD5tmp;
}
//计算短MD5
std::string SMD5(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
std::string SMD5(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
//计算哈希
std::string Hash(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
std::string Hash(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
//计算文件哈希
std::string FileHash(std::string path) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
std::string FileHash(const char* path) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
std::string FileHash(wchar_t path) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	std::string a;
	return a;
}
//调用Powershell


//内核对抗函数==============================================
//获取system权限并启动自己（需要管理员权限）（程序路径）
void GetSystem(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void GetSystem(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void GetSystem(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
//驱动相关函数
	//装载驱动（驱动绝对路径，服务名称）
void LoadWinDrive(const wchar_t* texta, const wchar_t* textb) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void LoadWinDrive(const char* texta, const char* textb) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void LoadWinDrive(std::string texta, std::string textb) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
//启动服务（服务名称）
void StartDriverService(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void StartDriverService(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void StartDriverService(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
//停止服务（服务名称）
void StopDriverService(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void StopDriverService(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void StopDriverService(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
//卸载驱动（服务名称）
void UnLoadWinDrive(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void UnLoadWinDrive(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}
void UnLoadWinDrive(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return;
}

//结束进程
	//结束方法：
	//0：尝试所有方法直到进程退出（相当极端）
	//1：使用taskkill命令不带强制标识符结束进程
	//2：使用taskkill命令带强制标识符结束进程
	//3：调用TerminateProcess()函数终止进程
	//4：调用TerminateThread()函数摧毁所有线程
	//5：（内核权限）使用ZwTerminateProcess()函数结束进程
	//6：（内核权限）动态调用PspTerminateThreadByPointer结束所有进程
	//7：（内核权限）清零内存
	//通常情况下，1~3较为安全，剩余比较危险
	//返回值：1~7：使用标号对应的方法成功结束了进程；0：未能成功结束进程
	//传入值：方法标号+进程名称/PID
int KillProcess(int a, const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return 0;
}
int KillProcess(int a, std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return 0;
}
int KillProcess(int a, int b) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "相关函数正在编写中" << std::endl;
	return 0;
}





