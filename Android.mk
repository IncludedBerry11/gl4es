LOCAL_PATH := $(call my-dir)

###########################
#
# GL static library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := gl4es_117_ptitseb

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES) -DBCMHOST

LOCAL_SRC_FILES := \
	src/gl/arbconverter.c \
	src/gl/arbgenerator.c \
	src/gl/arbhelper.c \
	src/gl/arbparser.c \
	src/gl/array.c \
	src/gl/blend.c \
	src/gl/blit.c \
	src/gl/buffers.c \
	src/gl/build_info.c \
	src/gl/debug.c \
	src/gl/decompress.c \
	src/gl/depth.c \
	src/gl/directstate.c \
	src/gl/drawing.c \
	src/gl/enable.c \
	src/gl/envvars.c \
	src/gl/eval.c \
	src/gl/face.c \
	src/gl/fog.c \
	src/gl/fpe.c \
	src/gl/fpe_cache.c \
	src/gl/fpe_shader.c \
	src/gl/framebuffers.c \
	src/gl/gl_lookup.c \
	src/gl/getter.c \
	src/gl/gl4es.c \
	src/gl/glstate.c \
	src/gl/hint.c \
	src/gl/init.c \
	src/gl/light.c \
	src/gl/line.c \
	src/gl/list.c \
	src/gl/listdraw.c \
	src/gl/listrl.c \
	src/gl/loader.c \
	src/gl/logs.c \
	src/gl/matrix.c \
	src/gl/matvec.c \
	src/gl/oldprogram.c \
	src/gl/pixel.c \
	src/gl/planes.c \
	src/gl/pointsprite.c \
	src/gl/preproc.c \
	src/gl/program.c \
	src/gl/queries.c \
	src/gl/raster.c \
	src/gl/render.c \
	src/gl/samplers.c \
	src/gl/shader.c \
	src/gl/shaderconv.c \
	src/gl/shader_hacks.c \
	src/gl/stack.c \
	src/gl/stencil.c \
	src/gl/string_utils.c \
	src/gl/stubs.c \
	src/gl/texenv.c \
	src/gl/texgen.c \
	src/gl/texture.c \
	src/gl/texture_compressed.c \
	src/gl/texture_params.c \
	src/gl/texture_read.c \
	src/gl/texture_3d.c \
	src/gl/uniform.c \
	src/gl/vertexattrib.c \
	src/gl/wrap/gl4eswraps.c \
	src/gl/wrap/gles.c \
	src/gl/wrap/glstub.c \
	src/gl/math/matheval.c \
	src/egl/egl.c \
	src/glx/glx_stubs.c \
	src/glx/rpi.c \
	src/glx/utils.c \
        src/egl/lookup.c \
	src/glx/hardext.c \
	src/glx/glx.c \
	src/glx/lookup.c \
	src/glx/gbm.c \
	src/glx/streaming.c \
        src/gl/libtxc_dxtn/txc_compress_dxtn.c

LOCAL_CFLAGS += -DANDROID -pipe -integrated-as -fno-plt -O3 -flto-thin -mllvm -polly -mllvm -polly-vectorizer=stripmine -mllvm -polly-invariant-load-hoisting -mllvm -polly-run-inliner -mllvm -polly-run-dce -std=gnu17 -funwind-tables -O3 -fvisibility=hidden -include include/android_debug.h
LOCAL_CFLAGS += -DNOX11
LOCAL_CFLAGS += -DNO_GBM
LOCAL_CFLAGS += -DUSE_ANDROID_LOG=1
LOCAL_CFLAGS += -DNO_INIT_CONSTRUCTOR
LOCAL_CFLAGS += -DNOEGL=ON
LOCAL_CFLAGS += -DNO_LOADER=ON
LOCAL_CFLAGS += -DDEFAULT_ES=3
//TODO: maybe temporary?
LOCAL_CFLAGS += -Wno-typedef-redefinition -Wno-dangling-else
LOCAL_CFLAGS += -Dasm=__asm__ -Dvolatile=__volatile__
LOCAL_CFLAGS += -include include/gl4esinit.h

LOCAL_LDLIBS := -ldl -llog -landroid -lEGL -lGLESv2 -lGLESv3
#building as a static lib

LOCAL_CFLAGS += -DSHAREDLIB
include $(BUILD_SHARED_LIBRARY)
