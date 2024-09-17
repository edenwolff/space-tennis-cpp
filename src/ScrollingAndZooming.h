#pragma once

#include "DrawingSurface.h"

// See FilterPoints.h for what these classes/methods do
// This file contains some examples of using the FilterPoints classes to change how drawing is done.

// Filter to apply a scaling to the points
class FilterScaling : public FilterPoints
{
public:
	FilterScaling(int xStretch, int xCompress, int yStretch, int yCompress, FilterPoints* pNextFilter = nullptr)
		: pNextFilter(pNextFilter), xStretch(xStretch), yStretch(yStretch), xCompress(xCompress), yCompress(yCompress)
	{
		// Everything has a minimum one
		if (xStretch < 1) xStretch = 1;
		if (yStretch < 1) yStretch = 1;
		if (xCompress < 1) xCompress = 1;
		if (xCompress < 1) xCompress = 1;
		// If stretch is set then compress is not, and vice versa
		if (xStretch > 1) xCompress = 1;
		if (yStretch > 1) xCompress = 1;
	}

	FilterScaling(int xFactor, int yFactor, FilterPoints* pNextFilter = nullptr)
		: pNextFilter(pNextFilter), xStretch(1), yStretch(1), xCompress(1), yCompress(1)
	{
		setStretch(xFactor, yFactor);
		//printf("FilterPointsScaling: %d,%d %d,%d\n", xStretch, yStretch, xCompress, yCompress);
	}

	/*
	This is a bit tricky because if zoomed in we probably need to set a square of pixels instead of a single one.
	So we use functions to do the x then y loops.
	*/
	virtual bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		handleXthenY(surface, xVirtual, yVirtual, uiColour);
		return false; // We already coloured the pixel anyway
	}

	// Calculate real from virtual position - apply the stretch then any following filter
	virtual int filterConvertVirtualToRealXPosition(int xVirtual) override
	{
		if (xStretch > 1)
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual * xStretch);
			else
				return xVirtual * xStretch;
		}
		else
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual / xCompress);
			else
				return xVirtual / xCompress;
		}
	}

	// Calculate real from virtual position - apply the stretch then any following filter
	virtual int filterConvertVirtualToRealYPosition(int yVirtual) override
	{
		if (yStretch > 1)
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual * yStretch);
			else
				return yVirtual * yStretch;
		}
		else
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual / xCompress);
			else
				return yVirtual / yCompress;
		}
	}

	// These convert from a clicked location to a virtual pixel position in a surface
	virtual int filterConvertRealToVirtualXPosition(int xReal) override
	{
		// Apply other filter first if it exists (since we are reversing the order we used for virtual to real)
		if (pNextFilter)
			xReal = pNextFilter->filterConvertRealToVirtualXPosition(xReal);
		// Other filter has now been applied so we can try to reverse the effect of THIS filter...
		if (xStretch > 1)
			return xReal / xStretch;
		else
			return xReal * xCompress;
	}
	virtual int filterConvertRealToVirtualYPosition(int yReal) override
	{
		if (pNextFilter)
			yReal = pNextFilter->filterConvertRealToVirtualYPosition(yReal);
		if (yStretch > 1)
			return yReal / yStretch;
		else
			return yReal * yCompress;
	}

	void stretchX() { if (xCompress > 1) --xCompress; else ++xStretch; }
	void stretchY() { if (yCompress > 1) --yCompress; else ++yStretch; }
	void compressX() { if (xStretch > 1) --xStretch; else ++xCompress; }
	void compressY() { if (yStretch > 1) --yStretch; else ++yCompress; }

	void compress() { compressX(); compressY(); }
	void stretch() { stretchX(); stretchY(); }

	void setStretch(int xFactor, int yFactor)
	{
		if (xFactor == 0) { xStretch = 1; xCompress = 1; }
		else if (xFactor < 0) { xStretch = 1; xCompress = 1 - xFactor; }
		else if (xFactor > 0) { xStretch = 1 + xFactor; xCompress = 1; }
		if (yFactor == 0) { yStretch = 1; yCompress = 1; }
		else if (yFactor < 0) { yStretch = 1; yCompress = 1 - yFactor; }
		else if (yFactor > 0) { yStretch = 1 + yFactor; yCompress = 1; }
	}

	float getZoomX()
	{
		int v1 = xStretch; if (v1 < 1) v1 = 1;
		int v2 = xCompress; if (v2 < 1) v2 = 1;
		return (float)v1 / (float)v2;
	}

	float getZoomY()
	{
		int v1 = yStretch; if (v1 < 1) v1 = 1;
		int v2 = yCompress; if (v2 < 1) v2 = 1;
		return (float)v1 / (float)v2;
	}


private:
	FilterPoints* pNextFilter;
	int xStretch, yStretch, xCompress, yCompress;

	void handleXthenY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
	{
		if (xStretch > 1)
		{
			xVirtual *= xStretch;
			for (int i = 0; i < xStretch; i++)
				handleY(surface, xVirtual + i, yVirtual, uiColour);
		}
		else 
		{
			xVirtual /= xCompress; 
			handleY(surface, xVirtual, yVirtual, uiColour);
		}
	}

	void handleY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
	{
		if (yStretch > 1)
		{
			yVirtual *= yStretch;
			for (int i = 0; i < yStretch; i++)
			{
				int yTest = yVirtual + i;
				if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yTest, uiColour))
					surface->rawSetPixel(xVirtual, yTest, uiColour);
			}
		}
		else
		{
			yVirtual /= yCompress;
			if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
				surface->rawSetPixel(xVirtual, yVirtual, uiColour);
		}
	}
};

class FilterTranslation : public FilterPoints
{
public:
	FilterTranslation(int xModifier, int yModifier, FilterPoints* pNextFilter = nullptr)
		: xModifier(xModifier), yModifier(yModifier), pNextFilter(pNextFilter)
	{
	}

	virtual bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		xVirtual += xModifier;
		yVirtual += yModifier;
		return (pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour);
	}

	void setOffset(int offsetX, int offsetY)
	{
		xModifier = offsetX;
		yModifier = offsetY;
	}

	int getXOffset() { return xModifier; }
	int getYOffset() { return yModifier; }

	void changeOffset(int offsetXIncrement, int offsetYIncrement)
	{
		xModifier += offsetXIncrement;
		yModifier += offsetYIncrement;
	}

private:
	int xModifier, yModifier;
	FilterPoints* pNextFilter;
};
