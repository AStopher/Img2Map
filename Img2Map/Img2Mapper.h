#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "opencv2/opencv.hpp"

#pragma once
class Img2Mapper
{
public:
	Img2Mapper(int argc, char *argv[]);
	~Img2Mapper();

	static const int MAX_PIXELS = 16058880;

	struct pixel
	{
		int colour_r;
		int colour_g;
		int colour_b;
		int colour_a;
		int colour_hex;
	};

	struct image
	{
		std::string file_path;
		pixel pixel_data[MAX_PIXELS]; //Maximum image size this can process is 16MP, which should be enough. If file is larger than this then pixels outside these bounds will be ignored.
		int total_pixels = 0;
	};

	bool is_exit = false;

private:
	image working_img;

	bool DeconstructImage();
	void ExportAsASSMF();
	unsigned long CreateHex(int r, int g, int b);
};