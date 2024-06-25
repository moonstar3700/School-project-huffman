#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include "data/binary-tree.h"
#include "encoding/encoding.h"
#include "data/frequency-table.h"
#include "util.h"





u64 get_weight(const data::Node<std::pair<Datum, unsigned>>& node);
std::shared_ptr<encoding::EncodingImplementation> create_huffman_implementation(u64 domain_size);
std::unique_ptr<data::Node<std::pair<Datum, unsigned>>> getbuild_tree(const std::shared_ptr<data::FrequencyTable<Datum>> frequency_table);
std::map<Datum, std::vector<Datum>> getbuild_codes(const std::shared_ptr<data::FrequencyTable<Datum>> frequency_table);

namespace encoding
{

	template<u64 N>
	encoding::Encoding<N, 2> huffman_encoding() {
		auto encoder = Encoding<N, 2>(create_huffman_implementation(N));
		return encoder;
	}
}



#endif
