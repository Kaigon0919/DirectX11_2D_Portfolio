#include "MyRandom.h"

int RandomInt(int min, int max)
{
	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<int> range(min, max);

	return range(rnd);
}
