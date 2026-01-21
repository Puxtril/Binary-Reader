#pragma once

#include "BinaryReader/BinaryReader.h"

#include <fstream>
#include <cstdint>
#include <string>
#include <memory>

namespace BinaryReader
{
	class FileSlice : public BinaryReader
	{
		std::ifstream _reader;
        std::string m_filePath;
        size_t m_start;
		size_t m_length;

	private:
		void
		read1Byte(uint8_t* dst) override
		{
			this->_reader.read((char*)dst, 1);
		}

		void
		read2Bytes(uint8_t* dst) override
		{
			this->_reader.read((char*)dst, 2);
		}

		void
		read2BytesBE(uint8_t* dst) override
		{
			this->_reader.read((char*)dst + 1, 1);
			this->_reader.read((char*)dst, 1);
		}

		void
		read4Bytes(uint8_t* dst) override
		{
			this->_reader.read((char*)dst, 4);
		}

		void
		read4BytesBE(uint8_t* dst) override
		{
			this->_reader.read((char*)dst + 3, 1);
			this->_reader.read((char*)dst + 2, 1);
			this->_reader.read((char*)dst + 1, 1);
			this->_reader.read((char*)dst, 1);
		}

		void
		read8Bytes(uint8_t* dst) override
		{
			this->_reader.read((char*)dst, 8);
		}

		void
		read8BytesBE(uint8_t* dst) override
		{
			this->_reader.read((char*)dst + 7, 1);
			this->_reader.read((char*)dst + 6, 1);
			this->_reader.read((char*)dst + 5, 1);
			this->_reader.read((char*)dst + 4, 1);
			this->_reader.read((char*)dst + 3, 1);
			this->_reader.read((char*)dst + 2, 1);
			this->_reader.read((char*)dst + 1, 1);
			this->_reader.read((char*)dst, 1);
		}

	public:
		FileSlice()
		{
			this->m_length = 0;
            this->m_start = 0;
			this->seek(0, std::ios_base::beg);
		}

		FileSlice(const std::string& filePath, size_t offset)
		{
			this->_reader = std::ifstream(filePath, std::ifstream::in | std::ifstream::binary);
            m_filePath = filePath;

			if (this->_reader.fail())
				throw std::runtime_error("File does not exist");
			
            this->m_start = offset;
			this->setLength();
			this->seek(0, std::ios_base::beg);
		}
		
		#ifdef USING_FILESYSTEM
		File(const fs::path& filePath) : File(filePath.string()) {}
		#endif

		size_t
		getLength() override
		{
			return this->m_length;
		}

		FileSlice&
		seek(std::streamoff offset, std::ios_base::seekdir way) override
		{
            if (way == std::ios::beg)
                _reader.seekg(m_start + offset, way);
            else
			    _reader.seekg(offset, way);

			return *this;
		}

		size_t
		tell() override
		{
			return (size_t)this->_reader.tellg() - m_start;
		}

        BinaryReader
		slice(size_t size) override
		{
			FileSlice slice(m_filePath, tell() + m_start);
			seek(size, std::ios::cur);
			return slice;
		}

		FileSlice
		getSlice(size_t size)
		{
			FileSlice slice(m_filePath, tell() + m_start);
			seek(size, std::ios::cur);
			return slice;
		}

	private:
		void
		setLength()
		{
			this->seek(0, std::ios_base::end);
			this->m_length = this->tell() - m_start;
		}
	};
};