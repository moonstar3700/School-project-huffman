#include "data/binary-tree.h"
#include "util.h"
#include "io/streams.h"

namespace encoding {

	void encode_tree(const data::Node<std::pair<Datum, unsigned>>& root, unsigned nbits, io::OutputStream& output);
	std::unique_ptr<data::Node<Datum>> decode_tree(io::InputStream& input, unsigned nbits);

}