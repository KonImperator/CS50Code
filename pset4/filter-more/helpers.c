#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int current_pixel_red = image[row][col].rgbtRed;
            int current_pixel_green = image[row][col].rgbtGreen;
            int current_pixel_blue = image[row][col].rgbtBlue;

            int average = round((current_pixel_red + current_pixel_green + current_pixel_blue) / 3.0);

            image[row][col].rgbtRed = average;
            image[row][col].rgbtGreen = average;
            image[row][col].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            RGBTRIPLE buffer = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - 1 - col] = buffer;
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
        for (int col = 0; col < width; col++)
        {
            // copying original image for an unchanged copy to iterate with
            copy[row][col] = image[row][col];
        }
    }
    // looping through array finding individual pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // initializing variables for calculation
            float divisor = 0.00;
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;

            // looping through previous pixel, current pixel and next pixel
            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = col - 1; j <= col + 1; j++)
                {
                    // excluding anything outside of range
                    if (i < 0 || i >= height || j < 0 || j >= width)
                    {
                        continue;
                    }
                    // calculating individual colors
                    sum_red += copy[i][j].rgbtRed;
                    sum_green += copy[i][j].rgbtGreen;
                    sum_blue += copy[i][j].rgbtBlue;
                    divisor++;
                }
            }
            // giving each pixel its new value
            image[row][col].rgbtRed = round(sum_red / divisor);
            image[row][col].rgbtGreen = round(sum_green / divisor);
            image[row][col].rgbtBlue = round(sum_blue / divisor);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // copying original image for an unchanged copy to iterate with
            copy[row][col] = image[row][col];
        }
    }
    // looping through array finding individual pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // initializing variables for calculation
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;
            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;
            int gx_array[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int gy_array[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
            int counter = 0;

            // looping through previous pixel, current pixel and next pixel
            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = col - 1; j <= col + 1; j++)
                {
                    // if outside of range disregard and increase counter
                    if (i < 0 || i >= height || j < 0 || j >= width)
                    {
                        counter++;
                    }
                    else
                    {
                        // calculating Gx and Gy values for each color

                        gx_red += copy[i][j].rgbtRed * gx_array[counter];
                        gx_green += copy[i][j].rgbtGreen * gx_array[counter];
                        gx_blue += copy[i][j].rgbtBlue * gx_array[counter];
                        gy_red += copy[i][j].rgbtRed * gy_array[counter];
                        gy_green += copy[i][j].rgbtGreen * gy_array[counter];
                        gy_blue += copy[i][j].rgbtBlue * gy_array[counter];
                        counter++;
                    }
                }
            }
            // calculating the new color value
            double red = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            double green = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
            double blue = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));

            // cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // replacing old value with the new one
            image[row][col].rgbtRed = red;
            image[row][col].rgbtGreen = green;
            image[row][col].rgbtBlue = blue;
        }
    }
}
