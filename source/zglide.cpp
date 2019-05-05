#include <stdio.h>
#include <bx/bx.h>
#include <bx/string.h>
#include "MemoryModule.h"
#include "main.h"
#include "zglide.h"

/*
loaded by i76.exe at 0x00426900
*/

namespace zglide {
namespace original {

// exports

int (*CheckFunc)(void *hwConfig); // GrHwConfiguration
int (*FirstDevice)(int *_arg1);
int (*GetFuncDesc)(char *_arg1, int *_arg2, int arg3);
void (*GetNumDevice)();
int (*GetSocketCaps)();
int (*LastDevice)();
int (*LockDisplay)(int *_arg1);
void (*LostDeviceDisplay)();
void (*PreloadTexture)();
void (*RefreshDisplay)();
void (*Render)();
void (*RenderNoClip)();
void (*RenderRefresh)();
void (*RestoreDevice)();
void (*SetLumaTable)();
int (*SetState)(int _arg1, int _arg2);
void (*SetTexturePalette)();
int (*UnlockDisplay)();
void (*UpdateTexture)();

} // namespace original

namespace wrap {

// exports

// just wraps grSstQueryBoards
// returns 1 on success (number of graphics subsystems)
int CheckFunc(void *hwConfig) {
	Logf("[" ZGLIDE_DLL " | export | CheckFunc]\n");
	int result = original::CheckFunc(hwConfig);
	Logf("   %d\n", result);
	return result;
}

// _args1[1] is bpp, seems to always be 8?
// _args1[2] is 768, must be bitmask
//     if & 1, use GR_DEPTHBUFFER_WBUFFER
//     if & 2, use fog
//     if & 256, use GR_TEXFMT_ARGB_1555 instead of GR_TEXFMT_RGB_565
// _args1[5] is the fog color
// _args1[15] is 640
// _args1[16] is 480
// returns 0 on success
int FirstDevice(int *_arg1) {
	Logf("[" ZGLIDE_DLL " | export | FirstDevice]\n");
	/*int copy[28];
	memset(copy, 0, 28 * 4);
	copy[1] = 16;
	copy[2] = 0;
	copy[5] = 0;
	copy[15] = 640;
	copy[16] = 480;*/
	int result = original::FirstDevice(_arg1);
	Logf("   %d\n", result);
	return result;
}

// always returns 0
int GetFuncDesc(char *_arg1, int *_arg2, int _arg3) {
	// _arg3 is always 0
	Logf("[" ZGLIDE_DLL " | export | GetFuncDesc]\n");
	return original::GetFuncDesc(_arg1, _arg2, _arg3);
	// _arg1 will be RASTER
	// _arg2 should be 0, 1 or 2
}

void GetNumDevice() {
	Logf("[" ZGLIDE_DLL " | export | GetNumDevice]\n");
}

// & 1 - use wbuffer
// & 2 - use fog
// see FirstDevice
int GetSocketCaps() {
	Logf("[" ZGLIDE_DLL " | export | GetSocketCaps]\n");
	return original::GetSocketCaps();
}

int LastDevice() {
	Logf("[" ZGLIDE_DLL " | export | LastDevice]\n");
	int result =  original::LastDevice();
	Logf("   %d\n", result);
	return result;
}

int LockDisplay(int *_arg1) {
	Logf("[" ZGLIDE_DLL " | export | LockDisplay] %d\n", *_arg1);
	int result = original::LockDisplay(_arg1);
	Logf("   %d\n", result);
	return result;
}

void LostDeviceDisplay() {
	Logf("[" ZGLIDE_DLL " | export | LostDeviceDisplay]\n");
}

void PreloadTexture() {
	Logf("[" ZGLIDE_DLL " | export | PreloadTexture]\n");
}

void RefreshDisplay() {
	Logf("[" ZGLIDE_DLL " | export | RefreshDisplay]\n");
}

void Render() {
	Logf("[" ZGLIDE_DLL " | export | Render]\n");
}

void RenderNoClip() {
	Logf("[" ZGLIDE_DLL " | export | RenderNoClip]\n");
}

void RenderRefresh() {
	Logf("[" ZGLIDE_DLL " | export | RenderRefresh]\n");
}

void RestoreDevice() {
	Logf("[" ZGLIDE_DLL " | export | RestoreDevice]\n");
}

void SetLumaTable() {
	Logf("[" ZGLIDE_DLL " | export | SetLumaTable]\n");
}

// always returns 0
int SetState(int _arg1, int _arg2) {
	Logf("[" ZGLIDE_DLL " | export | SetState] %d %d\n", _arg1, _arg2);
	return original::SetState(_arg1, _arg2);
}

void SetTexturePalette() {
	Logf("[" ZGLIDE_DLL " | export | SetTexturePalette]\n");
}

// just wraps grLfbUnlock
int UnlockDisplay() {
	Logf("[" ZGLIDE_DLL " | export | UnlockDisplay]\n");
	int result = original::UnlockDisplay();
	Logf("   %d\n", result);
	return result;
}

void UpdateTexture() {
	Logf("[" ZGLIDE_DLL " | export | UpdateTexture]\n");
}

} // namespace wrap

static WrappedFunc s_wrappedExports[] = {
	WRAPPED_FUNC("zglide.dll", CheckFunc),
	WRAPPED_FUNC("zglide.dll", FirstDevice),
	WRAPPED_FUNC("zglide.dll", GetFuncDesc),
	WRAPPED_FUNC("zglide.dll", GetNumDevice),
	WRAPPED_FUNC("zglide.dll", GetSocketCaps),
	WRAPPED_FUNC("zglide.dll", LastDevice),
	WRAPPED_FUNC("zglide.dll", LockDisplay),
	WRAPPED_FUNC("zglide.dll", LostDeviceDisplay),
	WRAPPED_FUNC("zglide.dll", PreloadTexture),
	WRAPPED_FUNC("zglide.dll", RefreshDisplay),
	WRAPPED_FUNC("zglide.dll", Render),
	WRAPPED_FUNC("zglide.dll", RenderNoClip),
	WRAPPED_FUNC("zglide.dll", RenderRefresh),
	WRAPPED_FUNC("zglide.dll", RestoreDevice),
	WRAPPED_FUNC("zglide.dll", SetLumaTable),
	WRAPPED_FUNC("zglide.dll", SetState),
	WRAPPED_FUNC("zglide.dll", SetTexturePalette),
	WRAPPED_FUNC("zglide.dll", UnlockDisplay),
	WRAPPED_FUNC("zglide.dll", UpdateTexture)
};

static MemoryModuleUserData s_memoryModuleUserData;
static HMEMORYMODULE s_memoryModule;

HMODULE Load() {
	FILE *f;
	if (fopen_s(&f, ZGLIDE_DLL, "rb") != 0) {
		fprintf(stderr, "Error opening %s\n", ZGLIDE_DLL);
		return nullptr;
	}
	fseek(f, 0, SEEK_END);
	auto fileLength = (size_t)ftell(f);
	fseek(f, 0, SEEK_SET);
	auto fileData = new uint8_t[fileLength];
	if (fread(fileData, 1, fileLength, f) != fileLength) {
		delete [] fileData;
		fprintf(stderr, "Error reading %s\n", ZGLIDE_DLL);
		return nullptr;
	}
	fclose(f);
	s_memoryModule = CustomMemoryLoadLibrary(fileData, fileLength, &s_memoryModuleUserData);
	if (!s_memoryModule) {
		fprintf(stderr, "MemoryLoadLibraryEx failed for %s\n", ZGLIDE_DLL);
		return nullptr;
	}
	Logf("Loaded %s\n", ZGLIDE_DLL);
	return (HMODULE)s_memoryModule;
}

bool IsModule(HMODULE _module) {
	return (HMEMORYMODULE)_module == s_memoryModule;
}

FARPROC GetProcAddress(const char *_name) {
	Logf("%s: GetProcAddress %s\n", ZGLIDE_DLL, _name);
	FARPROC result = MemoryGetProcAddress(s_memoryModule, _name);
	for (uint32_t i = 0; i < BX_COUNTOF(s_wrappedExports); i++) {
		WrappedFunc &wrap = s_wrappedExports[i];
		if (bx::strCmpI(_name, wrap.symbol) == 0) {
			*wrap.original = result;
			result = (FARPROC)wrap.wrap;
			break;
		}
	}
	return result;
}

} // namespace zglide
