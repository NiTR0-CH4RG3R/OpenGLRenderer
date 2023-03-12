// //////////////////////////////////////////////////////////
// xxhash64.h
// Copyright (c) 2016 Stephan Brumme. All rights reserved.
// see http://create.stephan-brumme.com/disclaimer.html
//

#pragma once
#include <stdint.h> // for uint32_t and uint64_t

/// XXHash (64 bit), based on Yann Collet's descriptions, see http://cyan4973.github.io/xxHash/
/** How to use:
    uint64_t myseed = 0;
    XXHash64 myhash(myseed);
    myhash.add(pointerToSomeBytes,     numberOfBytes);
    myhash.add(pointerToSomeMoreBytes, numberOfMoreBytes); // call add() as often as you like to ...
    // and compute hash:
    uint64_t result = myhash.hash();

    // or all of the above in one single line:
    uint64_t result2 = XXHash64::hash(mypointer, numBytes, myseed);

    Note: my code is NOT endian-aware !
**/
class XXHash64
{
public:
  /// create new XXHash (64 bit)
  /** @param seed your seed value, even zero is a valid seed **/
	explicit XXHash64(uint64_t seed);

  /// add a chunk of bytes
  /** @param  input  pointer to a continuous block of data
      @param  length number of bytes
      @return false if parameters are invalid / zero **/
	bool add(const void* input, uint64_t length);

  /// get current hash
  /** @return 64 bit XXHash **/
	uint64_t hash() const;


  /// combine constructor, add() and hash() in one static function (C style)
  /** @param  input  pointer to a continuous block of data
      @param  length number of bytes
      @param  seed your seed value, e.g. zero is a valid seed
      @return 64 bit XXHash **/
	static uint64_t hash(const void* input, uint64_t length, uint64_t seed);

private:
  /// magic constants :-)
  static const uint64_t Prime1 = 11400714785074694791ULL;
  static const uint64_t Prime2 = 14029467366897019727ULL;
  static const uint64_t Prime3 =  1609587929392839161ULL;
  static const uint64_t Prime4 =  9650029242287828579ULL;
  static const uint64_t Prime5 =  2870177450012600261ULL;

  /// temporarily store up to 31 bytes between multiple add() calls
  static const uint64_t MaxBufferSize = 31+1;

  uint64_t      state[4];
  unsigned char buffer[MaxBufferSize];
  unsigned int  bufferSize;
  uint64_t      totalLength;

  /// rotate bits, should compile to a single CPU instruction (ROL)
  static inline uint64_t rotateLeft(uint64_t x, unsigned char bits)
  {
    return (x << bits) | (x >> (64 - bits));
  }

  /// process a single 64 bit value
  static inline uint64_t processSingle(uint64_t previous, uint64_t input)
  {
    return rotateLeft(previous + input * Prime2, 31) * Prime1;
  }

  /// process a block of 4x4 bytes, this is the main part of the XXHash32 algorithm
  static inline void process(const void* data, uint64_t& state0, uint64_t& state1, uint64_t& state2, uint64_t& state3)
  {
    const uint64_t* block = (const uint64_t*) data;
    state0 = processSingle(state0, block[0]);
    state1 = processSingle(state1, block[1]);
    state2 = processSingle(state2, block[2]);
    state3 = processSingle(state3, block[3]);
  }
};
