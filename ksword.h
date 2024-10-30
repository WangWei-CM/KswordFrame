#ifndef KSWORD_HEAD_FILE
#define KSWORD_HEAD_FILE
//�Ƿ����׼������������Ϣ��1=�����0=�����
#define KSWORD_PRINT_DEBUG_INFO 1
//�Ƿ����ð�ȫģʽ�����ú󽫻��ֹһЩ�����ϵͳ����ƻ��Ĳ���
#define KSWORD_SAFE_MODE 0
//��������Ksword�����Ŷӳ�Ա�����򲻽������ô�ѡ��
#define KSWORD_DEVER_MODE 0
//�Ƿ��Ե�����ʽչʾKsword�Ĵ���;���
#define KSWORD_WINDOW_WAE 0
//�쳣�˳�����ֵ
#define KSWORD_ERROE_EXIT 0
//�����˳�����ֵ
#define KSWORD_SUCCESS_EXIT 1

//MD5����ؼ�ֵ
#define KSWORD_MD5_A 0x67452301
#define KSWORD_MD5_B 0xefcdab89
#define KSWORD_MD5_C 0x98badcfe
#define KSWORD_MD5_D 0x10325476
const char ksword_md5_str16[] = "0123456789abcdef";
const unsigned int ksword_md5_T[] = {
	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
	0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
	0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
	0x6b901122,0xfd987193,0xa679438e,0x49b40821,
	0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
	0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
	0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
	0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
	0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
	0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
	0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
	0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
	0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
	0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
	0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 };

const unsigned int ksword_md5_s[] = { 7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
						   5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
						   4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
						   6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21 };

// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2018 Free Software Foundation, Inc.
/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

 // 17.4.1.2 Headers

 // C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <charconv>
#include <filesystem>
#endif

#include <windows.h>

//Ksword�淶��Ϣ����=========================================
//��Ϣ��ʾ[ * ]
void KMesInfo(const char*);
void KMesInfo(std::string);

//������ʾ[ ! ]
void KMesWarn(std::string);
void KMesWarn(const char*);
//������ʾ[ X ]
void KMesErr(std::string);
void KMesErr(const char*);

//����̨�������Բٿغ���=====================================
//�ö���ȡ���ö���������1=�ɹ�0=ʧ��
bool SetTopWindow();
bool UnTopWindow();
bool KTopWindow();
//������ȡ�����غ���
bool HideWindow();
bool ShowWindow();
//���ش��ڱ߿�
bool HideSide();
//����ȫ��
bool FullScreen();
bool KFullScreen();
bool KResetWindow();
//��������ʾָ��
bool ShowCursor();
void HideCursor();
//����ָ��λ�ã������ң��������£�
void SetCursor(int, int);
//��ɫ����ı����ı����ݣ�ǰ��ɫ������ɫ��
//0 = ��ɫ 8 = ��ɫ
//1 = ��ɫ 9 = ����ɫ
//2 = ��ɫ 10 = ����ɫ
//3 = ǳ��ɫ 11 = ��ǳ��ɫ
//4 = ��ɫ 12 = ����ɫ
//5 = ��ɫ 13 = ����ɫ
//6 = ��ɫ 14 = ����ɫ
//7 = ��ɫ 15 = ����ɫ
void cprint(const char*, int, int);
void cprint(std::string, int, int);
//�޸Ŀ���̨���ڱ�������
//void SetTitle(const char*);
//void SetTitle(std::string);

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
int WinVer();
//̽��CPU���������ʣ�����0~100������Ϊ��ǰ�ٷֱ�ֵ
__int64 CompareFileTime(FILETIME, FILETIME);
int CPUUsage();
//̽���ڴ�ٷֱȣ�����0~100������Ϊ��ǰ�ٷֱ�ֵ
int RAMUsage();
//̽���ڴ�����������������GB��������ȡ����
int RAMSize();
//̽���ڴ�����������������MB��������ȡ����
int RAMSizeMB();
//��ȡϵͳ���̷��������̷�
char SystemDrive();
//��ȡָ���̿��ÿռ䣨-1�����̲����ڣ�
int FreeSpaceOfDrive(char);
//̽���Ƿ������
	//���أ�0���������
	// 1��VMwareϵ��
	// 2��VPCϵ��
	int IsVM();
	bool IsInsideVPC();
	bool IsInsideVMWare();


//��������==================================================
//�첽ִ��cmd����
void RunCmdAsyn(const char*);
void RunCmdAsyn(std::string);
//ʵʱ����ִ��cmd����
int RunCmdNow(const char*);
int RunCmdNow(std::string);
//�������ԱȨ�޲������Լ�������·����
void RequestAdmin(const char*);
void RequestAdmin(std::string);
void RequestAdmin(wchar_t);
//���㳤MD5
std::string LMD5(const char*);
std::string LMD5(std::string);
//�����MD5
std::string SMD5(const char*);
std::string SMD5(std::string);
//�����ϣ
std::string Hash(const char*);
std::string Hash(std::string);
//�����ļ���ϣ
std::string FileHash(std::string path);
std::string FileHash(const char* path);
std::string FileHash(wchar_t path);
//����Powershell


//�ں˶Կ�����==============================================
//��ȡsystemȨ�޲������Լ�����Ҫ����ԱȨ�ޣ�������·����
void GetSystem(const wchar_t*);
void GetSystem(std::string);
void GetSystem(const char*);
//������غ���
	//װ����������������·�����������ƣ�
	void LoadWinDrive(const wchar_t*,const wchar_t*);
	void LoadWinDrive(const char*,const char*);
	void LoadWinDrive(std::string,std::string);
	//�������񣨷������ƣ�
	void StartDriverService(const wchar_t*);
	void StartDriverService(const char*);
	void StartDriverService(std::string);
	//ֹͣ���񣨷������ƣ�
	void StopDriverService(const wchar_t*);
	void StopDriverService(std::string);
	void StopDriverService(const char*);
	//ж���������������ƣ�
	void UnLoadWinDrive(const wchar_t*);
	void UnLoadWinDrive(std::string);
	void UnLoadWinDrive(const char*);

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
	int KillProcess(int, const char*);
	int KillProcess(int, std::string);
	int KillProcess(int, int);



#endif
