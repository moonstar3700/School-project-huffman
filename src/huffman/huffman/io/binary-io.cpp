#ifndef BINARYIO_CPP
#define BINARYIO_CPP
#include "binary-io.h"
#include <cmath>
#include <assert.h>

namespace io {
	u64 io::read_bits(unsigned nbits, io::InputStream& input) {

		assert(nbits <= 64);

		Datum result = 0;
		while (!input.end_reached() && nbits > 0) {
			result = (result << 1) | input.read();
			nbits--;
		}
		return result << nbits;

	}
	void io::write_bits(u64 value, unsigned nbits, io::OutputStream& output) {

		assert(nbits <= 64);
		for (int i = nbits - 1; i >= 0; i--) {
			output.write((value >> i) & 1);
		}
	}
}

#endif