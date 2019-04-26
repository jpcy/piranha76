#include <vector>
#include <stdio.h>
#include <bx/bx.h>
#include <bx/os.h>
#include "MemoryModule.h"
#include <ddraw.h>

#define LOG_IMPORTS 0
#define LOG_VERBOSE 0
#define FORCE_ENUM_DISPLAY_MODE_16BPP 0
#define FORCE_1024_RESOLUTION 1
#define FORCE_WINDOWED 1

struct MsgName
{
	UINT id;
	const char *name;
};

#define MSG_NAME(id) { id, #id }

static MsgName s_msgNames[] = {
	MSG_NAME(WM_NULL),
	MSG_NAME(WM_CREATE),
	MSG_NAME(WM_DESTROY),
	MSG_NAME(WM_MOVE),
	MSG_NAME(WM_SIZE),
	MSG_NAME(WM_ACTIVATE),
	MSG_NAME(WM_SETFOCUS),
	MSG_NAME(WM_KILLFOCUS),
	MSG_NAME(WM_ENABLE),
	MSG_NAME(WM_SETREDRAW),
	MSG_NAME(WM_SETTEXT),
	MSG_NAME(WM_GETTEXT),
	MSG_NAME(WM_GETTEXTLENGTH),
	MSG_NAME(WM_PAINT),
	MSG_NAME(WM_CLOSE),
	MSG_NAME(WM_QUERYENDSESSION),
	MSG_NAME(WM_QUIT),
	MSG_NAME(WM_QUERYOPEN),
	MSG_NAME(WM_ERASEBKGND),
	MSG_NAME(WM_SYSCOLORCHANGE),
	MSG_NAME(WM_ENDSESSION),
	MSG_NAME(WM_SHOWWINDOW),
	MSG_NAME(WM_WININICHANGE),
	MSG_NAME(WM_DEVMODECHANGE),
	MSG_NAME(WM_ACTIVATEAPP),
	MSG_NAME(WM_FONTCHANGE),
	MSG_NAME(WM_TIMECHANGE),
	MSG_NAME(WM_CANCELMODE),
	MSG_NAME(WM_SETCURSOR),
	MSG_NAME(WM_MOUSEACTIVATE),
	MSG_NAME(WM_CHILDACTIVATE),
	MSG_NAME(WM_QUEUESYNC),
	MSG_NAME(WM_GETMINMAXINFO),
	MSG_NAME(WM_PAINTICON),
	MSG_NAME(WM_ICONERASEBKGND),
	MSG_NAME(WM_NEXTDLGCTL),
	MSG_NAME(WM_SPOOLERSTATUS),
	MSG_NAME(WM_DRAWITEM),
	MSG_NAME(WM_MEASUREITEM),
	MSG_NAME(WM_DELETEITEM),
	MSG_NAME(WM_VKEYTOITEM),
	MSG_NAME(WM_CHARTOITEM),
	MSG_NAME(WM_SETFONT),
	MSG_NAME(WM_GETFONT),
	MSG_NAME(WM_SETHOTKEY),
	MSG_NAME(WM_GETHOTKEY),
	MSG_NAME(WM_QUERYDRAGICON),
	MSG_NAME(WM_COMPAREITEM),
	MSG_NAME(WM_GETOBJECT),
	MSG_NAME(WM_COMPACTING),
	MSG_NAME(WM_COMMNOTIFY),
	MSG_NAME(WM_WINDOWPOSCHANGING),
	MSG_NAME(WM_WINDOWPOSCHANGED),
	MSG_NAME(WM_POWER),
	MSG_NAME(WM_COPYDATA),
	MSG_NAME(WM_CANCELJOURNAL),
	MSG_NAME(WM_NOTIFY),
	MSG_NAME(WM_INPUTLANGCHANGEREQUEST),
	MSG_NAME(WM_INPUTLANGCHANGE),
	MSG_NAME(WM_TCARD),
	MSG_NAME(WM_HELP),
	MSG_NAME(WM_USERCHANGED),
	MSG_NAME(WM_NOTIFYFORMAT),
	MSG_NAME(WM_CONTEXTMENU),
	MSG_NAME(WM_STYLECHANGING),
	MSG_NAME(WM_STYLECHANGED),
	MSG_NAME(WM_DISPLAYCHANGE),
	MSG_NAME(WM_GETICON),
	MSG_NAME(WM_SETICON),
	MSG_NAME(WM_NCCREATE),
	MSG_NAME(WM_NCDESTROY),
	MSG_NAME(WM_NCCALCSIZE),
	MSG_NAME(WM_NCHITTEST),
	MSG_NAME(WM_NCPAINT),
	MSG_NAME(WM_NCACTIVATE),
	MSG_NAME(WM_GETDLGCODE),
	MSG_NAME(WM_SYNCPAINT),
	MSG_NAME(WM_NCMOUSEMOVE),
	MSG_NAME(WM_NCLBUTTONDOWN),
	MSG_NAME(WM_NCLBUTTONUP),
	MSG_NAME(WM_NCLBUTTONDBLCLK),
	MSG_NAME(WM_NCRBUTTONDOWN),
	MSG_NAME(WM_NCRBUTTONUP),
	MSG_NAME(WM_NCRBUTTONDBLCLK),
	MSG_NAME(WM_NCMBUTTONDOWN),
	MSG_NAME(WM_NCMBUTTONUP),
	MSG_NAME(WM_NCMBUTTONDBLCLK),
	MSG_NAME(WM_NCXBUTTONDOWN),
	MSG_NAME(WM_NCXBUTTONUP),
	MSG_NAME(WM_NCXBUTTONDBLCLK),
	MSG_NAME(EM_GETSEL),
	MSG_NAME(EM_SETSEL),
	MSG_NAME(EM_GETRECT),
	MSG_NAME(EM_SETRECT),
	MSG_NAME(EM_SETRECTNP),
	MSG_NAME(EM_SCROLL),
	MSG_NAME(EM_LINESCROLL),
	MSG_NAME(EM_SCROLLCARET),
	MSG_NAME(EM_GETMODIFY),
	MSG_NAME(EM_SETMODIFY),
	MSG_NAME(EM_GETLINECOUNT),
	MSG_NAME(EM_LINEINDEX),
	MSG_NAME(EM_SETHANDLE),
	MSG_NAME(EM_GETHANDLE),
	MSG_NAME(EM_GETTHUMB),
	MSG_NAME(EM_LINELENGTH),
	MSG_NAME(EM_REPLACESEL),
	MSG_NAME(EM_GETLINE),
	MSG_NAME(EM_LIMITTEXT),
	MSG_NAME(EM_SETLIMITTEXT),
	MSG_NAME(EM_CANUNDO),
	MSG_NAME(EM_UNDO),
	MSG_NAME(EM_FMTLINES),
	MSG_NAME(EM_LINEFROMCHAR),
	MSG_NAME(EM_SETTABSTOPS),
	MSG_NAME(EM_SETPASSWORDCHAR),
	MSG_NAME(EM_EMPTYUNDOBUFFER),
	MSG_NAME(EM_GETFIRSTVISIBLELINE),
	MSG_NAME(EM_SETREADONLY),
	MSG_NAME(EM_SETWORDBREAKPROC),
	MSG_NAME(EM_GETWORDBREAKPROC),
	MSG_NAME(EM_GETPASSWORDCHAR),
	MSG_NAME(EM_SETMARGINS),
	MSG_NAME(EM_GETMARGINS),
	MSG_NAME(EM_GETLIMITTEXT),
	MSG_NAME(EM_POSFROMCHAR),
	MSG_NAME(EM_CHARFROMPOS),
	MSG_NAME(EM_SETIMESTATUS),
	MSG_NAME(EM_GETIMESTATUS),
	MSG_NAME(SBM_SETPOS),
	MSG_NAME(SBM_GETPOS),
	MSG_NAME(SBM_SETRANGE),
	MSG_NAME(SBM_GETRANGE),
	MSG_NAME(SBM_ENABLE_ARROWS),
	MSG_NAME(SBM_SETRANGEREDRAW),
	MSG_NAME(SBM_SETSCROLLINFO),
	MSG_NAME(SBM_GETSCROLLINFO),
	MSG_NAME(SBM_GETSCROLLBARINFO),
	MSG_NAME(BM_GETCHECK),
	MSG_NAME(BM_SETCHECK),
	MSG_NAME(BM_GETSTATE),
	MSG_NAME(BM_SETSTATE),
	MSG_NAME(BM_SETSTYLE),
	MSG_NAME(BM_CLICK),
	MSG_NAME(BM_GETIMAGE),
	MSG_NAME(BM_SETIMAGE),
	MSG_NAME(WM_INPUT),
	MSG_NAME(WM_KEYDOWN),
	MSG_NAME(WM_KEYFIRST),
	MSG_NAME(WM_KEYUP),
	MSG_NAME(WM_CHAR),
	MSG_NAME(WM_DEADCHAR),
	MSG_NAME(WM_SYSKEYDOWN),
	MSG_NAME(WM_SYSKEYUP),
	MSG_NAME(WM_SYSCHAR),
	MSG_NAME(WM_SYSDEADCHAR),
	MSG_NAME(WM_KEYLAST),
	MSG_NAME(WM_UNICHAR),
	MSG_NAME(WM_IME_STARTCOMPOSITION),
	MSG_NAME(WM_IME_ENDCOMPOSITION),
	MSG_NAME(WM_IME_COMPOSITION),
	MSG_NAME(WM_IME_KEYLAST),
	MSG_NAME(WM_INITDIALOG),
	MSG_NAME(WM_COMMAND),
	MSG_NAME(WM_SYSCOMMAND),
	MSG_NAME(WM_TIMER),
	MSG_NAME(WM_HSCROLL),
	MSG_NAME(WM_VSCROLL),
	MSG_NAME(WM_INITMENU),
	MSG_NAME(WM_INITMENUPOPUP),
	MSG_NAME(WM_MENUSELECT),
	MSG_NAME(WM_MENUCHAR),
	MSG_NAME(WM_ENTERIDLE),
	MSG_NAME(WM_MENURBUTTONUP),
	MSG_NAME(WM_MENUDRAG),
	MSG_NAME(WM_MENUGETOBJECT),
	MSG_NAME(WM_UNINITMENUPOPUP),
	MSG_NAME(WM_MENUCOMMAND),
	MSG_NAME(WM_CHANGEUISTATE),
	MSG_NAME(WM_UPDATEUISTATE),
	MSG_NAME(WM_QUERYUISTATE),
	MSG_NAME(WM_CTLCOLORMSGBOX),
	MSG_NAME(WM_CTLCOLOREDIT),
	MSG_NAME(WM_CTLCOLORLISTBOX),
	MSG_NAME(WM_CTLCOLORBTN),
	MSG_NAME(WM_CTLCOLORDLG),
	MSG_NAME(WM_CTLCOLORSCROLLBAR),
	MSG_NAME(WM_CTLCOLORSTATIC),
	MSG_NAME(WM_MOUSEFIRST),
	MSG_NAME(WM_MOUSEMOVE),
	MSG_NAME(WM_LBUTTONDOWN),
	MSG_NAME(WM_LBUTTONUP),
	MSG_NAME(WM_LBUTTONDBLCLK),
	MSG_NAME(WM_RBUTTONDOWN),
	MSG_NAME(WM_RBUTTONUP),
	MSG_NAME(WM_RBUTTONDBLCLK),
	MSG_NAME(WM_MBUTTONDOWN),
	MSG_NAME(WM_MBUTTONUP),
	MSG_NAME(WM_MBUTTONDBLCLK),
	MSG_NAME(WM_MOUSELAST),
	MSG_NAME(WM_MOUSEWHEEL),
	MSG_NAME(WM_XBUTTONDOWN),
	MSG_NAME(WM_XBUTTONUP),
	MSG_NAME(WM_XBUTTONDBLCLK),
	MSG_NAME(WM_PARENTNOTIFY),
	MSG_NAME(WM_ENTERMENULOOP),
	MSG_NAME(WM_EXITMENULOOP),
	MSG_NAME(WM_NEXTMENU),
	MSG_NAME(WM_SIZING),
	MSG_NAME(WM_CAPTURECHANGED),
	MSG_NAME(WM_MOVING),
	MSG_NAME(WM_POWERBROADCAST),
	MSG_NAME(WM_DEVICECHANGE),
	MSG_NAME(WM_MDICREATE),
	MSG_NAME(WM_MDIDESTROY),
	MSG_NAME(WM_MDIACTIVATE),
	MSG_NAME(WM_MDIRESTORE),
	MSG_NAME(WM_MDINEXT),
	MSG_NAME(WM_MDIMAXIMIZE),
	MSG_NAME(WM_MDITILE),
	MSG_NAME(WM_MDICASCADE),
	MSG_NAME(WM_MDIICONARRANGE),
	MSG_NAME(WM_MDIGETACTIVE),
	MSG_NAME(WM_MDISETMENU),
	MSG_NAME(WM_ENTERSIZEMOVE),
	MSG_NAME(WM_EXITSIZEMOVE),
	MSG_NAME(WM_DROPFILES),
	MSG_NAME(WM_MDIREFRESHMENU),
	MSG_NAME(WM_IME_SETCONTEXT),
	MSG_NAME(WM_IME_NOTIFY),
	MSG_NAME(WM_IME_CONTROL),
	MSG_NAME(WM_IME_COMPOSITIONFULL),
	MSG_NAME(WM_IME_SELECT),
	MSG_NAME(WM_IME_CHAR),
	MSG_NAME(WM_IME_REQUEST),
	MSG_NAME(WM_IME_KEYDOWN),
	MSG_NAME(WM_IME_KEYUP),
	MSG_NAME(WM_NCMOUSEHOVER),
	MSG_NAME(WM_MOUSEHOVER),
	MSG_NAME(WM_NCMOUSELEAVE),
	MSG_NAME(WM_MOUSELEAVE),
	MSG_NAME(WM_CUT),
	MSG_NAME(WM_COPY),
	MSG_NAME(WM_PASTE),
	MSG_NAME(WM_CLEAR),
	MSG_NAME(WM_UNDO),
	MSG_NAME(WM_RENDERFORMAT),
	MSG_NAME(WM_RENDERALLFORMATS),
	MSG_NAME(WM_DESTROYCLIPBOARD),
	MSG_NAME(WM_DRAWCLIPBOARD),
	MSG_NAME(WM_PAINTCLIPBOARD),
	MSG_NAME(WM_VSCROLLCLIPBOARD),
	MSG_NAME(WM_SIZECLIPBOARD),
	MSG_NAME(WM_ASKCBFORMATNAME),
	MSG_NAME(WM_CHANGECBCHAIN),
	MSG_NAME(WM_HSCROLLCLIPBOARD),
	MSG_NAME(WM_QUERYNEWPALETTE),
	MSG_NAME(WM_PALETTEISCHANGING),
	MSG_NAME(WM_PALETTECHANGED),
	MSG_NAME(WM_HOTKEY),
	MSG_NAME(WM_PRINT),
	MSG_NAME(WM_PRINTCLIENT),
	MSG_NAME(WM_APPCOMMAND),
	MSG_NAME(WM_HANDHELDFIRST),
	MSG_NAME(WM_HANDHELDLAST),
	MSG_NAME(WM_AFXFIRST),
	MSG_NAME(WM_AFXLAST),
	MSG_NAME(WM_PENWINFIRST),
	MSG_NAME(WM_PENWINLAST)
};

static void PrintMsg(UINT msg) {
	for (int i = 0; i < BX_COUNTOF(s_msgNames); i++) {
		if (msg == s_msgNames[i].id) {
			printf("%s", s_msgNames[i].name);
			return;
		}
	}
	printf("%u", msg);
}

#define CHECK_HR_RETURN(func) { HRESULT hr = (func); if (hr) printf("   HRESULT: %u\n", hr); return hr; }

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

void *(*StrLookupCreate)(const char *_filename);

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
	printf("   %ux%u, %u bpp\n", Arg1->dwWidth, Arg1->dwHeight, Arg1->ddpfPixelFormat.dwRGBBitCount);
	if (Arg2)
		printf("      arg2 is not null\n");
#if FORCE_ENUM_DISPLAY_MODE_16BPP
	// i76 only cares about dwWidth, dwHeight, and this
	Arg1->ddpfPixelFormat.dwRGBBitCount = 16;
#endif
	HRESULT hr = original::ddrawEnumDisplayModes(Arg1, Arg2);
	if (hr != DDENUMRET_OK)
		printf("      cancel enumeration\n");
	return hr;
}

struct CustomIDirectDraw
{
	/*** IUnknown methods ***/
	virtual __declspec(nothrow) HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj) {
		printf("[IDirectDraw::QueryInterface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->QueryInterface(riid, ppvObj));
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
		CHECK_HR_RETURN(original::directDrawInterface->Compact());
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreateClipper(DWORD arg1, LPDIRECTDRAWCLIPPER FAR* arg2, IUnknown FAR * arg3) {
		printf("[IDirectDraw::CreateClipper]\n");
		CHECK_HR_RETURN(original::directDrawInterface->CreateClipper(arg1, arg2, arg3));
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreatePalette(DWORD arg1, LPPALETTEENTRY arg2, LPDIRECTDRAWPALETTE FAR* arg3, IUnknown FAR * arg4) {
		printf("[IDirectDraw::CreatePalette]\n");
		CHECK_HR_RETURN(original::directDrawInterface->CreatePalette(arg1, arg2, arg3, arg4));
	}

	virtual __declspec(nothrow) HRESULT __stdcall CreateSurface(LPDDSURFACEDESC2 arg1, LPDIRECTDRAWSURFACE7 FAR *arg2, IUnknown FAR *arg3) {
		printf("[IDirectDraw::CreateSurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->CreateSurface(arg1, arg2, arg3));
	}

	virtual __declspec(nothrow) HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE7 arg1, LPDIRECTDRAWSURFACE7 FAR * arg2) {
		printf("[IDirectDraw::DuplicateSurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->DuplicateSurface(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall EnumDisplayModes(DWORD arg1, LPDDSURFACEDESC2 arg2, LPVOID arg3, LPDDENUMMODESCALLBACK2 arg4) {
		printf("[IDirectDraw::EnumDisplayModes]\n");
		original::ddrawEnumDisplayModes = arg4;
		CHECK_HR_RETURN(original::directDrawInterface->EnumDisplayModes(arg1, arg2, arg3, EnumDisplayModesCallback));
	}

	virtual __declspec(nothrow) HRESULT __stdcall EnumSurfaces(DWORD arg1, LPDDSURFACEDESC2 arg2, LPVOID arg3, LPDDENUMSURFACESCALLBACK7 arg4) {
		printf("[IDirectDraw::EnumSurfaces]\n");
		CHECK_HR_RETURN(original::directDrawInterface->EnumSurfaces(arg1, arg2, arg3, arg4));
	}

	virtual __declspec(nothrow) HRESULT __stdcall FlipToGDISurface() {
		printf("[IDirectDraw::FlipToGDISurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->FlipToGDISurface());
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetCaps(LPDDCAPS arg1, LPDDCAPS arg2) {
		printf("[IDirectDraw::GetCaps]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetCaps(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC2 arg1) {
		printf("[IDirectDraw::GetDisplayMode]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetDisplayMode(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetFourCCCodes(LPDWORD arg1, LPDWORD arg2) {
		printf("[IDirectDraw::GetFourCCCodes]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetFourCCCodes(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE7 FAR *arg1) {
		printf("[IDirectDraw::GetGDISurface]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetGDISurface(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetMonitorFrequency(LPDWORD arg1) {
		printf("[IDirectDraw::GetMonitorFrequency]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetMonitorFrequency(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetScanLine(LPDWORD arg1) {
		printf("[IDirectDraw::GetScanLine]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetScanLine(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetVerticalBlankStatus(LPBOOL arg1) {
		printf("[IDirectDraw::GetVerticalBlankStatus]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetVerticalBlankStatus(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall Initialize(GUID FAR *arg1) {
		printf("[IDirectDraw::Initialize]\n");
		CHECK_HR_RETURN(original::directDrawInterface->Initialize(arg1));
	}

	virtual __declspec(nothrow) HRESULT __stdcall RestoreDisplayMode() {
		printf("[IDirectDraw::RestoreDisplayMode]\n");
		CHECK_HR_RETURN(original::directDrawInterface->RestoreDisplayMode());
	}

	virtual __declspec(nothrow) HRESULT __stdcall SetCooperativeLevel(HWND arg1, DWORD arg2) {
		// 17 = DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE
		printf("[IDirectDraw::SetCooperativeLevel value:%u]\n", arg2);
#if FORCE_WINDOWED
		CHECK_HR_RETURN(original::directDrawInterface->SetCooperativeLevel(arg1, DDSCL_NORMAL));
#else
		CHECK_HR_RETURN(original::directDrawInterface->SetCooperativeLevel(arg1, arg2));
#endif
	}

	virtual __declspec(nothrow) HRESULT __stdcall SetDisplayMode(DWORD arg1, DWORD arg2, DWORD arg3, DWORD arg4, DWORD arg5) {
		printf("[IDirectDraw::SetDisplayMode]\n");
		CHECK_HR_RETURN(original::directDrawInterface->SetDisplayMode(arg1, arg2, arg3, arg4, arg5));
	}

	virtual __declspec(nothrow) HRESULT __stdcall WaitForVerticalBlank(DWORD arg1, HANDLE arg2) {
		printf("[IDirectDraw::WaitForVerticalBlank]\n");
		CHECK_HR_RETURN(original::directDrawInterface->WaitForVerticalBlank(arg1, arg2));
	}

	/*** Added in the v2 interface ***/
	virtual __declspec(nothrow) HRESULT __stdcall GetAvailableVidMem(LPDDSCAPS2 arg1, LPDWORD arg2, LPDWORD arg3) {
		printf("[IDirectDraw::GetAvailableVidMem]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetAvailableVidMem(arg1, arg2, arg3));
	}

	/*** Added in the V4 Interface ***/
	virtual __declspec(nothrow) HRESULT __stdcall GetSurfaceFromDC(HDC arg1, LPDIRECTDRAWSURFACE7 *arg2) {
		printf("[IDirectDraw::GetSurfaceFromDC]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetSurfaceFromDC(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall RestoreAllSurfaces() {
		printf("[IDirectDraw::RestoreAllSurfaces]\n");
		CHECK_HR_RETURN(original::directDrawInterface->RestoreAllSurfaces());
	}

	virtual __declspec(nothrow) HRESULT __stdcall TestCooperativeLevel() {
		printf("[IDirectDraw::TestCooperativeLevel]\n");
		CHECK_HR_RETURN(original::directDrawInterface->TestCooperativeLevel());
	}

	virtual __declspec(nothrow) HRESULT __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 arg1, DWORD arg2) {
		printf("[IDirectDraw::GetDeviceIdentifier]\n");
		CHECK_HR_RETURN(original::directDrawInterface->GetDeviceIdentifier(arg1, arg2));
	}

	virtual __declspec(nothrow) HRESULT __stdcall StartModeTest(LPSIZE arg1, DWORD arg2, DWORD arg3) {
		printf("[IDirectDraw::StartModeTest]\n");
		CHECK_HR_RETURN(original::directDrawInterface->StartModeTest(arg1, arg2, arg3));
	}

	virtual __declspec(nothrow) HRESULT __stdcall EvaluateMode(DWORD arg1, DWORD * arg2) {
		printf("[IDirectDraw::EvaluateMode]\n");
		CHECK_HR_RETURN(original::directDrawInterface->EvaluateMode(arg1, arg2));
	}
};

static CustomIDirectDraw *directDrawInterface = nullptr;

HRESULT WINAPI DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter) {
	printf("[DirectDrawCreate]\n");
	HRESULT hr = original::DirectDrawCreate((GUID *)DDCREATE_EMULATIONONLY, lplpDD, pUnkOuter);
	if (hr)
		printf("HRESULT: %u\n", hr);
#if 1
	original::directDrawInterface = (LPDIRECTDRAW7)*lplpDD;
	directDrawInterface = new CustomIDirectDraw();
	*lplpDD = (LPDIRECTDRAW)directDrawInterface;
#endif
	return hr;
}

HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext) {
	printf("[DirectDrawEnumerateA]\n");
	CHECK_HR_RETURN(original::DirectDrawEnumerateA(lpCallback, lpContext));
}

// gdi32.dll

int WINAPI AddFontResourceA(LPCSTR Arg1) {
	printf("[AddFontResourceA]\n");
	return original::AddFontResourceA(Arg1);
}

HDC WINAPI CreateCompatibleDC(HDC hdc) {
	printf("[CreateCompatibleDC]\n");
	return original::CreateCompatibleDC(hdc);
}

HBITMAP WINAPI CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset) {
	printf("[CreateDIBSection]\n");
	return original::CreateDIBSection(hdc, pbmi, usage, ppvBits, hSection, offset);
}

HFONT WINAPI CreateFontIndirectA(LOGFONTA *lplf) {
	printf("[CreateFontIndirectA]\n");
	return original::CreateFontIndirectA(lplf);
}

HPALETTE WINAPI CreatePalette(CONST LOGPALETTE * plpal) {
	printf("[CreatePalette]\n");
	return original::CreatePalette(plpal);
}

BOOL WINAPI CreateScalableFontResourceA(DWORD fdwHidden, LPCSTR lpszFont, LPCSTR lpszFile, LPCSTR lpszPath) {
	printf("[CreateScalableFontResourceA]\n");
	return original::CreateScalableFontResourceA(fdwHidden, lpszFont, lpszFile, lpszPath);
}

BOOL WINAPI DeleteDC(HDC hdc) {
	printf("[DeleteDC]\n");
	return original::DeleteDC(hdc);
}

BOOL WINAPI DeleteObject(HGDIOBJ ho) {
	printf("[DeleteObject]\n");
	return original::DeleteObject(ho);
}

int WINAPI GetDeviceCaps(HDC hdc, int index) {
	printf("[GetDeviceCaps]\n");
	return original::GetDeviceCaps(hdc, index);
}

HGDIOBJ WINAPI GetStockObject(int i) {
	printf("[GetStockObject]\n");
	return original::GetStockObject(i);
}

UINT WINAPI GetSystemPaletteEntries(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries) {
	printf("[GetSystemPaletteEntries]\n");
	return original::GetSystemPaletteEntries(hdc, iStart, cEntries, pPalEntries);
}

BOOL APIENTRY GetTextExtentExPointA(HDC hdc, LPCSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize) {
	printf("[GetTextExtentExPointA]\n");
	return original::GetTextExtentExPointA(hdc, lpszString, cchString, nMaxExtent, lpnFit, lpnDx, lpSize);
}

BOOL APIENTRY GetTextExtentPoint32A(HDC hdc, LPCSTR lpString, int c, LPSIZE psizl) {
	printf("[GetTextExtentPoint32A]\n");
	return original::GetTextExtentPoint32A(hdc, lpString, c, psizl);
}

BOOL WINAPI GdiFlush(void) {
	printf("[GdiFlush]\n");
	return original::GdiFlush();
}

UINT WINAPI RealizePalette(HDC hdc) {
	printf("[RealizePalette]\n");
	return original::RealizePalette(hdc);
}

BOOL WINAPI Rectangle(HDC hdc, int left, int top, int right, int bottom) {
	printf("[Rectangle]\n");
	return original::Rectangle(hdc, left, top, right, bottom);
}

BOOL WINAPI RemoveFontResourceA(LPCSTR lpFileName) {
	printf("[RemoveFontResourceA]\n");
	return original::RemoveFontResourceA(lpFileName);
}

HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ h) {
	printf("[SelectObject]\n");
	return original::SelectObject(hdc, h);
}

HPALETTE WINAPI SelectPalette(HDC hdc, HPALETTE hPal, BOOL bForceBkgd) {
	printf("[SelectPalette]\n");
	return original::SelectPalette(hdc, hPal, bForceBkgd);
}

COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color) {
	printf("[SetBkColor]\n");
	return original::SetBkColor(hdc, color);
}

int WINAPI SetBkMode(HDC hdc, int mode) {
	printf("[SetBkMode]\n");
	return original::SetBkMode(hdc, mode);
}

int WINAPI SetDIBitsToDevice(HDC hdc, int xDest, int yDest, DWORD w, DWORD h, int xSrc, int ySrc, UINT StartScan, UINT cLines, CONST VOID * lpvBits, CONST BITMAPINFO * lpbmi, UINT ColorUse) {
	printf("[SetDIBitsToDevice]\n");
	return original::SetDIBitsToDevice(hdc, xDest, yDest, w, h, xSrc, ySrc, StartScan, cLines, lpvBits, lpbmi, ColorUse);
}

DWORD WINAPI SetMapperFlags(HDC hdc, DWORD flags) {
	printf("[SetMapperFlags]\n");
	return original::SetMapperFlags(hdc, flags);
}

UINT WINAPI SetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries, CONST PALETTEENTRY *pPalEntries) {
	printf("[SetPaletteEntries]\n");
	return original::SetPaletteEntries(hpal, iStart, cEntries, pPalEntries);
}

COLORREF WINAPI SetTextColor(HDC hdc, COLORREF color) {
	printf("[SetTextColor]\n");
	return original::SetTextColor(hdc, color);
}

BOOL WINAPI TextOutA(HDC hdc, int x, int y, LPCSTR lpString, int c) {
	printf("[TextOutA]\n");
	return original::TextOutA(hdc, x, y, lpString, c);
}

// kernel32.dll

BOOL WINAPI CloseHandle(HANDLE hObject) {
	printf("[CloseHandle]\n");
	return original::CloseHandle(hObject);
}

BOOL WINAPI CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists) {
	printf("[CopyFileA] from:'%s', to:'%s'\n", lpExistingFileName, lpNewFileName);
	return original::CopyFileA(lpExistingFileName, lpNewFileName, bFailIfExists);
}

HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	printf("[CreateFileA] '%s'\n", lpFileName);
	return original::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName) {
	printf("[CreateFileMappingA] '%s'\n", lpName);
	return original::CreateFileMappingA(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

BOOL WINAPI DeleteFileA(LPCSTR lpFileName) {
	printf("[DeleteFileA] '%s'\n", lpFileName);
	return original::DeleteFileA(lpFileName);
}

BOOL WINAPI FindClose(HANDLE hFindFile) {
	printf("[FindClose]\n");
	return original::FindClose(hFindFile);
}

HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
	printf("[FindFirstFileA] '%s'\n", lpFileName);
	return original::FindFirstFileA(lpFileName, lpFindFileData);
}

BOOL WINAPI FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) {
	printf("[FindNextFileA]\n");
	return original::FindNextFileA(hFindFile, lpFindFileData);
}

BOOL WINAPI FreeLibrary(HMODULE hLibModule) {
	printf("[FreeLibrary]\n");
	return original::FreeLibrary(hLibModule);
}

DWORD WINAPI GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer) {
	printf("[GetCurrentDirectoryA]\n");
	return original::GetCurrentDirectoryA(nBufferLength, lpBuffer);
}

HANDLE WINAPI GetCurrentProcess() {
	printf("[GetCurrentProcess]\n");
	return original::GetCurrentProcess();
}

UINT WINAPI GetDriveTypeA(LPCSTR lpRootPathName) {
	printf("[GetDriveTypeA] root:'%s'\n", lpRootPathName);
	return original::GetDriveTypeA(lpRootPathName);
}

BOOL WINAPI GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime) {
	printf("[GetFileTime]\n");
	return original::GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
}

DWORD WINAPI GetLogicalDrives() {
	printf("[GetLogicalDrives]\n");
	return original::GetLogicalDrives();
}

HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName) {
	printf("[GetModuleHandleA] '%s'\n", lpModuleName);
	return original::GetModuleHandleA(lpModuleName);
}

FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
	printf("[GetProcAddress] proc:'%s'\n", lpProcName);
	return original::GetProcAddress(hModule, lpProcName);
}

HANDLE WINAPI GetProcessHeap() {
	printf("[GetProcessHeap]\n");
	return original::GetProcessHeap();
}

DWORD WINAPI GetTickCount() {
	printf("[GetTickCount]\n");
	return original::GetTickCount();
}

VOID WINAPI GetStartupInfoA(LPSTARTUPINFOA lpStartupInfo) {
	printf("[GetStartupInfoA]\n");
	original::GetStartupInfoA(lpStartupInfo);
}

LCID WINAPI GetSystemDefaultLCID() {
	printf("[GetSystemDefaultLCID]\n");
	return original::GetSystemDefaultLCID();
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

LPVOID WINAPI HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes) {
	printf("[HeapAlloc]\n");
	return original::HeapAlloc(hHeap, dwFlags, dwBytes);
}

SIZE_T WINAPI HeapCompact(HANDLE hHeap, DWORD dwFlags) {
	printf("[HeapCompact]\n");
	return original::HeapCompact(hHeap, dwFlags);
}

HANDLE WINAPI HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) {
	printf("[HeapCreate]\n");
	return original::HeapCreate(flOptions, dwInitialSize, dwMaximumSize);
}

BOOL WINAPI HeapDestroy(HANDLE hHeap) {
	printf("[HeapDestroy]\n");
	return original::HeapDestroy(hHeap);
}

BOOL WINAPI HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
	printf("[HeapFree]\n");
	return original::HeapFree(hHeap, dwFlags, lpMem);
}

LPVOID WINAPI HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes) {
	printf("[HeapReAlloc]\n");
	return original::HeapReAlloc(hHeap, dwFlags, lpMem, dwBytes);
}

SIZE_T WINAPI HeapSize(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) {
	printf("[HeapSize]\n");
	return original::HeapSize(hHeap, dwFlags, lpMem);
}

LPSTR WINAPI lstrcatA(LPSTR lpString1, LPCSTR lpString2) {
	printf("[lstrcatA]\n");
	return original::lstrcatA(lpString1, lpString2);
}

LPSTR WINAPI lstrcpyA(LPSTR lpString1, LPCSTR lpString2) {
	printf("[lstrcpyA]\n");
	return original::lstrcpyA(lpString1, lpString2);
}

HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName) {
	printf("[LoadLibraryA] filename:'%s'\n", lpLibFileName);
	return original::LoadLibraryA(lpLibFileName);
}

LPVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap) {
	printf("[MapViewOfFile]\n");
	return original::MapViewOfFile(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
}

VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString) {
	printf("[OutputDebugStringA] '%s'\n", lpOutputString);
	original::OutputDebugStringA(lpOutputString);
}

BOOL WINAPI SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes) {
	printf("[SetFileAttributesA] filename:'%s'\n", lpFileName);
	return original::SetFileAttributesA(lpFileName, dwFileAttributes);
}

BOOL WINAPI SetPriorityClass(HANDLE hProcess, DWORD dwPriorityClass) {
	printf("[SetPriorityClass]\n");
	return original::SetPriorityClass(hProcess, dwPriorityClass);
}

BOOL WINAPI UnmapViewOfFile(LPCVOID lpBaseAddress) {
	printf("[UnmapViewOfFile]\n");
	return original::UnmapViewOfFile(lpBaseAddress);
}

LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
	printf("[VirtualAlloc]\n");
	return original::VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL WINAPI VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) {
	printf("[VirtualFree]\n");
	return original::VirtualFree(lpAddress, dwSize, dwFreeType);
}

SIZE_T WINAPI VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	printf("[VirtualQuery]\n");
	return original::VirtualQuery(lpAddress, lpBuffer, dwLength);
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
	printf("[ClipCursor]");
	if (lpRect)
		printf(" left:%d, right:%d, top:%d, bottom:%d\n", lpRect->left, lpRect->right, lpRect->top, lpRect->bottom);
	else
		printf("\n");
	return original::ClipCursor(lpRect);
}

HWND WINAPI CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
	printf("[CreateWindowExA] classname:'%s', window name:'%s', width:%d, height:%d\n", lpClassName, lpWindowName, nWidth, nHeight);
	return original::CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	printf("[DefWindowProcA] msg:");
	PrintMsg(Msg);
	printf("\n");
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
#if FORCE_1024_RESOLUTION
	if (nIndex == SM_CXSCREEN)
		return 1024;
	else if (nIndex == SM_CYSCREEN)
		return 768;
#endif
	return original::GetSystemMetrics(nIndex);
}

BOOL WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect) {
	printf("[GetWindowRect\n");
	return original::GetWindowRect(hWnd, lpRect);
}

HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) {
	printf("[LoadCursorA]\n");
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
#if LOG_VERBOSE
	printf("[PeekMessageA]\n");
#endif
	return original::PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

static LRESULT __stdcall WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	printf("   WNDPROC msg:");
	PrintMsg(uMsg);
	printf("\n");
	return original::windowProc(hWnd, uMsg, wParam, lParam);
}

ATOM WINAPI RegisterClassA(CONST WNDCLASSA *lpWndClass) {
	original::windowProc = lpWndClass->lpfnWndProc;
	((WNDCLASSA *)lpWndClass)->lpfnWndProc = WindowProc;
	printf("[RegisterClassA] name:%s\n", lpWndClass->lpszClassName);
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
	data::errorMessage = (const char *)(0x005FDB00);
	MemoryCallEntryPoint(module);
	return 0;
}
