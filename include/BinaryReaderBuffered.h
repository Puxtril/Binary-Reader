#pragma once

#include "BinaryReader.h"
#include "BinaryReaderExceptions.h"

#include <fstream>
#include <string>
#include <cstring>

class BinaryReaderBuffered : public BinaryReader
{
	char* m_data;
	size_t m_dataLen;
	size_t m_curPos;

	void read1Byte(char* dst) override;
	void read2Bytes(char* dst) override;
	void read2BytesBE(char* dst) override;
	void read4Bytes(char* dst) override;
	void read4BytesBE(char* dst) override;
	void read8Bytes(char* dst) override;
	void read8BytesBE(char* dst) override;

public:
	BinaryReaderBuffered();
	BinaryReaderBuffered(uint8_t* data, size_t dataLen);
	BinaryReaderBuffered(const BinaryReaderBuffered& other) = delete;
	~BinaryReaderBuffered();

	BinaryReaderBuffered& operator=(const BinaryReaderBuffered& other) = delete;
	size_t getLength() override;
	const char* getPtr();

	BinaryReaderBuffered& seek(std::streamoff offset, std::ios_base::seekdir way) override;
	size_t tell() override;
};
