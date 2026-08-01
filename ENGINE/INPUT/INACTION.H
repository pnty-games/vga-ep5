#ifndef _INACTION_H_
#define _INACTION_H_

#include "engine\defs.h"
#include "engine\types\hashstr.h"

class VGInput;

class VGInputAction {
  VGInput* _Input;
  uint16_t _PackedKey;

protected:
	uint16_t Action() const { return _PackedKey; }

public:
  VGInputAction() : _Input(null) { ; }
  virtual ~VGInputAction() { ; }

  void Setup(VGInput* _input, uint16_t _packed) {
		_Input = _input; _PackedKey = _packed;
  }

  virtual bool React() = 0;
};

#endif
