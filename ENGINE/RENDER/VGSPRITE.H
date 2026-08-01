#ifndef _VGSPRITE_H_
#define _VGSPRITE_H_

#include "engine\defs.h"

class PixelBuffer;

class VGSprite {

	bool _Transparent;
	const PixelBuffer* _Pixels;
  int16_t _X;
  int16_t _Y;

public:
	VGSprite(const PixelBuffer* _buff, int16_t _x = 0, int16_t _y = 0, bool _transparent = true) :
  	_Pixels(_buff), _X(_x), _Y(_y), _Transparent(_transparent) { ; }
	virtual ~VGSprite() { ; }

  void FreePixels();

  int16_t X() const { return _X; }
  VGSprite& X(int16_t _x) { _X = _x; return *this; }
  int16_t Y() const { return _Y; }
  VGSprite& Y(int16_t _y) { _Y = _y; return *this; }
  void SetPosition(int16_t _x, int16_t _y) { _X = _x; _Y = _y; }

  void Transparent(bool _transparent) { _Transparent = _transparent; }
  bool Transparent() const { return _Transparent; }

  void SetPixels(const PixelBuffer* _pixels) { _Pixels = _pixels; }
  const PixelBuffer* Pixels() const { return _Pixels; }

	virtual void Blit(PixelBuffer* _target) const;
};

#endif
