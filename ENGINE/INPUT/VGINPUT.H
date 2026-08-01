#ifndef __VGINPUT_H 
#define __VGINPUT_H

#include "engine\defs.h"

#include "engine\types\ringbuff.h"
#include "engine\types\vgvector.h"

class VGKeyboard;
class VGInputLayer;

class VGInput {
private:

	VGRingBuffer<uint16_t> _InputQueue;
	VGVector<VGInputLayer*> _InputStack;
	VGKeyboard* _Keyboard;

public:
	VGInput();
  ~VGInput();

  VGKeyboard* GetKeyboard() { return _Keyboard; }
	VGRingBuffer<uint16_t>& InputQueue() { return _InputQueue; }

  void PushLayer(VGInputLayer* _layer);
  void PopLayer(VGInputLayer* _layer);

  void Poll();
};


#endif