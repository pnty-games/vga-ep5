#ifndef __PXLBUFF_H
#define __PXLBUFF_H

#include "engine/defs.h"

class PixelBuffer {

	byte_t far* _Buffer;
	int16_t _Width;
	int16_t _Height;

	bool _ownBuffer;

public:
	PixelBuffer(int16_t _w, int16_t _h);
	PixelBuffer(byte_t far* _Buffer, int16_t _w, int16_t _h, bool own = false);

	int16_t W() const { return _Width; }
	int16_t H() const { return _Height; }


	byte_t GetPixel(int16_t _x, int16_t _y) const;

	void Clear(byte_t _c = 0);
	void Plot(int16_t _x, int16_t _y, byte_t _c);
	void Blit(int _sx, int _sy, int _sw, int _sh,
	 PixelBuffer* _dest, int _dx, int _dy);
	void Blit(int _sx, int _sy, int _sw, int _sh,
	 byte_t far* _bffer, int _dx, int _dy, int _dw, int _dh);
};

#endif