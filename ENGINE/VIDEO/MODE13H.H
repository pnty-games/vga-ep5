#ifndef __MODE13H_H 
#define __MODE13H_H

#include "engine\defs.h"

class PixelBuffer;

class Mode13h {

	static const uint16_t _Width;
  static const uint16_t _Height;

  PixelBuffer* _Pixels;

public:

	Mode13h();
  ~Mode13h();

  uint16_t Width() const { return _Width; }
  uint16_t Height() const { return _Height; }


  PixelBuffer* Pixels() const { return _Pixels; }

  void Clear(uint8_t _color);
  void Present();

  void DrawPixel(uint16_t _x, uint16_t _y, uint8_t _c);
};

#endif