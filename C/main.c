#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/image.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image_path> <output_image_name>\n", argv[0]);
        return 1;
    }

    char *input_path = argv[1];
    char *output_name = argv[2];

    // Load the image
    image im = load_image(input_path);
    if (!im.data) {
        fprintf(stderr, "Failed to load image: %s\n", input_path);
        return 1;
    }

    printf("Image loaded. Width: %d, Height: %d, Channels: %d\n", im.w, im.h, im.c);

    // Convert to grayscale
    image gray = rgb_to_grayscale(im);

    // Prepare output path
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "output/%s", output_name);

    // Save the grayscale image
    save_image(gray, output_path);
    printf("Grayscale image saved to: %s\n", output_path);

    // Free memory
    free_image(im);
    free_image(gray);

    return 0;
}
