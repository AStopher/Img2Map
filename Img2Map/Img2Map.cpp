// Img2Map.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Img2Mapper.h"

//Expects the image file name to be the only argument.

int main(int argc, char *argv[])
{
	Img2Mapper *img_mapper = new Img2Mapper(argc, argv);
	
	while (!img_mapper->is_exit) {}

    return 0;
}
