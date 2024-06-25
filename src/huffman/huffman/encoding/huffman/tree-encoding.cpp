#ifndef BINARYIO_CPP
#define BINARYIO_CPP
#include <cmath>
#include <assert.h>
#include <memory>
#include <data/binary-tree.h>
#include <util.h>
#include <io/streams.h>
#include <io/binary-io.h>
#include "tree-encoding.h"

namespace encoding {

    void encode_tree(const data::Node<std::pair<Datum, unsigned>>& root, unsigned nbits, io::OutputStream& output) {

        if (!root.isLeaf()) {
            auto& node = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(root);
            output.write(1);
            encode_tree(node.getLeftNode(), nbits, output);
            encode_tree(node.getRightNode(), nbits, output);
        }
        else {
            auto& node = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(root);
            output.write(0);
            io::write_bits(node.getValue().first, nbits, output);
        }

    }
    std::unique_ptr<data::Node<Datum>> decode_tree(io::InputStream& input, unsigned nbits) {
        if (input.read() == 1) {
            auto left_node = decode_tree(input, nbits);
            auto right_node = decode_tree(input, nbits);
            return std::make_unique<data::Branch<Datum>>(std::move(left_node), std::move(right_node));
        }
        else {
            auto leaf = io::read_bits(nbits, input);
            return std::make_unique<data::Leaf<Datum>>(leaf);
        }

    }
}

#endif

