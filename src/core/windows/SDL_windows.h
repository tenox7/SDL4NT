/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* This is an include file for windows.h with the SDL build settings */

#ifndef _INCLUDED_WINDOWS_H
#define _INCLUDED_WINDOWS_H

#if defined(__WIN32__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef STRICT
#define STRICT 1
#endif
#ifndef UNICODE
#define UNICODE 1
#endif
#undef WINVER
#undef _WIN32_WINNT
#if defined(SDL_BUILD_NT4)
#define _WIN32_WINNT 0x0400
#elif SDL_VIDEO_RENDER_D3D12
#define _WIN32_WINNT 0xA00 /* For D3D12, 0xA00 is required */
#elif defined(HAVE_SHELLSCALINGAPI_H)
#define _WIN32_WINNT 0x603 /* For DPI support */
#else
#define _WIN32_WINNT 0x501 /* Need 0x410 for AlphaBlend() and 0x500 for EnumDisplayDevices(), 0x501 for raw input */
#endif
#define WINVER _WIN32_WINNT

#elif defined(__WINGDK__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef STRICT
#define STRICT 1
#endif
#ifndef UNICODE
#define UNICODE 1
#endif
#undef WINVER
#undef _WIN32_WINNT
#define _WIN32_WINNT 0xA00
#define WINVER       _WIN32_WINNT

#elif defined(__XBOXONE__) || defined(__XBOXSERIES__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef STRICT
#define STRICT 1
#endif
#ifndef UNICODE
#define UNICODE 1
#endif
#undef WINVER
#undef _WIN32_WINNT
#define _WIN32_WINNT 0xA00
#define WINVER       _WIN32_WINNT
#endif

/* See https://github.com/libsdl-org/SDL/pull/7607  */
/* force_align_arg_pointer attribute requires gcc >= 4.2.x.  */
#if defined(__clang__)
#define HAVE_FORCE_ALIGN_ARG_POINTER
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))
#define HAVE_FORCE_ALIGN_ARG_POINTER
#endif
#if defined(__GNUC__) && defined(__i386__) && defined(HAVE_FORCE_ALIGN_ARG_POINTER)
#define MINGW32_FORCEALIGN __attribute__((force_align_arg_pointer))
#else
#define MINGW32_FORCEALIGN
#endif

#include <windows.h>
#include <basetyps.h> /* for REFIID with broken mingw.org headers */

#ifdef SDL_BUILD_NT4
#include <ole2.h>
#ifndef UINT16
typedef unsigned short UINT16;
#endif
#ifndef UINT32
typedef unsigned int UINT32;
#endif
#ifndef INT32
typedef int INT32;
#endif
#ifndef UINT64
typedef unsigned __int64 UINT64;
#endif
#ifndef INT64
typedef __int64 INT64;
#endif
#ifndef SIZE_T
typedef unsigned long SIZE_T;
#endif
#ifndef ULONG_PTR
typedef unsigned long ULONG_PTR;
#endif
#ifndef LONG_PTR
typedef long LONG_PTR;
#endif
#ifndef ERROR_TIMEOUT
#define ERROR_TIMEOUT 1460L
#endif
#ifndef GWLP_WNDPROC
#define GWLP_WNDPROC GWL_WNDPROC
#endif
#ifndef GWLP_USERDATA
#define GWLP_USERDATA GWL_USERDATA
#endif
#ifndef GWLP_HINSTANCE
#define GWLP_HINSTANCE GWL_HINSTANCE
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif
#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wParam) ((short)HIWORD(wParam))
#endif
#ifndef WM_INPUT
#define WM_INPUT 0x00FF
#endif
#ifndef WM_XBUTTONDOWN
#define WM_XBUTTONDOWN 0x020B
#define WM_XBUTTONUP 0x020C
#define WM_XBUTTONDBLCLK 0x020D
#define XBUTTON1 0x0001
#define XBUTTON2 0x0002
#define GET_XBUTTON_WPARAM(wParam) (HIWORD(wParam))
#endif
#ifndef VK_XBUTTON1
#define VK_XBUTTON1 0x05
#define VK_XBUTTON2 0x06
#endif
#ifndef VK_MODECHANGE
#define VK_MODECHANGE 0x1F
#endif
#ifndef VK_BROWSER_BACK
#define VK_BROWSER_BACK 0xA6
#define VK_BROWSER_FORWARD 0xA7
#define VK_BROWSER_REFRESH 0xA8
#define VK_BROWSER_STOP 0xA9
#define VK_BROWSER_SEARCH 0xAA
#define VK_BROWSER_FAVORITES 0xAB
#define VK_BROWSER_HOME 0xAC
#define VK_VOLUME_MUTE 0xAD
#define VK_VOLUME_DOWN 0xAE
#define VK_VOLUME_UP 0xAF
#define VK_MEDIA_NEXT_TRACK 0xB0
#define VK_MEDIA_PREV_TRACK 0xB1
#define VK_MEDIA_STOP 0xB2
#define VK_MEDIA_PLAY_PAUSE 0xB3
#define VK_LAUNCH_MAIL 0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1 0xB6
#define VK_LAUNCH_APP2 0xB7
#endif
#ifndef MK_XBUTTON1
#define MK_XBUTTON1 0x0020
#define MK_XBUTTON2 0x0040
#endif
#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif
#ifndef WM_MOUSELEAVE
#define WM_MOUSELEAVE 0x02A3
#endif
#ifndef UNICODE_NOCHAR
#define UNICODE_NOCHAR 0xFFFF
#endif
#ifndef UINT_PTR
typedef unsigned long UINT_PTR;
typedef unsigned long DWORD_PTR;
typedef long INT_PTR;
#endif
#ifndef ICON_SMALL
#define ICON_SMALL 0
#define ICON_BIG 1
#endif
#ifndef WS_EX_NOACTIVATE
#define WS_EX_NOACTIVATE 0x08000000L
#endif
#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED 0x00080000
#endif
#ifndef LWA_ALPHA
#define LWA_ALPHA 0x00000002
#endif
#ifndef HWND_MESSAGE
#define HWND_MESSAGE ((HWND)-3)
#endif
#ifndef GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT 0x00000002
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS 0x00000004
#define GetModuleHandleEx GetModuleHandleExW
#endif
#ifndef FLASHW_STOP
typedef struct {
    UINT cbSize;
    HWND hwnd;
    DWORD dwFlags;
    UINT uCount;
    DWORD dwTimeout;
} FLASHWINFO;
#define FLASHW_STOP 0
#define FLASHW_TRAY 0x00000002
#define FLASHW_TIMERNOFG 0x0000000C
#endif
/* Redirect missing NT4 APIs to our stubs (macros only, decls below) */
#define TryEnterCriticalSection SDL_NT4_TryEnterCriticalSection
#define InterlockedCompareExchange SDL_NT4_InterlockedCompareExchange
#define TrackMouseEvent SDL_NT4_TrackMouseEvent
#define ChangeDisplaySettingsExW SDL_NT4_ChangeDisplaySettingsExW
#define CoInitializeEx SDL_NT4_CoInitializeEx

#ifndef LOCALE_SISO639LANGNAME
#define LOCALE_SISO639LANGNAME 0x00000059
#define LOCALE_SISO3166CTRYNAME 0x0000005A
#endif
#ifndef CSIDL_APPDATA
#define CSIDL_APPDATA 0x001a
#define CSIDL_FLAG_CREATE 0x8000
#endif
#ifndef COINIT_APARTMENTTHREADED
#define COINIT_APARTMENTTHREADED 0x2
#define COINIT_MULTITHREADED 0x0
#endif
#ifndef RPC_E_CHANGED_MODE
#define RPC_E_CHANGED_MODE 0x80010106L
#endif
#ifndef ES_CONTINUOUS
#define ES_CONTINUOUS 0x80000000
#define ES_DISPLAY_REQUIRED 0x00000002
#endif
#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif
#ifndef DS_SHELLFONT
#define DS_SHELLFONT (DS_SETFONT | 0x40)
#endif
#ifndef SM_CXVIRTUALSCREEN
#define SM_CXVIRTUALSCREEN 78
#define SM_CYVIRTUALSCREEN 79
#endif
#ifndef SPI_SETMOUSESPEED
#define SPI_SETMOUSESPEED 0x0071
#define SPI_GETMOUSESPEED 0x0070
#endif
#ifndef SM_REMOTESESSION
#define SM_REMOTESESSION 0x1000
#endif
#ifndef TME_LEAVE
typedef struct tagTRACKMOUSEEVENT {
    DWORD cbSize;
    DWORD dwFlags;
    HWND hwndTrack;
    DWORD dwHoverTime;
} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;
#define TME_LEAVE 0x00000002
#endif
#ifndef WH_KEYBOARD_LL
#define WH_KEYBOARD_LL 13
typedef struct tagKBDLLHOOKSTRUCT {
    DWORD vkCode;
    DWORD scanCode;
    DWORD flags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
} KBDLLHOOKSTRUCT;
#endif
typedef HANDLE HRAWINPUT;
#ifndef RID_INPUT
#define RID_INPUT 0x10000003
#endif
#ifndef RIM_TYPEMOUSE
#define RIM_TYPEMOUSE 0
#define RIM_TYPEKEYBOARD 1
#endif
#ifndef MOUSE_MOVE_RELATIVE
#define MOUSE_MOVE_RELATIVE 0
#endif
#ifndef RI_MOUSE_BUTTON_1_DOWN
#define RI_MOUSE_BUTTON_1_DOWN 0x0001
#define RI_MOUSE_BUTTON_1_UP 0x0002
#define RI_MOUSE_BUTTON_2_DOWN 0x0004
#define RI_MOUSE_BUTTON_2_UP 0x0008
#define RI_MOUSE_BUTTON_3_DOWN 0x0010
#define RI_MOUSE_BUTTON_3_UP 0x0020
#define RI_MOUSE_BUTTON_4_DOWN 0x0040
#define RI_MOUSE_BUTTON_4_UP 0x0080
#define RI_MOUSE_BUTTON_5_DOWN 0x0100
#define RI_MOUSE_BUTTON_5_UP 0x0200
#endif
#ifndef RIDEV_INPUTSINK
#define RIDEV_INPUTSINK 0x00000100
#define RIDEV_REMOVE 0x00000001
#endif
typedef struct tagRAWINPUTHEADER {
    DWORD dwType;
    DWORD dwSize;
    HANDLE hDevice;
    WPARAM wParam;
} RAWINPUTHEADER;
typedef struct tagRAWMOUSE {
    USHORT usFlags;
    union {
        ULONG ulButtons;
        struct {
            USHORT usButtonFlags;
            USHORT usButtonData;
        };
    };
    ULONG ulRawButtons;
    LONG lLastX;
    LONG lLastY;
    ULONG ulExtraInformation;
} RAWMOUSE;
typedef struct tagRAWKEYBOARD {
    USHORT MakeCode;
    USHORT Flags;
    USHORT Reserved;
    USHORT VKey;
    UINT Message;
    ULONG ExtraInformation;
} RAWKEYBOARD;
typedef struct tagRAWHID {
    DWORD dwSizeHid;
    DWORD dwCount;
    BYTE bRawData[1];
} RAWHID;
typedef struct tagRAWINPUT {
    RAWINPUTHEADER header;
    union {
        RAWMOUSE mouse;
        RAWKEYBOARD keyboard;
        RAWHID hid;
    } data;
} RAWINPUT;
typedef struct tagRAWINPUTDEVICE {
    USHORT usUsagePage;
    USHORT usUsage;
    DWORD dwFlags;
    HWND hwndTarget;
} RAWINPUTDEVICE;
#define MOUSE_VIRTUAL_DESKTOP 0x02
#define MOUSE_MOVE_ABSOLUTE 1
#ifndef MAPVK_VK_TO_VSC
#define MAPVK_VK_TO_VSC 0
#define MAPVK_VSC_TO_VK 1
#define MAPVK_VK_TO_CHAR 2
#endif
#ifndef WM_UNICHAR
#define WM_UNICHAR 0x0109
#endif
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0
#endif
#ifndef WM_GETDPISCALEDSIZE
#define WM_GETDPISCALEDSIZE 0x02E1
#endif
#ifndef WM_TOUCH
#define WM_TOUCH 0x0240
#endif
#ifndef HMONITOR
typedef HANDLE HMONITOR;
#endif
#ifndef MONITOR_DEFAULTTONEAREST
#define MONITOR_DEFAULTTONEAREST 2
#define MONITOR_DEFAULTTOPRIMARY 1
#endif
#ifndef MONITORINFOF_PRIMARY
#define MONITORINFOF_PRIMARY 1
typedef struct tagMONITORINFO {
    DWORD cbSize;
    RECT rcMonitor;
    RECT rcWork;
    DWORD dwFlags;
} MONITORINFO, *LPMONITORINFO;
typedef struct tagMONITORINFOEXW {
    DWORD cbSize;
    RECT rcMonitor;
    RECT rcWork;
    DWORD dwFlags;
    WCHAR szDevice[32];
} MONITORINFOEXW;
typedef BOOL (CALLBACK *MONITORENUMPROC)(HMONITOR, HDC, LPRECT, LPARAM);
#endif
#ifndef DISPLAY_DEVICE_ATTACHED_TO_DESKTOP
#define DISPLAY_DEVICE_ATTACHED_TO_DESKTOP 0x00000001
#define DISPLAY_DEVICE_PRIMARY_DEVICE 0x00000004
typedef struct _DISPLAY_DEVICEW {
    DWORD cb;
    WCHAR DeviceName[32];
    WCHAR DeviceString[128];
    DWORD StateFlags;
    WCHAR DeviceID[128];
    WCHAR DeviceKey[128];
} DISPLAY_DEVICEW;
#endif
#ifndef DISP_CHANGE_BADPARAM
#define DISP_CHANGE_BADPARAM -5
#endif
#ifndef ENUM_CURRENT_SETTINGS
#define ENUM_CURRENT_SETTINGS ((DWORD)-1)
#endif

BOOL SDL_NT4_TryEnterCriticalSection(CRITICAL_SECTION *);
LONG __cdecl SDL_NT4_InterlockedCompareExchange(LONG volatile *, LONG, LONG);
BOOL SDL_NT4_TrackMouseEvent(LPTRACKMOUSEEVENT);
LONG SDL_NT4_ChangeDisplaySettingsExW(LPCWSTR, DEVMODEW *, HWND, DWORD, LPVOID);
HRESULT SDL_NT4_CoInitializeEx(LPVOID, DWORD);
#endif

#include "SDL_rect.h"

/* Routines to convert from UTF8 to native Windows text */
#define WIN_StringToUTF8W(S) SDL_iconv_string("UTF-8", "UTF-16LE", (const char *)(S), (SDL_wcslen(S) + 1) * sizeof(WCHAR))
#define WIN_UTF8ToStringW(S) (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (const char *)(S), SDL_strlen(S) + 1)
/* !!! FIXME: UTF8ToString() can just be a SDL_strdup() here. */
#define WIN_StringToUTF8A(S) SDL_iconv_string("UTF-8", "ASCII", (const char *)(S), (SDL_strlen(S) + 1))
#define WIN_UTF8ToStringA(S) SDL_iconv_string("ASCII", "UTF-8", (const char *)(S), SDL_strlen(S) + 1)
#if UNICODE
#define WIN_StringToUTF8 WIN_StringToUTF8W
#define WIN_UTF8ToString WIN_UTF8ToStringW
#define SDL_tcslen       SDL_wcslen
#define SDL_tcsstr       SDL_wcsstr
#else
#define WIN_StringToUTF8 WIN_StringToUTF8A
#define WIN_UTF8ToString WIN_UTF8ToStringA
#define SDL_tcslen       SDL_strlen
#define SDL_tcsstr       SDL_strstr
#endif

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Sets an error message based on a given HRESULT */
extern int WIN_SetErrorFromHRESULT(const char *prefix, HRESULT hr);

/* Sets an error message based on GetLastError(). Always return -1. */
extern int WIN_SetError(const char *prefix);

#if !defined(__WINRT__)
/* Load a function from combase.dll */
void *WIN_LoadComBaseFunction(const char *name);
#endif

/* Wrap up the oddities of CoInitialize() into a common function. */
extern HRESULT WIN_CoInitialize(void);
extern void WIN_CoUninitialize(void);

/* Wrap up the oddities of RoInitialize() into a common function. */
extern HRESULT WIN_RoInitialize(void);
extern void WIN_RoUninitialize(void);

/* Returns true if we're running on Wine */
extern BOOL WIN_IsWine(void);

/* Returns SDL_TRUE if we're running on Windows Vista and newer */
extern BOOL WIN_IsWindowsVistaOrGreater(void);

/* Returns SDL_TRUE if we're running on Windows 7 and newer */
extern BOOL WIN_IsWindows7OrGreater(void);

/* Returns SDL_TRUE if we're running on Windows 8 and newer */
extern BOOL WIN_IsWindows8OrGreater(void);

/* You need to SDL_free() the result of this call. */
extern char *WIN_LookupAudioDeviceName(const WCHAR *name, const GUID *guid);

/* Checks to see if two GUID are the same. */
extern BOOL WIN_IsEqualGUID(const GUID *a, const GUID *b);
extern BOOL WIN_IsEqualIID(REFIID a, REFIID b);

/* Convert between SDL_rect and RECT */
extern void WIN_RECTToRect(const RECT *winrect, SDL_Rect *sdlrect);
extern void WIN_RectToRECT(const SDL_Rect *sdlrect, RECT *winrect);

/* Returns SDL_TRUE if the rect is empty */
extern BOOL WIN_IsRectEmpty(const RECT *rect);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _INCLUDED_WINDOWS_H */

/* vi: set ts=4 sw=4 expandtab: */
