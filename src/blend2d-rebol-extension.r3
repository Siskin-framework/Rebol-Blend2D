REBOL [
	title: "Blen2D module builder"
	type: module
]

commands: [
	init-words: [cmd-words [block!] arg-words [block!]]
	;--------------------------

	;draw-test: [
	;	{Draws test}
	;	image [image! pair!]
	;]
	draw: [
		{Draws scalable vector graphics to an image}
		image [image! pair!]
		commands [block!]
	]
	path: [
		{Prepares path object}
		commands [block!]
	]
	font: [
		{Prepares font handle}
		file [file! string!] {Font location or name}
	]
	image: [
		{Prepares Blend2D's native image}
		from [pair! image! file!]
	]
	info: [
		{Returns info about Blend2D library}
		/of handle [handle!] {Blend2D object}
	]
	;--------------------------
]

cmd-words: [
	;@@ order of these is important!
	move
	line
	curve
	curv
	cubic
	quad
	hline
	vline
	qcurve
	qcurv

	polygon
	shape
	box
	circle
	ellipse
	arc
	image
	text
	fill-all ; fills all context area
	clear
	clear-all
	point
	point-size
	triangle

	pen
	fill
	line-width
	line-cap
	line-join
	alpha
	blend     ; blend-mode?
	composite ; composite-mode?

	reset-matrix
	rotate
	scale
	translate
	close

	clip

	font
	;- aliases (for compatibility)
	fill-pen ; alias for `fill` 
]
arg-words: [
	;@@ order of these is important!
	;- pattern/gradient modes
	pad              ; BL_EXTEND_MODE_PAD = 0,
	tile             ; BL_EXTEND_MODE_REPEAT = 1,
	flip             ; BL_EXTEND_MODE_REFLECT = 2,
	tile-y           ; BL_EXTEND_MODE_PAD_X_REPEAT_Y = 3,
	flip-y           ; BL_EXTEND_MODE_PAD_X_REFLECT_Y = 4,
	tile-x           ; BL_EXTEND_MODE_REPEAT_X_PAD_Y = 5,
	tile-x-flip-y    ; BL_EXTEND_MODE_REPEAT_X_REFLECT_Y = 6,
	flip-x           ; BL_EXTEND_MODE_REFLECT_X_PAD_Y = 7,
	flip-x-tile-y    ; BL_EXTEND_MODE_REFLECT_X_REPEAT_Y = 8,
	;- gradient types:
	linear
	radial
	conical
	;- blend modes:
	source-over      ; BL_COMP_OP_SRC_OVER = 0,
 	source-copy      ; BL_COMP_OP_SRC_COPY = 1,
  	source-in        ; BL_COMP_OP_SRC_IN = 2,
	source-out       ; BL_COMP_OP_SRC_OUT = 3,
	source-atop      ; BL_COMP_OP_SRC_ATOP = 4,
	destination-over ; BL_COMP_OP_DST_OVER = 5,
	destination-copy ; BL_COMP_OP_DST_COPY = 6,
	destination-in   ; BL_COMP_OP_DST_IN = 7,
	destination-out  ; BL_COMP_OP_DST_OUT = 8,
	destination-atop ; BL_COMP_OP_DST_ATOP = 9,
	xor              ; BL_COMP_OP_XOR = 10,
	clear            ; BL_COMP_OP_CLEAR = 11,
	plus             ; BL_COMP_OP_PLUS = 12,
	minus            ; BL_COMP_OP_MINUS = 13,
	modulate         ; BL_COMP_OP_MODULATE = 14,
	multiply         ; BL_COMP_OP_MULTIPLY = 15,
	screen           ; BL_COMP_OP_SCREEN = 16,
	overlay          ; BL_COMP_OP_OVERLAY = 17,
	darken           ; BL_COMP_OP_DARKEN = 18,
	lighten          ; BL_COMP_OP_LIGHTEN = 19,
	color-dodge      ; BL_COMP_OP_COLOR_DODGE = 20,
	color-burn       ; BL_COMP_OP_COLOR_BURN = 21,
	linear-burn      ; BL_COMP_OP_LINEAR_BURN = 22,
	linear-light     ; BL_COMP_OP_LINEAR_LIGHT = 23,
	pin-light        ; BL_COMP_OP_PIN_LIGHT = 24,
	hard-light       ; BL_COMP_OP_HARD_LIGHT = 25,
	soft-light       ; BL_COMP_OP_SOFT_LIGHT = 26,
	difference       ; BL_COMP_OP_DIFFERENCE = 27,
	exclusion        ; BL_COMP_OP_EXCLUSION = 28,
	;- line-cap:
	miter
	bevel
	round
	;- arc types:
	pie
	closed ; same as pie
	chord
	sweep
	large
	;------------------------------


;	stroke-alignment
;	center
;	inner
;	outer

]


;-------------------------------------- ----------------------------------------
reb-code: ajoin [
	{REBOL [Title: "Rebol Blend2D Extension"}
	{ Name: blend2d Type: module Exports: [draw]}
	{ Version: 0.0.18.2}
	{ Author: Oldes}
	{ Date: } now/utc
	{ License: Apache-2.0}
	{ Url: https://github.com/Siskin-framework/Rebol-Blend2D}
	#"]"
]
enu-commands:  "" ;; command name enumerations
cmd-declares:  "" ;; command function declarations
cmd-dispatch:  "" ;; command functionm dispatcher
b2d-cmd-words: "enum b2d_cmd_words {W_B2D_CMD_0"
b2d-arg-words: "enum b2d_arg_words {W_B2D_ARG_0"

;- generate C and Rebol code from the command specifications -------------------
foreach [name spec] commands [
	append reb-code ajoin [lf name ": command "]
	new-line/all spec false
	append/only reb-code mold spec

	name: form name
	replace/all name #"-" #"_"
	
	append enu-commands ajoin ["^/^-CMD_B2D_" uppercase copy name #","]

	append cmd-declares ajoin ["^/int cmd_" name "(RXIFRM *frm, void *ctx);"]
	append cmd-dispatch ajoin ["^-cmd_" name ",^/"]
]

;- additional Rebol initialization code ----------------------------------------
foreach word cmd-words [
	word: uppercase form word
	replace/all word #"-" #"_"
	append b2d-cmd-words ajoin [",^/^-W_B2D_CMD_" word]
]
foreach word arg-words [
	word: uppercase form word
	replace/all word #"-" #"_"
	append b2d-arg-words ajoin [",^/^-W_B2D_ARG_" word]
]
append b2d-cmd-words "^/};"
append b2d-arg-words "^/};"
append reb-code ajoin [{
init-words words: } mold/flat cmd-words #" " mold/flat arg-words {
protect/hide 'init-words}
]

print reb-code

;- convert Rebol code to C-string ----------------------------------------------
init-code: copy ""
foreach line split reb-code lf [
	replace/all line #"^"" {\"}
	append init-code ajoin [{\^/^-"} line {\n"}] 
]

;-- C file templates -----------------------------------------------------------
header: {//
// auto-generated file, do not modify!
//

#include "blend2d-command.h"

#define MIN_REBOL_VER 3
#define MIN_REBOL_REV 10
#define MIN_REBOL_UPD 2
#define VERSION(a, b, c) (a << 16) + (b << 8) + c
#define MIN_REBOL_VERSION VERSION(MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD)

enum ext_commands {$enu-commands
};

$cmd-declares
$b2d-cmd-words
$b2d-arg-words

typedef int (*MyCommandPointer)(RXIFRM *frm, void *ctx);

#define B2D_EXT_INIT_CODE $init-code
}
;;------------------------------------------------------------------------------
ctable: {//
// auto-generated file, do not modify!
//
#include "blend2d-rebol-extension.h"
MyCommandPointer Command[] = {
$cmd-dispatch};
}

;- output generated files ------------------------------------------------------
write %blend2d-rebol-extension.h reword :header self
write %blend2d-commands-table.c  reword :ctable self
