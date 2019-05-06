#include <stdio.h>
#include <bx/bx.h>
#include <bx/string.h>
#define CINTERFACE
#include <ddraw.h>
#undef CINTERFACE
#include "main.h"
#include "ddraw.h"
#include "i76shell.h"
#include "zglide.h"

#define I76_LOG(_module, _function, ...) LogFunctionf(I76_EXE, _module, _function, __VA_ARGS__)

namespace i76 {
namespace data {

const char *errorMessage;

}

namespace original {

// advapi32.dll

LSTATUS (APIENTRY *RegOpenKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
LSTATUS (APIENTRY *RegCloseKey)(HKEY hKey);
LSTATUS (APIENTRY *RegQueryValueExA)(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
LSTATUS (APIENTRY *RegCreateKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition );
LSTATUS (APIENTRY *RegSetValueExA)(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData);

// gdi32.dll

int (WINAPI *AddFontResourceA)(LPCSTR Arg1);
HDC (WINAPI *CreateCompatibleDC)(HDC hdc);
HBITMAP (WINAPI *CreateDIBSection)(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset);
HFONT (WINAPI *CreateFontIndirectA)(LOGFONTA *lplf);
HPALETTE (WINAPI *CreatePalette)(CONST LOGPALETTE * plpal);
BOOL (WINAPI *CreateScalableFontResourceA)(DWORD fdwHidden, LPCSTR lpszFont, LPCSTR lpszFile, LPCSTR lpszPath);
BOOL (WINAPI *DeleteDC)(HDC hdc);
BOOL (WINAPI *DeleteObject)(HGDIOBJ ho);
int (WINAPI *GetDeviceCaps)(HDC hdc, int index);
HGDIOBJ (WINAPI *GetStockObject)(int i);
UINT (WINAPI *GetSystemPaletteEntries)(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries);
BOOL (APIENTRY *GetTextExtentExPointA)(HDC hdc, LPCSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize);
BOOL (APIENTRY *GetTextExtentPoint32A)(HDC hdc, LPCSTR lpString, int c, LPSIZE psizl);
BOOL (WINAPI *GdiFlush)(void);
UINT (WINAPI *RealizePalette)(HDC hdc);
BOOL (WINAPI *Rectangle)(HDC hdc, int left, int top, int right, int bottom);
BOOL (WINAPI *RemoveFontResourceA)(LPCSTR lpFileName);
HGDIOBJ (WINAPI *SelectObject)(HDC hdc, HGDIOBJ h);
HPALETTE (WINAPI *SelectPalette)(HDC hdc, HPALETTE hPal, BOOL bForceBkgd);
COLORREF (WINAPI *SetBkColor)(HDC hdc, COLORREF color);
int (WINAPI *SetBkMode)(HDC hdc, int mode);
int (WINAPI *SetDIBitsToDevice)(HDC hdc, int xDest, int yDest, DWORD w, DWORD h, int xSrc, int ySrc, UINT StartScan, UINT cLines, CONST VOID * lpvBits, CONST BITMAPINFO * lpbmi, UINT ColorUse);
DWORD (WINAPI *SetMapperFlags)(HDC hdc, DWORD flags);
UINT (WINAPI *SetPaletteEntries)(HPALETTE hpal, UINT iStart, UINT cEntries, CONST PALETTEENTRY *pPalEntries);
COLORREF (WINAPI *SetTextColor)(HDC hdc, COLORREF color);
BOOL (WINAPI *TextOutA)(HDC hdc, int x, int y, LPCSTR lpString, int c);

// kernel32.dll

BOOL (WINAPI *CloseHandle)(HANDLE hObject);
BOOL (WINAPI *CopyFileA)(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists);
HANDLE (WINAPI *CreateFileA)(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
HANDLE (WINAPI *CreateFileMappingA)(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName);
BOOL (WINAPI *DeleteFileA)(LPCSTR lpFileName);
BOOL (WINAPI *FindClose)(HANDLE hFindFile);
HANDLE (WINAPI *FindFirstFileA)(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
BOOL (WINAPI *FindNextFileA)(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
BOOL (WINAPI *FreeLibrary)(HMODULE hLibModule);
DWORD (WINAPI *GetCurrentDirectoryA)(DWORD nBufferLength, LPSTR lpBuffer);
HANDLE (WINAPI *GetCurrentProcess)();
UINT (WINAPI *GetDriveTypeA)(LPCSTR lpRootPathName);
BOOL (WINAPI *GetFileTime)(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
DWORD (WINAPI *GetLogicalDrives)(VOID);
HMODULE (WINAPI *GetModuleHandleA)(LPCSTR lpModuleName);
FARPROC (WINAPI *GetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
HANDLE (WINAPI *GetProcessHeap)();
DWORD (WINAPI *GetTickCount)();
VOID (WINAPI *GetStartupInfoA)(LPSTARTUPINFOA lpStartupInfo);
LCID (WINAPI *GetSystemDefaultLCID)();
VOID (WINAPI *GetSystemInfo)(LPSYSTEM_INFO lpSystemInfo);
BOOL (WINAPI *GetVolumeInformationA)(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize);
VOID (WINAPI *GlobalMemoryStatus)(LPMEMORYSTATUS lpBuffer);
LPVOID (WINAPI *HeapAlloc)(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
SIZE_T (WINAPI *HeapCompact)(HANDLE hHeap, DWORD dwFlags);
HANDLE (WINAPI *HeapCreate)(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize);
BOOL (WINAPI *HeapDestroy)(HANDLE hHeap);
BOOL (WINAPI *HeapFree)(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);
LPVOID (WINAPI *HeapReAlloc)(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes);
SIZE_T (WINAPI *HeapSize)(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem);
LPSTR (WINAPI *lstrcatA)(LPSTR lpString1, LPCSTR lpString2);
LPSTR (WINAPI *lstrcpyA)(LPSTR lpString1, LPCSTR lpString2);
HMODULE (WINAPI *LoadLibraryA)(LPCSTR);
LPVOID (WINAPI *MapViewOfFile)(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap);
VOID (WINAPI *OutputDebugStringA)(LPCSTR lpOutputString);
BOOL (WINAPI *SetFileAttributesA)(LPCSTR lpFileName, DWORD dwFileAttributes);
BOOL (WINAPI *SetPriorityClass)(HANDLE hProcess, DWORD dwPriorityClass);
BOOL (WINAPI *UnmapViewOfFile)(LPCVOID lpBaseAddress);
LPVOID (WINAPI *VirtualAlloc)(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
BOOL (WINAPI *VirtualFree)(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);
SIZE_T (WINAPI *VirtualQuery)(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

// strlkup.dll

//void *StrLookup_Global_Object;
void *(*StrLookupCreate)(char *_filename);
void (*StrLookupDestroy)(void *_obj);
char *(*StrLookupFind)(void *_obj, char *_string);
int (*StrLookupFormat)(char *buffer_, char *_format, ...);

// user32.dll

WNDPROC windowProc = nullptr;

BOOL (WINAPI *AdjustWindowRect)(LPRECT lpRect, DWORD dwStyle, BOOL bMenu);
HDC (WINAPI *BeginPaint)(HWND hWnd, LPPAINTSTRUCT lpPaint);
BOOL (WINAPI *ClientToScreen)(HWND hWnd, LPPOINT lpPoint);
BOOL (WINAPI *ClipCursor)(CONST RECT *lpRect);
HWND (WINAPI *CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
LRESULT (WINAPI *DefWindowProcA)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL (WINAPI *DestroyWindow)(HWND hWnd);
LRESULT (WINAPI *DispatchMessageA)(CONST MSG *lpMsg);
BOOL (WINAPI *EndPaint)(HWND hWnd, CONST PAINTSTRUCT *lpPaint);
HWND (WINAPI *FindWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName);
SHORT (WINAPI *GetAsyncKeyState)(int vKey);
BOOL (WINAPI *GetClientRect)(HWND hWnd, LPRECT lpRect);
BOOL (WINAPI *GetCursorPos)(LPPOINT lpPoint);
HDC (WINAPI *GetDC)(HWND hWnd);
HWND (WINAPI *GetFocus)(VOID);
int (WINAPI *GetKeyboardType)(int nTypeFlag);
SHORT (WINAPI *GetKeyState)(int nVirtKey);
int (WINAPI *GetSystemMetrics)(int nIndex);
BOOL (WINAPI *GetWindowRect)(HWND hWnd, LPRECT lpRect);
HCURSOR (WINAPI *LoadCursorA)(HINSTANCE hInstance, LPCSTR lpCursorName);
UINT (WINAPI *MapVirtualKeyA)(UINT uCode, UINT uMapType);
int (WINAPI *MessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
BOOL (WINAPI *PeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
ATOM (WINAPI *RegisterClassA)(CONST WNDCLASSA *lpWndClass);
int (WINAPI *ReleaseDC)(HWND hWnd, HDC hDC);
BOOL (WINAPI *ScreenToClient)(HWND hWnd, LPPOINT lpPoint);
LRESULT (WINAPI *SendMessageA)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HCURSOR (WINAPI *SetCursor)(HCURSOR hCursor);
BOOL (WINAPI *SetCursorPos)(int X, int Y);
HWND (WINAPI *SetFocus)(HWND hWnd);
BOOL (WINAPI *SetMenu)(HWND hWnd, HMENU hMenu);
BOOL (WINAPI *SetRect)(LPRECT lprc, int xLeft, int yTop, int xRight,int yBottom);
LONG (WINAPI *SetWindowLongA)(HWND hWnd, int nIndex, LONG dwNewLong);
BOOL (WINAPI *SetWindowPos)(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
int (WINAPI *ShowCursor)(BOOL bShow);
BOOL (WINAPI *ShowWindow)(HWND hWnd, int nCmdShow);
BOOL (WINAPI *TranslateMessage)(CONST MSG *lpMsg);
BOOL (WINAPI *UpdateWindow)(HWND hWnd);
BOOL (WINAPI *ValidateRect)(HWND hWnd, CONST RECT *lpRect);
int (WINAPIV *wsprintfA)(LPSTR, LPCSTR, ...);
int (WINAPI *wvsprintfA)(LPSTR, LPCSTR, va_list arglist);

// win32.dll

MCIERROR (WINAPI *mciSendCommandA)(MCIDEVICEID mciId, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

} // namespace original

namespace wrap {

// advapi32.dll

LSTATUS APIENTRY RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) {
	I76_LOG("advapi32.dll", "RegOpenKeyExA", "sub key:'%s'", lpSubKey);
	LSTATUS status = original::RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	return status;
}

LSTATUS APIENTRY RegCloseKey(HKEY hKey) {
	I76_LOG("advapi32.dll", "RegCloseKey");
	//return original::RegCloseKey(hKey);
	return 0;
}

LSTATUS APIENTRY RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
	I76_LOG("advapi32.dll", "RegQueryValueExA");
	//return original::RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	*lpData = 48;
	return 0;
}

LSTATUS APIENTRY RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition ) {
	I76_LOG("advapi32.dll", "RegCreateKeyExA", "sub key:'%s'", lpSubKey);
	LSTATUS status = original::RegCreateKeyExA(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
	return 0;
	//return status;
}

LSTATUS APIENTRY RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData) {
	I76_LOG("advapi32.dll", "RegSetValueExA");
	return original::RegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);
}

// gdi32.dll

int WINAPI AddFontResourceA(LPCSTR Arg1) {
	I76_LOG("gdi32.dll", "AddFontResourceA");
	return original::AddFontResourceA(Arg1);
}

HDC WINAPI CreateCompatibleDC(HDC hdc) {
	I76_LOG("gdi32.dll", "CreateCompatibleDC");
	return original::CreateCompatibleDC(hdc);
}

HBITMAP WINAPI CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset) {
	I76_LOG("gdi32.dll", "CreateDIBSection");
	return original::CreateDIBSection(hdc, pbmi, usage, ppvBits, hSection, offset);
}

HFONT WINAPI CreateFontIndirectA(LOGFONTA *lplf) {
	I76_LOG("gdi32.dll", "CreateFontIndirectA");
	return original::CreateFontIndirectA(lplf);
}

HPALETTE WINAPI CreatePalette(CONST LOGPALETTE * plpal) {
	I76_LOG("gdi32.dll", "CreatePalette");
	return original::CreatePalette(plpal);
}

BOOL WINAPI CreateScalableFontResourceA(DWORD fdwHidden, LPCSTR lpszFont, LPCSTR lpszFile, LPCSTR lpszPath) {
	I76_LOG("gdi32.dll", "CreateScalableFontResourceA");
	return original::CreateScalableFontResourceA(fdwHidden, lpszFont, lpszFile, lpszPath);
}

BOOL WINAPI DeleteDC(HDC hdc) {
	I76_LOG("gdi32.dll", "DeleteDC");
	return original::DeleteDC(hdc);
}

BOOL WINAPI DeleteObject(HGDIOBJ ho) {
	I76_LOG("gdi32.dll", "DeleteObject");
	return original::DeleteObject(ho);
}

int WINAPI GetDeviceCaps(HDC hdc, int index) {
	I76_LOG("gdi32.dll", "GetDeviceCaps");
	return original::GetDeviceCaps(hdc, index);
}

HGDIOBJ WINAPI GetStockObject(int i) {
	I76_LOG("gdi32.dll", "GetStockObject");
	return original::GetStockObject(i);
}

UINT WINAPI GetSystemPaletteEntries(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries) {
	I76_LOG("gdi32.dll", "GetSystemPaletteEntries");
	return original::GetSystemPaletteEntries(hdc, iStart, cEntries, pPalEntries);
}

BOOL APIENTRY GetTextExtentExPointA(HDC hdc, LPCSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize) {
	I76_LOG("gdi32.dll", "GetTextExtentExPointA");
	return original::GetTextExtentExPointA(hdc, lpszString, cchString, nMaxExtent, lpnFit, lpnDx, lpSize);
}

BOOL APIENTRY GetTextExtentPoint32A(HDC hdc, LPCSTR lpString, int c, LPSIZE psizl) {
	I76_LOG("gdi32.dll", "GetTextExtentPoint32A");
	return original::GetTextExtentPoint32A(hdc, lpString, c, psizl);
}

BOOL WINAPI GdiFlush(void) {
	I76_LOG("gdi32.dll", "GdiFlush");
	return original::GdiFlush();
}

UINT WINAPI RealizePalette(HDC hdc) {
	I76_LOG("gdi32.dll", "RealizePalette");
	return original::RealizePalette(hdc);
}

BOOL WINAPI Rectangle(HDC hdc, int left, int top, int right, int bottom) {
	I76_LOG("gdi32.dll", "Rectangle");
	return original::Rectangle(hdc, left, top, right, bottom);
}

BOOL WINAPI RemoveFontResourceA(LPCSTR lpFileName) {
	I76_LOG("gdi32.dll", "RemoveFontResourceA");
	return original::RemoveFontResourceA(lpFileName);
}

HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ h) {
	I76_LOG("gdi32.dll", "SelectObject");
	return original::SelectObject(hdc, h);
}

HPALETTE WINAPI SelectPalette(HDC hdc, HPALETTE hPal, BOOL bForceBkgd) {
	I76_LOG("gdi32.dll", "SelectPalette");
	return original::SelectPalette(hdc, hPal, bForceBkgd);
}

COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color) {
	I76_LOG("gdi32.dll", "SetBkColor");
	return original::SetBkColor(hdc, color);
}

int WINAPI SetBkMode(HDC hdc, int mode) {
	I76_LOG("gdi32.dll", "SetBkMode");
	return original::SetBkMode(hdc, mode);
}

int WINAPI SetDIBitsToDevice(HDC hdc, int xDest, int yDest, DWORD w, DWORD h, int xSrc, int ySrc, UINT StartScan, UINT cLines, CONST VOID * lpvBits, CONST BITMAPINFO * lpbmi, UINT ColorUse) {
	I76_LOG("gdi32.dll", "SetDIBitsToDevice");
	return original::SetDIBitsToDevice(hdc, xDest, yDest, w, h, xSrc, ySrc, StartScan, cLines, lpvBits, lpbmi, ColorUse);
}

DWORD WINAPI SetMapperFlags(HDC hdc, DWORD flags) {
	I76_LOG("gdi32.dll", "SetMapperFlags");
	return original::SetMapperFlags(hdc, flags);
}

UINT WINAPI SetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries, CONST PALETTEENTRY *pPalEntries) {
	I76_LOG("gdi32.dll", "SetPaletteEntries");
	return original::SetPaletteEntries(hpal, iStart, cEntries, pPalEntries);
}

COLORREF WINAPI SetTextColor(HDC hdc, COLORREF color) {
	I76_LOG("gdi32.dll", "SetTextColor");
	return original::SetTextColor(hdc, color);
}

BOOL WINAPI TextOutA(HDC hdc, int x, int y, LPCSTR lpString, int c) {
	I76_LOG("gdi32.dll", "TextOutA");
	return original::TextOutA(hdc, x, y, lpString, c);
}

// kernel32.dll

BOOL WINAPI CloseHandle(HANDLE hObject) {
	I76_LOG("kernel32.dll", "CloseHandle");
	return original::CloseHandle(hObject);
}

BOOL WINAPI CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists) {
	I76_LOG("kernel32.dll", "CopyFileA", "from:'%s', to:'%s'", lpExistingFileName, lpNewFileName);
	return original::CopyFileA(lpExistingFileName, lpNewFileName, bFailIfExists);
}

HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	I76_LOG("kernel32.dll", "CreateFileA", "'%s'", lpFileName);
	return original::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName) {
	I76_LOG("kernel32.dll", "CreateFileMappingA", "'%s'", lpName);
	return original::CreateFileMappingA(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

BOOL WINAPI DeleteFileA(LPCSTR lpFileName) {
	I76_LOG("kernel32.dll", "DeleteFileA", "'%s'", lpFileName);
	return original::DeleteFileA(lpFileName);
}

BOOL WINAPI FindClose(HANDLE hFindFile) {
	I76_LOG("kernel32.dll", "FindClose");
	return original::FindClose(hFindFile);
}

HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
	I76_LOG("kernel32.dll", "FindFirstFileA", "'%s'", lpFileName);
	return original::FindFirstFileA(lpFileName, lpFindFileData);
}

BOOL WINAPI FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) {
	I76_LOG("kernel32.dll", "FindNextFileA");
	return original::FindNextFileA(hFindFile, lpFindFileData);
}

BOOL WINAPI FreeLibrary(HMODULE hLibModule) {
	I76_LOG("kernel32.dll", "FreeLibrary");
	return original::FreeLibrary(hLibModule);
}

DWORD WINAPI GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer) {
	I76_LOG("kernel32.dll", "GetCurrentDirectoryA");
	return original::GetCurrentDirectoryA(nBufferLength, lpBuffer);
}

HANDLE WINAPI GetCurrentProcess() {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "GetCurrentProcess");
#endif
	return original::GetCurrentProcess();
}

UINT WINAPI GetDriveTypeA(LPCSTR lpRootPathName) {
	I76_LOG("kernel32.dll", "GetDriveTypeA", "root:'%s'", lpRootPathName);
	return original::GetDriveTypeA(lpRootPathName);
}

BOOL WINAPI GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime) {
	I76_LOG("kernel32.dll", "GetFileTime");
	return original::GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
}

DWORD WINAPI GetLogicalDrives() {
	I76_LOG("kernel32.dll", "GetLogicalDrives");
	return original::GetLogicalDrives();
}

HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName) {
	I76_LOG("kernel32.dll", "GetModuleHandleA", "'%s'", lpModuleName);
	return original::GetModuleHandleA(lpModuleName);
}

FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
	if (i76shell::IsModule(hModule))
		return i76shell::GetProcAddress(lpProcName);
#if WRAP_ZGLIDE
	if (zglide::IsModule(hModule))
		return zglide::GetProcAddress(lpProcName);
#endif
	I76_LOG("kernel32.dll", "GetProcAddress", "proc:'%s'", lpProcName);
	return original::GetProcAddress(hModule, lpProcName);
}

HANDLE WINAPI GetProcessHeap() {
	I76_LOG("kernel32.dll", "GetProcessHeap");
	return original::GetProcessHeap();
}

DWORD WINAPI GetTickCount() {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "GetTickCount");
#endif
	return original::GetTickCount();
}

VOID WINAPI GetStartupInfoA(LPSTARTUPINFOA lpStartupInfo) {
	I76_LOG("kernel32.dll", "GetStartupInfoA");
	original::GetStartupInfoA(lpStartupInfo);
}

LCID WINAPI GetSystemDefaultLCID() {
	I76_LOG("kernel32.dll", "GetSystemDefaultLCID");
	return original::GetSystemDefaultLCID();
}

BOOL WINAPI GetVolumeInformationA(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize) {
	I76_LOG("kernel32.dll", "GetVolumeInformationA");
	return original::GetVolumeInformationA(lpRootPathName, lpVolumeNameBuffer, nVolumeNameSize, lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags, lpFileSystemNameBuffer, nFileSystemNameSize);
}

VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo) {
	I76_LOG("kernel32.dll", "GetSystemInfo");
	original::GetSystemInfo(lpSystemInfo);
	// 386, 486 or 586 will result in call to _disable() which throws an exception
	lpSystemInfo->dwProcessorType = 0;
}

VOID WINAPI GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer) {
	I76_LOG("kernel32.dll", "GlobalMemoryStatus");
	original::GlobalMemoryStatus(lpBuffer);
}

LPVOID WINAPI HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "HeapAlloc");
#endif
	return original::HeapAlloc(hHeap, dwFlags, dwBytes);
}

SIZE_T WINAPI HeapCompact(HANDLE hHeap, DWORD dwFlags) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "HeapCompact");
#endif
	return original::HeapCompact(hHeap, dwFlags);
}

HANDLE WINAPI HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "HeapCreate");
#endif
	return original::HeapCreate(flOptions, dwInitialSize, dwMaximumSize);
}

BOOL WINAPI HeapDestroy(HANDLE hHeap) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "HeapDestroy");
#endif
	return original::HeapDestroy(hHeap);
}

BOOL WINAPI HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "HeapFree");
#endif
	return original::HeapFree(hHeap, dwFlags, lpMem);
}

LPVOID WINAPI HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "HeapReAlloc");
#endif
	return original::HeapReAlloc(hHeap, dwFlags, lpMem, dwBytes);
}

SIZE_T WINAPI HeapSize(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "HeapSize");
#endif
	return original::HeapSize(hHeap, dwFlags, lpMem);
}

LPSTR WINAPI lstrcatA(LPSTR lpString1, LPCSTR lpString2) {
	I76_LOG("kernel32.dll", "lstrcatA", "'%s' '%s'", lpString1, lpString2);
	return original::lstrcatA(lpString1, lpString2);
}

LPSTR WINAPI lstrcpyA(LPSTR lpString1, LPCSTR lpString2) {
	I76_LOG("kernel32.dll", "lstrcpyA", "'%s'", lpString2);
	return original::lstrcpyA(lpString1, lpString2);
}

HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName) {
	I76_LOG("kernel32.dll", "LoadLibraryA", "filename:'%s'", lpLibFileName);
	if (bx::strCmpI(lpLibFileName, I76SHELL_DLL) == 0)
		return i76shell::Load();
#if WRAP_ZGLIDE
	if (bx::strCmpI(lpLibFileName, ZGLIDE_DLL) == 0)
		return zglide::Load();
#endif
	return original::LoadLibraryA(lpLibFileName);
}

LPVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap) {
	I76_LOG("kernel32.dll", "MapViewOfFile");
	return original::MapViewOfFile(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
}

VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString) {
	I76_LOG("kernel32.dll", "OutputDebugStringA", "'%s'", lpOutputString);
	original::OutputDebugStringA(lpOutputString);
}

BOOL WINAPI SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes) {
	I76_LOG("kernel32.dll", "SetFileAttributesA", "filename:'%s'", lpFileName);
	return original::SetFileAttributesA(lpFileName, dwFileAttributes);
}

BOOL WINAPI SetPriorityClass(HANDLE hProcess, DWORD dwPriorityClass) {
#if LOG_VERBOSE
	I76_LOG("kernel32.dll", "SetPriorityClass");
#endif
	return original::SetPriorityClass(hProcess, dwPriorityClass);
}

BOOL WINAPI UnmapViewOfFile(LPCVOID lpBaseAddress) {
	I76_LOG("kernel32.dll", "UnmapViewOfFile");
	return original::UnmapViewOfFile(lpBaseAddress);
}

LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
	I76_LOG("kernel32.dll", "VirtualAlloc");
	return original::VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL WINAPI VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) {
	I76_LOG("kernel32.dll", "VirtualFree");
	return original::VirtualFree(lpAddress, dwSize, dwFreeType);
}

SIZE_T WINAPI VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	I76_LOG("kernel32.dll", "VirtualQuery");
	return original::VirtualQuery(lpAddress, lpBuffer, dwLength);
}

// strlkup.dll

//void *StrLookup_Global_Object;

void *StrLookupCreate(char *_filename) {
	I76_LOG("strlkup.dll", "StrLookupCreate", "filename:'%s'", _filename);
	return original::StrLookupCreate(_filename);
}

void StrLookupDestroy(void *_obj) {
	I76_LOG("strlkup.dll", "StrLookupDestroy");
	return original::StrLookupDestroy(_obj);
}

char *StrLookupFind(void *_obj, char *_string) {
	I76_LOG("strlkup.dll", "StrLookupFind", "string:'%s'", _string);
	return original::StrLookupFind(_obj, _string);
}

int StrLookupFormat(char *buffer_, char *_format, ...) {
	I76_LOG("strlkup.dll", "StrLookupFormat");
	return original::StrLookupFormat(buffer_, _format);
}

// user32.dll

BOOL WINAPI AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu) {
	I76_LOG("user32.dll", "AdjustWindowRect");
	return original::AdjustWindowRect(lpRect, dwStyle, bMenu);
}

HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint) {
	I76_LOG("user32.dll", "BeginPaint");
	return original::BeginPaint(hWnd, lpPaint);
}

BOOL WINAPI ClientToScreen(HWND hWnd, LPPOINT lpPoint) {
	I76_LOG("user32.dll", "ClientToScreen");
	return original::ClientToScreen(hWnd, lpPoint);
}

BOOL WINAPI ClipCursor(CONST RECT *lpRect) {
	if (lpRect)
		I76_LOG("user32.dll", "ClipCursor", "left:%d, right:%d, top:%d, bottom:%d", lpRect->left, lpRect->right, lpRect->top, lpRect->bottom);
	else
		I76_LOG("user32.dll", "ClipCursor");
	return original::ClipCursor(lpRect);
}

HWND WINAPI CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
	I76_LOG("user32.dll", "CreateWindowExA", "classname:'%s', window name:'%s', width:%d, height:%d", lpClassName, lpWindowName, nWidth, nHeight);
	return original::CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
#if LOG_VERBOSE
	I76_LOG("user32.dll", "DefWindowProcA", "msg:%s (%u)", MsgToString(Msg), Msg);
#endif
	return original::DefWindowProcA(hWnd, Msg, wParam, lParam);
}

BOOL WINAPI DestroyWindow(HWND hWnd) {
	I76_LOG("user32.dll", "DestroyWindow");
	return original::DestroyWindow(hWnd);
}

LRESULT WINAPI DispatchMessageA(CONST MSG *lpMsg) {
#if LOG_VERBOSE
	I76_LOG("user32.dll", "DispatchMessageA");
#endif
	return original::DispatchMessageA(lpMsg);
}

BOOL WINAPI EndPaint(HWND hWnd, CONST PAINTSTRUCT *lpPaint) {
	I76_LOG("user32.dll", "EndPaint");
	return original::EndPaint(hWnd, lpPaint);
}

HWND WINAPI FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {
	I76_LOG("user32.dll", "FindWindowA", "classname:'%s', window name:'%s'", lpClassName, lpWindowName);
	return original::FindWindowA(lpClassName, lpWindowName);
}

SHORT WINAPI GetAsyncKeyState(int vKey) {
	I76_LOG("user32.dll", "GetAsyncKeyState", "key:%d", vKey);
	return original::GetAsyncKeyState(vKey);
}

BOOL WINAPI GetClientRect(HWND hWnd, LPRECT lpRect) {
	I76_LOG("user32.dll", "GetClientRect");
	return original::GetClientRect(hWnd, lpRect);
}

BOOL WINAPI GetCursorPos(LPPOINT lpPoint) {
	I76_LOG("user32.dll", "GetCursorPos");
	return original::GetCursorPos(lpPoint);
}

HDC WINAPI GetDC(HWND hWnd) {
	I76_LOG("user32.dll", "GetDC");
	return original::GetDC(hWnd);
}

HWND WINAPI GetFocus(VOID) {
#if LOG_VERBOSE
	I76_LOG("user32.dll", "GetFocus");
#endif
	return original::GetFocus();
}

int WINAPI GetKeyboardType(int nTypeFlag) {
	I76_LOG("user32.dll", "GetKeyboardType");
	return original::GetKeyboardType(nTypeFlag);
}

SHORT WINAPI GetKeyState(int nVirtKey) {
	I76_LOG("user32.dll", "GetKeyState", "key:%d", nVirtKey);
	return original::GetKeyState(nVirtKey);
}

int WINAPI GetSystemMetrics(int nIndex) {
	I76_LOG("user32.dll", "GetSystemMetrics", "nIndex:%d", nIndex);
#if FORCE_1024_RESOLUTION
	if (nIndex == SM_CXSCREEN)
		return 1024;
	else if (nIndex == SM_CYSCREEN)
		return 768;
#endif
	return original::GetSystemMetrics(nIndex);
}

BOOL WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect) {
	I76_LOG("user32.dll", "GetWindowRect");
	return original::GetWindowRect(hWnd, lpRect);
}

HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) {
	I76_LOG("user32.dll", "LoadCursorA");
	return original::LoadCursorA(hInstance, lpCursorName);
}

UINT WINAPI MapVirtualKeyA(UINT uCode, UINT uMapType) {
	I76_LOG("user32.dll", "MapVirtualKeyA");
	return original::MapVirtualKeyA(uCode, uMapType);
}

int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	I76_LOG("user32.dll", "MessageBoxA", "text:'%s' caption:'%s'", lpText, lpCaption);
	return original::MessageBoxA(hWnd, lpText, lpCaption, uType);
}

BOOL WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
#if LOG_VERBOSE
	I76_LOG("user32.dll", "PeekMessageA");
#endif
	return original::PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

static LRESULT __stdcall WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
#if LOG_WINPROC
	Logf("   WNDPROC msg:%s (%u)", MsgToString(uMsg), uMsg);
#endif
	return original::windowProc(hWnd, uMsg, wParam, lParam);
}

ATOM WINAPI RegisterClassA(CONST WNDCLASSA *lpWndClass) {
	original::windowProc = lpWndClass->lpfnWndProc;
	((WNDCLASSA *)lpWndClass)->lpfnWndProc = WindowProc;
	I76_LOG("user32.dll", "RegisterClassA", "name:%s", lpWndClass->lpszClassName);
	return original::RegisterClassA(lpWndClass);
}

int WINAPI ReleaseDC(HWND hWnd, HDC hDC) {
	I76_LOG("user32.dll", "ReleaseDC");
	return original::ReleaseDC(hWnd, hDC);
}

BOOL WINAPI ScreenToClient(HWND hWnd, LPPOINT lpPoint) {
	I76_LOG("user32.dll", "ScreenToClient", "x:%d, y:%d", lpPoint->x, lpPoint->y);
	return original::ScreenToClient(hWnd, lpPoint);
}

LRESULT WINAPI SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	I76_LOG("user32.dll", "SendMessageA");
	return original::SendMessageA(hWnd, Msg, wParam, lParam);
}

HCURSOR WINAPI SetCursor(HCURSOR hCursor) {
	I76_LOG("user32.dll", "SetCursor");
	return original::SetCursor(hCursor);
}

BOOL WINAPI SetCursorPos(int X, int Y) {
	I76_LOG("user32.dll", "SetCursorPos", "x:%d, y:%d", X, Y);
	return original::SetCursorPos(X, Y);
}

HWND WINAPI SetFocus(HWND hWnd) {
	I76_LOG("user32.dll", "SetFocus");
	return original::SetFocus(hWnd);
}

BOOL WINAPI SetMenu(HWND hWnd, HMENU hMenu) {
	I76_LOG("user32.dll", "SetMenu");
	return original::SetMenu(hWnd, hMenu);
}

BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight,int yBottom) {
	I76_LOG("user32.dll", "SetRect");
	return original::SetRect(lprc, xLeft, yTop, xRight, yBottom);
}

LONG WINAPI SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong) {
	I76_LOG("user32.dll", "SetWindowLongA");
	return original::SetWindowLongA(hWnd, nIndex, dwNewLong);
}

BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
	I76_LOG("user32.dll", "SetWindowPos");
	return original::SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

int WINAPI ShowCursor(BOOL bShow) {
	I76_LOG("user32.dll", "ShowCursor", "value:%s", bShow ? "true" : "false");
	return original::ShowCursor(bShow);
}

BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) {
	I76_LOG("user32.dll", "ShowWindow");
	return original::ShowWindow(hWnd, nCmdShow);
}

BOOL WINAPI TranslateMessage(CONST MSG *lpMsg) {
#if LOG_VERBOSE
	I76_LOG("user32.dll", "TranslateMessage");
#endif
	return original::TranslateMessage(lpMsg);
}

BOOL WINAPI UpdateWindow(HWND hWnd) {
	I76_LOG("user32.dll", "UpdateWindow");
	return original::UpdateWindow(hWnd);
}

BOOL WINAPI ValidateRect(HWND hWnd, CONST RECT *lpRect) {
	I76_LOG("user32.dll", "ValidateRect");
	return original::ValidateRect(hWnd, lpRect);
}

int WINAPIV wsprintfA(LPSTR arg1, LPCSTR arg2, ...) {
	I76_LOG("user32.dll", "wsprintfA");
	return 0;
}

int WINAPI wvsprintfA(LPSTR arg1, LPCSTR arg2, va_list arglist) {
	I76_LOG("user32.dll", "wvsprintfA");
	return original::wvsprintfA(arg1, arg2, arglist);
}

// win32.dll

MCIERROR WINAPI mciSendCommandA(MCIDEVICEID mciId, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
	I76_LOG("win32.dll", "mciSendCommandA");
	return original::mciSendCommandA(mciId, uMsg, dwParam1, dwParam2);
}

} // namespace wrap

static WrappedFunc s_wrappedFuncs[] = {
	WRAPPED_FUNC(advapi32.dll, RegOpenKeyExA),
	WRAPPED_FUNC(advapi32.dll, RegCloseKey),
	WRAPPED_FUNC(advapi32.dll, RegQueryValueExA),
	WRAPPED_FUNC(advapi32.dll, RegCreateKeyExA),
	WRAPPED_FUNC(advapi32.dll, RegSetValueExA),
	WRAPPED_FUNC(gdi32.dll, AddFontResourceA),
	WRAPPED_FUNC(gdi32.dll, CreateCompatibleDC),
	WRAPPED_FUNC(gdi32.dll, CreateDIBSection),
	WRAPPED_FUNC(gdi32.dll, CreateFontIndirectA),
	WRAPPED_FUNC(gdi32.dll, CreatePalette),
	WRAPPED_FUNC(gdi32.dll, CreateScalableFontResourceA),
	WRAPPED_FUNC(gdi32.dll, DeleteDC),
	WRAPPED_FUNC(gdi32.dll, DeleteObject),
	WRAPPED_FUNC(gdi32.dll, GetDeviceCaps),
	WRAPPED_FUNC(gdi32.dll, GetStockObject),
	WRAPPED_FUNC(gdi32.dll, GetSystemPaletteEntries),
	WRAPPED_FUNC(gdi32.dll, GetTextExtentExPointA),
	WRAPPED_FUNC(gdi32.dll, GetTextExtentPoint32A),
	WRAPPED_FUNC(gdi32.dll, GdiFlush),
	WRAPPED_FUNC(gdi32.dll, RealizePalette),
	WRAPPED_FUNC(gdi32.dll, Rectangle),
	WRAPPED_FUNC(gdi32.dll, RemoveFontResourceA),
	WRAPPED_FUNC(gdi32.dll, SelectObject),
	WRAPPED_FUNC(gdi32.dll, SelectPalette),
	WRAPPED_FUNC(gdi32.dll, SetBkColor),
	WRAPPED_FUNC(gdi32.dll, SetBkMode),
	WRAPPED_FUNC(gdi32.dll, SetDIBitsToDevice),
	WRAPPED_FUNC(gdi32.dll, SetMapperFlags),
	WRAPPED_FUNC(gdi32.dll, SetPaletteEntries),
	WRAPPED_FUNC(gdi32.dll, SetTextColor),
	WRAPPED_FUNC(gdi32.dll, TextOutA),
	WRAPPED_FUNC(kernel32.dll, CloseHandle),
	WRAPPED_FUNC(kernel32.dll, CopyFileA),
	WRAPPED_FUNC(kernel32.dll, CreateFileA),
	WRAPPED_FUNC(kernel32.dll, CreateFileMappingA),
	WRAPPED_FUNC(kernel32.dll, DeleteFileA),
	WRAPPED_FUNC(kernel32.dll, FindClose),
	WRAPPED_FUNC(kernel32.dll, FindFirstFileA),
	WRAPPED_FUNC(kernel32.dll, FindNextFileA),
	WRAPPED_FUNC(kernel32.dll, FreeLibrary),
	WRAPPED_FUNC(kernel32.dll, GetCurrentDirectoryA),
	WRAPPED_FUNC(kernel32.dll, GetCurrentProcess),
	WRAPPED_FUNC(kernel32.dll, GetDriveTypeA),
	WRAPPED_FUNC(kernel32.dll, GetFileTime),
	WRAPPED_FUNC(kernel32.dll, GetLogicalDrives),
	WRAPPED_FUNC(kernel32.dll, GetModuleHandleA),
	WRAPPED_FUNC(kernel32.dll, GetProcAddress),
	WRAPPED_FUNC(kernel32.dll, GetProcessHeap),
	WRAPPED_FUNC(kernel32.dll, GetTickCount),
	WRAPPED_FUNC(kernel32.dll, GetStartupInfoA),
	WRAPPED_FUNC(kernel32.dll, GetSystemDefaultLCID),
	WRAPPED_FUNC(kernel32.dll, GetVolumeInformationA),
	WRAPPED_FUNC(kernel32.dll, GetSystemInfo),
	WRAPPED_FUNC(kernel32.dll, GlobalMemoryStatus),
	WRAPPED_FUNC(kernel32.dll, HeapAlloc),
	WRAPPED_FUNC(kernel32.dll, HeapCompact),
	WRAPPED_FUNC(kernel32.dll, HeapCreate),
	WRAPPED_FUNC(kernel32.dll, HeapDestroy),
	WRAPPED_FUNC(kernel32.dll, HeapFree),
	WRAPPED_FUNC(kernel32.dll, HeapReAlloc),
	WRAPPED_FUNC(kernel32.dll, HeapSize),
	WRAPPED_FUNC(kernel32.dll, lstrcatA),
	WRAPPED_FUNC(kernel32.dll, lstrcpyA),
	WRAPPED_FUNC(kernel32.dll, LoadLibraryA),
	WRAPPED_FUNC(kernel32.dll, MapViewOfFile),
	WRAPPED_FUNC(kernel32.dll, OutputDebugStringA),
	WRAPPED_FUNC(kernel32.dll, SetFileAttributesA),
	WRAPPED_FUNC(kernel32.dll, SetPriorityClass),
	WRAPPED_FUNC(kernel32.dll, UnmapViewOfFile),
	WRAPPED_FUNC(kernel32.dll, VirtualAlloc),
	WRAPPED_FUNC(kernel32.dll, VirtualFree),
	WRAPPED_FUNC(kernel32.dll, VirtualQuery),
	WRAPPED_FUNC(strlkup.dll, StrLookupCreate),
	WRAPPED_FUNC(strlkup.dll, StrLookupDestroy),
	WRAPPED_FUNC(strlkup.dll, StrLookupFind),
	WRAPPED_FUNC(strlkup.dll, StrLookupFormat),
	WRAPPED_FUNC(user32.dll, AdjustWindowRect),
	WRAPPED_FUNC(user32.dll, BeginPaint),
	WRAPPED_FUNC(user32.dll, ClientToScreen),
	WRAPPED_FUNC(user32.dll, ClipCursor),
	WRAPPED_FUNC(user32.dll, CreateWindowExA),
	WRAPPED_FUNC(user32.dll, DefWindowProcA),
	WRAPPED_FUNC(user32.dll, DestroyWindow),
	WRAPPED_FUNC(user32.dll, DispatchMessageA),
	WRAPPED_FUNC(user32.dll, EndPaint),
	WRAPPED_FUNC(user32.dll, FindWindowA),
	WRAPPED_FUNC(user32.dll, GetAsyncKeyState),
	WRAPPED_FUNC(user32.dll, GetClientRect),
	WRAPPED_FUNC(user32.dll, GetCursorPos),
	WRAPPED_FUNC(user32.dll, GetDC),
	WRAPPED_FUNC(user32.dll, GetFocus),
	WRAPPED_FUNC(user32.dll, GetKeyboardType),
	WRAPPED_FUNC(user32.dll, GetKeyState),
	WRAPPED_FUNC(user32.dll, GetSystemMetrics),
	WRAPPED_FUNC(user32.dll, GetWindowRect),
	WRAPPED_FUNC(user32.dll, LoadCursorA),
	WRAPPED_FUNC(user32.dll, MapVirtualKeyA),
	WRAPPED_FUNC(user32.dll, MessageBoxA),
	WRAPPED_FUNC(user32.dll, PeekMessageA),
	WRAPPED_FUNC(user32.dll, RegisterClassA),
	WRAPPED_FUNC(user32.dll, ReleaseDC),
	WRAPPED_FUNC(user32.dll, ScreenToClient),
	WRAPPED_FUNC(user32.dll, SendMessageA),
	WRAPPED_FUNC(user32.dll, SetCursor),
	WRAPPED_FUNC(user32.dll, SetCursorPos),
	WRAPPED_FUNC(user32.dll, SetFocus),
	WRAPPED_FUNC(user32.dll, SetMenu),
	WRAPPED_FUNC(user32.dll, SetRect),
	WRAPPED_FUNC(user32.dll, SetWindowLongA),
	WRAPPED_FUNC(user32.dll, SetWindowPos),
	WRAPPED_FUNC(user32.dll, ShowCursor),
	WRAPPED_FUNC(user32.dll, ShowWindow),
	WRAPPED_FUNC(user32.dll, TranslateMessage),
	WRAPPED_FUNC(user32.dll, UpdateWindow),
	WRAPPED_FUNC(user32.dll, ValidateRect),
	WRAPPED_FUNC(user32.dll, wsprintfA),
	WRAPPED_FUNC(user32.dll, wvsprintfA),
	WRAPPED_FUNC(win32.dll, mciSendCommandA),
	ddraw::g_DirectDrawCreateFunc,
	ddraw::g_DirectDrawEnumerateA
};

static OrdinalSymbol s_ordinalSymbols[] = {
	{ "SMACKW32.DLL", 21, "_SmackNextFrame@4" },
	{ "SMACKW32.DLL", 32, "_SmackWait@4" },
	{ "SMACKW32.DLL", 7, "_SmackBufferSetPalette@4" },
	{ "SMACKW32.DLL", 14, "_SmackOpen@12" },
	{ "SMACKW32.DLL", 5, "_SmackBufferNewPalette@12" },
	{ "SMACKW32.DLL", 17, "_SmackSoundOnOff@8" },
	{ "SMACKW32.DLL", 23, "_SmackToBuffer@28" },
	{ "SMACKW32.DLL", 18, "_SmackClose@4" },
	{ "SMACKW32.DLL", 28, "_SmackToBufferRect@8" },
	{ "SMACKW32.DLL", 25, "_SmackColorRemap@16" },
	{ "SMACKW32.DLL", 19, "_SmackDoFrame@4" },
	{ "SMACKW32.DLL", 3, "_SmackBufferBlit@32" },
	{ "SMACKW32.DLL", 6, "_SmackBufferClose@4" },
	{ "SMACKW32.DLL", 38, "_SmackSoundUseDirectSound@4" },
	{ "SMACKW32.DLL", 2, "_SmackBufferOpen@24" }
};

bool Load() {
	const char *filename = "i76.exe";
	FILE *f;
	if (fopen_s(&f, filename, "rb") != 0) {
		fprintf(stderr, "Error opening %s\n", filename);
		return false;
	}
	fseek(f, 0, SEEK_END);
	auto fileLength = (size_t)ftell(f);
	fseek(f, 0, SEEK_SET);
	auto fileData = new uint8_t[fileLength];
	if (fread(fileData, 1, fileLength, f) != fileLength) {
		delete [] fileData;
		fprintf(stderr, "Error reading %s\n", filename);
		return false;
	}
	fclose(f);
	MemoryModuleUserData userData;
	userData.ordinalSymbols = ArrayView<OrdinalSymbol>(s_ordinalSymbols, BX_COUNTOF(s_ordinalSymbols));
	userData.wrappedFuncs = ArrayView<WrappedFunc>(s_wrappedFuncs, BX_COUNTOF(s_wrappedFuncs));
	HMEMORYMODULE module = CustomMemoryLoadLibrary(fileData, fileLength, &userData);
	if (!module) {
		fprintf(stderr, "MemoryLoadLibraryEx failed for %s\n", filename);
		return false;
	}
	Logf("Loaded %s\n", filename);
	data::errorMessage = (const char *)(0x005FDB00);
	ddraw::Init();
	MemoryCallEntryPoint(module);
	return true;
}

} // namespace i76
