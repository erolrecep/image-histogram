# Image Histogram with C Language

This is a simple C program that generates a histogram from an input image. It uses the stb_image and stb_image_write libraries for image loading, manipulation, and saving. For plotting the histogram, GNUPlot is used. 
<br>
Some part of the code is taken from https://github.com/pjreddie/vision-hw0 repository and modified.

## Setup

There is no need any setup. Just clone the repository and run the Makefile.
The tech stack of the project is
 - C Language (your favorite C compiler)
 - GNUPlot
 - Makefile

## Usage

Makefile is provided to build and run the program.

```bash
    make
    # or
    make -j 4
```

This step will compile the program and create an executable file named "main".

```bash
    make run
```

This will load an image, generate a histogram for each channel and grayscale. You can change the image path in the main.c file to use a different image.

```bash
    make plot
```

This will plot the histograms for each channel and grayscale using GNUPlot.


## Expected Output

<table>
  <tr>
    <td align="center">
      <img src="images/cats.jpg" alt="Original Image" width="400"/><br>
      <em>Original Image</em>
    </td>
    <td align="center">
      <img src="images/image_grayscale.jpg" alt="Grayscale Image" width="400"/><br>
      <em>Grayscale Image</em>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="images/image_grayscale_hist.png" alt="Image Grayscale Histogram" width="400"/><br>
      <em>Original Image</em>
    </td>
    <td align="center">
      <img src="images/image_gray_equlized.jpg" alt="Grayscale Image Histogram Equalized" width="400"/><br>
      <em>Grayscale Image</em>
    </td>
  </tr>
</table>

## Histogram Equalization

ChatGPT was kind enough to explain the math behind histogram equalization.

<img src="images/chatgpt_histogram_equalization01.png" alt="Histogram Equalization Math 01" width="800"/>
<br>
<img src="images/chatgpt_histogram_equalization02.png" alt="Histogram Equalization Math 02" width="800"/>

## Contributing
If you'd like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.
