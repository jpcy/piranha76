#include <stdio.h>
#include <bx/bx.h>
#include <bx/string.h>
#include <ddraw.h>
#include "MemoryModule.h"
#include "main.h"
#include "i76shell.h"
#include "zglide.h"

namespace i76 {
namespace data {

const char *errorMessage;

struct DisplayMode
{
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
	uint32_t zero;
};

uint32_t *numDisplayModes;
DisplayMode *displayModes; // length: 50

}

namespace original {

// advapi32.dll

LSTATUS (APIENTRY *RegOpenKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
LSTATUS (APIENTRY *RegCloseKey)(HKEY hKey);
LSTATUS (APIENTRY *RegQueryValueExA)(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
LSTATUS (APIENTRY *RegCreateKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition );
LSTATUS (APIENTRY *RegSetValueExA)(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData);

// ddraw.dll

LPDDENUMMODESCALLBACK2 ddrawEnumDisplayModes = nullptr;
LPDIRECTDRAW7 directDrawInterface = nullptr;

HRESULT (WINAPI *DirectDrawCreate)(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter);
HRESULT (WINAPI *DirectDrawEnumerateA)(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext);

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
	Logf("[i76.exe | advapi32.dll | RegOpenKeyExA] sub key:'%s'\n", lpSubKey);
	LSTATUS status = original::RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	return status;
}

LSTATUS APIENTRY RegCloseKey(HKEY hKey) {
	Logf("[i76.exe | advapi32.dll | RegCloseKey]\n");
	//return original::RegCloseKey(hKey);
	return 0;
}

LSTATUS APIENTRY RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
	Logf("[i76.exe | advapi32.dll | RegQueryValueExA]\n");
	//return original::RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	*lpData = 48;
	return 0;
}

LSTATUS APIENTRY RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition ) {
	Logf("[i76.exe | advapi32.dll | RegCreateKeyExA] sub key:'%s'\n", lpSubKey);
	LSTATUS status = original::RegCreateKeyExA(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
	return 0;
	//return status;
}

LSTATUS APIENTRY RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData) {
	Logf("[i76.exe | advapi32.dll | RegSetValueExA]\n");
	return original::RegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);
}

// ddraw.dll

static HRESULT __stdcall EnumDisplayModesCallback(LPDDSURFACEDESC2 Arg1, LPVOID Arg2) {
	Logf("   %ux%u, %u bpp\n", Arg1->dwWidth, Arg1->dwHeight, Arg1->ddpfPixelFormat.dwRGBBitCount);
	if (Arg2)
		Logf("      arg2 is not null\n");
#if FORCE_ENUM_DISPLAY_MODE_16BPP
	// i76 only cares about dwWidth, dwHeight, and this
	Arg1->ddpfPixelFormat.dwRGBBitCount = 16;
#endif
#if 1
	data::DisplayMode &mode = data::displayModes[*data::numDisplayModes];
	mode.width = Arg1->dwWidth;
	mode.height = Arg1->dwHeight;
	mode.bpp = Arg1->ddpfPixelFormat.dwRGBBitCount;
	mode.zero = 0;
	(*data::numDisplayModes)++;
	return DDENUMRET_OK;
#else
	HRESULT hr = original::ddrawEnumDisplayModes(Arg1, Arg2);
	if (hr != DDENUMRET_OK)
		Logf("      cancel enumeration\n");
	return hr;
#endif
}

struct CustomIDirectDraw
{
	/*** IUnknown methods ***/
	virtual __declspec(nothrow) HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj) {
		Logf("[i76.exe | IDirectDraw::QueryInterface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->QueryInterface(riid, ppvObj));
	}

	virtual __declspec(nothrow) ULONG __stdcall AddRef() {
		Logf("[i76.exe | IDirectDraw::AddRef]\n");
		return original::directDrawInterface->AddRef();
	}

	virtual __declspec(nothrow) ULONG __stdcall Release() {
		Logf("[i76.exe | IDirectDraw::Release]\n");
		return original::directDrawInterface->Release();
	}

	/*** IDirectDraw methods ***/
	virtual __declspec(nothrow) HRESULT __stdcall Compact() {
		Logf("[i76.exe | IDirectDraw::Compact]\n");
		CHECK_HR_RETURN(original::directDrawInterface->Compact());
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreateClipper(DWORD arg1, LPDIRECTDRAWCLIPPER FAR* arg2, IUnknown FAR * arg3) {
		Logf("[i76.exe | IDirectDraw::CreateClipper]\n");
		CHECK_HR_RETURN(original::directDrawInterface->CreateClipper(arg1, arg2, arg3));
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreatePalette(DWORD arg1, LPPALETTEENTRY arg2, LPDIRECTDRAWPALETTE FAR* arg3, IUnknown FAR * arg4) {
		Logf("[i76.exe | IDirectDraw::CreatePalette]\n");
		CHECK_HR_RETURN(original::directDrawInterface->CreatePalette(arg1, arg2, arg3, arg4));
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreateSurface(LPDDSURFACEDESC2 arg1, LPDIRECTDRAWSURFACE7 FAR *arg2, IUnknown FAR *arg3) {
		Logf("[i76.exe | IDirectDraw::CreateSurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->CreateSurface(arg1, arg2, arg3));
	}

	virtual __declspec(nothrow) HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE7 arg1, LPDIRECTDRAWSURFACE7 FAR * arg2) {
		Logf("[i76.exe | IDirectDraw::DuplicateSurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->DuplicateSurface(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall EnumDisplayModes(DWORD arg1, LPDDSURFACEDESC2 arg2, LPVOID arg3, LPDDENUMMODESCALLBACK2 arg4) {
		Logf("[i76.exe | IDirectDraw::EnumDisplayModes]\n");
		original::ddrawEnumDisplayModes = arg4;
		CHECK_HR_RETURN(original::directDrawInterface->EnumDisplayModes(arg1, arg2, arg3, EnumDisplayModesCallback));
	}

	virtual __declspec(nothrow) HRESULT __stdcall EnumSurfaces(DWORD arg1, LPDDSURFACEDESC2 arg2, LPVOID arg3, LPDDENUMSURFACESCALLBACK7 arg4) {
		Logf("[i76.exe | IDirectDraw::EnumSurfaces]\n");
		CHECK_HR_RETURN(original::directDrawInterface->EnumSurfaces(arg1, arg2, arg3, arg4));
	}

	virtual __declspec(nothrow) HRESULT __stdcall FlipToGDISurface() {
		Logf("[i76.exe | IDirectDraw::FlipToGDISurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->FlipToGDISurface());
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetCaps(LPDDCAPS arg1, LPDDCAPS arg2) {
		Logf("[i76.exe | IDirectDraw::GetCaps]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetCaps(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC2 arg1) {
		Logf("[i76.exe | IDirectDraw::GetDisplayMode]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetDisplayMode(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetFourCCCodes(LPDWORD arg1, LPDWORD arg2) {
		Logf("[i76.exe | IDirectDraw::GetFourCCCodes]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetFourCCCodes(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE7 FAR *arg1) {
		Logf("[i76.exe | IDirectDraw::GetGDISurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetGDISurface(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetMonitorFrequency(LPDWORD arg1) {
		Logf("[i76.exe | IDirectDraw::GetMonitorFrequency]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetMonitorFrequency(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetScanLine(LPDWORD arg1) {
		Logf("[i76.exe | IDirectDraw::GetScanLine]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetScanLine(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetVerticalBlankStatus(LPBOOL arg1) {
		Logf("[i76.exe | IDirectDraw::GetVerticalBlankStatus]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetVerticalBlankStatus(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall Initialize(GUID FAR *arg1) {
		Logf("[i76.exe | IDirectDraw::Initialize]\n");
		CHECK_HR_RETURN(original::directDrawInterface->Initialize(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall RestoreDisplayMode() {
		Logf("[i76.exe | IDirectDraw::RestoreDisplayMode]\n");
		CHECK_HR_RETURN(original::directDrawInterface->RestoreDisplayMode());
	}

	virtual __declspec(nothrow) HRESULT __stdcall SetCooperativeLevel(HWND arg1, DWORD arg2) {
		// 17 = DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE
		Logf("[i76.exe | IDirectDraw::SetCooperativeLevel value:%u]\n", arg2);
#if FORCE_WINDOWED
		CHECK_HR_RETURN(original::directDrawInterface->SetCooperativeLevel(arg1, DDSCL_NORMAL));
#else
		CHECK_HR_RETURN(original::directDrawInterface->SetCooperativeLevel(arg1, arg2));
#endif
	}

	// https://docs.microsoft.com/en-us/windows/desktop/api/ddraw/nf-ddraw-idirectdraw7-setdisplaymode
	// "As part of the prior-version IDirectDraw interface, this method did not include the dwRefreshRate and dwFlags parameters."
	//virtual __declspec(nothrow) HRESULT __stdcall SetDisplayMode(DWORD width, DWORD height, DWORD bpp, DWORD refreshRate, DWORD flags) {
	virtual __declspec(nothrow) HRESULT __stdcall SetDisplayMode(DWORD width, DWORD height, DWORD bpp) {
		Logf("[i76.exe | IDirectDraw::SetDisplayMode] width:%u, height:%u, bpp:%u\n", width, height, bpp);
		CHECK_HR_RETURN(original::directDrawInterface->SetDisplayMode(width, height, bpp, 60, 0));
	}

	virtual __declspec(nothrow) HRESULT __stdcall WaitForVerticalBlank(DWORD arg1, HANDLE arg2) {
		Logf("[i76.exe | IDirectDraw::WaitForVerticalBlank]\n");
		CHECK_HR_RETURN(original::directDrawInterface->WaitForVerticalBlank(arg1, arg2));
	}

	/*** Added in the v2 interface ***/
	virtual __declspec(nothrow) HRESULT __stdcall GetAvailableVidMem(LPDDSCAPS2 arg1, LPDWORD arg2, LPDWORD arg3) {
		Logf("[i76.exe | IDirectDraw::GetAvailableVidMem]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetAvailableVidMem(arg1, arg2, arg3));
	}

	/*** Added in the V4 Interface ***/
	virtual __declspec(nothrow) HRESULT __stdcall GetSurfaceFromDC(HDC arg1, LPDIRECTDRAWSURFACE7 *arg2) {
		Logf("[i76.exe | IDirectDraw::GetSurfaceFromDC]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetSurfaceFromDC(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall RestoreAllSurfaces() {
		Logf("[i76.exe | IDirectDraw::RestoreAllSurfaces]\n");
		CHECK_HR_RETURN(original::directDrawInterface->RestoreAllSurfaces());
	}

	virtual __declspec(nothrow) HRESULT __stdcall TestCooperativeLevel() {
		Logf("[i76.exe | IDirectDraw::TestCooperativeLevel]\n");
		CHECK_HR_RETURN(original::directDrawInterface->TestCooperativeLevel());
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 arg1, DWORD arg2) {
		Logf("[i76.exe | IDirectDraw::GetDeviceIdentifier]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetDeviceIdentifier(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall StartModeTest(LPSIZE arg1, DWORD arg2, DWORD arg3) {
		Logf("[i76.exe | IDirectDraw::StartModeTest]\n");
		CHECK_HR_RETURN(original::directDrawInterface->StartModeTest(arg1, arg2, arg3));
	}

	virtual __declspec(nothrow) HRESULT __stdcall EvaluateMode(DWORD arg1, DWORD * arg2) {
		Logf("[i76.exe | IDirectDraw::EvaluateMode]\n");
		CHECK_HR_RETURN(original::directDrawInterface->EvaluateMode(arg1, arg2));
	}
};

static CustomIDirectDraw *directDrawInterface = nullptr;

HRESULT WINAPI DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter) {
	Logf("[i76.exe | ddraw.dll | DirectDrawCreate]\n");
	HRESULT hr = original::DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
	if (hr)
		Logf("HRESULT: %u\n", hr);
#if WRAP_DDRAW
	original::directDrawInterface = (LPDIRECTDRAW7)*lplpDD;
	directDrawInterface = new CustomIDirectDraw();
	*lplpDD = (LPDIRECTDRAW)directDrawInterface;
#endif
	return hr;
}

HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext) {
	Logf("[i76.exe | ddraw.dll | DirectDrawEnumerateA]\n");
	CHECK_HR_RETURN(original::DirectDrawEnumerateA(lpCallback, lpContext));
}

// gdi32.dll

int WINAPI AddFontResourceA(LPCSTR Arg1) {
	Logf("[i76.exe | gdi32.dll | AddFontResourceA]\n");
	return original::AddFontResourceA(Arg1);
}

HDC WINAPI CreateCompatibleDC(HDC hdc) {
	Logf("[i76.exe | gdi32.dll | CreateCompatibleDC]\n");
	return original::CreateCompatibleDC(hdc);
}

HBITMAP WINAPI CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset) {
	Logf("[i76.exe | gdi32.dll | CreateDIBSection]\n");
	return original::CreateDIBSection(hdc, pbmi, usage, ppvBits, hSection, offset);
}

HFONT WINAPI CreateFontIndirectA(LOGFONTA *lplf) {
	Logf("[i76.exe | gdi32.dll | CreateFontIndirectA]\n");
	return original::CreateFontIndirectA(lplf);
}

HPALETTE WINAPI CreatePalette(CONST LOGPALETTE * plpal) {
	Logf("[i76.exe | gdi32.dll | CreatePalette]\n");
	return original::CreatePalette(plpal);
}

BOOL WINAPI CreateScalableFontResourceA(DWORD fdwHidden, LPCSTR lpszFont, LPCSTR lpszFile, LPCSTR lpszPath) {
	Logf("[i76.exe | gdi32.dll | CreateScalableFontResourceA]\n");
	return original::CreateScalableFontResourceA(fdwHidden, lpszFont, lpszFile, lpszPath);
}

BOOL WINAPI DeleteDC(HDC hdc) {
	Logf("[i76.exe | gdi32.dll | DeleteDC]\n");
	return original::DeleteDC(hdc);
}

BOOL WINAPI DeleteObject(HGDIOBJ ho) {
	Logf("[i76.exe | gdi32.dll | DeleteObject]\n");
	return original::DeleteObject(ho);
}

int WINAPI GetDeviceCaps(HDC hdc, int index) {
	Logf("[i76.exe | gdi32.dll | GetDeviceCaps]\n");
	return original::GetDeviceCaps(hdc, index);
}

HGDIOBJ WINAPI GetStockObject(int i) {
	Logf("[i76.exe | gdi32.dll | GetStockObject]\n");
	return original::GetStockObject(i);
}

UINT WINAPI GetSystemPaletteEntries(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries) {
	Logf("[i76.exe | gdi32.dll | GetSystemPaletteEntries]\n");
	return original::GetSystemPaletteEntries(hdc, iStart, cEntries, pPalEntries);
}

BOOL APIENTRY GetTextExtentExPointA(HDC hdc, LPCSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize) {
	Logf("[i76.exe | gdi32.dll | GetTextExtentExPointA]\n");
	return original::GetTextExtentExPointA(hdc, lpszString, cchString, nMaxExtent, lpnFit, lpnDx, lpSize);
}

BOOL APIENTRY GetTextExtentPoint32A(HDC hdc, LPCSTR lpString, int c, LPSIZE psizl) {
	Logf("[i76.exe | gdi32.dll | GetTextExtentPoint32A]\n");
	return original::GetTextExtentPoint32A(hdc, lpString, c, psizl);
}

BOOL WINAPI GdiFlush(void) {
	Logf("[i76.exe | gdi32.dll | GdiFlush]\n");
	return original::GdiFlush();
}

UINT WINAPI RealizePalette(HDC hdc) {
	Logf("[i76.exe | gdi32.dll | RealizePalette]\n");
	return original::RealizePalette(hdc);
}

BOOL WINAPI Rectangle(HDC hdc, int left, int top, int right, int bottom) {
	Logf("[i76.exe | gdi32.dll | Rectangle]\n");
	return original::Rectangle(hdc, left, top, right, bottom);
}

BOOL WINAPI RemoveFontResourceA(LPCSTR lpFileName) {
	Logf("[i76.exe | gdi32.dll | RemoveFontResourceA]\n");
	return original::RemoveFontResourceA(lpFileName);
}

HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ h) {
	Logf("[i76.exe | gdi32.dll | SelectObject]\n");
	return original::SelectObject(hdc, h);
}

HPALETTE WINAPI SelectPalette(HDC hdc, HPALETTE hPal, BOOL bForceBkgd) {
	Logf("[i76.exe | gdi32.dll | SelectPalette]\n");
	return original::SelectPalette(hdc, hPal, bForceBkgd);
}

COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color) {
	Logf("[i76.exe | gdi32.dll | SetBkColor]\n");
	return original::SetBkColor(hdc, color);
}

int WINAPI SetBkMode(HDC hdc, int mode) {
	Logf("[i76.exe | gdi32.dll | SetBkMode]\n");
	return original::SetBkMode(hdc, mode);
}

int WINAPI SetDIBitsToDevice(HDC hdc, int xDest, int yDest, DWORD w, DWORD h, int xSrc, int ySrc, UINT StartScan, UINT cLines, CONST VOID * lpvBits, CONST BITMAPINFO * lpbmi, UINT ColorUse) {
	Logf("[i76.exe | gdi32.dll | SetDIBitsToDevice]\n");
	return original::SetDIBitsToDevice(hdc, xDest, yDest, w, h, xSrc, ySrc, StartScan, cLines, lpvBits, lpbmi, ColorUse);
}

DWORD WINAPI SetMapperFlags(HDC hdc, DWORD flags) {
	Logf("[i76.exe | gdi32.dll | SetMapperFlags]\n");
	return original::SetMapperFlags(hdc, flags);
}

UINT WINAPI SetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries, CONST PALETTEENTRY *pPalEntries) {
	Logf("[i76.exe | gdi32.dll | SetPaletteEntries]\n");
	return original::SetPaletteEntries(hpal, iStart, cEntries, pPalEntries);
}

COLORREF WINAPI SetTextColor(HDC hdc, COLORREF color) {
	Logf("[i76.exe | gdi32.dll | SetTextColor]\n");
	return original::SetTextColor(hdc, color);
}

BOOL WINAPI TextOutA(HDC hdc, int x, int y, LPCSTR lpString, int c) {
	Logf("[i76.exe | gdi32.dll | TextOutA]\n");
	return original::TextOutA(hdc, x, y, lpString, c);
}

// kernel32.dll

BOOL WINAPI CloseHandle(HANDLE hObject) {
	Logf("[i76.exe | kernel32.dll | CloseHandle]\n");
	return original::CloseHandle(hObject);
}

BOOL WINAPI CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists) {
	Logf("[i76.exe | kernel32.dll | CopyFileA] from:'%s', to:'%s'\n", lpExistingFileName, lpNewFileName);
	return original::CopyFileA(lpExistingFileName, lpNewFileName, bFailIfExists);
}

HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	Logf("[i76.exe | kernel32.dll | CreateFileA] '%s'\n", lpFileName);
	return original::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName) {
	Logf("[i76.exe | kernel32.dll | CreateFileMappingA] '%s'\n", lpName);
	return original::CreateFileMappingA(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

BOOL WINAPI DeleteFileA(LPCSTR lpFileName) {
	Logf("[i76.exe | kernel32.dll | DeleteFileA] '%s'\n", lpFileName);
	return original::DeleteFileA(lpFileName);
}

BOOL WINAPI FindClose(HANDLE hFindFile) {
	Logf("[i76.exe | kernel32.dll | FindClose]\n");
	return original::FindClose(hFindFile);
}

HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
	Logf("[i76.exe | kernel32.dll | FindFirstFileA] '%s'\n", lpFileName);
	return original::FindFirstFileA(lpFileName, lpFindFileData);
}

BOOL WINAPI FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) {
	Logf("[i76.exe | kernel32.dll | FindNextFileA]\n");
	return original::FindNextFileA(hFindFile, lpFindFileData);
}

BOOL WINAPI FreeLibrary(HMODULE hLibModule) {
	Logf("[i76.exe | kernel32.dll | FreeLibrary]\n");
	return original::FreeLibrary(hLibModule);
}

DWORD WINAPI GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer) {
	Logf("[i76.exe | kernel32.dll | GetCurrentDirectoryA]\n");
	return original::GetCurrentDirectoryA(nBufferLength, lpBuffer);
}

HANDLE WINAPI GetCurrentProcess() {
	Logf("[i76.exe | kernel32.dll | GetCurrentProcess]\n");
	return original::GetCurrentProcess();
}

UINT WINAPI GetDriveTypeA(LPCSTR lpRootPathName) {
	Logf("[i76.exe | kernel32.dll | GetDriveTypeA] root:'%s'\n", lpRootPathName);
	return original::GetDriveTypeA(lpRootPathName);
}

BOOL WINAPI GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime) {
	Logf("[i76.exe | kernel32.dll | GetFileTime]\n");
	return original::GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
}

DWORD WINAPI GetLogicalDrives() {
	Logf("[i76.exe | kernel32.dll | GetLogicalDrives]\n");
	return original::GetLogicalDrives();
}

HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName) {
	Logf("[i76.exe | kernel32.dll | GetModuleHandleA] '%s'\n", lpModuleName);
	return original::GetModuleHandleA(lpModuleName);
}

FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
	if (i76shell::IsModule(hModule))
		return i76shell::GetProcAddress(lpProcName);
	if (zglide::IsModule(hModule))
		return zglide::GetProcAddress(lpProcName);
	Logf("[i76.exe | kernel32.dll | GetProcAddress] proc:'%s'\n", lpProcName);
	return original::GetProcAddress(hModule, lpProcName);
}

HANDLE WINAPI GetProcessHeap() {
	Logf("[i76.exe | kernel32.dll | GetProcessHeap]\n");
	return original::GetProcessHeap();
}

DWORD WINAPI GetTickCount() {
#if LOG_VERBOSE
	Logf("[i76.exe | kernel32.dll | GetTickCount]\n");
#endif
	return original::GetTickCount();
}

VOID WINAPI GetStartupInfoA(LPSTARTUPINFOA lpStartupInfo) {
	Logf("[i76.exe | kernel32.dll | GetStartupInfoA]\n");
	original::GetStartupInfoA(lpStartupInfo);
}

LCID WINAPI GetSystemDefaultLCID() {
	Logf("[i76.exe | kernel32.dll | GetSystemDefaultLCID]\n");
	return original::GetSystemDefaultLCID();
}

BOOL WINAPI GetVolumeInformationA(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize) {
	Logf("[i76.exe | kernel32.dll | GetVolumeInformationA]\n");
	return original::GetVolumeInformationA(lpRootPathName, lpVolumeNameBuffer, nVolumeNameSize, lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags, lpFileSystemNameBuffer, nFileSystemNameSize);
}

VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo) {
	Logf("[i76.exe | kernel32.dll | GetSystemInfo]\n");
	original::GetSystemInfo(lpSystemInfo);
	// 386, 486 or 586 will result in call to _disable() which throws an exception
	lpSystemInfo->dwProcessorType = 0;
}

VOID WINAPI GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer) {
	Logf("[i76.exe | kernel32.dll | GlobalMemoryStatus]\n");
	original::GlobalMemoryStatus(lpBuffer);
}

LPVOID WINAPI HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes) {
#if LOG_VERBOSE
	Logf("[i76.exe | kernel32.dll | HeapAlloc]\n");
#endif
	return original::HeapAlloc(hHeap, dwFlags, dwBytes);
}

SIZE_T WINAPI HeapCompact(HANDLE hHeap, DWORD dwFlags) {
	Logf("[i76.exe | kernel32.dll | HeapCompact]\n");
	return original::HeapCompact(hHeap, dwFlags);
}

HANDLE WINAPI HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) {
	Logf("[i76.exe | kernel32.dll | HeapCreate]\n");
	return original::HeapCreate(flOptions, dwInitialSize, dwMaximumSize);
}

BOOL WINAPI HeapDestroy(HANDLE hHeap) {
	Logf("[i76.exe | kernel32.dll | HeapDestroy]\n");
	return original::HeapDestroy(hHeap);
}

BOOL WINAPI HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
#if LOG_VERBOSE
	Logf("[i76.exe | kernel32.dll | HeapFree]\n");
#endif
	return original::HeapFree(hHeap, dwFlags, lpMem);
}

LPVOID WINAPI HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes) {
	Logf("[i76.exe | kernel32.dll | HeapReAlloc]\n");
	return original::HeapReAlloc(hHeap, dwFlags, lpMem, dwBytes);
}

SIZE_T WINAPI HeapSize(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) {
#if LOG_VERBOSE
	Logf("[i76.exe | kernel32.dll | HeapSize]\n");
#endif
	return original::HeapSize(hHeap, dwFlags, lpMem);
}

LPSTR WINAPI lstrcatA(LPSTR lpString1, LPCSTR lpString2) {
	Logf("[i76.exe | kernel32.dll | lstrcatA] '%s' '%s'\n", lpString1, lpString2);
	return original::lstrcatA(lpString1, lpString2);
}

LPSTR WINAPI lstrcpyA(LPSTR lpString1, LPCSTR lpString2) {
	Logf("[i76.exe | kernel32.dll | lstrcpyA] '%s'\n", lpString2);
	return original::lstrcpyA(lpString1, lpString2);
}

HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName) {
	Logf("[i76.exe | kernel32.dll | LoadLibraryA] filename:'%s'\n", lpLibFileName);
	if (bx::strCmpI(lpLibFileName, I76SHELL_DLL) == 0)
		return i76shell::Load();
	if (bx::strCmpI(lpLibFileName, ZGLIDE_DLL) == 0)
		return zglide::Load();
	return original::LoadLibraryA(lpLibFileName);
}

LPVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap) {
	Logf("[i76.exe | kernel32.dll | MapViewOfFile]\n");
	return original::MapViewOfFile(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
}

VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString) {
	Logf("[i76.exe | kernel32.dll | OutputDebugStringA] '%s'\n", lpOutputString);
	original::OutputDebugStringA(lpOutputString);
}

BOOL WINAPI SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes) {
	Logf("[i76.exe | kernel32.dll | SetFileAttributesA] filename:'%s'\n", lpFileName);
	return original::SetFileAttributesA(lpFileName, dwFileAttributes);
}

BOOL WINAPI SetPriorityClass(HANDLE hProcess, DWORD dwPriorityClass) {
	Logf("[i76.exe | kernel32.dll | SetPriorityClass]\n");
	return original::SetPriorityClass(hProcess, dwPriorityClass);
}

BOOL WINAPI UnmapViewOfFile(LPCVOID lpBaseAddress) {
	Logf("[i76.exe | kernel32.dll | UnmapViewOfFile]\n");
	return original::UnmapViewOfFile(lpBaseAddress);
}

LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
	Logf("[i76.exe | kernel32.dll | VirtualAlloc]\n");
	return original::VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL WINAPI VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) {
	Logf("[i76.exe | kernel32.dll | VirtualFree]\n");
	return original::VirtualFree(lpAddress, dwSize, dwFreeType);
}

SIZE_T WINAPI VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	Logf("[i76.exe | kernel32.dll | VirtualQuery]\n");
	return original::VirtualQuery(lpAddress, lpBuffer, dwLength);
}

// strlkup.dll

//void *StrLookup_Global_Object;

void *StrLookupCreate(char *_filename) {
	Logf("[i76.exe | strlkup.dll | StrLookupCreate] filename:'%s'\n", _filename);
	return original::StrLookupCreate(_filename);
}

void StrLookupDestroy(void *_obj) {
	Logf("[i76.exe | strlkup.dll | StrLookupDestroy]\n");
	return original::StrLookupDestroy(_obj);
}

char *StrLookupFind(void *_obj, char *_string) {
	Logf("[i76.exe | strlkup.dll | StrLookupFind] string:'%s'\n", _string);
	return original::StrLookupFind(_obj, _string);
}

int StrLookupFormat(char *buffer_, char *_format, ...) {
	Logf("[i76.exe | strlkup.dll | StrLookupFormat]\n");
	return original::StrLookupFormat(buffer_, _format);
}

// user32.dll

BOOL WINAPI AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu) {
	Logf("[i76.exe | user32.dll | AdjustWindowRect]\n");
	return original::AdjustWindowRect(lpRect, dwStyle, bMenu);
}

HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint) {
	Logf("[i76.exe | user32.dll | BeginPaint]\n");
	return original::BeginPaint(hWnd, lpPaint);
}

BOOL WINAPI ClientToScreen(HWND hWnd, LPPOINT lpPoint) {
	Logf("[i76.exe | user32.dll | ClientToScreen]\n");
	return original::ClientToScreen(hWnd, lpPoint);
}

BOOL WINAPI ClipCursor(CONST RECT *lpRect) {
	Logf("[i76.exe | user32.dll | ClipCursor]");
	if (lpRect)
		Logf(" left:%d, right:%d, top:%d, bottom:%d\n", lpRect->left, lpRect->right, lpRect->top, lpRect->bottom);
	else
		Logf("\n");
	return original::ClipCursor(lpRect);
}

HWND WINAPI CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
	Logf("[i76.exe | user32.dll | CreateWindowExA] classname:'%s', window name:'%s', width:%d, height:%d\n", lpClassName, lpWindowName, nWidth, nHeight);
	return original::CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
#if LOG_VERBOSE
	Logf("[i76.exe | user32.dll | DefWindowProcA] msg:");
	PrintMsg(Msg);
	Logf("\n");
#endif
	return original::DefWindowProcA(hWnd, Msg, wParam, lParam);
}

BOOL WINAPI DestroyWindow(HWND hWnd) {
	Logf("[i76.exe | user32.dll | DestroyWindow]\n");
	return original::DestroyWindow(hWnd);
}

LRESULT WINAPI DispatchMessageA(CONST MSG *lpMsg) {
#if LOG_VERBOSE
	Logf("[i76.exe | user32.dll | DispatchMessageA]\n");
#endif
	return original::DispatchMessageA(lpMsg);
}

BOOL WINAPI EndPaint(HWND hWnd, CONST PAINTSTRUCT *lpPaint) {
	Logf("[i76.exe | user32.dll | EndPaint]\n");
	return original::EndPaint(hWnd, lpPaint);
}

HWND WINAPI FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {
	Logf("[i76.exe | user32.dll | FindWindowA] classname:'%s', window name:'%s'\n", lpClassName, lpWindowName);
	return original::FindWindowA(lpClassName, lpWindowName);
}

SHORT WINAPI GetAsyncKeyState(int vKey) {
	Logf("[i76.exe | user32.dll | GetAsyncKeyState] key:%d\n", vKey);
	return original::GetAsyncKeyState(vKey);
}

BOOL WINAPI GetClientRect(HWND hWnd, LPRECT lpRect) {
	Logf("[i76.exe | user32.dll | GetClientRect]\n");
	return original::GetClientRect(hWnd, lpRect);
}

BOOL WINAPI GetCursorPos(LPPOINT lpPoint) {
	Logf("[i76.exe | user32.dll | GetCursorPos]\n");
	return original::GetCursorPos(lpPoint);
}

HDC WINAPI GetDC(HWND hWnd) {
	Logf("[i76.exe | user32.dll | GetDC]\n");
	return original::GetDC(hWnd);
}

HWND WINAPI GetFocus(VOID) {
#if LOG_VERBOSE
	Logf("[i76.exe | user32.dll | GetFocus]\n");
#endif
	return original::GetFocus();
}

int WINAPI GetKeyboardType(int nTypeFlag) {
	Logf("[i76.exe | user32.dll | GetKeyboardType]\n");
	return original::GetKeyboardType(nTypeFlag);
}

SHORT WINAPI GetKeyState(int nVirtKey) {
	Logf("[i76.exe | user32.dll | GetKeyState] key:%d\n", nVirtKey);
	return original::GetKeyState(nVirtKey);
}

int WINAPI GetSystemMetrics(int nIndex) {
	Logf("[i76.exe | user32.dll | GetSystemMetrics] nIndex:%d\n", nIndex);
#if FORCE_1024_RESOLUTION
	if (nIndex == SM_CXSCREEN)
		return 1024;
	else if (nIndex == SM_CYSCREEN)
		return 768;
#endif
	return original::GetSystemMetrics(nIndex);
}

BOOL WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect) {
	Logf("[i76.exe | user32.dll | GetWindowRect]\n");
	return original::GetWindowRect(hWnd, lpRect);
}

HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) {
	Logf("[i76.exe | user32.dll | LoadCursorA]\n");
	return original::LoadCursorA(hInstance, lpCursorName);
}

UINT WINAPI MapVirtualKeyA(UINT uCode, UINT uMapType) {
	Logf("[i76.exe | user32.dll | MapVirtualKeyA]\n");
	return original::MapVirtualKeyA(uCode, uMapType);
}

int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	Logf("[i76.exe | user32.dll | MessageBoxA] text:'%s' caption:'%s'\n", lpText, lpCaption);
	return original::MessageBoxA(hWnd, lpText, lpCaption, uType);
}

BOOL WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
#if LOG_VERBOSE
	Logf("[i76.exe | user32.dll | PeekMessageA]\n");
#endif
	return original::PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

static LRESULT __stdcall WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
#if LOG_WINPROC
	Logf("   WNDPROC msg:");
	PrintMsg(uMsg);
	Logf("\n");
#endif
	return original::windowProc(hWnd, uMsg, wParam, lParam);
}

ATOM WINAPI RegisterClassA(CONST WNDCLASSA *lpWndClass) {
	original::windowProc = lpWndClass->lpfnWndProc;
	((WNDCLASSA *)lpWndClass)->lpfnWndProc = WindowProc;
	Logf("[i76.exe | user32.dll | RegisterClassA] name:%s\n", lpWndClass->lpszClassName);
	return original::RegisterClassA(lpWndClass);
}

int WINAPI ReleaseDC(HWND hWnd, HDC hDC) {
	Logf("[i76.exe | user32.dll | ReleaseDC]\n");
	return original::ReleaseDC(hWnd, hDC);
}

BOOL WINAPI ScreenToClient(HWND hWnd, LPPOINT lpPoint) {
	Logf("[i76.exe | user32.dll | ScreenToClient] x:%d, y:%d\n", lpPoint->x, lpPoint->y);
	return original::ScreenToClient(hWnd, lpPoint);
}

LRESULT WINAPI SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	Logf("[i76.exe | user32.dll | SendMessageA]\n");
	return original::SendMessageA(hWnd, Msg, wParam, lParam);
}

HCURSOR WINAPI SetCursor(HCURSOR hCursor) {
	Logf("[i76.exe | user32.dll | SetCursor]\n");
	return original::SetCursor(hCursor);
}

BOOL WINAPI SetCursorPos(int X, int Y) {
	Logf("[i76.exe | user32.dll | SetCursorPos] x:%d, y:%d\n", X, Y);
	return original::SetCursorPos(X, Y);
}

HWND WINAPI SetFocus(HWND hWnd) {
	Logf("[i76.exe | user32.dll | SetFocus]\n");
	return original::SetFocus(hWnd);
}

BOOL WINAPI SetMenu(HWND hWnd, HMENU hMenu) {
	Logf("[i76.exe | user32.dll | SetMenu]\n");
	return original::SetMenu(hWnd, hMenu);
}

BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight,int yBottom) {
	Logf("[i76.exe | user32.dll | SetRect]\n");
	return original::SetRect(lprc, xLeft, yTop, xRight, yBottom);
}

LONG WINAPI SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong) {
	Logf("[i76.exe | user32.dll | SetWindowLongA]\n");
	return original::SetWindowLongA(hWnd, nIndex, dwNewLong);
}

BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
	Logf("[i76.exe | user32.dll | SetWindowPos]\n");
	return original::SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

int WINAPI ShowCursor(BOOL bShow) {
	Logf("[i76.exe | user32.dll | ShowCursor] value:%s\n", bShow ? "true" : "false");
	return original::ShowCursor(bShow);
}

BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) {
	Logf("[i76.exe | user32.dll | ShowWindow]\n");
	return original::ShowWindow(hWnd, nCmdShow);
}

BOOL WINAPI TranslateMessage(CONST MSG *lpMsg) {
#if LOG_VERBOSE
	Logf("[i76.exe | user32.dll | TranslateMessage]\n");
#endif
	return original::TranslateMessage(lpMsg);
}

BOOL WINAPI UpdateWindow(HWND hWnd) {
	Logf("[i76.exe | user32.dll | UpdateWindow]\n");
	return original::UpdateWindow(hWnd);
}

BOOL WINAPI ValidateRect(HWND hWnd, CONST RECT *lpRect) {
	Logf("[i76.exe | user32.dll | ValidateRect]\n");
	return original::ValidateRect(hWnd, lpRect);
}

int WINAPIV wsprintfA(LPSTR arg1, LPCSTR arg2, ...) {
	Logf("[i76.exe | user32.dll | wsprintfA]\n");
	return 0;
}

int WINAPI wvsprintfA(LPSTR arg1, LPCSTR arg2, va_list arglist) {
	Logf("[i76.exe | user32.dll | wvsprintfA]\n");
	return original::wvsprintfA(arg1, arg2, arglist);
}

// win32.dll

MCIERROR WINAPI mciSendCommandA(MCIDEVICEID mciId, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
	Logf("[i76.exe | win32.dll | mciSendCommandA]\n");
	return original::mciSendCommandA(mciId, uMsg, dwParam1, dwParam2);
}

} // namespace wrap

static WrappedFunc s_wrappedFuncs[] = {
	WRAPPED_FUNC(advapi32.dll, RegOpenKeyExA),
	WRAPPED_FUNC(advapi32.dll, RegCloseKey),
	WRAPPED_FUNC(advapi32.dll, RegQueryValueExA),
	WRAPPED_FUNC(advapi32.dll, RegCreateKeyExA),
	WRAPPED_FUNC(advapi32.dll, RegSetValueExA),
	WRAPPED_FUNC(ddraw.dll, DirectDrawCreate),
	WRAPPED_FUNC(ddraw.dll, DirectDrawEnumerateA),
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
	WRAPPED_FUNC(win32.dll, mciSendCommandA)
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
	data::numDisplayModes = (uint32_t *)(0x006080D8);
	data::displayModes = (data::DisplayMode	 *)(0x006080E0);
	MemoryCallEntryPoint(module);
	return true;
}

} // namespace i76
