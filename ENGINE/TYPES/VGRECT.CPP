#include "engine\types\vgrect.h"

#include <stdlib.h>

int16_t VGRect::X0() const { return _X; }
int16_t VGRect::Y0() const { return _Y; }
int16_t VGRect::X1() const { return _X + _W; }
int16_t VGRect::Y1() const { return _Y + _H; }

VGRect& VGRect::X0(int16_t _x0) {
	int16_t x1 = X1(); _X = vmin(_x0, x1);
  W(abs(x1 - _x0));
  return *this;
}
VGRect& VGRect::Y0(int16_t _y0) {
	int16_t y1 = Y1(); _Y = vmin(_y0, y1);
  H(abs(y1 - _y0));
  return *this;
}

VGRect& VGRect::X1(int16_t _x1) {
	int16_t x0 = X0(); _X = vmin(x0, _x1);
  W(abs(_x1 - x0));
  return *this;
}

VGRect& VGRect::Y1(int16_t _y1) {
	int16_t y0 = Y0(); _Y = vmin(y0, _y1);
  H(abs(_y1 - y0));
  return *this;
}

bool VGRect::Contains(int16_t _x, int16_t _y) const {
  return (_x >= _X && _x < _X + _W) &&
         (_y >= _Y && _y < _Y + _H);
}
