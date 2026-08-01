#include "engine\types\vgstring.h"

#include <alloc.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream.h>

VGString::VGString(const char* _string):
	_Capacity(0), _Length(0), _String(0) {
  int newLength = (int)strlen(_string);
  if (newLength > 0) {
	  Realloc(newLength + 1);
  	_fmemcpy(_String, _string, newLength);

		_Length = newLength;
  	_String[_Length] = '\0';
  }
}

VGString::VGString(const VGString& _string) :
	_Capacity(0), _Length(0), _String(0) {
	if (_string._Capacity > 0) {
	  Realloc(_string._Capacity);
	  _fmemcpy(_String, _string._String, _string._Length);

	  _Length = _string._Length;
  	_String[_Length] = '\0';
  }
}

VGString::~VGString() {
	if (_String != 0) {
  	farfree(_String);
  }
}

void VGString::Grow() {
	Realloc(_Capacity == 0 ? 4 : _Capacity * 2);
}

void VGString::Realloc(int _capacity) {
  int oldCapacity = _Capacity;
	_Capacity = _capacity == -1 ? _Capacity : _capacity;

  char far* newData = (char far*)farmalloc(_Capacity);

  if (_String != 0) {
	  _fmemcpy(newData, _String, vmin(oldCapacity, _Capacity));
		farfree(_String);
  }

  _String = newData;
  _String[_Length] = 0;
}

char VGString::operator[](int _index) const {
	return *(_String + _index);
}

char& VGString::operator[](int _index) {
	return *(_String + _index);
}

VGString& VGString::operator=(const VGString& _other) {
	_Length = _other._Length;
  _Capacity = _other._Capacity;

  if (_String != 0) {
	  farfree(_String);
  }

  if (_Capacity > 0) {
	  _String = (char far*)farmalloc(_Capacity);
  	_fmemcpy(_String, _other._String, _other._Capacity);
  } else {
  	_String = 0;
  }

  return *this;
}

VGString& VGString::operator=(const char* _string) {
	return *this = VGString(_string);
}

VGString& VGString::operator+=(const VGString& _other) {
	int newLength = _Length + _other._Length;
  int newCapacity = newLength + 1;

  if (_Capacity < newCapacity) {
  	Realloc(newCapacity);
  }

	_fmemcpy(&(_String[_Length]), _other._String, _other._Length);
	_Length = newLength;
	_String[_Length] = '\0';

  return *this;
}

VGString& VGString::operator+=(const char* _string) {
	return *this += VGString(_string);
}

VGString VGString::operator+(const VGString& _other) const {
	VGString newString(*this);
	newString += _other;
	return newString;
}

VGString VGString::operator+(const char* _other) const {
	return *this + VGString(_other);
}

bool VGString::operator==(const VGString& _other) const {
	const char* ostring = _other._String;
  return (strcmp(ostring, _String) == 0);
}

bool VGString::operator==(const char* _string) const {
	return (strcmp(_string, _String) == 0);
}

