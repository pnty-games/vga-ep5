#ifndef __VGSPRITE_H
#define __VGSPRITE_H

#include "engine\defs.h"

class PixelBuffer;
class Mode13h;

class VGSprite {
	PixelBuffer *_Pixels;

	int _X;
	int _Y;

public:
	VGSprite::VGSprite(int _x = 0, int _y = 0, PixelBuffer* _Pixels = null) :
	 _X(0), _Y(0), _Pixels(null) { ; }

	int X() const { return _X; }
	VGSprite& X(int32_t _x) { _X = _x; return *this; }
	int Y() const { return _Y; }
	VGSprite& Y(int32_t _y) { _Y = _y; return *this; }

	void Draw(Mode13h* _draw);
};

#endif