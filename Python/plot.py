#!/usr/bin/env python3
"""
This module contains functions for plotting histograms.
"""
import numpy as np
import matplotlib.pyplot as plt
import cv2
from PIL import Image


def show_image_opencv(image: np.ndarray) -> None:
    """ Show an image.
    Args:
        image (np.ndarray): The image as a NumPy array.
    Returns:
        None
    """
    cv2.imshow("Input Image", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def show_image_pillow(image: np.ndarray) -> None:
    """ Show an image.
    Args:
        image (np.ndarray): The image as a NumPy array.
    Returns:
        None
    """
    pillow_image = Image.fromarray(image)
    pillow_image.show()


def show_image_matplotlib(image: np.ndarray) -> None:
    """ Show an image.
    Args:
        image (np.ndarray): The image as a NumPy array.
    Returns:
        None
    """
    plt.imshow(image)
    plt.show()
    plt.close()


def plot_histogram(histogram: np.ndarray, channel: str, save_path: str = None) -> None:
    """ Plot a histogram.
    Args:
        histogram (np.ndarray): The histogram as a NumPy array.
        channel (str): The color channel (e.g., "Red", "Green", "Blue").
            if channel is "Grayscale" then the color is "orange".
            if channel is "Equalized" then the color is "olive".
            if channel is "Filtered" then the color is "magenta".
        save_path (str, optional): Path to save the plot. Defaults to None.
    Returns:
        None
    """
    x = [i for i in range(256)]
    if channel == "Grayscale":
        channel = "orange"
    elif channel == "Equalized":
        channel = "olive"
    elif channel == "Filtered":
        channel = "magenta"
    plt.plot(x, histogram, label=channel, color=f"{channel.lower()}")
    plt.fill_between(x, histogram.flatten(), 0, color=f"{channel.lower()}", alpha=0.5)
    plt.title(f"Histogram of {channel} channel")
    plt.xlabel("Pixel Value")
    plt.ylabel("Histogram Frequency")
    plt.grid(True)
    plt.legend(loc="upper right")
    if save_path is not None:
        plt.savefig(save_path)
    plt.show()
    plt.close()


# TODO: write a function to plot a histogram for all channels in one plot
def plot_histogram_for_all_channels(histogram_dict: dict, save_path: str = None) -> None:
    """ Plot a histogram for all channels in one plot.
    Args:
        histogram_dict (dict): {"channel": histogram } structured dictionary for all channels.
            if channel is "Grayscale" then the color is "orange".
            if channel is "Equalized" then the color is "olive".
            if channel is "Filtered" then the color is "magenta".
        save_path (str, optional): Path to save the plot. Defaults to None.
    Returns:
        None
    """
    x = [i for i in range(256)]
    for channel, histogram in histogram_dict.items():
        if channel == "Grayscale":
            channel = "orange"
        elif channel == "Equalized":
            channel = "olive"
        elif channel == "Filtered":
            channel = "magenta"
        plt.plot(x, histogram, label=channel, color=f"{channel.lower()}")
        plt.fill_between(x, histogram.flatten(), 0, color=f"{channel.lower()}", alpha=0.3)
    plt.title("Histogram Plot for All Channels")
    plt.xlabel("Pixel Value")
    plt.ylabel("Histogram Frequency")
    plt.grid(True)
    plt.legend(loc="upper right")
    if save_path is not None:
        plt.savefig(save_path)
    plt.show()
    plt.close()
