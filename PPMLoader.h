#ifndef PPMLoader_D
#define PPMLoader_D
#include "includes.h"


class PPMLoader {
public:

	// Constructor
	PPMLoader();
	GLubyte* loadPPM(char* file, int* width, int* height, int* max);
};

#endif
