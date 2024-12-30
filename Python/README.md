# Image Histogram with Python 

This is a simple Python application that generates a histogram of an image. It uses the OpenCV and Pillow libraries for image processing and Matplotlib for plotting the histogram.

## Setup
 - Create a virtual environment and activate it.
```bash
    conda create -n image-histogram python=3.10
    conda activate image-histogram
```

 - Install the required packages using pip:
```bash
    conda install --file requirements.txt
    # or
    pip install -r requirements.txt
```

Make sure, you have Python 3.10 installed. Then virtual environment is created and activated. Also check from the Python REPL if the required packages are installed.

## Usage
 - Run the main.py script:
```bash
    python main.py
```
This will load an image, generate a histogram, and display the histogram plot drawed by matplotlib. You can change the image path in the main.py file to use a different image.

## Expected Output



_This project is tested on Linux Ubuntu 22.04 and MacOs Sonoma. If you encounter any issues, please open an issue._


## Contributing
If you'd like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.
