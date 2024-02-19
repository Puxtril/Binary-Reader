# C++ Binary Reader

Read binary data from files into C++ primitives. This provides readers for:

- (u)int8
- (u)int16
- (u)int32
- (u)int64
- Half-precision floats
- Single-precision floats
- Double-presicion floats
- Little/Big endian versions
- Array readers

## Floats
[Comparing floats is difficult.](https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/) This project casts floats to signed integers for comparisons, known as ULP comparisons. It also uses flags to account for special floats. These flags are defined in `BinaryReader.h` and are:
* `CONV_INF` - Converts +/- infinity to their respective integer min and max.
* `CONV_ZERO` - Converts -0 to 0
* `FAIL_SUBNORM` - Throws an exception if a subnormal float is read.

