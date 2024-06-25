#include "encoding/encoding.h"
#include "data/frequency-table.h"
#include "encoding/huffman/tree-encoding.h"
#include <memory>
#include <vector>
#include <util.h>
#include <data/binary-tree.h>
#include <algorithm>
#include <assert.h>


namespace {

	std::vector<Datum> streamToVector(io::InputStream& input) {
		std::vector<Datum> vector;
		while (!input.end_reached()) {
			vector.push_back(input.read());
		}
		return vector;
	}

	unsigned weight(const data::Node<std::pair<Datum, unsigned >>& tree) {
		if (tree.isLeaf()) {
			auto& leaf = *static_cast<const data::Leaf<std::pair<Datum, unsigned >>*> (&tree);
			assert(leaf.getValue().second != 0);
			return leaf.getValue().second;
		}
		auto& branch = *static_cast<const data::Branch<std::pair<Datum, unsigned >>*> (&tree);
		return weight(branch.getLeftNode()) + weight(branch.getRightNode());
	}



	std::unique_ptr<data::Node<std::pair<Datum, unsigned>>> build_tree(data::FrequencyTable<Datum>& freq) {

		std::vector<std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>> vector = freq.getAsleaves();

		assert(vector.size() != 0);

		auto pop = [&vector]() {
			auto leaf = std::move(vector.back());
			vector.pop_back();
			return leaf;
		};

		std::function<bool(std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>&, std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>&)> lambda = [](
			std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>& p1,
			std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>& p2
			) { return weight(*p1) > weight(*p2); };


		while (vector.size() > 1) { 
			auto leftleaf = pop(); 
			auto rightleaf = pop(); 		

			auto newBranch = std::make_unique<data::Branch<std::pair<Datum, unsigned>>>(std::move(leftleaf), std::move(rightleaf));



			vector.push_back(std::move(newBranch));
			std::sort(vector.begin(), vector.end(), lambda);
		}

		return std::move(vector[0]);
	}

	std::vector<Datum> addBit(std::vector<Datum> bits, Datum bit) {
		bits.push_back(bit);
		return bits;
	}

	void build_vector(const data::Node<std::pair<Datum, unsigned>>& node, std::vector<Datum> bits, std::map<Datum, std::vector<Datum>>& codes, unsigned depth) {
		if (node.isLeaf()) {
			auto& current_leaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(node);
			std::vector<Datum> code(bits.end() - depth, bits.end());
			codes.insert(std::pair<Datum, std::vector<Datum>>(current_leaf.getValue().first, bits));
		}
		else {
			const auto& current_branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(node);
			unsigned new_depth = depth + 1;
			if (&current_branch.getLeftNode() != nullptr) {
				build_vector(current_branch.getLeftNode(), addBit(bits, 0), codes, new_depth);
			}
			if (&current_branch.getRightNode() != nullptr) {
				build_vector(current_branch.getRightNode(), addBit(bits, 1), codes, new_depth);
			}
		}
	}

	std::map<Datum, std::vector<Datum>> build_codes(const data::Node<std::pair<Datum, unsigned>>& root) {
		std::map<Datum, std::vector<Datum>> codes;
		std::vector<Datum> bits;
		build_vector(root, bits, codes, 0);
		return codes;
	}


	void encode_data(std::map<Datum, std::vector<Datum>>& codes, const std::vector<Datum>& data, io::OutputStream& outputStream) {
		for (auto value : data) {
			auto bits = codes[value];
			for (auto bit : bits) {
				outputStream.write(bit);
			}
		}
	}

	Datum decode_single_datum(const data::Node<Datum>& root, io::InputStream& input)
	{
		auto current = &root;
		while (!current->isLeaf()) {
			if (input.end_reached()) {
				return 0;
			}
			auto& branch = static_cast<const data::Branch<Datum>&>(*current);
			if (input.read() == 0) {
				current = &branch.getLeftNode();
			}
			else {
				current = &branch.getRightNode();
			}
		}
		auto& leaf = static_cast<const data::Leaf<Datum>&>(*current);
		return leaf.getValue();
	}


	void decode_bits(io::InputStream& input_stream, io::OutputStream& output_stream, data::Node<Datum>& root) {
		while (!input_stream.end_reached()) {
			Datum data = decode_single_datum(root, input_stream);
			output_stream.write(data);
		}
	}


	class HuffmanEncodingImplementation : public encoding::EncodingImplementation {
	private:
		const Datum _domain_size;

	public:
		HuffmanEncodingImplementation(const Datum domain_size) : EncodingImplementation(), _domain_size(domain_size) {}

		virtual void encode(io::InputStream& input, io::OutputStream& output) {

			auto vector = streamToVector(input);
			data::FrequencyTable<Datum> freqtable = data::FrequencyTable<Datum>(vector);
			std::unique_ptr<data::Node<std::pair<Datum, unsigned>>> root = build_tree(freqtable);

			int actualbits = bits_needed(_domain_size);
			encoding::encode_tree(*root, actualbits, output);

			auto codes = build_codes(*root);
			encode_data(codes, vector, output);

		}
		virtual void decode(io::InputStream& input, io::OutputStream& output) {
			auto root = encoding::decode_tree(input, bits_needed(_domain_size));
			assert(!root->isLeaf());
			decode_bits(input, output, *root);
		}
	};



}


u64 get_weight(const data::Node<std::pair<Datum, unsigned>>& node) {
	return weight(node);
}
std::shared_ptr<encoding::EncodingImplementation> create_huffman_implementation(u64 domain_size)
{
	return std::make_shared<HuffmanEncodingImplementation>(domain_size);
}


std::unique_ptr<data::Node<std::pair<Datum, unsigned>>> getbuild_tree(std::shared_ptr<data::FrequencyTable<Datum>> frequency_table)
{
	return build_tree(*frequency_table);
}

std::map<Datum, std::vector<Datum>> getbuild_codes(std::shared_ptr<data::FrequencyTable<Datum>> frequency_table)
{
	auto newroot = build_tree(*frequency_table);
	return build_codes(*newroot);
}

