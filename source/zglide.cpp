#include "pch.h"
#include "MemoryModule.h"
#include "main.h"
#include "zglide.h"

/*
loaded by i76.exe at 0x00426900
*/

#define ZGLIDE_LOG(_function, ...) LogFunctionf(I76_EXE, ZGLIDE_DLL, _function, __VA_ARGS__)

namespace zglide {
namespace original {

// exports

int (*CheckFunc)(void *hwConfig); // GrHwConfiguration
int (*FirstDevice)(int *_arg1);
int (*GetFuncDesc)(char *_arg1, int *_arg2, int arg3);
int (*GetNumDevice)();
int (*GetSocketCaps)();
int (*LastDevice)();
int (*LockDisplay)(int *_arg1);
int (*LostDeviceDisplay)();
int (*PreloadTexture)(void **_arg1, int _arg2);
int (*RefreshDisplay)();
int (*Render)(int _arg1, int _arg2, int _arg3, int _arg4, int _arg5);
int (*RenderNoClip)(int _arg1, int _arg2, int _arg3, int _arg4, int _arg5);
int (*RenderRefresh)();
int (*RestoreDevice)();
void (*SetLumaTable)();
int (*SetState)(int _arg1, int _arg2);
int (*SetTexturePalette)();
int (*UnlockDisplay)();
int (*UpdateTexture)(void **_arg1, int _arg2);

} // namespace original

namespace wrap {

// exports

// just wraps grSstQueryBoards
// returns 1 on success (number of graphics subsystems)
int CheckFunc(void *hwConfig) {
	ZGLIDE_LOG("CheckFunc");
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
	ZGLIDE_LOG("FirstDevice");
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
	ZGLIDE_LOG("GetFuncDesc");
	return original::GetFuncDesc(_arg1, _arg2, _arg3);
	// _arg1 will be RASTER
	// _arg2 should be 0, 1 or 2
}

// simply returns 1
int GetNumDevice() {
	ZGLIDE_LOG("GetNumDevice");
	return 1;
}

// & 1 - use wbuffer
// & 2 - use fog
// see FirstDevice
int GetSocketCaps() {
	ZGLIDE_LOG("GetSocketCaps");
	return original::GetSocketCaps();
}

int LastDevice() {
	ZGLIDE_LOG("LastDevice");
	int result =  original::LastDevice();
	Logf("   %d\n", result);
	return result;
}

int LockDisplay(int *_arg1) {
	ZGLIDE_LOG("LockDisplay", "%d", *_arg1);
	int result = original::LockDisplay(_arg1);
	Logf("   %d\n", result);
	return result;
}

// always returns 0
int LostDeviceDisplay() {
	ZGLIDE_LOG("LostDeviceDisplay");
	return original::LostDeviceDisplay();
}

int PreloadTexture(void **_arg1, int _arg2) {
	ZGLIDE_LOG("PreloadTexture", "arg2:%d", _arg2);
	return original::PreloadTexture(_arg1, _arg2);
}

int RefreshDisplay() {
	ZGLIDE_LOG("RefreshDisplay");
	int result = original::RefreshDisplay();
	Logf("   %d\n", result);
	return result;
}

int Render(int _arg1, int _arg2, int _arg3, int _arg4, int _arg5) {
#if LOG_ZGLIDE_VERBOSE
	ZGLIDE_LOG("Render");
#endif
	return original::Render(_arg1, _arg2, _arg3, _arg4, _arg5);
}

int RenderNoClip(int _arg1, int _arg2, int _arg3, int _arg4, int _arg5) {
	ZGLIDE_LOG("RenderNoClip");
	return original::RenderNoClip(_arg1, _arg2, _arg3, _arg4, _arg5);
}

// just increments a counter
// always returns 0
int RenderRefresh() {
	ZGLIDE_LOG("RenderRefresh");
	return original::RenderRefresh();
}

int RestoreDevice() {
	ZGLIDE_LOG("RestoreDevice");
	return original::RestoreDevice();
}

void SetLumaTable() {
	ZGLIDE_LOG("SetLumaTable");
	original::SetLumaTable();
}

// always returns 0
int SetState(int _arg1, int _arg2) {
	ZGLIDE_LOG("SetState", "%d %d\n", _arg1, _arg2);
	return original::SetState(_arg1, _arg2);
}

// simply returns 0
int SetTexturePalette() {
	ZGLIDE_LOG("SetTexturePalette");
	return 0;
}

// just wraps grLfbUnlock
int UnlockDisplay() {
	ZGLIDE_LOG("UnlockDisplay");
	int result = original::UnlockDisplay();
	Logf("   %d\n", result);
	return result;
}

int UpdateTexture(void **_arg1, int _arg2) {
	ZGLIDE_LOG("UpdateTexture", "arg2:%d", _arg2);
	return original::UpdateTexture(_arg1, _arg2);
}

} // namespace wrap

static WrappedFunc s_wrappedExports[] = {
	WRAPPED_FUNC(ZGLIDE_DLL, CheckFunc),
	WRAPPED_FUNC(ZGLIDE_DLL, FirstDevice),
	WRAPPED_FUNC(ZGLIDE_DLL, GetFuncDesc),
	WRAPPED_FUNC(ZGLIDE_DLL, GetNumDevice),
	WRAPPED_FUNC(ZGLIDE_DLL, GetSocketCaps),
	WRAPPED_FUNC(ZGLIDE_DLL, LastDevice),
	WRAPPED_FUNC(ZGLIDE_DLL, LockDisplay),
	WRAPPED_FUNC(ZGLIDE_DLL, LostDeviceDisplay),
	WRAPPED_FUNC(ZGLIDE_DLL, PreloadTexture),
	WRAPPED_FUNC(ZGLIDE_DLL, RefreshDisplay),
	WRAPPED_FUNC(ZGLIDE_DLL, Render),
	WRAPPED_FUNC(ZGLIDE_DLL, RenderNoClip),
	WRAPPED_FUNC(ZGLIDE_DLL, RenderRefresh),
	WRAPPED_FUNC(ZGLIDE_DLL, RestoreDevice),
	WRAPPED_FUNC(ZGLIDE_DLL, SetLumaTable),
	WRAPPED_FUNC(ZGLIDE_DLL, SetState),
	WRAPPED_FUNC(ZGLIDE_DLL, SetTexturePalette),
	WRAPPED_FUNC(ZGLIDE_DLL, UnlockDisplay),
	WRAPPED_FUNC(ZGLIDE_DLL, UpdateTexture)
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
