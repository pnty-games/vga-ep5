#include "engine\render\biostext.h"

#include "engine\render\pxlbuff.h"

#include <dos.h>

VGBIOSText::VGBIOSText() {
	struct REGPACK regs;
  regs.r_ax = 0x1130;
  regs.r_bx = 0x0300;
  intr(0x10, &regs);

  uint16_t segment = regs.r_es;
  uint16_t offset = regs.r_bp;

	_FontData = (byte_t far*)MK_FP(segment, offset);
}

void VGBIOSText::DrawChar(PixelBuffer* _dest, int _x, int _y, char _c,
 byte_t _color) const {
	byte_t far* glyph = _FontData + (_c * 8);

  for (int row = 0; row < 8; ++row) {
  	byte_t bits = glyph[row];
    for (int col = 0; col < 8; ++col) {
			if (bits & (0x80 >> col)) {
      	_dest->Plot(_x + col, _y + row, _color);
      }
    }
  }
}
