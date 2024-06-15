# C++ Binary Reader (Concepts Edition)

Read binary data from files into C++ primitives. This library utilizes templates + concepts to simplify the interface. But let's just jump into some examples.

## Creating the Reader

```cpp
#include "BinaryReaderFile.h"
#include "BinaryReaderBuffered.h"
#include "BinaryReaderSlice.h"

#include <cstdint>

int main()
{
    // Create a reader from a file path
    // This uses `std::ifstream` internally
    BinaryReader::BinaryReaderFile readerFile("data.bin");

    // Create from a buffer
    std::vector<uint8_t> rawData;
    // Fill vector with data
    BinaryReader::BinaryReaderBuffered readerBuff(std::move(rawData));

    // Create a "view" that doesn't transfer data ownership
    // Helpful if you need to pass a reader to a function but want to
    //   manage the position and size
    std::vector<uint8_t> rawData2(1024);
    BinaryReader::BinaryReaderSlice readerSlice(rawData2.data() + 512, 512);

    // All interfaces support these basic file operations
    readerFile.seek(5, std::ios::beg);
    size_t len = readerFile.getLength();
    size_t curPos = readerFile.tell();
}
```

## Reading Scalars

```cpp
#include "BinaryReaderFile.h"
#include <cstdint>

int main()
{
    BinaryReader::BinaryReaderFile reader("data.bin");

    // Read an Unsigned 32-bit integer as little endian (default) and big endian
    reader.readScalar<uint32_t>();
    reader.readScalarBE<uint32_t>();

    // Any integer can be used
    // You *could* use variable width integers... but like... don't
    reader.readScalar<char>();
    reader.readScalar<uint8_t>();
    reader.readScalarBE<int16_t>();
    reader.readScalar<uint64_t>();

    // Sometimes you want to bound-check the values
    // If the value here isn't between 0 and 10 (inclusive/exclusive)
    //    a BinaryReader::LimitException will be thrown.
    // The 3rd argument is a message that will be included in LimitException
    reader.readScalarSafe<uint32_t>(0, 10, "Value must be less than 10");

    // You can also restrict to just 1 value    
    reader.readScalarSafe<uint32_t>(9, "Value must be 9");
}
```

## Arrays

```cpp
#include "BinaryReaderFile.h"
#include <cstdint>

int main()
{ 
    BinaryReader::BinaryReaderFile reader("data.bin");
    std::vector<uint32_t> ints(20);

    // Reading arrays is very similar to the scalar interface
    reader.readScalarArray<uint32_t>(ints.data(), 20);
    reader.readScalarArrayBE<uint32_t>(ints.data(), 20);

    // Bounds-checking is also available
    // Thrown LimitExceptions will include the index of the limit-breached value
    // The index is also stored inside the exception `LimitException.index`
    reader.readScalarArraySafe<uint32_t>(ints.data(), 20, 0, 10, "Value must be less than 10");
    reader.readScalarArraySafe<uint32_t>(ints.data(), 20, 9, "Value must be 9");
}
```

## Floats

```cpp
#include "BinaryReaderFile.h"
#include <cstdint>

int main()
{
    BinaryReader::BinaryReaderFile reader("data.bin");
    std::vector<float> floats(20);

    // Floats can also be read like integers
    reader.readScalar<float>();
    reader.readScalar<double>();

    // Arrays too
    reader.readScalarArray<float>(floats.data(), 20);

    // Comparing floats however requires accounting for the edge cases
    // The interface for reading floats with bound-checking adds 1 extra parameter for flags
    // See below for a description of these flags
    reader.readScalarArraySafe<float>(floats.data(), 20, 0.0F, 10.0F, CONV_INF | CONV_ZERO | FAIL_SUBNORM, "Value must be less than 10");
    reader.readScalarArraySafe<float>(floats.data(), 20, 9.0F, CONV_INF | CONV_ZERO | FAIL_SUBNORM, "Value must be 9");

    // These can also be ignored
    // But you must pass 0 for flags to acknowlege these edge cases are being ignored
    reader.readScalarArraySafe<float>(floats.data(), 20, 9.0F, 0, "Value must be 9");
}
```

[Comparing floats is difficult.](https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/) This project casts floats to signed integers for comparisons, known as ULP comparisons. It also uses flags to account for special floats. These flags are defined in `BinaryReader.h` and are:
* `CONV_INF` - Converts +/- infinity to their respective integer min and max.
* `CONV_ZERO` - Converts -0 to 0
* `FAIL_SUBNORM` - Throws an exception if a subnormal float is read.


## Variable Width Integers

```cpp
#include "BinaryReaderFile.h"
#include <cstdint>
#include <iostream>

int main()
{
    BinaryReader::BinaryReaderFile reader("data.bin");

    // Scalars can be read with variable bit widths
    // The destination type must be specified
    uint32_t bitInt = reader.readBitwiseScalar<uint32_t>(24);

    // Signed integers will be converted assuming the source integer's most-signifigant bit is signed
    int32_t bitIntS = reader.readBitwiseScalar<int32_t>(24);

    // Bit offset is stored internally, so sequential bit-wise reads start at the previous stop
    BinaryReader::BinaryReaderFile reader2("data.bin");
    std::cout << reader2.tell() << ", " << reader2.tellBit() << std::endl; // 0, 0
    reader2.readBitwiseScalar<uint8_t>(5);
    std::cout << reader2.tell() << ", " << reader2.tellBit() << std::endl; // 0, 5
    reader2.readBitwiseScalar<uint8_t>(6);
    std::cout << reader2.tell() << ", " << reader2.tellBit() << std::endl; // 1, 3
    reader2.readBitwiseScalar<uint8_t>(5);
    std::cout << reader2.tell() << ", " << reader2.tellBit() << std::endl; // 2, 0

    // You can also seek bits
    reader2.seekBit(17, std::ios::beg);
    std::cout << reader2.tell() << ", " << reader2.tellBit() << std::endl; // 2, 1
    reader2.seekBit(-8, std::ios::cur);
    std::cout << reader2.tell() << ", " << reader2.tellBit() << std::endl; // 1, 1
    reader2.seekBit(-1, std::ios::end);
    std::cout << reader2.tell() << ", " << reader2.tellBit() << std::endl; // 1, 6

    // When you switch between bit/byte reading, the current bit offset should be taken into account
    // When the current bitoffset != 0, reading a scalar will *not* reset it to 0
    // One of thse should be run manually
    // Seeks to the beginning of the current byte
    reader2.seekBit(0, std::ios::beg);
    // Seeks 1 past the end of the current byte (0 of next byte)
    reader2.seekBit(1, std::ios::end);
}
```