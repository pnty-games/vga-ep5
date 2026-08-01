#include "engine\ui\vgpanel.h"

#include "engine\render\vgtext.h"
#include "engine\render\pxlbuff.h"
#include "engine\render\vgsprite.h"

#include <dos.h>

VGPanel::~VGPanel() {
	if (_Label != null) {
  	delete _Label;
    _Label = null;
  }
}

VGText* VGPanel::Text() const {
	if (_Text != null) {
  	return _Text;
  }

  //todo: get default BIOStext from UI
  return null;
}

bool VGPanel::ContainsChild(VGPanel* _child) {
  // check if we're above the child
	VGPanel* iter = _child->_Parent;
  while (iter != null) {
  	if (iter == this) {
    	return true;
    }
    iter = iter->_Parent;
  }

  // check if the child is above us
  iter = _Parent;
  while (iter != null) {
  	if (iter == _child) {
    	return true;
    }
    iter = iter->_Parent;
  }

  return false;
}

void VGPanel::AddChild(VGPanel* _child) {
	if (ContainsChild(_child)) {
	  return;
  }

  _Children.PushBack(_child);
  _child->_Parent = this;
	Unsettle();
  _child->Unsettle();
}

bool VGPanel::RemoveChild(VGPanel* _child) {
	for (int i = 0, num = _Children.Num(); i < num; ++i) {
   	VGPanel* child = _Children[i];
    if (child == _child) {
    	_Children.RemoveAt(i);
      return true;
    }
    return child->RemoveChild(_child);
  }

  return false;
}

void VGPanel::Settle() {
	if (!_Unsettled) {
		return;
  }
  _Unsettled = false;

	int x = _Defined.X();
  int y = _Defined.Y();

  if (_Parent != null) {
  	_Parent->Settle();

    x += _Parent->X();
    y += _Parent->Y();
  }

  _Settled.X(x).Y(y).W(_Defined.W()).H(_Defined.H());
}

void VGPanel::Unsettle(bool _includeChildren) {
	_Unsettled = true;

  if (_includeChildren) {
	  for (int32_t childIndex = 0, num = _Children.Num(); childIndex < num; ++childIndex) {
  		VGPanel* child = _Children[childIndex];
      child->Unsettle(true);
    }
  }
}

void VGPanel::Draw(PixelBuffer* _dest) const {
	int x = X();
  int y = Y();

  if (_FillColor >= 0) {
  	_dest->Rect(_Settled, _FillColor);
  }

  if (_Sprite != null) {
  	_Sprite->X(x).Y(y);
  	_Sprite->Blit(_dest);
  }

  if (_Label != null) {
   	VGText* _text = Text();
    if (_text != null) {
    	_text->Draw(_dest, x, y, _Label->c_str(), _LabelColor);
    }
  }

  for (int32_t childIndex = 0, num = _Children.Num(); childIndex < num; ++childIndex) {
  	VGPanel* child = _Children[childIndex];
		child->Draw(_dest);
	}
}
