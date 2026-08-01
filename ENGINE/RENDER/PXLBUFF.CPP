#include "engine\render\pxlbuff.h"

#include "engine\types\vgrect.h"

#include <alloc.h>
#include <mem.h>

void PixelBuffer::FreeBuffer() {
	if (!_OwnsBuffer || _Pixels == null) {
  	return;
  }

  farfree(_Pixels);
  _Pixels = null;
}

void PixelBuffer::Resize(int16_t _w, int16_t _h) {
	if (!_OwnsBuffer) {
  	return;
  }

  byte_t far* newBuffer = (byte_t far*)farmalloc((int32_t)_w * _h);
  if (newBuffer == null) {
  	// TODO: Logger Log this
  	return;
  }

  if (_Pixels != null) {
		int32_t w = vmin(_w, _Width);
    int32_t h = vmin(_h, _Height);

    if (w == _Width) {
    	_fmemcpy(newBuffer, _Pixels, w * h);
    } else {
    	for (int row = 0; row < h; ++row) {
      	_fmemcpy(newBuffer, _Pixels + (row * w), w);
      }
    }

    delete _Pixels;
  }

	_Pixels = newBuffer;
}

byte_t PixelBuffer::GetPixel(int16_t _x, int16_t _y) const {
  if (_x < 0 || _x >= _Width ||
      _y < 0 || _y >= _Height) {
  	return 0;
  }

	int32_t index = _x + (int32_t)_y * _Width;
  return _Pixels[index];
}

void PixelBuffer::Plot(int16_t _x, int16_t _y, byte_t _c) {
  if (_x < 0 || _x >= _Width ||
      _y < 0 || _y >= _Height) {
  	return;
  }

	int32_t index = _x + (int32_t)_y * _Width;
	_Pixels[index] = _c;
}

void PixelBuffer::Rect(const VGRect& _rect, byte_t _c) {
	Rect(_rect.X(), _rect.Y(), _rect.W(), _rect.H(), _c);
}

void PixelBuffer::Rect(int16_t _x, int16_t _y, int16_t _w, int16_t _h, byte_t _color) {
  if ((_x + _w) >= _Width) {
  	_w = _Width - _x;
  }

  if ((_y + _h) >= _Height) {
  	_h = _Height - _y;
  }

	for (int row = 0; row < _h; ++row) {
    uint32_t index = _x + ((uint32_t)_Width * (_y + row));
  	_fmemset(&_Pixels[index], _color, _w);
  }
}


void PixelBuffer::Blit(int16_t _dx, int16_t _dy,
 PixelBuffer* _dest, bool _transparent) const {
	Blit(0, 0, _Width, _Height, _dx, _dy, _dest, _transparent);
}

void PixelBuffer::Blit(int16_t _sx, int16_t _sy, int16_t _sw, int16_t _sh,
	 int16_t _dx, int16_t _dy, PixelBuffer* _dest, bool _transparent) const {

  int dw = _dest->W();
  int dh = _dest->H();
  byte_t far* dest = _dest->_Pixels;

  for (int row = 0; row < _sh; ++row) {
		int sy = _sy + row;
    int dy = _dy + row;
    if (dy < 0 || dy >= dh)
    	continue;

    for (int col = 0; col < _sw; ++col) {
			int sx = _sx + col;
      int dx = _dx + col;
      if (dx < 0 || dx >= dw)
      	continue;

      uint32_t si = (uint32_t)sy * _Width + sx;
      byte_t pixel = _Pixels[si];

      if (!_transparent || pixel != 0) {
      	uint32_t di = (uint32_t)dy * dw + dx;
        dest[di] = pixel;
			}
    }
  }
}
