// dllmain.cpp : Defines the entry point for the DLL application.


#ifndef LIB1_H_INCLUDED
#define LIB1_H_INCLUDED

#include "mind.h"
#include <iostream>
#include <thread>

#include <windows.h>
#include <imagehlp.h>
#include <stdlib.h>
#include <tchar.h>
#include "string.h"
 
inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName);
 
inline BOOL CALLBACK MiniDumpCallback(PVOID pParam, const PMINIDUMP_CALLBACK_INPUT pInput, PMINIDUMP_CALLBACK_OUTPUT pOutput);
 
 //Create Dump file
inline void CreateMiniDump(EXCEPTION_POINTERS* pep, LPCTSTR strFileName);
 
LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
 
BOOL PreventSetUnhandledExceptionFilter();
 
 
LONG WINAPI UnhandledExceptionFilterEx(struct _EXCEPTION_POINTERS *pException);
 
 //Run exception handling
void RunCrashHandler();
 
 
#pragma comment(lib, "dbghelp.lib")
 
inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)
{
	if(pModuleName == 0)
	{
		return FALSE;
	}
 /*
	WCHAR szFileName[255] = L"";
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);
	if(wcsicmp(szFileName, L"ntdll") == 0)
		return TRUE;
 */
	return FALSE; 
}
 
inline BOOL CALLBACK MiniDumpCallback(PVOID                            pParam, 
	const PMINIDUMP_CALLBACK_INPUT   pInput, 
	PMINIDUMP_CALLBACK_OUTPUT        pOutput)
{
	if(pInput == 0 || pOutput == 0)
		return FALSE;
 
	switch(pInput->CallbackType)
	{
	case ModuleCallback: 
		if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg) 
 
			if(!IsDataSectionNeeded(pInput->Module.FullPath)) 
 
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg); 
 
	case IncludeModuleCallback:
	case IncludeThreadCallback:
	case ThreadCallback:
	case ThreadExCallback:
		return TRUE;
 
	default:;
	}
 
	return FALSE;
}
 
 //Create Dump file
inline void CreateMiniDump(EXCEPTION_POINTERS* pep, LPCTSTR strFileName)
{
	HANDLE hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId           = GetCurrentThreadId();
		mdei.ExceptionPointers  = pep;
		mdei.ClientPointers     = FALSE;
		MINIDUMP_CALLBACK_INFORMATION mci;
		mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
		mci.CallbackParam       = 0;
		MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)0x0000ffff;
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &mdei, NULL, &mci);
 
		CloseHandle(hFile); 
	}
}
 
LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	return NULL;
}
 
BOOL PreventSetUnhandledExceptionFilter()
{
	HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
	if (hKernel32 ==   NULL)
		return FALSE;
 
 
	void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
	if(pOrgEntry == NULL)
		return FALSE;
 
 
	unsigned char newJump[ 100 ];
	DWORD dwOrgEntryAddr = (DWORD) pOrgEntry;
	dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far
 
 
	void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
	DWORD dwNewEntryAddr = (DWORD) pNewFunc;
	DWORD dwRelativeAddr = dwNewEntryAddr -  dwOrgEntryAddr;
 
 
	newJump[ 0 ] = 0xE9;  // JMP absolute
	memcpy(&newJump[ 1 ], &dwRelativeAddr, sizeof(pNewFunc));
	SIZE_T bytesWritten;
	BOOL bRet = WriteProcessMemory(GetCurrentProcess(),    pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
	return bRet;
}
 
 
LONG WINAPI UnhandledExceptionFilterEx(struct _EXCEPTION_POINTERS *pException)
{
	CreateMiniDump(pException,"C:\\dev\\GORCHAN.dmp");
	// TODO: MiniDumpWriteDump
	FatalAppExit(-1,  _T("Fatal Error"));
	return EXCEPTION_CONTINUE_SEARCH;
}
 
 //Run exception handling
void RunCrashHandler()
{
	SetUnhandledExceptionFilter(UnhandledExceptionFilterEx);
	PreventSetUnhandledExceptionFilter();
}


int main()
{
   std::cout<<"Hi to all"<<std::endl;
   std::cout<<"Wait debbuger"<<std::endl;
   int i = 0;
   //std::cin>>i;

 
   mind* _mind = nullptr;
   get_mind(&_mind);
   _mind->init();
   _mind->percive("a = a", false);
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("b = b", false);
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("ab", true);
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("c = c", false);
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   //  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   // _mind->percive("=a", true);
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("a = b", false);
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("b = c", false);


   std::this_thread::sleep_for(std::chrono::minutes(1));


   return 111;
}




#endif /* LIB1_H_INCLUDED */