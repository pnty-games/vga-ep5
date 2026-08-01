#include "engine\video\mode13h.h" 

#include "engine\render\pxlbuff.h"

#include <alloc.h>
#include <dos.h>
#include <mem.h>

const uint16_t Mode13h::_Width = 320;
const uint16_t Mode13h::_Height = 200;

byte_t far* FrameBuffer = (byte_t far*)MK_FP(0xA000, 0x0000);
byte_t far BackBuffer[64000UL];


Mode13h::Mode13h() {

	asm {
  	mov ax, 0x13
    int 0x10
  }

  _Pixels = new PixelBuffer(BackBuffer, _Width, _Height);
}

Mode13h::~Mode13h() {
	asm {
  	mov ax, 0x03
    int 0x10
  }

  delete _Pixels;
}

void Mode13h::Clear(uint8_t _color) {
	_fmemset(BackBuffer, _color, _Width * _Height);
}

void Mode13h::Present() {
	_fmemcpy(FrameBuffer, BackBuffer, 64000UL);
}

void Mode13h::DrawPixel(uint16_t _x, uint16_t _y, uint8_t _c) {
	BackBuffer[_x + (_Width * _y)] = _c;
}