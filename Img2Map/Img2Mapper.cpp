#include "stdafx.h"
#include "Img2Mapper.h"


Img2Mapper::Img2Mapper(int argc, char *argv[])
{
	if (argc > 0)
	{
		std::cout << "Error! Expecting a single argument, found " << argc << " instead.\n";
		is_exit = true;
	}
	else if (argc == -1)
	{
		std::cout << "Error! Image file wasn't specified [must be a single console argument]\n";
		is_exit = true;
	}

	working_img.file_path = argv[0];
}


Img2Mapper::~Img2Mapper()
{

}

bool Img2Mapper::DeconstructImage()
{
	/*
		Steps needed:
			- Check if image file exists.
			- Load it
			- Loop through each pixel and save its data to the pixel struct
			- If successful, return true, else return false.
	*/

	//Check that the image file exists.
	std::ifstream infile(working_img.file_path.c_str());
	if (!infile.good())
	{
		return false;
	}
}