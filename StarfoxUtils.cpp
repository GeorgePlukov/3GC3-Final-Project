#include "StarfoxUtils.h"

StarfoxUtils::StarfoxUtils()
{
	srand(time(0));
}

/* Generate scalings of varying heights*/
PPoint3f StarfoxUtils::getRandomBuildingScaling()
{
	return PPoint3f(1,generateRandomNumber(10,20),1);
}

/* Generate translations outside of the clipping plane!*/
PPoint3f StarfoxUtils::getRandomBuildingTranslation()
{
	return PPoint3f(generateRandomNumber(-10,10), 0, generateRandomNumber(-60, -1));
}

float StarfoxUtils::generateRandomNumber(int min, int max)
{
	return rand() % (max-min) + min;
}