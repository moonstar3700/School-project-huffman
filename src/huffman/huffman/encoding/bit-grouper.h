#ifndef BITGROUPER_H
#define BITGROUPER_H

#include "util.h"
#include "io/memory-buffer.h"
#include "encoding/encoding.h"
#include <memory>

std::shared_ptr<encoding::EncodingImplementation> create_bit_grouper_implementation(u64 _group_size);

namespace encoding {
	template<unsigned GROUP_SIZE>
	encoding::Encoding<2, 1 << GROUP_SIZE>bit_grouper() {
		return encoding::Encoding<2, 1 << GROUP_SIZE>(create_bit_grouper_implementation(GROUP_SIZE));

	}
}




#endif