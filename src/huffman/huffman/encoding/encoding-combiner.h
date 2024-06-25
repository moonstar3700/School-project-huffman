#ifndef ENCODINGCOMBINOR_H
#define ENCODINGCOMBINOR_H
#include "encoding/encoding.h"



namespace encoding {
	template<u64 N1, u64 N2, u64 N3>
	class EncodingCombinerImplementation : public encoding::EncodingImplementation
	{
	private:
		const Encoding<N1, N2> _encoding_1;
		const Encoding<N2, N3> _encoding_2;

	public:

		EncodingCombinerImplementation(const Encoding<N1, N2> encoding_1, const Encoding<N2, N3> encoding_2) : _encoding_1(std::move(encoding_1)), _encoding_2(std::move(encoding_2)) {}

		virtual void encode(io::InputStream& input, io::OutputStream& output) {

			auto temp_buffer = io::MemoryBuffer<N2, u64>();
			auto outputbuffer = temp_buffer.destination()->create_output_stream();
			auto inbuffer = temp_buffer.source()->create_input_stream();

			_encoding_1->encode(input, *outputbuffer);
			_encoding_2->encode(*inbuffer, output);
		}
		virtual void decode(io::InputStream& input, io::OutputStream& output) {

			auto temp_buffer = io::MemoryBuffer<N2, u64>();
			auto outputbuffer = temp_buffer.destination()->create_output_stream();
			auto inbuffer = temp_buffer.source()->create_input_stream();

			_encoding_2->decode(input, *outputbuffer);
			_encoding_1->decode(*inbuffer, output);
		}


	};
	template<u64 N1, u64 N2, u64 N3>
	encoding::Encoding<N1, N3> operator | (const Encoding<N1, N2> E1, const Encoding<N2, N3> E2) {
		auto encodercombiner = std::make_shared<EncodingCombinerImplementation<N1, N2, N3>>(E1, E2);
		return Encoding<N1, N3>(encodercombiner);
	}
}



#endif