#ifndef __VGVECTOR_H
#define __VGVECTOR_H

#include "engine\defs.h"

#include <memory.h>
#include <new.h>

template <class T>
class VGVector {
private:
	static const int InitialSize;

	T* _Data;
  int _Size;
  int _Capacity;


public:

	VGVector() : _Data(0), _Size(0), _Capacity(0) { ; }
	~VGVector() {
		delete[] _Data;
  }

  VGVector(const VGVector& _other) : _Data(0) { *this = _other; }
  VGVector operator=(const VGVector& _other) {
		_Size = _other._Size;
    _Capacity = _other._Capacity;

    if (_Data != 0) {
    	delete[] _Data;
    }
    _Data = new T[_Capacity];

    for (int i = 0; i < _Size; ++i) {
    	_Data[i] = _other._Data[i];
    }

    return *this;
  }

  int Num() const { return _Size; }
	bool Empty() const { return _Size == 0; }

  void PushBack(const T& _elem) {
   	if (_Size == _Capacity) {
    	Grow();
    }
		_Data[_Size++] = _elem;
  }

  void Insert(int _index, const T& _elem) {
  	if (_Size == _Capacity) {
    	Grow();
    }

    for (int i = _Size; i >= _index; --i) {
			_Data[i + 1] = _Data[i];
    }
    _Data[_index] = _elem;
    ++_Size;
  }

  void Remove(const T& _elem) {
  	for (int index = 0; index < _Size; ++index) {
    	if (_elem == _Data[index]) {
      	RemoveAt(index);
        return;
      }
    }
  }

  void RemoveAt(int _index) {
		for (int i = _index; (i + 1) < _Size; ++i) {
			_Data[i] = _Data[i + 1];
    }

    T& elem = _Data[_Size - 1];
    ((T*)&elem)->T::~T();

    --_Size;
  }

  T PopBack() { return _Data[--_Size]; }
  T PopFront() {
		T elem = _Data[0];
    RemoveAt(0);
    return elem;
  }

  T& Top() { return _Data[_Size - 1]; }
  const T& Top() const { return _Data[_Size - 1]; }

  T& operator[](int _index) { return _Data[_index]; }
  const T& operator[](int _index) const { return _Data[_index]; }

  void Grow() {
		int newCapacity = _Capacity == 0 ? InitialSize : (_Capacity * 2);

		T* newData = new T[newCapacity];
		for (int i = 0; i < _Size; ++i) {
			newData[i] = _Data[i];
		}
		delete[] _Data;

		_Data = newData;
		_Capacity = newCapacity;

  }

  void Clear(bool _reserve = 0) {
  	if (_Capacity == 0) {
    	return;
    }

    if (!_reserve) {
    	delete[] _Data;
      _Capacity = 0;
      _Size = 0;
      _Data = 0;
      return;
    }

    T* newData = new T[_Capacity];
    delete[] _Data;

    _Data = newData;
    _Size = 0;
  }
};

template <class T>
const int VGVector<T>::InitialSize = 4;

#endif

