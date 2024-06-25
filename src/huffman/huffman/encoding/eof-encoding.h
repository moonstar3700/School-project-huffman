#ifndef EOFENCODING_H
#define EOFENCODING_H
#include "encoding/encoding.h"
#include <memory>

std::shared_ptr<encoding::EncodingImplementation> create_eof_implementation(u64 domain_size);

namespace encoding {
	template<u64 N>
	encoding::Encoding<N, N + 1> eof_encoding() {
		return encoding::Encoding<N, N + 1>(create_eof_implementation(N));
	}
}

#endif


