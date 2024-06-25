
#include "catch.hpp"
#include <iostream>
#include <memory>
#include "data/binary-tree.h"
#include "encoding/huffman/huffman-encoding.h"
#include "encoding/bit-grouper.h"
#include "encoding/eof-encoding.h"
#include "encoding/encoding.h"
#include "encoding/encoding-combiner.h"
#include "io/files.h"

#ifdef TEST_BUILD


TEST_CASE("Main Test")
{

    const Datum N = 256;
    const auto eof = encoding::eof_encoding<N>();
    const auto huffman = encoding::huffman_encoding<N + 1>();
    const auto grouper = encoding::bit_grouper<8>();

    const auto combined = eof | huffman | grouper;
    std::vector<u8> vector = { '1', '1','1', '0', '8' };

    io::MemoryBuffer<256> _first(vector);
    io::MemoryBuffer<256> _mid;
    io::MemoryBuffer<256> _last;

    encoding::encode(_first.source(), _mid.destination(), combined);
    encoding::decode(_mid.source(), _last.destination(), combined);


    REQUIRE(*_first.data() == *_last.data());

}



#endif
