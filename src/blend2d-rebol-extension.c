//
// Blend2D experimental Rebol extension
// ====================================
// Use on your own risc!

#include "blend2d-rebol-extension.h"

#ifndef BL_BUILD_STATIC
#pragma comment(lib,"blend2d.lib")
#endif

RL_LIB *RL; // Link back to reb-lib from embedded extensions

//==== Globals ===============================================================//
u32*   b2d_cmd_words;
u32*   b2d_arg_words;
REBCNT Handle_BLPath;
REBCNT Handle_BLFontFace;
REBCNT Handle_BLImage;

REBDEC doubles[DOUBLE_BUFFER_SIZE];
RXIARG arg[ARG_BUFFER_SIZE];

extern MyCommandPointer Command[];            // in blend2d-rebol-extension.c //
//============================================================================//


static const char* init_block = B2D_EXT_INIT_CODE;

int cmd_init_words(RXIFRM *frm, void *ctx) {
	b2d_cmd_words = RL_MAP_WORDS(RXA_SERIES(frm,1));
	b2d_arg_words = RL_MAP_WORDS(RXA_SERIES(frm,2));
	return RXR_TRUE;
}

RXIEXT const char *RX_Init(int opts, RL_LIB *lib) {
    RL = lib;
	REBYTE ver[8];
	RL_VERSION(ver);
	debug_print("RXinit b2d; Rebol v%i.%i.%i\n", ver[1], ver[2], ver[3]);

	if (MIN_REBOL_VERSION > VERSION(ver[1], ver[2], ver[3])) {
		debug_print("Needs at least Rebol v%i.%i.%i!\n", MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD);
		return 0;
	}
    if (!CHECK_STRUCT_ALIGN) {
    	trace("CHECK_STRUCT_ALIGN failed!");
    	return 0;
    }
	Handle_BLPath     = RL_REGISTER_HANDLE(b_cast("BLPath"), sizeof(BLPathCore), releasePath);
	Handle_BLFontFace = RL_REGISTER_HANDLE(b_cast("BLFontFace"), sizeof(BLFontFaceCore), releaseFontFace);
	Handle_BLImage    = RL_REGISTER_HANDLE(b_cast("BLImage"), sizeof(BLImageCore), releaseImage);
    return init_block;
}

RXIEXT int RX_Call(int cmd, RXIFRM *frm, void *ctx) {
	return Command[cmd](frm, ctx);
}

RXIEXT int RX_Quit(int opts) {
    return 0;
}
