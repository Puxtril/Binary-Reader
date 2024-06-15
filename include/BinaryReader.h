#pragma once

#include "BinaryReaderExceptions.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cmath>
#include <concepts>

namespace BinaryReader
{
	// Converts floating point infinity to floating point max
	#define CONV_INF 1
	// Converts -0 to 0
	#define CONV_ZERO 2
	// Throws NonNormalFloatException if float is sub-normal
	#define FAIL_SUBNORM 4

	// Used for bit-wise operations (limited to 64 bits)
	const static uint64_t POW2[64] = {	0ULL,					2ULL,					4ULL,
										8ULL,					16ULL,					32ULL,
										64ULL,					128ULL,					256ULL,
										512ULL, 				1024ULL,				2048ULL,
										4096ULL,				8192ULL,				16384ULL,
										32768ULL,				65536ULL,				131072ULL,
										262144ULL,				524288ULL,				1048576ULL,
										2097152ULL,				4194304ULL,				8388608ULL,
										16777216ULL,			33554432ULL,			67108864ULL,
										134217728ULL,			268435456ULL,			536870912ULL,
										1073741824ULL,			2147483648ULL,			4294967296ULL,
										8589934592ULL,			17179869184ULL,			34359738368ULL,
										68719476736ULL,			137438953472ULL,		274877906944ULL,
										549755813888ULL, 		1099511627776ULL,		2199023255552ULL,
										4398046511104ULL, 		8796093022208ULL,		17592186044416ULL,
										35184372088832ULL,		70368744177664ULL,		140737488355328ULL,
										281474976710656ULL, 	562949953421312ULL,		1125899906842624ULL,
										2251799813685248ULL, 	4503599627370496ULL,	9007199254740992ULL,
										18014398509481984ULL,	36028797018963968ULL,	72057594037927936ULL,
										144115188075855872ULL,	288230376151711744ULL,	576460752303423488ULL,
										1152921504606846976ULL,	2305843009213693952ULL,	4611686018427387904ULL,
										9223372036854775808ULL};

	template <class T>
	concept isSimpleComparable = requires(T a, T b)
	{
		a < b;
		a > b;
	};

	class BinaryReader
	{
		int m_bitOffset;

	protected:
		// Only requirements for child classes
		virtual void readBytes(void* dst, int count) = 0;
		virtual void readBytesBE(void* dst, int count) = 0;

	public:
		BinaryReader() : m_bitOffset(0) {};

		virtual BinaryReader& seek(std::streamoff offset, std::ios_base::seekdir way = std::ios::cur) = 0;
		virtual size_t getLength() = 0;
		virtual size_t tell() = 0;

		//////////////////////////////////////////////////////////////////////////////
		// Basic read. Use this for structs

		template <typename T>
		T
		read()
		{
			T data;
			readBytes(&data, sizeof(T));
			return data;
		}

		//////////////////////////////////////////////////////////////////////////////
		// Scalars

		template <typename T>
		requires std::integral<T> || std::floating_point<T>
		T
		readScalar()
		{
			T data;
			readBytes(&data, sizeof(T));
			return data;
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		T
		readScalarSafe(T min, T max, const std::string& debugMsg)
		{
			T data;
			readBytes(&data, sizeof(T));

			if (data < min)
				throw LimitException(data, min, debugMsg);
			else if (data >= max)
				throw LimitException(data, max, debugMsg);

			return data;
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		T
		readScalarSafe(T exact, const std::string& debugMsg)
		{
			T data;
			readBytes(&data, sizeof(T));

			if (data != exact)
				throw LimitException(data, exact, debugMsg);

			return data;
		}

		template <typename T>
		requires std::integral<T> || std::floating_point<T>
		T
		readScalarBE()
		{
			T data;
			readBytesBE(&data, sizeof(T));
			return data;
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		T
		readScalarBESafe(T min, T max, const std::string& debugMsg)
		{
			T data;
			readBytesBE(&data, sizeof(T));

			if (data < min)
				throw LimitException(data, min, debugMsg);
			else if (data >= max)
				throw LimitException(data, max, debugMsg);

			return data;
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		T
		readScalarBESafe(T exact, const std::string& debugMsg)
		{
			T data;
			readBytesBE(&data, sizeof(T));

			if (data != exact)
				throw LimitException(data, exact, debugMsg);

			return data;
		}

		//////////////////////////////////////////////////////////////////////////////
		// Scalar Arrays

		template <typename T>
		requires std::integral<T> || std::floating_point<T>
		void
		readScalarArray(T* dst, size_t count)
		{
			readBytes(dst, sizeof(T) * count);
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		void
		readScalarArraySafe(T* dst, size_t count, T min, T max, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytes(&dst[i], sizeof(T));

				if (dst[i] < min)
					throw LimitException(dst[i], min, i, debugMsg);
				else if (dst[i] >= max)
					throw LimitException(dst[i], max, i, debugMsg);
			}
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		void
		readScalarArraySafe(T* dst, size_t count, T exact, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytes(&dst[i], sizeof(T));

				if (dst[i] != exact)
					throw LimitException(dst[i], exact, i, debugMsg);
			}
		}

		template <typename T>
		requires std::integral<T> || std::floating_point<T>
		void
		readScalarArrayBE(T* dst, size_t count)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytesBE(&dst[i], sizeof(T));
			}
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		void
		readScalarArrayBESafe(T* dst, size_t count, T min, T max, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytesBE(&dst[i], sizeof(T));

				if (dst[i] < min)
					throw LimitException(dst[i], min, i, debugMsg);
				else if (dst[i] >= max)
					throw LimitException(dst[i], max, i, debugMsg);
			}
		}

		template <typename T>
		requires std::integral<T> && isSimpleComparable<T>
		void
		readScalarArrayBESafe(T* dst, size_t count, T exact, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytesBE(&dst[i], sizeof(T));

				if (dst[i] != exact)
					throw LimitException(dst[i], exact, i, debugMsg);
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		// Float Overloads

		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		T
		readScalarSafe(T min, T max, uint8_t flags, const std::string& debugMsg)
		{
			T data;
			readBytes(&data, sizeof(T));
			data = _checkFloat<T>(data, min, max, flags, debugMsg);
			return data;
		}

		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		T
		readScalarSafe(T exact, uint8_t flags, const std::string& debugMsg)
		{
			T data;
			readBytes(&data, sizeof(T));
			data = _checkFloat<T>(data, exact, flags, debugMsg);
			return data;
		}

		// Dunno if BE floats are actually used
		// But here's the code anyway
		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		T
		readScalarBESafe(T min, T max, uint8_t flags, const std::string& debugMsg)
		{
			T data;
			readBytesBE(&data, sizeof(T));
			data = _checkFloat<T>(data, min, max, flags, debugMsg);
			return data;
		}

		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		T
		readScalarBESafe(T exact, uint8_t flags, const std::string& debugMsg)
		{
			T data;
			readBytesBE(&data, sizeof(T));
			data = _checkFloat<T>(data, exact, flags, debugMsg);
			return data;
		}

		//////////////////////////////////////////////////////////////////////////////
		// Float Array Overloads

		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		void
		readScalarArraySafe(T* dst, size_t count, T min, T max, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytes(&dst[i], sizeof(T));
				dst[i] = _checkFloat<T>(dst[i], min, max, flags, debugMsg);
			}
		}

		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		void
		readScalarArraySafe(T* dst, size_t count, T exact, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytes(&dst[i], sizeof(T));
				dst[i] = _checkFloat<T>(dst[i], exact, flags, debugMsg);
			}
		}

		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		void
		readScalarArrayBESafe(T* dst, size_t count, T min, T max, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytesBE(&dst[i], sizeof(T));
				dst[i] = _checkFloat<T>(dst[i], min, max, flags, debugMsg);
			}
		}

		template <typename T>
		requires std::floating_point<T> && isSimpleComparable<T>
		void
		readScalarArrayBESafe(T* dst, size_t count, T exact, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				readBytesBE(&dst[i], sizeof(T));
				dst[i] = _checkFloat<T>(dst[i], exact, flags, debugMsg);
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		// Bit-wise Scalars

		template <typename T>
		requires std::integral<T>
		T
		readBitwiseScalar(int readBitCount)
		{
			if (readBitCount == 0)
				throw std::invalid_argument("Read bits cannot be 0");
			if (readBitCount > 64)
				throw std::invalid_argument("Read bits cannot be >= 64");
			
			int bytesToRead = std::ceil((m_bitOffset + readBitCount) / 8.0F);
			T retValue = _readBitwiseScalar<T>(readBitCount, bytesToRead);
			m_bitOffset = (m_bitOffset + readBitCount) % 8;
			// More data in the previous position
			if (m_bitOffset > 0)
				seek(-1, std::ios::cur);

			return retValue;
		}

		//////////////////////////////////////////////////////////////////////////////
		// Half-Floats

		float
		readHalf()
		{
			return _readHalfFloat();
		}

		float
		readHalfSafe(float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			float data = _readHalfFloat();
			return _checkFloat<float>(data, min, max, flags, debugMsg);
		}

		float
		readHalfSafe(float exact, uint8_t flags, const std::string& debugMsg)
		{
			float data = _readHalfFloat();
			return _checkFloat<float>(data, exact, flags, debugMsg);
		}


		void
		readHalfArray(float* dst, size_t count)
		{
			for (size_t i = 0; i < count; i++)
				dst[i] = readHalf();
		}

		void
		readHalfArraySafe(float* dst, size_t count, float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				dst[i] = readHalf();
				dst[i] = _checkFloat<float>(dst[i], min, max, flags, debugMsg);
			}
		}

		void
		readHalfArraySafe(float* dst, size_t count, float exact, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t i = 0; i < count; i++)
			{
				dst[i] = readHalf();
				dst[i] = _checkFloat<float>(dst[i], exact, flags, debugMsg);
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		// LEB

		uint64_t
		readULEB(int maxBits = 64)
		{
			return _readULEB(maxBits);
		}

		uint64_t
		readULEBSafe(uint64_t min, uint64_t max, const std::string& debugMsg, int maxBits = 64)
		{
			uint64_t data = _readULEB(maxBits);

			if (data < min)
				throw LimitException(data, min, debugMsg);
			else if (data >= max)
				throw LimitException(data, max, debugMsg);

			return data;
		}

		uint64_t
		readULEBSafe(uint64_t exact, const std::string& debugMsg, int maxBits = 64)
		{
			uint64_t data = _readULEB(maxBits);

			if (data != exact)
				throw LimitException(data, exact, debugMsg);

			return data;
		}

		void
		readULEBArray(uint64_t* dst, size_t count, int maxBits = 64)
		{
			for (size_t i = 0; i < count; i++)
				dst[i] = _readULEB(maxBits);
		}

		void
		readULEBArraySafe(uint64_t* dst, size_t count, uint64_t min, uint64_t max, const std::string& debugMsg, int maxBits = 64)
		{
			for (size_t i = 0; i < count; i++)
			{
				dst[i] = _readULEB(maxBits);
				
				if (dst[i] < min)
					throw LimitException(dst[i], min, i, debugMsg);
				else if (dst[i] >= max)
					throw LimitException(dst[i], max, i, debugMsg);
			}
		}

		void
		readULEBArraySafe(uint64_t* dst, size_t count, uint64_t exact, const std::string& debugMsg, int maxBits = 64)
		{
			for (size_t i = 0; i < count; i++)
			{
				dst[i] = _readULEB(maxBits);
				
				if (dst[i] != exact)
					throw LimitException(dst[i], exact, i, debugMsg);
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		// Other members

		int
		tellBit() const
		{
			return m_bitOffset;
		}

		BinaryReader&
		seekBit(int count, std::ios_base::seekdir way)
		{
			int seekTo = m_bitOffset;
			switch(way)
			{
			case(std::ios::beg):
				seekTo = count;
				break;
			case(std::ios::cur):
				seekTo += count;
				break;
			// Silly
			case(std::ios::end):
				seekTo = 7 - count;
				break;
			}

			std::div_t bytesAndBits = std::div(seekTo, 8);
			int bytesToSeek = bytesAndBits.quot;
			int bitsToSeek = bytesAndBits.rem;
			if (bitsToSeek < 0)
			{
				bytesToSeek -= 1;
				bitsToSeek = 7 - bytesAndBits.rem;
			}

			seek(bytesToSeek, std::ios::cur);
			m_bitOffset = bitsToSeek;

			return *this;
		}

	private:
		//////////////////////////////////////////////////////////////////////////////
		// Utils

		// Unsigned
		template <typename T>
		requires std::unsigned_integral<T>
		T
		_readBitwiseScalar(int bitCount, int byteCount)
		{
			static uint64_t buf;
			readBytes(&buf, byteCount);
			T ret = buf >> m_bitOffset;
			return ret & (T)(POW2[bitCount] - 1);
		}

		// Signed
		template <typename T>
		requires std::signed_integral<T>
		T
		_readBitwiseScalar(int bitCount, int byteCount)
		{
			static uint64_t buf;
			readBytes(&buf, byteCount);
			T ret = buf >> m_bitOffset;
			ret &= (T)(POW2[bitCount] - 1);

			// Convert signed integer of width `bitCount` to width `sizeof(T)`
			T signedMask = (T)(POW2[bitCount - 1]);
			if ((ret & signedMask) > 0)
			{
				// Fill T-width integer with 1s, then shift right `bitcount`
				T shiftSignedBitMask = (T)(POW2[sizeof(T) * 8] - 1) << bitCount;
				ret |= shiftSignedBitMask;
			}
			
			return ret;
		}

		template <typename T>
		requires std::floating_point<T>
		T
		_convertFloat(T data, uint8_t flags, const std::string& debugMsg)
		{
			T fixed = data;

			switch(std::fpclassify(data))
			{
				case FP_INFINITE:
				{
					if (flags & CONV_INF)
					{
						if (data == std::numeric_limits<T>::infinity())
						{
							const static T floatMax = std::numeric_limits<T>::max();
							std::memcpy(&fixed, &floatMax, sizeof(T));
						}
						else
						{
							const static T floatMin = -std::numeric_limits<T>::max();
							std::memcpy(&fixed, &floatMin, sizeof(T));
						}
					}
					else
						throw LimitException(data, 0, debugMsg);
					break;
				}
				case FP_NAN:
				{
					throw NonNormalFloatException(data, debugMsg);
					break;
				}
				case FP_ZERO:
				{
					if (flags & CONV_ZERO)
						fixed = 0;
					break;
				}
				case FP_SUBNORMAL:
				{
					if (flags & FAIL_SUBNORM)
						throw NonNormalFloatException(data, debugMsg);
					break;
				}
				case FP_NORMAL:
				default:
					break;
			}

			return fixed;
		}

		template <typename T>
		requires std::floating_point<T>
		T
		_checkFloat(T data, T min, T max, uint8_t flags, const std::string& debugMsg)
		{
			T fixed = _convertFloat(data, flags, debugMsg);

			int64_t intMin;
			int64_t intMax;
			int64_t intData;
			std::memcpy(&intMin, &min, sizeof(T));
			std::memcpy(&intMax, &max, sizeof(T));
			std::memcpy(&intData, &fixed, sizeof(T));

			if (intData < intMin)
				throw LimitException(data, min, debugMsg);
			else if (intData >= intMax)
				throw LimitException(data, max, debugMsg);

			return fixed;
		}

		template <typename T>
		requires std::floating_point<T>
		T
		_checkFloat(T data, T exact, uint8_t flags, const std::string& debugMsg)
		{
			T fixed = _convertFloat(data, flags, debugMsg);

			int64_t intExact;
			int64_t intData;
			std::memcpy(&intExact, &exact, sizeof(T));
			std::memcpy(&intData, &fixed, sizeof(T));

			if (intData != exact)
				throw LimitException(data, exact, debugMsg);

			return fixed;
		}

		// https://github.com/yretenai/Lotus/blob/500c5d615563467a87bd002df70b789e944c3240/Lotus.Struct/CursoredMemoryMarshal.cs#L125C31-L125C38
		uint64_t
		_readULEB(int maxBits = 64)
		{
			uint64_t result = 0;
			
			uint8_t curByte;
			for (int curShift = 0; curShift < maxBits - 1; curShift += 7)
			{
				curByte = readScalar<uint8_t>();
				result |= (curByte & 0x7Ful) << curShift;

				if (curByte <= 0x7ful)
					return result;
			}

			curByte = readScalar<uint8_t>();
			result |= (uint64_t)curByte << (maxBits - 1);
			return result;
		}

		// I saved this from somewhere online
		// If I remembered where, I would give credit
		float
		_readHalfFloat()
		{
			int hbits = readScalar<uint16_t>();
			int mant = hbits & 0x03ff;            // 10 bits mantissa
			int exp = hbits & 0x7c00;            // 5 bits exponent
			if (exp == 0x7c00)                   // NaN/Inf
				exp = 0x3fc00;                    // -> NaN/Inf
			else if (exp != 0)                   // normalized value
			{
				exp += 0x1c000;                   // exp - 15 + 127
				if (mant == 0 && exp > 0x1c400)  // smooth transition
				{
					uint32_t t = ((hbits & 0x8000) << 16) | (exp << 13);
					float ret;
					std::memcpy(&ret, &t, 4);
					return ret;
				}
			}
			else if (mant != 0)                  // && exp==0 -> subnormal
			{
				exp = 0x1c400;                    // make it normal
				do
				{
					mant <<= 1;                   // mantissa * 2
					exp -= 0x400;                 // decrease exp by 1
				} while ((mant & 0x400) == 0); // while not normal
				mant &= 0x3ff;                    // discard subnormal bit
			}                                     // else +/-0 -> +/-0
			uint32_t t(                      // combine all parts
				((hbits & 0x8000) << 16)         // sign  << ( 31 - 15 )
				| ((exp | mant) << 13));         // value << ( 23 - 10 )
			float ret;
			std::memcpy(&ret, &t, 4);
			return ret;
		}
	};
};
