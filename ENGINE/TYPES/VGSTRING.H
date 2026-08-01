#ifndef __VGSTRING_H
#define __VGSTRING_H

#include "engine\defs.h"


class VGString {
private:

	int _Length;
  int _Capacity;
  char* _String;

  void Grow();
  void Realloc(int _capacity);

public:

	VGString() : _String(0), _Length(0), _Capacity(0) { }
  VGString(const char* _string);
  VGString(const VGString& _string);
  ~VGString();

  const char* c_str() const { return _String; }
	int Length() const { return _Length; }

  char operator[](int _index) const;
  char& operator[](int _index);

  VGString& operator=(const VGString& _other);
  VGString& operator=(const char* _string);

  VGString& operator+=(const VGString& _other);
  VGString& operator+=(const char* _string);

  VGString operator+(const VGString& _other) const;
  VGString operator+(const char* _other) const;

  bool operator==(const VGString& _other) const;
  bool operator==(const char* _string) const;

};

#endif
