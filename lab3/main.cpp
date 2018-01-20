#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <iostream>

#include "WavData.h"

using namespace std;

int main(int argc, char *argv[]) {
	//-o
	rand();
	//cout << sizeof(unsigned long) << endl;
	//cout << sizeof(WavHeader) << endl;
	cout << "************** | WavCore | **************" << endl;
	//WavData wav1;
	try {
		//WavData wav10("D:\\main\\2 course\\labs\\oop\\lab03\\3.wav");
	}
	catch (WavException &e) {
		cout << e.what() << endl;
	}
	WavData wav1("D:\\main\\2_course\\labs\\oop\\lab03\\0.wav");
	wav1.printInfo();
	wav1.makeMono();
	//wav1.ApplyReverb(0.500, 0.6f);
	wav1.saveToFile("D:\\main\\2_course\\labs\\oop\\lab03\\1.wav");
	wav1.printInfo();

	WavData wav2("D:\\main\\2_course\\labs\\oop\\lab03\\0.wav");
	wav2.printInfo();
	

	//wav2.ChangeSampleRate(22050);

	// Cut first 10 seconds and last 20 seconds
	//wav2.CutBegin(10.0);
	//wav2.CutEnd(20.0);

	//wav2.Save(); // Overwrite the original file.

	/*			 // ################  Tests for WavCore  ################

	const char* input_fname = "D:\\main\\2 course\\labs\\oop\\lab03\\0.wav";
	const char* output_fname = "D:\\main\\2 course\\labs\\oop\\lab03\\1.wav";

	wav_errors_e err;
	wav_header_s header;


	// #### Opening WAV file, checking header.
	err = read_header(input_fname, &header);
	if (err != WAV_OK) {
		cerr << "read_header() error: " << (int)err << endl;
		print_info(&header);
		return err;
	}


	// #### Printing header.
	print_info(&header);


	// #### Reading PCM data from file.
	vector< vector<short> > chans_data;
	err = extract_data_int16(input_fname, chans_data);
	if (err != WAV_OK) {
		cerr << "extract_data_int16() error: " << (int)err << endl;
		return err;
	}
	cout << endl << "********************" << endl;


	// #### Make several changes to PCM data.

	// # Making signal mono from stereo.
	vector< vector<short> > edited_data;
	err = make_mono(chans_data, edited_data);
	if (err != WAV_OK) {
		cerr << "make_mono() error: " << (int)err << endl;
		return err;
	}


	// #### Making new WAV file using edited PCM data.
	err = make_wav_file(output_fname, 44100, edited_data);
	if (err != WAV_OK) {
		cerr << "make_wav_file() error: " << (int)err << endl;
		print_info(&header);
		return err;
	}


	// #### Reading the file just created to check its header corectness.
	err = read_header(output_fname, &header);
	if (err != WAV_OK) {
		cerr << "read_header() error: " << (int)err << endl;
		print_info(&header);
		return err;
	}
	print_info(&header);

	*/
	system("pause");
	return 0;
}
