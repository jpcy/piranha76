#include <vector>
#include <stdio.h>
#include <bx/bx.h>
#include <bx/os.h>
#include "MemoryModule.h"

namespace original {

HMODULE (*LoadLibraryA)(LPCSTR);
int (WINAPI *MessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

} // namespace original

namespace wrap {

HMODULE LoadLibraryA(LPCSTR lpLibFileName) {
	printf("Called LoadLibraryA filename:'%s'\n", lpLibFileName);
	return original::LoadLibraryA(lpLibFileName);
}

int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	printf("Called MessageBoxA text:'%s' caption:'%s'\n", lpText, lpCaption);
	return original::MessageBoxA(hWnd, lpText, lpCaption, uType);
}

} // namespace wrap

struct WrappedFunc
{
	char *lib;
	char *symbol;
	void *wrap;
	void **original;
};

static WrappedFunc s_wrappedFuncs[] = {
	{ "kernel32.dll", "LoadLibraryA", wrap::LoadLibraryA, (void **)&original::LoadLibraryA },
	{ "user32.dll", "MessageBoxA", wrap::MessageBoxA, (void **)&original::MessageBoxA }
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
	printf("Load library %s\n", _filename);
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
	printf("   symbol %s\n", _proc);
	auto result = (FARPROC)bx::dlsym(_lib, _proc);
	if (!result)
		fprintf(stderr, "failed\n");
	for (const WrappedFunc wrap : s_wrappedFuncs) {
		if (bx::strCmpI(libName, wrap.lib) == 0 && bx::strCmpI(_proc, wrap.symbol) == 0) {
			*wrap.original = result;
			result = (FARPROC)wrap.wrap;
			break;
		}
	}
	return result;
}

static void customFreeLibrary(HCUSTOMMODULE _lib, void * /*_userData*/) {
	bx::dlclose(_lib);
}

int main(int /*argc*/, char ** /*argv*/) {
	const char *filename = "i76.exe";
	FILE *f = fopen(filename, "rb");
	if (!f) {
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
