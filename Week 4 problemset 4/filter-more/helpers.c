#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel take the rgb value add them all together and divide them 3 to get the average then assign that value to r, g and b
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            image[h][w].rgbtRed = image[h][w].rgbtBlue = image[h][w].rgbtGreen = round((float)(image[h][w].rgbtRed + image[h][w].rgbtBlue + image[h][w].rgbtGreen) / 3);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create another image and copy the original image there
    RGBTRIPLE tempImage[height][width];

    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            tempImage[h][w].rgbtRed = image[h][w].rgbtRed;
            tempImage[h][w].rgbtGreen = image[h][w].rgbtGreen;
            tempImage[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    /* For each pixel assign each pixel from the copied image to the opposite side of the image (using (width - 1 - w so for example if it's the pixel 0 in the array and width = 128 then the pixel 0 in tempImage will end up in the 127th pixel
    one less pixel because we need to count pixel 0)*/
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            image[h][w].rgbtRed = tempImage[h][width - w - 1].rgbtRed;
            image[h][w].rgbtBlue = tempImage[h][width - w - 1].rgbtBlue;
            image[h][w].rgbtGreen = tempImage[h][width - w - 1].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a carbon copy of the image
    RGBTRIPLE tempImage[height][width];
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            tempImage[h][w].rgbtRed = image[h][w].rgbtRed;
            tempImage[h][w].rgbtGreen = image[h][w].rgbtGreen;
            tempImage[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    // For each pixel create 4 variables 3 of those are average for R, G and B and another one as a counter for the number of pixels taken as average
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            float avgReds = 0;
            float avgGreens = 0;
            float avgBlues = 0;
            int numPixels = 0;
            //For each pixel in the 3x3 box if they're not outside the picture add each pixel to the average of the corresponding color and add one to the number of pixels
            for (int i = -1; i < 2; ++i)
            {
                for (int j = -1; j < 2; ++j)
                {
                    if ((h + i >= 0 && h + i < height) && (w + j >= 0 && w + j < width))
                    {
                        avgReds += tempImage[h + i][w + j].rgbtRed;
                        avgGreens += tempImage[h + i][w + j].rgbtGreen;
                        avgBlues += tempImage[h + i][w + j].rgbtBlue;
                        ++numPixels;

                    }
                }
            }
            //Assign for each color their average divided by the number of pixels to blur the pixels
            image[h][w].rgbtRed = round(avgReds / numPixels);
            image[h][w].rgbtGreen = round(avgGreens / numPixels);
            image[h][w].rgbtBlue = round(avgBlues / numPixels);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image and define Gx and Gy as an array
    RGBTRIPLE tempImage[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            tempImage[h][w].rgbtRed = image[h][w].rgbtRed;
            tempImage[h][w].rgbtGreen = image[h][w].rgbtGreen;
            tempImage[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            int GxR = 0;
            int GxG = 0;
            int GxB = 0;
            int GyR = 0;
            int GyG = 0;
            int GyB = 0;

            for (int i = -1; i < 2; ++i)
            {
                for (int j = -1; j < 2; ++j)
                {
                    if (h + i < 0 || h + i > height - 1)
                    {
                        continue;
                    }
                    if (w + j < 0 || w + j > width - 1)
                    {
                        continue;
                    }

                    GxR += tempImage[h + i][w + j].rgbtRed * Gx[i + 1][j + 1];
                    GyR += tempImage[h + i][w + j].rgbtRed * Gy[i + 1][j + 1];
                    GxG += tempImage[h + i][w + j].rgbtGreen * Gx[i + 1][j + 1];
                    GyG += tempImage[h + i][w + j].rgbtGreen * Gy[i + 1][j + 1];
                    GxB += tempImage[h + i][w + j].rgbtBlue * Gx[i + 1][j + 1];
                    GyB += tempImage[h + i][w + j].rgbtBlue * Gy[i + 1][j + 1];


                }
            }

            int Red = round(sqrt(GxR * GxR + GyR * GyR));
            int Green = round(sqrt(GxG * GxG + GyG * GyG));
            int Blue = round(sqrt(GxB * GxB + GyB * GyB));

            image[h][w].rgbtRed = (Red > 255) ? 255 : Red;
            image[h][w].rgbtGreen = (Green > 255) ? 255 : Green;
            image[h][w].rgbtBlue = (Blue > 255) ? 255 : Blue;

        }
    }
    return;
}
