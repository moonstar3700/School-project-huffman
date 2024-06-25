#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/eof-encoding.h"
#include <vector>

#include <algorithm>

#include <vector>
#include <string>
#include <iostream>

TEST_CASE("EOF Encoder")
{
    io::MemoryBuffer<17> inbuffer;
    auto data = inbuffer.destination()->create_output_stream();

    for (int i = 0; i <= 16; i++) {
        data->write(0);
    }

    io::MemoryBuffer<18> outbuffer;

    auto source = inbuffer.source();
    auto destination = outbuffer.destination();

    auto encoding = encoding::eof_encoding<17>();

    encoding::encode<17, 18>(source, destination, encoding);

    auto outbufferdata = *outbuffer.data().get();
    REQUIRE(outbufferdata.size() == 18);
    auto result = *find(outbufferdata.begin(), outbufferdata.end(), 17);
    REQUIRE(result == 17);
}


#endif