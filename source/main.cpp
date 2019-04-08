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

HRESULT (APIENTRY *DirectDrawCreate)(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter);

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

HWND (WINAPI *CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
HWND (WINAPI *FindWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName);
int (WINAPI *GetSystemMetrics)(int nIndex);
int (WINAPI *MessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
BOOL (WINAPI *ShowWindow)(HWND hWnd, int nCmdShow);

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

HRESULT APIENTRY DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter) {
	printf("[DirectDrawCreate]\n");
	return original::DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
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

HWND WINAPI CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
	printf("[CreateWindowExA] classname:'%s', window name:'%s', width:%d, height:%d\n", lpClassName, lpWindowName, nWidth, nHeight);
	return original::CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

HWND WINAPI FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {
	printf("[FindWindowA] classname:'%s', window name:'%s'\n", lpClassName, lpWindowName);
	return original::FindWindowA(lpClassName, lpWindowName);
}

int WINAPI GetSystemMetrics(int nIndex) {
	printf("[GetSystemMetrics] nIndex:%d\n", nIndex);
	if (nIndex == SM_CXSCREEN)
		return 1600;
	else if (nIndex == SM_CYSCREEN)
		return 900;
	return original::GetSystemMetrics(nIndex);
}

int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	printf("[MessageBoxA] text:'%s' caption:'%s'\n", lpText, lpCaption);
	return original::MessageBoxA(hWnd, lpText, lpCaption, uType);
}

BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) {
	printf("[ShowWindow]\n");
	return original::ShowWindow(hWnd, nCmdShow);
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
	WRAPPED_FUNC(gdi32.dll, CreateDIBSection),
	WRAPPED_FUNC(kernel32.dll, GetDriveTypeA),
	WRAPPED_FUNC(kernel32.dll, GetLogicalDrives),
	WRAPPED_FUNC(kernel32.dll, GetVolumeInformationA),
	WRAPPED_FUNC(kernel32.dll, GetSystemInfo),
	WRAPPED_FUNC(kernel32.dll, GlobalMemoryStatus),
	WRAPPED_FUNC(kernel32.dll, LoadLibraryA),
	WRAPPED_FUNC(strlkup.dll, StrLookupCreate),
	WRAPPED_FUNC(user32.dll, CreateWindowExA),
	WRAPPED_FUNC(user32.dll, FindWindowA),
	WRAPPED_FUNC(user32.dll, GetSystemMetrics),
	WRAPPED_FUNC(user32.dll, MessageBoxA),
	WRAPPED_FUNC(user32.dll, ShowWindow),
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
