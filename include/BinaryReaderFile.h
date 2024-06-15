#pragma once

#include "BinaryReaderExceptions.h"
#include "BinaryReader.h"

#include <fstream>
#include <cstdint>
#include <string>
#include <memory>

namespace BinaryReader
{
	class BinaryReaderFile : public BinaryReader
	{
		std::ifstream _reader;
		size_t m_length;

	private:
		void
		readBytes(void* dst, int count) override
		{
			this->_reader.read((char*)dst, count);
		}
		
		void
		readBytesBE(void* dst, int count) override
		{
			for (size_t i = count; i > 0; i--)
				this->_reader.read((char*)dst + i, 1);
		}

	public:
		BinaryReaderFile()
		{
			this->m_length = 0;
			this->seek(0, std::ios_base::beg);
		}

		BinaryReaderFile(const std::string& filePath)
		{
			this->_reader = std::ifstream(filePath, std::ifstream::in | std::ifstream::binary);

			if (this->_reader.fail())
				throw std::runtime_error("File does not exist");
			
			this->setLength();
			this->seek(0, std::ios_base::beg);
		}

		size_t
		getLength() override
		{
			return this->m_length;
		}

		BinaryReaderFile&
		seek(std::streamoff offset, std::ios_base::seekdir way = std::ios::cur) override
		{
			_reader.seekg(offset, way);
			return *this;
		}

		size_t
		tell() override
		{
			return (size_t)this->_reader.tellg();
		}

	private:
		void
		setLength()
		{
			this->seek(0, std::ios_base::end);
			this->m_length = this->tell();
		}
	};
};