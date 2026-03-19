CFLAGS = /nologo /O2 /Zi /c /DSDL_BUILD_NT4 /Iinclude

all: SDL2_static.lib

{src}.c{}.obj:
	cl $(CFLAGS) $<

{src\stdlib}.c{}.obj:
	cl $(CFLAGS) $<

{src\cpuinfo}.c{}.obj:
	cl $(CFLAGS) $<

{src\atomic}.c{}.obj:
	cl $(CFLAGS) $<

{src\dynapi}.c{}.obj:
	cl $(CFLAGS) $<

{src\thread}.c{}.obj:
	cl $(CFLAGS) $<

{src\thread\generic}.c{}.obj:
	cl $(CFLAGS) $<

{src\thread\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\timer}.c{}.obj:
	cl $(CFLAGS) $<

{src\timer\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\file}.c{}.obj:
	cl $(CFLAGS) $<

{src\events}.c{}.obj:
	cl $(CFLAGS) $<

{src\video}.c{}.obj:
	cl $(CFLAGS) $<

{src\video\dummy}.c{}.obj:
	cl $(CFLAGS) $<

{src\video\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\core\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\render}.c{}.obj:
	cl $(CFLAGS) $<

{src\render\software}.c{}.obj:
	cl $(CFLAGS) $<

{src\loadso\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\filesystem\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\locale}.c{}.obj:
	cl $(CFLAGS) $<

{src\locale\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\misc}.c{}.obj:
	cl $(CFLAGS) $<

{src\misc\windows}.c{}.obj:
	cl $(CFLAGS) $<

{src\video\yuv2rgb}.c{}.obj:
	cl $(CFLAGS) $<

{src\libm}.c{}.obj:
	cl $(CFLAGS) $<

OBJS = \
	SDL.obj \
	SDL_assert.obj \
	SDL_error.obj \
	SDL_guid.obj \
	SDL_log.obj \
	SDL_dataqueue.obj \
	SDL_hints.obj \
	SDL_list.obj \
	SDL_utils.obj \
	SDL_getenv.obj \
	SDL_iconv.obj \
	SDL_malloc.obj \
	SDL_qsort.obj \
	SDL_stdlib.obj \
	SDL_string.obj \
	SDL_strtokr.obj \
	SDL_crc16.obj \
	SDL_crc32.obj \
	SDL_mslibc.obj \
	SDL_cpuinfo.obj \
	SDL_atomic.obj \
	SDL_spinlock.obj \
	SDL_dynapi.obj \
	SDL_thread.obj \
	SDL_syscond.obj \
	SDL_sysmutex.obj \
	SDL_syssem.obj \
	SDL_systhread.obj \
	SDL_systls.obj \
	SDL_timer.obj \
	SDL_systimer.obj \
	SDL_rwops.obj \
	SDL_events.obj \
	SDL_quit.obj \
	SDL_keyboard.obj \
	SDL_mouse.obj \
	SDL_windowevents.obj \
	SDL_clipboardevents.obj \
	SDL_dropevents.obj \
	SDL_displayevents.obj \
	SDL_gesture.obj \
	SDL_touch.obj \
	SDL_video.obj \
	SDL_blit.obj \
	SDL_blit_0.obj \
	SDL_blit_1.obj \
	SDL_blit_A.obj \
	SDL_blit_auto.obj \
	SDL_blit_copy.obj \
	SDL_blit_N.obj \
	SDL_blit_slow.obj \
	SDL_fillrect.obj \
	SDL_bmp.obj \
	SDL_pixels.obj \
	SDL_rect.obj \
	SDL_RLEaccel.obj \
	SDL_shape.obj \
	SDL_stretch.obj \
	SDL_surface.obj \
	SDL_clipboard.obj \
	SDL_yuv.obj \
	SDL_egl.obj \
	SDL_vulkan_utils.obj \
	yuv_rgb_std.obj \
	SDL_nullvideo.obj \
	SDL_nullframebuffer.obj \
	SDL_nullevents.obj \
	SDL_windowsclipboard.obj \
	SDL_windowsevents.obj \
	SDL_windowsframebuffer.obj \
	SDL_windowskeyboard.obj \
	SDL_windowsmessagebox.obj \
	SDL_windowsmodes.obj \
	SDL_windowsmouse.obj \
	SDL_windowsopengl.obj \
	SDL_windowsopengles.obj \
	SDL_windowsshape.obj \
	SDL_windowsvideo.obj \
	SDL_windowsvulkan.obj \
	SDL_windowswindow.obj \
	SDL_windows.obj \
	SDL_nt4stubs.obj \
	SDL_render.obj \
	SDL_yuv_sw.obj \
	SDL_render_sw.obj \
	SDL_blendfillrect.obj \
	SDL_blendline.obj \
	SDL_blendpoint.obj \
	SDL_drawline.obj \
	SDL_drawpoint.obj \
	SDL_rotate.obj \
	SDL_triangle.obj \
	SDL_sysloadso.obj \
	SDL_sysfilesystem.obj \
	SDL_locale.obj \
	SDL_syslocale.obj \
	SDL_url.obj \
	SDL_sysurl.obj \
	e_atan2.obj \
	e_exp.obj \
	e_fmod.obj \
	e_log.obj \
	e_log10.obj \
	e_pow.obj \
	e_rem_pio2.obj \
	e_sqrt.obj \
	k_cos.obj \
	k_rem_pio2.obj \
	k_sin.obj \
	k_tan.obj \
	s_atan.obj \
	s_copysign.obj \
	s_cos.obj \
	s_fabs.obj \
	s_floor.obj \
	s_scalbn.obj \
	s_sin.obj \
	s_tan.obj

LIBS = kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib shell32.lib advapi32.lib winmm.lib imm32.lib version.lib uuid.lib

SDL_windowskeyboard.obj: src\video\windows\SDL_windowskeyboard.c
	cl /nologo /Od /Zi /c /DSDL_BUILD_NT4 /Iinclude src\video\windows\SDL_windowskeyboard.c

SDL_blit_auto.obj: src\video\SDL_blit_auto.c
	cl $(CFLAGS) /wd4935 src\video\SDL_blit_auto.c

yuv_rgb_std.obj: src\video\yuv2rgb\yuv_rgb_std.c
	cl $(CFLAGS) /wd4615 /wd4616 src\video\yuv2rgb\yuv_rgb_std.c

SDL2.dll: $(OBJS)
	link /nologo /dll /debug /out:SDL2.dll /implib:SDL2.lib @<<
$(OBJS) $(LIBS)
<<

SDL2_static.lib: $(OBJS)
	lib /nologo /out:SDL2_static.lib @<<
$(OBJS)
<<

clean:
	-del *.obj
	-del SDL2.lib
	-del SDL2.dll
	-del SDL2.exp
	-del SDL2_static.lib
