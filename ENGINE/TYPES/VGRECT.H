#ifndef _VGRECT_H_
#define _VGRECT_H_

#include "engine\defs.h"

class VGRect {

	int16_t _X, _Y;
  int16_t _W, _H;

public:
	VGRect(int16_t _x = 0, int16_t _y = 0, int16_t _w = 0, int16_t _h = 0) :
   _X(_x), _Y(_y), _W(_w), _H(_h) { ; }
	virtual ~VGRect() {;}

  int16_t X() const { return _X; }
  VGRect& X(int16_t _x) { _X = _x; return *this; }
  int16_t Y() const { return _Y; }
  VGRect& Y(int16_t _y) { _Y = _y; return *this; }

  int16_t W() const { return _W; }
  VGRect& W(int16_t _w) { _W = _w; return *this; }
  int16_t H() const { return _H; }
  VGRect& H(int16_t _h) { _H = _h; return *this; }

  int16_t X0() const;
  int16_t Y0() const;
	int16_t X1() const;
  int16_t Y1() const;

  VGRect& X0(int16_t _x0);
  VGRect& Y0(int16_t _x1);
  VGRect& X1(int16_t _y0);
  VGRect& Y1(int16_t _y1);

  bool operator==(const VGRect& _r) const {
  	return _X == _r._X && _Y == _r._Y &&
		       _W == _r._W && _H == _r._H;
	}

  bool Contains(int16_t _x, int16_t _y) const;
};

#endif
