#include "header.h"
#include "ObjectMapper.h"
#include "DrawingSurface.h"

bool ObjectMapper::mapCoordinates(double& x, double& y, const SimpleImage& image)
{
	// First apply any shift into the image
	x += m_iSourceShiftX;
	y += m_iSourceShiftY;

	// Now check that coordinates are actually within the image
	// To be honest I'm thinking this may be unnecessary, since we validate after the rotation anyway
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	if (1)
	{	// Don't bother doing these calculations if we have no rotation, they would just slow it down...

		// Shift offset to the rotation centre, so we can rotate around centre
		x -= m_iRotationCentreX;
		y -= m_iRotationCentreY;

		// Rotate it
		double dAngle = atan(y / (x + 0.0001));
		if (x < 0)
			dAngle += M_PI;
		double hyp = ::sqrt(x * x + y * y);
		dAngle += (double)rotation;

		x = hyp * ::cos(dAngle);
		y = hyp * ::sin(dAngle);

		// Shift offset back to the corner
		x += m_iRotationCentreX;
		y += m_iRotationCentreY;

		// Verify that new coordinates are still within the image
		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= (image.getWidth() - 0.5)) return false;
		if (y >= (image.getHeight() - 0.5)) return false;
	}

	return true;
}

bool ObjectMapper::changePixelColour(int x, int y, int& iNewColour, DrawingSurface* pTarget)
{
	// If pixel is transparency colour (black), then don't draw
	if (iNewColour == 0)
	{
		return false;
	}
	return true;
}

int ObjectMapper::getTransparencyColour()
{
	return m_iTransparencyColour;
}

