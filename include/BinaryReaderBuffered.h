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

	void
	read1Byte(char* dst) override
	{
		m_curPos += 1;
		std::memcpy(dst, &m_data[m_curPos - 1], 1);
	}

	void
	read2Bytes(char* dst) override
	{
		m_curPos += 2;
		std::memcpy(dst, &m_data[m_curPos - 2], 2);
	}

	void
	read2BytesBE(char* dst) override
	{
		std::memcpy(dst + 1, &m_data[m_curPos++], 1);
		std::memcpy(dst, &m_data[m_curPos++], 1);
	}

	void
	read4Bytes(char* dst) override
	{
		m_curPos += 4;
		std::memcpy(dst, &m_data[m_curPos - 4], 4);
	}

	void
	read4BytesBE(char* dst) override
	{
		std::memcpy(dst + 3, &m_data[m_curPos++], 1);
		std::memcpy(dst + 2, &m_data[m_curPos++], 1);
		std::memcpy(dst + 1, &m_data[m_curPos++], 1);
		std::memcpy(dst, &m_data[m_curPos++], 1);
	}

	void
	read8Bytes(char* dst) override
	{
		m_curPos += 8;
		std::memcpy(dst, &m_data[m_curPos - 8], 8);
	}

	void
	read8BytesBE(char* dst) override
	{
		std::memcpy(dst + 7, &m_data[m_curPos++], 1);
		std::memcpy(dst + 6, &m_data[m_curPos++], 1);
		std::memcpy(dst + 5, &m_data[m_curPos++], 1);
		std::memcpy(dst + 4, &m_data[m_curPos++], 1);
		std::memcpy(dst + 3, &m_data[m_curPos++], 1);
		std::memcpy(dst + 2, &m_data[m_curPos++], 1);
		std::memcpy(dst + 1, &m_data[m_curPos++], 1);
		std::memcpy(dst, &m_data[m_curPos++], 1);
	}

public:
	BinaryReaderBuffered()
		: m_data(nullptr), m_dataLen(0), m_curPos(0)
	{
	}

	BinaryReaderBuffered(uint8_t* data, size_t dataLen)
		: m_data((char*)data), m_dataLen(dataLen), m_curPos(0)
	{
	}

	BinaryReaderBuffered(const BinaryReaderBuffered& other) = delete;
	~BinaryReaderBuffered()
	{
		delete[] m_data;
	}

	BinaryReaderBuffered& operator=(const BinaryReaderBuffered& other) = delete;

	size_t
	getLength() override
	{
		return m_dataLen;
	}

	const char*
	getPtr()
	{
		return m_data;
	}


	BinaryReaderBuffered&
	seek(std::streamoff offset, std::ios_base::seekdir way) override
	{
		switch (way)
		{
		case std::ios_base::beg:
			m_curPos = offset;
			break;
		case std::ios_base::cur:
			m_curPos += offset;
			break;
		case std::ios_base::end:
			m_curPos = m_dataLen + offset;
			break;
		}
		return *this;
	}

	size_t
	tell() override
	{
		return m_curPos;
	}

};
