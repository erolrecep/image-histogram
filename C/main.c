#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "src/image.h"


void parseFileName(const char *path, char *baseName, char *extension) {
    // Find the last slash in the path
    const char *slash = strrchr(path, '/');
    const char *filename = (slash) ? slash + 1 : path; // Start after the slash

    // Find the last dot in the file name
    const char *dot = strrchr(filename, '.');
    if (dot) {
        // Copy the base name
        size_t baseLength = dot - filename;
        strncpy(baseName, filename, baseLength);
        baseName[baseLength] = '\0'; // Null-terminate

        // Copy the extension
        strcpy(extension, dot + 1); // Skip the dot
    } else {
        // No extension found
        strcpy(baseName, filename);
        extension[0] = '\0'; // Empty extension
    }
}


// write histogram to file
void writeHistogramToFile(const char *filename, int *histogram, int bins) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    for (int i = 0; i < bins; ++i) {
        fprintf(file, "%d, %d\n", i, histogram[i]);
    }

    fclose(file);
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_image_path>\n", argv[0]);
        return 1;
    }

    char *input_path = argv[1];

    // Check if the input image file path exists
    if (access(input_path, F_OK) == -1) {
        fprintf(stderr, "Error: Input file '%s' does not exist.\n", input_path);
        return 1;
    }

    // Extract the image name from the input path
    char imageName[128], extension[6];

    // For consistency, we want to use same name for each output.
    parseFileName(input_path, imageName, extension);

    printf("Image Name: %s\n", imageName);
    printf("Extension: %s\n", extension);

    // replace the image name with "image"
    strcpy(imageName, "image");

    char output_name[128];
    snprintf(output_name, sizeof(output_name), "%s_grayscale.%s", imageName, extension);

    // Load the image
    image im = load_image(input_path);
    if (!im.data) {
        fprintf(stderr, "Failed to load image: %s\n", input_path);
        return 1;
    }

    printf("Image loaded. Width: %d, Height: %d, Channels: %d\n", im.w, im.h, im.c);

    // Convert to grayscale
    image gray = rgb_to_grayscale(im);

    // Siplit image into channels
    image r, g, b;
    split_image(im, &r, &g, &b);

    printf("Image split into channels.\n");

    // Calculate histograms for each channel
    int *r_hist = histogram(r, 0, 1, 256);
    int *g_hist = histogram(g, 0, 1, 256);
    int *b_hist = histogram(b, 0, 1, 256);
    int *gray_hist = histogram(gray, 0, 1, 256);

    // Save histograms to files
    char output_r_hist[128], output_g_hist[128], output_b_hist[128], output_gray_hist[128];
    snprintf(output_r_hist, sizeof(output_r_hist), "output/%s_r_hist.txt", imageName);
    snprintf(output_g_hist, sizeof(output_g_hist), "output/%s_g_hist.txt", imageName);
    snprintf(output_b_hist, sizeof(output_b_hist), "output/%s_b_hist.txt", imageName);
    snprintf(output_gray_hist, sizeof(output_gray_hist), "output/%s_gray_hist.txt", imageName);

    writeHistogramToFile(output_r_hist, r_hist, 256);
    writeHistogramToFile(output_g_hist, g_hist, 256);
    writeHistogramToFile(output_b_hist, b_hist, 256);
    writeHistogramToFile(output_gray_hist, gray_hist, 256);

    printf("Histograms saved to: %s, %s, %s, %s\n", output_r_hist, output_g_hist, output_b_hist, output_gray_hist);

    // Apply histogram equalization to all channels
    image r_equlized = copy_image(histogram_equlizer(r));
    image g_equlized = copy_image(histogram_equlizer(g));
    image b_equlized = copy_image(histogram_equlizer(b));
    image gray_equlized = copy_image(histogram_equlizer(gray));

    printf("Histogram equalization applied to all channels.\n");

    // Save equalized images
    char output_r_equlized[128], output_g_equlized[128], output_b_equlized[128], output_gray_equlized[128];
    snprintf(output_r_equlized, sizeof(output_r_equlized), "output/%s_r_equlized.%s", imageName, extension);
    snprintf(output_g_equlized, sizeof(output_g_equlized), "output/%s_g_equlized.%s", imageName, extension);
    snprintf(output_b_equlized, sizeof(output_b_equlized), "output/%s_b_equlized.%s", imageName, extension);
    snprintf(output_gray_equlized, sizeof(output_gray_equlized), "output/%s_gray_equlized.%s", imageName, extension);

    save_image(r_equlized, output_r_equlized);
    save_image(g_equlized, output_g_equlized);
    save_image(b_equlized, output_b_equlized);
    save_image(gray_equlized, output_gray_equlized);

    printf("Equalized images saved to: %s, %s, %s, %s\n", output_r_equlized, output_g_equlized, output_b_equlized, output_gray_equlized);

    // Save all individual channels as an image
    char output_r_channel[128], output_g_channel[128], output_b_channel[128];
    snprintf(output_r_channel, sizeof(output_r_channel), "output/%s_r_channel.%s", imageName, extension);
    snprintf(output_g_channel, sizeof(output_g_channel), "output/%s_g_channel.%s", imageName, extension);
    snprintf(output_b_channel, sizeof(output_b_channel), "output/%s_b_channel.%s", imageName, extension);

    save_image(r, output_r_channel);
    save_image(g, output_g_channel);
    save_image(b, output_b_channel);

    printf("Individual channels saved to: %s, %s, %s\n", output_r_channel, output_g_channel, output_b_channel);

    // Prepare output path
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "output/%s", output_name);

    // Save the grayscale image
    save_image(gray, output_path);
    printf("Grayscale image saved to: %s\n", output_path);

    // Free memory
    free_image(im);
    free_image(gray);
    free_image(r);
    free_image(g);
    free_image(b);
    free_image(r_equlized);
    free_image(g_equlized);
    free_image(b_equlized);
    free_image(gray_equlized);
    free(r_hist);
    free(g_hist);
    free(b_hist);
    free(gray_hist);
    printf("Memory freed.\n");

    return 0;
}
