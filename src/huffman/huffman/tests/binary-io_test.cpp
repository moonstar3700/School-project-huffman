#ifdef TEST_BUILD

#include "catch.hpp"
#include <io/memory-buffer.h>
#include <io/binary-io.h>


void check(u64 n, unsigned nbits)
{
    io::MemoryBuffer<2> buffer;
    auto input = buffer.source()->create_input_stream();
    auto output = buffer.destination()->create_output_stream();
    io::write_bits(n, nbits, *output);
    auto result = io::read_bits(nbits, *input);

    REQUIRE(n == result);
}
void checkIncomplete(u64 n, unsigned nbits)
{
    io::MemoryBuffer<2> buffer;
    auto input = buffer.source()->create_input_stream();
    auto output = buffer.destination()->create_output_stream();

    io::write_bits(n, nbits, *output);
    auto result1 = io::read_bits(nbits, *input);

    io::write_bits(result1, nbits, *output);
    auto result2 = io::read_bits(nbits, *input);

    REQUIRE(result1 == result2);
}

TEST_CASE("IO Read&Write Test") {

    check(111, 7);
    check(64, 7);
    check(2048, 12);
    check(777, 10);
    check(50, 6);
    check(0, 1);
    check(1, 1);
    check(2, 2);
    check(9999999, 24);

    checkIncomplete(9999999, 3);
    checkIncomplete(1, 3);

    check('A', 8);
    check('.', 8);
    check('8', 8);

}


#endif