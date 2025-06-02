#pragma once

#include "types.h"

EXPORTED void font_set_size__Fss(short sizeX, short sizeY);

EXPORTED void flfntSetColor__FUl(long rgba);

EXPORTED void font_print_ex__FsssPSce(short xpos, short ypos, short color, char* fmt, ...);