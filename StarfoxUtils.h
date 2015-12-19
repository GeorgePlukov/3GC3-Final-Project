#ifndef __STARFOXUTILS_H__
#define __STARFOXUTILS_H__ 

#include "PMath/PPoint.h"
#include <cstdlib>
#include <ctime>

class StarfoxUtils
{
public:
	StarfoxUtils();
	PPoint3f getRandomBuildingScaling();
	PPoint3f getRandomBuildingTranslation();

private:
	float generateRandomNumber(int,int);

};

#endif