#include "StarfoxUtils.h"

StarfoxUtils::StarfoxUtils()
{
	srand(time(0));
}

PPoint3f StarfoxUtils::getRandomBuildingScaling()
{
	return PPoint3f(1,generateRandomNumber(10,20),1);
}

PPoint3f StarfoxUtils::getRandomBuildingTranslation()
{
	return PPoint3f(generateRandomNumber(-10,10), 0, generateRandomNumber(-70, 70));
}

float StarfoxUtils::generateRandomNumber(int min, int max)
{
	return rand() % (max-min) + min;
}