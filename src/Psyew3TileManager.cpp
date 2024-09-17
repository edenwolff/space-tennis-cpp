#include "header.h"
#include "Psyew3TileManager.h"
#include "Psyew3Engine.h"
#include "ObjectMapper.h"

/* Tile manager drawing manager */
void Psyew3TileManager::virtDrawTileAt(
	BaseEngine* e,
	DrawingSurface* ds,
	int mapX, int mapY,
	int startX, int startY) const
{
	if (mapX == 0 && mapY == 0)
	{
		racket.renderImageApplyingMapping(e, ds, startX, startY, 100, 100, (ImagePixelMapping*)&oMapper);

		if (getMapValue(0, 0) == 10)
		{
			selectedRacket.renderImageApplyingMapping(e, ds, startX, startY, 100, 100, (ImagePixelMapping*)&oMapper);
		}
	}

	else if((mapX == 0 && mapY == 1))
	{
		racket2.renderImageApplyingMapping(e, ds, startX, startY, 100, 100, (ImagePixelMapping*)&oMapper);
	}

	else if ((mapX == 1 && mapY == 0))
	{
		ballSkin.renderImageApplyingMapping(e, ds, startX, startY, 100, 100, (ImagePixelMapping*)&oMapper);
	}

	else
	{
		orangeBallSkin.renderImageApplyingMapping(e, ds, startX, startY, 100, 100, (ImagePixelMapping*)&oMapper);
	}
}