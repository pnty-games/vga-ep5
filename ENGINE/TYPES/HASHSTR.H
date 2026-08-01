#ifndef _HASHSTR_H_
#define _HASHSTR_H_

#include "engine\defs.h"
#include "engine\types\vgstring.h"

class VGHashString {
	VGString _String;
  uint32_t _Hash;
public:
	VGHashString() : _Hash(0) { ; }
  VGHashString(const VGString& _str) { SetString(_str); }

  const VGString& String() const { return _String; }
  uint32_t Hash() const { return _Hash; }

  void SetString(const VGString& _str) {
  	_String = _str;
    _Hash = CalculateHash(_String);
  }

  bool operator==(const VGHashString& _other) const { return _other._Hash == _Hash; }

  static uint32_t CalculateHash(const char* _str) {
		uint32_t hash = 5381;
    while (*_str) {
			hash = ((hash << 5) + hash) + *_str;
    	_str++;
    }

    return hash;
  }

  static uint32_t CalculateHash(const VGString& _str) {
  	return CalculateHash(_str.c_str());
  }
};

#endif
