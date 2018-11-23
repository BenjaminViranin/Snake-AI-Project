
#include "include/tools/Random.h"
#include <ctime>
#include <type_traits>

using namespace Tools;

std::default_random_engine Random::s_generator = std::default_random_engine(static_cast<unsigned int>(time(0)));

bool Random::CheckPercentage(float p_percentage)
{
	std::uniform_real_distribution<float> distribution(0.0f, 100.0f);
	return distribution(s_generator) <= p_percentage;
}