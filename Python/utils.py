#!/usr/bin/env python3
"""
This module contains utility functions for image processing.
"""
import os
import numpy as np
import cv2
from PIL import Image, ImageFilter


def if_file_exists(file_path: str) -> bool:
    """ Check if a file exists.
    Args:
        file_path (str): The path to the file.
    Returns:
        bool: True if the file exists, False otherwise.
    """
    if not os.path.exists(file_path):
        return False
    return True


def load_image_opencv(image_path: str) -> np.ndarray:
    """ Load an image from a file path.
    Args:
        image_path (str): The path to the image file.
    Returns:
        np.ndarray: The image as a NumPy array.
    """
    image = cv2.imread(image_path)
    return image


def load_image_pillow(image_path: str) -> Image.Image:
    """ Load an image from a file path.
    Args:
        image_path (str): The path to the image file.
    Returns:
        Image.Image: The image as a PIL Image object.
    """
    image = Image.open(image_path)
    return image


def convert_pillow_to_numpy(image: Image.Image) -> np.ndarray:
    """ Convert a PIL Image object to a NumPy array.
    Args:
        image (Image.Image): The image as a PIL Image object.
    Returns:
        np.ndarray: The image as a NumPy array.
    """
    image = np.array(image)
    return image


def convert_rgb_to_grayscale(image: np.ndarray) -> np.ndarray:
    """ Convert an RGB image to grayscale.
    Args:
        image (np.ndarray): The image as a NumPy array.
    Returns:
        np.ndarray: The grayscale image as a NumPy array.
    """
    image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    return image


def convert_bgr_to_grayscale(image: np.ndarray) -> np.ndarray:
    """ Convert a BGR image to grayscale.
    Args:
        image (np.ndarray): The image as a NumPy array.
    Returns:
        np.ndarray: The grayscale image as a NumPy array.
    """
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    return image


def calculate_histogram(image: np.ndarray, channel: int) -> np.ndarray:
    """ Calculate the histogram of an image.
    Args:
        image (np.ndarray): The image as a NumPy array.
        channel (int): The channel to calculate the histogram for.
    Returns:
        np.ndarray: The histogram of the image.
    """
    histogram = cv2.calcHist([image], [channel], None, [256], [0, 256])
    return histogram


def histogram_equalization(image: np.ndarray) -> np.ndarray:
    """ Apply histogram equalization to an image.
    Args:
        image (np.ndarray): The image as a NumPy array.
    Returns:
        np.ndarray: The equalized image as a NumPy array.
    """
    equalized_image = cv2.equalizeHist(image)
    return equalized_image


def apply_convolution_opencv(image: np.ndarray, kernel: np.ndarray) -> np.ndarray:
    """ Apply convolution to an image.
    Args:
        image (np.ndarray): The image as a NumPy array.
        kernel (np.ndarray): The kernel to apply.
    Returns:
        np.ndarray: The convolved image as a NumPy array.
    """
    convolved_image = cv2.filter2D(image, -1, kernel)
    return convolved_image


def apply_convolution_pillow(image: np.ndarray, kernel: np.ndarray) -> np.ndarray:
    """ Apply convolution to an image.
    Args:
        image (np.ndarray): The image as a NumPy array.
        kernel (np.ndarray): The kernel to apply.
    Returns:
        np.ndarray: The convolved image as a NumPy array.
    """
    pillow_image = Image.fromarray(image)
    pillow_image = pillow_image.filter(ImageFilter.Kernel(kernel.shape, kernel))
    convolved_image = np.array(pillow_image)
    return convolved_image


def save_image_opencv(image: np.ndarray, image_path: str) -> None:
    """ Save an image to a file path.
    Args:
        image (np.ndarray): The image as a NumPy array.
        image_path (str): The path to the image file.
    Returns:
        None
    """
    # TODO: write an error checking case if the image is saved correctly or not?
    if cv2.imwrite(image_path, image):
        print(f"{image_path} saved successfully.")
    else:
        raise Exception("Failed to save the image.")


def save_image_pillow(image: np.ndarray, image_path: str) -> None:
    """ Save an image to a file path.
    Args:
        image (np.ndarray): The image as a NumPy array.
        image_path (str): The path to the image file.
    Returns:
        None
    """
    image = Image.fromarray(image)
    if image.save(image_path):
        print(f"{image_path} saved successfully.")
    else:
        raise Exception("Failed to save the image.")
