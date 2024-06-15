#pragma once

#include "BinaryReader.h"
#include "BinaryReaderExceptions.h"

#include <fstream>
#include <string>
#include <cstring>
#include <vector>

namespace BinaryReader
{
	class BinaryReaderSlice : public BinaryReader
	{
		size_t m_size;
		uint8_t* m_dataPtr;
		size_t m_curPos;

		void
		readBytes(void* dst, int count) override
		{
			std::memcpy(dst, m_dataPtr + m_curPos, count);
			m_curPos += count;
		}
		
		void
		readBytesBE(void* dst, int count) override
		{
			for (size_t i = 0; i < count; i++)
				std::memcpy((char*)dst + i, &m_dataPtr[m_curPos + count - i], 1);
			
			m_curPos += count;
		}

	public:
		BinaryReaderSlice()
			: m_curPos(0)
		{
		}

		BinaryReaderSlice(uint8_t* data, size_t size)
			: m_size(size), m_dataPtr(data), m_curPos(0)
		{
		}
		
		~BinaryReaderSlice()
		{
		}

		size_t
		getLength() override
		{
			return m_size;
		}

		const uint8_t*
		getPtr()
		{
			return m_dataPtr;
		}

		BinaryReaderSlice&
		seek(std::streamoff offset, std::ios_base::seekdir way = std::ios::cur) override
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
				m_curPos = m_size + offset;
				break;
			}
			return *this;
		}

		size_t
		tell() override
		{
			return m_curPos;
		}

		BinaryReaderSlice
		slice(size_t size)
		{
			BinaryReaderSlice ret(m_dataPtr + tell(), size);
			seek(size, std::ios::cur);
			return ret;
		}
	};
};