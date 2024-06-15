#pragma once

#include "BinaryReader.h"
#include "BinaryReaderSlice.h"
#include "BinaryReaderExceptions.h"

#include <fstream>
#include <string>
#include <cstring>
#include <vector>

namespace BinaryReader
{
	class BinaryReaderBuffered : public BinaryReader
	{
		std::vector<uint8_t> m_data;
		size_t m_curPos;

		void
		readBytes(void* dst, int count) override
		{
			std::memcpy(dst, m_data.data() + m_curPos, count);
			m_curPos += count;
		}
		
		void
		readBytesBE(void* dst, int count) override
		{
			for (size_t i = 0; i < count; i++)
				std::memcpy((char*)dst + i, &m_data[m_curPos + count - i], 1);
			
			m_curPos += count;
		}

	public:
		BinaryReaderBuffered()
			: m_data(), m_curPos(0)
		{
		}

		BinaryReaderBuffered(std::vector<uint8_t>&& data)
			: m_data(data), m_curPos(0)
		{
		}
		
		~BinaryReaderBuffered()
		{
		}


		size_t
		getLength() override
		{
			return m_data.size();
		}

		const std::vector<uint8_t>&
		getPtr()
		{
			return m_data;
		}

		BinaryReaderBuffered&
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
				m_curPos = m_data.size() + offset;
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
			BinaryReaderSlice ret(m_data.data() + tell(), size);
			seek(size, std::ios::cur);
			return ret;
		}
	};
};