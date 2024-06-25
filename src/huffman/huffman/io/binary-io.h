
#ifndef BINARYIO_H
#define BINARYIO_H
#include <io/streams.h>
namespace io {
	u64 read_bits(unsigned nbits, io::InputStream& input);
	void write_bits(u64 value, unsigned nbits, io::OutputStream& output);
}

#endif