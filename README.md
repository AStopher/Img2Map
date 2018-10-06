# Img2Map

Maps a given image to the ASSMF (Alexander Stopher Simple Map File) format, in order for game engines to effectively reconstruct the image one pixel at a time.

# As a game developer, why should I want to do this?

Reading in and constructing an image in this way means that it can be manipulated on-the-fly. I created this tool so I could dynamically erode land in a rain simulation.

# How do I read in the file?

That's completely up to you, this tool only generates an output.
Each line in the output file represents a pixel and should be read in consecutively from start to end. This means that you can loop through each line.

The output for each line is like so:

    [r],[g],[b],[a],[hex]
    
That's all there is to reading ASSMF.

# Is there anything I need to be aware of?

If you want to use the binary version of this tool without rebuilding its source, you should know that the maximum image size that the program can process is **16 megapixels**- any images larger than this will be chopped-off when 16 megapixels is reached. Anyhow, for a game, 16 megapixels should be more than large enough.
