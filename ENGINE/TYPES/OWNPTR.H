#ifndef _OWNPTR_H_
#define _OWNPTR_H_

#include <mem.h>

template <class T>
class VGOwnPtr {
	T* _Ptr;

public:
	VGOwnPtr(T* _ptr = null) : _Ptr(_ptr) { ; }
  ~VGOwnPtr() {
  	if (_Ptr != null) {
    	delete _Ptr;
      _Ptr = null;
    }
  }

  VGOwnPtr(VGOwnPtr& _other) : _Ptr(_other._Ptr) { _other.Release(); }

  VGOwnPtr& operator=(VGOwnPtr& _other) {
		if (this != &_other) {
    	if (_Ptr != null) delete _Ptr;
      _Ptr = _other._Ptr;
      _other.Release();
		}
		return *this;
  }

  VGOwnPtr& operator=(T* _ptr) {
  	if (_Ptr != null) delete _Ptr;
    _Ptr = _ptr;
    return *this;
	}

  T* Get() const { return _Ptr; }
  T* operator->() const { return _Ptr; }
	T& operator*() const { return *_Ptr; }

  T* Release() {
  	T* ptr =_Ptr;
    _Ptr = null;

		return ptr;
  }
};

#endif
