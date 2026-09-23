// Composite.cpp : Pixel-wise composite operations (Term Project 01)
//
// A pixel belongs to a "figure" when its color is far enough from the
// background color. The background color is read from the top-left corner,
// so the code still works if the shapes are moved, resized or recolored.

#include "stdafx.h"
#include "Composite.h"

// Squared RGB distance a pixel must exceed to count as a figure pixel.
// The margin makes the detection robust against JPEG noise.
static const int FIGURE_THRESHOLD = 60 * 60;

static int ColorDistance(RGBQUAD a, RGBQUAD b)
{
	int dr = a.rgbRed   - b.rgbRed;
	int dg = a.rgbGreen - b.rgbGreen;
	int db = a.rgbBlue  - b.rgbBlue;
	return dr * dr + dg * dg + db * db;
}

static RGBQUAD MakeColor(BYTE r, BYTE g, BYTE b)
{
	RGBQUAD c;
	c.rgbRed = r;
	c.rgbGreen = g;
	c.rgbBlue = b;
	c.rgbReserved = 0;
	return c;
}

static RGBQUAD BackgroundColor(CxImage* pImage)
{
	return pImage->GetPixelColor(0, 0);
}

static bool IsFigure(CxImage* pImage, long x, long y, RGBQUAD background)
{
	return ColorDistance(pImage->GetPixelColor(x, y), background) > FIGURE_THRESHOLD;
}

// Average color of all figure pixels.
static RGBQUAD AverageFigureColor(CxImage* pImage, long width, long height, RGBQUAD background)
{
	long sumR = 0, sumG = 0, sumB = 0, count = 0;

	for (long y = 0; y < height; y++) {
		for (long x = 0; x < width; x++) {
			RGBQUAD c = pImage->GetPixelColor(x, y);
			if (ColorDistance(c, background) > FIGURE_THRESHOLD) {
				sumR += c.rgbRed;
				sumG += c.rgbGreen;
				sumB += c.rgbBlue;
				count++;
			}
		}
	}

	if (count == 0)
		return background;
	return MakeColor((BYTE)(sumR / count), (BYTE)(sumG / count), (BYTE)(sumB / count));
}

// Picks the first candidate that is clearly different from both figures
// and from the background.
static RGBQUAD PickOverlapColor(RGBQUAD first, RGBQUAD second, RGBQUAD background)
{
	const RGBQUAD candidates[] = {
		MakeColor(255, 220,   0),	// yellow
		MakeColor(255, 255, 255),	// white
		MakeColor(255,   0, 255),	// magenta
		MakeColor(  0, 255, 255)	// cyan
	};
	const int minDistance = 4 * FIGURE_THRESHOLD;

	for (int i = 0; i < 4; i++) {
		if (ColorDistance(candidates[i], first)      > minDistance &&
			ColorDistance(candidates[i], second)     > minDistance &&
			ColorDistance(candidates[i], background) > minDistance)
			return candidates[i];
	}
	return candidates[0];
}

// Only the area covered by both images is processed,
// in case the input sizes differ slightly.
static void CommonSize(CxImage* pFirst, CxImage* pSecond, long& width, long& height)
{
	width  = (long)pFirst->GetWidth();
	height = (long)pFirst->GetHeight();

	if ((long)pSecond->GetWidth()  < width)  width  = (long)pSecond->GetWidth();
	if ((long)pSecond->GetHeight() < height) height = (long)pSecond->GetHeight();
}

void CompositeAdd(CxImage* pFirst, CxImage* pSecond)
{
	long width, height;
	CommonSize(pFirst, pSecond, width, height);

	RGBQUAD firstBackground  = BackgroundColor(pFirst);
	RGBQUAD secondBackground = BackgroundColor(pSecond);

	RGBQUAD overlapColor = PickOverlapColor(
		AverageFigureColor(pFirst,  width, height, firstBackground),
		AverageFigureColor(pSecond, width, height, secondBackground),
		firstBackground);

	for (long y = 0; y < height; y++) {
		for (long x = 0; x < width; x++) {
			bool inFirst  = IsFigure(pFirst,  x, y, firstBackground);
			bool inSecond = IsFigure(pSecond, x, y, secondBackground);

			if (inFirst && inSecond)
				pFirst->SetPixelColor(x, y, overlapColor);                     // overlap
			else if (inSecond)
				pFirst->SetPixelColor(x, y, pSecond->GetPixelColor(x, y));     // second figure only
			// first figure only, or background: keep the pixel as it is
		}
	}
}

void CompositeSubtract(CxImage* pFirst, CxImage* pSecond)
{
	long width, height;
	CommonSize(pFirst, pSecond, width, height);

	RGBQUAD firstBackground  = BackgroundColor(pFirst);
	RGBQUAD secondBackground = BackgroundColor(pSecond);

	for (long y = 0; y < height; y++) {
		for (long x = 0; x < width; x++) {
			if (IsFigure(pSecond, x, y, secondBackground))
				pFirst->SetPixelColor(x, y, firstBackground);
		}
	}
}
