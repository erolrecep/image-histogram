#!/usr/bin/env python3


import cv2
from utils import load_image_opencv, calculate_histogram, if_file_exists, histogram_equalization, convert_bgr_to_grayscale, save_image_opencv, apply_convolution_opencv
from plot import plot_histogram, show_image_opencv, plot_histogram_for_all_channels
from filters import laplacian, gaussian_blur_3x3, sharpen_kernel, low_pass, high_pass


def main():
    """ Main function. """

    # Load the image
    image_path = "images/GS_team.jpg"
    image_name = image_path.split("/")[-1].split(".")[0]

    # Check if the image file exists
    if if_file_exists(image_path):
        image = load_image_opencv(image_path)
    else:
        print("Provided input image file does not exist.")
        return

    # display image
    # show_image_opencv(image)

    # split input image channels into individual one
    b, g, r = cv2.split(image)

    # calculate histogram for each channel
    b_hist = calculate_histogram(b, 0)
    g_hist = calculate_histogram(g, 0)
    r_hist = calculate_histogram(r, 0)

    # plot histogram for all channels and save them to files
    plot_histogram(b_hist, "Blue", f"output/{image_name}_histogram_blue.png")
    plot_histogram(g_hist, "Green", f"output/{image_name}_histogram_green.png")
    plot_histogram(r_hist, "Red", f"output/{image_name}_histogram_red.png")

    print("Histograms are saved to output folder.")

    # plot all histograms in one plot
    plot_histogram_for_all_channels({"Blue": b_hist, "Green": g_hist, "Red": r_hist}, f"output/{image_name}_histogram_all.png")

    # convert bgr image to grayscale
    image_grayscale = convert_bgr_to_grayscale(image)

    # apply histogram equalization
    equalized_image = histogram_equalization(image_grayscale)

    # display image
    show_image_opencv(image_grayscale)
    save_image_opencv(image_grayscale, f"output/{image_name}_grayscale.png")
    
    # display equalized image
    show_image_opencv(equalized_image)
    save_image_opencv(equalized_image, f"output/{image_name}_equalized.png")

    # calculate histogram for grayscale image
    grayscale_hist = calculate_histogram(image_grayscale, 0)

    # plot histogram for grayscale image
    plot_histogram(grayscale_hist, "Grayscale", f"output/{image_name}_histogram_grayscale.png")

    # calculate histogram for equalized image
    equalized_hist = calculate_histogram(equalized_image, 0)

    # plot histogram for equalized image
    plot_histogram(equalized_hist, "Equalized", f"output/{image_name}_histogram_equalized.png")

    # plot grayscale and equalized histograms in one plot
    plot_histogram_for_all_channels({"Grayscale": grayscale_hist, "Equalized": equalized_hist}, f"output/{image_name}_histogram_grayscale_equalized.png")

    # apply laplacian filter to the grayscale image
    laplacian_image = apply_convolution_opencv(image_grayscale, laplacian)

    # display laplacian image
    show_image_opencv(laplacian_image)
    save_image_opencv(laplacian_image, f"output/{image_name}_laplacian.png")

    # calculate histogram for laplacian image
    laplacian_hist = calculate_histogram(laplacian_image, 0)

    # plot histogram for laplacian image
    plot_histogram(laplacian_hist, "Filtered", f"output/{image_name}_histogram_laplacian.png")

    # apply gaussian blur to the grayscale image
    gaussian_blur_image = apply_convolution_opencv(image_grayscale, gaussian_blur_3x3)
    show_image_opencv(gaussian_blur_image)
    save_image_opencv(gaussian_blur_image, f"output/{image_name}_gaussian_blur.png")

    # calculate histogram for gaussian blur image
    gaussian_blur_hist = calculate_histogram(gaussian_blur_image, 0)
    plot_histogram(gaussian_blur_hist, "Filtered", f"output/{image_name}_histogram_gaussian_blur.png")

    # plot grayscale and gaussian blur histograms in one plot
    plot_histogram_for_all_channels({"Grayscale": grayscale_hist, "Filtered": gaussian_blur_hist}, f"output/{image_name}_histogram_grayscale_gassian_blur_filtered.png")

    # apply sharpen filter to the grayscale image
    sharpen_image = apply_convolution_opencv(image_grayscale, sharpen_kernel)
    show_image_opencv(sharpen_image)
    save_image_opencv(sharpen_image, f"output/{image_name}_sharpen.png")

    # calculate histogram for sharpen image
    sharpen_hist = calculate_histogram(sharpen_image, 0)
    plot_histogram(sharpen_hist, "Filtered", f"output/{image_name}_histogram_sharpen.png")
    plot_histogram_for_all_channels({"Grayscale": grayscale_hist, "Filtered": sharpen_hist}, f"output/{image_name}_histogram_grayscale_sharpen_filtered.png")


if __name__ == "__main__":
    main()
