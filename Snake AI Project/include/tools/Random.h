#pragma once

#ifndef _RANDOM_H
#define _RANDOM_H

#include <random>

namespace Tools
{
	class Random final
	{
	private:
		static std::default_random_engine s_generator;

	public:
		/* Desactivate the constructor (Un-instanciable static class) */
		Random() = delete;

		/**
		* Generate a random between two given integers (Closed interval)
		* @param p_min
		* @param p_max
		*/
		template<typename T>
		static T GenerateInt(T p_min, T p_max)
		{
			std::uniform_int_distribution<std::mt19937::result_type> dist6(p_min, p_max);
			return  dist6(s_generator);
		}

		/**
		* Generate a random between two given floats (Closed interval)
		* @param p_min
		* @param p_max
		*/
		template<typename T>
		static T GenerateFloat(T p_min, T p_max)
		{
			std::uniform_int_distribution<std::mt19937::result_type> dist6(p_min, p_max);
			return  dist6(s_generator);
		}

		/**
		* Verify if the percentage is satisfied
		* @param p_percentage
		*/
		static bool CheckPercentage(float p_percentage);
	};
}

#endif //_RANDOM_H
