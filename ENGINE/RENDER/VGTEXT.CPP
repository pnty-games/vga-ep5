#include "engine\render\vgtext.h"

#include "engine\render\pxlbuff.h"

void VGText::Draw(PixelBuffer* _dest, int _x, int _y,
 const char* _text, byte_t _color) const {

	int dw = _dest->W();
	int cw = CellW();

  const char* str = _text;
  while (*str) {
  	DrawChar(_dest, _x, _y, *str, _color);
    _x += cw;

    if ((_x + cw) >= dw)
    	return;

		++str;
  };
}
