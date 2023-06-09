#include "xxhash32.h"

/// create new XXHash (32 bit)
/** @param seed your seed value, even zero is a valid seed and e.g. used by LZ4 **/

XXHash32::XXHash32(uint32_t seed)
{
	state[0] = seed + Prime1 + Prime2;
	state[1] = seed + Prime2;
	state[2] = seed;
	state[3] = seed - Prime1;
	bufferSize = 0;
	totalLength = 0;
}

/// add a chunk of bytes
/** @param  input  pointer to a continuous block of data
@param  length number of bytes
@return false if parameters are invalid / zero **/

bool XXHash32::add(const void * input, uint64_t length)
{
	// no data ?
	if (!input || length == 0)
		return false;

	totalLength += length;
	// byte-wise access
	const unsigned char* data = (const unsigned char*)input;

	// unprocessed old data plus new data still fit in temporary buffer ?
	if (bufferSize + length < MaxBufferSize)
	{
		// just add new data
		while (length-- > 0)
			buffer[bufferSize++] = *data++;
		return true;
	}

	// point beyond last byte
	const unsigned char* stop = data + length;
	const unsigned char* stopBlock = stop - MaxBufferSize;

	// some data left from previous update ?
	if (bufferSize > 0)
	{
		// make sure temporary buffer is full (16 bytes)
		while (bufferSize < MaxBufferSize)
			buffer[bufferSize++] = *data++;

		// process these 16 bytes (4x4)
		process(buffer, state[0], state[1], state[2], state[3]);
	}

	// copying state to local variables helps optimizer A LOT
	uint32_t s0 = state[0], s1 = state[1], s2 = state[2], s3 = state[3];
	// 16 bytes at once
	while (data <= stopBlock)
	{
		// local variables s0..s3 instead of state[0]..state[3] are much faster
		process(data, s0, s1, s2, s3);
		data += 16;
	}
	// copy back
	state[0] = s0; state[1] = s1; state[2] = s2; state[3] = s3;

	// copy remainder to temporary buffer
	bufferSize = (uint32_t)(stop - data);
	for (unsigned int i = 0; i < bufferSize; i++)
		buffer[i] = data[i];

	// done
	return true;
}

/// get current hash
/** @return 32 bit XXHash **/

uint32_t XXHash32::hash() const
{
	uint32_t result = (uint32_t)totalLength;

	// fold 128 bit state into one single 32 bit value
	if (totalLength >= MaxBufferSize)
		result += rotateLeft(state[0], 1) +
		rotateLeft(state[1], 7) +
		rotateLeft(state[2], 12) +
		rotateLeft(state[3], 18);
	else
		// internal state wasn't set in add(), therefore original seed is still stored in state2
		result += state[2] + Prime5;

	// process remaining bytes in temporary buffer
	const unsigned char* data = buffer;
	// point beyond last byte
	const unsigned char* stop = data + bufferSize;

	// at least 4 bytes left ? => eat 4 bytes per step
	for (; data + 4 <= stop; data += 4)
		result = rotateLeft(result + *(uint32_t*)data * Prime3, 17) * Prime4;

	// take care of remaining 0..3 bytes, eat 1 byte per step
	while (data != stop)
		result = rotateLeft(result + (*data++) * Prime5, 11) * Prime1;

	// mix bits
	result ^= result >> 15;
	result *= Prime2;
	result ^= result >> 13;
	result *= Prime3;
	result ^= result >> 16;
	return result;
}

/// combine constructor, add() and hash() in one static function (C style)
/** @param  input  pointer to a continuous block of data
@param  length number of bytes
@param  seed your seed value, e.g. zero is a valid seed and used by LZ4
@return 32 bit XXHash **/

uint32_t XXHash32::hash(const void * input, uint64_t length, uint32_t seed)
{
	XXHash32 hasher(seed);
	hasher.add(input, length);
	return hasher.hash();
}
