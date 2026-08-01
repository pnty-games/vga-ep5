#include "engine\render\vgsprite.h"

#include "engine\render\pxlbuff.h"

void VGSprite::FreePixels() {
	if (_Pixels == null)
  	return;

  delete _Pixels;
}

void VGSprite::Blit(PixelBuffer* _target) const {
	if (_Pixels == null) return;

  _Pixels->Blit(_X, _Y, _target, _Transparent);
}
