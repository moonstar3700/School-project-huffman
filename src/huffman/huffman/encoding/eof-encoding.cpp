#include "encoding/encoding.h"
#include <memory>

namespace {

	class EofEncodingImplementation : public encoding::EncodingImplementation {
	private:
		const u64 _domain_size;
	public:
		EofEncodingImplementation(u64 domain_size) : _domain_size(std::move(domain_size)) {}

		virtual void encode(io::InputStream& input, io::OutputStream& output) {
			while (!input.end_reached()) {
				output.write(input.read());
			}
			output.write(_domain_size);
		}
		virtual void decode(io::InputStream& input, io::OutputStream& output) {

			u64 current = input.read();
			while (current != _domain_size) {
				output.write(current);
				current = input.read();
			}

		}

	};
}


std::shared_ptr<encoding::EncodingImplementation> create_eof_implementation(u64 domain_size) {

	return std::make_shared<EofEncodingImplementation>(domain_size);

}
