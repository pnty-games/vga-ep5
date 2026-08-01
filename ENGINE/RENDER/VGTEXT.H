#ifndef _VGTEXT_H_
#define _VGTEXT_H_

#include "engine\defs.h"

class PixelBuffer;

class VGText {

public:
	virtual ~VGText() { ; }

  virtual int16_t CellW() const = 0;
  virtual int16_t CellH() const = 0;

	virtual void DrawChar(PixelBuffer* _dest, int _x, int _y, char _c,
   byte_t _color) const = 0;
  virtual void Draw(PixelBuffer* _dest, int _x, int _y,
	 const char* _text, byte_t _color) const;
};

#endif
