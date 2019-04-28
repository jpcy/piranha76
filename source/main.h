#pragma once
#include <vector>
#include <stdint.h>

#define LOG_IMPORTS 0
#define LOG_VERBOSE 0
#define LOG_WINPROC 0
#define FORCE_ENUM_DISPLAY_MODE_16BPP 0
#define FORCE_1024_RESOLUTION 1
#define FORCE_WINDOWED 1

template<class T>
struct ArrayView
{
	ArrayView() : data(nullptr), length(0) {}
	ArrayView(T *data, uint32_t length) : data(data), length(length) {}
	T *data;
	uint32_t length;
};

#define CHECK_HR_RETURN(func) { HRESULT hr = (func); if (hr) Logf("   HRESULT: %u\n", hr); return hr; }

void Logf(const char *_format, ...);
void PrintMsg(uint32_t msg);

struct Library
{
	char name[256];
	void *handle;
};

struct OrdinalSymbol
{
	char moduleName[256];
	uint32_t ordinal;
	char name[256];
};

struct WrappedFunc
{
	char *lib;
	char *symbol;
	void *wrap;
	void **original;
};

struct MemoryModuleUserData
{
	std::vector<Library> libraries;
	ArrayView<OrdinalSymbol> ordinalSymbols;
	ArrayView<WrappedFunc> wrappedFuncs;
};

#define WRAPPED_FUNC(lib, name) { #lib, #name, wrap::##name, (void **)&original::##name }

HMEMORYMODULE CustomMemoryLoadLibrary(const void *_fileData, size_t _fileLength, MemoryModuleUserData *_userData);