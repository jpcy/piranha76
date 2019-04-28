#include <stdio.h>
#include <bx/bx.h>
#include <bx/os.h>
#include "MemoryModule.h"
#include "main.h"
#include "i76.h"

void Logf(const char *_format, ...) {
	va_list args;
	va_start(args, _format);
	char buffer[2048];
	vsnprintf(buffer, sizeof(buffer), _format, args);
	va_end(args);
	printf("%s", buffer);
	OutputDebugStringA(buffer);
}

struct MsgName
{
	uint32_t id;
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

void PrintMsg(uint32_t msg) {
	for (int i = 0; i < BX_COUNTOF(s_msgNames); i++) {
		if (msg == s_msgNames[i].id) {
			Logf("%s", s_msgNames[i].name);
			return;
		}
	}
	Logf("%u", msg);
}

static HCUSTOMMODULE CustomLoadLibrary(LPCSTR _filename, void *_userData) {
	auto userData = (MemoryModuleUserData *)_userData;
#if LOG_IMPORTS
	Logf("Load library %s\n", _filename);
#endif
	Library lib;
	bx::strCopy(lib.name, sizeof(lib.name), _filename);
	lib.handle = bx::dlopen(_filename);
	userData->libraries.push_back(lib);
	return lib.handle;
}

static FARPROC CustomGetProcAddress(HCUSTOMMODULE _lib, LPCSTR _proc, void *_userData) {
	auto userData = (MemoryModuleUserData *)_userData;
	const char *libName = nullptr;
	for (const Library &lib : userData->libraries) {
		if (_lib == lib.handle) {
			libName = lib.name;
			break;
		}
	}
	for (uint32_t i = 0; i < userData->ordinalSymbols.length; i++) {
		const OrdinalSymbol &symbol = userData->ordinalSymbols.data[i];
		if (bx::strCmpI(libName, symbol.moduleName) == 0) {
			auto ordinal = *((uint32_t *)&_proc);
			if (symbol.ordinal == ordinal) {
				_proc = symbol.name;
				break;
			}
		}
	}
#if LOG_IMPORTS
	Logf("   symbol %s", _proc);
#endif
	auto result = (FARPROC)bx::dlsym(_lib, _proc);
	if (!result) {
		fprintf(stderr, "%s: failed to get symbol %s\n", libName, _proc);
		exit(1);
	}
	for (uint32_t i = 0; i < userData->wrappedFuncs.length; i++) {
		WrappedFunc &wrap = userData->wrappedFuncs.data[i];
		if (bx::strCmpI(libName, wrap.lib) == 0 && bx::strCmpI(_proc, wrap.symbol) == 0) {
			*wrap.original = result;
			result = (FARPROC)wrap.wrap;
#if LOG_IMPORTS
			Logf(" (wrapped)");
#endif
			break;
		}
	}
#if LOG_IMPORTS
	Logf("\n");
#endif
	return result;
}

static void CustomFreeLibrary(HCUSTOMMODULE _lib, void * /*_userData*/) {
	bx::dlclose(_lib);
}

HMEMORYMODULE CustomMemoryLoadLibrary(const void *_fileData, size_t _fileLength, MemoryModuleUserData *_userData) {
	return MemoryLoadLibraryEx(_fileData, _fileLength, MemoryDefaultAlloc, MemoryDefaultFree, CustomLoadLibrary, CustomGetProcAddress, CustomFreeLibrary, _userData);
}

int main(int /*argc*/, char ** /*argv*/) {
	if (!i76::Load())
		return 1;
	return 0;
}
