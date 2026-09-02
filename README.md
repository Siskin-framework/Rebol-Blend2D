[![rebol-blend2d](https://github.com/user-attachments/assets/7ad6b294-8bcb-4e2e-ab45-d34003c4cff0)](https://github.com/Siskin-framework/Rebol-Blend2D)

[![Rebol-Blend2D CI](https://github.com/Siskin-framework/Rebol-Blend2D/actions/workflows/main.yml/badge.svg)](https://github.com/Siskin-framework/Rebol-Blend2D/actions/workflows/main.yml)
[![Gitter](https://badges.gitter.im/rebol3/community.svg)](https://app.gitter.im/#/room/#Rebol3:gitter.im)
[![Zulip](https://img.shields.io/badge/zulip-join_chat-brightgreen.svg)](https://rebol.zulipchat.com/)

# Rebol/Blend2D

[Blend2D](https://github.com/blend2d/blend2d) extension for [Rebol3](https://github.com/Oldes/Rebol3) (drawing dialect)

## Usage

This extension requires Oldes' version of *Rebol* language interpreter (at least `3.22.5`),
which can be downloaded [here](https://github.com/Oldes/Rebol3/releases).
To use Blend2D's `draw` dialect, the extension must be loaded using:
```rebol
import 'blend2d
```
Once the module is imported, the new `draw` function may be used to draw into any image.
```rebol
>> help draw
USAGE:
     DRAW image commands

DESCRIPTION:
     Draws scalable vector graphics to an image.
     DRAW is a command! value.

ARGUMENTS:
     image         [image! pair!]
     commands      [block!]
```

The dialect is similar but not exactly same like the [original Rebol2 implementation](http://www.rebol.com/r3/docs/view/draw.html) or [Red language draw](https://github.com/red/docs/blob/master/en/draw.adoc).
Not all commands are implemented... it was more considered as a proof of concept.

**For some code examples, visit [test/README.md](test/README.md).**

## Building

The extension is built with the [Siskin builder](https://github.com/Siskin-framework/Builder/) using the
included `RebolBlend2D.nest` project file. The C header (`src/gen-blend2d.h`) and the command table
(`src/gen-blend2d.c`) are generated from the declarative specification in `src/blend2d.reb` by
`make-extension.r3`, which also refreshes the reference sections of this file. Do not modify the
generated sources or the reference below - modify the specification instead.

## Testing

`ci-test.r3` exercises every command, the draw dialect and the handle accessors, and exits
with a non-zero code when anything fails, so it can gate CI:

```
r3 ci-test.r3            ;; full run
r3 ci-test.r3 --quick    ;; skips the recycle loop
```

It imports the module by name, so point it at a freshly built library with
`REBOL_MODULES_DIR` (or run it from the directory holding the built `.rebx` under CI).

## Extension commands:


#### `draw` `:image` `:commands`
Draws scalable vector graphics to an image
* `image` `[image! pair!]` Target image, or a size of a new one
* `commands` `[block!]` The draw dialect

#### `path` `:commands`
Prepares path object
* `commands` `[block!]` Path dialect: move, line, curve, curv, qcurve, qcurv, arc, hline, vline, close

#### `font` `:file`
Prepares font handle
* `file` `[file! string!]` Font location or name

#### `image` `:from`
Prepares Blend2D's native image
* `from` `[pair! image! file!]` Size of a new image, an image to wrap, or a file to load

#### `info`
Returns info about Blend2D library
* `/of`
* `handle` `[handle!]` Blend2D object

#### `set-threads` `:count`
Sets number of threads to be used
* `count` `[integer!]` 0 means synchronous rendering; 1 is for async on main thread only else thread pool is used


## Used handles and its getters / setters

#### __IMAGE__ - Blend2D image (BLImage)

```rebol
;Refinement       Gets                Sets                          Description
/size             pair!               none                          "Image size in pixels"
/width            integer!            none                          "Image width in pixels"
/height           integer!            none                          "Image height in pixels"
/format           integer!            none                          "Pixel format (BLFormat value; 1 is PRGB32)"
/stride           integer!            none                          "Number of bytes between two consecutive rows"
```

#### __PATH__ - Blend2D path (BLPath)

```rebol
;Refinement       Gets                Sets                          Description
/size             integer!            none                          "Number of vertices"
/capacity         integer!            none                          "Number of vertices which fit without reallocating"
```

#### __FONT-FACE__ - Blend2D font face (BLFontFace)

```rebol
;Refinement       Gets                Sets                          Description
/glyphs           integer!            none                          "Number of glyphs the face provides"
/face-type        integer!            none                          "Face type (BLFontFaceType value)"
/outline-type     integer!            none                          "Outline type (BLFontOutlineType value)"
/revision         integer!            none                          "Face revision"
/face-index       integer!            none                          "Index of the face in a font collection"
/face-flags       integer!            none                          "Face flags (BLFontFaceFlags bit set)"
/diag-flags       integer!            none                          "Diagnostic flags (BLFontFaceDiagFlags bit set)"
```
