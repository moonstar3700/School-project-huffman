#ifdef TEST_BUILD
#include "data/binary-tree.h"
#include "catch.hpp"
#include "data/frequency-table.h"
#include "encoding/huffman/huffman-encoding.h"
#include "encoding/bit-grouper.h"
#include "encoding/eof-encoding.h"
#include "encoding/encoding.h"
#include "encoding/encoding-combiner.h"
#include "util.h"


TEST_CASE("Build tree test")
{
    auto freqTable = std::make_shared<data::FrequencyTable<Datum>>();

    freqTable->increment(1230);

    freqTable->increment(356);
    freqTable->increment(356);

    freqTable->increment(2);
    freqTable->increment(2);
    freqTable->increment(2);

    freqTable->increment(1);
    freqTable->increment(1);
    freqTable->increment(1);
    freqTable->increment(1);

    freqTable->increment('A');
    freqTable->increment(*"A");
    freqTable->increment(*"A");
    freqTable->increment(*"A");
    freqTable->increment(*"A");
    freqTable->increment(*"A");

    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");

    auto root = std::move(getbuild_tree(freqTable));

    REQUIRE(!root->isLeaf());
    auto& rootbranch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(*root);

    REQUIRE(rootbranch.getLeftNode().isLeaf());
    REQUIRE(!rootbranch.getRightNode().isLeaf());

    auto& l0_leftleaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(rootbranch.getLeftNode());
    auto& l0_branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(rootbranch.getRightNode());

    REQUIRE(l0_leftleaf.getValue().first == 'B');

    auto& l1_leftleaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(l0_branch.getLeftNode());
    auto& l1_branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(l0_branch.getRightNode());

    REQUIRE(l1_leftleaf.getValue().first == 'A');

    auto& l2_leftleaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(l1_branch.getLeftNode());
    auto& l2_branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(l1_branch.getRightNode());

    REQUIRE(l2_leftleaf.getValue().first == 1);

}


TEST_CASE("Build tree test 1")
{
    auto freqTable = std::make_shared<data::FrequencyTable<Datum>>();

    freqTable->increment(1230);

    freqTable->increment(356);
    freqTable->increment(356);

    freqTable->increment(2);
    freqTable->increment(2);
    freqTable->increment(2);

    freqTable->increment(1);
    freqTable->increment(1);
    freqTable->increment(1);
    freqTable->increment(1);

    freqTable->increment('A');
    freqTable->increment(*"A");
    freqTable->increment(*"A");
    freqTable->increment(*"A");
    freqTable->increment(*"A");
    freqTable->increment(*"A");

    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");
    freqTable->increment(*"B");

    auto root = std::move(getbuild_tree(freqTable));

    REQUIRE(!root->isLeaf());
    auto& rootbranch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(*root);

    REQUIRE(rootbranch.getLeftNode().isLeaf());
    REQUIRE(!rootbranch.getRightNode().isLeaf());

    auto& l0_leftleaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(rootbranch.getLeftNode());
    auto& l0_branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(rootbranch.getRightNode());

    REQUIRE(l0_leftleaf.getValue().first == 'B');

    auto& l1_leftleaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(l0_branch.getLeftNode());
    auto& l1_branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(l0_branch.getRightNode());

    REQUIRE(l1_leftleaf.getValue().first == 'A');

    auto& l2_leftleaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(l1_branch.getLeftNode());
    auto& l2_branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(l1_branch.getRightNode());

    REQUIRE(l2_leftleaf.getValue().first == 1);

}
TEST_CASE("building tree test 3")  
{

    std::vector<Datum> input = { 'B', 'A', 'C', 'A', 'B', 'A', 'A' };
    auto freq = std::make_shared<data::FrequencyTable<Datum>>(data::count_frequencies(input));


    auto tree = std::move(getbuild_tree(freq));



    const data::Branch<std::pair<Datum, unsigned>>& tree_root = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(*tree);
    REQUIRE(get_weight(tree_root) == 7);

    auto& branch1 = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(tree_root.getLeftNode());
    assert(&branch1 != nullptr);
    REQUIRE(get_weight(branch1) == 3);


}


TEST_CASE("Build codes test 1")
{
    auto freqTable = std::make_shared<data::FrequencyTable<Datum>>();
    freqTable->increment(1);
    freqTable->increment(1);
    freqTable->increment(1);
    freqTable->increment(1);


    freqTable->increment(2);
    freqTable->increment(2);



    auto codes = getbuild_codes(freqTable);
    REQUIRE(codes.size() == 2);
}


TEST_CASE("huffmanTree returns same")
{

    const Datum N = 256;
    const auto eof = encoding::eof_encoding<N>();
    const auto huffman = encoding::huffman_encoding<N + 1>();

    io::MemoryBuffer<8> inbuffer;
    auto output = inbuffer.destination()->create_output_stream();
    auto input = inbuffer.source()->create_input_stream();

    auto combined = eof | huffman;

    for (int i = 0; i <= 16; i++) {
        output->write(*"A");
    }
    std::vector<u8> vector = { 0,0,0,0,1,0,1,1, 0,0,0,0,0,0,0,0 };

    io::MemoryBuffer<256> _first(vector);
    io::MemoryBuffer<2> _mid;
    io::MemoryBuffer<256> _last;

    encoding::encode(_first.source(), _mid.destination(), combined);
    encoding::decode(_mid.source(), _last.destination(), combined);

    REQUIRE(*_first.data() == *_last.data());


}


#endif
