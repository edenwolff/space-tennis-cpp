#pragma once
#include "DrawingSurface.h"
#include "ImagePixelMapping.h"


class ObjectMapper :
    public ImagePixelMappingRotateAndColour
{
public:
    ObjectMapper() : ImagePixelMappingRotateAndColour(0.0, 50 , 50) 
    {
    };


    bool mapCoordinates(double&, double&, const SimpleImage&) override;
    bool changePixelColour(int, int, int&, DrawingSurface*);
    int getTransparencyColour();
};
