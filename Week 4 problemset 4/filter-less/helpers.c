#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel divide every color by 3 and round it to the closest decimal and then assign that value to Red, Green and Blue;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = round((r + g + b) / 3);
            image[i][j].rgbtGreen = image[i][j].rgbtBlue = image[i][j].rgbtRed;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (image[i][j].rgbtRed > 255)
                image[i][j].rgbtRed = 255;

            if (image[i][j].rgbtGreen > 255)
                image[i][j].rgbtGreen = 255;

            if (image[i][j].rgbtBlue > 255)
                image[i][j].rgbtBlue = 255;

            temp_image[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    /*For each image's pixel create 3 float variables for RGB and multiply each color to get the shade for the sepia
     filter round them and assign them to RGB then check if each color isn't above 255 if they are bring them to 255*/
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            float sepiaRed = 0;
            float sepiaGreen = 0;
            float sepiaBlue = 0;

            sepiaRed = .393 * temp_image[i][j].rgbtRed + .769 * temp_image[i][j].rgbtGreen + .189 * temp_image[i][j].rgbtBlue;
            sepiaGreen = .349 * temp_image[i][j].rgbtRed + .686 * temp_image[i][j].rgbtGreen + .168 * temp_image[i][j].rgbtBlue;
            sepiaBlue = .272 * temp_image[i][j].rgbtRed + .534 * temp_image[i][j].rgbtGreen + .131 * temp_image[i][j].rgbtBlue;

            if (sepiaRed > 255)
                sepiaRed = 255;

            if (sepiaGreen > 255)
                sepiaGreen = 255;

            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary image of the same size to write the reversed image in;
    RGBTRIPLE temp_image[height][width];

    // Assign each image pixel to the temporary image
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            temp_image[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // Take the temporary image as template and reflect each rows of pixels to get the reflected image
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j].rgbtRed = temp_image[i][(width - 1) - j].rgbtRed;
            image[i][j].rgbtGreen = temp_image[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtBlue = temp_image[i][(width - 1) - j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a temporary image
    RGBTRIPLE temp_image[height][width];

    // Duplicate the image into the temporary image
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            temp_image[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_image[i][j].rgbtBlue = image[i][j].rgbtBlue;

        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // Create average for each colors and assign them 0 and create a variable pixelsUsed and reset it to 0
            float avgReds = 0;
            float avgBlues = 0;
            float avgGreens = 0;
            int pixelsUsed = 0;

            // We taka a 3 by 3 box of pixels and get the average for each pixels RGB
            for (int k = -1; k < 2; ++k)
            {
                for (int l = -1; l < 2; ++l)
                {
                    // This is to make sure we're not outside the picture if we're not add each Red value, Blue value and Green value to the average corresponding color.
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        avgReds += temp_image[i + k][j + l].rgbtRed;
                        avgGreens +=  temp_image[i + k][j + l].rgbtGreen;
                        avgBlues +=  temp_image[i + k][j + l].rgbtBlue;
                        ++pixelsUsed;
                    }
                }
            }
            // set the current pixel we are on to the avg of the block
            image[i][j].rgbtRed = round(avgReds / pixelsUsed);
            image[i][j].rgbtGreen = round(avgGreens / pixelsUsed);
            image[i][j].rgbtBlue = round(avgBlues / pixelsUsed);
        }
    }
    return;
}
