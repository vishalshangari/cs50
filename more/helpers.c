#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE* temp = malloc(sizeof(RGBTRIPLE));
            float pixel_avg = (float)((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float)3);
            int pixel_avg_int = roundf(pixel_avg);
            image[i][j].rgbtRed = pixel_avg_int;
            image[i][j].rgbtBlue = pixel_avg_int;
            image[i][j].rgbtGreen = pixel_avg_int;
            free(temp);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE tempFlip[width];

        memset(tempFlip, 0, width*sizeof(RGBTRIPLE));

        for (int j = 0; j < width; j++)
        {

            tempFlip[j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            tempFlip[j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            tempFlip[j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
        }

        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tempFlip[j].rgbtBlue;
            image[i][j].rgbtRed = tempFlip[j].rgbtRed;
            image[i][j].rgbtGreen = tempFlip[j].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE tempImage[height][width];
    memset(tempImage, 0, height*width*sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float *blueSum = malloc(sizeof(float));
            float *redSum = malloc(sizeof(float));
            float *greenSum = malloc(sizeof(float));
            float *avgCount = malloc(sizeof(float));
            *blueSum = 0;
            *redSum = 0;
            *greenSum = 0;
            *avgCount = 0;



            for (int blur_height = i - 1; blur_height <= i + 1; blur_height++)
            {
                for (int blur_width = j - 1; blur_width <= j + 1; blur_width++)
                {
                    if (blur_height >= 0 && blur_height < height && blur_width >= 0 && blur_width < width)
                    {
                        (*avgCount)++;
                        *blueSum += image[blur_height][blur_width].rgbtBlue;
                        *redSum += image[blur_height][blur_width].rgbtRed;
                        *greenSum += image[blur_height][blur_width].rgbtGreen;


                    }
                    else
                    {

                    }

                }
            }

            tempImage[i][j].rgbtBlue = roundf(*blueSum / *avgCount);
            tempImage[i][j].rgbtRed = roundf(*redSum / *avgCount);
            tempImage[i][j].rgbtGreen = roundf(*greenSum / *avgCount);


        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
        }

    }
    return;

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int* Gx_red = malloc(sizeof(float));
    int* Gx_blue = malloc(sizeof(float));
    int* Gx_green = malloc(sizeof(float));
    int* Gy_red = malloc(sizeof(float));
    int* Gy_blue = malloc(sizeof(float));
    int* Gy_green = malloc(sizeof(float));

    RGBTRIPLE tempImage[height][width];

    memset(tempImage, 0, height*width*sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            *Gx_red = 0;
            *Gx_blue = 0;
            *Gx_green = 0;
            *Gy_red = 0;
            *Gy_blue = 0;
            *Gy_green = 0;

            int xMat[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int yMat[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


            for (int xk_h = i - 1, mat_y = 0; xk_h <= i + 1; xk_h++, mat_y++)
            {
                for (int xk_w = j - 1, mat_x = 0; xk_w <= j + 1; xk_w++, mat_x++)
                {
                    if (xk_h >= 0 && xk_h < height && xk_w >= 0 && xk_w < width)
                    {
                        *Gx_red += xMat[mat_y][mat_x] * image[xk_h][xk_w].rgbtRed;
                        *Gy_red += yMat[mat_y][mat_x] * image[xk_h][xk_w].rgbtRed;

                        *Gx_blue += xMat[mat_y][mat_x] * image[xk_h][xk_w].rgbtBlue;
                        *Gy_blue += yMat[mat_y][mat_x] * image[xk_h][xk_w].rgbtBlue;

                        *Gx_green += xMat[mat_y][mat_x] * image[xk_h][xk_w].rgbtGreen;
                        *Gy_green += yMat[mat_y][mat_x] * image[xk_h][xk_w].rgbtGreen;
                    }
                }
            }

            if ( sqrtf( powf(*Gx_red, 2.0) + powf(*Gy_red, 2.0) ) > 255 )
            {
                tempImage[i][j].rgbtRed = 255;
            }
            else
            {
                tempImage[i][j].rgbtRed = round(sqrt( powf(*Gx_red, 2.0) + powf(*Gy_red, 2.0)));
            }

             if ( sqrtf( powf(*Gx_blue, 2.0) + powf(*Gy_blue, 2.0) ) > 255 )
            {
                tempImage[i][j].rgbtBlue = 255;
            }
            else
            {
                tempImage[i][j].rgbtBlue = round(sqrt( powf(*Gx_blue, 2.0) + powf(*Gy_blue, 2.0)));
            }


             if ( sqrtf( powf(*Gx_green, 2.0) + powf(*Gy_green, 2.0) ) > 255 )
            {
                tempImage[i][j].rgbtGreen = 255;
            }
            else
            {
                tempImage[i][j].rgbtGreen = round(sqrt( powf(*Gx_green, 2.0) + powf(*Gy_green, 2.0)));
            }


        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
        }

    }
    return;
}