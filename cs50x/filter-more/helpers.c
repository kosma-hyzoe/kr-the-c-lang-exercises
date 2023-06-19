#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define BLUE 0
#define GREEN 1
#define RED 2

#define PIX_AVRG(p) (round((p.rgbtBlue + p.rgbtGreen + p.rgbtRed) / 3.0))
#define IN_BOUNDS(x, y) (0 <= (x) && (x) < (y))
#define CAP_255(x) (x > 255 ? 255 : x)

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            uint8_t avrg = PIX_AVRG(image[h][w]);
            image[h][w] = (RGBTRIPLE){avrg, avrg, avrg};
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width / 2; w++) {
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = tmp;
        }
    }
}

RGBTRIPLE _blur_box_average(int x, int y, int height, int width,
                            RGBTRIPLE img[height][width])
{
    uint16_t rgbsum[3] = {0, 0, 0};

    int n = 0;
    for (int h = x - 1; h <= x + 1; h++) {
        for (int w = y - 1; w <= y + 1; w++) {
            if (IN_BOUNDS(w, width) && IN_BOUNDS(h, height)) {
                n++;
                rgbsum[BLUE] += img[h][w].rgbtBlue;
                rgbsum[GREEN] += img[h][w].rgbtGreen;
                rgbsum[RED] += img[h][w].rgbtRed;
            }
        }
    }
    if (n == 0)
        return (RGBTRIPLE){0, 0, 0};

    return (RGBTRIPLE){round(rgbsum[BLUE] / (float)n),
                       round(rgbsum[GREEN] / (float)n),
                       round(rgbsum[RED] / (float)n)};
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_ref[height][width];
    memcpy(img_ref, image, sizeof(RGBTRIPLE) * height * width);
    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++)
            image[h][w] = _blur_box_average(h, w, height, width, img_ref);
}


RGBTRIPLE _edges_sobel_operator(int ph, int pw, int height, int width,
                  RGBTRIPLE img_ref[height][width])
{

    int gxweight[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gyweight[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int gxsum[3] = {0, 0, 0}, gysum[3] = {0, 0, 0};

    int i = 0;
    for (int h = ph - 1; h <= ph + 1; h++) {
        for (int w = pw - 1; w <= pw + 1; w++) {
            if (IN_BOUNDS(w, width) && IN_BOUNDS(h, height)) {
                gxsum[BLUE] += img_ref[h][w].rgbtBlue * gxweight[i];
                gxsum[GREEN] += img_ref[h][w].rgbtGreen * gxweight[i];
                gxsum[RED] += img_ref[h][w].rgbtRed * gxweight[i];

                gysum[BLUE] += img_ref[h][w].rgbtBlue * gyweight[i];
                gysum[GREEN] += img_ref[h][w].rgbtGreen * gyweight[i];
                gysum[RED] += img_ref[h][w].rgbtRed * gyweight[i];
            }
            i++;
        }
    }

    return (RGBTRIPLE) {
        CAP_255(round(sqrt(pow(gxsum[BLUE], 2) + pow(gysum[BLUE], 2)))),
        CAP_255(round(sqrt(pow(gxsum[GREEN], 2) + pow(gysum[GREEN], 2)))),
        CAP_255(round(sqrt(pow(gxsum[RED], 2) + pow(gysum[RED], 2)))),
    };
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_ref[height][width];
    memcpy(img_ref, image, sizeof(RGBTRIPLE) * height * width);
    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++)
            image[h][w] = _edges_sobel_operator(h, w, height, width, img_ref);
}