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

HRESULT (WINAPI *DirectDrawCreate)(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter);
HRESULT (WINAPI *DirectDrawEnumerateA)(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext);

} // namespace original

struct IDirectDraw_Wrapped;
struct IDirectDrawClipper_Wrapped;
struct IDirectDrawPalette_Wrapped;
struct IDirectDrawSurface_Wrapped;

struct IDirectDrawClipperVtbl_Wrapped
{
	HRESULT (__stdcall *QueryInterface)(IDirectDrawClipper_Wrapped *_this, REFIID riid, LPVOID * ppvObj);
	ULONG (__stdcall *AddRef)(IDirectDrawClipper_Wrapped *_this);
	ULONG (__stdcall *Release)(IDirectDrawClipper_Wrapped *_this);
	HRESULT (__stdcall *GetClipList)(IDirectDrawClipper_Wrapped *_this, LPRECT arg1, LPRGNDATA arg2, LPDWORD arg3);
	HRESULT (__stdcall *GetHWnd)(IDirectDrawClipper_Wrapped *_this, HWND *arg1);
	HRESULT (__stdcall *Initialize)(IDirectDrawClipper_Wrapped *_this, LPDIRECTDRAW arg1, DWORD arg2);
	HRESULT (__stdcall *IsClipListChanged)(IDirectDrawClipper_Wrapped *_this, BOOL *arg1);
	HRESULT (__stdcall *SetClipList)(IDirectDrawClipper_Wrapped *_this, LPRGNDATA arg1, DWORD arg2);
	HRESULT (__stdcall *SetHWnd)(IDirectDrawClipper_Wrapped *_this, DWORD arg1, HWND arg2);
};

struct IDirectDrawClipper_Wrapped
{
	IDirectDrawClipperVtbl_Wrapped *lpVtbl;
	LPDIRECTDRAWCLIPPER original;
};

struct IDirectDrawSurfaceVtbl_Wrapped
{
	HRESULT (__stdcall *QueryInterface)(IDirectDrawSurface_Wrapped *_this, REFIID riid, LPVOID * ppvObj);
	ULONG (__stdcall *AddRef)(IDirectDrawSurface_Wrapped *_this);
	ULONG (__stdcall *Release)(IDirectDrawSurface_Wrapped *_this);
	HRESULT (__stdcall *AddAttachedSurface)(IDirectDrawSurface_Wrapped *_this, IDirectDrawSurface_Wrapped *arg1);
	HRESULT (__stdcall *AddOverlayDirtyRect)(IDirectDrawSurface_Wrapped *_this, LPRECT arg1);
	HRESULT (__stdcall *Blt)(IDirectDrawSurface_Wrapped *_this, LPRECT arg1, IDirectDrawSurface_Wrapped *arg2, LPRECT arg3, DWORD arg4, LPDDBLTFX arg5);
	HRESULT (__stdcall *BltBatch)(IDirectDrawSurface_Wrapped *_this, LPDDBLTBATCH arg1, DWORD arg2, DWORD arg3);
	HRESULT (__stdcall *BltFast)(IDirectDrawSurface_Wrapped *_this, DWORD arg1, DWORD arg2, IDirectDrawSurface_Wrapped *arg3, LPRECT arg4, DWORD arg5);
	HRESULT (__stdcall *DeleteAttachedSurface)(IDirectDrawSurface_Wrapped *_this, DWORD arg1, IDirectDrawSurface_Wrapped *arg2);
	HRESULT (__stdcall *EnumAttachedSurfaces)(IDirectDrawSurface_Wrapped *_this, LPVOID arg1, LPDDENUMSURFACESCALLBACK arg2);
	HRESULT (__stdcall *EnumOverlayZOrders)(IDirectDrawSurface_Wrapped *_this, DWORD arg1, LPVOID arg2, LPDDENUMSURFACESCALLBACK arg3);
	HRESULT (__stdcall *Flip)(IDirectDrawSurface_Wrapped *_this, IDirectDrawSurface_Wrapped *arg1, DWORD arg2);
	HRESULT (__stdcall *GetAttachedSurface)(IDirectDrawSurface_Wrapped *_this, LPDDSCAPS arg1, LPDIRECTDRAWSURFACE * arg2);
	HRESULT (__stdcall *GetBltStatus)(IDirectDrawSurface_Wrapped *_this, DWORD arg1);
	HRESULT (__stdcall *GetCaps)(IDirectDrawSurface_Wrapped *_this, LPDDSCAPS arg1);
	HRESULT (__stdcall *GetClipper)(IDirectDrawSurface_Wrapped *_this, LPDIRECTDRAWCLIPPER * arg1);
	HRESULT (__stdcall *GetColorKey)(IDirectDrawSurface_Wrapped *_this, DWORD arg1, LPDDCOLORKEY arg2);
	HRESULT (__stdcall *GetDC)(IDirectDrawSurface_Wrapped *_this, HDC *arg1);
	HRESULT (__stdcall *GetFlipStatus)(IDirectDrawSurface_Wrapped *_this, DWORD arg1);
	HRESULT (__stdcall *GetOverlayPosition)(IDirectDrawSurface_Wrapped *_this, LPLONG arg1, LPLONG arg2);
	HRESULT (__stdcall *GetPalette)(IDirectDrawSurface_Wrapped *_this, LPDIRECTDRAWPALETTE * arg1);
	HRESULT (__stdcall *GetPixelFormat)(IDirectDrawSurface_Wrapped *_this, LPDDPIXELFORMAT arg1);
	HRESULT (__stdcall *GetSurfaceDesc)(IDirectDrawSurface_Wrapped *_this, LPDDSURFACEDESC arg1);
	HRESULT (__stdcall *Initialize)(IDirectDrawSurface_Wrapped *_this, LPDIRECTDRAW arg1, LPDDSURFACEDESC arg2);
	HRESULT (__stdcall *IsLost)(IDirectDrawSurface_Wrapped *_this);
	HRESULT (__stdcall *Lock)(IDirectDrawSurface_Wrapped *_this, LPRECT arg1, LPDDSURFACEDESC arg2, DWORD arg3, HANDLE arg4);
	HRESULT (__stdcall *ReleaseDC)(IDirectDrawSurface_Wrapped *_this, HDC arg1);
	HRESULT (__stdcall *Restore)(IDirectDrawSurface_Wrapped *_this);
	HRESULT (__stdcall *SetClipper)(IDirectDrawSurface_Wrapped *_this, IDirectDrawClipper_Wrapped *arg1);
	HRESULT (__stdcall *SetColorKey)(IDirectDrawSurface_Wrapped *_this, DWORD arg1, LPDDCOLORKEY arg2);
	HRESULT (__stdcall *SetOverlayPosition)(IDirectDrawSurface_Wrapped *_this, LONG arg1, LONG arg2);
	HRESULT (__stdcall *SetPalette)(IDirectDrawSurface_Wrapped *_this, IDirectDrawPalette_Wrapped *arg1);
	HRESULT (__stdcall *Unlock)(IDirectDrawSurface_Wrapped *_this, LPVOID arg1);
	HRESULT (__stdcall *UpdateOverlay)(IDirectDrawSurface_Wrapped *_this, LPRECT arg1, IDirectDrawSurface_Wrapped *arg2, LPRECT arg3, DWORD arg4, LPDDOVERLAYFX arg5);
	HRESULT (__stdcall *UpdateOverlayDisplay)(IDirectDrawSurface_Wrapped *_this, DWORD arg1);
	HRESULT (__stdcall *UpdateOverlayZOrder)(IDirectDrawSurface_Wrapped *_this, DWORD arg1, IDirectDrawSurface_Wrapped *arg2);
};

struct IDirectDrawSurface_Wrapped
{
	IDirectDrawSurfaceVtbl_Wrapped *lpVtbl;
	LPDIRECTDRAWSURFACE original;
};

struct IDirectDrawPaletteVtbl_Wrapped
{
	HRESULT (__stdcall *QueryInterface)(IDirectDrawPalette_Wrapped *_this, REFIID riid, LPVOID * ppvObj);
	ULONG (__stdcall *AddRef)(IDirectDrawPalette_Wrapped *_this);
	ULONG (__stdcall *Release)(IDirectDrawPalette_Wrapped *_this);
	HRESULT (__stdcall *GetCaps)(IDirectDrawPalette_Wrapped *_this, LPDWORD arg1);
	HRESULT (__stdcall *GetEntries)(IDirectDrawPalette_Wrapped *_this, DWORD arg1, DWORD arg2, DWORD arg3, LPPALETTEENTRY arg4);
	HRESULT (__stdcall *Initialize)(IDirectDrawPalette_Wrapped *_this, IDirectDraw_Wrapped *arg1, DWORD arg2, LPPALETTEENTRY arg3);
	HRESULT (__stdcall *SetEntries)(IDirectDrawPalette_Wrapped *_this, DWORD arg1, DWORD arg2, DWORD arg3, LPPALETTEENTRY arg4);
};

struct IDirectDrawPalette_Wrapped
{
	IDirectDrawPaletteVtbl_Wrapped *lpVtbl;
	LPDIRECTDRAWPALETTE original;
};

struct IDirectDrawVtbl_Wrapped
{
	HRESULT (__stdcall *QueryInterface)(IDirectDraw_Wrapped *_this, REFIID riid, LPVOID * ppvObj);
	ULONG (__stdcall *AddRef)(IDirectDraw_Wrapped *_this);
	ULONG (__stdcall *Release)(IDirectDraw_Wrapped *_this);
	HRESULT (__stdcall *Compact)(IDirectDraw_Wrapped *_this);
	HRESULT (__stdcall *CreateClipper)(IDirectDraw_Wrapped *_this, DWORD arg1, IDirectDrawClipper_Wrapped **arg2, IUnknown * arg3);
	HRESULT (__stdcall *CreatePalette)(IDirectDraw_Wrapped *_this, DWORD arg1, LPPALETTEENTRY arg2, IDirectDrawPalette_Wrapped **arg3, IUnknown * arg4);
	HRESULT (__stdcall *CreateSurface)(IDirectDraw_Wrapped *_this, LPDDSURFACEDESC arg1, IDirectDrawSurface_Wrapped **arg2, IUnknown *arg3);
	HRESULT (__stdcall *DuplicateSurface)(IDirectDraw_Wrapped *_this, LPDIRECTDRAWSURFACE arg1, LPDIRECTDRAWSURFACE * arg2);
	HRESULT (__stdcall *EnumDisplayModes)(IDirectDraw_Wrapped *_this, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMMODESCALLBACK arg4);
	HRESULT (__stdcall *EnumSurfaces)(IDirectDraw_Wrapped *_this, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMSURFACESCALLBACK arg4);
	HRESULT (__stdcall *FlipToGDISurface)(IDirectDraw_Wrapped *_this);
	HRESULT (__stdcall *GetCaps)(IDirectDraw_Wrapped *_this, LPDDCAPS arg1, LPDDCAPS arg2);
	HRESULT (__stdcall *GetDisplayMode)(IDirectDraw_Wrapped *_this, LPDDSURFACEDESC arg1);
	HRESULT (__stdcall *GetFourCCCodes)(IDirectDraw_Wrapped *_this, LPDWORD arg1, LPDWORD arg2);
	HRESULT (__stdcall *GetGDISurface)(IDirectDraw_Wrapped *_this, LPDIRECTDRAWSURFACE *arg1);
	HRESULT (__stdcall *GetMonitorFrequency)(IDirectDraw_Wrapped *_this, LPDWORD arg1);
	HRESULT (__stdcall *GetScanLine)(IDirectDraw_Wrapped *_this, LPDWORD arg1);
	HRESULT (__stdcall *GetVerticalBlankStatus)(IDirectDraw_Wrapped *_this, LPBOOL arg1);
	HRESULT (__stdcall *Initialize)(IDirectDraw_Wrapped *_this, GUID *arg1);
	HRESULT (__stdcall *RestoreDisplayMode)(IDirectDraw_Wrapped *_this);
	HRESULT (__stdcall *SetCooperativeLevel)(IDirectDraw_Wrapped *_this, HWND arg1, DWORD arg2);
	HRESULT (__stdcall *SetDisplayMode)(IDirectDraw_Wrapped *_this, DWORD width, DWORD height, DWORD bpp);
	HRESULT (__stdcall *WaitForVerticalBlank)(IDirectDraw_Wrapped *_this, DWORD arg1, HANDLE arg2);
};

struct IDirectDraw_Wrapped
{
	IDirectDrawVtbl_Wrapped *lpVtbl;
	LPDIRECTDRAW original;
};

namespace clipper {

HRESULT __stdcall QueryInterface(IDirectDrawClipper_Wrapped *_this, REFIID riid, LPVOID * ppvObj) {
	DDRAW_LOG("IDirectDrawClipper::QueryInterface");
	CHECK_HR_RETURN(_this->original->lpVtbl->QueryInterface(_this->original, riid, ppvObj));
}

ULONG __stdcall AddRef(IDirectDrawClipper_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawClipper::AddRef");
	return _this->original->lpVtbl->AddRef(_this->original);
}

ULONG __stdcall Release(IDirectDrawClipper_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawClipper::Release");
	return _this->original->lpVtbl->Release(_this->original);
}

HRESULT __stdcall GetClipList(IDirectDrawClipper_Wrapped *_this, LPRECT arg1, LPRGNDATA arg2, LPDWORD arg3) {
	DDRAW_LOG("IDirectDrawClipper::GetClipList");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetClipList(_this->original, arg1, arg2, arg3));
}

HRESULT __stdcall GetHWnd(IDirectDrawClipper_Wrapped *_this, HWND *arg1) {
	DDRAW_LOG("IDirectDrawClipper::GetHWnd");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetHWnd(_this->original, arg1));
}

HRESULT __stdcall Initialize(IDirectDrawClipper_Wrapped *_this, LPDIRECTDRAW arg1, DWORD arg2) {
	DDRAW_LOG("IDirectDrawClipper::Initialize");
	CHECK_HR_RETURN(_this->original->lpVtbl->Initialize(_this->original, arg1, arg2));
}

HRESULT __stdcall IsClipListChanged(IDirectDrawClipper_Wrapped *_this, BOOL *arg1) {
	DDRAW_LOG("IDirectDrawClipper::IsClipListChanged");
	CHECK_HR_RETURN(_this->original->lpVtbl->IsClipListChanged(_this->original, arg1));
}

HRESULT __stdcall SetClipList(IDirectDrawClipper_Wrapped *_this, LPRGNDATA arg1, DWORD arg2) {
	DDRAW_LOG("IDirectDrawClipper::SetClipList");
	CHECK_HR_RETURN(_this->original->lpVtbl->SetClipList(_this->original, arg1, arg2));
}

HRESULT __stdcall SetHWnd(IDirectDrawClipper_Wrapped *_this, DWORD arg1, HWND arg2) {
	DDRAW_LOG("IDirectDrawClipper::SetHWnd");
	CHECK_HR_RETURN(_this->original->lpVtbl->SetHWnd(_this->original, arg1, arg2));
}


} // namespace clipper

namespace surface {

HRESULT __stdcall QueryInterface(IDirectDrawSurface_Wrapped *_this, REFIID riid, LPVOID * ppvObj) {
	DDRAW_LOG("IDirectDrawSurface::QueryInterface");
	CHECK_HR_RETURN(_this->original->lpVtbl->QueryInterface(_this->original, riid, ppvObj));
}

ULONG __stdcall AddRef(IDirectDrawSurface_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawSurface::AddRef");
	return _this->original->lpVtbl->AddRef(_this->original);
}

ULONG __stdcall Release(IDirectDrawSurface_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawSurface::Release");
	return _this->original->lpVtbl->Release(_this->original);
}

HRESULT __stdcall AddAttachedSurface(IDirectDrawSurface_Wrapped *_this, IDirectDrawSurface_Wrapped *arg1) {
	DDRAW_LOG("IDirectDrawSurface::AddAttachedSurface");
	CHECK_HR_RETURN(_this->original->lpVtbl->AddAttachedSurface(_this->original, arg1->original));
}

HRESULT __stdcall AddOverlayDirtyRect(IDirectDrawSurface_Wrapped *_this, LPRECT arg1) {
	DDRAW_LOG("IDirectDrawSurface::AddOverlayDirtyRect");
	CHECK_HR_RETURN(_this->original->lpVtbl->AddOverlayDirtyRect(_this->original, arg1));
}

HRESULT __stdcall Blt(IDirectDrawSurface_Wrapped *_this, LPRECT arg1, IDirectDrawSurface_Wrapped *arg2, LPRECT arg3, DWORD arg4, LPDDBLTFX arg5) {
	DDRAW_LOG("IDirectDrawSurface::Blt");
	// arg2 can be NULL
	CHECK_HR_RETURN(_this->original->lpVtbl->Blt(_this->original, arg1, arg2 ? arg2->original : nullptr, arg3, arg4, arg5));
}

HRESULT __stdcall BltBatch(IDirectDrawSurface_Wrapped *_this, LPDDBLTBATCH arg1, DWORD arg2, DWORD arg3) {
	DDRAW_LOG("IDirectDrawSurface::BltBatch");
	CHECK_HR_RETURN(_this->original->lpVtbl->BltBatch(_this->original, arg1, arg2, arg3));
}

HRESULT __stdcall BltFast(IDirectDrawSurface_Wrapped *_this, DWORD arg1, DWORD arg2, IDirectDrawSurface_Wrapped *arg3, LPRECT arg4, DWORD arg5) {
	DDRAW_LOG("IDirectDrawSurface::BltFast");
	CHECK_HR_RETURN(_this->original->lpVtbl->BltFast(_this->original, arg1, arg2, arg3->original, arg4, arg5));
}

HRESULT __stdcall DeleteAttachedSurface(IDirectDrawSurface_Wrapped *_this, DWORD arg1, IDirectDrawSurface_Wrapped *arg2) {
	DDRAW_LOG("IDirectDrawSurface::DeleteAttachedSurface");
	CHECK_HR_RETURN(_this->original->lpVtbl->DeleteAttachedSurface(_this->original, arg1, arg2->original));
}

HRESULT __stdcall EnumAttachedSurfaces(IDirectDrawSurface_Wrapped *_this, LPVOID arg1, LPDDENUMSURFACESCALLBACK arg2) {
	DDRAW_LOG("IDirectDrawSurface::EnumAttachedSurfaces");
	CHECK_HR_RETURN(_this->original->lpVtbl->EnumAttachedSurfaces(_this->original, arg1, arg2));
}

HRESULT __stdcall EnumOverlayZOrders(IDirectDrawSurface_Wrapped *_this, DWORD arg1, LPVOID arg2, LPDDENUMSURFACESCALLBACK arg3) {
	DDRAW_LOG("IDirectDrawSurface::EnumOverlayZOrders");
	CHECK_HR_RETURN(_this->original->lpVtbl->EnumOverlayZOrders(_this->original, arg1, arg2, arg3));
}

HRESULT __stdcall Flip(IDirectDrawSurface_Wrapped *_this, IDirectDrawSurface_Wrapped *arg1, DWORD arg2) {
	DDRAW_LOG("IDirectDrawSurface::Flip");
	CHECK_HR_RETURN(_this->original->lpVtbl->Flip(_this->original, arg1->original, arg2));
}

HRESULT __stdcall GetAttachedSurface(IDirectDrawSurface_Wrapped *_this, LPDDSCAPS arg1, LPDIRECTDRAWSURFACE * arg2) {
	DDRAW_LOG("IDirectDrawSurface::GetAttachedSurface");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetAttachedSurface(_this->original, arg1, arg2));
}

HRESULT __stdcall GetBltStatus(IDirectDrawSurface_Wrapped *_this, DWORD arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetBltStatus");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetBltStatus(_this->original, arg1));
}

HRESULT __stdcall GetCaps(IDirectDrawSurface_Wrapped *_this, LPDDSCAPS arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetCaps");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetCaps(_this->original, arg1));
}

HRESULT __stdcall GetClipper(IDirectDrawSurface_Wrapped *_this, LPDIRECTDRAWCLIPPER * arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetClipper");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetClipper(_this->original, arg1));
}

HRESULT __stdcall GetColorKey(IDirectDrawSurface_Wrapped *_this, DWORD arg1, LPDDCOLORKEY arg2) {
	DDRAW_LOG("IDirectDrawSurface::GetColorKey");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetColorKey(_this->original, arg1, arg2));
}

HRESULT __stdcall GetDC(IDirectDrawSurface_Wrapped *_this, HDC *arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetDC");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetDC(_this->original, arg1));
}

HRESULT __stdcall GetFlipStatus(IDirectDrawSurface_Wrapped *_this, DWORD arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetFlipStatus");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetFlipStatus(_this->original, arg1));
}

HRESULT __stdcall GetOverlayPosition(IDirectDrawSurface_Wrapped *_this, LPLONG arg1, LPLONG arg2) {
	DDRAW_LOG("IDirectDrawSurface::GetOverlayPosition");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetOverlayPosition(_this->original, arg1, arg2));
}

HRESULT __stdcall GetPalette(IDirectDrawSurface_Wrapped *_this, LPDIRECTDRAWPALETTE * arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetPalette");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetPalette(_this->original, arg1));
}

HRESULT __stdcall GetPixelFormat(IDirectDrawSurface_Wrapped *_this, LPDDPIXELFORMAT arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetPixelFormat");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetPixelFormat(_this->original, arg1));
}

HRESULT __stdcall GetSurfaceDesc(IDirectDrawSurface_Wrapped *_this, LPDDSURFACEDESC arg1) {
	DDRAW_LOG("IDirectDrawSurface::GetSurfaceDesc");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetSurfaceDesc(_this->original, arg1));
}

HRESULT __stdcall Initialize(IDirectDrawSurface_Wrapped *_this, LPDIRECTDRAW arg1, LPDDSURFACEDESC arg2) {
	DDRAW_LOG("IDirectDrawSurface::Initialize");
	CHECK_HR_RETURN(_this->original->lpVtbl->Initialize(_this->original, arg1, arg2));
}

HRESULT __stdcall IsLost(IDirectDrawSurface_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawSurface::IsLost");
	CHECK_HR_RETURN(_this->original->lpVtbl->IsLost(_this->original));
}

HRESULT __stdcall Lock(IDirectDrawSurface_Wrapped *_this, LPRECT arg1, LPDDSURFACEDESC arg2, DWORD arg3, HANDLE arg4) {
	DDRAW_LOG("IDirectDrawSurface::Lock");
	CHECK_HR_RETURN(_this->original->lpVtbl->Lock(_this->original, arg1, arg2, arg3, arg4));
}

HRESULT __stdcall ReleaseDC(IDirectDrawSurface_Wrapped *_this, HDC arg1) {
	DDRAW_LOG("IDirectDrawSurface::ReleaseDC");
	CHECK_HR_RETURN(_this->original->lpVtbl->ReleaseDC(_this->original, arg1));
}

HRESULT __stdcall Restore(IDirectDrawSurface_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawSurface::Restore");
	CHECK_HR_RETURN(_this->original->lpVtbl->Restore(_this->original));
}

HRESULT __stdcall SetClipper(IDirectDrawSurface_Wrapped *_this, IDirectDrawClipper_Wrapped *arg1) {
	DDRAW_LOG("IDirectDrawSurface::SetClipper");
	CHECK_HR_RETURN(_this->original->lpVtbl->SetClipper(_this->original, arg1->original));
}

HRESULT __stdcall SetColorKey(IDirectDrawSurface_Wrapped *_this, DWORD arg1, LPDDCOLORKEY arg2) {
	DDRAW_LOG("IDirectDrawSurface::SetColorKey");
	CHECK_HR_RETURN(_this->original->lpVtbl->SetColorKey(_this->original, arg1, arg2));
}

HRESULT __stdcall SetOverlayPosition(IDirectDrawSurface_Wrapped *_this, LONG arg1, LONG arg2) {
	DDRAW_LOG("IDirectDrawSurface::SetOverlayPosition");
	CHECK_HR_RETURN(_this->original->lpVtbl->SetOverlayPosition(_this->original, arg1, arg2));
}

HRESULT __stdcall SetPalette(IDirectDrawSurface_Wrapped *_this, IDirectDrawPalette_Wrapped *arg1) {
	DDRAW_LOG("IDirectDrawSurface::SetPalette");
	CHECK_HR_RETURN(_this->original->lpVtbl->SetPalette(_this->original, arg1->original));
}

HRESULT __stdcall Unlock(IDirectDrawSurface_Wrapped *_this, LPVOID arg1) {
	DDRAW_LOG("IDirectDrawSurface::Unlock");
	CHECK_HR_RETURN(_this->original->lpVtbl->Unlock(_this->original, arg1));
}

HRESULT __stdcall UpdateOverlay(IDirectDrawSurface_Wrapped *_this, LPRECT arg1, IDirectDrawSurface_Wrapped *arg2, LPRECT arg3, DWORD arg4, LPDDOVERLAYFX arg5) {
	DDRAW_LOG("IDirectDrawSurface::UpdateOverlay");
	CHECK_HR_RETURN(_this->original->lpVtbl->UpdateOverlay(_this->original, arg1, arg2->original, arg3, arg4, arg5));
}

HRESULT __stdcall UpdateOverlayDisplay(IDirectDrawSurface_Wrapped *_this, DWORD arg1) {
	DDRAW_LOG("IDirectDrawSurface::UpdateOverlayDisplay");
	CHECK_HR_RETURN(_this->original->lpVtbl->UpdateOverlayDisplay(_this->original, arg1));
}

HRESULT __stdcall UpdateOverlayZOrder(IDirectDrawSurface_Wrapped *_this, DWORD arg1, IDirectDrawSurface_Wrapped *arg2) {
	DDRAW_LOG("IDirectDrawSurface::UpdateOverlayZOrder");
	CHECK_HR_RETURN(_this->original->lpVtbl->UpdateOverlayZOrder(_this->original, arg1, arg2->original));
}

} // namespace surface

namespace palette {

HRESULT __stdcall QueryInterface(IDirectDrawPalette_Wrapped *_this, REFIID riid, LPVOID * ppvObj) {
	DDRAW_LOG("IDirectDrawPalette::QueryInterface");
	CHECK_HR_RETURN(_this->original->lpVtbl->QueryInterface(_this->original, riid, ppvObj));
}

ULONG __stdcall AddRef(IDirectDrawPalette_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawPalette::AddRef");
	return _this->original->lpVtbl->AddRef(_this->original);
}

ULONG __stdcall Release(IDirectDrawPalette_Wrapped *_this) {
	DDRAW_LOG("IDirectDrawPalette::Release");
	return _this->original->lpVtbl->Release(_this->original);
}

HRESULT __stdcall GetCaps(IDirectDrawPalette_Wrapped *_this, LPDWORD arg1) {
	DDRAW_LOG("IDirectDrawPalette::GetCaps");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetCaps(_this->original, arg1));
}

HRESULT __stdcall GetEntries(IDirectDrawPalette_Wrapped *_this, DWORD arg1, DWORD arg2, DWORD arg3, LPPALETTEENTRY arg4) {
	DDRAW_LOG("IDirectDrawPalette::GetEntries");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetEntries(_this->original, arg1, arg2, arg3, arg4));
}

HRESULT __stdcall Initialize(IDirectDrawPalette_Wrapped *_this, IDirectDraw_Wrapped *arg1, DWORD arg2, LPPALETTEENTRY arg3) {
	DDRAW_LOG("IDirectDrawPalette::Initialize");
	CHECK_HR_RETURN(_this->original->lpVtbl->Initialize(_this->original, arg1->original, arg2, arg3));
}

HRESULT __stdcall SetEntries(IDirectDrawPalette_Wrapped *_this, DWORD arg1, DWORD arg2, DWORD arg3, LPPALETTEENTRY arg4) {
	DDRAW_LOG("IDirectDrawPalette::SetEntries");
	CHECK_HR_RETURN(_this->original->lpVtbl->SetEntries(_this->original, arg1, arg2, arg3, arg4));
}

} // namespace palette

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

HRESULT __stdcall QueryInterface(IDirectDraw_Wrapped *_this, REFIID riid, LPVOID * ppvObj) {
	DDRAW_LOG("IDirectDraw::QueryInterface");
	CHECK_HR_RETURN(_this->original->lpVtbl->QueryInterface(_this->original, riid, ppvObj));
}

ULONG __stdcall AddRef(IDirectDraw_Wrapped *_this) {
	DDRAW_LOG("IDirectDraw::AddRef");
	return _this->original->lpVtbl->AddRef(_this->original);
}

ULONG __stdcall Release(IDirectDraw_Wrapped *_this) {
	DDRAW_LOG("IDirectDraw::Release");
	return _this->original->lpVtbl->Release(_this->original);
}

HRESULT __stdcall Compact(IDirectDraw_Wrapped *_this) {
	DDRAW_LOG("IDirectDraw::Compact");
	CHECK_HR_RETURN(_this->original->lpVtbl->Compact(_this->original));
}

HRESULT __stdcall CreateClipper(IDirectDraw_Wrapped *_this, DWORD arg1, IDirectDrawClipper_Wrapped **arg2, IUnknown * arg3) {
	DDRAW_LOG("IDirectDraw::CreateClipper");
	LPDIRECTDRAWCLIPPER original;
	HRESULT hr = _this->original->lpVtbl->CreateClipper(_this->original, arg1, &original, arg3);
	if (hr) {
		Logf("HRESULT: %u\n", hr);
		return hr;
	}
	auto clipper = new IDirectDrawClipper_Wrapped();
	clipper->lpVtbl = new IDirectDrawClipperVtbl_Wrapped();
	clipper->lpVtbl->QueryInterface = clipper::QueryInterface;
	clipper->lpVtbl->AddRef = clipper::AddRef;
	clipper->lpVtbl->Release = clipper::Release;
	clipper->lpVtbl->GetClipList = clipper::GetClipList;
	clipper->lpVtbl->GetHWnd = clipper::GetHWnd;
	clipper->lpVtbl->Initialize = clipper::Initialize;
	clipper->lpVtbl->IsClipListChanged = clipper::IsClipListChanged;
	clipper->lpVtbl->SetClipList = clipper::SetClipList;
	clipper->lpVtbl->SetHWnd = clipper::SetHWnd;
	clipper->original = original;
	*arg2 = clipper;
	return hr;
}

HRESULT __stdcall CreatePalette(IDirectDraw_Wrapped *_this, DWORD arg1, LPPALETTEENTRY arg2, IDirectDrawPalette_Wrapped **arg3, IUnknown * arg4) {
	DDRAW_LOG("IDirectDraw::CreatePalette");
	LPDIRECTDRAWPALETTE original;
	HRESULT hr = _this->original->lpVtbl->CreatePalette(_this->original, arg1, arg2, &original, arg4);
	if (hr) {
		Logf("HRESULT: %u\n", hr);
		return hr;
	}
	auto pal = new IDirectDrawPalette_Wrapped();
	pal->lpVtbl = new IDirectDrawPaletteVtbl_Wrapped();
	pal->lpVtbl->QueryInterface = palette::QueryInterface;
	pal->lpVtbl->AddRef = palette::AddRef;
	pal->lpVtbl->Release = palette::Release;
	pal->lpVtbl->GetCaps = palette::GetCaps;
	pal->lpVtbl->GetEntries = palette::GetEntries;
	pal->lpVtbl->Initialize = palette::Initialize;
	pal->lpVtbl->SetEntries = palette::SetEntries;
	pal->original = original;
	*arg3 = pal;
	return hr;
}

HRESULT __stdcall CreateSurface(IDirectDraw_Wrapped *_this, LPDDSURFACEDESC arg1, IDirectDrawSurface_Wrapped **arg2, IUnknown *arg3) {
	DDRAW_LOG("IDirectDraw::CreateSurface", "%ux%u", arg1->dwWidth, arg1->dwHeight);
	LPDIRECTDRAWSURFACE original;
	HRESULT hr = _this->original->lpVtbl->CreateSurface(_this->original, arg1, &original, arg3);
	if (hr) {
		Logf("HRESULT: %u\n", hr);
		return hr;
	}
	auto surf = new IDirectDrawSurface_Wrapped();
	surf->lpVtbl = new IDirectDrawSurfaceVtbl_Wrapped();
	surf->lpVtbl->QueryInterface = surface::QueryInterface;
	surf->lpVtbl->AddRef = surface::AddRef;
	surf->lpVtbl->Release = surface::Release;
	surf->lpVtbl->AddAttachedSurface = surface::AddAttachedSurface;
	surf->lpVtbl->AddOverlayDirtyRect = surface::AddOverlayDirtyRect;
	surf->lpVtbl->Blt = surface::Blt;
	surf->lpVtbl->BltBatch = surface::BltBatch;
	surf->lpVtbl->BltFast = surface::BltFast;
	surf->lpVtbl->DeleteAttachedSurface = surface::DeleteAttachedSurface;
	surf->lpVtbl->EnumAttachedSurfaces = surface::EnumAttachedSurfaces;
	surf->lpVtbl->EnumOverlayZOrders = surface::EnumOverlayZOrders;
	surf->lpVtbl->Flip = surface::Flip;
	surf->lpVtbl->GetAttachedSurface = surface::GetAttachedSurface;
	surf->lpVtbl->GetBltStatus = surface::GetBltStatus;
	surf->lpVtbl->GetCaps = surface::GetCaps;
	surf->lpVtbl->GetClipper = surface::GetClipper;
	surf->lpVtbl->GetColorKey = surface::GetColorKey;
	surf->lpVtbl->GetDC = surface::GetDC;
	surf->lpVtbl->GetFlipStatus = surface::GetFlipStatus;
	surf->lpVtbl->GetOverlayPosition = surface::GetOverlayPosition;
	surf->lpVtbl->GetPalette = surface::GetPalette;
	surf->lpVtbl->GetPixelFormat = surface::GetPixelFormat;
	surf->lpVtbl->GetSurfaceDesc = surface::GetSurfaceDesc;
	surf->lpVtbl->Initialize = surface::Initialize;
	surf->lpVtbl->IsLost = surface::IsLost;
	surf->lpVtbl->Lock = surface::Lock;
	surf->lpVtbl->ReleaseDC = surface::ReleaseDC;
	surf->lpVtbl->Restore = surface::Restore;
	surf->lpVtbl->SetClipper = surface::SetClipper;
	surf->lpVtbl->SetColorKey = surface::SetColorKey;
	surf->lpVtbl->SetOverlayPosition = surface::SetOverlayPosition;
	surf->lpVtbl->SetPalette = surface::SetPalette;
	surf->lpVtbl->Unlock = surface::Unlock;
	surf->lpVtbl->UpdateOverlay = surface::UpdateOverlay;
	surf->lpVtbl->UpdateOverlayDisplay = surface::UpdateOverlayDisplay;
	surf->lpVtbl->UpdateOverlayZOrder = surface::UpdateOverlayZOrder;
	surf->original = original;
	*arg2 = surf;
	return hr;
}

HRESULT __stdcall DuplicateSurface(IDirectDraw_Wrapped *_this, LPDIRECTDRAWSURFACE arg1, LPDIRECTDRAWSURFACE * arg2) {
	DDRAW_LOG("IDirectDraw::DuplicateSurface");
	CHECK_HR_RETURN(_this->original->lpVtbl->DuplicateSurface(_this->original, arg1, arg2));
}

HRESULT __stdcall EnumDisplayModes(IDirectDraw_Wrapped *_this, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMMODESCALLBACK arg4) {
	DDRAW_LOG("IDirectDraw::EnumDisplayModes");
	original::ddrawEnumDisplayModes = arg4;
	CHECK_HR_RETURN(_this->original->lpVtbl->EnumDisplayModes(_this->original, arg1, arg2, arg3, EnumDisplayModesCallback));
}

HRESULT __stdcall EnumSurfaces(IDirectDraw_Wrapped *_this, DWORD arg1, LPDDSURFACEDESC arg2, LPVOID arg3, LPDDENUMSURFACESCALLBACK arg4) {
	DDRAW_LOG("IDirectDraw::EnumSurfaces");
	CHECK_HR_RETURN(_this->original->lpVtbl->EnumSurfaces(_this->original, arg1, arg2, arg3, arg4));
}

HRESULT __stdcall FlipToGDISurface(IDirectDraw_Wrapped *_this) {
	DDRAW_LOG("IDirectDraw::FlipToGDISurface");
	CHECK_HR_RETURN(_this->original->lpVtbl->FlipToGDISurface(_this->original));
}

HRESULT __stdcall GetCaps(IDirectDraw_Wrapped *_this, LPDDCAPS arg1, LPDDCAPS arg2) {
	DDRAW_LOG("IDirectDraw::GetCaps");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetCaps(_this->original, arg1, arg2));
}

HRESULT __stdcall GetDisplayMode(IDirectDraw_Wrapped *_this, LPDDSURFACEDESC arg1) {
	DDRAW_LOG("IDirectDraw::GetDisplayMode");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetDisplayMode(_this->original, arg1));
}

HRESULT __stdcall GetFourCCCodes(IDirectDraw_Wrapped *_this, LPDWORD arg1, LPDWORD arg2) {
	DDRAW_LOG("IDirectDraw::GetFourCCCodes");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetFourCCCodes(_this->original, arg1, arg2));
}

HRESULT __stdcall GetGDISurface(IDirectDraw_Wrapped *_this, LPDIRECTDRAWSURFACE *arg1) {
	DDRAW_LOG("IDirectDraw::GetGDISurface");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetGDISurface(_this->original, arg1));
}

HRESULT __stdcall GetMonitorFrequency(IDirectDraw_Wrapped *_this, LPDWORD arg1) {
	DDRAW_LOG("IDirectDraw::GetMonitorFrequency");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetMonitorFrequency(_this->original, arg1));
}

HRESULT __stdcall GetScanLine(IDirectDraw_Wrapped *_this, LPDWORD arg1) {
	DDRAW_LOG("IDirectDraw::GetScanLine");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetScanLine(_this->original, arg1));
}

HRESULT __stdcall GetVerticalBlankStatus(IDirectDraw_Wrapped *_this, LPBOOL arg1) {
	DDRAW_LOG("IDirectDraw::GetVerticalBlankStatus");
	CHECK_HR_RETURN(_this->original->lpVtbl->GetVerticalBlankStatus(_this->original, arg1));
}

HRESULT __stdcall Initialize(IDirectDraw_Wrapped *_this, GUID *arg1) {
	DDRAW_LOG("IDirectDraw::Initialize");
	CHECK_HR_RETURN(_this->original->lpVtbl->Initialize(_this->original, arg1));
}

HRESULT __stdcall RestoreDisplayMode(IDirectDraw_Wrapped *_this) {
	DDRAW_LOG("IDirectDraw::RestoreDisplayMode");
	CHECK_HR_RETURN(_this->original->lpVtbl->RestoreDisplayMode(_this->original));
}

HRESULT __stdcall SetCooperativeLevel(IDirectDraw_Wrapped *_this, HWND arg1, DWORD arg2) {
	// 17 = DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE
	DDRAW_LOG("IDirectDraw::SetCooperativeLevel", "value:%u", arg2);
#if FORCE_WINDOWED
	CHECK_HR_RETURN(_this->original->lpVtbl->SetCooperativeLevel(_this->original, arg1, DDSCL_NORMAL));
#else
	CHECK_HR_RETURN(_this->original->lpVtbl->SetCooperativeLevel(_this->original, arg1, arg2));
#endif
}

HRESULT __stdcall SetDisplayMode(IDirectDraw_Wrapped *_this, DWORD width, DWORD height, DWORD bpp) {
	DDRAW_LOG("IDirectDraw::SetDisplayMode", "width:%u, height:%u, bpp:%u", width, height, bpp);
	CHECK_HR_RETURN(_this->original->lpVtbl->SetDisplayMode(_this->original, width, height, bpp));
}

HRESULT __stdcall WaitForVerticalBlank(IDirectDraw_Wrapped *_this, DWORD arg1, HANDLE arg2) {
	DDRAW_LOG("IDirectDraw::WaitForVerticalBlank");
	CHECK_HR_RETURN(_this->original->lpVtbl->WaitForVerticalBlank(_this->original, arg1, arg2));
}

HRESULT WINAPI DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter) {
	DDRAW_LOG("DirectDrawCreate");
	HRESULT hr = original::DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
	if (hr) {
		Logf("HRESULT: %u\n", hr);
		return hr;
	}
#if WRAP_DDRAW
	IDirectDraw_Wrapped *dd = new IDirectDraw_Wrapped();
	dd->lpVtbl = new IDirectDrawVtbl_Wrapped();
	dd->lpVtbl->QueryInterface = ddraw::QueryInterface;
	dd->lpVtbl->AddRef = ddraw::AddRef;
	dd->lpVtbl->Release = ddraw::Release;
	dd->lpVtbl->Compact = ddraw::Compact;
	dd->lpVtbl->CreateClipper = ddraw::CreateClipper;
	dd->lpVtbl->CreatePalette = ddraw::CreatePalette;
	dd->lpVtbl->CreateSurface = ddraw::CreateSurface;
	dd->lpVtbl->DuplicateSurface = ddraw::DuplicateSurface;
	dd->lpVtbl->EnumDisplayModes = ddraw::EnumDisplayModes;
	dd->lpVtbl->EnumSurfaces = ddraw::EnumSurfaces;
	dd->lpVtbl->FlipToGDISurface = ddraw::FlipToGDISurface;
	dd->lpVtbl->GetCaps = ddraw::GetCaps;
	dd->lpVtbl->GetDisplayMode = ddraw::GetDisplayMode;
	dd->lpVtbl->GetFourCCCodes = ddraw::GetFourCCCodes;
	dd->lpVtbl->GetGDISurface = ddraw::GetGDISurface;
	dd->lpVtbl->GetMonitorFrequency = ddraw::GetMonitorFrequency;
	dd->lpVtbl->GetScanLine = ddraw::GetScanLine;
	dd->lpVtbl->GetVerticalBlankStatus = ddraw::GetVerticalBlankStatus;
	dd->lpVtbl->Initialize = ddraw::Initialize;
	dd->lpVtbl->RestoreDisplayMode = ddraw::RestoreDisplayMode;
	dd->lpVtbl->SetCooperativeLevel = ddraw::SetCooperativeLevel;
	dd->lpVtbl->SetDisplayMode = ddraw::SetDisplayMode;
	dd->lpVtbl->WaitForVerticalBlank = ddraw::WaitForVerticalBlank;
	dd->original = *lplpDD;
	*lplpDD = (LPDIRECTDRAW)dd;
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
