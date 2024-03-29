using System;
using System.Drawing;
using System.ComponentModel;

namespace Labs_1
{
    abstract class Filters
    {
        protected abstract Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y);

        public int Clamp(int value, int min, int max)
        {
            if (value < min) return min;
            if (value > max) return max;
            return value;
        }

        public Bitmap ProcessImage(Bitmap sourceImage, BackgroundWorker worker)
        {
            if (sourceImage == null) // Check if sourceImage is null
                throw new ArgumentNullException("sourceImage");

            Bitmap resultImage = new Bitmap(sourceImage.Width, sourceImage.Height);

            for (int i = 0; i < sourceImage.Width; i++)
            {
                worker.ReportProgress((int)((float)i / sourceImage.Width * 100));
                if (worker.CancellationPending) return null;
                for (int j = 0; j < sourceImage.Height; j++)
                {
                    resultImage.SetPixel(i, j, CalculateNewPixelColor(sourceImage, i, j));
                }
            }
            return resultImage;
        }
    }

    class InvertedImage : Filters
    {
        protected override Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);
            Color resultColor = Color.FromArgb(255 - sourceColor.R, 255 - sourceColor.G, 255 - sourceColor.B);
            return resultColor;
        }
    }

    class GrayImage : Filters
    {
        protected override Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color pixel = sourceImage.GetPixel(x, y);
            int intensity = (int)(0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B);
            return Color.FromArgb(intensity, intensity, intensity);
        }
    }

    class SepiaImage : Filters
    {
        protected override Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            int k = 20;

            Color pixel = sourceImage.GetPixel(x, y);
            int intensity = (int)(0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B);

            int sepiaR = intensity + 2 * k;
            int sepiaG = intensity + (int)(0.5 * k);
            int sepiaB = intensity - k;

            sepiaR = Clamp(sepiaR, 0, 255);
            sepiaG = Clamp(sepiaG, 0, 255);
            sepiaB = Clamp(sepiaB, 0, 255);

            return Color.FromArgb(sepiaR, sepiaG, sepiaB);
        }
    }

    class BrightnessIncreaseFilter : Filters
    {
        protected override Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color pixel = sourceImage.GetPixel(x, y);

            // Increase the intensity of each color channel by 20
            int newR = pixel.R + 20;
            int newG = pixel.G + 20;
            int newB = pixel.B + 20;

            // Ensure new color values are within the valid range [0, 255] using the Clamp method
            newR = Clamp(newR, 0, 255);
            newG = Clamp(newG, 0, 255);
            newB = Clamp(newB, 0, 255);

            // Return the new pixel color
            return Color.FromArgb(newR, newG, newB);
        }
    }
    class ShiftRightFilter : Filters
    {
        protected override Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            if (x >= 50 && x < sourceImage.Width)
            {
                return sourceImage.GetPixel(x - 50, y);
            }
            else
            {
                return Color.Black;
            }
        }
    }

    class GrayWorldFilter : Filters
    {
        protected override Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color pixelColor = sourceImage.GetPixel(x, y);

            // Initialize average RGB values
            double Avg_R = 0;
            double Avg_G = 0;
            double Avg_B = 0;

            // Calculate sum of RGB values for the entire image
            for (int i = 0; i < sourceImage.Width; i++)
            {
                for (int j = 0;j < sourceImage.Height; j++)
                {
                    Color color = sourceImage.GetPixel(i, j);
                    Avg_R += color.R;
                    Avg_G += color.G;
                    Avg_B += color.B;
                }
            }

            // Calculate average RGB values
            int totalPixels = sourceImage.Width * sourceImage.Height;
            Avg_R /= totalPixels;
            Avg_G /= totalPixels;
            Avg_B /= totalPixels;

            // Calculate new RGB values for the current pixel using Gray World algorithm
            int resultR = (int)(pixelColor.R * (Avg_R / Avg_R));
            int resultG = (int)(pixelColor.G * (Avg_G / Avg_G));
            int resultB = (int)(pixelColor.B * (Avg_B / Avg_B));

            // Ensure the calculated RGB values are within the valid range [0, 255]
            resultR = Math.Min(Math.Max(resultR, 0), 255);
            resultG = Math.Min(Math.Max(resultG, 0), 255);
            resultB = Math.Min(Math.Max(resultB, 0), 255);

            // Return the new color for the current pixel
            return Color.FromArgb(resultR, resultG, resultB);
        }
    }
}
