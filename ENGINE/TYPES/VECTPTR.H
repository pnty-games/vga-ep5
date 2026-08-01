#ifndef _VECTPTR_H_
#define _VECTPTR_H_

#include "engine\defs.h"
#include "engine\types\ownptr.h"


template <class T>
class VGVectorPtr {
	static const int InitialSize;
private:

	VGOwnPtr<T>* _Data;
  int _Size;
  int _Capacity;

public:
  VGVectorPtr() : _Data(null), _Size(0), _Capacity(0) { ; }
  ~VGVectorPtr() {
  	delete[] _Data;
  }

  int Num() const { return _Size; }
  bool Empty() const { return _Size == 0; }

  // We take ownership of the pointer on push
  void PushBack(VGOwnPtr<T> _elem) {
  	if (_Size == _Capacity) {
    	Grow();
    }
		_Data[_Size++] = _elem;
  }

  void RemoveAt(int _index) {
  	for (int i = _index; (i + 1) < _Size; ++i)
    	_Data[i] = _Data[i + 1];

    --_Size;
  }

  T* operator[](int _index) const {
  	return _Data[_index].Get();
  }

  void Grow() {
  	int newCapacity = _Capacity == 0 ? InitialSize : (_Capacity * 2);

    VGOwnPtr<T>* newData = new VGOwnPtr<T>[newCapacity];
    for (int i = 0; i < _Size; ++i)
			newData[i] = _Data[i];
    delete[] _Data;

		_Data = newData;
		_Capacity = newCapacity;
	}

  void Clear() {
  	if (_Capacity == 0) return;

    delete[] _Data;
    _Data = 0;
    _Size = 0;
    _Capacity = 0;
  }
};

template <class T>
const int VGVectorPtr<T>::InitialSize = 4;

#endif
