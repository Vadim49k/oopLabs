#pragma once
#include <iostream>
#include <vector>
#include "WavHeader.h"
#include "Exception.h"

class WavData {
public:
	WavData() = delete;
	WavData(const char *filename);

	void printInfo();
	void WavData::saveToFile(const char* filename);
	void WavData::makeMono();

	unsigned short getAudioFormat();
	unsigned short getNumChunnel();
	unsigned long getSampleRate();
	unsigned long getByteRate();
	unsigned short getBitsPerSample();

private:
	void fill_header(int chan_count, int bits_per_sample, int sample_rate, int samples_count_per_chan);
	void prefill_header();
	void readHeader(const char *filename);
	void checkHeader();
	void extract_data_int16(const char* filename);

	size_t file_size;
	WavHeader header;
	std::vector<std::vector<short> > source;
};