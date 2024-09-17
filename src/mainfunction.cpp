#include "header.h"
#include <ctime>

#include "Psyew3Engine.h"

// These are passed to initialise to determine the window size
const int BaseScreenWidth = 1200;
const int BaseScreenHeight = 659;


// This was only moved outside of main so that I can do some memory checking once it ends.
// Main calls this then checks for errors before ending.
int doProgram(int argc, char *argv[])
{ 
	int iResult = 0;

	Psyew3Engine oMainDemoObject;

	char buf[1024];
	// Screen caption can be set on following line...
	sprintf(buf, "Space Tennis", BaseScreenWidth, BaseScreenHeight);
	iResult = oMainDemoObject.initialise(buf, BaseScreenWidth, BaseScreenHeight, "Cornerstone Regular.ttf", 24);

	iResult = oMainDemoObject.mainLoop();
	oMainDemoObject.deinitialise();
	return iResult;
} // Main object (created on the stack) gets destroyed at this point, so it will free its memory

/* Separate main function, so we can check for memory leaks after objects are destroyed */
int main(int argc, char *argv[])
{
	// Send random number generator with current time
	::srand( (unsigned int)time(0));

	int iResult = doProgram( argc, argv );
		
	// Free the cached images by destroying the image manager
	// Ensure that you do this AFTER the main object and any other objects have been destroyed
	// The game object is a stack object inside doProgram() so will have been 
	ImageManager::destroyImageManager();
	
	// Uncomment the following line to introduce a memory leak!
	// new int();
	// _CrtDumpMemoryLeaks() should make Visual studio tell you about memory leaks when it ends. 
	/* e.g.:
	Detected memory leaks!
		Dumping objects ->
	{189} normal block at 0x0358C828, 4 bytes long.
		Data: < > 00 00 00 00
		Object dump complete.
	*/

// Detect memory leaks on windows if building for debug (not release!)
#if defined(_MSC_VER)
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
#endif

	return iResult;
}
