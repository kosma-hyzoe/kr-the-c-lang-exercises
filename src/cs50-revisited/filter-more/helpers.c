#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PIX_AVRG(p) ((p.rgbtBlue + p.rgbtGreen + p.rgbtRed) / 3)
#define IN_BOUNDS(x, y) (0 <= (x) && (x) < (y))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define PIX_CAP(x) ((MIN(x, 255)))

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

RGBTRIPLE _box_avrg(int ph, int pw, int height, int width,
                    RGBTRIPLE img[height][width])
{

    int npix = 0;
    uint16_t rgbsum[3] = {0, 0, 0};
    for (int h = ph - 1; h <= ph + 1; h++) {
        for (int w = pw - 1; w <= pw + 1; w++) {
            if (IN_BOUNDS(w, width) && IN_BOUNDS(h, height)) {
                npix++;
                rgbsum[0] += img[h][w].rgbtBlue;
                rgbsum[1] += img[h][w].rgbtGreen;
                rgbsum[2] += img[h][w].rgbtRed;
            }
        }
    }
    if (npix == 0)
        return (RGBTRIPLE){0, 0, 0};
    return (RGBTRIPLE){rgbsum[0] / npix, rgbsum[1] / npix, rgbsum[2] / npix};
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_ref[height][width];
    memcpy(img_ref, image, sizeof(RGBTRIPLE) * height * width);
    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++)
            image[h][w] = _box_avrg(h, w, height, width, img_ref);
}

RGBTRIPLE _sobel_filter(int ph, int pw, int height, int width,
                        RGBTRIPLE img[height][width],
                        RGBTRIPLE img_ref[height][width])
{
    int npix = 0;
    uint16_t rgbsum[3] = {0, 0, 0};
    int break_flag = 0;

    uint16_t gxsum[3], yxsum[3], sobel[3];
    int gxweight[][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int yxweight[][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int h = ph - 1; h <= ph + 1; h++) {
        for (int w = pw - 1; w <= pw + 1; w++) {
            if (IN_BOUNDS(w, width) && IN_BOUNDS(h, height)) {
                gxsum[0] = img_ref[h][w].rgbtRed * gxweight[h][w];
                gxsum[1] = img_ref[h][w].rgbtGreen * gxweight[h][w];
                gxsum[2] = img_ref[h][w].rgbtBlue * gxweight[h][w];

                yxsum[0] = img_ref[h][w].rgbtRed * yxweight[h][w];
                yxsum[1] = img_ref[h][w].rgbtGreen * yxweight[h][w];
                yxsum[2] = img_ref[h][w].rgbtBlue * yxweight[h][w];

                sobel[0] = PIX_CAP(sqrt(pow(gxsum[0]) + pow(yxsum[0])));
                sobel[1] = PIX_CAP(sqrt(pow(gxsum[1]) + pow(yxsum[1])));
                sobel[2] = PIX_CAP(sqrt(pow(gxsum[2]), pow(yxsum[2])));

                img[h][w].rgbtRed = sobel[0];
                img[h][w].rgbtGreen = sobel[1];
                img[h][w].rgbtBlue = sobel[2];
            } else {
                continue;
            }
        }
    }

    if (npix == 0)
        return (RGBTRIPLE){0, 0, 0};
    return (RGBTRIPLE){rgbsum[0] / npix, rgbsum[1] / npix, rgbsum[2] / npix};
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_ref[height][width];
    memcpy(img_ref, image, sizeof(RGBTRIPLE) * height * width);
    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++)
            _sobel_filter(h, w, height, width, image[height][width], img_ref[height][width]);
}