#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int current_pixel_red = image[row][column].rgbtRed;
            int current_pixel_green = image[row][column].rgbtGreen;
            int current_pixel_blue = image[row][column].rgbtBlue;

            int average = round((current_pixel_red + current_pixel_green + current_pixel_blue) / 3.0);

            image[row][column].rgbtRed = average;
            image[row][column].rgbtGreen = average;
            image[row][column].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int current_pixel_red = image[row][column].rgbtRed;
            int current_pixel_green = image[row][column].rgbtGreen;
            int current_pixel_blue = image[row][column].rgbtBlue;

            int sepiaRed = round(.393 * current_pixel_red + .769 * current_pixel_green + .189 * current_pixel_blue);
            int sepiaGreen = round(.349 * current_pixel_red + .686 * current_pixel_green + .168 * current_pixel_blue);
            int sepiaBlue = round(.272 * current_pixel_red + .534 * current_pixel_green + .131 * current_pixel_blue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[row][column].rgbtRed = sepiaRed;
            image[row][column].rgbtBlue = sepiaBlue;
            image[row][column].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            RGBTRIPLE buffer = image[row][column];
            image[row][column] = image[row][width - column - 1];
            image[row][width - 1 - column] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // copying original image for an unchanged copy to iterate with
            copy[row][column] = image[row][column];
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (row == 0)
            {
                if (column == 0)
                // Top left corner
                {
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed + copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) / 4.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) / 4.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) / 4.0);
                }
                else if (column == width - 1)
                // Top right corner
                {
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row + 1][column].rgbtRed + copy[row][column - 1].rgbtRed + copy[1][column row + - 1].rgbtRed) / 4.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row][column - 1].rgbtGreen + copy[row + 1][column - 1].rgbtGreen) / 4.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row][column - 1].rgbtBlue + copy[row + 1][column - 1].rgbtBlue) / 4.0);
                }
                else
                {
                    // Top edge
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row + 1][column].rgbtRed + copy[row][column - 1].rgbtRed + copy[row + 1][column - 1].rgbtRed + copy[row][column + 1].rgbtRed + copy[row + 1][column + 1].rgbtRed) / 6.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row][column - 1].rgbtGreen + copy[row + 1][column - 1].rgbtGreen + copy[row][column + 1].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) / 6.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row][column - 1].rgbtBlue + copy[row + 1][column - 1].rgbtBlue + copy[row][column + 1].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) / 6.0);
                }
            }
            else if (row > 0 && row < height - 1)
            {
                if (column == 0)
                // Left edge
                {
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row + 1][column].rgbtRed + copy[row - 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed + copy[row][column + 1].rgbtRed + copy[row - 1][column + 1].rgbtRed) / 6.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen + copy[row][column + 1].rgbtGreen + copy[row - 1][column + 1].rgbtGreen) / 6.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue + copy[row][column + 1].rgbtBlue + copy[row - 1][column + 1].rgbtBlue) / 6.0);
                }
                else if (column == width - 1)
                // Right edge
                {
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row + 1][column].rgbtRed + copy[row - 1][column].rgbtRed + copy[row + 1][column - 1].rgbtRed + copy[row][column - 1].rgbtRed + copy[row - 1][column - 1].rgbtRed) / 6.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row + 1][column - 1].rgbtGreen + copy[row][column - 1].rgbtGreen + copy[row - 1][column - 1].rgbtGreen) / 6.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row + 1][column - 1].rgbtBlue + copy[row][column - 1].rgbtBlue + copy[row - 1][column - 1].rgbtBlue) / 6.0);
                }
                else
                {
                    // any pixel not at an edge or corner
                    image[row][column].rgbtRed = round((copy[row - 1][column - 1].rgbtRed + copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed + copy[row][column - 1].rgbtRed + copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed + copy[row + 1][column - 1].rgbtRed + copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) / 9.0);
                    image[row][column].rgbtBlue = round((copy[row - 1][column - 1].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue + copy[row][column - 1].rgbtBlue + copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue + copy[row + 1][column - 1].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) / 9.0);
                    image[row][column].rgbtGreen = round((copy[row - 1][column - 1].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen + copy[row][column - 1].rgbtGreen + copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen + copy[row + 1][column - 1].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) / 9.0);
                }
            }
            else if (row == height - 1)
            {
                if (column == 0)
                // Bottom left corner
                {
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row - 1][column].rgbtRed + copy[row][column + 1].rgbtRed + copy[row - 1][column + 1].rgbtRed) / 4.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row][column + 1].rgbtGreen + copy[row - 1][column + 1].rgbtGreen) / 4.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row][column + 1].rgbtBlue + copy[row - 1][column + 1].rgbtBlue) / 4.0);
                }
                else if (column == width - 1)
                // Bottom right corner
                {
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row - 1][column].rgbtRed + copy[row][column - 1].rgbtRed + copy[row - 1][column - 1].rgbtRed) / 4.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row][column - 1].rgbtGreen + copy[row - 1][column - 1].rgbtGreen) / 4.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row][column - 1].rgbtBlue + copy[row - 1][column - 1].rgbtBlue) / 4.0);
                }
                else
                // Bottom edge
                {
                    image[row][column].rgbtRed = round((copy[row][column].rgbtRed + copy[row - 1][column].rgbtRed + copy[row][column - 1].rgbtRed + copy[row - 1][column - 1].rgbtRed + copy[row][column + 1].rgbtRed + copy[row - 1][column + 1].rgbtRed) / 6.0);
                    image[row][column].rgbtGreen = round((copy[row][column].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row][column - 1].rgbtGreen + copy[row - 1][column - 1].rgbtGreen + copy[row][column + 1].rgbtGreen + copy[row - 1][column + 1].rgbtGreen) / 6.0);
                    image[row][column].rgbtBlue = round((copy[row][column].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row][column - 1].rgbtBlue + copy[row - 1][column - 1].rgbtBlue + copy[row][column + 1].rgbtBlue + copy[row - 1][column + 1].rgbtBlue) / 6.0);
                }
            }
        }
    }
}