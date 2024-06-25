#include "encoding/encoding.h"
#include "io/binary-io.h"
#include <memory>

namespace {

	class BitGrouperImplementation : public encoding::EncodingImplementation
	{
	private:
		const u64 _group_size;
	public:
		BitGrouperImplementation(u64 group_size) : _group_size(std::move(group_size)) {}

		virtual void encode(io::InputStream& input, io::OutputStream& output) {
			while (!input.end_reached()) {
				u64 data = io::read_bits(_group_size, input);
				output.write(data);
			}
		}
		virtual void decode(io::InputStream& input, io::OutputStream& output) {
			while (!input.end_reached()) {
				u64 data = input.read();
				io::write_bits(data, _group_size, output);
			}
		}

	};
}

std::shared_ptr<encoding::EncodingImplementation> create_bit_grouper_implementation(u64 _group_size) {

	BitGrouperImplementation coding = BitGrouperImplementation(_group_size);
	return std::make_shared<BitGrouperImplementation>(coding);

}
