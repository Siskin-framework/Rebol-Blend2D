//
// Blend2D experimental Rebol extension
// ====================================
// Use on your own risc!

#include "blend2d-rebol-extension.h"

// Function for quick native experimenting
int cmd_draw_test(RXIFRM *frm, void *reb_ctx) {
	BLResult r;
	BLImageCore img;
	BLContextCore ctx;
	REBXYF size;
	REBINT w, h;
	REBSER *reb_img = 0;
	
	if (RXA_TYPE(frm, 1) == RXT_PAIR) {
		size = RXA_PAIR(frm, 1);
		w = ROUND_TO_INT(size.x);
		h = ROUND_TO_INT(size.y);
		reb_img = (REBSER *)RL_MAKE_IMAGE(w,h);
	}
	else {
		w = RXA_IMAGE_WIDTH(frm, 1);
		h = RXA_IMAGE_HEIGHT(frm, 1);
		reb_img = (REBSER *)RXA_ARG(frm,1).image;
	}
	RXA_TYPE(frm, 1) = RXT_IMAGE;
	RXA_ARG(frm, 1).width = w;
	RXA_ARG(frm, 1).height = h;
	RXA_ARG(frm, 1).image = reb_img;

	blImageInit(&img);
	r = blImageCreateFromData(&img, w, h, BL_FORMAT_PRGB32, reb_img->data, (intptr_t)w * 4, BL_DATA_ACCESS_WRITE, NULL, NULL);
	if (r != BL_SUCCESS) return r;

	r = blContextInitAs(&ctx, &img, NULL);
	if (r != BL_SUCCESS) return r;

	// now process some drawing...

	BLGradientCore gradient;
	BLLinearGradientValues values = { 0, 0, 256, 256 };
	r = blGradientInitAs(&gradient, BL_GRADIENT_TYPE_LINEAR, &values, BL_EXTEND_MODE_PAD, NULL, 0, NULL);
	if (r != BL_SUCCESS) return 1;

	blGradientAddStopRgba32(&gradient, 0.0, 0xFFFFFFFFu);
	blGradientAddStopRgba32(&gradient, 0.5, 0xFFFFAF00u);
	blGradientAddStopRgba32(&gradient, 1.0, 0xFFFF0000u);

	blContextSetFillStyle(&ctx, &gradient);
	blContextFillAll(&ctx);
	blGradientReset(&gradient);


end_ctx:

	// END ...
	blContextEnd(&ctx);
	trace("ok");

	// output to file...
	BLImageCodecCore codec;
	blImageCodecInit(&codec);
	blImageCodecFindByName(&codec, "BMP", SIZE_MAX, NULL);
	blImageWriteToFile(&img, "test.bmp", &codec);
	blImageCodecReset(&codec);

	blImageReset(&img);
	blContextReset(&ctx);
	return RXR_UNSET;
}
