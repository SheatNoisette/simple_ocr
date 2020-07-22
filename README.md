# OCR
A simple optical character recognition system made for the final S3 project at
EPITA.

The project was made by the following authors:
* SheatNoisette
* César "Macaron" Milesi
* jpbinger

# Program architecture

The OCR is divided into four main parts :
* The bitmap loader (`src/bitmap/`),
* The character extraction system (`src/recognition/`),
* Image filters and binarization (`src/filters/`),
* Neural network for character recognition (`src/neural/`).

# Building
Type `make` in the repository root to build the OCR. You will need SDL 2 on your
computer. The executable will be located on the `bin/ocr`.

Required packages :
`gtk-3.0`
`SDL2`

You can install these packages on a Debian/Debian-based system using this command: 
`sudo apt-get install libsdl2-dev libgtk-3-dev`

A minimal version without GTK and SDL support of the OCR can be built with:
`make nosdl=1 nogtk=1`

# Test files
There is some sample file to test the OCR in the `sample` folder.
A lot are black text in a white background.

**Please note that sample folder contains a zip archive when extracted 
output a image file bigger than 300> MB.**

# Usage

Here are the command line arguments:

`-t <File>   Run neural network training and save generated`

`            training data in <file> (default: train_data.txt)`

`-w <File>   Use custom training data for recognition`

`                (Default: train_data.txt)`

`-i <File>   Image to cut character from`

`-v          Show the caracter cutting`

`-d <File>   Specifiy a custom dataset (default: dataset.txt)`

`-o          Use Otsu binarization instead of basic threshold`

`-f <Filter> Apply a convolutional filter on the image`

`                Valid input: a / s / d - A-ll D-enoise S-harpen`

`-h          Print this help`
