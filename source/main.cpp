#include <vector>
#include <stdio.h>
#include <bx/bx.h>
#include <bx/os.h>
#include "MemoryModule.h"
#include <ddraw.h>

#define LOG_IMPORTS 0

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

HBITMAP (WINAPI *CreateDIBSection)(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset);

// kernel32.dll

UINT (WINAPI *GetDriveTypeA)(LPCSTR lpRootPathName);
DWORD (WINAPI *GetLogicalDrives)(VOID);
BOOL (WINAPI *GetVolumeInformationA)(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize);
VOID (WINAPI *GetSystemInfo)(LPSYSTEM_INFO lpSystemInfo);
VOID (WINAPI *GlobalMemoryStatus)(LPMEMORYSTATUS lpBuffer);
HMODULE (WINAPI *LoadLibraryA)(LPCSTR);

// strlkup.dll

void *(*StrLookupCreate)(const char *_filename);

// user32.dll

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
	printf("[RegOpenKeyExA] sub key:'%s'\n", lpSubKey);
	LSTATUS status = original::RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	return status;
}

LSTATUS APIENTRY RegCloseKey(HKEY hKey) {
	printf("[RegCloseKey]\n");
	//return original::RegCloseKey(hKey);
	return 0;
}

LSTATUS APIENTRY RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
	printf("[RegQueryValueExA]\n");
	//return original::RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	*lpData = 48;
	return 0;
}

LSTATUS APIENTRY RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition ) {
	printf("[RegCreateKeyExA] sub key:'%s'\n", lpSubKey);
	LSTATUS status = original::RegCreateKeyExA(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
	return 0;
	//return status;
}

LSTATUS APIENTRY RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData) {
	printf("[RegSetValueExA]\n");
	return original::RegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);
}

// ddraw.dll

static HRESULT __stdcall EnumDisplayModesCallback(LPDDSURFACEDESC2 Arg1, LPVOID Arg2) {
	printf("   %ux%u, %u bpp\n", Arg1->dwWidth, Arg1->dwHeight, Arg1->lPitch / Arg1->dwWidth * 8);
	//Arg1->lPitch /= 2;
	return original::ddrawEnumDisplayModes(Arg1, Arg2);
}

struct CustomIDirectDraw
{
	/*** IUnknown methods ***/
	virtual __declspec(nothrow) HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj) {
		printf("[IDirectDraw::QueryInterface]\n");
		return original::directDrawInterface->QueryInterface(riid, ppvObj);
	}

	virtual __declspec(nothrow) ULONG __stdcall AddRef() {
		printf("[IDirectDraw::AddRef]\n");
		return original::directDrawInterface->AddRef();
	}

	virtual __declspec(nothrow) ULONG __stdcall Release() {
		printf("[IDirectDraw::Release]\n");
		return original::directDrawInterface->Release();
	}

	/*** IDirectDraw methods ***/
	virtual __declspec(nothrow) HRESULT __stdcall Compact() {
		printf("[IDirectDraw::Compact]\n");
		return original::directDrawInterface->Compact();
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreateClipper(DWORD arg1, LPDIRECTDRAWCLIPPER FAR* arg2, IUnknown FAR * arg3) {
		printf("[IDirectDraw::CreateClipper]\n");
		return original::directDrawInterface->CreateClipper(arg1, arg2, arg3);
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreatePalette(DWORD arg1, LPPALETTEENTRY arg2, LPDIRECTDRAWPALETTE FAR* arg3, IUnknown FAR * arg4) {
		printf("[IDirectDraw::CreatePalette]\n");
		return original::directDrawInterface->CreatePalette(arg1, arg2, arg3, arg4);
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreateSurface(LPDDSURFACEDESC2 arg1, LPDIRECTDRAWSURFACE7 FAR *arg2, IUnknown FAR *arg3) {
		printf("[IDirectDraw::CreateSurface]\n");
		return original::directDrawInterface->CreateSurface(arg1, arg2, arg3);
	}

	virtual __declspec(nothrow) HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE7 arg1, LPDIRECTDRAWSURFACE7 FAR * arg2) {
		printf("[IDirectDraw::DuplicateSurface]\n");
		return original::directDrawInterface->DuplicateSurface(arg1, arg2);
	}

	virtual __declspec(nothrow) HRESULT __stdcall EnumDisplayModes(DWORD arg1, LPDDSURFACEDESC2 arg2, LPVOID arg3, LPDDENUMMODESCALLBACK2 arg4) {
		printf("[IDirectDraw::EnumDisplayModes]\n");
		original::ddrawEnumDisplayModes = arg4;
		return original::directDrawInterface->EnumDisplayModes(arg1, arg2, arg3, EnumDisplayModesCallback);
	}

	virtual __declspec(nothrow) HRESULT __stdcall EnumSurfaces(DWORD arg1, LPDDSURFACEDESC2 arg2, LPVOID arg3, LPDDENUMSURFACESCALLBACK7 arg4) {
		printf("[IDirectDraw::EnumSurfaces]\n");
		return original::directDrawInterface->EnumSurfaces(arg1, arg2, arg3, arg4);
	}

	virtual __declspec(nothrow) HRESULT __stdcall FlipToGDISurface() {
		printf("[IDirectDraw::FlipToGDISurface]\n");
		return original::directDrawInterface->FlipToGDISurface();
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetCaps(LPDDCAPS arg1, LPDDCAPS arg2) {
		printf("[IDirectDraw::GetCaps]\n");
		return original::directDrawInterface->GetCaps(arg1, arg2);
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC2 arg1) {
		printf("[IDirectDraw::GetDisplayMode]\n");
		return original::directDrawInterface->GetDisplayMode(arg1);
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetFourCCCodes(LPDWORD arg1, LPDWORD arg2) {
		printf("[IDirectDraw::GetFourCCCodes]\n");
		return original::directDrawInterface->GetFourCCCodes(arg1, arg2);
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE7 FAR *arg1) {
		printf("[IDirectDraw::GetGDISurface]\n");
		return original::directDrawInterface->GetGDISurface(arg1);
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetMonitorFrequency(LPDWORD arg1) {
		printf("[IDirectDraw::GetMonitorFrequency]\n");
		return original::directDrawInterface->GetMonitorFrequency(arg1);
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetScanLine(LPDWORD arg1) {
		printf("[IDirectDraw::GetScanLine]\n");
		return original::directDrawInterface->GetScanLine(arg1);
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetVerticalBlankStatus(LPBOOL arg1) {
		printf("[IDirectDraw::GetVerticalBlankStatus]\n");
		return original::directDrawInterface->GetVerticalBlankStatus(arg1);
	}

	virtual __declspec(nothrow) HRESULT __stdcall Initialize(GUID FAR *arg1) {
		printf("[IDirectDraw::Initialize]\n");
		return original::directDrawInterface->Initialize(arg1);
	}

	virtual __declspec(nothrow) HRESULT __stdcall RestoreDisplayMode() {
		printf("[IDirectDraw::RestoreDisplayMode]\n");
		return original::directDrawInterface->RestoreDisplayMode();
	}

	virtual __declspec(nothrow) HRESULT __stdcall SetCooperativeLevel(HWND arg1, DWORD arg2) {
		// 17 = DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE
		printf("[IDirectDraw::SetCooperativeLevel value:%u]\n", arg2);
		return original::directDrawInterface->SetCooperativeLevel(arg1, arg2);
		//return original::directDrawInterface->SetCooperativeLevel(arg1, DDSCL_NORMAL);
	}

	virtual __declspec(nothrow) HRESULT __stdcall SetDisplayMode(DWORD arg1, DWORD arg2, DWORD arg3, DWORD arg4, DWORD arg5) {
		printf("[IDirectDraw::SetDisplayMode]\n");
		return original::directDrawInterface->SetDisplayMode(arg1, arg2, arg3, arg4, arg5);
	}

	virtual __declspec(nothrow) HRESULT __stdcall WaitForVerticalBlank(DWORD arg1, HANDLE arg2) {
		printf("[IDirectDraw::WaitForVerticalBlank]\n");
		return original::directDrawInterface->WaitForVerticalBlank(arg1, arg2);
	}

	/*** Added in the v2 interface ***/
	virtual __declspec(nothrow) HRESULT __stdcall GetAvailableVidMem(LPDDSCAPS2 arg1, LPDWORD arg2, LPDWORD arg3) {
		printf("[IDirectDraw::GetAvailableVidMem]\n");
		return original::directDrawInterface->GetAvailableVidMem(arg1, arg2, arg3);
	}

	/*** Added in the V4 Interface ***/
	virtual __declspec(nothrow) HRESULT __stdcall GetSurfaceFromDC(HDC arg1, LPDIRECTDRAWSURFACE7 *arg2) {
		printf("[IDirectDraw::GetSurfaceFromDC]\n");
		return original::directDrawInterface->GetSurfaceFromDC(arg1, arg2);
	}

	virtual __declspec(nothrow) HRESULT __stdcall RestoreAllSurfaces() {
		printf("[IDirectDraw::RestoreAllSurfaces]\n");
		return original::directDrawInterface->RestoreAllSurfaces();
	}

	virtual __declspec(nothrow) HRESULT __stdcall TestCooperativeLevel() {
		printf("[IDirectDraw::TestCooperativeLevel]\n");
		return original::directDrawInterface->TestCooperativeLevel();
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 arg1, DWORD arg2) {
		printf("[IDirectDraw::GetDeviceIdentifier]\n");
		return original::directDrawInterface->GetDeviceIdentifier(arg1, arg2);
	}

	virtual __declspec(nothrow) HRESULT __stdcall StartModeTest(LPSIZE arg1, DWORD arg2, DWORD arg3) {
		printf("[IDirectDraw::StartModeTest]\n");
		return original::directDrawInterface->StartModeTest(arg1, arg2, arg3);
	}

	virtual __declspec(nothrow) HRESULT __stdcall EvaluateMode(DWORD arg1, DWORD * arg2) {
		printf("[IDirectDraw::EvaluateMode]\n");
		return original::directDrawInterface->EvaluateMode(arg1, arg2);
	}
};

static CustomIDirectDraw *directDrawInterface = nullptr;

HRESULT WINAPI DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter) {
	printf("[DirectDrawCreate]\n");
	HRESULT result = original::DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
	original::directDrawInterface = (LPDIRECTDRAW7)*lplpDD;
	directDrawInterface = new CustomIDirectDraw();
	*lplpDD = (LPDIRECTDRAW)directDrawInterface;
	return result;
}

HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext) {
	printf("[DirectDrawEnumerateA]\n");
	return original::DirectDrawEnumerateA(lpCallback, lpContext);
}

// gdi32.dll

HBITMAP WINAPI CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset) {
	printf("[CreateDIBSection]\n");
	return original::CreateDIBSection(hdc, pbmi, usage, ppvBits, hSection, offset);
}

// kernel32.dll

UINT WINAPI GetDriveTypeA(LPCSTR lpRootPathName) {
	printf("[GetDriveTypeA] root:'%s\n", lpRootPathName);
	return original::GetDriveTypeA(lpRootPathName);
}

DWORD WINAPI GetLogicalDrives(VOID) {
	printf("[GetLogicalDrives]\n");
	return original::GetLogicalDrives();
}

BOOL WINAPI GetVolumeInformationA(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize) {
	printf("[GetVolumeInformationA]\n");
	return original::GetVolumeInformationA(lpRootPathName, lpVolumeNameBuffer, nVolumeNameSize, lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags, lpFileSystemNameBuffer, nFileSystemNameSize);
}

VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo) {
	printf("[GetSystemInfo]\n");
	original::GetSystemInfo(lpSystemInfo);
	// 386, 486 or 586 will result in call to _disable() which throws an exception
	lpSystemInfo->dwProcessorType = 0;
}

VOID WINAPI GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer) {
	printf("[GlobalMemoryStatus]\n");
	original::GlobalMemoryStatus(lpBuffer);
}

HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName) {
	printf("[LoadLibraryA] filename:'%s'\n", lpLibFileName);
	return original::LoadLibraryA(lpLibFileName);
}

// strlkup.dll

void *StrLookupCreate(const char *_filename) {
	printf("[StrLookupCreate] filename:'%s'\n", _filename);
	return original::StrLookupCreate(_filename);
}

// user32.dll

BOOL WINAPI AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu) {
	printf("[AdjustWindowRect]\n");
	return original::AdjustWindowRect(lpRect, dwStyle, bMenu);
}

HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint) {
	printf("[BeginPaint]\n");
	return original::BeginPaint(hWnd, lpPaint);
}

BOOL WINAPI ClientToScreen(HWND hWnd, LPPOINT lpPoint) {
	printf("[ClientToScreen]\n");
	return original::ClientToScreen(hWnd, lpPoint);
}

BOOL WINAPI ClipCursor(CONST RECT *lpRect) {
	printf("[ClipCursor] left:%d, right:%d, top:%d, bottom:%d\n", lpRect->left, lpRect->right, lpRect->top, lpRect->bottom);
	return original::ClipCursor(lpRect);
}

HWND WINAPI CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
	printf("[CreateWindowExA] classname:'%s', window name:'%s', width:%d, height:%d\n", lpClassName, lpWindowName, nWidth, nHeight);
	return original::CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	printf("[DefWindowProcA]\n");
	return original::DefWindowProcA(hWnd, Msg, wParam, lParam);
}

BOOL WINAPI DestroyWindow(HWND hWnd) {
	printf("[DestroyWindow]\n");
	return original::DestroyWindow(hWnd);
}

LRESULT WINAPI DispatchMessageA(CONST MSG *lpMsg) {
	printf("[DispatchMessageA]\n");
	return original::DispatchMessageA(lpMsg);
}

BOOL WINAPI EndPaint(HWND hWnd, CONST PAINTSTRUCT *lpPaint) {
	printf("[EndPaint]\n");
	return original::EndPaint(hWnd, lpPaint);
}

HWND WINAPI FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {
	printf("[FindWindowA] classname:'%s', window name:'%s'\n", lpClassName, lpWindowName);
	return original::FindWindowA(lpClassName, lpWindowName);
}

SHORT WINAPI GetAsyncKeyState(int vKey) {
	printf("[GetAsyncKeyState] key:%d\n", vKey);
	return original::GetAsyncKeyState(vKey);
}

BOOL WINAPI GetClientRect(HWND hWnd, LPRECT lpRect) {
	printf("[GetClientRect]\n");
	return original::GetClientRect(hWnd, lpRect);
}

BOOL WINAPI GetCursorPos(LPPOINT lpPoint) {
	printf("[GetCursorPos]\n");
	return original::GetCursorPos(lpPoint);
}

HDC WINAPI GetDC(HWND hWnd) {
	printf("[GetDC]\n");
	return original::GetDC(hWnd);
}

HWND WINAPI GetFocus(VOID) {
	printf("[GetFocus]\n");
	return original::GetFocus();
}

int WINAPI GetKeyboardType(int nTypeFlag) {
	printf("[GetKeyboardType]\n");
	return original::GetKeyboardType(nTypeFlag);
}

SHORT WINAPI GetKeyState(int nVirtKey) {
	printf("[GetKeyState] key:%d\n", nVirtKey);
	return original::GetKeyState(nVirtKey);
}

int WINAPI GetSystemMetrics(int nIndex) {
	printf("[GetSystemMetrics] nIndex:%d\n", nIndex);
	/*if (nIndex == SM_CXSCREEN)
		return 1600;
	else if (nIndex == SM_CYSCREEN)
		return 900;*/
	return original::GetSystemMetrics(nIndex);
}

BOOL WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect) {
	printf("[GetWindowRect\n");
	return original::GetWindowRect(hWnd, lpRect);
}

HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) {
	printf("[LoadCursorA\n");
	return original::LoadCursorA(hInstance, lpCursorName);
}

UINT WINAPI MapVirtualKeyA(UINT uCode, UINT uMapType) {
	printf("[MapVirtualKeyA]\n");
	return original::MapVirtualKeyA(uCode, uMapType);
}

int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	printf("[MessageBoxA] text:'%s' caption:'%s'\n", lpText, lpCaption);
	return original::MessageBoxA(hWnd, lpText, lpCaption, uType);
}

BOOL WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
	printf("[PeekMessageA]\n");
	return original::PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

ATOM WINAPI RegisterClassA(CONST WNDCLASSA *lpWndClass) {
	printf("[RegisterClassA]\n");
	return original::RegisterClassA(lpWndClass);
}

int WINAPI ReleaseDC(HWND hWnd, HDC hDC) {
	printf("[ReleaseDC]\n");
	return original::ReleaseDC(hWnd, hDC);
}

BOOL WINAPI ScreenToClient(HWND hWnd, LPPOINT lpPoint) {
	printf("[ScreenToClient] x:%d, y:%d\n", lpPoint->x, lpPoint->y);
	return original::ScreenToClient(hWnd, lpPoint);
}

LRESULT WINAPI SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	printf("[SendMessageA]\n");
	return original::SendMessageA(hWnd, Msg, wParam, lParam);
}

HCURSOR WINAPI SetCursor(HCURSOR hCursor) {
	printf("[SetCursor]\n");
	return original::SetCursor(hCursor);
}

BOOL WINAPI SetCursorPos(int X, int Y) {
	printf("[SetCursorPos] x:%d, y:%d\n", X, Y);
	return original::SetCursorPos(X, Y);
}

HWND WINAPI SetFocus(HWND hWnd) {
	printf("[SetFocus]\n");
	return original::SetFocus(hWnd);
}

BOOL WINAPI SetMenu(HWND hWnd, HMENU hMenu) {
	printf("[SetMenu]\n");
	return original::SetMenu(hWnd, hMenu);
}

BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight,int yBottom) {
	printf("[SetRect]\n");
	return original::SetRect(lprc, xLeft, yTop, xRight, yBottom);
}

LONG WINAPI SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong) {
	printf("[SetWindowLongA]\n");
	return original::SetWindowLongA(hWnd, nIndex, dwNewLong);
}

BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
	printf("[SetWindowPos]\n");
	return original::SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

int WINAPI ShowCursor(BOOL bShow) {
	printf("[ShowCursor] value:%s\n", bShow ? "true" : "false");
	return original::ShowCursor(bShow);
}

BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) {
	printf("[ShowWindow]\n");
	return original::ShowWindow(hWnd, nCmdShow);
}

BOOL WINAPI TranslateMessage(CONST MSG *lpMsg) {
	printf("[TranslateMessage]\n");
	return original::TranslateMessage(lpMsg);
}

BOOL WINAPI UpdateWindow(HWND hWnd) {
	printf("[UpdateWindow]\n");
	return original::UpdateWindow(hWnd);
}

BOOL WINAPI ValidateRect(HWND hWnd, CONST RECT *lpRect) {
	printf("[ValidateRect]\n");
	return original::ValidateRect(hWnd, lpRect);
}

int WINAPIV wsprintfA(LPSTR, LPCSTR, ...) {
	printf("[wsprintfA]\n");
	return 0;
}

int WINAPI wvsprintfA(LPSTR, LPCSTR, va_list arglist) {
	printf("[wvsprintfA]\n");
	return 0;
}

// win32.dll

MCIERROR WINAPI mciSendCommandA(MCIDEVICEID mciId, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
	printf("[mciSendCommandA]\n");
	return original::mciSendCommandA(mciId, uMsg, dwParam1, dwParam2);
}

} // namespace wrap

struct WrappedFunc
{
	char *lib;
	char *symbol;
	void *wrap;
	void **original;
};

#define WRAPPED_FUNC(lib, name) { #lib, #name, wrap::##name, (void **)&original::##name }

static WrappedFunc s_wrappedFuncs[] = {
	WRAPPED_FUNC(advapi32.dll, RegOpenKeyExA),
	WRAPPED_FUNC(advapi32.dll, RegCloseKey),
	WRAPPED_FUNC(advapi32.dll, RegQueryValueExA),
	WRAPPED_FUNC(advapi32.dll, RegCreateKeyExA),
	WRAPPED_FUNC(advapi32.dll, RegSetValueExA),
	WRAPPED_FUNC(ddraw.dll, DirectDrawCreate),
	WRAPPED_FUNC(ddraw.dll, DirectDrawEnumerateA),
	WRAPPED_FUNC(gdi32.dll, CreateDIBSection),
	WRAPPED_FUNC(kernel32.dll, GetDriveTypeA),
	WRAPPED_FUNC(kernel32.dll, GetLogicalDrives),
	WRAPPED_FUNC(kernel32.dll, GetVolumeInformationA),
	WRAPPED_FUNC(kernel32.dll, GetSystemInfo),
	WRAPPED_FUNC(kernel32.dll, GlobalMemoryStatus),
	WRAPPED_FUNC(kernel32.dll, LoadLibraryA),
	WRAPPED_FUNC(strlkup.dll, StrLookupCreate),
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

struct Library
{
	char name[256];
	void *handle;
};

static std::vector<Library> s_libraries;

struct Symbol
{
	uint32_t ordinal;
	char name[256];
};

static Symbol s_smackSymbols[] = {
	{ 21, "_SmackNextFrame@4" },
	{ 32, "_SmackWait@4" },
	{ 7, "_SmackBufferSetPalette@4" },
	{ 14, "_SmackOpen@12" },
	{ 5, "_SmackBufferNewPalette@12" },
	{ 17, "_SmackSoundOnOff@8" },
	{ 23, "_SmackToBuffer@28" },
	{ 18, "_SmackClose@4" },
	{ 28, "_SmackToBufferRect@8" },
	{ 25, "_SmackColorRemap@16" },
	{ 19, "_SmackDoFrame@4" },
	{ 3, "_SmackBufferBlit@32" },
	{ 6, "_SmackBufferClose@4" },
	{ 38, "_SmackSoundUseDirectSound@4" },
	{ 2, "_SmackBufferOpen@24" }
};

static HCUSTOMMODULE customLoadLibrary(LPCSTR _filename, void * /*_userData*/) {
#if LOG_IMPORTS
	printf("Load library %s\n", _filename);
#endif
	Library lib;
	bx::strCopy(lib.name, sizeof(lib.name), _filename);
	lib.handle = bx::dlopen(_filename);
	s_libraries.push_back(lib);
	return lib.handle;
}

static FARPROC customGetProcAddress(HCUSTOMMODULE _lib, LPCSTR _proc, void * /*_userData*/) {
	const char *libName = nullptr;
	for (const Library &lib : s_libraries) {
		if (_lib == lib.handle) {
			libName = lib.name;
			break;
		}
	}
	if (bx::strCmpI(libName, "SMACKW32.DLL") == 0) {
		auto ordinal = *((uint32_t *)&_proc);
		for (const Symbol &symbol : s_smackSymbols) {
			if (symbol.ordinal == ordinal) {
				_proc = symbol.name;
				break;
			}
		}
	}
#if LOG_IMPORTS
	printf("   symbol %s", _proc);
#endif
	auto result = (FARPROC)bx::dlsym(_lib, _proc);
	if (!result) {
		fprintf(stderr, "%s: failed to get symbol %s\n", libName, _proc);
		exit(1);
	}
	for (const WrappedFunc wrap : s_wrappedFuncs) {
		if (bx::strCmpI(libName, wrap.lib) == 0 && bx::strCmpI(_proc, wrap.symbol) == 0) {
			*wrap.original = result;
			result = (FARPROC)wrap.wrap;
#if LOG_IMPORTS
			printf(" (wrapped)");
#endif
			break;
		}
	}
#if LOG_IMPORTS
	printf("\n");
#endif
	return result;
}

static void customFreeLibrary(HCUSTOMMODULE _lib, void * /*_userData*/) {
	bx::dlclose(_lib);
}

int main(int /*argc*/, char ** /*argv*/) {
	const char *filename = "i76.exe";
	FILE *f;
	if (fopen_s(&f, filename, "rb") != 0) {
		fprintf(stderr, "Error opening %s\n", filename);
		return 1;
	}
	fseek(f, 0, SEEK_END);
	auto fileLength = (size_t)ftell(f);
	fseek(f, 0, SEEK_SET);
	auto fileData = new uint8_t[fileLength];
	if (fread(fileData, 1, fileLength, f) != fileLength) {
		delete [] fileData;
		fprintf(stderr, "Error reading %s\n", filename);
		return 1;
	}
	fclose(f);
	HMEMORYMODULE module = MemoryLoadLibraryEx(fileData, fileLength, MemoryDefaultAlloc, MemoryDefaultFree, customLoadLibrary, customGetProcAddress, customFreeLibrary, nullptr);
	if (!module) {
		fprintf(stderr, "MemoryLoadLibraryEx failed\n");
		return 1;
	}
	MemoryCallEntryPoint(module);
	return 0;
}
