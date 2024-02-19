#include "BinaryReaderFile.h"

BinaryReaderFile::BinaryReaderFile()
{
    this->m_length = 0;
    this->seek(0, std::ios_base::beg);
}

BinaryReaderFile::BinaryReaderFile(const std::string& filePath)
{
	this->_reader = std::ifstream(filePath, std::ifstream::in | std::ifstream::binary);

	if (this->_reader.fail())
		throw std::runtime_error("File does not exist");
    
    this->setLength();
    this->seek(0, std::ios_base::beg);
}

void
BinaryReaderFile::read1Byte(char* dst)
{
	this->_reader.read(dst, 1);
}

void
BinaryReaderFile::read2Bytes(char* dst)
{
	this->_reader.read(dst, 2);
}

void
BinaryReaderFile::read2BytesBE(char* dst)
{
	this->_reader.read(dst + 1, 1);
	this->_reader.read(dst, 1);
}

void
BinaryReaderFile::read4Bytes(char* dst)
{
	this->_reader.read(dst, 4);
}

void
BinaryReaderFile::read4BytesBE(char* dst)
{
	this->_reader.read(dst + 3, 1);
	this->_reader.read(dst + 2, 1);
	this->_reader.read(dst + 1, 1);
	this->_reader.read(dst, 1);
}

void
BinaryReaderFile::read8Bytes(char* dst)
{
	this->_reader.read(dst, 8);
}

void
BinaryReaderFile::read8BytesBE(char* dst)
{
	this->_reader.read(dst + 7, 1);
	this->_reader.read(dst + 6, 1);
	this->_reader.read(dst + 5, 1);
	this->_reader.read(dst + 4, 1);
	this->_reader.read(dst + 3, 1);
	this->_reader.read(dst + 2, 1);
	this->_reader.read(dst + 1, 1);
	this->_reader.read(dst, 1);
}

size_t
BinaryReaderFile::getLength()
{
    return this->m_length;
}

BinaryReaderFile& BinaryReaderFile::seek(std::streamoff offset, std::ios_base::seekdir way)
{
    _reader.seekg(offset, way);
    return *this;
}

size_t BinaryReaderFile::tell()
{
    return (size_t)this->_reader.tellg();
}

void
BinaryReaderFile::setLength()
{
    this->seek(0, std::ios_base::end);
    this->m_length = this->tell();
}
