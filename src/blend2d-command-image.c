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

void* releaseImage(void* image) {
	debug_print("releasing image: %p\n", image);
	blImageDestroy(image);
	return NULL;
}

BLResult b2d_init_image_from_file(BLImageCore* image, REBSER* fileName) {
	BLArrayCore codecs;
	blImageCodecArrayInitBuiltInCodecs(&codecs);
	return blImageReadFromFile(image, SERIES_TEXT(fileName), &codecs);
}
BLResult b2d_init_image_from_image(BLImageCore* image, void* data, REBINT width, REBINT height) {
	return blImageCreateFromData(image, width, height, BL_FORMAT_PRGB32, data, (intptr_t)width * 4, BL_DATA_ACCESS_RW, NULL, NULL);
}

BLResult b2d_init_image_from_arg(BLImageCore* image, RXIARG arg, REBCNT type) {
	REBHOB* hob;
	switch (type) {
//	case RXT_HANDLE:
//		hob = arg.handle.ptr;
//		if (hob->sym != Handle_BLImage)
//			return BL_ERROR_INVALID_HANDLE;
//		image = (BLImageCore*)hob->data;
//		return BL_SUCCESS;
	case RXT_IMAGE:
		blImageReset(image);
		return blImageCreateFromData(image, arg.width, arg.height, BL_FORMAT_PRGB32, ((REBSER*)arg.series)->data, (intptr_t)arg.width * 4, BL_DATA_ACCESS_RW, NULL, NULL);
	case RXT_FILE:
		blImageReset(image);
		return b2d_init_image_from_file(image, (REBSER*)arg.series);
	case RXT_PAIR:
		blImageReset(image);
		return blImageCreate(image, arg.width, arg.height, BL_FORMAT_PRGB32);
	}
	return BL_ERROR_INVALID_VALUE;
}

int cmd_image(RXIFRM* frm, void* reb_ctx) {
	BLResult r;
	BLImageCore* image;
	REBHOB* hob = RL_MAKE_HANDLE_CONTEXT(Handle_BLImage);
	if (hob == NULL) {
		r = BL_ERROR_OUT_OF_MEMORY;
		goto error;
	}

	image = (BLImageCore*)hob->data;
	debug_print("New image handle: %u data: %p\n", hob->sym, hob->data);
	blImageInit(image);

	r = b2d_init_image_from_arg(image, RXA_ARG(frm, 1), RXA_TYPE(frm, 1));
	if (r != BL_SUCCESS) goto error;

	hob->flags |= HANDLE_CONTEXT; //@@ temp fix!
	RXA_HANDLE(frm, 1) = hob;
	RXA_HANDLE_TYPE(frm, 1) = hob->sym;
	RXA_HANDLE_FLAGS(frm, 1) = hob->flags;
	RXA_TYPE(frm, 1) = RXT_HANDLE;
	return RXR_VALUE;

error:
	RXA_SERIES(frm,1) = "Blend2D failed to make an image handle!";
	return RXR_ERROR;

}