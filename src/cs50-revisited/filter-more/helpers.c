#include "helpers.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PIX_AVRG(p) ((p.rgbtBlue + p.rgbtGreen + p.rgbtRed) / 3)
#define IN_BOUNDS(x, y) (0 <= (x) && (x) < (y))

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define RAND_RGB_OFFSET() (-255 + (rand() / (RAND_MAX / (255 - -255))))
#define OFFSET_PIXEL(p, off) (MIN(255, MAX(0, p + off)))



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

RGBTRIPLE box_avrg(int ph, int pw, int height, int width,
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
        return (RGBTRIPLE) {0, 0, 0};
    return (RGBTRIPLE){rgbsum[0] / npix, rgbsum[1] / npix, rgbsum[2] / npix};
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_ref[height][width];
    memcpy(img_ref, image, sizeof(RGBTRIPLE) * height * width);
    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++)
            image[h][w] = box_avrg(h, w, height, width, img_ref);
}

// Random color offset
void offset_color(int height, int width, RGBTRIPLE image[height][width])
{
    srand(time(NULL));
    int roff = RAND_RGB_OFFSET();
    int goff = RAND_RGB_OFFSET();
    int boff = RAND_RGB_OFFSET();
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            BYTE tmp = image[h][w].rgbtRed;
            image[h][w].rgbtRed = OFFSET_PIXEL(image[h][w].rgbtBlue, roff);
            image[h][w].rgbtGreen = OFFSET_PIXEL(image[h][w].rgbtGreen, goff);
            image[h][w].rgbtBlue = OFFSET_PIXEL(tmp, boff);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) { return; }