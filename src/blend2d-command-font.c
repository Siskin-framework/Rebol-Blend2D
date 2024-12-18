//   ____  __   __        ______        __
//  / __ \/ /__/ /__ ___ /_  __/__ ____/ /
// / /_/ / / _  / -_|_-<_ / / / -_) __/ _ \
// \____/_/\_,_/\__/___(@)_/  \__/\__/_// /
//  ~~~ oldes.huhuman at gmail.com ~~~ /_/
//
// SPDX-License-Identifier: Apache-2.0
// =============================================================================
// Rebol/Blend2D extension commands
// =============================================================================

#include "blend2d-rebol-extension.h"

void* releaseFontFace(void* font) {
	debug_print("releasing font: %p\n", font);
	blFontFaceDestroy((BLFontFaceCore*)font);
	return NULL;
}


int cmd_font(RXIFRM* frm, void* reb_ctx) {
	BLResult ret;
	REBSER* src;
	BLFontFaceCore* face = NULL;
	 
	REBHOB* hob = RL_MAKE_HANDLE_CONTEXT(Handle_BLFontFace);

	if (hob == NULL) {
		RXA_SERIES(frm,1) = "Blend2D failed to make a font handle!";
		return RXR_ERROR;
	}
	
	src = RXA_SERIES(frm, 1);
	src = RL_ENCODE_UTF8_STRING(SERIES_DATA(src), SERIES_TAIL(src), SERIES_WIDE(src) > 1, FALSE);

	face = (BLFontFaceCore*)hob->data;
	blFontFaceInit(face);

	ret = blFontFaceCreateFromFile(face, SERIES_TEXT(src), BL_FILE_READ_MMAP_ENABLED | BL_FILE_READ_MMAP_AVOID_SMALL);
	if (ret != BL_SUCCESS) {
		debug_print("Failed to load font: %s, reason: %i\n", SERIES_DATA(src), ret);
		RXA_SERIES(frm,1) = "Blend2D's blFontFaceCreateFromFile failed!";
		return RXR_ERROR;
	}
	hob->flags |= HANDLE_CONTEXT; //@@ temp fix!
	RXA_HANDLE(frm, 1) = hob;
	RXA_HANDLE_TYPE(frm, 1) = hob->sym;
	RXA_HANDLE_FLAGS(frm, 1) = hob->flags;
	RXA_TYPE(frm, 1) = RXT_HANDLE;
	return RXR_VALUE;
}
