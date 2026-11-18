#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // to take average of each rgb then apply that value to all sets r g b
    // first i need to loop through each and every pixel - images - height var and width var , i
    // need 2 loops one for height and one for width then i call the fnx RGBTRIPLE
    // image[height][width]
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // i need to find avg of all values
            int temp;
            // temp var
            temp = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) /
                         (float) 3);
            // temp avg of the og values
            image[i][j].rgbtRed = temp;
            // red is assigned the og value
            // where is the avg with red being the og avg?? why am i assigning everyhting to reds
            // avg without including avg red into avg blue and avg green calcualations
            image[i][j].rgbtGreen = image[i][j].rgbtBlue = image[i][j].rgbtRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // need to loop through height
    // need to take a pixel at width i and swap it with a pixel at width (width-i)
    for (int i = 0; i < height; i++)
    {
        for (int k = width - 1; k >= width / 2; k = k - 1) // k goes from width end to 0
        {
            RGBTRIPLE temp;
            temp = image[i][k]; // temp stores first pixel
            image[i][k] =
                image[i][width - k - 1];    // width-k means pixel from k distance end = first pixel
            image[i][width - k - 1] = temp; // end pixel is changed to first pixel
            // this programme stops at centre cuz width-k=width at k/2
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // need to find avg of all colour values in 1 distance from the pixel im working on
    // need to loop through each pixel then i have to loop trhough all nearby pixels and stop at
    // edge cases too
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int av1;
            int av2;
            int av3;
            int count = 1;
            int temp = image[i][j].rgbtRed;
            int temp1 = image[i][j].rgbtGreen;
            int temp2 = image[i][j].rgbtBlue;
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                temp = temp + image[i - 1][j - 1].rgbtRed;
                temp1 = temp1 + image[i - 1][j - 1].rgbtGreen;
                temp2 = temp2 + image[i - 1][j - 1].rgbtBlue;
                count++;
            }
            if (i - 1 >= 0 && j >= 0)
            {
                temp = temp + image[i - 1][j].rgbtRed;
                temp1 = temp1 + image[i - 1][j].rgbtGreen;
                temp2 = temp2 + image[i - 1][j].rgbtBlue;
                count++;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                temp = temp + image[i - 1][j + 1].rgbtRed;
                temp1 = temp1 + image[i - 1][j + 1].rgbtGreen;
                temp2 = temp2 + image[i - 1][j + 1].rgbtBlue;
                count++;
            }
            if (i >= 0 && j - 1 >= 0)
            {
                temp = temp + image[i][j - 1].rgbtRed;
                temp1 = temp1 + image[i][j - 1].rgbtGreen;
                temp2 = temp2 + image[i][j - 1].rgbtBlue;
                count++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                temp = temp + image[i + 1][j + 1].rgbtRed;
                temp1 = temp1 + image[i + 1][j + 1].rgbtGreen;
                temp2 = temp2 + image[i + 1][j + 1].rgbtBlue;
                count++;
            }
            if (i + 1 < height && j >= 0)
            {
                temp = temp + image[i + 1][j].rgbtRed;
                temp1 = temp1 + image[i + 1][j].rgbtGreen;
                temp2 = temp2 + image[i + 1][j].rgbtBlue;
                count++;
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                temp = temp + image[i + 1][j - 1].rgbtRed;
                temp1 = temp1 + image[i + 1][j - 1].rgbtGreen;
                temp2 = temp2 + image[i + 1][j - 1].rgbtBlue;
                count++;
            }
            if (i < height && j + 1 < width)
            {
                temp = temp + image[i][j + 1].rgbtRed;
                temp1 = temp1 + image[i][j + 1].rgbtGreen;
                temp2 = temp2 + image[i][j + 1].rgbtBlue;
                count++;
            }
            av1 = round(temp / (float) count);
            av2 = round(temp1 / (float) count);
            av3 = round(temp2 / (float) count);

            copy[i][j].rgbtRed = av1;
            copy[i][j].rgbtGreen = av2;
            copy[i][j].rgbtBlue = av3;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0, gx_green = 0, gx_blue = 0;
            int gy_red = 0, gy_green = 0, gy_blue = 0;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                gx_red = (-1 * image[i - 1][j - 1].rgbtRed);
                gx_green = (-1 * image[i - 1][j - 1].rgbtGreen);
                gx_blue = (-1 * image[i - 1][j - 1].rgbtBlue);
                gy_red = (-1 * image[i - 1][j - 1].rgbtRed);
                gy_green = (-1 * image[i - 1][j - 1].rgbtGreen);
                gy_blue = (-1 * image[i - 1][j - 1].rgbtBlue);
            }
            if (i - 1 >= 0 && j >= 0)
            {
                gy_red = gy_red + (-2 * image[i - 1][j].rgbtRed);
                gy_green = gy_green + (-2 * image[i - 1][j].rgbtGreen);
                gy_blue = gy_blue + (-2 * image[i - 1][j].rgbtBlue);
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                gx_red = gx_red + (1 * image[i - 1][j + 1].rgbtRed);
                gx_green = gx_green + (1 * image[i - 1][j + 1].rgbtGreen);
                gx_blue = gx_blue + (1 * image[i - 1][j + 1].rgbtBlue);
                gy_red = gy_red + (-1 * image[i - 1][j + 1].rgbtRed);
                gy_green = gy_green + (-1 * image[i - 1][j + 1].rgbtGreen);
                gy_blue = gy_blue + (-1 * image[i - 1][j + 1].rgbtBlue);
            }
            if (i >= 0 && j - 1 >= 0)
            {
                gx_red = gx_red + (-2 * image[i][j - 1].rgbtRed);
                gx_green = gx_green + (-2 * image[i][j - 1].rgbtGreen);
                gx_blue = gx_blue + (-2 * image[i][j - 1].rgbtBlue);
            }
            if (i + 1 < height && j + 1 < width)
            {
                gx_red = gx_red + (1 * image[i + 1][j + 1].rgbtRed);
                gx_green = gx_green + (1 * image[i + 1][j + 1].rgbtGreen);
                gx_blue = gx_blue + (1 * image[i + 1][j + 1].rgbtBlue);
                gy_red = gy_red + (1 * image[i + 1][j + 1].rgbtRed);
                gy_green = gy_green + (1 * image[i + 1][j + 1].rgbtGreen);
                gy_blue = gy_blue + (1 * image[i + 1][j + 1].rgbtBlue);
            }
            if (i + 1 < height && j >= 0)
            {
                gy_red = gy_red + (2 * image[i + 1][j].rgbtRed);
                gy_green = gy_green + (2 * image[i + 1][j].rgbtGreen);
                gy_blue = gy_blue + (2 * image[i + 1][j].rgbtBlue);
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                gx_red = gx_red + (-1 * image[i + 1][j - 1].rgbtRed);
                gx_green = gx_green + (-1 * image[i + 1][j - 1].rgbtGreen);
                gx_blue = gx_blue + (-1 * image[i + 1][j - 1].rgbtBlue);
                gy_red = gy_red + (1 * image[i + 1][j - 1].rgbtRed);
                gy_green = gy_green + (1 * image[i + 1][j - 1].rgbtGreen);
                gy_blue = gy_blue + (1 * image[i + 1][j - 1].rgbtBlue);
            }
            if (i < height && j + 1 < width)
            {
                gx_red = gx_red + (2 * image[i][j + 1].rgbtRed);
                gx_green = gx_green + (2 * image[i][j + 1].rgbtGreen);
                gx_blue = gx_blue + (2 * image[i][j + 1].rgbtBlue);
            }

            int redop = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            int greenop = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
            int blueop = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));
            if (redop > 255)
                redop = 255;
            if (greenop > 255)
                greenop = 255;
            if (blueop > 255)
                blueop = 255;

            copy[i][j].rgbtRed = redop;
            copy[i][j].rgbtGreen = greenop;
            copy[i][j].rgbtBlue = blueop;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}