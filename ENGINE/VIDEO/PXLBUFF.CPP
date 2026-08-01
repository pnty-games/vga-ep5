#include "engine\video\pxlbuff.h"

#include <mem.h>

PixelBuffer::PixelBuffer(int16_t _w, int16_t _h) :
 _Buffer(null), _Width(_w), _Height(_h), _OwnBuffer(true) {
	Resize(_w, _h);
}

PixelBuffer::PixelBuffer(byte_t far* _buffer, int16_t _w, int16_t _h, bool own) :
 _Buffer(_buffer), _Width(_w), _Height(_h), _OwnBuffer(own) {;}

byte_t PixelBuffer::GetPixel(int16_t _x, int16_t _y) const {
	if (_x < 0 || _x >= _Width ||
			_y < 0 || _y >= _Height)
		return 0;

	int32_t index = _x + ((int32_t)_y * _Width);
	return _Buffer[index];
}

void PixelBuffer::Clear(byte_t _c = 0) {
	_fmemset(_Buffer, _c, (uint32_t)_Width * _Height);
}

void PixelBuffer::Plot(int16_t _x, int16_t _y, byte_t _c) {
	if (_x < 0 || _x >= _Width ||
			_y < 0 || _y >= _Height)
		return 0;

	int32_t index = _x + ((int32_t)_y * _Width);
	_Buffer[index] = _c;
}

void PixelBuffer::Blit(int _sx, int _sy, int _sw, int _sh,
 PixelBuffer* _dest, int _dx, int _dy);
void PixelBuffer::Blit(int _sx, int _sy, int _sw, int _sh,
 byte_t far* _buffer, int _dx, int _dy, int _dw, int _dh);
