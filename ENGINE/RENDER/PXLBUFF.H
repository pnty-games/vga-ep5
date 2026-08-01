#ifndef _PXLBUFF_H_
#define _PXLBUFF_H_

#include "engine\defs.h"

class VGRect;

class PixelBuffer {

	byte_t far* _Pixels;
  int16_t _Width;
  int16_t _Height;

  bool _OwnsBuffer;

public:
	PixelBuffer(int16_t _w, int16_t _h) :
	 _Pixels(null), _Width(_w), _Height(_h), _OwnsBuffer(true)
	 { Resize(_w, _h); }
  PixelBuffer(byte_t far* _buff, int16_t _w, int16_t _h, bool _own = false) :
   _Pixels(_buff), _Width(_w), _Height(_h), _OwnsBuffer(_own) { ; }

	virtual ~PixelBuffer() {
		if (_OwnsBuffer && _Pixels != null) {
    	delete _Pixels;
      _Pixels = null;
    }
  }

  byte_t far* Pixels() { return _Pixels; }
	void FreeBuffer();

  int W() const { return _Width; }
  int H() const { return _Height; }

	void Resize(int16_t _w, int16_t _h);

  byte_t GetPixel(int16_t _x, int16_t _y) const;
  void Plot(int16_t _x, int16_t _y, byte_t _c);

  void Rect(const VGRect& _rect, byte_t _c);
  void Rect(int16_t _x, int16_t _y, int16_t _w, int16_t _h, byte_t _color);

  void Blit(int16_t _dx, int16_t _dy, PixelBuffer* _dest, bool _transparent = true) const;
  void Blit(int16_t _sx, int16_t _sy, int16_t _sw, int16_t _sh,
	 int16_t _dx, int16_t _dy, PixelBuffer* _dest, bool _transparent = true) const;
};

#endif
