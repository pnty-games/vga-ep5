#ifndef _INLAYER_H_
#define _INLAYER_H_

#include "engine\defs.h"

#include "engine\types\hashmap.h"
#include "engine\types\vectptr.h"
#include "engine\input\inaction.h"

class VGInput;

class VGInputLayer {
	VGHashMap<uint16_t, VGVectorPtr<VGInputAction>* > _Actions;
	bool _IsOpaque;

public:
	VGInputLayer(bool _isOpaque = false) : _IsOpaque(_isOpaque) { ; }

  bool IsOpaque() const { return _IsOpaque; }
  void SetOpaque(bool _isOpaque) { _IsOpaque = _isOpaque; }

  void Bind(uint16_t _packedKey, VGOwnPtr<VGInputAction> _action);
  bool React(VGInput* _input, uint16_t _packedKey) const;
};



#endif
