// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

using namespace std;


DWORD baseOffset = 0x01065DA8;
DWORD transOffset = 0x01080DA4;
DWORD scoreBoardOffset = 0x010607C0;
DWORD directXOffset = 0x00FB09F8; //old

DMain* dMain;
DTrans* dTrans;
DScoreboard* dScoreboard;

typedef int (WINAPI *Present_t)(LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
Present_t oPresent;

typedef int (WINAPI *Reset_t)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters);
Reset_t oReset;

DWORD* dwpVTableStart = NULL; // d3d9.dll device vtable
DWORD* dwpDeviceVMT = NULL; // game's d3d9 device vtable

Hooked_D3D9 hookedD3D9;

void  CreateDebugConsole(LPCWSTR lPConsoleTitle)
{
	HANDLE lStdHandle = 0;
	int hConHandle = 0;
	FILE *fp = 0;
	AllocConsole();
	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);
	SetConsoleTitle(lPConsoleTitle);
	SetConsoleTextAttribute(lStdHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
}

int WINAPI HookedPresent(LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	static bool RunOnce = true;
	if (RunOnce)
	{
		char pad3[] = "Hi this is a pad";
		char buf[50] = { 0 };
		sprintf_s(buf, pad3);
		
		RunOnce = false;
		hookedD3D9.Initialize(pDevice); // create our objects before we start rendering
	}
	hookedD3D9.Render();
	oPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	return 0;
}
int WINAPI HookedReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	hookedD3D9.Reset();

	char pad4[] = "this is a pad also";
	char buf[50] = { 0 };
	sprintf_s(buf, pad4);

	oReset(pDevice, pPresentationParameters);
	hookedD3D9.Initialize(pDevice);
	return 0;
}

template <typename T> T HookVTableFunction(DWORD* dwpTable, int index, DWORD dwNewFunc)
{
	DWORD dwProt = 0;
	VirtualProtect(&dwpTable[index], 4, PAGE_EXECUTE_READWRITE, &dwProt);
	T oFunc = (T)dwpTable[index];
	dwpTable[index] = dwNewFunc;
	VirtualProtect(&dwpTable[index], 4, dwProt, 0);
	return oFunc;
}

/*
int WINAPI RemoveHooks()
{
	// reinsert the original pointer addresses
	//hookedD3D9.CleanUp();
	HookVTableFunction<Reset_t>(dwpVTableStart, 16, (DWORD)oReset);
	HookVTableFunction<Present_t>(dwpVTableStart, 17, (DWORD)oPresent);
	HookVTableFunction<Reset_t>(dwpDeviceVMT, 16, (DWORD)oReset);
	HookVTableFunction<Present_t>(dwpDeviceVMT, 17, (DWORD)oPresent);
	Sleep(998);
	return 0;
} */

DWORD GetModuleSize(LPSTR strModuleName)
{
	MODULEENTRY32	lpme = { 0 };
	DWORD			dwSize = 0;
	DWORD			PID = GetCurrentProcessId();
	BOOL			isMod = 0;
	char			chModName[256];

	strcpy_s(chModName, strModuleName);
	_strlwr_s(chModName);

	HANDLE hSnapshotModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	if (hSnapshotModule)
	{
		lpme.dwSize = sizeof(lpme);
		isMod = Module32First(hSnapshotModule, &lpme);
		while (isMod)
		{
			if (strcmp((char*)lpme.szExePath, chModName))
			{
				dwSize = (DWORD)lpme.modBaseSize;
				CloseHandle(hSnapshotModule);
				return dwSize;
			}
			isMod = Module32Next(hSnapshotModule, &lpme);
		}
	}
	CloseHandle(hSnapshotModule);

	return 0;
}


// Credits to GD
bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'y' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

// Credits to GD
DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
	{
		if (bDataCompare((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);
	}
	return 0;
}


int WINAPI InputThread(LPVOID lpStatus)
{
	CreateDebugConsole(L"DayZ Debug");
	std::cout << "Thread Successfully Created" << std::endl;

	//Find Sigs
	DWORD DayZHandle = (DWORD)GetModuleHandle(L"DayZ.exe");
	DWORD DayZSize = (DWORD)GetModuleSize("DayZ.exe");

	char dMainString[] = "\x8B\x0D\xFA\xFA\xFA\xFA\xA3\xFA\xFA\xFA\xFA\x83\xB9";
	XOR(dMainString, 'v');
	char dMainMask[] = "yy????y????yy";
	XOR(dMainMask, 'v');
	DWORD dMainAddr = dwFindPattern(DayZHandle, DayZSize, (PBYTE)XORRuntime(dMainString, 'v').c_str(), const_cast<char*>(XORRuntime(dMainMask, 'v').c_str()));

	char dScoreString[] = "\xB9\xFA\xFA\xFA\xFA\xE8\xFA\xFA\xFA\xFA\x8B\x44\x24\x18\x6A\x01";
	XOR(dScoreString, 'v');
	char dScoreMask[] = "y????y????yyyyyy";
	XOR(dScoreMask, 'v');
	DWORD dScoreAddr = dwFindPattern(DayZHandle, DayZSize, (PBYTE)XORRuntime(dScoreString, 'v').c_str(), const_cast<char*>(XORRuntime(dScoreMask, 'v').c_str()));

	char dTransString[] = "\x8B\x0D\xFA\xFA\xFA\xFA\x85\xC9\x0F\x84\xFA\xFA\xFA\xFA\x83\xBE";
	XOR(dTransString, 'v');
	char dTransMask[] = "yy????yyyy????yy";
	XOR(dTransMask, 'v');
	DWORD dTransAddr = dwFindPattern(DayZHandle, DayZSize, (PBYTE)XORRuntime(dTransString, 'v').c_str(), const_cast<char*>(XORRuntime(dTransMask, 'v').c_str()));

	char dD3DString[] = "\x8B\x0D\xFA\xFA\xFA\xFA\x8B\x01\x8B\x56\x08\x8B\x80";
	XOR(dD3DString, 'v');
	char dD3DMask[] = "yy????yyyyyyy";
	XOR(dD3DMask, 'v');
	DWORD dD3DAddr = dwFindPattern(DayZHandle, DayZSize, (PBYTE)XORRuntime(dD3DString, 'v').c_str(), const_cast<char*>(XORRuntime(dD3DMask, 'v').c_str()));

	char dD3DOffString[] = "\x8B\x86\xFA\xFA\xFA\xFA\x3B\xC3\x74\x0E\x8B\x08\x8B\x51\x08\x50\xFF\xD2\x89\x9E\xFA\xFA\xFA\xFA\x5E\x5B";
	XOR(dD3DOffString, 'v');
	char dD3DOffMask[] = "yy????yyyyyyyyyyyyyy????yy";
	XOR(dD3DOffMask, 'v');
	DWORD dD3DOffAddr = dwFindPattern(DayZHandle, DayZSize, (PBYTE)XORRuntime(dD3DOffString, 'v').c_str(), const_cast<char*>(XORRuntime(dD3DOffMask, 'v').c_str()));

	char sig_isStopped[] = "\x33\xC0\x38\x81\xFA\xFA\xFA\xFA\x0F\x94\xC0\xC3";
	XOR(sig_isStopped, 'v');
	char mask_isStopped[] = "yyyy????yyyy";
	XOR(mask_isStopped, 'v');
	DWORD addr_isStopped = dwFindPattern(DayZHandle, DayZSize, (PBYTE)XORRuntime(sig_isStopped, 'v').c_str(), const_cast<char*>(XORRuntime(mask_isStopped, 'v').c_str()));


	//End Find Sigs

	//epiphany!! do not dereference - > instead create a base class as in timon's hook. remember to update all if's (YAY IT WORKS)
	dMain = (DMain*)(baseOffset);
	dTrans = (DTrans*)(transOffset);
	dScoreboard = (DScoreboard*)(scoreBoardOffset + 0x28);

	cout << hex << dMain << endl << dScoreboard << endl << dTrans << endl << endl;
	
	cout << hex << dMainAddr << " -> " << *(PDWORD)(dMainAddr + 2) << endl 
				<< dScoreAddr << " -> " << *(PDWORD)(dScoreAddr + 1) << endl
				<< dTransAddr << " -> " << *(PDWORD)(dTransAddr + 2) << endl
				<< dD3DAddr << endl << dD3DOffAddr << endl;

	cout << hex << addr_isStopped << endl;


	HMODULE hModule = NULL;
	char dzdll[] = "d3d9.dll";
	XOR(dzdll, 'g');
	while (!hModule)
	{
		hModule = GetModuleHandleA(XORRuntime(dzdll, 'g').c_str());
		Sleep(100);
	}

	char sigString[] = "\xC7\x06\xFA\xFA\xFA\xFA\x89\x86\xFA\xFA\xFA\xFA\x89\x86";
	XOR(sigString, 'v');

	char sigMask[] = "yy????yy????yy";
	XOR(sigMask, 'v');

	DWORD dwVTable = dwFindPattern((DWORD)hModule, 0x128001, (PBYTE)XORRuntime(sigString, 'v').c_str(), const_cast<char*>(XORRuntime(sigMask, 'v').c_str()));
	memcpy(&dwpVTableStart, (LPVOID)(dwVTable + 2), 4); //*pointer to vtable start in d3d9.dll

	cout << "Found Pattern" << endl;

	DWORD dwPtr1 = NULL;
	while (!dwPtr1)
	{
		//dwPtr1 = (*(DWORD*)(directXOffset));
		dwPtr1 = (*(DWORD*)((DWORD)dMain->dMain + 0x8));
	}

	cout << "dwPtr1 Found" << endl;

	char pad1[] = "\x6A\x1B\xFF\xFF\x00";
	DWORD dwDeviceVMTPtr = NULL;
	while (!dwDeviceVMTPtr)
	{
		dwDeviceVMTPtr = (*(DWORD*)(dwPtr1 + 0x18A0)); //perhaps 1890,18A0
	}

	memcpy(&dwpDeviceVMT, (LPVOID)dwDeviceVMTPtr, 4);
	
	cout << "dwDeviceVMTPtr Found" << endl;
	// VMT Hook
	// make copies of the original function locations and insert our function pointer
	HookVTableFunction<Reset_t>(dwpVTableStart, 16, (DWORD)&HookedReset);
	HookVTableFunction<Present_t>(dwpVTableStart, 17, (DWORD)&HookedPresent);
	// these two make the game recopy the VMT again for some reason
	oReset = HookVTableFunction<Reset_t>(dwpDeviceVMT, 16, (DWORD)&HookedReset);
	oPresent = HookVTableFunction<Present_t>(dwpDeviceVMT, 17, (DWORD)&HookedPresent);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(InputThread), NULL, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

