#ifndef _VGPANEL_H_
#define _VGPANEL_H_

#include "engine\defs.h"

#include "engine\types\vgrect.h"
#include "engine\types\vgstring.h"
#include "engine\types\vgvector.h"

class PixelBuffer;
class VGSprite;
class VGText;

class VGPanel {

	VGString _Name;

	VGRect _Settled;
  VGRect _Defined;

  int _FillColor;
  int _LabelColor;
  VGString* _Label;
  VGSprite* _Sprite;

  VGPanel* _Parent;
	VGVector<VGPanel*> _Children;
	VGText* _Text;

  bool _Unsettled;

public:
	VGPanel(VGPanel* _parent = null) :
	 _FillColor(-1), _LabelColor(15), _Label(null), _Sprite(null),
   _Parent(_parent), _Text(null), _Unsettled(true) { ; }
	virtual ~VGPanel();

  int32_t X() const { return _Settled.X(); }
  int32_t Y() const { return _Settled.Y(); }
  int32_t W() const { return _Settled.W(); }
  int32_t H() const { return _Settled.H(); }

  void SetName(const VGString& _name) { _Name = _name; }
  void SetRect(const VGRect& _rect) { _Defined = _rect; Unsettle(); }
  void SetText(VGText* _text) { _Text = _text; }
  VGText* Text() const;

  void SetFill(int16_t _fill) { _FillColor = _fill; }
  void SetLabelColor(int16_t _color) { _LabelColor = _color; }
  void SetLabel(const char* _str) { _Label = new VGString(_str); }
  void SetSprite(VGSprite* _sprite) { _Sprite = _sprite; }

  void AddChild(VGPanel* _child);
  bool RemoveChild(VGPanel* _child);
  bool ContainsChild(VGPanel* _child);
  const VGVector<VGPanel*>& Children() const { return _Children; }

  void Unsettle(bool _includeChildren = false);
  void Settle();

	void Draw(PixelBuffer* _dest) const;
};

#endif
