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


int cmd_set_threads(RXIFRM* frm, void* reb_ctx) {
	threadCount = RXA_INT32(frm, 0);
	if (threadCount < 0) threadCount = 0;
	return RXR_VALUE;
}
