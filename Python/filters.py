#!/usr/bin/env python3
"""
This module contains data structures for applying filters to images.
"""

import numpy as np

# New filters
# 1. Gaussian Blur (3x3)
gaussian_blur_3x3 = np.array([[1, 2, 1], [2, 4, 2], [1, 2, 1]]) / 9

# 2. Box Blur (3x3)
box_blur_3x3 = np.ones((3, 3)) / 9

# 3. Edge Detection (Sobel X)
sobel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])

# 4. Edge Detection (Sobel Y)
sobel_y = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])

# 5. Laplacian (Edge Detection)
laplacian = np.array([[0, 1, 0], [1, -4, 1], [0, 1, 0]])

# 6. Emboss
emboss = np.array([[-2, -1, 0], [-1, 1, 1], [0, 1, 2]])

# 7. Prewitt X (Edge Detection)
prewitt_x = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]])

# 8. Prewitt Y (Edge Detection)
prewitt_y = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])

# 9. Unsharp Masking
unsharp_masking = np.array([[-1, -1, -1], [-1, 9, -1], [-1, -1, -1]]) / 9

# 10. High Pass
high_pass = np.array([[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]])

# 11. Low Pass
low_pass = np.array([[1, 1, 1], [1, 1, 1], [1, 1, 1]]) / 9

# 12. Sharpen
sharpen_kernel = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])

# 13. Salt and Pepper Noise
salt_and_pepper_kernel = np.array([[0, 0, 0], [0, 1, 0], [0, 0, 0]])

# 14. Canny Edge Detection
canny_edge_detection = np.array([[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]])
