#define CINTERFACE
#include <ddraw.h>
#undef CINTERFACE
#include "main.h"
#include "i76.h"
#include "ddraw.h"

#define DDRAW_LOG(_function, ...) LogFunctionf(I76_EXE, DDRAW_DLL, _function, __VA_ARGS__)

namespace ddraw {
namespace data {

struct DisplayMode
{
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
	uint32_t zero;
};

uint32_t *numDisplayModes;
DisplayMode *displayModes; // length: 50

} // namespace data

namespace original {

LPDDENUMMODESCALLBACK ddrawEnumDisplayModes = nullptr;
LPDIRECTDRAW ddrawContext = nullptr;

HRESULT (WINAPI *DirectDrawCreate)(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter);
HRESULT (WINAPI *DirectDrawEnumerateA)(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext);

} // namespace original

static HRESULT __stdcall EnumDisplayModesCallback(LPDDSURFACEDESC Arg1, LPVOID Arg2) {
	Logf("   %ux%u, %u bpp\n", Arg1->dwWidth, Arg1->dwHeight, Arg1->ddpfPixelFormat.dwRGBBitCount);
	if (Arg2)
		Logf("      arg2 is not null\n");
#if FORCE_ENUM_DISPLAY_MODE_16BPP
	// i76 only cares about dwWidth, dwHeight, and this
	Arg1->ddpfPixelFormat.dwRGBBitCount = 16;
#endif
#if 0
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

HRESULT __stdcall QueryInterface(IDirectDraw FAR * /*_this*/, REFIID riid, LPVOID FAR * ppvObj) {
	DDRAW_LOG("IDirectDraw::QueryInterface");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->QueryInterface(original::ddrawContext, riid, ppvObj));
}

ULONG __stdcall AddRef(IDirectDraw FAR * /*_this*/) {
	DDRAW_LOG("IDirectDraw::AddRef");
	return original::ddrawContext->lpVtbl->AddRef(original::ddrawContext);
}

ULONG __stdcall Release(IDirectDraw FAR * /*_this*/) {
	DDRAW_LOG("IDirectDraw::Release");
	return original::ddrawContext->lpVtbl->Release(original::ddrawContext);
}

HRESULT __stdcall Compact(IDirectDraw FAR * /*_this*/) {
	DDRAW_LOG("IDirectDraw::Compact");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->Compact(original::ddrawContext));
}

HRESULT __stdcall CreateClipper(IDirectDraw FAR * /*_this*/, DWORD arg1, LPDIRECTDRAWCLIPPER FAR* arg2, IUnknown FAR * arg3) {
	DDRAW_LOG("IDirectDraw::CreateClipper");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->CreateClipper(original::ddrawContext, arg1, arg2, arg3));
}

HRESULT __stdcall CreatePalette(IDirectDraw FAR * /*_this*/, DWORD arg1, LPPALETTEENTRY arg2, LPDIRECTDRAWPALETTE FAR* arg3, IUnknown FAR * arg4) {
	DDRAW_LOG("IDirectDraw::CreatePalette");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->CreatePalette(original::ddrawContext, arg1, arg2, arg3, arg4));
}

HRESULT __stdcall CreateSurface(IDirectDraw FAR * /*_this*/, LPDDSURFACEDESC arg1, LPDIRECTDRAWSURFACE FAR *arg2, IUnknown FAR *arg3) {
	DDRAW_LOG("IDirectDraw::CreateSurface", "%ux%u", arg1->dwWidth, arg1->dwHeight);
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->CreateSurface(original::ddrawContext, arg1, arg2, arg3));
}

HRESULT __stdcall DuplicateSurface(IDirectDraw FAR * /*_this*/, LPDIRECTDRAWSURFACE arg1, LPDIRECTDRAWSURFACE FAR * arg2) {
	DDRAW_LOG("IDirectDraw::DuplicateSurface");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->DuplicateSurface(original::ddrawContext, arg1, arg2));
}

HRESULT __stdcall EnumDisplayModes(IDirectDraw FAR * /*_this*/, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMMODESCALLBACK arg4) {
	DDRAW_LOG("IDirectDraw::EnumDisplayModes");
	original::ddrawEnumDisplayModes = arg4;
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->EnumDisplayModes(original::ddrawContext, arg1, arg2, arg3, EnumDisplayModesCallback));
}

HRESULT __stdcall EnumSurfaces(IDirectDraw FAR * /*_this*/, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMSURFACESCALLBACK arg4) {
	DDRAW_LOG("IDirectDraw::EnumSurfaces");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->EnumSurfaces(original::ddrawContext, arg1, arg2, arg3, arg4));
}

HRESULT __stdcall FlipToGDISurface(IDirectDraw FAR * /*_this*/) {
	DDRAW_LOG("IDirectDraw::FlipToGDISurface");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->FlipToGDISurface(original::ddrawContext));
}

HRESULT __stdcall GetCaps(IDirectDraw FAR * /*_this*/, LPDDCAPS arg1, LPDDCAPS arg2) {
	DDRAW_LOG("IDirectDraw::GetCaps");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->GetCaps(original::ddrawContext, arg1, arg2));
}

HRESULT __stdcall GetDisplayMode(IDirectDraw FAR * /*_this*/, LPDDSURFACEDESC arg1) {
	DDRAW_LOG("IDirectDraw::GetDisplayMode");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->GetDisplayMode(original::ddrawContext, arg1));
}

HRESULT __stdcall GetFourCCCodes(IDirectDraw FAR * /*_this*/, LPDWORD arg1, LPDWORD arg2) {
	DDRAW_LOG("IDirectDraw::GetFourCCCodes");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->GetFourCCCodes(original::ddrawContext, arg1, arg2));
}

HRESULT __stdcall GetGDISurface(IDirectDraw FAR * /*_this*/, LPDIRECTDRAWSURFACE FAR *arg1) {
	DDRAW_LOG("IDirectDraw::GetGDISurface");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->GetGDISurface(original::ddrawContext, arg1));
}

HRESULT __stdcall GetMonitorFrequency(IDirectDraw FAR * /*_this*/, LPDWORD arg1) {
	DDRAW_LOG("IDirectDraw::GetMonitorFrequency");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->GetMonitorFrequency(original::ddrawContext, arg1));
}

HRESULT __stdcall GetScanLine(IDirectDraw FAR * /*_this*/, LPDWORD arg1) {
	DDRAW_LOG("IDirectDraw::GetScanLine");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->GetScanLine(original::ddrawContext, arg1));
}

HRESULT __stdcall GetVerticalBlankStatus(IDirectDraw FAR * /*_this*/, LPBOOL arg1) {
	DDRAW_LOG("IDirectDraw::GetVerticalBlankStatus");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->GetVerticalBlankStatus(original::ddrawContext, arg1));
}

HRESULT __stdcall Initialize(IDirectDraw FAR * /*_this*/, GUID FAR *arg1) {
	DDRAW_LOG("IDirectDraw::Initialize");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->Initialize(original::ddrawContext, arg1));
}

HRESULT __stdcall RestoreDisplayMode(IDirectDraw FAR * /*_this*/) {
	DDRAW_LOG("IDirectDraw::RestoreDisplayMode");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->RestoreDisplayMode(original::ddrawContext));
}

HRESULT __stdcall SetCooperativeLevel(IDirectDraw FAR * /*_this*/, HWND arg1, DWORD arg2) {
	// 17 = DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE
	DDRAW_LOG("IDirectDraw::SetCooperativeLevel", "value:%u", arg2);
#if FORCE_WINDOWED
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->SetCooperativeLevel(original::ddrawContext, arg1, DDSCL_NORMAL));
#else
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->SetCooperativeLevel(original::ddrawContext, arg1, arg2));
#endif
}

HRESULT __stdcall SetDisplayMode(IDirectDraw FAR * /*_this*/, DWORD width, DWORD height, DWORD bpp) {
	DDRAW_LOG("IDirectDraw::SetDisplayMode", "width:%u, height:%u, bpp:%u", width, height, bpp);
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->SetDisplayMode(original::ddrawContext, width, height, bpp));
}

HRESULT __stdcall WaitForVerticalBlank(IDirectDraw FAR * /*_this*/, DWORD arg1, HANDLE arg2) {
	DDRAW_LOG("IDirectDraw::WaitForVerticalBlank");
	CHECK_HR_RETURN(original::ddrawContext->lpVtbl->WaitForVerticalBlank(original::ddrawContext, arg1, arg2));
}

struct VTable
{
	HRESULT (__stdcall *QueryInterface)(IDirectDraw FAR *_this, REFIID riid, LPVOID FAR * ppvObj);
	ULONG (__stdcall *AddRef)(IDirectDraw FAR *_this);
	ULONG (__stdcall *Release)(IDirectDraw FAR *_this);
	HRESULT (__stdcall *Compact)(IDirectDraw FAR *_this);
	HRESULT (__stdcall *CreateClipper)(IDirectDraw FAR *_this, DWORD arg1, LPDIRECTDRAWCLIPPER FAR* arg2, IUnknown FAR * arg3);
	HRESULT (__stdcall *CreatePalette)(IDirectDraw FAR *_this, DWORD arg1, LPPALETTEENTRY arg2, LPDIRECTDRAWPALETTE FAR* arg3, IUnknown FAR * arg4);
	HRESULT (__stdcall *CreateSurface)(IDirectDraw FAR *_this, LPDDSURFACEDESC arg1, LPDIRECTDRAWSURFACE FAR *arg2, IUnknown FAR *arg3);
	HRESULT (__stdcall *DuplicateSurface)(IDirectDraw FAR *_this, LPDIRECTDRAWSURFACE arg1, LPDIRECTDRAWSURFACE FAR * arg2);
	HRESULT (__stdcall *EnumDisplayModes)(IDirectDraw FAR *_this, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMMODESCALLBACK arg4);
	HRESULT (__stdcall *EnumSurfaces)(IDirectDraw FAR *_this, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMSURFACESCALLBACK arg4);
	HRESULT (__stdcall *FlipToGDISurface)(IDirectDraw FAR *_this);
	HRESULT (__stdcall *GetCaps)(IDirectDraw FAR *_this, LPDDCAPS arg1, LPDDCAPS arg2);
	HRESULT (__stdcall *GetDisplayMode)(IDirectDraw FAR *_this, LPDDSURFACEDESC arg1);
	HRESULT (__stdcall *GetFourCCCodes)(IDirectDraw FAR *_this, LPDWORD arg1, LPDWORD arg2);
	HRESULT (__stdcall *GetGDISurface)(IDirectDraw FAR *_this, LPDIRECTDRAWSURFACE FAR *arg1);
	HRESULT (__stdcall *GetMonitorFrequency)(IDirectDraw FAR *_this, LPDWORD arg1);
	HRESULT (__stdcall *GetScanLine)(IDirectDraw FAR *_this, LPDWORD arg1);
	HRESULT (__stdcall *GetVerticalBlankStatus)(IDirectDraw FAR *_this, LPBOOL arg1);
	HRESULT (__stdcall *Initialize)(IDirectDraw FAR *_this, GUID FAR *arg1);
	HRESULT (__stdcall *RestoreDisplayMode)(IDirectDraw FAR *_this);
	HRESULT (__stdcall *SetCooperativeLevel)(IDirectDraw FAR *_this, HWND arg1, DWORD arg2);
	HRESULT (__stdcall *SetDisplayMode)(IDirectDraw FAR *_this, DWORD width, DWORD height, DWORD bpp);
	HRESULT (__stdcall *WaitForVerticalBlank)(IDirectDraw FAR *_this, DWORD arg1, HANDLE arg2);
};

struct Context
{
	VTable FAR *lpVtbl;
};

static Context *ddrawContext = nullptr;

HRESULT WINAPI DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter) {
	DDRAW_LOG("DirectDrawCreate");
	HRESULT hr = original::DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
	if (hr)
		Logf("HRESULT: %u\n", hr);
#if WRAP_DDRAW
	original::ddrawContext = (LPDIRECTDRAW)*lplpDD;
	ddrawContext = new Context();
	ddrawContext->lpVtbl = new VTable();
	ddrawContext->lpVtbl->QueryInterface = ddraw::QueryInterface;
	ddrawContext->lpVtbl->AddRef = ddraw::AddRef;
	ddrawContext->lpVtbl->Release = ddraw::Release;
	ddrawContext->lpVtbl->Compact = ddraw::Compact;
	ddrawContext->lpVtbl->CreateClipper = ddraw::CreateClipper;
	ddrawContext->lpVtbl->CreatePalette = ddraw::CreatePalette;
	ddrawContext->lpVtbl->CreateSurface = ddraw::CreateSurface;
	ddrawContext->lpVtbl->DuplicateSurface = ddraw::DuplicateSurface;
	ddrawContext->lpVtbl->EnumDisplayModes = ddraw::EnumDisplayModes;
	ddrawContext->lpVtbl->EnumSurfaces = ddraw::EnumSurfaces;
	ddrawContext->lpVtbl->FlipToGDISurface = ddraw::FlipToGDISurface;
	ddrawContext->lpVtbl->GetCaps = ddraw::GetCaps;
	ddrawContext->lpVtbl->GetDisplayMode = ddraw::GetDisplayMode;
	ddrawContext->lpVtbl->GetFourCCCodes = ddraw::GetFourCCCodes;
	ddrawContext->lpVtbl->GetGDISurface = ddraw::GetGDISurface;
	ddrawContext->lpVtbl->GetMonitorFrequency = ddraw::GetMonitorFrequency;
	ddrawContext->lpVtbl->GetScanLine = ddraw::GetScanLine;
	ddrawContext->lpVtbl->GetVerticalBlankStatus = ddraw::GetVerticalBlankStatus;
	ddrawContext->lpVtbl->Initialize = ddraw::Initialize;
	ddrawContext->lpVtbl->RestoreDisplayMode = ddraw::RestoreDisplayMode;
	ddrawContext->lpVtbl->SetCooperativeLevel = ddraw::SetCooperativeLevel;
	ddrawContext->lpVtbl->SetDisplayMode = ddraw::SetDisplayMode;
	ddrawContext->lpVtbl->WaitForVerticalBlank = ddraw::WaitForVerticalBlank;
	*lplpDD = (LPDIRECTDRAW)ddrawContext;
#endif
	return hr;
}

HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext) {
	DDRAW_LOG("DirectDrawEnumerateA");
	CHECK_HR_RETURN(original::DirectDrawEnumerateA(lpCallback, lpContext));
}

WrappedFunc g_DirectDrawCreateFunc = { DDRAW_DLL, "DirectDrawCreate", DirectDrawCreate, (void **)&original::DirectDrawCreate };
WrappedFunc g_DirectDrawEnumerateA = { DDRAW_DLL, "DirectDrawEnumerateA", DirectDrawEnumerateA, (void **)&original::DirectDrawEnumerateA };

void Init() {
	data::numDisplayModes = (uint32_t *)(0x006080D8);
	data::displayModes = (data::DisplayMode	 *)(0x006080E0);
}

} // namespace ddraw
