
#ifdef TEST_BUILD
#include "catch.hpp"
#include "io/memory-buffer.h"
TEST_CASE("Memory buffer stream")
{
    auto original_data = std::make_shared<std::vector<Datum>>();
    original_data->push_back(0);
    original_data->push_back(1);
    original_data->push_back(2);
    original_data->push_back(3);

    auto input_stream = io::create_memory_input_stream(original_data);

    auto data_receiver = std::make_shared<std::vector<Datum>>();
    auto output_stream = io::create_memory_output_stream(data_receiver);


}

#endif
