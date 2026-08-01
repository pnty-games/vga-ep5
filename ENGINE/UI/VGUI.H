#ifndef _VGUI_H_
#define _VGUI_H_

#include "engine\defs.h"

#include "engine\types\vgvector.h"

class VGPanel;
class PixelBuffer;

class VGUI {

	VGVector<VGPanel*> _Panels;
  VGVector<VGPanel*> _Roots;

  bool _Regenerate;

public:
	VGUI() : _Regenerate(false) {;}

  void Init();
  void Render(PixelBuffer* _dest);
	void PostTick();

  void Regenerate();

  void AddRoot(VGPanel* _root);

};

#endif
