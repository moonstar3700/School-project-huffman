#ifdef TEST_BUILD

#include "io/binary-io.h"
#include "encoding/bit-grouper.h"
#include "encoding/encoding.h"
#include "io/memory-buffer.h"
#include "catch.hpp"
#include <Vector>

TEST_CASE("Bit grouper test") {

    io::MemoryBuffer<2> _in;
    io::MemoryBuffer<256> _out;

    auto data = _in.destination()->create_output_stream();

    data->write(0);
    data->write(0);
    data->write(0);
    data->write(0);
    data->write(1);
    data->write(0);
    data->write(1);
    data->write(1);
    data->write(1);
    data->write(0);

    encoding::encode<2, 256>(_in.source(), _out.destination(), encoding::bit_grouper<8>());
    auto& outbufferdata = *_out.data();

    REQUIRE(outbufferdata[0] == 11);
    REQUIRE(outbufferdata[1] == 128);
    REQUIRE(outbufferdata.size() == 2);

}

#endif