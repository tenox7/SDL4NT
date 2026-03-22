/*
  NT4 compatibility stubs for SDL2
  Provides stub implementations for Win2K/XP+ APIs that don't exist on NT4.
*/
#include "../../SDL_internal.h"

#ifdef SDL_BUILD_NT4

#include "SDL_windows.h"

/* Intrinsics that MSVC 4.0 doesn't have */
void _mm_pause(void) { }
void __debugbreak(void) { __asm { int 3 } }

unsigned char _BitScanReverse(unsigned long *idx, unsigned long mask)
{
    unsigned long i;
    if (mask == 0) return 0;
    for (i = 31; i > 0; i--) {
        if (mask & (1UL << i)) { *idx = i; return 1; }
    }
    *idx = 0;
    return 1;
}

LONG __cdecl InterlockedCompareExchange(LONG volatile *dest, LONG exchange, LONG comperand)
{
    LONG ret;
    __asm {
        mov ecx, dest
        mov eax, comperand
        mov edx, exchange
        lock cmpxchg [ecx], edx
        mov ret, eax
    }
    return ret;
}

/* Multi-monitor stubs - fake single monitor */
HMONITOR MonitorFromWindow(HWND hwnd, DWORD dwFlags) { return (HMONITOR)1; }
HMONITOR MonitorFromRect(const RECT *lprc, DWORD dwFlags) { return (HMONITOR)1; }
HMONITOR MonitorFromPoint(POINT pt, DWORD dwFlags) { return (HMONITOR)1; }

BOOL GetMonitorInfoW(HMONITOR hMonitor, LPMONITORINFO lpmi)
{
    if (!lpmi) return FALSE;
    lpmi->rcMonitor.left = 0;
    lpmi->rcMonitor.top = 0;
    lpmi->rcMonitor.right = GetSystemMetrics(SM_CXSCREEN);
    lpmi->rcMonitor.bottom = GetSystemMetrics(SM_CYSCREEN);
    lpmi->rcWork = lpmi->rcMonitor;
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &lpmi->rcWork, 0);
    lpmi->dwFlags = MONITORINFOF_PRIMARY;
    if (lpmi->cbSize >= sizeof(MONITORINFOEXW)) {
        MONITORINFOEXW *lpmiex = (MONITORINFOEXW *)lpmi;
        lstrcpyW(lpmiex->szDevice, L"\\\\.\\DISPLAY1");
    }
    return TRUE;
}

BOOL GetMonitorInfo(HMONITOR hMonitor, LPMONITORINFO lpmi)
{
    return GetMonitorInfoW(hMonitor, lpmi);
}

BOOL EnumDisplayMonitors(HDC hdc, const RECT *lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData)
{
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    if (lpfnEnum) lpfnEnum((HMONITOR)1, hdc, &rc, dwData);
    return TRUE;
}

BOOL EnumDisplayDevicesW(LPCWSTR lpDevice, DWORD iDevNum, DISPLAY_DEVICEW *lpDisplayDevice, DWORD dwFlags)
{
    if (iDevNum > 0) return FALSE;
    if (!lpDisplayDevice) return FALSE;
    lpDisplayDevice->StateFlags = DISPLAY_DEVICE_ATTACHED_TO_DESKTOP | DISPLAY_DEVICE_PRIMARY_DEVICE;
    lstrcpyW(lpDisplayDevice->DeviceName, L"\\\\.\\DISPLAY1");
    lstrcpyW(lpDisplayDevice->DeviceString, L"NT4 Display");
    return TRUE;
}

LONG ChangeDisplaySettingsExW(LPCWSTR lpszDeviceName, DEVMODEW *lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
{
    return ChangeDisplaySettingsW(lpDevMode, dwflags);
}

/* Clipboard */
DWORD GetClipboardSequenceNumber(void) { return 0; }

/* Raw input stubs */
UINT GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
{
    return (UINT)-1;
}

BOOL RegisterRawInputDevices(const RAWINPUTDEVICE *pRawInputDevices, UINT uiNumDevices, UINT cbSize)
{
    return FALSE;
}

/* Mouse tracking */
BOOL TrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack) { return FALSE; }

/* Window extras */
BOOL SetLayeredWindowAttributes(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags) { return FALSE; }
BOOL FlashWindowEx(FLASHWINFO *pfwi) { return FALSE; }
BOOL GetModuleHandleExW(DWORD dwFlags, LPCWSTR lpModuleName, HMODULE *phModule) { return FALSE; }
BOOL GetModuleHandleExA(DWORD dwFlags, LPCSTR lpModuleName, HMODULE *phModule) { return FALSE; }

/* Execution state */
DWORD SetThreadExecutionState(DWORD esFlags) { return 0; }

/* Debug */
BOOL IsDebuggerPresent(void) { return FALSE; }

/* File size/pointer (64-bit) */
BOOL GetFileSizeEx(HANDLE hFile, LARGE_INTEGER *lpFileSize)
{
    DWORD lo, hi;
    lo = GetFileSize(hFile, &hi);
    if (lo == 0xFFFFFFFF && GetLastError() != NO_ERROR) return FALSE;
    lpFileSize->LowPart = lo;
    lpFileSize->HighPart = hi;
    return TRUE;
}

BOOL SetFilePointerEx(HANDLE hFile, LARGE_INTEGER liDistanceToMove, LARGE_INTEGER *lpNewFilePointer, DWORD dwMoveMethod)
{
    LONG hi = liDistanceToMove.HighPart;
    DWORD lo = SetFilePointer(hFile, liDistanceToMove.LowPart, &hi, dwMoveMethod);
    if (lo == 0xFFFFFFFF && GetLastError() != NO_ERROR) return FALSE;
    if (lpNewFilePointer) {
        lpNewFilePointer->LowPart = lo;
        lpNewFilePointer->HighPart = hi;
    }
    return TRUE;
}

/* Threading */
BOOL InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION *lpCriticalSection, DWORD dwSpinCount)
{
    InitializeCriticalSection(lpCriticalSection);
    return TRUE;
}

BOOL TryEnterCriticalSection(CRITICAL_SECTION *lpCriticalSection)
{
    EnterCriticalSection(lpCriticalSection);
    return TRUE;
}

/* COM */
HRESULT CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit)
{
    return CoInitialize(pvReserved);
}

/* Shell */
HRESULT SHGetFolderPathW(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath)
{
    UINT len;
    if (!pszPath) return E_FAIL;
    len = GetWindowsDirectoryW(pszPath, MAX_PATH);
    if (len == 0) return E_FAIL;
    return S_OK;
}

/* windowsx.h macros that might be missing */
#ifndef GET_X_LPARAM
int GET_X_LPARAM(LPARAM lp) { return (int)(short)LOWORD(lp); }
int GET_Y_LPARAM(LPARAM lp) { return (int)(short)HIWORD(lp); }
#endif

/* GetWindowLongPtr - on 32-bit, maps to GetWindowLong */
LONG GetWindowLongPtr(HWND hWnd, int nIndex)
{
    return GetWindowLongW(hWnd, nIndex);
}

LONG SetWindowLongPtr(HWND hWnd, int nIndex, LONG dwNewLong)
{
    return SetWindowLongW(hWnd, nIndex, dwNewLong);
}

/* IID_IUnknown - {00000000-0000-0000-C000-000000000046} */
static const IID local_IID_IUnknown = {0x00000000, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
const IID *_IID_IUnknown_ptr = &local_IID_IUnknown;

#endif /* SDL_BUILD_NT4 */
