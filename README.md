# Steganography Tool

This is a tool that can be used to hide data within an image. The format of that data is irrelevent, and all that matters is if the image is large enough to hold it. Methods have been implemeneted to increase the security and to obsure the data from potential onlookers.

## Prerequisites

+ Cmake
+ make
+ gcc

## Installing

+ Run *cmake .* from the root directory
+ run *make*

## Running

### To hide data in an image

    ./StegTool -i img/in.png -o img/out.png -f txt/text.txt

### To extract the data from an image

    ./StegTool -i img/out.png -o txt/out.txt

## Command Line Arguments

| Command | Name              | Description                                                                              |
| :-----: | ----------------- | ---------------------------------------------------------------------------------------- |
|   -i    | input image       | the image that is either read from or modified                                           |
|   -o    | output image/file | the output file from the execution. Either the image with the data or the data if desteg |
|   -f    | data file         | The file that is to be hidden within the image                                           |
|   -c    | compress          | Store more in less data (May cause more disfigurement on the pixels)                     |
|   -d    | desteg            | Extract the data from an image                                                           |
|   -v    | verbose           | Print Verbose information                                                                |


## Meta

Jonathon Winter - Jonathon.Winter979@gmail.com

Distrubutes under the MIT Liocense. See LICENSE.md for more information

https://www.github.com/Zazu979 