#pragma once

#include "BinaryReaderExceptions.h"
#include "BinaryReader.h"

#include <fstream>
#include <cstdint>
#include <string>
#include <memory>

#ifdef __cpp_lib_filesystem
	#define USING_FILESYSTEM 1
	#include <filesystem>
	namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
	#define USING_FILESYSTEM 1
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif

namespace BinaryReader
{
	class BinaryReaderFile : public BinaryReader
	{
		std::ifstream _reader;
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
		
		#ifdef USING_FILESYSTEM
		BinaryReaderFile(const fs::path& filePath) : BinaryReaderFile(filePath.string()) {}
		#endif

		size_t
		getLength() override
		{
			return this->m_length;
		}

		BinaryReaderFile&
		seek(std::streamoff offset, std::ios_base::seekdir way) override
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