/*
  SDL2 configuration for Windows NT 4.0 + Visual Studio 4.0
*/

#ifndef SDL_config_nt4_h_
#define SDL_config_nt4_h_
#define SDL_config_h_

#include "SDL_platform.h"

/* MSVC 4.0 stdint types */
typedef signed __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#ifndef _UINTPTR_T_DEFINED
typedef unsigned int uintptr_t;
#define _UINTPTR_T_DEFINED
#endif

/* MSVC 4.0 lacks __FUNCTION__, __forceinline, __declspec(deprecated/noreturn) */
#ifndef __FUNCTION__
#define __FUNCTION__ ""
#endif
#define SDL_FORCE_INLINE static __inline
#define SDL_DEPRECATED
#define SDL_NORETURN

#define SIZEOF_VOIDP 4

/* Use C runtime */
#define HAVE_LIBC 1
#define STDC_HEADERS 1
#define HAVE_CTYPE_H 1
#define HAVE_FLOAT_H 1
#define HAVE_LIMITS_H 1
#define HAVE_MATH_H 1
#define HAVE_SIGNAL_H 1
#define HAVE_STDIO_H 1
#define HAVE_STRING_H 1

/* C library functions */
#define HAVE_MALLOC 1
#define HAVE_CALLOC 1
#define HAVE_REALLOC 1
#define HAVE_FREE 1
#define HAVE_ALLOCA 1
#define HAVE_QSORT 1
#define HAVE_BSEARCH 1
#define HAVE_ABS 1
#define HAVE_MEMSET 1
#define HAVE_MEMCPY 1
#define HAVE_MEMMOVE 1
#define HAVE_MEMCMP 1
#define HAVE_STRLEN 1
#define HAVE__STRREV 1
#define HAVE_STRCHR 1
#define HAVE_STRRCHR 1
#define HAVE_STRSTR 1
#define HAVE_STRTOL 1
#define HAVE_STRTOUL 1
#define HAVE_STRTOD 1
#define HAVE_ATOI 1
#define HAVE_ATOF 1
#define HAVE_STRCMP 1
#define HAVE_STRNCMP 1
#define HAVE__STRICMP 1
#define HAVE__STRNICMP 1
#define HAVE__WCSICMP 1
#define HAVE__WCSNICMP 1

/* Math - double versions only, MSVC 4.0 lacks float math */
#define HAVE_ACOS 1
#define HAVE_ASIN 1
#define HAVE_ATAN 1
#define HAVE_ATAN2 1
#define HAVE_CEIL 1
#define HAVE_COS 1
#define HAVE_EXP 1
#define HAVE_FABS 1
#define HAVE_FLOOR 1
#define HAVE_FMOD 1
#define HAVE_LOG 1
#define HAVE_LOG10 1
#define HAVE_POW 1
#define HAVE_SIN 1
#define HAVE_SQRT 1
#define HAVE_TAN 1
#define HAVE__COPYSIGN 1

/* Disabled subsystems */
#define SDL_AUDIO_DISABLED 1
#define SDL_JOYSTICK_DISABLED 1
#define SDL_HAPTIC_DISABLED 1
#define SDL_SENSOR_DISABLED 1
#define SDL_POWER_DISABLED 1

/* Shared object loading */
#define SDL_LOADSO_WINDOWS 1

/* Threading - use generic condition variables (NT4 lacks native ones) */
#define SDL_THREAD_GENERIC_COND_SUFFIX 1
#define SDL_THREAD_WINDOWS 1

/* Timer */
#define SDL_TIMER_WINDOWS 1

/* Video */
#define SDL_VIDEO_DRIVER_DUMMY 1
#define SDL_VIDEO_DRIVER_WINDOWS 1

/* Filesystem */
#define SDL_FILESYSTEM_WINDOWS 1

#endif /* SDL_config_nt4_h_ */
