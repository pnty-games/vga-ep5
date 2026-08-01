#include "engine\input\vginput.h" 

#include "engine\input\keyboard.h"
#include "engine\input\inlayer.h"

VGInput::VGInput() {
	_Keyboard = new VGKeyboard(this);
}

VGInput::~VGInput() {
	delete _Keyboard;
  _Keyboard = 0;
}

void VGInput::PushLayer(VGInputLayer* _layer) {
	_InputStack.Remove(_layer);
  _InputStack.PushBack(_layer);
}

void VGInput::PopLayer(VGInputLayer* _layer) {
	if (_layer == null) {
  	_InputStack.PopBack();
  } else {
  	_InputStack.Remove(_layer);
  }
}

void VGInput::Poll() {
	_Keyboard->Poll();

  while (!_InputQueue.Empty()) {
	  uint16_t* pPackedKey = _InputQueue.PopNext();
    if (pPackedKey == null) continue;

    uint16_t packedKey = *pPackedKey;

  	for (int stackIndex = _InputStack.Num() - 1; stackIndex >= 0; --stackIndex) {
  		VGInputLayer* _layer = _InputStack[stackIndex];

	    if (_layer->React(this, packedKey)) break;
  	  if (_layer->IsOpaque()) break;
	  }
  }
}
