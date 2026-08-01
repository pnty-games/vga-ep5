#ifndef _BIOSTEXT_H_
#define _BIOSTEXT_H_

#include "engine\defs.h"

#include "engine\render\vgtext.h"

class VGBIOSText : public VGText {
	byte_t far* _FontData; // grab the 8x8 BIOS font from the ROMMMMM

public:
	VGBIOSText();

  virtual int16_t CellW() const { return 8; }
  virtual int16_t CellH() const { return 8; }
  virtual void DrawChar(PixelBuffer* _dest, int _x, int _y, char _c,
   byte_t _color) const;
};

#endif
