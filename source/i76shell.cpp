#include <stdio.h>
#include <bx/bx.h>
#include "MemoryModule.h"
#include "main.h"
#include "i76shell.h"

namespace i76shell {
namespace original {

// advapi32.dll

LSTATUS (APIENTRY *RegOpenKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
LSTATUS (APIENTRY *RegCloseKey)(HKEY hKey);
LSTATUS (APIENTRY *RegQueryValueExA)(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);

// gdi32.dll

BOOL (WINAPI *BitBlt)(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
HDC (WINAPI *CreateCompatibleDC)(HDC hdc);
HBITMAP (WINAPI *CreateDIBSection)(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset);
HPALETTE (WINAPI *CreatePalette)(CONST LOGPALETTE * plpal);
BOOL (WINAPI *DeleteDC)(HDC hdc);
BOOL (WINAPI *DeleteObject)(HGDIOBJ ho);
int (WINAPI *GetDeviceCaps)(HDC hdc, int index);
UINT (WINAPI *GetSystemPaletteEntries)(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries);
UINT (WINAPI *RealizePalette)(HDC hdc);
HGDIOBJ (WINAPI *SelectObject)(HDC hdc, HGDIOBJ h);
HPALETTE (WINAPI *SelectPalette)(HDC hdc, HPALETTE hPal, BOOL bForceBkgd);
UINT (WINAPI *SetDIBColorTable)(HDC  hdc, UINT iStart, UINT cEntries, CONST RGBQUAD *prgbq);
UINT (WINAPI *SetPaletteEntries)(HPALETTE hpal, UINT iStart, UINT cEntries, CONST PALETTEENTRY *pPalEntries);
UINT (WINAPI *SetSystemPaletteUse)(HDC hdc, UINT use);
BOOL (WINAPI *StretchBlt)(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop);

// kernel32.dll

BOOL (WINAPI *CloseHandle)(HANDLE hObject);
BOOL (WINAPI *CopyFileA)(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists);
HANDLE (WINAPI *CreateFileA)(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
BOOL (WINAPI *CreateProcessA)(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
HANDLE (WINAPI *CreateThread)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
BOOL (WINAPI *DisableThreadLibraryCalls)(HMODULE hLibModule);
UINT (WINAPI *GetDriveTypeA)(LPCSTR lpRootPathName);
DWORD (WINAPI *GetLastError)();
DWORD (WINAPI *GetLogicalDriveStringsA)(DWORD nBufferLength, LPSTR lpBuffer);
DWORD (WINAPI *GetTickCount)();
UINT (WINAPI *GetWindowsDirectoryA)(LPSTR lpBuffer, UINT uSize);
LPVOID (WINAPI *HeapAlloc)(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
HANDLE (WINAPI *HeapCreate)(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize);
BOOL (WINAPI *HeapDestroy)(HANDLE hHeap);
BOOL (WINAPI *HeapFree)(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);
LPVOID (WINAPI *HeapReAlloc)(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes);
DWORD (WINAPI *LoadModule)(LPCSTR lpModuleName, LPVOID lpParameterBlock);
VOID (WINAPI *OutputDebugStringA)(LPCSTR lpOutputString);
BOOL (WINAPI *QueryPerformanceCounter)(LARGE_INTEGER* lpPerformanceCount);
BOOL (WINAPI *ReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
VOID (WINAPI *Sleep)(DWORD dwMilliseconds);
DWORD (WINAPI *WaitForSingleObject)(HANDLE hHandle, DWORD dwMilliseconds);

} // namespace original

namespace wrap {

// advapi32.dll

LSTATUS APIENTRY RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) {
	Logf("[" I76SHELL_DLL " | advapi32.dll | RegOpenKeyExA] sub key:'%s'\n", lpSubKey);
	LSTATUS status = original::RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	return status;
}

LSTATUS APIENTRY RegCloseKey(HKEY hKey) {
	Logf("[" I76SHELL_DLL " | advapi32.dll | RegCloseKey]\n");
	return original::RegCloseKey(hKey);
}

LSTATUS APIENTRY RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
	Logf("[" I76SHELL_DLL " | advapi32.dll | RegQueryValueExA]\n");
	return original::RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}

// gdi32.dll

BOOL WINAPI BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | BitBlt]\n");
	return original::BitBlt(hdc, x, y, cx, cy, hdcSrc, x1, y1, rop);
}

HDC WINAPI CreateCompatibleDC(HDC hdc) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | CreateCompatibleDC]\n");
	return original::CreateCompatibleDC(hdc);
}

HBITMAP WINAPI CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | CreateDIBSection]\n");
	return original::CreateDIBSection(hdc, pbmi, usage, ppvBits, hSection, offset);
}

HPALETTE WINAPI CreatePalette(CONST LOGPALETTE * plpal) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | CreatePalette]\n");
	return original::CreatePalette(plpal);
}

BOOL WINAPI DeleteDC(HDC hdc) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | DeleteDC]\n");
	return original::DeleteDC(hdc);
}

BOOL WINAPI DeleteObject(HGDIOBJ ho) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | DeleteObject]\n");
	return original::DeleteObject(ho);
}

int WINAPI GetDeviceCaps(HDC hdc, int index) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | GetDeviceCaps]\n");
	return original::GetDeviceCaps(hdc, index);
}

UINT WINAPI GetSystemPaletteEntries(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | GetSystemPaletteEntries]\n");
	return original::GetSystemPaletteEntries(hdc, iStart, cEntries, pPalEntries);
}

UINT WINAPI RealizePalette(HDC hdc) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | RealizePalette]\n");
	return original::RealizePalette(hdc);
}

HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ h) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | SelectObject]\n");
	return original::SelectObject(hdc, h);
}

HPALETTE WINAPI SelectPalette(HDC hdc, HPALETTE hPal, BOOL bForceBkgd) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | SelectPalette]\n");
	return original::SelectPalette(hdc, hPal, bForceBkgd);
}

UINT WINAPI SetDIBColorTable(HDC hdc, UINT iStart, UINT cEntries, CONST RGBQUAD *prgbq) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | SetDIBColorTable]\n");
	return original::SetDIBColorTable(hdc, iStart, cEntries, prgbq);
}

UINT WINAPI SetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries, CONST PALETTEENTRY *pPalEntries) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | SetPaletteEntries]\n");
	return original::SetPaletteEntries(hpal, iStart, cEntries, pPalEntries);
}

UINT WINAPI SetSystemPaletteUse(HDC hdc, UINT use) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | SetSystemPaletteUse]\n");
	return original::SetSystemPaletteUse(hdc, use);
}

BOOL WINAPI StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop) {
	Logf("[" I76SHELL_DLL " | gdi32.dll | StretchBlt]\n");
	return original::StretchBlt(hdcDest, xDest, yDest, wDest, hDest, hdcSrc, xSrc, ySrc, wSrc, hSrc, rop);
}

// kernel32.dll

BOOL WINAPI CloseHandle(HANDLE hObject) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | CloseHandle]\n");
	return original::CloseHandle(hObject);
}

BOOL WINAPI CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | CopyFileA] from:'%s', to:'%s'\n", lpExistingFileName, lpNewFileName);
	return original::CopyFileA(lpExistingFileName, lpNewFileName, bFailIfExists);
}

HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | CreateFileA] '%s'\n", lpFileName);
	return original::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL WINAPI CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | CreateProcessA] app:'%s'\n", lpApplicationName);
	return original::CreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | CreateThread]\n");
	return original::CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

BOOL WINAPI DisableThreadLibraryCalls(HMODULE hLibModule) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | DisableThreadLibraryCalls]\n");
	return original::DisableThreadLibraryCalls(hLibModule);
}

UINT WINAPI GetDriveTypeA(LPCSTR lpRootPathName) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | GetDriveTypeA] root:'%s'\n", lpRootPathName);
	return original::GetDriveTypeA(lpRootPathName);
}

DWORD WINAPI GetLastError() {
	Logf("[" I76SHELL_DLL " | kernel32.dll | GetLastError]\n");
	return original::GetLastError();
}

DWORD WINAPI GetLogicalDriveStringsA(DWORD nBufferLength, LPSTR lpBuffer) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | GetLogicalDriveStringsA]\n");
	return original::GetLogicalDriveStringsA(nBufferLength, lpBuffer);
}

DWORD WINAPI GetTickCount() {
	Logf("[" I76SHELL_DLL " | kernel32.dll | GetTickCount]\n");
	return original::GetTickCount();
}

UINT WINAPI GetWindowsDirectoryA(LPSTR lpBuffer, UINT uSize) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | GetWindowsDirectoryA]\n");
	return original::GetWindowsDirectoryA(lpBuffer, uSize);
}

LPVOID WINAPI HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes) {
#if LOG_VERBOSE
	Logf("[" I76SHELL_DLL " | kernel32.dll | HeapAlloc]\n");
#endif
	return original::HeapAlloc(hHeap, dwFlags, dwBytes);
}

HANDLE WINAPI HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | HeapCreate]\n");
	return original::HeapCreate(flOptions, dwInitialSize, dwMaximumSize);
}

BOOL WINAPI HeapDestroy(HANDLE hHeap) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | HeapDestroy]\n");
	return original::HeapDestroy(hHeap);
}

BOOL WINAPI HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
#if LOG_VERBOSE
	Logf("[" I76SHELL_DLL " | kernel32.dll | HeapFree]\n");
#endif
	return original::HeapFree(hHeap, dwFlags, lpMem);
}

LPVOID WINAPI HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | HeapReAlloc]\n");
	return original::HeapReAlloc(hHeap, dwFlags, lpMem, dwBytes);
}

DWORD WINAPI LoadModule(LPCSTR lpModuleName, LPVOID lpParameterBlock) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | LoadModule]\n");
	return original::LoadModule(lpModuleName, lpParameterBlock);
}

VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | OutputDebugStringA] '%s'\n", lpOutputString);
	original::OutputDebugStringA(lpOutputString);
}

BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | QueryPerformanceCounter]\n");
	return original::QueryPerformanceCounter(lpPerformanceCount);
}

BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | ReadFile]\n");
	return original::ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

VOID WINAPI Sleep(DWORD dwMilliseconds) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | Sleep] %u ms\n", dwMilliseconds);
	original::Sleep(dwMilliseconds);
}

DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) {
	Logf("[" I76SHELL_DLL " | kernel32.dll | WaitForSingleObject]\n");
	return original::WaitForSingleObject(hHandle, dwMilliseconds);
}

} // namespace wrap

static WrappedFunc s_wrappedFuncs[] = {
	WRAPPED_FUNC(advapi32.dll, RegOpenKeyExA),
	WRAPPED_FUNC(advapi32.dll, RegCloseKey),
	WRAPPED_FUNC(advapi32.dll, RegQueryValueExA),
	WRAPPED_FUNC(gdi32.dll, BitBlt),
	WRAPPED_FUNC(gdi32.dll, CreateCompatibleDC),
	WRAPPED_FUNC(gdi32.dll, CreateDIBSection),
	WRAPPED_FUNC(gdi32.dll, CreatePalette),
	WRAPPED_FUNC(gdi32.dll, DeleteDC),
	WRAPPED_FUNC(gdi32.dll, DeleteObject),
	WRAPPED_FUNC(gdi32.dll, GetDeviceCaps),
	WRAPPED_FUNC(gdi32.dll, GetSystemPaletteEntries),
	WRAPPED_FUNC(gdi32.dll, RealizePalette),
	WRAPPED_FUNC(gdi32.dll, SelectObject),
	WRAPPED_FUNC(gdi32.dll, SelectPalette),
	WRAPPED_FUNC(gdi32.dll, SetDIBColorTable),
	WRAPPED_FUNC(gdi32.dll, SetPaletteEntries),
	WRAPPED_FUNC(gdi32.dll, SetSystemPaletteUse),
	WRAPPED_FUNC(gdi32.dll, StretchBlt),
	WRAPPED_FUNC(kernel32.dll, CloseHandle),
	WRAPPED_FUNC(kernel32.dll, CopyFileA),
	WRAPPED_FUNC(kernel32.dll, CreateFileA),
	WRAPPED_FUNC(kernel32.dll, CreateProcessA),
	WRAPPED_FUNC(kernel32.dll, CreateThread),
	WRAPPED_FUNC(kernel32.dll, DisableThreadLibraryCalls),
	WRAPPED_FUNC(kernel32.dll, GetDriveTypeA),
	WRAPPED_FUNC(kernel32.dll, GetLastError),
	WRAPPED_FUNC(kernel32.dll, GetLogicalDriveStringsA),
	WRAPPED_FUNC(kernel32.dll, GetTickCount),
	WRAPPED_FUNC(kernel32.dll, GetWindowsDirectoryA),
	WRAPPED_FUNC(kernel32.dll, HeapAlloc),
	WRAPPED_FUNC(kernel32.dll, HeapCreate),
	WRAPPED_FUNC(kernel32.dll, HeapDestroy),
	WRAPPED_FUNC(kernel32.dll, HeapFree),
	WRAPPED_FUNC(kernel32.dll, HeapReAlloc),
	WRAPPED_FUNC(kernel32.dll, LoadModule),
	WRAPPED_FUNC(kernel32.dll, OutputDebugStringA),
	WRAPPED_FUNC(kernel32.dll, QueryPerformanceCounter),
	WRAPPED_FUNC(kernel32.dll, ReadFile),
	WRAPPED_FUNC(kernel32.dll, Sleep),
	WRAPPED_FUNC(kernel32.dll, WaitForSingleObject)
};

static MemoryModuleUserData s_memoryModuleUserData;
static HMEMORYMODULE s_memoryModule;

HMODULE Load() {
	FILE *f;
	if (fopen_s(&f, I76SHELL_DLL, "rb") != 0) {
		fprintf(stderr, "Error opening %s\n", I76SHELL_DLL);
		return nullptr;
	}
	fseek(f, 0, SEEK_END);
	auto fileLength = (size_t)ftell(f);
	fseek(f, 0, SEEK_SET);
	auto fileData = new uint8_t[fileLength];
	if (fread(fileData, 1, fileLength, f) != fileLength) {
		delete [] fileData;
		fprintf(stderr, "Error reading %s\n", I76SHELL_DLL);
		return nullptr;
	}
	fclose(f);
	s_memoryModuleUserData.wrappedFuncs = ArrayView<WrappedFunc>(s_wrappedFuncs, BX_COUNTOF(s_wrappedFuncs));
	s_memoryModule = CustomMemoryLoadLibrary(fileData, fileLength, &s_memoryModuleUserData);
	if (!s_memoryModule) {
		fprintf(stderr, "MemoryLoadLibraryEx failed for %s\n", I76SHELL_DLL);
		return nullptr;
	}
	Logf("Loaded %s\n", I76SHELL_DLL);
	return (HMODULE)s_memoryModule;
}

bool IsModule(HMODULE _module) {
	return (HMEMORYMODULE)_module == s_memoryModule;
}

FARPROC GetProcAddress(const char *_name) {
	Logf("%s: GetProcAddress %s\n", I76SHELL_DLL, _name);
	return MemoryGetProcAddress(s_memoryModule, _name);
}

} // namespace i76shell
