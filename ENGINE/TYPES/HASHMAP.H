#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "engine\defs.h"
#include "engine\types\hashstr.h"

#define HashMapThreshold (0.75f)

template <class TKey, class TValue>
class VGHashMap {

	struct BucketEntry {
		uint32_t HashKey;
    TValue Value;
    BucketEntry* Next;

    BucketEntry(uint32_t _k, const TValue& _v, BucketEntry* _n = null) :
     HashKey(_k), Value(_v), Next(_n) { ; }
  };

	uint16_t _Size;
  uint16_t _BucketCount;
  BucketEntry** _Buckets;

  typedef void(*ValueDeleter)(TValue);
  ValueDeleter _Deleter;

  // * * * * * * *
	// GetIndex
  // * * * * * * *

  int GetIndex(const VGHashString& _str, uint32_t* _ptrHash) const {
		uint32_t hash = _str.Hash();
    if (_ptrHash != null) *_ptrHash = hash;
    return hash % _BucketCount;
  }

	int GetIndex(const VGString& _str, uint32_t* _ptrHash) const {
		uint32_t hash = VGHashString::CalculateHash(_str);
  	if (_ptrHash != null) *_ptrHash = hash;
	  return hash % _BucketCount;
  }

  int GetIndex(const char* _str, uint32_t* _ptrHash) const {
		uint32_t hash = VGHashString::CalculateHash(_str);
  	if (_ptrHash != null) *_ptrHash = hash;
	  return hash % _BucketCount;
  }

  int GetIndex(int _k, uint32_t* _ptrHash) const {
		uint32_t hash = (uint32_t)(_k ^ (_k >> 8));
  	if (_ptrHash != null) *_ptrHash = hash;
	  return hash % _BucketCount;
  }


  // * * * * * * *

  void SetValue(uint32_t _hash, int _bucket, const TValue& _val) {
  	BucketEntry* bucket = _Buckets[_bucket];
    BucketEntry* newEntry = new BucketEntry(_hash, _val, bucket);
    _Buckets[_bucket] = newEntry;
    ++_Size;

    if (((float)_Size / _BucketCount) > HashMapThreshold) {
    	Rehash(_BucketCount * 2);
    }
  }

  void FreeBuckets(BucketEntry** _buckets, uint16_t _count) {
  	if (_buckets == null) return;

    for (int i = 0; i < _count; ++i) {
    	BucketEntry* entry = _buckets[i];
      while (entry != null) {
				BucketEntry* toDelete = entry;
        entry = entry->Next;

        if (_Deleter != null) _Deleter(toDelete->Value);
				delete toDelete;
      }
    }

		delete [] _buckets;
  }

  void Rehash(uint16_t _bucketCount) {
		BucketEntry** old = _Buckets;
    uint16_t oldCount = _BucketCount;

    _BucketCount = _bucketCount;
    _Buckets = new BucketEntry*[_BucketCount];
    memset(_Buckets, null, _BucketCount * sizeof(BucketEntry*));

    if (old == null) return;

    for (uint16_t i = 0; i < oldCount; ++i) {
    	BucketEntry* entry = old[i];
      while (entry != null) {
				SetValue(entry->HashKey, (entry->HashKey % _BucketCount), entry->Value);
        entry = entry->Next;
      }
    }

    FreeBuckets(old, oldCount);
  }

public:
	VGHashMap(int _bucketCount = 32, ValueDeleter _valueDeleter = null) :
   _BucketCount(0), _Size(0), _Buckets(null), _Deleter(_valueDeleter) {
  	Rehash(_bucketCount);
  }
	virtual ~VGHashMap() { FreeBuckets(_Buckets, _BucketCount); }

  void SetDeleter(ValueDeleter _deleter) { _Deleter = _deleter; }
  TValue& operator[](const TKey& _key) { return *Get(_key); }

  TValue* Get(const TKey& _key) const {
  	uint32_t hash = 0;
    int index = GetIndex(_key, &hash);
    BucketEntry* bucket = _Buckets[index];

    while(bucket != null) {
    	if (bucket->HashKey == hash) return &bucket->Value;
      bucket = bucket->Next;
    }

    return null;
  }

  void Set(const TKey& _key, const TValue& _value) {
   	uint32_t hash = 0;
    int index = GetIndex(_key, &hash);
    BucketEntry* bucket = _Buckets[index];
    SetValue(hash, index, _value);
  }

  void Remove(const TKey& _key, const TValue& _value) {
   	uint32_t hash = 0;
    int index = GetIndex(_key, &hash);
    BucketEntry* bucket = _Buckets[index];

    BucketEntry* prev = null;
    while (bucket != null) {
    	if (bucket->HashKey == hash) {
      	if (prev != null) prev->Next = bucket->Next;
        else prev = bucket->Next;

        if (_Deleter != null) delete bucket->Value;
        delete bucket;
        --_Size;
        return;
      }

      prev = bucket;
      bucket = bucket->Next;
    }

  }

  bool Contains(const TKey& _key, const TValue& _value) {
  	if (_Buckets == null) return false;

   	uint32_t hash = 0;
    int index = GetIndex(_key, &hash);
    BucketEntry* bucket = _Buckets[index];

    while (bucket != null) {
    	if (bucket->HashKey == hash) return true;
      bucket = bucket->Next;
    }

    return false;
  }

};

#endif
