#include "ksword.h"

//Ksword�淶��Ϣ����=========================================
//��Ϣ��ʾ[ * ]
void KMesInfo(const char* text) {
	cprint("[ * ]", 9, 15);
	std::cout << text << std::endl;
}
void KMesInfo(std::string text) {
	cprint("[ * ]", 9, 15);
	std::cout << text << std::endl;
}

//������ʾ[ ! ]
void KMesWarn(std::string text) {
	cprint("[ * ]", 6, 0);
	std::cout << text << std::endl;
}
void KMesWarn(const char* text) {
	cprint("[ * ]", 6, 0);
	std::cout << text << std::endl;
}

//������ʾ[ X ]
void KMesErr(std::string text) {
	cprint("[ X ]", 7, 4);
	std::cout << text << std::endl;
}
void KMesErr(const char* text) {
	cprint("[ X ]", 7, 4);
	std::cout << text << std::endl;
}

//����̨�������Բٿغ���=====================================
//�ö���ȡ���ö�����
bool SetTopWindow() {
	HWND hWnd = GetConsoleWindow(); // ��ȡ����̨���ھ��
	if (hWnd != NULL) {
		// �������ö�
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(KSWORD_PRINT_DEBUG_INFO)KMesInfo("�����ѱ��ö�");
		return KSWORD_SUCCESS_EXIT;
	} else {
		if(KSWORD_PRINT_DEBUG_INFO)KMesErr("��ȡ���ʧ��");
		return KSWORD_ERROE_EXIT;
	}
}
bool UnTopWindow() {
	HWND hWnd = GetConsoleWindow(); // ��ȡ����̨���ھ��
	if (hWnd != NULL) {
		// ȡ�������ö�
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(KSWORD_PRINT_DEBUG_INFO)KMesInfo("�ö�ȡ��");
		return KSWORD_SUCCESS_EXIT;
	} else {
		if(KSWORD_PRINT_DEBUG_INFO)KMesErr("��ȡ���ʧ��");
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
	// ��ǰ̨�����߳���������ǰ�̣߳�Ҳ���ǳ���A�еĵ����̣߳�
	::AttachThreadInput(dwCurID, dwForeID, FALSE);
	if (KSWORD_PRINT_DEBUG_INFO)KMesInfo("���ڳɹ��ö���");
	return KSWORD_SUCCESS_EXIT;
//ԭ�����ӣ�https://blog.csdn.net/weixin_45525272/article/details/116452142
}
//������ȡ�����غ���
bool HideWindow() {
	HWND hWnd = GetConsoleWindow();
	if (hWnd != NULL) {
		ShowWindow(hWnd, SW_HIDE);
		KMesInfo("�����Ѿ�����");
		return KSWORD_SUCCESS_EXIT;
	} else {
		KMesErr("��ȡ���ʧ�ܣ�");
		return KSWORD_ERROE_EXIT;
	}
}
bool ShowWindow() {
	HWND hWnd = GetConsoleWindow();
	if (hWnd != NULL) {
		ShowWindow(hWnd, SW_SHOW);
		KMesInfo("����״̬����Ϊ��ʾ");
		return KSWORD_SUCCESS_EXIT;
	} else {
		KMesErr("��ȡ���ʧ��!");
		return KSWORD_ERROE_EXIT;
	}
}
//���ش��ڱ߿�
bool HideSide() {
	// ��ȡ����̨���ڵľ��
	HWND hWnd = GetConsoleWindow();
	// ��ȡ���ڵĵ�ǰ��ʽ
	LONG style = GetWindowLong(hWnd, GWL_STYLE);
	// �Ƴ�������ʽ�еĴ��ڱ߿�ͱ�������־
	style &= ~(WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU);
	// Ӧ���µ���ʽ
	SetWindowLong(hWnd, GWL_STYLE, style);
	// ���´����Է�ӳ�µ���ʽ
	SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	return KSWORD_SUCCESS_EXIT;
}
//����ȫ��
bool KFullScreen() {
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
	/* ���ô�����Ϣ ��� ȡ�����������߿� */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
	KMesInfo("�ɹ�ʹ��WindowsAPIȫ����");
	return KSWORD_SUCCESS_EXIT;
}
bool KResetWindow() {
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
    LONG l_WinExStyle = GetWindowLong(hwnd, GWL_EXSTYLE); /* ��ȡ��չ������ʽ */

    /* �ָ�������ʽ���Ƴ������ʽ����ӱ��������߿� */
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle & ~WS_POPUP & ~WS_MAXIMIZE) | WS_CAPTION | WS_THICKFRAME | WS_BORDER);
    SetWindowLong(hwnd, GWL_EXSTYLE, l_WinExStyle | WS_EX_WINDOWEDGE); // ��Ӵ��ڱ�Ե��ʽ

    /* �ָ����ڵ�ԭʼ��С��λ�ã��������ԭʼ��С��λ������Ļ��һ�� */
    SetWindowPos(hwnd, NULL, 0, 0, cx / 2, cy / 2, SWP_NOZORDER | SWP_FRAMECHANGED);

    KMesInfo("�ɹ�ʹ��WindowsAPI����ȫ����");
    return KSWORD_SUCCESS_EXIT;
}
//ԭ�����ӣ�https ://blog.csdn.net/linuxwuj/article/details/81165885
bool FullScreen() {
	COORD font_size;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	/* ������Ϣ */
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

	GetCurrentConsoleFont(handle, FALSE, &cfi);             /* ��ȡ��ǰ����������Ϣ */
	font_size = GetConsoleFontSize(handle, cfi.index);      /* ��ȡ��ǰ��������Ϣ[�ַ���ȼ��߶���ռ������] */
//ԭ�����ӣ�https ://blog.csdn.net/linuxwuj/article/details/81165885
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� */
	char cmd[32] = { 0 };
	sprintf(cmd, "MODE CON: COLS=%d LINES=%d", cx / font_size.X, cy / font_size.Y);
	KMesInfo(cmd);
	system(cmd);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
	KMesInfo("�ɹ�ȫ��");
	return KSWORD_SUCCESS_EXIT;
}
//��������ʾָ��
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
		KMesErr("��ȡ���ʧ�ܣ�");
		return KSWORD_ERROE_EXIT;
	}
}
//ԭ�����ӣ�https://blog.csdn.net/qq_43312665/article/details/86790176
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//ԭ�����ӣ�https://blog.csdn.net/qq_33866593/article/details/104597731

//����ָ��λ�ã������ң��������£�
void SetCursor(int x, int y) {
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
	return;
}
//��ɫ����ı����ı����ݣ�ǰ��ɫ������ɫ��
//0 = ��ɫ 8 = ��ɫ
//1 = ��ɫ 9 = ����ɫ
//2 = ��ɫ 10 = ����ɫ
//3 = ǳ��ɫ 11 = ��ǳ��ɫ
//4 = ��ɫ 12 = ����ɫ
//5 = ��ɫ 13 = ����ɫ
//6 = ��ɫ 14 = ����ɫ
//7 = ��ɫ 15 = ����ɫ
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
//��غ�����Դ��https://blog.csdn.net/qq_42885747/article/details/103835671

//�޸Ŀ���̨���ڱ�������
//void SetTitle(const char* text) {
//	SetConsoleTitleW(text);
//	return;
//}
//void SetTitle(std::string text) {
//	SetConsoleTitleW(text.c_str());
//	return;
//}

//����̽�⺯��===============================================
//̽��Windowsϵͳ�汾��
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

	//�����ж��Ƿ���win11����������������ж�
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
		KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo("Win11 or later");
	}
	return 11;

	std::string vname;
	//���ж��Ƿ�Ϊwin8.1��win10
	typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibrary("ntdll.dll");
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		vname = "Microsoft Windows 8.1";
		if (KSWORD_PRINT_DEBUG_INFO) {
			KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
		}
		return 9;
	}
	if (dwMajor == 10 && dwMinor == 0)	//win 10
	{
		vname = "Microsoft Windows 10";
		if (KSWORD_PRINT_DEBUG_INFO) {
			KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
		}
		return 10;
	}
	//�ж�win8.1���µİ汾
	SYSTEM_INFO info;                //��SYSTEM_INFO�ṹ�ж�64λAMD������  
	GetSystemInfo(&info);            //����GetSystemInfo�������ṹ  
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((OSVERSIONINFO*)&os))
	{
		//������ݰ汾��Ϣ�жϲ���ϵͳ����  
		switch (os.dwMajorVersion)
		{                        //�ж����汾��  
		case 4:
			switch (os.dwMinorVersion)
			{                //�жϴΰ汾��  
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					vname = "Microsoft Windows NT 4.0";  //1996��7�·���  
				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
					vname = "Microsoft Windows 95";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 1;
				break;
			case 10:
				vname = "Microsoft Windows 98";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 2;
				break;
			case 90:
				vname = "Microsoft Windows Me";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 3;
				break;
			}
			break;
		case 5:
			switch (os.dwMinorVersion)
			{               //�ٱȽ�dwMinorVersion��ֵ  
			case 0:
				vname = "Microsoft Windows 2000";    //1999��12�·���  
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 4;
				break;
			case 1:
				vname = "Microsoft Windows XP";      //2001��8�·���  
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 5;
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION &&
					info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					vname = "Microsoft Windows XP Professional x64 Edition";
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					vname = "Microsoft Windows Server 2003";   //2003��3�·���  
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
					vname = "Microsoft Windows Server 2003 R2";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
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
					vname = "Microsoft Windows Server 2008";   //�������汾  
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 6;
				break;

			case 1:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 7";
				else
					vname = "Microsoft Windows Server 2008 R2";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 7;
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 8";
				else
					vname = "Microsoft Windows Server 2012";
				if (KSWORD_PRINT_DEBUG_INFO) {
					KMesInfo("̽�⵽�ò���ϵͳ�汾Ϊ"); KMesInfo(vname);
				}
				return 8;
				break;
			}
			break;
		default:
			vname = "δ֪����ϵͳ";
			if (KSWORD_PRINT_DEBUG_INFO) {
				KMesErr(vname);
			}
			return 0;

		}
	}
	else {
		vname = "δ֪����ϵͳ";
		if (KSWORD_PRINT_DEBUG_INFO) {
			KMesErr(vname);
		}
		return 0;
	}
	//ԭ�����ӣ�https ://blog.csdn.net/qq78442761/article/details/64440535
}
//̽��CPU���������ʣ�����0~100������Ϊ��ǰ�ٷֱ�ֵ
__int64 CompareFileTime(FILETIME time1, FILETIME time2)
{
	__int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
	__int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;

	return (b - a);
}
//WIN CPUʹ�����  

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

	hEvent = CreateEventA(NULL, FALSE, FALSE, NULL); // ��ʼֵΪ nonsignaled ������ÿ�δ������Զ�����Ϊnonsignaled  

	
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

//̽���ڴ�ٷֱȣ�����0~100������Ϊ��ǰ�ٷֱ�ֵ
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
		if( KSWORD_PRINT_DEBUG_INFO )KMesErr("��ȡ�ڴ�ռ����ʧ��");
		return -1;
	}
}
//̽���ڴ�����������������GB��������ȡ����
int RAMSize() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memInfo)) {
		DWORDLONG totalPhys = memInfo.ullTotalPhys;
		// ת��ΪGB��1 GB = 1024 * 1024 * 1024�ֽ�
		double totalMemoryGB = totalPhys / 1073741824.0;
		// ����ȡ��
		return static_cast<int>(totalMemoryGB) + (totalMemoryGB - static_cast<int>(totalMemoryGB) > 0 ? 1 : 0);
	}
	else {
		if (KSWORD_PRINT_DEBUG_INFO)
			KMesErr("��ȡ�ڴ�����ʧ��");
		return 0;
	}
	return 0;
}
//̽���ڴ�����������������MB��������ȡ����
int RAMSizeMB() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memInfo)) {
		DWORDLONG totalPhys = memInfo.ullTotalPhys;
		// ת��ΪMB��1 MB = 1024 * 1024�ֽ�
		int totalMemoryMB = static_cast<int>(totalPhys / (1024 * 1024));
		return totalMemoryMB;
	}
	else {
		if (KSWORD_PRINT_DEBUG_INFO)
			KMesErr("��ȡ�ڴ�����ʧ��");
		return 0;
	}
	return 0;
}
//��ȡϵͳ���̷��������̷�
char SystemDrive() {
	char systemDrive[3] = { 0 };
	GetEnvironmentVariableA("SYSTEMDRIVE", systemDrive, sizeof(systemDrive));
	std::string msgtmp;
	msgtmp += "̽�⵽ϵͳ���̷���";
	msgtmp += systemDrive[0];
	if (KSWORD_PRINT_DEBUG_INFO)KMesErr(msgtmp);
	return systemDrive[0];
}
//��ȡָ���̿��ÿռ䣨-1�����̲����ڣ�
int FreeSpaceOfDrive(char driveLetter) {
	ULARGE_INTEGER freeBytesAvailable;
	ULARGE_INTEGER totalNumberOfBytes;
	ULARGE_INTEGER totalNumberOfFreeBytes;
	// ����������·������ "C:\"
	char drivePath[4] = { driveLetter, ':', '\\', '\0' };
	// ��ȡ��������ʣ��ռ�
	if (GetDiskFreeSpaceEx(drivePath, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
		// ���ֽ�ת��Ϊ���ֽڣ�1 MB = 1024 * 1024 �ֽ�
		return static_cast<int>(freeBytesAvailable.QuadPart / (1024 * 1024));
	}
	else {
		if (KSWORD_PRINT_DEBUG_INFO)KMesErr("�Ҳ������������޷�������ÿռ�");
		// �����������ʧ�ܣ�����-1
		return -1;
	}
}
//̽���Ƿ������
	//���أ�0���������
	// 1��VMwareϵ��
	// 2��VPCϵ��
int IsVM() {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return 0;
}
bool IsInsideVPC() {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return 0;
}
bool IsInsideVMWare() {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return 0;
}


//��������==================================================
//�첽ִ��cmd����
void RunCmdAsyn(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void RunCmdAsyn(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
//ʵʱ����ִ��cmd����
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
		//��ȡ����ִ�й����е����
		while (fgets(MsgBuff, MsgLen, fp) != NULL){
			printf("%s\n", MsgBuff);
		}
		//�ر�ִ�еĽ���
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
		//��ȡ����ִ�й����е����
		while (fgets(MsgBuff, MsgLen, fp) != NULL) {
			printf("%s\n", MsgBuff);
		}
		//�ر�ִ�еĽ���
		if (_pclose(fp) == -1) {
			return -3;
		}
	}
	return 0;
}
//�������ԱȨ�޲������Լ�������·����
void RequestAdmin(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void RequestAdmin(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void RequestAdmin(wchar_t text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
//���㳤MD5
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
	// F����
	unsigned int Ksword_Md5_F(unsigned int b, unsigned int c, unsigned int d) {
		return (b & c) | ((~b) & d);
	}
	// G����
	unsigned int Ksword_Md5_G(unsigned int b, unsigned int c, unsigned int d) {
		return (b & d) | (c & (~d));
	}
	// H����
	unsigned int Ksword_Md5_H(unsigned int b, unsigned int c, unsigned int d) {
		return b ^ c ^ d;
	}
	// I����
	unsigned int Ksword_Md5_I(unsigned int b, unsigned int c, unsigned int d) {
		return c ^ (b | (~d));
	}
	// ��λ��������
	unsigned int Ksword_Md5_shift(unsigned int a, unsigned int n) {
		return (a << n) | (a >> (32 - n));
	}
	// ���뺯��
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
	// ѭ��ѹ��
	void Ksword_Md5_iterateFunc(unsigned int* X, int size = 16) {
		unsigned int a = tempKSWORD_MD5_A,
			b = tempKSWORD_MD5_B,
			c = tempKSWORD_MD5_C,
			d = tempKSWORD_MD5_D,
			rec = 0,
			g, k;
		for (int i = 0; i < 64; i++) {
			if (i < 16) {
				// F����
				g = Ksword_Md5_F(b, c, d);
				k = i;
			}
			else if (i < 32) {
				// G����
				g = Ksword_Md5_G(b, c, d);
				k = (1 + 5 * i) % 16;
			}
			else if (i < 48) {
				// H����
				g = Ksword_Md5_H(b, c, d);
				k = (5 + 3 * i) % 16;
			}
			else {
				// I����
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
	// ����ַ���
	std::vector<unsigned int> Ksword_Md5_padding(std::string src) {
		// ��512λ,64���ֽ�Ϊһ��
		unsigned int num = ((src.length() + 8) / 64) + 1;
		std::vector<unsigned int> rec(num * 16);
		strlength = num * 16;
		for (unsigned int i = 0; i < src.length(); i++) {
			// һ��unsigned int��Ӧ4���ֽڣ�����4���ַ���Ϣ
			rec[i >> 2] |= (int)(src[i]) << ((i % 4) * 8);
		}
		// ����1000...000
		rec[src.length() >> 2] |= (0x80 << ((src.length() % 4) * 8));
		// ���ԭ�ĳ���
		rec[rec.size() - 2] = (src.length() << 3);
		return rec;
	}
	// �������
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
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
std::string LMD5(std::string text) {
	MD5 test;
	std::string MD5tmp=test.Ksword_Md5_encode(text);
	if (KSWORD_PRINT_DEBUG_INFO) {
		KMesInfo("���MD5ת����ת����MD5ֵΪ");
		KMesInfo(MD5tmp);
	}
	return MD5tmp;
}
//�����MD5
std::string SMD5(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
std::string SMD5(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
//�����ϣ
std::string Hash(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
std::string Hash(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
//�����ļ���ϣ
std::string FileHash(std::string path) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
std::string FileHash(const char* path) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
std::string FileHash(wchar_t path) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	std::string a;
	return a;
}
//����Powershell


//�ں˶Կ�����==============================================
//��ȡsystemȨ�޲������Լ�����Ҫ����ԱȨ�ޣ�������·����
void GetSystem(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void GetSystem(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void GetSystem(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
//������غ���
	//װ����������������·�����������ƣ�
void LoadWinDrive(const wchar_t* texta, const wchar_t* textb) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void LoadWinDrive(const char* texta, const char* textb) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void LoadWinDrive(std::string texta, std::string textb) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
//�������񣨷������ƣ�
void StartDriverService(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void StartDriverService(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void StartDriverService(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
//ֹͣ���񣨷������ƣ�
void StopDriverService(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void StopDriverService(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void StopDriverService(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
//ж���������������ƣ�
void UnLoadWinDrive(const wchar_t* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void UnLoadWinDrive(std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}
void UnLoadWinDrive(const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return;
}

//��������
	//����������
	//0���������з���ֱ�������˳����൱���ˣ�
	//1��ʹ��taskkill�����ǿ�Ʊ�ʶ����������
	//2��ʹ��taskkill�����ǿ�Ʊ�ʶ����������
	//3������TerminateProcess()������ֹ����
	//4������TerminateThread()�����ݻ������߳�
	//5�����ں�Ȩ�ޣ�ʹ��ZwTerminateProcess()������������
	//6�����ں�Ȩ�ޣ���̬����PspTerminateThreadByPointer�������н���
	//7�����ں�Ȩ�ޣ������ڴ�
	//ͨ������£�1~3��Ϊ��ȫ��ʣ��Ƚ�Σ��
	//����ֵ��1~7��ʹ�ñ�Ŷ�Ӧ�ķ����ɹ������˽��̣�0��δ�ܳɹ���������
	//����ֵ���������+��������/PID
int KillProcess(int a, const char* text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return 0;
}
int KillProcess(int a, std::string text) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return 0;
}
int KillProcess(int a, int b) {
	if (KSWORD_PRINT_DEBUG_INFO)std::cout << std::endl << "��غ������ڱ�д��" << std::endl;
	return 0;
}





