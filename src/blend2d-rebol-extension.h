//   ____  __   __        ______        __
//  / __ \/ /__/ /__ ___ /_  __/__ ____/ /
// / /_/ / / _  / -_|_-<_ / / / -_) __/ _ \
// \____/_/\_,_/\__/___(@)_/  \__/\__/_// /
//  ~~~ oldes.huhuman at gmail.com ~~~ /_/
//
// Project: Rebol/Blend2D extension
// SPDX-License-Identifier: Apache-2.0
// =============================================================================
// NOTE: auto-generated file, do not modify!

#include "blend2d-command.h"

#define MIN_REBOL_VER 3
#define MIN_REBOL_REV 10
#define MIN_REBOL_UPD 2
#define VERSION(a, b, c) (a << 16) + (b << 8) + c
#define MIN_REBOL_VERSION VERSION(MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD)

enum ext_commands {
	CMD_B2D_INIT_WORDS,
	CMD_B2D_DRAW,
	CMD_B2D_PATH,
	CMD_B2D_FONT,
	CMD_B2D_IMAGE,
	CMD_B2D_INFO,
	CMD_B2D_SET_THREADS,
};


int cmd_init_words(RXIFRM *frm, void *ctx);
int cmd_draw(RXIFRM *frm, void *ctx);
int cmd_path(RXIFRM *frm, void *ctx);
int cmd_font(RXIFRM *frm, void *ctx);
int cmd_image(RXIFRM *frm, void *ctx);
int cmd_info(RXIFRM *frm, void *ctx);
int cmd_set_threads(RXIFRM *frm, void *ctx);
enum b2d_cmd_words {W_B2D_CMD_0,
	W_B2D_CMD_MOVE,
	W_B2D_CMD_LINE,
	W_B2D_CMD_CURVE,
	W_B2D_CMD_CURV,
	W_B2D_CMD_CUBIC,
	W_B2D_CMD_QUAD,
	W_B2D_CMD_HLINE,
	W_B2D_CMD_VLINE,
	W_B2D_CMD_QCURVE,
	W_B2D_CMD_QCURV,
	W_B2D_CMD_POLYGON,
	W_B2D_CMD_SHAPE,
	W_B2D_CMD_BOX,
	W_B2D_CMD_CIRCLE,
	W_B2D_CMD_ELLIPSE,
	W_B2D_CMD_ARC,
	W_B2D_CMD_IMAGE,
	W_B2D_CMD_TEXT,
	W_B2D_CMD_FILL_ALL,
	W_B2D_CMD_CLEAR,
	W_B2D_CMD_CLEAR_ALL,
	W_B2D_CMD_POINT,
	W_B2D_CMD_POINT_SIZE,
	W_B2D_CMD_TRIANGLE,
	W_B2D_CMD_PEN,
	W_B2D_CMD_FILL,
	W_B2D_CMD_LINE_WIDTH,
	W_B2D_CMD_LINE_CAP,
	W_B2D_CMD_LINE_JOIN,
	W_B2D_CMD_ALPHA,
	W_B2D_CMD_BLEND,
	W_B2D_CMD_COMPOSITE,
	W_B2D_CMD_RESET_MATRIX,
	W_B2D_CMD_ROTATE,
	W_B2D_CMD_SCALE,
	W_B2D_CMD_TRANSLATE,
	W_B2D_CMD_CLOSE,
	W_B2D_CMD_CLIP,
	W_B2D_CMD_FONT,
	W_B2D_CMD_FILL_PEN
};
enum b2d_arg_words {W_B2D_ARG_0,
	W_B2D_ARG_PAD,
	W_B2D_ARG_TILE,
	W_B2D_ARG_FLIP,
	W_B2D_ARG_TILE_Y,
	W_B2D_ARG_FLIP_Y,
	W_B2D_ARG_TILE_X,
	W_B2D_ARG_TILE_X_FLIP_Y,
	W_B2D_ARG_FLIP_X,
	W_B2D_ARG_FLIP_X_TILE_Y,
	W_B2D_ARG_LINEAR,
	W_B2D_ARG_RADIAL,
	W_B2D_ARG_CONICAL,
	W_B2D_ARG_SOURCE_OVER,
	W_B2D_ARG_SOURCE_COPY,
	W_B2D_ARG_SOURCE_IN,
	W_B2D_ARG_SOURCE_OUT,
	W_B2D_ARG_SOURCE_ATOP,
	W_B2D_ARG_DESTINATION_OVER,
	W_B2D_ARG_DESTINATION_COPY,
	W_B2D_ARG_DESTINATION_IN,
	W_B2D_ARG_DESTINATION_OUT,
	W_B2D_ARG_DESTINATION_ATOP,
	W_B2D_ARG_XOR,
	W_B2D_ARG_CLEAR,
	W_B2D_ARG_PLUS,
	W_B2D_ARG_MINUS,
	W_B2D_ARG_MODULATE,
	W_B2D_ARG_MULTIPLY,
	W_B2D_ARG_SCREEN,
	W_B2D_ARG_OVERLAY,
	W_B2D_ARG_DARKEN,
	W_B2D_ARG_LIGHTEN,
	W_B2D_ARG_COLOR_DODGE,
	W_B2D_ARG_COLOR_BURN,
	W_B2D_ARG_LINEAR_BURN,
	W_B2D_ARG_LINEAR_LIGHT,
	W_B2D_ARG_PIN_LIGHT,
	W_B2D_ARG_HARD_LIGHT,
	W_B2D_ARG_SOFT_LIGHT,
	W_B2D_ARG_DIFFERENCE,
	W_B2D_ARG_EXCLUSION,
	W_B2D_ARG_MITER,
	W_B2D_ARG_BEVEL,
	W_B2D_ARG_ROUND,
	W_B2D_ARG_PIE,
	W_B2D_ARG_CLOSED,
	W_B2D_ARG_CHORD,
	W_B2D_ARG_SWEEP,
	W_B2D_ARG_LARGE
};

typedef int (*MyCommandPointer)(RXIFRM *frm, void *ctx);

#define B2D_EXT_INIT_CODE \
	"REBOL [Title: \"Rebol Blend2D Extension\" Name: blend2d Type: module Exports: [draw] Version: 0.11.5.0 Author: Oldes Date: 27-Nov-2024/16:19:42 License: Apache-2.0 Url: https://github.com/Siskin-framework/Rebol-Blend2D]\n"\
	"init-words: command [cmd-words [block!] arg-words [block!]]\n"\
	"draw: command [\"Draws scalable vector graphics to an image\" image [image! pair!] commands [block!]]\n"\
	"path: command [\"Prepares path object\" commands [block!]]\n"\
	"font: command [\"Prepares font handle\" file [file! string!] \"Font location or name\"]\n"\
	"image: command [\"Prepares Blend2D's native image\" from [pair! image! file!]]\n"\
	"info: command [\"Returns info about Blend2D library\" /of handle [handle!] \"Blend2D object\"]\n"\
	"set-threads: command [\"Sets number of threads to be used\" count [integer!] {0 means synchronous rendering; 1 is for async on main thread only else thread pool is used}]\n"\
	"init-words words: [move line curve curv cubic quad hline vline qcurve qcurv polygon shape box circle ellipse arc image text fill-all clear clear-all point point-size triangle pen fill line-width line-cap line-join alpha blend composite reset-matrix rotate scale translate close clip font fill-pen] [pad tile flip tile-y flip-y tile-x tile-x-flip-y flip-x flip-x-tile-y linear radial conical source-over source-copy source-in source-out source-atop destination-over destination-copy destination-in destination-out destination-atop xor clear plus minus modulate multiply screen overlay darken lighten color-dodge color-burn linear-burn linear-light pin-light hard-light soft-light difference exclusion miter bevel round pie closed chord sweep large]\n"\
	"protect/hide 'init-words\n"
