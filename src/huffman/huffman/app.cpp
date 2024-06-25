#ifndef TEST_BUILD

/*
*   This file is only active in non-test builds (i.e., builds where TEST_BUILD is not defined).
*/

#include <iostream>
#include <memory>
#include "data/binary-tree.h"
#include "encoding/huffman/huffman-encoding.h"
#include "encoding/bit-grouper.h"
#include "encoding/eof-encoding.h"
#include "encoding/encoding.h"
#include "encoding/encoding-combiner.h"
#include "io/files.h"

void compress(const std::string& input_file, const std::string& output_file)
{
    std::cout << "Compressing..." << std::endl;

    const Datum N = 256;
    const auto eof = encoding::eof_encoding<N>();
    const auto huffman = encoding::huffman_encoding<N + 1>();
    const auto grouper = encoding::bit_grouper<8>();

    const auto combined = eof | huffman | grouper;

    encoding::encode(io::create_file_data_source(input_file), io::create_file_data_destination(output_file), combined);
}

void decompress(const std::string& input_file, const std::string& output_file)
{
    std::cout << "Decompressing..." << std::endl;

    const Datum N = 256;
    const auto eof = encoding::eof_encoding<N>();
    const auto huffman = encoding::huffman_encoding<N + 1>();
    const auto grouper = encoding::bit_grouper<8>();

    const auto combined = eof | huffman | grouper;

    encoding::decode(io::create_file_data_source(input_file), io::create_file_data_destination(output_file), combined);
}


int main(const int argc, char* argv[])
{
    for (int i = 0; argv[i] != NULL; ++i)
    {

        std::cout << i << ": " << argv[i] << "\n";
    }

    std::string WrongArgument = "Wrong arguments. (method, input.type, output.type)";

#ifdef NDEBUG
    if (argc != 4)
    {
        std::cout << WrongArgument << std::endl;
        return -1;
    }
    else
    {
        const std::string function(argv[1]);
        const std::string input_file(argv[2]);
        const std::string output_file(argv[3]);
        if (function == "compress")
        {
            compress(input_file, output_file);
            std::cout << "File " + input_file + " compressed successfully to " + output_file + "!" << std::endl;
            return 0;
        }
        else if (function == "decompress")
        {
            decompress(input_file, output_file);
            std::cout << "File " + input_file + " decompressed successfully to " + output_file + "!" << std::endl;
            return 0;
        }
        else
        {
            std::cout << WrongArgument << std::endl;
            return -1;
        }
    }
#else
#endif
}
#endif
