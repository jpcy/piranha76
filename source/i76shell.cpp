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
	WRAPPED_FUNC(gdi32.dll, StretchBlt)
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
