[![rebol-blend2d](https://github.com/user-attachments/assets/7ad6b294-8bcb-4e2e-ab45-d34003c4cff0)](https://github.com/Siskin-framework/Rebol-Blend2D)

[![Rebol-Blend2D CI](https://github.com/Siskin-framework/Rebol-Blend2D/actions/workflows/main.yml/badge.svg)](https://github.com/Siskin-framework/Rebol-Blend2D/actions/workflows/main.yml)
[![Gitter](https://badges.gitter.im/rebol3/community.svg)](https://app.gitter.im/#/room/#Rebol3:gitter.im)
[![Zulip](https://img.shields.io/badge/zulip-join_chat-brightgreen.svg)](https://rebol.zulipchat.com/)

# Rebol/Blend2D

[Blend2D](https://github.com/blend2d/blend2d) extension for [Rebol3](https://github.com/Siskin-framework/Rebol) (drawing dialect)

## Usage

This extension requires Oldes' version of *Rebol* language interpreter, which can be downloaded [here](https://github.com/Siskin-framework/Rebol/releases).
To use Bland2D's `draw` dialect, the extension must be loaded using:
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
