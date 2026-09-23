// Composite.h : Pixel-wise composite operations (Term Project 01)
//
// Both functions change the first image in place and only use the
// basic CxImage accessors: GetWidth, GetHeight, GetPixelColor, SetPixelColor.

#pragma once

// first = first + second
// Figures of both images are merged. Where the figures overlap,
// the pixels get a new color that differs from both figures.
void CompositeAdd(CxImage* pFirst, CxImage* pSecond);

// first = first - second
// Every figure pixel of the second image becomes background in the first image.
void CompositeSubtract(CxImage* pFirst, CxImage* pSecond);
