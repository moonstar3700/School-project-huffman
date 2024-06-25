#ifdef TEST_BUILD

#include "encoding/encoding.h"
#include "encoding/encoding-combiner.h"
#include "encoding/eof-encoding.h"
#include "encoding/bit-grouper.h"
#include "io/binary-io.h"
#include "catch.hpp"
#include <memory>

TEST_CASE("Combiner test")
{
    encoding::Encoding<2, 256> grouper = encoding::bit_grouper<8>();
    encoding::Encoding<256, 257> eof = encoding::eof_encoding<256>();


    encoding::Encoding<2, 257> combined = grouper | eof;

    std::vector<u8> vector = { 0,0,0,0,1,0,1,1, 0,0,0,0,0,0,0,0 };

    io::MemoryBuffer<2> _first(vector);
    io::MemoryBuffer<257> _mid;
    io::MemoryBuffer<2> _last;

    encoding::encode(_first.source(), _mid.destination(), combined);
    encoding::decode(_mid.source(), _last.destination(), combined);

    REQUIRE(*_first.data() == *_last.data());


}
#endif