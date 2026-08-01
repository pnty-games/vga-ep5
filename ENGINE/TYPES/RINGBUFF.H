#ifndef _RINGBUFF_H_
#define _RINGBUFF_H_

#include "engine\defs.h"

template <class T>
class VGRingBuffer {
	volatile int16_t _Head;
  volatile int16_t _Tail;
  volatile T* _Buffer;

  uint16_t _Mask;

public:
	VGRingBuffer(uint16_t _bufferSize = 32) :
   _Buffer(new T[_bufferSize]), _Head(0), _Tail(0) {
		_Mask = _bufferSize - 1;
  }
	~VGRingBuffer() { delete [] (T*)_Buffer; }

  void Push(const T& _elem) {
  	if (((_Tail + 1) & _Mask) == _Head) return; // full
    _Buffer[_Tail] = _elem;
    _Tail = (_Tail + 1) & _Mask;
  }

  T* PopNext() {
  	if (_Head == _Tail) return null; // empty
    volatile T* elem = &_Buffer[_Head];
    _Head = (_Head + 1) & _Mask;
    return (T*)elem;
  }

  T* At(uint16_t _index) const {
    volatile T* elem = &_Buffer[(_Head + _index) & _Mask];
    return (T*)elem;
  }

  int Num() const {
  	uint16_t count = 0;
    for (uint16_t curr = _Head; curr != _Tail; curr = (curr + 1) & _Mask)
    	++count;
    return count;
  }

  bool Empty() const { return _Head == _Tail; }
};

#endif
