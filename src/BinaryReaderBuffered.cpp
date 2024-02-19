#include "BinaryReaderBuffered.h"

BinaryReaderBuffered::BinaryReaderBuffered()
	: m_data(nullptr), m_dataLen(0), m_curPos(0)
{
}

BinaryReaderBuffered::BinaryReaderBuffered(uint8_t* data, size_t dataLen)
	: m_data((char*)data), m_dataLen(dataLen), m_curPos(0)
{
}

BinaryReaderBuffered::~BinaryReaderBuffered()
{
	delete[] m_data;
}

size_t
BinaryReaderBuffered::getLength()
{
	return m_dataLen;
}

const char*
BinaryReaderBuffered::getPtr()
{
    return m_data;
}

void
BinaryReaderBuffered::read1Byte(char* dst)
{
	m_curPos += 1;
	std::memcpy(dst, &m_data[m_curPos - 1], 1);
}

void
BinaryReaderBuffered::read2Bytes(char* dst)
{
	m_curPos += 2;
	std::memcpy(dst, &m_data[m_curPos - 2], 2);
}

void
BinaryReaderBuffered::read2BytesBE(char* dst)
{
	std::memcpy(dst + 1, &m_data[m_curPos++], 1);
	std::memcpy(dst, &m_data[m_curPos++], 1);
}

void
BinaryReaderBuffered::read4Bytes(char* dst)
{
	m_curPos += 4;
	std::memcpy(dst, &m_data[m_curPos - 4], 4);
}

void
BinaryReaderBuffered::read4BytesBE(char* dst)
{
	std::memcpy(dst + 3, &m_data[m_curPos++], 1);
	std::memcpy(dst + 2, &m_data[m_curPos++], 1);
	std::memcpy(dst + 1, &m_data[m_curPos++], 1);
	std::memcpy(dst, &m_data[m_curPos++], 1);
}

void
BinaryReaderBuffered::read8Bytes(char* dst)
{
	m_curPos += 8;
	std::memcpy(dst, &m_data[m_curPos - 8], 8);
}

void
BinaryReaderBuffered::read8BytesBE(char* dst)
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

BinaryReaderBuffered&
BinaryReaderBuffered::seek(std::streamoff offset, std::ios_base::seekdir way)
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
BinaryReaderBuffered::tell()
{
    return m_curPos;
}
