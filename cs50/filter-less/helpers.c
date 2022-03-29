#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    double k;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            k = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtRed = round(k);
            image[i][j].rgbtGreen = round(k);
            image[i][j].rgbtBlue = round(k);
            j++;
        }
        i++;
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    double sepiaRed;
    double sepiaGreen;
    double sepiaBlue;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            sepiaRed = image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtBlue * 0.189;
            sepiaGreen = image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtBlue * 0.168;
            sepiaBlue = image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtBlue * 0.131;
            if (round(sepiaRed) > 255)
            {
                sepiaRed = 255;
            }
            if (round(sepiaGreen) > 255)
            {
                sepiaGreen = 255;
            }
            if (round(sepiaBlue) > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
            j++;
        }
        i++;
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    RGBTRIPLE tmp;
    while (i < height)
    {
        j = 0;
        while (j < width / 2)
        {
            tmp = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = tmp;
            j++;
        }
        i++;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    RGBTRIPLE temp[height][width];
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            temp[i][j] = image[i][j];
            j++;
        }
        i++;
    }
    i = 0;
    j = 0;
    int k;
    int l;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            float sum_red;
            float sum_blue;
            float sum_green;
            int counter;
            sum_red = sum_blue = sum_green = counter = 0;
            k = -1;
            while (k < 2)
            {
                l = -1;
                while (l < 2)
                {
                    if (i + k < 0 || i + k >= height)
                    {
                        l++;
                        continue;
                    }
                    if (j + l < 0 || j + l >= width)
                    {
                        l++;
                        continue;
                    }
                    sum_red += temp[i + k][j + l].rgbtRed;
                    sum_blue += temp[i + k][j + l].rgbtBlue;
                    sum_green += temp[i + k][j + l].rgbtGreen;
                    counter++;
                    l++;
                }
                k++;
            }
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            j++;
        }
        i++;
    }
    return;
}
