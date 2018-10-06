#include "stdafx.h"
#include "Img2Mapper.h"


Img2Mapper::Img2Mapper(int argc, char *argv[])
{
	bool errors = false;
	if (argc > 2)
	{
		std::cout << "Error! Expecting a single argument, found " << argc << " instead.\n";
		errors = true;
	}
	else if (argc == 0)
	{
		std::cout << "Error! Image file wasn't specified [must be a single console argument]\n";
		errors = true;
	}

	if (!errors)
	{
		working_img.file_path = argv[1];

		if (DeconstructImage())
		{
			std::cout << "Start export.\n";
			ExportAsASSMF();
		}
	}
	else
	{
		std::cout << "Cannot continue.\n";
	}
}


Img2Mapper::~Img2Mapper()
{

}

void Img2Mapper::ExportAsASSMF()
{
	int last_rgba_value = -1;
	std::string output_file_path = working_img.file_path.substr(0, working_img.file_path.find_last_of("\\")); //Finds path before input file name.
	std::string output_file_name = working_img.file_path.substr(working_img.file_path.find_last_of("\\"), working_img.file_path.find_last_of(".")); //Finds file name, without extension.

	std::ostringstream output_full_path_ss;
	std::ostringstream file_line;
	std::string output_full_path;

	output_full_path_ss << output_file_path << output_file_name << ".assmf";
	output_full_path = output_full_path_ss.str();

	std::cout << "Export target is " << output_full_path << "\n";

	std::ofstream file;
	file.open(output_full_path);

	int repeat = 0;
	int line_rgba_val = -1;

	for (int i = 0; i < working_img.total_pixels; i++)
	{
		line_rgba_val = working_img.pixel_data[i].colour_r + working_img.pixel_data[i].colour_g + working_img.pixel_data[i].colour_b + working_img.pixel_data[i].colour_a;

		file_line << working_img.pixel_data[i].colour_r << "," << working_img.pixel_data[i].colour_g << "," << working_img.pixel_data[i].colour_b << "," << working_img.pixel_data[i].colour_a << std::endl;

		file << file_line.str();

		file_line.str("");
	}

	file.close();
	std::cout << "Export complete.\n";
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

	std::cout << "Preparing to deconstruct image.\n";

	//Check that the image file exists.
	std::ifstream infile(working_img.file_path.c_str());
	if (!infile.good())
	{
		return false;
	}

	std::cout << "Found file, it exists.\n";

	cv::Mat img = cv::imread(working_img.file_path.c_str());

	CV_Assert(img.depth() == CV_8U);

	int channels = img.channels();

	cv::MatIterator_<cv::Vec3b> it, end;
	int pos = 0;

	if (channels == 3) //No alpha transparency.
	{
		for (it = img.begin<cv::Vec3b>(), end = img.end<cv::Vec3b>(); it != end; ++it)
		{
			if (pos > MAX_PIXELS)
			{
				break;
			}

			//std::cout << "Reading pixel " << pos << ".\n";

			working_img.pixel_data[pos].colour_r = (*it)[2];
			working_img.pixel_data[pos].colour_g = (*it)[1];
			working_img.pixel_data[pos].colour_b = (*it)[0];
			working_img.pixel_data[pos].colour_a = 0;
			working_img.pixel_data[pos].colour_hex = CreateHex((*it)[2], (*it)[1], (*it)[0]);
			working_img.total_pixels++;
			pos++;
		}
	}
	else if (channels == 4)
	{
		for (it = img.begin<cv::Vec3b>(), end = img.end<cv::Vec3b>(); it != end; ++it)
		{
			if (pos > MAX_PIXELS)
			{
				break;
			}

			//std::cout << "Reading pixel " << pos << ".\n";

			working_img.pixel_data[pos].colour_r = (*it)[3];
			working_img.pixel_data[pos].colour_g = (*it)[2];
			working_img.pixel_data[pos].colour_b = (*it)[1];
			working_img.pixel_data[pos].colour_a = (*it)[0];
			working_img.pixel_data[pos].colour_hex = CreateHex((*it)[2], (*it)[1], (*it)[0]);
			working_img.total_pixels++;
			pos++;
		}
	}
	else
	{
		std::cout << "Error! Image file not supported!\n";
		//is_exit = true;
	}

	std::cout << "Image deconstruction successful.\n";

	return true;
}

unsigned long Img2Mapper::CreateHex(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}