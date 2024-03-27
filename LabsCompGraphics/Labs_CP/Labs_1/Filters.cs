﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Labs_1
{
    abstract class Filters
    {
        protected abstract Color calculateNewPixelColor(Bitmap sourceImage, int x, int y);
        public int Clamp(int value,int min, int max)
        {
            if (value < min ) return min;
            if (value > max ) return max;
            return value;
        }
        public Bitmap processImage(Bitmap sourceImage,BackgroundWorker worker)
        {
            Bitmap resultImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            for (int i=0;i< sourceImage.Width;i++)
            {
                worker.ReportProgress((int)((float)i / resultImage.Width * 100));
                if (worker.CancellationPending) return null;
                for (int j = 0; j < sourceImage.Height; j++)
                {
                    resultImage.SetPixel(i,j,calculateNewPixelColor(sourceImage,i,j));
                }
            }
            return resultImage;
        }

    }
    class invertedImage : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x,y);
            Color resultColor = Color.FromArgb(255 - sourceColor.R,255 - sourceColor.G,255 - sourceColor.B);
            return resultColor;

        }
    }
    class grayImage : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color pixel = sourceImage.GetPixel(x, y);
            int intensity = (int)(0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B);
            return Color.FromArgb(intensity, intensity, intensity);
        }
    }

}

