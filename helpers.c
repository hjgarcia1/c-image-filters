#include "helpers.h"
#include "stdio.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue;
    float average;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            red = image[j][i].rgbtRed;
            green = image[j][i].rgbtGreen;
            blue = image[j][i].rgbtBlue;

            average = (red + green + blue) / 3;

            image[j][i].rgbtRed = round(average);
            image[j][i].rgbtGreen = round(average);
            image[j][i].rgbtBlue = round(average);
        }
    }

    return;
}

int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue;
    float sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            red = image[j][i].rgbtRed;
            green = image[j][i].rgbtGreen;
            blue = image[j][i].rgbtBlue;

            sepiaRed = .393 * red + .769 * green + .189 * blue;
            sepiaGreen = .349 * red + .686 * green + .168 * blue;
            sepiaBlue = .272 * red + .534 * green + .131 * blue;

            image[j][i].rgbtRed = cap(round(sepiaRed));
            image[j][i].rgbtGreen = cap(round(sepiaGreen));
            image[j][i].rgbtBlue = cap(round(sepiaBlue));
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < width / 2; i++)
    {
        for (int j = 0; j < height; j++)
        {
            RGBTRIPLE temp = image[j][i];
            image[j][i] = image[j][width - 1 - i];
            image[j][width - i] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newImage[i][j] = image[i][j];
        }
    }

    int red = 0, blue = 0, green = 0, count = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = green = blue = count = 0;
            // add the center pixel
            if (i >= 0 && j >= 0)
            {
                red += newImage[i][j].rgbtRed;
                green += newImage[i][j].rgbtGreen;
                blue += newImage[i][j].rgbtBlue;
                count++;
            }
            // add below pixel
            if (i >= 0 && j - 1 >= 0)
            {
                red += newImage[i][j - 1].rgbtRed;
                green += newImage[i][j - 1].rgbtGreen;
                blue += newImage[i][j - 1].rgbtBlue;
                count++;
            }
            // add right pixel
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                red += newImage[i][j + 1].rgbtRed;
                green += newImage[i][j + 1].rgbtGreen;
                blue += newImage[i][j + 1].rgbtBlue;
                count++;
            }
            // add left pixel
            if (i - 1 >= 0 && j >= 0)
            {
                red += newImage[i - 1][j].rgbtRed;
                green += newImage[i - 1][j].rgbtGreen;
                blue += newImage[i - 1][j].rgbtBlue;
                count++;
            }
            // add left below pixel
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += newImage[i - 1][j - 1].rgbtRed;
                green += newImage[i - 1][j - 1].rgbtGreen;
                blue += newImage[i - 1][j - 1].rgbtBlue;
                count++;
            }
            // add left upper pixel
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                red += newImage[i - 1][j + 1].rgbtRed;
                green += newImage[i - 1][j + 1].rgbtGreen;
                blue += newImage[i - 1][j + 1].rgbtBlue;
                count++;
            }
            // add upper pixel
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += newImage[i + 1][j].rgbtRed;
                green += newImage[i + 1][j].rgbtGreen;
                blue += newImage[i + 1][j].rgbtBlue;
                count++;
            }
            // add below right pixel
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                red += newImage[i + 1][j - 1].rgbtRed;
                green += newImage[i + 1][j - 1].rgbtGreen;
                blue += newImage[i + 1][j - 1].rgbtBlue;
                count++;
            }
            // add upper right pixel
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                red += newImage[i + 1][j + 1].rgbtRed;
                green += newImage[i + 1][j + 1].rgbtGreen;
                blue += newImage[i + 1][j + 1].rgbtBlue;
                count++;
            }

            image[i][j].rgbtRed = round(red / (count * 1.0));
            image[i][j].rgbtGreen = round(green / (count * 1.0));
            image[i][j].rgbtBlue = round(blue / (count * 1.0));
        }
    }

    return;
}
