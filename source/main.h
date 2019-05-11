#pragma once
#include <vector>
#include <stdint.h>
#include "MemoryModule.h"

#define DDRAW_DLL "ddraw.dll"
#define I76_EXE "i76.exe"
#define I76SHELL_DLL "i76shell.dll"
#define ZGLIDE_DLL "zglide.dll"

#define LOG_IMPORTS 0
#define LOG_VERBOSE 0
#define LOG_ZGLIDE_VERBOSE 0
#define LOG_WINPROC 0
//#define FUNCTION_LOG_FILTER_MODULE ZGLIDE_DLL
#define WRAP_DDRAW 0
#define WRAP_ZGLIDE 1
#define FORCE_WINDOWED 0
#define DDRAW_DUMP_SURFACES 0

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
bool LogFunctionf(const char *_parentModule, const char *_module, const char *_function, const char *_argsFormat = nullptr, ...);
const char *MsgToString(uint32_t _msg);

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
