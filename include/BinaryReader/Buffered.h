#pragma once

#include "BinaryReader/BinaryReader.h"
#include "BinaryReader/BufferedSlice.h"
#include "BinaryReader/Exceptions.h"

#include <fstream>
#include <string>
#include <cstring>
#include <vector>

namespace BinaryReader
{
	class Buffered : public BinaryReader
	{
		std::vector<uint8_t> m_data;
		size_t m_curPos;

		void
		read1Byte(uint8_t* dst) override
		{
			m_curPos += 1;
			std::memcpy(dst, &m_data[m_curPos - 1], 1);
		}

		void
		read2Bytes(uint8_t* dst) override
		{
			m_curPos += 2;
			std::memcpy(dst, &m_data[m_curPos - 2], 2);
		}

		void
		read2BytesBE(uint8_t* dst) override
		{
			std::memcpy(dst + 1, &m_data[m_curPos++], 1);
			std::memcpy(dst, &m_data[m_curPos++], 1);
		}

		void
		read4Bytes(uint8_t* dst) override
		{
			m_curPos += 4;
			std::memcpy(dst, &m_data[m_curPos - 4], 4);
		}

		void
		read4BytesBE(uint8_t* dst) override
		{
			std::memcpy(dst + 3, &m_data[m_curPos++], 1);
			std::memcpy(dst + 2, &m_data[m_curPos++], 1);
			std::memcpy(dst + 1, &m_data[m_curPos++], 1);
			std::memcpy(dst, &m_data[m_curPos++], 1);
		}

		void
		read8Bytes(uint8_t* dst) override
		{
			m_curPos += 8;
			std::memcpy(dst, &m_data[m_curPos - 8], 8);
		}

		void
		read8BytesBE(uint8_t* dst) override
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
		Buffered()
			: m_data(), m_curPos(0)
		{
		}

		Buffered(std::vector<uint8_t>&& data)
			: m_data(data), m_curPos(0)
		{
		}
		
		~Buffered()
		{
		}

		std::string
        readAsciiString(size_t len) override
        {
            char *data = reinterpret_cast<char *>(m_data.data() + tell());
            m_curPos += len;
            return {data, len};
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

		Buffered&
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

		BufferedSlice
		slice(size_t size)
		{
			BufferedSlice ret(m_data.data() + tell(), size);
			seek(size, std::ios::cur);
			return ret;
		}
	};
};