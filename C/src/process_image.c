#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // Check if the user input did not meet with the expectation
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    
    // Check this one and make sure it's correct
    if (c < 0) c = 0;

    if (x > im.w) x = im.w - 1;
    if (y > im.h) y = im.h - 1;

    // Fill this in
    return im.data[x + y * im.w + im.w * im.h * c];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // Fill this in
    im.data[x + y * im.w + im.w * im.h * c] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    
    // Fill this in
    copy.w = im.w;
    copy.h = im.h;
    for (int channel = 0; channel < im.c; ++channel)
        for (int column = 0; column < im.w; ++column)
            for (int row = 0; row < im.h; ++row)
                set_pixel(copy, column, row, channel, get_pixel(im, column, row, channel));
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    
    // Fill this in
    for (int column = 0; column < im.w; ++column)
        for (int row = 0; row < im.h; ++row)
        {
            set_pixel(gray, 
                      column, 
                      row, 
                      0, 
                      0.299 * get_pixel(im, column, row, 0) + 
                      0.587 * get_pixel(im, column, row, 1) + 
                      0.114 * get_pixel(im, column, row, 2));
        }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for (int column = 0; column < im.w; ++column)
        for (int row = 0; row < im.h; ++row)
        {
            float new_value = get_pixel(im, column, row, c) + v;

            if (new_value<0) new_value = 0;
            else if (new_value>1) new_value = 1;

            set_pixel(im, column, row, c, new_value);
        }
}

void clamp_image(image im)
{
    // Fill this in
    for (int column = 0; column < im.w; ++column)
        for (int row = 0; row < im.h; ++row)
        {
            float r = get_pixel(im, column, row, 0);
            float g = get_pixel(im, column, row, 1);
            float b = get_pixel(im, column, row, 2);

            if (r<0) set_pixel(im, column, row, 0, r);
            else if (r>1) set_pixel(im, column, row, 0, r);

            if (g<0) set_pixel(im, column, row, 1, g);
            else if (g>1) set_pixel(im, column, row, 1, g);

            if (b<0) set_pixel(im, column, row, 2, b);
            else if (b>1) set_pixel(im, column, row, 2, b);
        }
}


void split_image(image im, image *r, image *g, image *b)
{
    // Fill this in
    *r = make_image(im.w, im.h, 1);
    *g = make_image(im.w, im.h, 1);
    *b = make_image(im.w, im.h, 1);

    for (int column = 0; column < im.w; ++column)
        for (int row = 0; row < im.h; ++row)
        {
            set_pixel(*r, column, row, 0, get_pixel(im, column, row, 0));
            set_pixel(*g, column, row, 0, get_pixel(im, column, row, 1));
            set_pixel(*b, column, row, 0, get_pixel(im, column, row, 2));
        }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}


float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}


void rgb_to_hsv(image im)
{
    // Fill this in
    for (int column = 0; column < im.w; ++column)
        for (int row = 0; row < im.h; ++row)
        {
            float r = get_pixel(im, column, row, 0);
            float g = get_pixel(im, column, row, 1);
            float b = get_pixel(im, column, row, 2);

            float V = three_way_max(r, g, b);
            float m = three_way_min(r, g, b);
            float C = V - m;
            float S = V == 0 ? 0 : C / V;

            float H;
            if (C == 0) H = 0;
            else{
                float H_prime;
                if (V == r) H_prime = (g - b) / C;
                else if (V == g) H_prime = (b - r) / C + 2;
                else {
                    H_prime = (r - g) / C + 4;
                }
                H = H_prime < 0 ? (H_prime / 6 + 1) : H_prime / 6;
            }

            set_pixel(im, column, row, 0, H);
            set_pixel(im, column, row, 1, S);
            set_pixel(im, column, row, 2, V);
        }
}


void hsv_to_rgb(image im)
{
    // TODO Fill this in
    for (int column = 0; column < im.w; ++column)
        for (int row = 0; row < im.h; ++row)
        {
            float H = get_pixel(im, column, row, 0);
            float S = get_pixel(im, column, row, 1);
            float V = get_pixel(im, column, row, 2);

            float H_prime = 6 * H;

            float C = V * S;
            float X = C * (1 - fabs(fmod(H_prime, 2) - 1));
            float m = V - C;
            int H_i = (int)6*H;

            float r, g, b;
            if(H_i == 0)
            {
                r = C;
                g = X;
                b = 0;
            }
            else if(H_i == 1)
            {
                r = X;
                g = C;
                b = 0;

            }
            else if(H_i == 2)
            {
                r = 0;
                g = C;
                b = X;
            }
            else if(H_i == 3)
            {
                r = 0;
                g = X;
                b = C;
            }
            else if(H_i == 4)
            {
                r = X;
                g = 0;
                b = C;
            }
            else
            {
                r = C;
                g = 0;
                b = X; 
            }

            set_pixel(im, column, row, 0, r+m);
            set_pixel(im, column, row, 1, g+m);
            set_pixel(im, column, row, 2, b+m);
        }
}


int* histogram(image im, float min, float max, int bins)
{
    int *histogram = calloc(bins, sizeof(int));
    float bin_size = (max - min) / bins;

    for (int column = 0; column < im.w; ++column)
        for (int row = 0; row < im.h; ++row)
        {
            for (int channel = 0; channel < im.c; ++channel)
            {
                float value = get_pixel(im, column, row, channel);
                int bin = (int)((value - min) / bin_size);
                if (value == max) bin = bins - 1; // Ensure max value falls in the last bin
                if (bin >= 0 && bin < bins) {
                    histogram[bin]++;
                }
            }
        }

    return histogram;
}


image histogram_equlizer(image im)
{
    // Fill this in
    image equlized = copy_image(im);
    int *histogram_values = histogram(equlized, 0, 1, 256);
    int total_pixels = equlized.w * equlized.h * equlized.c;
    float cdf[256] = {0};
    cdf[0] = histogram_values[0] / (float)total_pixels;
    for (int i = 1; i < 256; ++i)
    {
        cdf[i] = cdf[i-1] + histogram_values[i] / (float)total_pixels;
    }

    for (int column = 0; column < equlized.w; ++column)
        for (int row = 0; row < equlized.h; ++row)
        {
            for (int channel = 0; channel < equlized.c; ++channel)
            {
                float value = fminf(fmaxf(get_pixel(equlized, column, row, channel), 0.0f), 1.0f);
                int bin = (int)(value * 255);
                set_pixel(equlized, column, row, channel, cdf[bin]);
            }
        }
    return equlized;
}
