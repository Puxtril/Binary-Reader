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

class BinaryReader
{
private:
	virtual void read1Byte(char* dst) = 0;
	virtual void read2Bytes(char* dst) = 0;
	virtual void read2BytesBE(char* dst) = 0;
	virtual void read4Bytes(char* dst) = 0;
	virtual void read4BytesBE(char* dst) = 0;
	virtual void read8Bytes(char* dst) = 0;
	virtual void read8BytesBE(char* dst) = 0;

public:
	BinaryReader() = default;
	virtual ~BinaryReader() = default;

	uint8_t 	readUInt8();
	uint8_t 	readUInt8(uint8_t min, uint8_t max, const std::string& debugMsg);
	int8_t 		readInt8();
	int8_t 		readInt8(int8_t min, int8_t max, const std::string& debugMsg);

	uint16_t 	readUInt16();
	uint16_t 	readUInt16(uint16_t min, uint16_t max, const std::string& debugMsg);
	int16_t 	readInt16();
	int16_t 	readInt16(int16_t min, int16_t max, const std::string& debugMsg);
	
	uint16_t	readUInt16BE();
	uint16_t 	readUInt16BE(uint16_t min, uint16_t max, const std::string& debugMsg);
	int16_t 	readInt16BE();
	int16_t 	readInt16BE(int16_t min, int16_t max, const std::string& debugMsg);

	uint32_t	readUInt32();
	uint32_t	readUInt32(uint32_t min, uint32_t max, const std::string& debugMsg);
	int32_t		readInt32();
	int32_t		readInt32(int32_t min, int32_t max, const std::string& debugMsg);
	
	uint32_t	readUInt32BE();
	uint32_t	readUInt32BE(uint32_t min, uint32_t max, const std::string& debugMsg);
	int32_t		readInt32BE();
	int32_t		readInt32BE(int32_t min, int32_t max, const std::string& debugMsg);
	
	uint64_t	readUInt64();
	uint64_t	readUInt64(uint64_t min, uint64_t max, const std::string& debugMsg);
	int64_t		readInt64();
	int64_t		readInt64(int64_t min, int64_t max, const std::string& debugMsg);
	
	uint64_t	readUInt64BE();
	uint64_t	readUInt64BE(uint64_t min, uint64_t max, const std::string& debugMsg);
	int64_t		readInt64BE();
	int64_t		readInt64BE(int64_t min, int64_t max, const std::string& debugMsg);
	
	float		readHalf();
	float		readHalf(float min, float max, uint8_t flags, const std::string& debugMsg);
	
	float		readFloat();
	float		readFloat(float min, float max, uint8_t flags, const std::string& debugMsg);

	double		readDouble();
	double		readDouble(double min, double max, uint8_t flags, const std::string& debugMsg);

	std::vector<uint8_t>	readUInt8Array(size_t count);
	std::vector<uint8_t>	readUInt8Array(size_t count, uint8_t min, uint8_t max, const std::string& debugMsg);
	void					readUInt8Array(uint8_t* ptr, size_t count);
	void					readUInt8Array(uint8_t* ptr, size_t count, uint8_t min, uint8_t max, const std::string& debugMsg);

	std::vector<int8_t>		readInt8Array(size_t count);
	std::vector<int8_t>		readInt8Array(size_t count, int8_t min, int8_t max, const std::string& debugMsg);
	void					readInt8Array(int8_t* ptr, size_t count);
	void					readInt8Array(int8_t* ptr, size_t count, int8_t min, int8_t max, const std::string& debugMsg);

	std::vector<uint16_t>	readUInt16Array(size_t count);
	std::vector<uint16_t>	readUInt16Array(size_t count, uint16_t min, uint16_t max, const std::string& debugMsg);
	void					readUInt16Array(uint16_t* ptr, size_t count);
	void					readUInt16Array(uint16_t* ptr, size_t count, uint16_t min, uint16_t max, const std::string& debugMsg);
	std::vector<int16_t>	readInt16Array(size_t count);
	std::vector<int16_t>	readInt16Array(size_t count, int16_t min, int16_t max, const std::string& debugMsg);
	void					readInt16Array(int16_t* ptr, size_t count);
	void					readInt16Array(int16_t* ptr, size_t count, int16_t min, int16_t max, const std::string& debugMsg);
	
	std::vector<uint16_t>	readUInt16BEArray(size_t count);
	std::vector<uint16_t>	readUInt16BEArray(size_t count, uint16_t min, uint16_t max, const std::string& debugMsg);
	void					readUInt16BEArray(uint16_t* ptr, size_t count);
	void					readUInt16BEArray(uint16_t* ptr, size_t count, uint16_t min, uint16_t max, const std::string& debugMsg);
	std::vector<int16_t>	readInt16BEArray(size_t count);
	std::vector<int16_t>	readInt16BEArray(size_t count, int16_t min, int16_t max, const std::string& debugMsg);
	void					readInt16BEArray(int16_t* ptr, size_t count);
	void					readInt16BEArray(int16_t* ptr, size_t count, int16_t min, int16_t max, const std::string& debugMsg);

	std::vector<uint32_t>	readUInt32Array(size_t count);
	std::vector<uint32_t>	readUInt32Array(size_t count, uint32_t min, uint32_t max, const std::string& debugMsg);
	void					readUInt32Array(uint32_t* ptr, size_t count);
	void					readUInt32Array(uint32_t* ptr, size_t count, uint32_t min, uint32_t max, const std::string& debugMsg);
	std::vector<int32_t>	readInt32Array(size_t count);
	std::vector<int32_t>	readInt32Array(size_t count, int32_t min, int32_t max, const std::string& debugMsg);
	void					readInt32Array(int32_t* ptr, size_t count);
	void					readInt32Array(int32_t* ptr, size_t count, int32_t min, int32_t max, const std::string& debugMsg);

	std::vector<uint32_t>	readUInt32BEArray(size_t count);
	std::vector<uint32_t>	readUInt32BEArray(size_t count, uint32_t min, uint32_t max, const std::string& debugMsg);
	void					readUInt32BEArray(uint32_t* ptr, size_t count);
	void					readUInt32BEArray(uint32_t* ptr, size_t count, uint32_t min, uint32_t max, const std::string& debugMsg);
	std::vector<int32_t>	readInt32BEArray(size_t count);
	std::vector<int32_t>	readInt32BEArray(size_t count, int32_t min, int32_t max, const std::string& debugMsg);
	void					readInt32BEArray(int32_t* ptr, size_t count);
	void					readInt32BEArray(int32_t* ptr, size_t count, int32_t min, int32_t max, const std::string& debugMsg);
	
	std::vector<uint64_t>	readUInt64Array(size_t count);
	std::vector<uint64_t>	readUInt64Array(size_t count, uint64_t min, uint64_t max, const std::string& debugMsg);
	void					readUInt64Array(uint64_t* ptr, size_t count);
	void					readUInt64Array(uint64_t* ptr, size_t count, uint64_t min, uint64_t max, const std::string& debugMsg);
	std::vector<int64_t>	readInt64Array(size_t count);
	std::vector<int64_t>	readInt64Array(size_t count, int64_t min, int64_t max, const std::string& debugMsg);
	void					readInt64Array(int64_t* ptr, size_t count);
	void					readInt64Array(int64_t* ptr, size_t count, int64_t min, int64_t max, const std::string& debugMsg);

	std::vector<uint64_t>	readUInt64BEArray(size_t count);
	std::vector<uint64_t>	readUInt64BEArray(size_t count, uint64_t min, uint64_t max, const std::string& debugMsg);
	void					readUInt64BEArray(uint64_t* ptr, size_t count);
	void					readUInt64BEArray(uint64_t* ptr, size_t count, uint64_t min, uint64_t max, const std::string& debugMsg);
	std::vector<int64_t>	readInt64BEArray(size_t count);
	std::vector<int64_t>	readInt64BEArray(size_t count, int64_t min, int64_t max, const std::string& debugMsg);
	void					readInt64BEArray(int64_t* ptr, size_t count);
	void					readInt64BEArray(int64_t* ptr, size_t count, int64_t min, int64_t max, const std::string& debugMsg);

	std::vector<float>		readHalfArray(size_t count);
	std::vector<float>		readHalfArray(size_t count, float min, float max, uint8_t flags, const std::string& debugMsg);
	void					readHalfArray(float* ptr, size_t count);
	void					readHalfArray(float* ptr, size_t count, float min, float max, uint8_t flags, const std::string& debugMsg);

	std::vector<float>		readSingleArray(size_t count);
	std::vector<float>		readSingleArray(size_t count, float min, float max, uint8_t flags, const std::string& debugMsg);
	void					readSingleArray(float* ptr, size_t count);
	void					readSingleArray(float* ptr, size_t count, float min, float max, uint8_t flags, const std::string& debugMsg);

	std::vector<double>		readDoubleArray(size_t count);
	std::vector<double>		readDoubleArray(size_t count, double min, double max, uint8_t flags, const std::string& debugMsg);
	void					readDoubleArray(double* ptr, size_t count);
	void					readDoubleArray(double* ptr, size_t count, double min, double max, uint8_t flags, const std::string& debugMsg);

	std::string	readAsciiString(size_t len);

	virtual size_t getLength() = 0;
	virtual BinaryReader& seek(std::streamoff offset, std::ios_base::seekdir way) = 0;
	virtual size_t tell() = 0;
};
