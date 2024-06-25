#include <io/streams.h>
#include <io/memory-buffer.h>
#include <iostream>
#include <ostream>
#ifndef ENCODING_H
#define ENCODING_H

namespace encoding {

	class EncodingImplementation
	{

	public:

		virtual ~EncodingImplementation() {}

		virtual void encode(io::InputStream& input, io::OutputStream& output) = 0;
		virtual void decode(io::InputStream& input, io::OutputStream& output) = 0;

	};

	template<u64 IN, u64 OUT>
	class Encoding {
	private:
		std::shared_ptr<EncodingImplementation> _encodingImplementation;
	public:
		Encoding(std::shared_ptr<EncodingImplementation> encodingImplementation) : _encodingImplementation(encodingImplementation) {}

		std::shared_ptr<EncodingImplementation> operator -> ()
		{
			return _encodingImplementation;
		}

		const std::shared_ptr<EncodingImplementation> operator -> () const
		{
			return _encodingImplementation;
		}
	};

	template<u64 _IN, u64 _OUT>
	void encode(io::DataSource<_IN> data_source, io::DataDestination<_OUT> data_destination, Encoding<_IN, _OUT> encoding) {


		std::unique_ptr<io::InputStream> inputStream = data_source->create_input_stream();
		std::unique_ptr<io::OutputStream> outputStream = data_destination->create_output_stream();
		encoding->encode(*inputStream, *outputStream);

	}

	template<u64 _IN, u64 _OUT>
	void decode(io::DataSource<_IN> data_source, io::DataDestination<_OUT> data_destination, Encoding<_OUT, _IN> decoding) {

		std::unique_ptr<io::InputStream> inputStream = data_source->create_input_stream();
		std::unique_ptr<io::OutputStream> outputStream = data_destination->create_output_stream();
		decoding->decode(*inputStream, *outputStream);
	}


}

#endif