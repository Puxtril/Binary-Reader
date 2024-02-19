#pragma once

#include "BinaryReaderExceptions.h"

#include <fstream>
#include <cstdint>
#include <string>
#include <cstring>
#include <memory>
#include <cmath>
#include <climits>
#include <vector>

#define CONV_INF 1
#define CONV_ZERO 2
#define FAIL_SUBNORM 4

namespace BinaryReader
{
	class BinaryReader
	{
	private:
		virtual void read1Byte(uint8_t* dst) = 0;
		virtual void read2Bytes(uint8_t* dst) = 0;
		virtual void read2BytesBE(uint8_t* dst) = 0;
		virtual void read4Bytes(uint8_t* dst) = 0;
		virtual void read4BytesBE(uint8_t* dst) = 0;
		virtual void read8Bytes(uint8_t* dst) = 0;
		virtual void read8BytesBE(uint8_t* dst) = 0;

	public:
		BinaryReader() = default;

		virtual size_t getLength() = 0;
		virtual BinaryReader& seek(std::streamoff offset, std::ios_base::seekdir way) = 0;
		virtual size_t tell() = 0;

		uint8_t
		readUInt8()
		{
			uint8_t data;
			read1Byte(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		uint8_t
		readUInt8(uint8_t min, uint8_t max, const std::string& debugMsg)
		{
			uint8_t data;
			read1Byte(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((uint64_t)data, min, debugMsg);
			else if (data > max)
				throw LimitException((uint64_t)data, max, debugMsg);
			return data;
		}

		int8_t
		readInt8()
		{
			uint8_t data;
			read1Byte(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		int8_t
		readInt8(int8_t min, int8_t max, const std::string& debugMsg)
		{
			uint8_t data;
			read1Byte(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((int64_t)data, max, debugMsg);
			else if (data > max)
				throw LimitException((int64_t)data, max, debugMsg);
			return data;
		}

		uint16_t
		readUInt16()
		{
			uint16_t data;
			read2Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		uint16_t
		readUInt16(uint16_t min, uint16_t max, const std::string& debugMsg)
		{
			uint16_t data;
			read2Bytes(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((uint64_t)data, min, debugMsg);
			else if (data > max)
				throw LimitException((uint64_t)data, max, debugMsg);
			return data;
		}

		int16_t
		readInt16()
		{
			int16_t data;
			read2Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		int16_t
		readInt16(int16_t min, int16_t max, const std::string& debugMsg)
		{
			int16_t data;
			read2Bytes(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((int64_t)data, max, debugMsg);
			else if (data > max)
				throw LimitException((int64_t)data, max, debugMsg);
			return data;
		}

		uint16_t
		readUInt16BE()
		{
			uint16_t data;
			read2BytesBE(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		uint16_t
		readUInt16BE(uint16_t min, uint16_t max, const std::string& debugMsg)
		{
			uint16_t data;
			read2BytesBE(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((uint64_t)data, min, debugMsg);
			else if (data > max)
				throw LimitException((uint64_t)data, max, debugMsg);
			return data;
		}

		int16_t
		readInt16BE()
		{
			int16_t data;
			read2BytesBE(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		int16_t
		readInt16BE(int16_t min, int16_t max, const std::string& debugMsg)
		{
			int16_t data;
			read2BytesBE(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((int64_t)data, max, debugMsg);
			else if (data > max)
				throw LimitException((int64_t)data, max, debugMsg);
			return data;
		}

		uint32_t
		readUInt32()
		{
			uint32_t data;
			read4Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		uint32_t
		readUInt32(uint32_t min, uint32_t max, const std::string& debugMsg)
		{
			uint32_t data;
			read4Bytes(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((uint64_t)data, min, debugMsg);
			else if (data > max)
				throw LimitException((uint64_t)data, max, debugMsg);
			return data;
		}

		int32_t
		readInt32()
		{
			int32_t data;
			read4Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		int32_t
		readInt32(int32_t min, int32_t max, const std::string& debugMsg)
		{
			int32_t data;
			read4Bytes(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((int64_t)data, max, debugMsg);
			else if (data > max)
				throw LimitException((int64_t)data, max, debugMsg);
			return data;
		}

		uint32_t
		readUInt32BE()
		{
			uint32_t data;
			read4BytesBE(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		uint32_t
		readUInt32BE(uint32_t min, uint32_t max, const std::string& debugMsg)
		{
			uint32_t data;
			read4BytesBE(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((uint64_t)data, min, debugMsg);
			else if (data > max)
				throw LimitException((uint64_t)data, max, debugMsg);
			return data;
		}

		int32_t
		readInt32BE()
		{
			int32_t data;
			read4BytesBE(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		int32_t
		readInt32BE(int32_t min, int32_t max, const std::string& debugMsg)
		{
			int32_t data;
			read4BytesBE(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException((int64_t)data, max, debugMsg);
			else if (data > max)
				throw LimitException((int64_t)data, max, debugMsg);
			return data;
		}

		uint64_t
		readUInt64()
		{
			uint64_t data;
			read8Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		uint64_t
		readUInt64(uint64_t min, uint64_t max, const std::string& debugMsg)
		{
			uint64_t data;
			read8Bytes(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException(data, min, debugMsg);
			else if (data > max)
				throw LimitException(data, max, debugMsg);
			return data;
		}

		int64_t
		readInt64()
		{
			int64_t data;
			read8Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		int64_t
		readInt64(int64_t min, int64_t max, const std::string& debugMsg)
		{
			int64_t data;
			read8Bytes(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException(data, min, debugMsg);
			else if (data > max)
				throw LimitException(data, max, debugMsg);
			return data;
		}

		uint64_t
		readUInt64BE()
		{
			uint64_t data;
			read8BytesBE(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		uint64_t
		readUInt64BE(uint64_t min, uint64_t max, const std::string& debugMsg)
		{
			uint64_t data;
			read8BytesBE(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException(data, min, debugMsg);
			else if (data > max)
				throw LimitException(data, max, debugMsg);
			return data;
		}

		int64_t
		readInt64BE()
		{
			int64_t data;
			read8BytesBE(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		int64_t
		readInt64BE(int64_t min, int64_t max, const std::string& debugMsg)
		{
			int64_t data;
			read8BytesBE(reinterpret_cast<uint8_t*>(&data));

			if (data < min)
				throw LimitException(data, min, debugMsg);
			else if (data > max)
				throw LimitException(data, max, debugMsg);
			return data;
		}

		// I saved this from somewhere online
		// If I remembered where, I would give credit
		float
		readHalf()
		{
			int hbits = this->readUInt16();
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

		float
		readHalf(float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			float data = this->readHalf();
			
			int32_t castData = 0;
			switch(std::fpclassify(data))
			{
				case FP_INFINITE:
				{
					if (flags & CONV_INF)
					{
						if (data == std::numeric_limits<float>::infinity())
						{
							const static float floatMax = std::numeric_limits<float>::max();
							std::memcpy(&castData, &floatMax, 4);
						}
						else
						{
							const static float floatMin = -std::numeric_limits<float>::max();
							std::memcpy(&castData, &floatMin, 4);
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
						castData = 0;
					break;
				}
				case FP_SUBNORMAL:
				{
					if (flags & FAIL_SUBNORM)
						throw NonNormalFloatException(data, debugMsg);
					break;
				}
				case FP_NORMAL:
				{
					std::memcpy(&castData, &data, 4);
					break;
				}
				default:
					break;
			}

			int32_t intMin;
			int32_t intMax;
			std::memcpy(&intMin, &min, 4);
			std::memcpy(&intMax, &max, 4);
			if (castData < intMin)
				throw LimitException(data, min, debugMsg);
			else if (castData > intMax)
				throw LimitException(data, max, debugMsg);
			return data;
		}

		float
		readFloat()
		{
			float data;
			read4Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		float
		readFloat(float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			float data;
			read4Bytes(reinterpret_cast<uint8_t*>(&data));

			int32_t castData = 0;
			switch(std::fpclassify(data))
			{
				case FP_INFINITE:
				{
					if (flags & CONV_INF)
					{
						if (data == std::numeric_limits<float>::infinity())
						{
							const static float floatMax = std::numeric_limits<float>::max();
							std::memcpy(&castData, &floatMax, 4);
						}
						else
						{
							const static float floatMin = -std::numeric_limits<float>::max();
							std::memcpy(&castData, &floatMin, 4);
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
						castData = 0;
					break;
				}
				case FP_SUBNORMAL:
				{
					if (flags & FAIL_SUBNORM)
						throw NonNormalFloatException(data, debugMsg);
					break;
				}
				case FP_NORMAL:
				{
					std::memcpy(&castData, &data, 4);
					break;
				}
				default:
					break;
			}

			int32_t intMin;
			int32_t intMax;
			std::memcpy(&intMin, &min, 4);
			std::memcpy(&intMax, &max, 4);
			if (castData < intMin)
				throw LimitException(data, min, debugMsg);
			else if (castData > intMax)
				throw LimitException(data, max, debugMsg);
			return data;
		}

		double
		readDouble()
		{
			double data;
			read8Bytes(reinterpret_cast<uint8_t*>(&data));
			return data;
		}

		double
		readDouble(double min, double max, uint8_t flags, const std::string& debugMsg)
		{
			double data;
			read8Bytes(reinterpret_cast<uint8_t*>(&data));
			
			int64_t castData = 0;
			switch(std::fpclassify(data))
			{
				case FP_INFINITE:
				{
					if (flags & CONV_INF)
					{
						if (data == std::numeric_limits<double>::infinity())
						{
							const static double doubleMax = std::numeric_limits<double>::max();
							std::memcpy(&castData, &doubleMax, 4);
						}
						else
						{
							const static double doubleMin = -std::numeric_limits<double>::max();
							std::memcpy(&castData, &doubleMin, 4);
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
						castData = 0;
					break;
				}
				case FP_SUBNORMAL:
				{
					if (flags & FAIL_SUBNORM)
						throw NonNormalFloatException(data, debugMsg);
					break;
				}
				case FP_NORMAL:
				{
					std::memcpy(&castData, &data, 8);
					break;
				}
				default:
					break;
			}

			int64_t intMin;
			int64_t intMax;
			std::memcpy(&intMin, &min, 8);
			std::memcpy(&intMax, &max, 8);
			if (castData < intMin)
				throw LimitException(data, min, debugMsg);
			else if (castData > intMax)
				throw LimitException(data, max, debugMsg);
			return data;
		}

		std::string
		readAsciiString(size_t len)
		{
			std::vector<uint8_t> buffer = readUInt8Array(len);
			std::string data = std::string((char*)buffer.data(), len);
			return data;
		}

		std::vector<uint8_t>
		readUInt8Array(size_t count)
		{
			std::vector<uint8_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt8();
			return data;
		}

		std::vector<uint8_t>
		readUInt8Array(size_t count, uint8_t min, uint8_t max, const std::string& debugMsg)
		{
			std::vector<uint8_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt8(min, max, debugMsg);
			return data;
		}

		void
		readUInt8Array(uint8_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt8();
		}

		void
		readUInt8Array(uint8_t* ptr, size_t count, uint8_t min, uint8_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt8(min, max, debugMsg);
		}

		std::vector<int8_t>
		readInt8Array(size_t count)
		{
			std::vector<int8_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt8();
			return data;
		}

		std::vector<int8_t>
		readInt8Array(size_t count, int8_t min, int8_t max, const std::string& debugMsg)
		{
			std::vector<int8_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt8(min, max, debugMsg);
			return data;
		}

		void
		readInt8Array(int8_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt8();
		}

		void
		readInt8Array(int8_t* ptr, size_t count, int8_t min, int8_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt8(min, max, debugMsg);
		}

		std::vector<uint16_t>
		readUInt16Array(size_t count)
		{
			std::vector<uint16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt16();
			return data;
		}

		std::vector<uint16_t>
		readUInt16Array(size_t count, uint16_t min, uint16_t max, const std::string& debugMsg)
		{
			std::vector<uint16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt16(min, max, debugMsg);
			return data;
		}

		void
		readUInt16Array(uint16_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt16();
		}

		void
		readUInt16Array(uint16_t* ptr, size_t count, uint16_t min, uint16_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt16(min, max, debugMsg);
		}

		std::vector<int16_t>
		readInt16Array(size_t count)
		{
			std::vector<int16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt16();
			return data;
		}

		std::vector<int16_t>
		readInt16Array(size_t count, int16_t min, int16_t max, const std::string& debugMsg)
		{
			std::vector<int16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt16(min, max, debugMsg);
			return data;
		}

		void
		readInt16Array(int16_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt16();
		}

		void
		readInt16Array(int16_t* ptr, size_t count, int16_t min, int16_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt16(min, max, debugMsg);
		}

		std::vector<uint16_t>
		readUInt16BEArray(size_t count)
		{
			std::vector<uint16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt16BE();
			return data;
		}

		std::vector<uint16_t>
		readUInt16BEArray(size_t count, uint16_t min, uint16_t max, const std::string& debugMsg)
		{
			std::vector<uint16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt16BE(min, max, debugMsg);
			return data;
		}

		void
		readUInt16BEArray(uint16_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt16BE();
		}

		void
		readUInt16BEArray(uint16_t* ptr, size_t count, uint16_t min, uint16_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt16BE(min, max, debugMsg);
		}

		std::vector<int16_t>
		readInt16BEArray(size_t count)
		{
			std::vector<int16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt16BE();
			return data;
		}

		std::vector<int16_t>
		readInt16BEArray(size_t count, int16_t min, int16_t max, const std::string& debugMsg)
		{
			std::vector<int16_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt16BE(min, max, debugMsg);
			return data;
		}

		void
		readInt16BEArray(int16_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt16BE();
		}

		void
		readInt16BEArray(int16_t* ptr, size_t count, int16_t min, int16_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt16BE(min, max, debugMsg);
		}

		std::vector<uint32_t>
		readUInt32Array(size_t count)
		{
			std::vector<uint32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt32();
			return data;
		}

		std::vector<uint32_t>
		readUInt32Array(size_t count, uint32_t min, uint32_t max, const std::string& debugMsg)
		{
			std::vector<uint32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt32(min, max, debugMsg);
			return data;
		}

		void
		readUInt32Array(uint32_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt32();
		}

		void
		readUInt32Array(uint32_t* ptr, size_t count, uint32_t min, uint32_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt32(min, max, debugMsg);
		}

		std::vector<int32_t>
		readInt32Array(size_t count)
		{
			std::vector<int32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt32();
			return data;
		}

		std::vector<int32_t>
		readInt32Array(size_t count, int32_t min, int32_t max, const std::string& debugMsg)
		{
			std::vector<int32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt32(min, max, debugMsg);
			return data;
		}

		void
		readInt32Array(int32_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt32();
		}

		void
		readInt32Array(int32_t* ptr, size_t count, int32_t min, int32_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt32(min, max, debugMsg);
		}

		std::vector<uint32_t>
		readUInt32BEArray(size_t count)
		{
			std::vector<uint32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt32BE();
			return data;
		}

		std::vector<uint32_t>
		readUInt32BEArray(size_t count, uint32_t min, uint32_t max, const std::string& debugMsg)
		{
			std::vector<uint32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt32BE(min, max, debugMsg);
			return data;
		}

		void
		readUInt32BEArray(uint32_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt32BE();
		}

		void
		readUInt32BEArray(uint32_t* ptr, size_t count, uint32_t min, uint32_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt32BE(min, max, debugMsg);
		}

		std::vector<int32_t>
		readInt32BEArray(size_t count)
		{
			std::vector<int32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt32BE();
			return data;
		}

		std::vector<int32_t>
		readInt32BEArray(size_t count, int32_t min, int32_t max, const std::string& debugMsg)
		{
			std::vector<int32_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt32BE(min, max, debugMsg);
			return data;
		}

		void
		readInt32BEArray(int32_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt32BE();
		}

		void
		readInt32BEArray(int32_t* ptr, size_t count, int32_t min, int32_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt32BE(min, max, debugMsg);
		}

		std::vector<uint64_t>
		readUInt64Array(size_t count)
		{
			std::vector<uint64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt64();
			return data;
		}

		std::vector<uint64_t>
		readUInt64Array(size_t count, uint64_t min, uint64_t max, const std::string& debugMsg)
		{
			std::vector<uint64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt64(min, max, debugMsg);
			return data;
		}

		void
		readUInt64Array(uint64_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt64();
		}

		void
		readUInt64Array(uint64_t* ptr, size_t count, uint64_t min, uint64_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt64(min, max, debugMsg);
		}

		std::vector<int64_t>
		readInt64Array(size_t count)
		{
			std::vector<int64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt64();
			return data;
		}

		std::vector<int64_t>
		readInt64Array(size_t count, int64_t min, int64_t max, const std::string& debugMsg)
		{
			std::vector<int64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt64(min, max, debugMsg);
			return data;
		}

		void
		readInt64Array(int64_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt64();
		}

		void
		readInt64Array(int64_t* ptr, size_t count, int64_t min, int64_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt64(min, max, debugMsg);
		}

		std::vector<uint64_t>
		readUInt64BEArray(size_t count)
		{
			std::vector<uint64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt64BE();
			return data;
		}

		std::vector<uint64_t>
		readUInt64BEArray(size_t count, uint64_t min, uint64_t max, const std::string& debugMsg)
		{
			std::vector<uint64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readUInt64BE(min, max, debugMsg);
			return data;
		}

		void
		readUInt64BEArray(uint64_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readUInt64BE();
		}

		void
		readUInt64BEArray(uint64_t* ptr, size_t count, uint64_t min, uint64_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt64BE(min, max, debugMsg);
		}

		std::vector<int64_t>
		readInt64BEArray(size_t count)
		{
			std::vector<int64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt64BE();
			return data;
		}

		std::vector<int64_t>
		readInt64BEArray(size_t count, int64_t min, int64_t max, const std::string& debugMsg)
		{
			std::vector<int64_t> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readInt64BE(min, max, debugMsg);
			return data;
		}

		void
		readInt64BEArray(int64_t* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt64BE();
		}

		void
		readInt64BEArray(int64_t* ptr, size_t count, int64_t min, int64_t max, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readInt64BE(min, max, debugMsg);
		}

		std::vector<float>
		readHalfArray(size_t count)
		{
			std::vector<float> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readHalf();
			return data;
		}

		std::vector<float>
		readHalfArray(size_t count, float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			std::vector<float> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readHalf(min, max, flags, debugMsg);
			return data;
		}

		void
		readHalfArray(float* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readHalf();
		}

		void
		readHalfArray(float* ptr, size_t count, float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readHalf(min, max, flags, debugMsg);
		}

		std::vector<float>
		readSingleArray(size_t count)
		{
			std::vector<float> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readFloat();
			return data;
		}

		std::vector<float>
		readSingleArray(size_t count, float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			std::vector<float> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readFloat(min, max, flags, debugMsg);
			return data;
		}

		void
		readSingleArray(float* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readFloat();
		}

		void
		readSingleArray(float* ptr, size_t count, float min, float max, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readFloat(min, max, flags, debugMsg);
		}

		std::vector<double>
		readDoubleArray(size_t count)
		{
			std::vector<double> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readDouble();
			return data;
		}

		std::vector<double>
		readDoubleArray(size_t count, double min, double max, uint8_t flags, const std::string& debugMsg)
		{
			std::vector<double> data(count);
			for (size_t x = 0; x < count; x++)
				data[x] = readDouble(min, max, flags, debugMsg);
			return data;
		}

		void
		readDoubleArray(double* ptr, size_t count)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readDouble();
		}

		void
		readDoubleArray(double* ptr, size_t count, double min, double max, uint8_t flags, const std::string& debugMsg)
		{
			for (size_t x = 0; x < count; x++)
				ptr[x] = readDouble(min, max, flags, debugMsg);
		}
	};
};