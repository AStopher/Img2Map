#include <string>
#include <iostream>
#include <fstream>

#pragma once
class Img2Mapper
{
public:
	Img2Mapper(int argc, char *argv[]);
	~Img2Mapper();

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
		pixel pixel_data[16058880]; //Maximum image size this can process is 16MP, which should be enough. If file is larger than this then pixels outside these bounds will be ignored.
	};

	bool is_exit = false;

private:
	image working_img;

	bool DeconstructImage();
};