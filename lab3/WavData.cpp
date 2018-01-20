#define _CRT_SECURE_NO_WARNINGS
#include "WavData.h"

#include <cstdio>
#include <cstring>
#include "WavData.h"

WavData::WavData(const char * filename) {
	readHeader(filename);
	extract_data_int16(filename);
}

void WavData::printInfo() {
	printf("-------------------------\n");
	printf(" audioFormat   %u\n", header.audioFormat);
	printf(" numChannels   %u\n", header.numChannels);
	printf(" sampleRate    %u\n", header.sampleRate);
	printf(" bitsPerSample %u\n", header.bitsPerSample);
	printf(" byteRate      %u\n", header.byteRate);
	printf(" blockAlign    %u\n", header.blockAlign);
	printf(" chunkSize     %u\n", header.chunkSize);
	printf(" subchunk1Size %u\n", header.subchunk1Size);
	printf(" subchunk2Size %u\n", header.subchunk2Size);
	printf("-------------------------\n");
}

void WavData::saveToFile(const char* filename)
{
	//printf(">>>> make_wav_file( %s )\n", filename);
	int chan_count = (int)source.size();
	int samples_count_per_chan = (int)source[0].size();

	std::vector<short> all_channels;
	all_channels.resize(chan_count * samples_count_per_chan);

	for (int ch = 0; ch < chan_count; ch++) {
		const std::vector<short>& chdata = source[ch];
		for (size_t i = 0; i < samples_count_per_chan; i++) {
			all_channels[chan_count * i + ch] = chdata[i];
		}
	}

	FILE* f = fopen(filename, "wb");
	fwrite(&header, sizeof(header), 1, f);
	fwrite(all_channels.data(), sizeof(short), all_channels.size(), f);
	if (!f) {
		throw WavException("IO error");
	}

	fclose(f);

	//return WAV_OK;
}

void WavData::makeMono()
{
	int chan_count = (int)source.size();

	if (chan_count != 2) {
		throw WavException("Bad parametrs");
	}

	int samples_count_per_chan = (int)source[0].size();

	// Verify that all channels have the same number of samples.
	for (size_t ch = 0; ch < chan_count; ch++) {
		if (source[ch].size() != (size_t)samples_count_per_chan) {
			//throw BAD_PARAMS;
			throw WavException("Bad parametrs");
		}
	}
	std::vector< std::vector<short> > dest_mono;
	dest_mono.resize(1);
	std::vector<short>& mono = dest_mono[0];
	mono.resize(samples_count_per_chan);

	// Mono channel is an arithmetic mean of all (two) channels.
	for (size_t i = 0; i < samples_count_per_chan; i++) {
		mono[i] = (source[0][i] + source[1][i]) / 2;
	}
	fill_header(1, header.bitsPerSample, header.sampleRate, samples_count_per_chan);
	//return WAV_OK;
}

void WavData::fill_header(int chan_count, int bits_per_sample, int sample_rate, int samples_count_per_chan)
{
	if (bits_per_sample != 16) {
		throw WavException("Unsupported farmat");
	}

	if (chan_count < 1) {
		throw WavException("Bad parametrs");
	}
	prefill_header();

	int file_size_bytes = 44 + chan_count * (bits_per_sample / 8) * samples_count_per_chan;

	header.sampleRate = sample_rate;
	header.numChannels = chan_count;
	header.bitsPerSample = 16;

	header.chunkSize = file_size_bytes - 8;
	header.subchunk2Size = file_size_bytes - 44;

	header.byteRate = header.sampleRate * header.numChannels * header.bitsPerSample / 8;
	header.blockAlign = header.numChannels * header.bitsPerSample / 8;

	//return WAV_OK;
}

void WavData::prefill_header() {
	header.chunkId[0] = 'R';
	header.chunkId[1] = 'I';
	header.chunkId[2] = 'F';
	header.chunkId[3] = 'F';

	header.format[0] = 'W';
	header.format[1] = 'A';
	header.format[2] = 'V';
	header.format[3] = 'E';

	header.subchunk1Id[0] = 'f';
	header.subchunk1Id[1] = 'm';
	header.subchunk1Id[2] = 't';
	header.subchunk1Id[3] = ' ';

	header.subchunk2Id[0] = 'd';
	header.subchunk2Id[1] = 'a';
	header.subchunk2Id[2] = 't';
	header.subchunk2Id[3] = 'a';

	header.audioFormat = 1;
	header.subchunk1Size = 16;
	header.bitsPerSample = 16;

}

void WavData::readHeader(const char * filename) {
	//printf(">>>> read_header( %s )\n", filename);
	memset(&header, 0, sizeof(header));

	FILE* f = fopen(filename, "rb");
	if (!f) {
		throw WavException("File: \"" + std::string(filename) + "\" not found");
	}

	size_t blocks_read = fread(&header, sizeof(header), 1, f);
	if (blocks_read != 1) {
		// can't read header, because the file is too small.
		throw WavException("Bad format");
	}

	fseek(f, 0, SEEK_END); // seek to the end of the file
	file_size = ftell(f); // current position is a file size!
	fclose(f);

	checkHeader();
}

void WavData::checkHeader()
{
	// Go to wav_header.h for details

	if (header.chunkId[0] != 'R' ||
		header.chunkId[1] != 'I' ||
		header.chunkId[2] != 'F' ||
		header.chunkId[3] != 'F') {
		throw WavException("Header RIFF error");
	}

	if (header.chunkSize != file_size - 8) {
		throw WavException("Header file size error");
	}

	if (header.format[0] != 'W' ||
		header.format[1] != 'A' ||
		header.format[2] != 'V' ||
		header.format[3] != 'E') {
		throw WavException("Header WAVE error");
	}

	if (header.subchunk1Id[0] != 'f' ||
		header.subchunk1Id[1] != 'm' ||
		header.subchunk1Id[2] != 't' ||
		header.subchunk1Id[3] != ' ') {
		throw WavException("Header FMT error");
	}

	if (header.audioFormat != 1) {
		throw WavException("Header NOT PCM");
	}

	if (header.subchunk1Size != 16) {
		throw WavException("Header SUBCHUNK1 error");
	}

	if (header.byteRate != header.sampleRate * header.numChannels * header.bitsPerSample / 8) {
		throw WavException("Header BYTES RATE error");
	}

	if (header.blockAlign != header.numChannels * header.bitsPerSample / 8) {
		throw WavException("Header BLOCK ALIGN error");
	}

	if (header.subchunk2Id[0] != 'd' ||
		header.subchunk2Id[1] != 'a' ||
		header.subchunk2Id[2] != 't' ||
		header.subchunk2Id[3] != 'a') {
		throw WavException("Header FMT error");
	}

	if (header.subchunk2Size != file_size - 44) {
		throw WavException("Header SUBCHUNK2 SIZE error");
	}

	//return HEADER_OK;
}

void WavData::extract_data_int16(const char* filename)
{
	//printf(">>>> extract_data_int16( %s )\n", filename);

	if (header.bitsPerSample != 16) {
		// Only 16-bit samples is supported.
		throw WavException("Unsupported format");
	}

	FILE* f = fopen(filename, "rb");
	if (!f) {
		throw WavException("File: \"" + std::string(filename) + "\" not found");
	}
	fseek(f, 44, SEEK_SET); // Seek to the begining of PCM data.

	int chan_count = header.numChannels;
	int samples_per_chan = (header.subchunk2Size / sizeof(short)) / chan_count;

	// 1. Reading all PCM data from file to a single vector.
	std::vector<short> all_channels;
	all_channels.resize(chan_count * samples_per_chan);
	size_t read_bytes = fread(all_channels.data(), 1, header.subchunk2Size, f);
	if (read_bytes != header.subchunk2Size) {
		//printf("extract_data_int16() read only %zu of %u\n", read_bytes, header.subchunk2Size);
		throw WavException("IO error");
	}
	fclose(f);


	// 2. Put all channels to its own vector.
	source.resize(chan_count);
	for (size_t ch = 0; ch < source.size(); ch++) {
		source[ch].resize(samples_per_chan);
	}

	for (int ch = 0; ch < chan_count; ch++) {
		std::vector<short>& chdata = source[ch];
		for (size_t i = 0; i < samples_per_chan; i++) {
			chdata[i] = all_channels[chan_count * i + ch];
		}
	}
}

unsigned short WavData::getAudioFormat() {
	return header.audioFormat;
}

unsigned short WavData::getNumChunnel() {
	return header.numChannels;
}

unsigned long WavData::getSampleRate() {
	return header.sampleRate;
}

unsigned long WavData::getByteRate() {
	return header.byteRate;
}

unsigned short WavData::getBitsPerSample() {
	return header.bitsPerSample;
}
